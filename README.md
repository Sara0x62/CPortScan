# CPortScan
Lightweight, basic portscanner in C as a practice project, also supports threads.
Simply scans the top 1000 TCP ports, distributing them across the threads

Built on Linux, compiled with default `gcc main.c -o pscan`

Usage is `./pscan TARGET_URL THREADS`
Threads are optional, default is 20.

TODO; make it so it evenly distributes the TOP 1000 ports among the threads if a different thread count is set, havent tested that properly yet
