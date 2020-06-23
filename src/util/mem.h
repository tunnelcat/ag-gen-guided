#ifndef _MEM_H
#define _MEM_H

#include <stddef.h>

#define INITIALBUFSIZE 101

#ifdef __cplusplus
extern "C" {
#endif

char *dynstr(const char *str);
void *getmem(size_t size);
void *getcmem(size_t size);
int clearmem(void *data, size_t size);
char *getstr(size_t size);

void itoa(int n, char s[]);
void reverse(char s[]);

void strapp(char **str1, char *str2);

#ifdef __cplusplus
}
#endif

#endif //_MEM_H
