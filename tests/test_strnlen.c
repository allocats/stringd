#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

extern size_t s_strnlen(const char* s, size_t max);

double now() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC_RAW, &ts);
    return ts.tv_sec + ts.tv_nsec / 1e9;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("TEST SIZE NEEDED AS ARGUMENT\n");
        return 1;
    }

    int TEST_SIZE = atof(argv[1]);
    char* s = malloc(TEST_SIZE + 1);
    if (!s) {
        fprintf(stderr, "Allocation failed!\n");
        return 1;
    }

    memset(s, 'z', TEST_SIZE + 1);
    s[TEST_SIZE] = 0;

    double g_start = now();
    size_t g_len = strnlen(s, TEST_SIZE);
    double g_end = now();

    char* s2 = malloc(TEST_SIZE + 1);
    if (!s2) {
        fprintf(stderr, "Allocation failed!\n");
        return 1;
    }

    memset(s2, 'a', TEST_SIZE + 1);
    s2[TEST_SIZE] = 0;

    double s_start = now();
    size_t s_len = s_strnlen(s2, TEST_SIZE);
    double s_end = now();

    printf("GLIBC strnlen: %.5fms (%zu)\n", (double)(g_end - g_start) * 1000, g_len);
    printf("My strnlen: %.5fms (%zu)\n", (double)(s_end - s_start) * 1000, s_len);
    printf("Performance gain: %.3fx\n", ((double)(g_end - g_start) / (double)(s_end - s_start)));

    free(s);
    free(s2);

    return 0;
}
