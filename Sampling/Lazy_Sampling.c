#include <stdio.h>

// A binary lazy data source
struct LazySource {
    // The positive elements
    unsigned long Positives;
    // The negative elements
    unsigned long Negatives;
};

int takeElement(struct LazySource *source)
{
    if (source->Positives == 0 && source->Negatives == 0) 
    {
        // No elements left
        return -1;
    }

    double probability = (double) source->Positives / 
        (double) (source->Positives + source->Negatives);
    // TODO: Randomly select an element with the probability
    short positive = probability > 0.5;
    if (positive)
        source->Positives--;
    else
        source->Negatives--;
    return positive;
}

int getElement(struct LazySource *source)
{
    if (source->Positives == 0 && source->Negatives == 0) 
    {
        // No elements left
        return -1;
    }

    double probability = (double) source->Positives / 
        (double) (source->Positives + source->Negatives);
    // TODO: Randomly select an element with the probability
    return probability > 0.5;
}

struct LazySource getLazySource(int size, double probability)
{
    struct LazySource res;
    // TODO: Initialize randomly (i.e. with a binomial distribution)
    res.Positives = (int) (probability * size);
    res.Negatives = size - res.Positives;

    return res;
}

int main(int argc, char *argv[])
{
    int size;
    double probability;
    switch (argc)
    {
       case 1:
           size = 100;
           probability = 0.5;
           break;
       case 3:
           if (sscanf(argv[1], "%d", &size) == 1 &&
                   sscanf(argv[2], "%lf", &probability) == 1)
           {
               break;
           }
           fprintf(stderr, "Couldn't parse entries %s %s\n", argv[1], argv[2]);
           return 1;
       default:
           fprintf(stderr, "Invalid entry\n");
           return 1;
    }

    struct LazySource source = getLazySource(size, probability);
    for (int i = 0; i < size; i++)
    {
        printf("Pick %d got %d\n", i, takeElement(&source));
    }

    return 0;
}
