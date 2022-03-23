#include "keySpace2.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int M2_SIZE;
const char *saveFile = "C:/AISD/lab3/keys2.bin";

int hash(char *key) {
    unsigned int hash = 2139062143;
    for (; *key; key++)
        hash = 37 * hash + *key;
    return (int) hash % M2_SIZE;
}

int lastRelease(KeySpace2 **tab, char *key) {
    KeySpace2 *cur = tab[hash(key)];
    for (; cur; cur = cur->next) {
        if (!strcmp(key, cur->key)) {
            return cur->release;
        }
    }
    return 0;
}

void freeNode(KeySpace2 *node){
    free(node->key);
    node->release = 0;
    node->offset = 0;
    node->len = 0;
    free(node);
}

int KS2init(KeySpace2 ***tab, int msize) {
    int n, key2size;
    FILE *fd;

    M2_SIZE = msize;
    *tab = (KeySpace2 **) calloc(msize, sizeof(KeySpace2 *));
    while (--msize >= 0)
        *tab[msize] = NULL;
    if ((fd = fopen(saveFile, "rb"))) {
        fread(&n, sizeof(int), 1, fd);
        while(--n >= 0) {
            int h;
            KeySpace2 *cur = (KeySpace2 *) calloc(1, sizeof(KeySpace2));
            if (!cur)
                return 0;
            fread(&key2size, sizeof(int), 1, fd);
            cur->key = (char *) calloc( key2size, sizeof (char ));
            fread(cur->key, sizeof(char), key2size, fd);
            fread(&cur->release, sizeof(int), 1, fd);
            fread(&cur->offset, sizeof(int), 1, fd);
            fread(&cur->len, sizeof(int), 1, fd);
            h = hash(cur->key);
            (*tab)[h] = cur;
            cur->next = (*tab)[h];
        }
    }
    return 1;
}

int KS2push(KeySpace2 **tab, char *key, int offset, int len) {
    int release, h;
    KeySpace2 *new =(KeySpace2 *) malloc(sizeof(KeySpace2));
    
    if (!new)
        return 0;
    h = hash(key);
    release = lastRelease(tab, key);
    new->next = tab[h];
    new->release = release + 1;
    new->key = key;
    new->offset = offset;
    new->len = len;
    tab[h] = new;
    return 1;
}

KeySpace2 **KS2search(KeySpace2 **tab, char *key) {
    KeySpace2 **out = NULL, *cur;
    int msize = M2_SIZE;
    char *keyCopy;
    int keySize;

    cur = tab[hash(key)];    
    for (; cur; cur = cur->next) {
        if (!strcmp(key, cur->key)) {
            if (!out){
                if (!(out = (KeySpace2 **) calloc(msize, sizeof(KeySpace2 *))))
                    return NULL;
                while (--msize >= 0)
                    tab[msize] = NULL;
            }
            keySize = (int) strlen(cur->key) + 1;
            keyCopy = (char *) calloc(keySize, sizeof (char));            
            if (!KS2push(out, keyCopy, cur->offset, cur->len)){
                free(keyCopy);
                KS2free(out);
                return NULL;
            }                
        }
    }
    return out;
}

Item *KS2searchRelease(KeySpace2 **tab, char *key, int release) {
    KeySpace2 *cur = tab[hash(key)];
    
    for (; cur; cur = cur->next) {
        if (cur->release == release && !strcmp(key, cur->key))
            return readItem(cur->offset, cur->len);
    }
    return NULL;
}

int KS2deleteRelease(KeySpace2 **tab, char *key, int release){
    KeySpace2 **cur = &(tab[hash(key)]);
    
    for (; *cur; cur = &((*cur)->next)) {
        if (!(strcmp((*cur)->key, key)) && (*cur)->release == release) {
            KeySpace2 *buf = *cur;
            *cur = buf->next;
            freeNode(buf);
            return 1;
        }
    }
    return 0;
}

int KS2delete(KeySpace2 **tab, char *key){
    KeySpace2 **cur = &(tab[hash(key)]);
    int deleted = 0;

    while (*cur) {
        if (!(strcmp((*cur)->key, key))) {
            KeySpace2 *buf = *cur;
            *cur = buf->next;
            freeNode(buf);
            deleted += 1;
        } else
            cur = &((*cur)->next);
    }
    return deleted;
}

void KS2print(KeySpace2 **tab){
    int i = M2_SIZE;
    while (--i >= 0){
        KeySpace2 *cur = tab[i];
        for (; cur; cur = cur->next){
            Item *item = readItem(cur->offset, cur->len);
            printf("%d, %s: %s\n", item->key1, item->key2, item->info);
            freeItem(item);
        }
    }
}

void KS2free(KeySpace2 **tab){
    int i;
    for (i = 0; i < M2_SIZE; i++){
        KeySpace2 *cur = tab[i];
        while (cur){
            KeySpace2 *buf = cur;
            cur = buf->next;
            free(buf);
            buf = NULL;
        }
    }
    free(tab);
}

