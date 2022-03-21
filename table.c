#include "table.h"
#include "stdlib.h"

Table *initTable(){
    Table *table;
    table = (Table *)malloc(sizeof (Table));
    if (!KS1init(&(table->ks1)))
        return NULL;
    if (!KS2init(&(table->ks2), 20))
        return NULL;
    table->msize2 = 20;
    table->csize1 = 0;
    table->csize2 = 0;
    return table;
}

int push(Table *tab, Item *info){
    if (!KS1push(tab->ks1, info))
        return 0;
    if (!KS2push(tab->ks2, info)){
        KS1delete(tab->ks1, info->key1);
        return 0;
    }
    return 1;
}

int deleteByKey1(Table *tab, int key){
    Item *item;
    if (!(item = KS1search(tab->ks1, key)))
        return 0;
    KS2deleteRelease(tab->ks2, item->key2, item->p2->release);
    KS1delete(&(tab->ks1), key);
    return 1;
}
int deleteByKey2(Table *tab, char *key){
    int i;
    Item *item;
    for (i = 0; item = KS2searchRelease(tab->ks2, key, i+1); i++){
        KS1delete(tab->ks1, item->key1);
    }
    KS2delete(tab->ks2, key);
    return i;
}

int clear(Table *tab, char *key){
    return KS2clear(tab->ks2, key);
}


