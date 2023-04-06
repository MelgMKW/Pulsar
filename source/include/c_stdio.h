#ifndef _C_STDIO_
#define _C_STDIO_
#include <include/c_stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif


    int fclose(FILE *stream);
    int fflush(FILE *stream);
    size_t fwrite(const void *ptr, size_t size, size_t count, FILE *stream);
    size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);
    int fseek(FILE *stream, long int offset, int whence);
    long int ftell(FILE *stream);
    size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
    void rewind(FILE *stream);


    int printf(const char *format, ...);
    int sprintf(char *, const char *, ...);
    int sscanf(const char *str, const char *format, ...);
    int snprintf(char *, size_t, const char *, ...);
    int vprintf(const char *format, va_list arg);
    int vsprintf(char *, const char *, va_list);
    int vsnprintf(char *, size_t, const char *, va_list);

#ifdef __cplusplus
}
#endif
#endif