//
// Created by Kyle Cook on 3/7/18.
//

#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include <stdlib.h>
#include <string.h>

static void null_test_success(void **state) {
    (void) state;
}

extern char* dynstr(char* str);
static void dynstr_test(void **state) {
    (void) state;

    char *mystr = dynstr("Hello!");
    char *mystr2 = malloc(7);
    strcpy(mystr2, "Hello!");
    assert_memory_equal(mystr, mystr2, 7);
}

int main() {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(null_test_success),
        cmocka_unit_test(dynstr_test),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
