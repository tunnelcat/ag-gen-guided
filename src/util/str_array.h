//
// Created by Kyle Cook on 8/2/17.
//

#ifndef AG_GEN_STR_UTIL_H
#define AG_GEN_STR_UTIL_H

#include "util/hash.h"
#include <string.h>

#define INIT_SIZE 20

#ifdef __cplusplus
extern "C" {
#endif

typedef struct str_array {
    char **arr;
    size_t size;
    size_t used;
} str_array;

str_array *new_str_array(void);
void init_str_array(str_array *arr);
void add_str(str_array *arr, char *str);
char *get_str_idx(str_array *arr, size_t idx);
void free_str_array(str_array *arr);
void print_str_array(str_array *arr);

hashtable *str_array_to_hashtable(str_array *arr);

#ifdef __cplusplus
}
#endif

#endif // AG_GEN_STR_UTIL_H
