#ifndef BASIC_SAMPLING
#define BASIC_SAMPLING
#include <stdbool.h>

bool *getSampleArray(int size, double prob, int seed);
int getPositives(int size, double prob, int seed);

#endif
