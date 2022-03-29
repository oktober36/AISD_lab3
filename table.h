#ifndef LAB3_TABLE_H
#define LAB3_TABLE_H
#include "keySpace1.h"
#include "keySpace2.h"


typedef struct Table {
    KeySpace1 **ks1;
    KeySpace2 **ks2;
    int csize;
} Table;

Table *initTable();

int push(Table *tab, int key1, char *key2, char *info);

int findByKey1(Table *tab, int key1);
int findByKey2(Table *tab, char *key2);
int findByPair(Table *tab, int key1, char *key2);
int findByRelease(Table *tab, char *key2, int release);
int findByRange(Table *tab, int a, int b);

int deleteByKey1(Table *tab, int key1);
int deleteByKey2(Table *tab, char *key2);
int deleteByPair(Table *tab, int key1, char *key2);
int deleteByRelease(Table *tab, char *key2, int release);
int clear(Table *tab, char *key2);

#endif //LAB3_TABLE_H
