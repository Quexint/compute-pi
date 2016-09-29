CC = gcc
CFLAGS = -O0 -std=gnu99 -Wall -fopenmp -mavx
EXECUTABLE = \
	time_test_baseline time_test_baseline_plus time_test_openmp_2 \
	time_test_openmp_2_plus time_test_openmp_4 time_test_openmp_4_plus\
	time_test_avx time_test_avxunroll \
	benchmark_clock_gettime benchmark_error_rate

default: computepi.o
	$(CC) $(CFLAGS) computepi.o time_test.c -DBASELINE_PLUS -o time_test_baseline_plus
	$(CC) $(CFLAGS) computepi.o time_test.c -DOPENMP_2_PLUS -o time_test_openmp_2_plus
	$(CC) $(CFLAGS) computepi.o time_test.c -DOPENMP_4_PLUS -o time_test_openmp_4_plus
	$(CC) $(CFLAGS) computepi.o time_test.c -DBASELINE -o time_test_baseline
	$(CC) $(CFLAGS) computepi.o time_test.c -DOPENMP_2 -o time_test_openmp_2
	$(CC) $(CFLAGS) computepi.o time_test.c -DOPENMP_4 -o time_test_openmp_4
	$(CC) $(CFLAGS) computepi.o time_test.c -DAVX -o time_test_avx
	$(CC) $(CFLAGS) computepi.o time_test.c -DAVXUNROLL -o time_test_avxunroll
	$(CC) $(CFLAGS) computepi.o benchmark_clock_gettime.c -o benchmark_clock_gettime
	$(CC) $(CFLAGS) computepi.o benchmark_error_rate.c -o benchmark_error_rate

.PHONY: clean default

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@ 

check: default
	time ./time_test_baseline
	time ./time_test_openmp_2
	time ./time_test_openmp_4
	time ./time_test_baseline_plus
	time ./time_test_openmp_2_plus
	time ./time_test_openmp_4_plus
	time ./time_test_avx
	time ./time_test_avxunroll

gencsv: default
	echo "N baseline baselineP OMP2 OMP2P OMP4 OMP4P avx avx_{unroll}" > result_clock_gettime.csv
	for i in `seq 5000 5000 200000`; do \
		printf "%d " $$i;\
		./benchmark_clock_gettime $$i; \
	done >> result_clock_gettime.csv
	echo "N baseline baselineP OMP2 OMP2P OMP4 OMP4P avx avx_{unroll}" > result_error_rate.csv
	for i in `seq 5000 5000 200000`; do \
		printf "%d " $$i;\
		./benchmark_error_rate $$i; \
	done >> result_error_rate.csv

plot: default gencsv
	gnuplot runtime.gp
	gnuplot errorrate.gp

clean:
	rm -f $(EXECUTABLE) *.o *.s result_clock_gettime.csv result_error_rate.csv
