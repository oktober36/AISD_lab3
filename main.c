#include <stdio.h>
#include "dialog.h"

int main(){
    Table *table;
    table = initTable();
    dialog();
    printf("That's all. Bye!\n");
    return 0;

    /*Item item1 = {"123", 1, "32", NULL, NULL};
    Item item2 = {"123", 2, "32", NULL, NULL};
    Item item3 = {"123", 3, "32", NULL, NULL};
    push(table, &item1);
    push(table, &item2);
    push(table, &item3);
    clear(table, "32");

    DShow(table);*/

}
