#ifndef LAZY_SAMPLING
#define LAZY_SAMPLING

// A binary lazy data source
typedef struct {
    // The positive elements
    unsigned long Positives;
    // The negative elements
    unsigned long Negatives;
} LazySource;

int takeElement(LazySource *source);

int getElement(LazySource *source);

LazySource getLazySource(int size, double probability);

#endif
