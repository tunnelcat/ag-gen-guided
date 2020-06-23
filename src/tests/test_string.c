#include "util_common.h"
#include <stdlib.h>
#include <string.h>

int main() {
    char *text = "Hello, world!";
    int textLen = strlen(text);
    DEBUG_PRINT("text length: %d\n", textLen);

    // Must be freed!
    char *textCopy = dynstr(text);

    printf("%s\n", text);
    printf("%s\n", textCopy);

    free(textCopy);
}
