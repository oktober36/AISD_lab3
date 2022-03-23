#include "keySpace1.h"
#include <stdio.h>
#include <stdlib.h>

const char *saveFile = "C:/AISD/lab3/keys1.bin";

void freeNode(KeySpace1 *node){
    node->key = 0;
    node->offset = 0;
    node->len = 0;
    node->next = NULL;
    free(node);
}

int KS1init(KeySpace1 ***tab) {
    FILE *fd;
    int n;
    if (!(*tab = (KeySpace1 **) malloc(sizeof(KeySpace1*))))
        return 0;
    **tab = NULL;
    if ((fd = fopen(saveFile, "rb"))) {
        fread(&n, sizeof(int), 1, fd);
        while(--n >= 0) {
            KeySpace1 *cur = (KeySpace1 *) calloc(1, sizeof(KeySpace1));
            if (!cur)
                return 0;
            fread(&cur->key, sizeof(int), 1, fd);
            fread(&cur->offset, sizeof(int), 1, fd);
            fread(&cur->len, sizeof(int), 1, fd);
            **tab = cur;
            cur->next = **tab;
        }
    }
    return 1;
}

int KS1push(KeySpace1 **tab, int key, int offset, int len) {
    KeySpace1 *new;
    if (KS1search(tab, key))
        return 0;
    new = (KeySpace1 *) malloc(sizeof(KeySpace1));
    if (!new)
        return 0;
    new->key = key;
    new->offset = offset;
    new->len = len;
    new->next = *tab;
    *tab = new;
    return 1;
}

Item *KS1search(KeySpace1 **tab, int key) {
    KeySpace1 *buf = *tab;

    for (; buf != NULL; buf = buf->next) {
        if (key == buf->key)
            return readItem(buf->offset, buf->len);
    }
    return NULL;
}

KeySpace1 **KS1searchRange(KeySpace1 **tab, int a, int b) {
    KeySpace1 **out = NULL;
    KeySpace1 *buf = *tab;

    if (a > b)
        return NULL;
    for (; buf; buf = buf->next) {
        if (buf->key >= a && buf->key <= b)
            if (!out){
                if (!(out = (KeySpace1 **) malloc(sizeof (KeySpace1*)))){
                    KS1free(out);
                    return NULL;
                }

                *out = NULL;
            }
            KS1push(out, buf->key, buf->offset, buf->len);
    }
    return out;
}


int KS1delete(KeySpace1 **tab, int key) {
    KeySpace1 **cur = tab;
    for (; *cur; cur = &((*cur)->next)) {
        if ((*cur)->key == key) {
            KeySpace1 *buf = (*cur);
            *cur = buf->next;
            freeNode(buf);
            return 1;
        }
    }
    return 0;
}

void KS1print(KeySpace1 **tab) {
    KeySpace1 *cur = *tab;
    for (; cur; cur = cur->next){
        Item *item = readItem(cur->offset, cur->len);
        printf("%d, %s: %s\n", item->key1, item->key2, item->info);
    }
}

void KS1free(KeySpace1 **tab) {
    KeySpace1 *cur = *tab;
    while (cur) {
        KeySpace1 *buf = cur;
        cur = buf->next;
        freeNode(buf);
        buf = NULL;
    }
    free(tab);
}

void KS1save(KeySpace1 **tab, int size) {
    FILE *fd;

    if ((fd = fopen(saveFile, "wb"))) {

    } else {
        puts("Ошибка в сохранении 1 пространства");
    }
}



