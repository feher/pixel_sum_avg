Intro
-------
This is an implementation and test of https://en.wikipedia.org/wiki/Summed-area_table

Building
----------
Requirements:
* g++ with C++17 support (e.g. g++ 8.3.0)
* make (e.g. version 4.2.1 works fine)

Building:
$ make
The binaries are put in the ./build directory.

Running
---------
Unit tests:
$ ./test_unit.sh

Performance tests:
$ ./test_perf.sh

The performance test loops over the pixels of a 4096x4096 size buffer and does a query
for getPixelSum(), getPixelAverage(), getNonZeroCount() and getNonZeroAverage().
It also serves as unit/functional test (i.e. it checks the results).

Stress tests:
$ ./test_stress.sh

The stress test generates a random buffer and performs queries
to random locations with random window sizes.
It functions as a test against crashes. It must be combined with e.g. valgrind to function as
a memleak check.
