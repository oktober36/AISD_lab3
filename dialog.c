#include "dialog.h"
#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "conio.h"

const char *dialogMsgs[] = {"0. Quit", "1. Add", "2. Find", "3. Delete", "4. Show"};
const char *findMsgs[] = {"0. Back", "1. Key 1", "2. Key 2",
                          "3. Pair of keys", "4. Key 2 and release", "5. Range of key1"};
const char *deleteMsgs[] = {"0. Back", "1. Key 1", "2. Key 2",
                            "3. Pair of keys", "4. Key2 and release", "5. Delete old releases"};

void (*dialogFptr[])(Table *) = {NULL, DAdd, DFind, DDelete, DShow};

int getInt() {
    int out, flag;
    char *error;
    error = "";
    do {
        flag = 1;
        puts(error);
        error = "Please enter number";
        if (!scanf("%d%*[ ]", &out))
            flag = 0;
        if (getchar() != '\n')
            flag = 0;
        fflush(stdin);
    } while (!flag);
    return out;
}

char *getStr() {
    char *s, *buf = (char *) calloc(sizeof(char), 256);
    int flag;
    char *error;
    error = "";
    do {
        flag = 1;
        puts(error);
        error = "Please enter string without spaces";
        if (!scanf("%s%*[ ]", buf))
            flag = 0;
        if (getchar() != '\n')
            flag = 0;
        fflush(stdin);
    } while (!flag);
    s = (char *) calloc(sizeof(char), strlen(buf) + 1);
    strcpy(s, buf);
    free(buf);
    buf = NULL;
    return s;
}

int getOption(int optionNum, char *msg, char *errMsg, char **options) {
    int rc, i;
    char *error = "";
    do {
        puts(error);
        error = errMsg;
        for (i = 0; i < optionNum; ++i)
            puts(options[i]);
        puts(msg);
        rc = getInt();
    } while (rc < 0 || rc >= optionNum);
    return rc;
}

int dialog(Table *table) {
    int rc;
    while ((rc = getOption(5, "Select the command",
                           "Wrong command number, repeat", (char **) dialogMsgs)))
        dialogFptr[rc](table);
}

void DAdd(Table *table) {
    char *key2, *info;
    int key1;
    puts("Enter key1");
    key1 = getInt();
    puts("Enter key2");
    key2 = getStr();
    puts("Enter info");
    info = getStr();
    if (!push(table, key1, key2, info))
        printf("Duplicate key1");
}

void DFind(Table *table) {
    int key1, a, b, option;
    char *key2;
    option = getOption(6, "Select the search option",
                       "Wrong option number, repeat", (char **) findMsgs);
    if (!option)
        return;
    if (option == 1) {
        puts("Enter the key1");
        key1 = getInt();
        if (!findByKey1(table, key1))
            puts("Not found");
    } else if (option == 2) {
        puts("Enter the key2");
        key2 = getStr();
        if (!findByKey2(table, key2))
            puts("Not found");
        free(key2);
    } else if (option == 3) {
        puts("Enter the key1");
        key1 = getInt();
        puts("Enter the key2");
        key2 = getStr();
        if (!findByPair(table, key1, key2))
            puts("Not found");
        free(key2);
    } else if (option == 4) {
        puts("Enter the key2");
        key2 = getStr();
        puts("Enter the release");
        a = getInt();
        if (!findByRelease(table, key2, a))
            puts("Not found");
        free(key2);
    } else if (option == 5) {
        puts("Enter the left board");
        a = getInt();
        puts("Enter the right board");
        b = getInt();
        if (!findByRange(table, a, b)) {
            puts("Not found");
        }
    }
}

void DDelete(Table *table) {
    int key1, option, release;
    char *key2;
    option = getOption(6, "Select the delete option",
                       "Wrong option number, repeat", (char **) deleteMsgs);
    if (!option)
        return;
    if (option == 1) {
        puts("Enter the key1");
        key1 = getInt();
        if (!deleteByKey1(table, key1))
            puts("Not found");
    } else if (option == 2) {
        puts("Enter the key2");
        key2 = getStr();
        if (!deleteByKey2(table, key2))
            puts("Not found");
        free(key2);
    } else if (option == 3) {
        puts("Enter the key1");
        key1 = getInt();
        puts("Enter the key2");
        key2 = getStr();
        if (!deleteByPair(table, key1, key2))
            puts("Not found");
        free(key2);
    } else if (option == 4) {
        puts("Enter the key2");
        key2 = getStr();
        puts("Enter the release");
        release = getInt();
        if (!deleteByRelease(table, key2, release))
            puts("Not found");
        free(key2);
    } else if (option == 5) {
        puts("Enter the key2");
        key2 = getStr();
        if (!clear(table, key2))
            puts("Not found");
        free(key2);
    }
}

void DShow(Table *table) {
    if (table->csize == 0){
        puts("Table is clear");
        return;
    }
    KS1print(table->ks1);
}


