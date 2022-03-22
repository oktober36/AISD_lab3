#ifndef LAB3_DIALOG_H
#define LAB3_DIALOG_H
#include "table.h"

int getInt();
char *getStr();
int getOption(int optionNum, char *msg, char *errMsg, char **options);

int dialog();
void DAdd(Table *table);
void DFind(Table *table);
void DDelete(Table *table);
void DShow(Table *table);
void DClear(Table *table);
#endif //LAB3_DIALOG_H
