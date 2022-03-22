#include "table.h"
#include "stdlib.h"

Table *initTable(int size){
    Table *table;
    table = (Table *)malloc(sizeof (Table));
    if (!KS1init(&(table->ks1)))
        return NULL;
    if (!KS2init(&(table->ks2), size))
        return NULL;
    table->msize2 = size;
    table->csize1 = 0;
    table->csize2 = 0;
    return table;
}
int push(Table *tab, int key1, char *key2, char *info){return 0;}
int findByKey1(Table *tab, int key1){return 0;}
int findByKey2(Table *tab, char *key2){return 0;}
int findByPair(Table *tab, int key1, char *key2){return 0;}
int findByRelease(Table *tab, char *key2, int release){return 0;}
int findByRange(Table *tab, int a, int b){return 0;}

int deleteByKey1(Table *tab, int key1){return 0;}
int deleteByKey2(Table *tab, char *key2){return 0;}
int deleteByPair(Table *tab, int key1, char *key2){return 0;}
int deleteByRelease(Table *tab, char *key2, int release){return 0;}
int clear(Table *tab, char *key2){return 0;}


