//
// Created by Kyle Cook on 8/2/17.
//

#include <stdio.h>
#include <stdlib.h>

#include "util/mem.h"
#include "util/str_array.h"

str_array *new_str_array(void) {
    str_array *arr = (str_array *)getmem(sizeof(str_array));
    init_str_array(arr);
    return arr;
}

void init_str_array(str_array *arr) {
    arr->arr = (char **)getmem(INIT_SIZE * sizeof(char *));
    arr->size = INIT_SIZE;
    arr->used = 0;
}

void add_str(str_array *arr, char *str) {
    if (arr->size == arr->used) {
        arr->arr = (char **)realloc(arr->arr, arr->size * 2 * sizeof(char *));
        arr->size *= 2;
    }
    arr->arr[arr->used++] = dynstr(str);
}

char *get_str_idx(str_array *arr, size_t idx) {
    return arr->arr[idx];
}

void free_str_array(str_array *arr) {
    for (size_t i = 0; i < arr->used; i++) {
        free(arr->arr[i]);
    }
    free(arr->arr);
}

void print_str_array(str_array *arr) {
    for (size_t i = 0; i < arr->used; i++) {
        printf("\t%s\n", arr->arr[i]);
    }
}

hashtable *str_array_to_hashtable(str_array *arr) {
    hashtable *ht = new_hashtable(7);
    for(size_t i=0; i<arr->used; i++) {
        //printf("TEST: %s - %d\n", get_str_idx(arr, i), i);
        add_hashtable(ht, get_str_idx(arr, i), i);
    }
    return ht;
}
