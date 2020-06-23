#include "util_hash.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    struct HashTable *table = hashtable_new();

    hashtable_set(table, "hello", "12345");
    char *value = hashtable_get(table, "hello");
    printf("%d\n", atoi(value));

    hashtable_set(table, "goodbye", "Thing");
    char *str = hashtable_get(table, "goodbye");
    printf("%s\n", str);

    hashtable_free(table);

    return 0;
}
