To build:
$ make

To execute:
$ ./lzw.out <-c || -d> <input_file>

Testing:
Run selftest.sh script to run a test the functionalites, memory leaks, coding
standards, cppcheck, clang build.

To use this script install the following packages, using the below command.

$ sudo apt -y install clang cppcheck valgrind

It is assumed that checkpatch.pl is present in the path mentioned below:

/usr/src/<kernel_version>/scripts/checkpatch.pl
