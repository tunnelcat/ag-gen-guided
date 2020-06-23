#ifndef _UTIL_HASH
#define _UTIL_HASH

#include <stdbool.h>
#include <stdint.h>

#define LOAD_FACTOR .75

#ifdef __cplusplus
extern "C" {
#endif

typedef struct hashnode {
    char *key;
    unsigned int val;
    struct hashnode *next;
} hashnode;

typedef struct hashtable {
    hashnode **arr;
    int size;
    int used;
} hashtable;

uint64_t hash(char *str);

hashtable *new_hashtable(unsigned int size);
void init_hashtable(hashtable *t, unsigned int size);
int get_hashtable(hashtable *t, char *key);
void add_hashtable(hashtable *t, char *key, unsigned int val);
void free_hashtable(hashtable *t);

#ifdef __cplusplus
}
#endif

#endif
