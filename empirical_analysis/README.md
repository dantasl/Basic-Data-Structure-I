# Empirical Analysis of Sorting Algorithms

In the present repository I'm storing the codes created to perform the empirical analaysis task and its results.

<b>Lucas Gomes Dantas</b> (<dantaslucas@ufrn.edu.br>), student in the <b>Basic Data Structure I</b> class of <b>Prof. Dr. Selan Rodrigues dos Santos</b> at <b>Federal University of Rio Grande do Norte</b>.

## Methodology

From the sorting functions, 7 were chosen: <code>Insertion Sort</code>, <code>Selection Sort</code>, <code>Bubble Sort</code>, <code>Quick Sort</code>, <code>Merge Sort</code>, <code>Shell Sort</code> and <code>Radix Sort (LSD)</code>. The goal here is to measure the average time that each of them takes to run <code>25 unsigned integer samples of different sizes</code>. To calculate a more stable average, each function executes <code>50 times the same sample</code> and them stores its value on a file.

The samples size begins at 1 and them increments 2240 until it reaches 56000. There are three sets of samples: the ones filled with random numbers between one and the sample size; the ones filled with non-decreasing numbers between 1 and the sample size and the ones filled with non-increasing numbers between the sample size and 1.

After the average time is collected, a comparative graph for each of them is generated.

## Compiling and Running

Follow the instructions below to compile and run the project:

* Go, via prompt, to the directory where you've cloned this repository;
* Type <code>make init</code> to create the project structure;
* Type <code>make</code> to compile the project.

In order to run, there are some options you may want to explore.

If you want to run only certain sorting functions instead of the whole group, you can type <code>-f {function name}</code> where the params can be:

* <code>i</code> for <code>Insertion Sort</code>;
* <code>s</code> for <code>Selection Sort</code>;
* <code>b</code> for <code>Bubble Sort</code>;
* <code>q</code> for <code>Quick Sort</code>;
* <code>m</code> for <code>Merge Sort</code>;
* <code>sh</code> for <code>Shell Sort</code>;
* <code>r</code> for <code>Radix Sort (LSD)</code>.

You can make any combinations of functions that you want, <b>e.g.</b>: <code>./bin/sort_algorithms -f i m sh r</code> will run the analysis for Insertion Sort, Merge Sort, Shell Sort and Radix Sort (LSD) only.

In addition to that, you may choose any sample size that you want. The only difference is that the code will execute only the custom size, ignoring all the others.

If you want to do so, just add <code>-ri {new sample size}</code>, where the params can be any unsigned integer that you want, <b>e.g.</b>: <code>./bin/sort_algorithms -ri 10000</code>

You can also combine the params, <b>e.g.</b>:

* <code>./bin/sort_algorithms -f i s b -ri 1200</code>

This will run Insertion Sort, Selection Sort and Bubble Sort with a sample size of 1200.

If you just want to run the code with the default configurations, type:

* <code>./bin/sort_algorithms</code>

<b>For more information, check the code and the comments or send me an email.</b>
