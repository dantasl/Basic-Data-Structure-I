set title 'Empirical Analysis - Random Inputs'
set key above
set xlabel 'Sample Size'
set ylabel 'Average Time (milliseconds)'
p 'file' title 'file' with lines smooth csplines
