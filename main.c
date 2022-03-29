#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dialog.h"


main(){
    Table *table;
    int msize2;
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
}
