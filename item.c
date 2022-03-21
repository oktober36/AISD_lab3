#include "item.h"
#include "stdio.h"

void printItem(Item *item){
    printf("%d %s: %s", item->key1, item->key2, item->info);
}

