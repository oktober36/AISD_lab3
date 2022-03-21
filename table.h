#ifndef LAB3_TABLE_H
#define LAB3_TABLE_H
#include "keySpace1.h"
#include "keySpace2.h"


typedef struct Table {
    KeySpace1 **ks1;
    KeySpace2 **ks2;
    int msize2;
    int csize1;
    int csize2;
} Table;

int push(Table *tab, Item *info);
Table *initTable();
int deleteByKey1(Table *tab, int key);
int deleteByKey2(Table *tab, char *key);
int clear(Table *tab, char *key);

#endif //LAB3_TABLE_H
