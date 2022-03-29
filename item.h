#include "stdio.h"
#ifndef LAB3_ITEM_H
#define LAB3_ITEM_H

typedef struct Item{
    int key1;
    char *key2;
    int release;
    char *info;
} Item;

void freeItem(Item *item);
int writeItem(Item *item);
Item *readItem(int offset, int len);
void deleteItem(int offset, int len);

#endif //LAB3_ITEM_H
