#ifndef LAZY_SAMPLING
#define LAZY_SAMPLING

// A binary lazy data source
typedef struct LazySource LazySource;

int takeElement(LazySource *source);

int getElement(LazySource *source);

LazySource* getLazySource(int size, double probability);

void reset(LazySource *source);

unsigned long countPositives(LazySource *source);

unsigned long countNegatives(LazySource *source);

#endif
