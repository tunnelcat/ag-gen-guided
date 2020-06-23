/** \file list_test.c
 * \author Kyle Cook <kylecook80@gmail.com>
 * \date June 2016
 * \copyright Copyright (C) The University of Tulsa - All Rights Reserved.
 * Unauthorized copying or distribution of this file is strictly prohibited.
 */

#include <stdio.h>
#include <stdlib.h>

#include "test.h"
#include "util_list.h"

int create_free_list() {
    // creating and freeing list
    struct List *list = list_new();
    list_free(list);
    return PASS;
}

int push_pop_list() {
    struct List *list = list_new();
    FAILIF(list == NULL);

    list_push(list, (void *)1);
    list_push(list, (void *)2);
    list_push(list, (void *)3);

    int val;
    val = (int)list_pop(list);
    FAILIFNEQ(INT, val, 3);

    val = (int)list_pop(list);
    FAILIFNEQ(INT, val, 2);

    val = (int)list_pop(list);
    FAILIFNEQ(INT, val, 1);

    list_free(list);
    // free(list);
    return PASS;
}

int main() {
    TEST(create_free_list);
    TEST(push_pop_list);
}
