#ifndef _C_WCHAR_
#define _C_WCHAR_
#include <include/c_stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
    //File

    int fwide(FILE *stream, int mode);

    //Prints
    int swprintf(wchar_t *, size_t, const wchar_t *, ...);
    int vswprintf(wchar_t *, size_t, const wchar_t *, va_list);

    //Strings
    int wcscmp(const wchar_t *wcs1, const wchar_t *wcs2);
    wchar_t *wcscpy(wchar_t *, const wchar_t *);
    size_t wcslen(const wchar_t *wcs);
    int wcsncmp(const wchar_t *wcs1, const wchar_t *wcs2, size_t num);
    wchar_t *wcsncpy(wchar_t *, const wchar_t *, size_t);

#ifdef __cplusplus
}
#endif
#endif