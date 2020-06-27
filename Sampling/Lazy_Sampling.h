#ifndef LAZY_SAMPLING
#define LAZY_SAMPLING

// A binary lazy data source
typedef struct {
    // The positive elements
    unsigned long Positives;
    // The negative elements
    unsigned long Negatives;

    // Initial values, to enable a reset functionality
    unsigned long InitialPositives;
    unsigned long InitialNegatives;
} LazySource;

int takeElement(LazySource *source);

int getElement(LazySource *source);

LazySource getLazySource(int size, double probability);

void reset(LazySource *source);

#endif
