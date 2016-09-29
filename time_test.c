#include <stdio.h>
#include "computepi.h"
#include <math.h>

int main(int argc, char const *argv[])
{
    __attribute__((unused)) int N = 400000000;
    double pi = 0.0;

#if defined(BASELINE)
    pi = compute_pi_baseline(N);
#endif

#if defined(BASELINE_PLUS)
    pi = compute_pi_baseline(N);
#endif

#if defined(OPENMP_2)
    pi = compute_pi_openmp(N, 2);
#endif
#if defined(OPENMP_2_PLUS)
    pi = compute_pi_openmp(N, 2);
#endif

#if defined(OPENMP_4)
    pi = compute_pi_openmp(N, 4);
#endif
#if defined(OPENMP_4_PLUS)
    pi = compute_pi_openmp(N, 4);
#endif

#if defined(AVX)
    pi = compute_pi_avx(N);
#endif

#if defined(AVXUNROLL)
    pi = compute_pi_avx_unroll(N);
#endif
    double diff = pi - M_PI > 0 ? pi - M_PI : M_PI - pi;
    double error = diff / M_PI;
    printf("N = %d , pi = %lf , error = %lf\n", N, pi, error);

    return 0;
}
