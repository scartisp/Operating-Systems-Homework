# Operating Systems HW1 sloppy counter

this is a sloppy counter simulation created in C++ for my operating systems class. 
it is meant to simualate both cpu and io bound work and uses the pthread API for threading.

# instructions:
run using the make file, which compiles the code using g++ 11.4.0. The executable is titled
sloppySim. to run the executable, write ./sloppySim followed by any arguments you want.
The arguments are as follows: 
number of threads, sloppiness (aka, local bucket size), work time,
work iterations, cpu bound (true or false), and logging (true or false).
to measure execution duration on linux, use the time command

example execution command:
time ./sloppySim 4 10 10 1000 true true

to remove the executable, run make clean on your terminal

# Written by: Simion Cartis