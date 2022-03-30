#include "item.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

char *values;

void freeItem(Item *item){
    free(item->info);
    free(item->key2);
    item->info = NULL;
    item->key2 = NULL;
    item->key1 = 0;
    free(item);
}

int writeItem(Item *item){
    int offset, key2size, fLen;
    FILE *fd;

    fd = fopen(values, "a");
    fseek(fd, 0, SEEK_END);
    offset = ftell(fd);
    fwrite(&(item->key1), sizeof (int), 1, fd);
    key2size = strlen(item->key2) + 1;
    fwrite(&key2size, sizeof (int), 1, fd);
    fwrite(item->key2, sizeof (char), key2size, fd);
    fwrite(&item->release, sizeof (int), 1, fd);
    fwrite(item->info, sizeof (char), strlen(item->info) + 1, fd);
    fclose(fd);
    freeItem(item);
    return offset;
}


Item *readItem(int offset, int len){
    FILE *fd;
    int key2len;
    Item *item = (Item *) malloc(sizeof (Item));

    fd = fopen(values, "rb");
    fseek(fd, offset, SEEK_SET);
    fread(&(item->key1), sizeof (int), 1, fd);
    fread(&key2len, sizeof (int), 1, fd);
    item->key2 = (char *) malloc(key2len);
    fread(item->key2, sizeof (char ), key2len, fd);
    fread(&item->release, sizeof (int), 1, fd);
    item->info = (char *) malloc(len);
    fread(item->info, sizeof (char), len, fd);
    fclose(fd);
    return item;
}
