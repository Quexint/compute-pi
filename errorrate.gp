reset
set ylabel 'time(sec)'
set style histogram cluster gap 1
set style fill solid
set title 'perfomance comparison'
set boxwidth 0.8
set term png enhanced font 'Verdana,10'
set output 'errorrate.png'

plot for [COL=2:9] 'result_error_rate.csv' using COL:xticlabels(1) title columnheader
