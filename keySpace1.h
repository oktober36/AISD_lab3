#include "item.h"

#ifndef LAB3_KEYSPACE1_H
#define LAB3_KEYSPACE1_H

typedef struct KeySpace1 {
    int key;
    int offset;
    int len;
    struct KeySpace1 *next;
} KeySpace1;

int KS1init(KeySpace1 ***tab);
int KS1push(KeySpace1 **tab, int key, int offset, int len);
Item *KS1search(KeySpace1 **tab, int key);
KeySpace1 **KS1searchRange(KeySpace1 **tab, int a, int b);
int KS1delete(KeySpace1 **tab, int key);
void KS1print(KeySpace1 **tab);
void KS1free(KeySpace1 **tab)

#endif //LAB3_KEYSPACE1_H
