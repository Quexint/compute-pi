reset
set ylabel 'time(sec)'
set style histogram cluster gap 1
set style fill solid
set title 'perfomance comparison'
set boxwidth 0.8
set term png enhanced font 'Verdana,10'
set output 'runtime.png'
set xtics 0,50000,200000
set xtics rotate by -45

plot for [COL=2:9] 'result_clock_gettime.csv' using COL:xticlabels(1) title columnheader
