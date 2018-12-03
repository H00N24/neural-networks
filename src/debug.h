#ifndef DEBUG_H_
#define DEBUG_H_

#include <assert.h>
#define ASSERT(EXP, MESSAGE)                    \
  do {                                          \
    if (!(EXP)) {                               \
      fprintf(stderr, "Error: " #MESSAGE "\n"); \
      assert(EXP);                              \
    }                                           \
  } while (0)

#ifdef DEBUG
#include <stdio.h>
#include <time.h>
double __start_time, __time_counter;
#define DPRINT(...)      \
  do {                   \
    printf(__VA_ARGS__); \
    fflush(stdout);      \
  } while (0)
#define DPRINT_MATRIX(...) print_matrix(__VA_ARGS__)

#define DTIME_INIT          \
  do {                      \
    __start_time = clock(); \
  } while (0)

#define DTIME_START_COUNTER   \
  do {                        \
    __time_counter = clock(); \
  } while (0)
#define DTIME_DURATION (double)(clock() - __time_counter) / CLOCKS_PER_SEC

#define DTIME_END (double)(clock() - __start_time) / CLOCKS_PER_SEC
#else
#define DPRINT(...)
#define DPRINT_MATRIX(...)
#define DTIME_INIT
#define DTIME_START_COUNTER
#define DTIME_DURATION
#define DTIME_END
#endif

#endif