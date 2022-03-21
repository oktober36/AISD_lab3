#include "item.h"

#ifndef LAB3_KEYSPACE1_H
#define LAB3_KEYSPACE1_H

typedef struct KeySpace1 {
    int key;
    Item *info;
    struct KeySpace1 *next;
} KeySpace1;

int KS1init(KeySpace1 ***tab);

Item *KS1search(KeySpace1 **tab, int key);

KeySpace1 **KS1searchRange(KeySpace1 **tab, int a, int b);

int KS1push(KeySpace1 **tab, Item *info);

int KS1delete(KeySpace1 **tab, int key);

void KS1print(KeySpace1 **tab);

#endif //LAB3_KEYSPACE1_H
