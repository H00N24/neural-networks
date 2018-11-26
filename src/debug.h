#ifndef DEBUG_H_
#define DEBUG_H_

#ifdef DEBUG
#include <stdio.h>
#define DPRINT(...) printf(__VA_ARGS__)
#define DPRINT_MATRIX(...) print_matrix(__VA_ARGS__)
#else
#define DPRINT(...)
#define DPRINT_MATRIX(...)
#endif

#endif