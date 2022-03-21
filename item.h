#ifndef LAB3_ITEM_H
#define LAB3_ITEM_H

typedef struct Item {
    char *info;

    int key1;
    char *key2;

    struct KeySpace1 *p1;
    struct KeySpace2 *p2;
} Item;

void printItem(Item *item);

#endif //LAB3_ITEM_H
