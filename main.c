#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dialog.h"


main(){
    Table *table;
    int msize2;
    char *fNames;

    puts("Enter file names");
    fNames = getStr();
    setFileNames(fNames);
    puts("Enter size of keyspace 2");
    msize2 = getInt();
    if (!(table = initTable(msize2))){
        puts("Error");
        return 1;
    }
    dialog(table);
    KS1save(table->ks1, table -> csize);
    KS2save(table->ks2, table -> csize);
    return 0;


    /*char *s, *k1, *k2, *i1, *i2;
    table = initTable(1);
    k1 = calloc(7, sizeof(char));
    k2 = calloc(7, sizeof(char));
    i1 = calloc(7, sizeof(char));
    i2 = calloc(7, sizeof(char));
    s = "fddfwd";
    strcpy(k1, s);
    s = "rfgthv";
    strcpy(k2, s);
    s = "fntnds";
    strcpy(i1, s);
    s = "fntnds";
    strcpy(i2, s);
    push(table, 1, k1, i1);
    push(table, 2, k2, i2);
    DShow(table);
    return 0;*/
}
