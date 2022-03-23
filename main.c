#include "dialog.h"


int main(){
    /*Table *table;
    table = initTable();
    dialog();
    printf("That's all. Bye!\n");
    return 0;
    */
    Item item1 = {123, "1", "2"};
    Item item2 = {123, "2", "3412"};
//    Item item3 = {123, "3", "2"};
    writeItem(&item1);
    int a = writeItem(&item2);

    readItem(0, 2);
    readItem(a, 5);
    deleteItem(0, 2);
    readItem(0, 5);
    return 0;
}
