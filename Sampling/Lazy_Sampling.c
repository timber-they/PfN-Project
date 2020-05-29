#include <stdio.h>
#include "Lazy_Sampling.h"

int takeElement(LazySource *source)
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

int getElement(LazySource *source)
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

LazySource getLazySource(int size, double probability)
{
    LazySource res;
    // TODO: Initialize randomly (i.e. with a binomial distribution)
    res.Positives = (int) (probability * size);
    res.Negatives = size - res.Positives;

    return res;
}

