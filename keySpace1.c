#include "keySpace1.h"
#include <stdio.h>
#include <stdlib.h>

int KS1init(KeySpace1 ***tab) {
    *tab = (KeySpace1 **) malloc(sizeof(KeySpace1 *));
    if (*tab == NULL)
        return 0;
    **tab = NULL;
    return 1;
}

Item *KS1search(KeySpace1 **tab, int key) {
    KeySpace1 *buf = (*tab);
    for (; buf != NULL; buf = buf->next) {
        if (key == buf->key)
            return buf->info;
    }
    return NULL;
}

KeySpace1 **KS1searchRange(KeySpace1 **tab, int a, int b) {
    KeySpace1 **out = NULL;
    KeySpace1 *buf = *tab;
    if (a > b)
        return NULL;
    for (; buf; buf = buf->next) {
        if (buf->key >= a && buf->key <= b) {
            if (!out)
                if (!KS1init(&out))
                    return NULL;
            if (!KS1push(out, buf->info))
                return NULL;
        }
    }
    return out;
}

int KS1push(KeySpace1 **tab, Item *info) {
    int key = info->key1;
    KeySpace1 *new;
    if (KS1search(tab, key))
        return 0;
    new = (KeySpace1 *) malloc(sizeof(KeySpace1));
    if (!new)
        return 0;
    info->p1 = new;
    new->key = key;
    new->info = info;
    new->next = *tab;
    *tab = new;
    return 1;
}

int KS1delete(KeySpace1 **tab, int key) {
    KeySpace1 **cur = tab;
    for (; *cur; cur = &((*cur)->next)) {
        if ((*cur)->key == key) {
            KeySpace1 *buf = (*cur);
            *cur = buf->next;
            free(buf);
            return 1;
        }
    }
    return 0;
}

void KS1print(KeySpace1 **tab) {
    int i;
    KeySpace1 *cur = *tab;
    for (; cur; cur = cur->next){
        printf("%d, %s: %s\n", cur->key, cur->info->key2, cur->info->info);
        }
}

void KS1free(KeySpace1 ***tab) {
    KeySpace1 **cur = *tab;
    while (*cur) {
        KeySpace1 *buf = (*cur);
        *cur = buf->next;
        free(buf);
    }
}



