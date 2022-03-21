#include "dialog.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "conio.h"

const char *msgs[ ] = {"0. Quit", "1. Add","2. Find", "3. Delete", "4. Show", "5. Clear"};
const char *findMsgs[ ] = {"1. Key 1","2. Key 2", "3. Range of key1"};

void (*fptr[ ])(Table *) = {NULL, DAdd, DFind, DDelete, DShow, DClear};

int dialog()
{
    char *errmsg = "";
    int rc;
    int i;
    do{
        puts(errmsg);
        errmsg = "You are wrong. Repeat, please!";
        for(i = 0; i < 6; ++i)
            puts(msgs[i]);
        puts("Make your choice ");
        if (!getInt(&rc))
            continue;
    } while(rc < 0 || rc >= 6);
    return rc;
}

int getInt(int *k){
    int out = 1;
    if (!scanf("%I64d", k)){
        out = 0;
    }
    fflush(stdin);
    return out;
}

char *getStr(){
    char *s, *buf = (char *)calloc(sizeof (char), 11);
    scanf("%10s", buf);
    fflush(stdin);
    s = (char *)calloc(sizeof (char), strlen(buf) + 1);
    strcpy(s, buf);
    free(buf);
    return s;
}

void DAdd(Table *table){
    char *errmsg = "";
    Item *item = (Item *) malloc(sizeof (Item));
    do{
        puts(errmsg);
        errmsg = "You are wrong. Repeat, please!";
        puts("Enter key1 ");
    } while(!getInt(&(item->key1)));
    puts("Enter key2 ");
    item->key2 = getStr();
    puts("Enter info ");
    item->info = getStr();
    if (!push(table, item))
        printf("Duplicate key1");
}

void DFind(Table *table){
    int key1, i, type, a, b;
    char *key2, *errmsg;
    Item *item;
    KeySpace1 **ks1;
    KeySpace2 **ks2;
    errmsg = "";
    do{
        puts(errmsg);
        errmsg = "You are wrong. Repeat, please!";
        for(i = 0; i < 3; ++i)
            puts(findMsgs[i]);
        puts("Make your choice ");
        if (!getInt(&type))
            continue;
    } while(type < 1 || type > 3);
    if (type == 1){
        errmsg = "";
        do{
            puts(errmsg);
            errmsg = "You are wrong. Repeat, please!";
            puts("Enter key ");
        } while(!getInt(&key1));
        if (!(item = KS1search(table->ks1, key1))){
            printf("Can't find item");
            return;
        }
        printItem(item);
    }
    if (type == 2){
        puts("Enter key ");
        key2 = getStr();
        if (!(ks2 = KS2search(table->ks2, key2))){
            printf("Can't find items");
            return;
        }
        free(key2);
        KS2print(ks2);
    }
    if (type == 3){
        errmsg = "";
        do{
            puts(errmsg);
            errmsg = "You are wrong. Repeat, please!";
            puts("Enter left board ");
        } while(!getInt(&a));
        errmsg = "";
        do{
            puts(errmsg);
            errmsg = "You are wrong. Repeat, please!";
            puts("Enter right board ");
        } while(!getInt(&b));
        if (!(ks1 = KS1searchRange(table->ks1, a, b))){
            printf("Can't find items");
            return;
        }
        KS1print(ks1);
    }
}

void DDelete(Table *table){
    int key1, type;
    char *errmsg = "", *key2;
    do{
        puts(errmsg);
        errmsg = "You are wrong. Repeat, please!";
        puts("Enter type of key ");
        if (!getInt(&type))
            continue;
    } while(type < 1 || type > 2);
    if (type == 1){
        errmsg = "";
        do{
            puts(errmsg);
            errmsg = "You are wrong. Repeat, please!";
            puts("Enter key ");
        } while(!getInt(&key1));
        if (!(deleteByKey1(table, key1))){
            printf("No such key");
            return;
        }
    }
    if (type == 2){
        puts("Enter key ");
        key2 = getStr();
        if (!(deleteByKey2(table, key2))) {
            printf("No such key");
        }
        free(key2);
    }
}
void DShow(Table *table){
    KS1print(table->ks1);
}

void DClear(Table *table){
    char *key2;
    puts("Enter key 2");
    key2 = getStr();
    if (!(clear(table, key2))) {
        printf("Table needn't clear");
    }
    free(key2);
}


