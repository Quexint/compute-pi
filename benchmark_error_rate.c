#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "computepi.h"
#include <math.h>

#define CLOCK_ID CLOCK_MONOTONIC_RAW
#define ONE_SEC 1000000000.0

int main(int argc, char const *argv[])
{

    if (argc < 2) return -1;

    int N = atoi(argv[1]);
    int i, loop = 5;
    double pi, diff, error;

    // Baseline
    for(i = 0; i < loop; i++) {
        pi = compute_pi_baseline(N);
    }
    diff = pi - M_PI > 0 ? pi - M_PI : M_PI - pi;
    error = diff / M_PI;
    printf("%lf ", error);

    // Baseline Plus
    for(i = 0; i < loop; i++) {
        pi = compute_pi_baseline_plus(N);
    }
    diff = pi - M_PI > 0 ? pi - M_PI : M_PI - pi;
    error = diff / M_PI;
    printf("%lf ", error);

    // OpenMP with 2 threads
    for(i = 0; i < loop; i++) {
        pi = compute_pi_openmp(N, 2);
    }
    diff = pi - M_PI > 0 ? pi - M_PI : M_PI - pi;
    error = diff / M_PI;
    printf("%lf ", error);

    // OpenMP Plus with 2 threads
    for(i = 0; i < loop; i++) {
        pi = compute_pi_openmp_plus(N, 2);
    }
    diff = pi - M_PI > 0 ? pi - M_PI : M_PI - pi;
    error = diff / M_PI;
    printf("%lf ", error);

    // OpenMP with 4 threads
    for(i = 0; i < loop; i++) {
        pi = compute_pi_openmp(N, 4);
    }
    diff = pi - M_PI > 0 ? pi - M_PI : M_PI - pi;
    error = diff / M_PI;
    printf("%lf ", error);

    // OpenMP Plus with 4 threads
    for(i = 0; i < loop; i++) {
        pi = compute_pi_openmp_plus(N, 4);
    }
    diff = pi - M_PI > 0 ? pi - M_PI : M_PI - pi;
    error = diff / M_PI;
    printf("%lf ", error);

    // AVX SIMD
    for(i = 0; i < loop; i++) {
        pi = compute_pi_avx(N);
    }
    diff = pi - M_PI > 0 ? pi - M_PI : M_PI - pi;
    error = diff / M_PI;
    printf("%lf ", error);


    // AVX SIMD + Loop unrolling
    for(i = 0; i < loop; i++) {
        pi = compute_pi_avx_unroll(N);
    }
    diff = pi - M_PI > 0 ? pi - M_PI : M_PI - pi;
    error = diff / M_PI;
    printf("%lf\n", error);

    return 0;
}
