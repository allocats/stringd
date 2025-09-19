#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <time.h>

static inline double now() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

static inline void print_result(const char* label, double start, double end) {
    printf("%s: %.5fms\n", label, (double)(end - start) * 1000);
}


#endif // !TEST_H
