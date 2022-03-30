#include "table.h"
#include "stdlib.h"
#include "string.h"

void setFileNames(char *name){
    int len;
    len = (int) strlen(name);
    KS1saveFile = calloc(24 + len, sizeof (char ));
    sprintf(KS1saveFile, "C:/AISD/lab3/%s.keys1.bin", name);
    KS2saveFile =calloc(24 + len, sizeof (char ));
    sprintf(KS2saveFile, "C:/AISD/lab3/%s.keys2.bin", name);
    values = calloc(25 + len, sizeof (char ));
    sprintf(values, "C:/AISD/lab3/%s.values.bin", name);
}

Table *initTable(int msize2){
    Table *table;
    table = (Table *)malloc(sizeof (Table));
    if (!KS1init(&(table->ks1)))
        return NULL;
    table->csize = KS2init(&(table->ks2), msize2);
    return table;
}
int push(Table *tab, int key1, char *key2, char *info){
    int offset, len, release;
    char *key2Copy;
    Item *item;

    if (KS1find(tab->ks1, key1))
        return 0;
    item = (Item *) malloc(sizeof (Item));
    len = (int) strlen(key2) + 1;
    key2Copy = calloc(len, sizeof (char));
    strcpy(key2Copy, key2);
    release = KS2lastRelease(tab->ks2, key2) + 1;
    item->key1 = key1;
    item->key2 = key2Copy;
    item->release = release;
    item->info = info;
    offset = writeItem(item);

    KS1push(tab->ks1, key1, offset, len);
    KS2push(tab->ks2, key2, release, offset, len);
    tab -> csize++;
    return 1;
}

int findByKey1(Table *tab, int key1){
    Item *item = KS1search(tab->ks1, key1);
    if (!item)
        return 0;
    printf("%d, %s: %s\n", item->key1, item->key2, item->info);
    return 1;
}
int findByKey2(Table *tab, char *key2){
    KeySpace2 **out;
    if (!(out = KS2search(tab->ks2, key2)))
        return 0;
    KS2print(out);
    KS2free(out);
    return 1;
}
int findByPair(Table *tab, int key1, char *key2){
    Item *item = KS1search(tab->ks1, key1);
    if (!(item = KS1search(tab->ks1, key1)))
        return 0;
    if ( strcmp(item->key2, key2) != 0){
        freeItem(item);
        return 0;
    }
    printf("%d, %s: %s\n", item->key1, item->key2, item->info);
    return 1;
}
int findByRelease(Table *tab, char *key2, int release){
    Item *item = KS2searchRelease(tab->ks2, key2, release);
    if (!item)
        return 0;
    printf("%d, %s: %s\n", item->key1, item->key2, item->info);
    return 1;
}
int findByRange(Table *tab, int a, int b){
    KeySpace1 **out;
    if (!(out = KS1searchRange(tab->ks1, a, b)))
        return 0;
    KS1print(out);
    KS1free(out);
    return 1;
}

int deleteByKey1(Table *tab, int key1) {
    Item *item;
    int out;

    if (!(item = KS1search(tab->ks1, key1)))
        return 0;
    KS1delete(tab->ks1, key1);
    out = KS2deleteRelease(tab->ks2, item->key2, item->release);
    tab->csize -= out;
    return out;
}
int deleteByKey2(Table *tab, char *key2){
    int release, deleted;

    for (deleted = 0; (release = KS2lastRelease(tab->ks2, key2)); deleted++){
        Item *item = KS2searchRelease(tab->ks2, key2, release);
        KS1delete(tab->ks1, item->key1);
        freeItem(item);
        KS2deleteRelease(tab->ks2, key2, release);
    }
    tab->csize -= deleted;
    return deleted;

}
int deleteByPair(Table *tab, int key1, char *key2){
    Item *item;
    int out;

    if (!(item = KS1search(tab->ks1, key1)))
        return 0;
    if ( strcmp(item->key2, key2) != 0){
        freeItem(item);
        return 0;
    }
    KS1delete(tab->ks1, key1);
    out = KS2deleteRelease(tab->ks2, item->key2, item->release);
    freeItem(item);

    tab->csize -= out;
    return out;
}

int deleteByRelease(Table *tab, char *key2, int release){
    Item *item;
    int out;

    if (!(item = KS2searchRelease(tab->ks2, key2, release)))
        return 0;
    KS1delete(tab->ks1, item->key1);
    out = KS2deleteRelease(tab->ks2, key2, release);
    freeItem(item);

    tab->csize -= out;
    return out;
}

int clear(Table *tab, char *key2){
    int release, deleted;
    KeySpace2 **found = KS2search(tab->ks2, key2);
    if (!found)
        return 0;
    release = KS2lastRelease(found, key2);
    KS2deleteRelease(found, key2, release);
    for (deleted = 0; (release = KS2lastRelease(found, key2)); deleted++){
        Item *item = KS2searchRelease(found, key2, release);
        KS1delete(tab->ks1, item->key1);
        KS2deleteRelease(tab->ks2, key2, release);
        KS2deleteRelease(found, key2, release);
        freeItem(item);
    }
    KS2free(found);
    tab->csize -= deleted;
    return deleted;
}


