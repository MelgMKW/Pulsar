#ifndef _C_STRING_
#define _C_STRING_
#include <include/c_stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif


    //Copying
    void *memcpy(void *dest, const void *src, size_t);
    void *memmove(void *, const void *, size_t);
    char *strcpy(char *dest, const char *src);
    char *strncpy(char *dest, const char *src, size_t);

    //Cat
    char *strcat(char *dest, const char *src);
    char *strncat(char *, const char *, size_t);

    //Compare
    int memcmp(const void *, const void *, size_t);
    int strcmp(const char *, const char *);
    int strncmp(const char *, const char *, size_t);

    //Search
    void *memchr(const void *, int, size_t);
    char *strchr(const char *, int);
    size_t strcspn(const char *str1, const char *str2);
    char *strstr(const char *, const char *);
    char *strrchr(const char *str, int c);
    char *strtok(char *str, const char *delimiter1, ...);

    //Misc
    void *memset(void *, int, size_t);
    size_t strlen(const char *);

    //Not Standard
    int stricmp(const char *, const char *); // not standard but nsmbw's got it anyway!

#ifdef __cplusplus
}
#endif
#endif