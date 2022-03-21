#ifndef LAB3_DIALOG_H
#define LAB3_DIALOG_H
#include "table.h"


extern void(*fptr[ ])(Table *);
int dialog();
int getInt(int *k);
void DAdd(Table *table);
void DFind(Table *table);
void DDelete(Table *table);
void DShow(Table *table);
void DClear(Table *table);
#endif //LAB3_DIALOG_H
