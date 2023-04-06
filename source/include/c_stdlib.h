#ifndef __C_STDLIB_H
#define __C_STDLIB_H

#ifdef __cplusplus
extern "C" {
#endif



    typedef struct va_list_struct {
        char gpr, fpr, reserved[2], *input_arg_area, *reg_save_area;
    } va_list[1];

    typedef struct _iobuf
    {
        void *_Placeholder;
    } FILE;

    //stdlib.h
    double atof(const char *str);
    int atoi(const char *str);
    long int strtol(const char *str, char **endptr, int base);
    unsigned long int strtoul(const char *str, char **endptr, int base);


    int rand(void);
    void srand(unsigned int seed);

    int atexit(void (*func)(void));
    void exit(int status);

    void qsort(void *base, size_t nitems, size_t size, int (*compar)(const void *, const void *));



    int mbtowc(wchar_t *pwc, const char *pmb, size_t max);
    size_t mbstowcs(wchar_t *dest, const char *src, size_t max);
    int wcstombs(char *dest, const wchar_t *src, size_t);




#ifdef __cplusplus
}
#endif

#endif
