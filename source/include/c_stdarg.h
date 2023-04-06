#ifndef _C_STDARG_
#define _C_STDARG_

#ifdef __cplusplus
extern "C" {
#endif

    extern void *__va_arg(void *, int);
#define va_start(ap, last) (__builtin_va_info(&ap))
#define va_arg(ap, type) (*((type *)__va_arg(ap, _var_arg_typeof(type))))
#define va_end(ap) ((void)0)

#ifdef __cplusplus
}
#endif
#endif