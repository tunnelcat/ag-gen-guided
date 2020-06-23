#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "util/hash.h"
#include "util/mem.h"

static double get_loadfactor(hashtable *t);
static bool should_rehash(hashtable *t);
static void rehash(hashtable *t);

/* http://www.cse.yorku.ca/~oz/hash.html */
uint64_t hash(char *str) {
    uint64_t hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

hashtable *new_hashtable(unsigned int size) {
    hashtable *t = (hashtable *)getmem(sizeof(hashtable));
    init_hashtable(t, size);
    return t;
}

void init_hashtable(hashtable *t, unsigned int size) {
    t->arr = (hashnode **)getmem(size * sizeof(hashnode *));
    t->size = size;
    t->used = 0;
    clearmem(t->arr, size * sizeof(hashnode *));
}

void add_hashtable(hashtable *t, char *key, unsigned int val) {
    if (should_rehash(t))
        rehash(t);
    uint64_t idx = hash(key) % t->size;
    //    printf("hashing: %s with size %d\n", key, t->size);

    hashnode *newnode = (hashnode *)getmem(sizeof(hashnode));
    newnode->key = key;
    newnode->val = val;
    newnode->next = NULL;

    hashnode *prevnode = t->arr[idx];
    if (prevnode != NULL) {
        while (prevnode->next != NULL) {
            if (strcmp(prevnode->key, key) == 0) {
                free(newnode);
                return;
            }
            prevnode = prevnode->next;
        }
        prevnode->next = newnode;
    } else {
        t->arr[idx] = newnode;
    }

    t->used++;
}

int get_hashtable(hashtable *t, char *str) {
    uint64_t idx = hash(str) % t->size;
    hashnode *currnode = t->arr[idx];
    // printf("Looking for '%s' with size %d\n", str, t->size);
    while (currnode != NULL) {
        // printf("Have '%s'\n", currnode->key);
        if (strcmp(currnode->key, str) == 0) {
            // printf("Found\n\n");
            return currnode->val;
        }
        // printf("Next linked node\n");
        currnode = currnode->next;
    }
    // printf("Not Found\n\n");
    return -1;
}

void free_hashtable(hashtable *t) {
    for (int i = 0; i < t->size; i++) {
        hashnode *node = t->arr[i];
        if (node != NULL) {
            while (node->next != NULL) {
                hashnode *tmp = node;
                free(node);
                node = tmp->next;
            }
            free(node);
        }
    }
}

// Load factor should be below 75%
static double get_loadfactor(hashtable *t) { return ((double)t->used / t->size); }

static bool should_rehash(hashtable *t) {
    if (get_loadfactor(t) < LOAD_FACTOR) {
        return false;
    }
    return true;
}

static void rehash(hashtable *t) {
    printf("REHASHING\n");
    hashtable *newhashtable = new_hashtable((t->size * 2) + 1);
    for (int i = 0; i < t->size; i++) {
        hashnode *data = t->arr[i];
        if (data != NULL) {
            while (data->next != NULL) {
                add_hashtable(newhashtable, data->key, data->val);
                data = data->next;
            }
            add_hashtable(newhashtable, data->key, data->val);
        }
    }
    t->arr = newhashtable->arr;
    t->size = (t->size * 2) + 1;
}
