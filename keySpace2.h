#ifndef LAB3_KEYSPACE2_H
#define LAB3_KEYSPACE2_H

#include "item.h"
extern int M2_SIZE;


typedef struct KeySpace2 {
    char *key;
    int release;
    int offset;
    int len;
    struct KeySpace2 *next;
} KeySpace2;

int KS2lastRelease(KeySpace2 **tab, char *key);
int KS2init(KeySpace2 ***tab, int msize);
int KS2push(KeySpace2 **tab, char *key, int release, int offset, int len);
KeySpace2 **KS2search(KeySpace2 **tab, char *key);
Item *KS2searchRelease(KeySpace2 **tab, char *key, int release);
int KS2delete(KeySpace2 **tab, char *key);
int KS2deleteRelease(KeySpace2 **tab, char *key, int release);
int KS2clear(KeySpace2 **tab, char *key);
void KS2print(KeySpace2 **tab);
void KS2free(KeySpace2 **tab);
void KS2save(KeySpace2 **tab, int size);

#endif //LAB3_KEYSPACE2_H
