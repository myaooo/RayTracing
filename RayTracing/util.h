#ifndef UTIL_H
#define UTIL_H

#include <string>

// color predefine in 0x16 format in strings
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

#define PI 3.1415926535f
#define Epsilon 1e-6f
#define FloatPrecision 1024

#define isBetween(a, b, c) ((a >= b) && (a <= c))
#define getMin(a, b) (a > b ? b : a)
#define getMax(a, b) (a > b ? a : b)

template <class T>
inline T Min(const T& la, const T& ra){
    return la > ra ? ra : la;
}
template <class T>
inline T Max(const T & la, const T & ra){
    return la > ra ? la : ra;
}

typedef double real_t;


#endif
