#ifndef _C_MATH_
#define _C_MATH_
#define PI 3.141592653589793f
#define PIx2 (PI * 2.0f)

#ifdef __INTELLISENSE__
#define __fabs(...) true
#else
#endif

inline double fabs(double x) { return __fabs(x); }
double acos(double);
double asin(double);
double atan(double);
double atan2(double, double);
double ceil(double);
double copysign(double, double);
double cos(double);
double cosh(double); // not in nsmbw
double exp(double); // not in nsmbw

double floor(double);
double fmod(double, double);
double frexp(double, int *);
double ldexp(double, int);
double log(double); // not in nsmbw?
double log10(double);
double modf(double, double *);
double pow(double, double);
double sin(double);
double sinh(double); // not in nsmbw
double sqrt(double);
double tan(double);
double tanh(double); // not in nsmbw

extern double NAN;

#endif