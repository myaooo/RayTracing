//
//  util.h
//  RayTracing
//
//  Created by Ming Yao on 15/10/26.
//
#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <float.h>
#include <time.h>
#include <cmath>
// color predefine in 0x16 format in strings
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"

#define PI 3.1415926f
#define Epsilon 1e-6f
#define Inf DBL_MAX
#define InfDistance 1e10
#define FloatPrecision 1024
#define COLORRANGE 255.0

#define isBetween(a, b, c) ((a >= b) && (a <= c))
#define getMin(a, b) (a > b ? b : a)
#define getMax(a, b) (a > b ? a : b)
#define getSqr(a) ((a) * (a))
#define ABS(a) ((a) > 0 ? (a) : -(a))
#define isEqual(a, b) (ABS(a-b) < Epsilon)

typedef double real_t;

struct Clock {
    clock_t start;
public:
    Clock() : start(clock()){}
    void reset() {
        start = clock();
    }
    real_t getTime() {
        real_t timeLapse = (double)(clock() - start);
        return timeLapse / CLOCKS_PER_SEC;
    }
};


#endif
