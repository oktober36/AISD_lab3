#include "keySpace2.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int M2_SIZE;

int KS2findRelease(KeySpace2 **tab, char *key);

int KS2init(KeySpace2 ***tab, int msize) {
    int i;
    M2_SIZE = msize;
    *tab = (KeySpace2 **) calloc(sizeof(KeySpace2 *), msize);
    if (!*tab)
        return 0;
    for (i = 0; i < msize; i++)
        (*tab)[i] = NULL;
    return 1;
}

int hash(char *key) {
    unsigned int hash = 2139062143;
    for (; *key; key++)
        hash = 37 * hash + *key;
    return hash % M2_SIZE;
}

KeySpace2 **KS2search(KeySpace2 **tab, char *key) {
    KeySpace2 **out = NULL;
    KeySpace2 *cur = tab[hash(key)];
    for (; cur; cur = cur->next) {
        if (!strcmp(key, cur->key)) {
            if (!out)
                if (!KS2init(&out, cur->release))
                    return NULL;
            if (!KS2push(out, cur->info))
                return NULL;
        }
    }
    return out;
}

Item *KS2searchRelease(KeySpace2 **tab, char *key, int release) {
    KeySpace2 *cur = tab[hash(key)];
    for (; cur; cur = cur->next) {
        if (cur->release == release && !strcmp(key, cur->key))
            return cur->info;
    }
    return NULL;
}

int KS2push(KeySpace2 **tab, Item *info) {
    char *key = info->key2;
    int release, h = hash(key);
    KeySpace2 *new = malloc(sizeof(KeySpace2));
    KeySpace2 *cur = tab[h];
    if (!new)
        return 0;
    release = KS2findRelease(tab, key);
    new->next = cur;
    tab[h] = new;
    tab[h]->release = release + 1;
    tab[h]->key = key;
    tab[h]->info = info;
    info->p2 = tab[h];
    return 1;
}

int KS2deleteRelease(KeySpace2 **tab, char *key, int release){
    KeySpace2 **cur = &(tab[hash(key)]);
    for (; *cur; cur = &((*cur)->next)) {
        if (!(strcmp((*cur)->key, key)) && (*cur)->release == release) {
            KeySpace2 *buf = (*cur);
            *cur = buf->next;
            free(buf);
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
            KeySpace2 *buf = (*cur);
            *cur = buf->next;
            free(buf);
            deleted += 1;
        }
        else{
            cur = &((*cur)->next);
        }
    }
    return deleted;
}

void KS2print(KeySpace2 **tab){
    int i;
    for (i = 0; i < M2_SIZE; i++){
        KeySpace2 *cur = tab[i];
        for (; cur; cur = cur->next){
            printf("%d, %s: %s\n",cur->info->key1, cur->key, cur->info->info);
        }
    }
}

void KS2free(KeySpace2 ***tab){
    int i;
    for (i = 0; i < M2_SIZE; i++){
        KeySpace2 **cur = &((*tab)[i]);
        while (*cur){
            KeySpace2 *buf = (*cur);
            *cur = buf->next;
            free(buf);
        }
    }
    free(*tab);
}

int KS2findRelease(KeySpace2 **tab, char *key){
    KeySpace2 *cur = tab[hash(key)];
    for (; cur; cur = cur->next) {
        if (!strcmp(key, cur->key)) {
            return cur->release;
        }
    }
    return 0;
}

int KS2clear(KeySpace2 **tab, char *key){
    int i, release = KS2findRelease(tab, key);
    KeySpace2 **cur = &(tab[hash(key)]);
    int deleted = 0;

    while (*cur) {
        if (!(strcmp((*cur)->key, key)) && (*cur)->release < release) {
            KeySpace2 *buf = (*cur);
            *cur = buf->next;
            free(buf);
            deleted += 1;
        }
        else{
            cur = &((*cur)->next);
        }
    }
}