# Dev notes on acca

*   With OpenMP enabled, Valgrind will turn up memory "still reachable" at exit.
    Good description of the situation by Auraham Camacho: [(Pseudo-)memory leaks
    when using OpenMP]
    (https://medium.com/@auraham/pseudo-memory-leaks-when-using-openmp-11a383cc4cf9).
*   TODO: Fix the version string handling by converting to bump2version. Currently 
    it's set in configure.ac.


