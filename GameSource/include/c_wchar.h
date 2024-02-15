#ifndef _C_WCHAR_
#define _C_WCHAR_
#include <include/c_stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
    //File

    int fwide(FILE* stream, int mode);

    //Prints
    int swprintf(wchar_t*, size_t, const wchar_t*, ...);
    int vswprintf(wchar_t*, size_t, const wchar_t*, va_list);

    //Strings
    int wcscmp(const wchar_t* wcs1, const wchar_t* wcs2);
    wchar_t* wcscpy(wchar_t*, const wchar_t*);
    size_t wcslen(const wchar_t* wcs);
    const wchar_t* wcschr(const wchar_t* ws, wchar_t wc); //80017a48
    wchar_t* wcsncpy(wchar_t*, const wchar_t*, size_t); //800179d0
    wchar_t* wmemcpy(wchar_t* dest, const wchar_t* src, size_t count);


    int mbtowc(wchar_t* pwc, const char* pmb, size_t max);
    size_t mbstowcs(wchar_t* dest, const char* src, size_t max);
    int wcstombs(char* dest, const wchar_t* src, size_t);

#ifdef __cplusplus
}
#endif
#endif