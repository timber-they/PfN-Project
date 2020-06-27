#include <stdio.h>
#include <stdlib.h>
#include "Lazy_Sampling.h"
#include "Random.h"

struct LazySource {
    // The positive elements
    unsigned long Positives;
    // The negative elements
    unsigned long Negatives;

    // Initial values, to enable a reset functionality
    unsigned long InitialPositives;
    unsigned long InitialNegatives;
};

int takeElement(LazySource *source)
{
    if (source->Positives == 0 && source->Negatives == 0) 
    {
        // No elements left
        return -1;
    }

    double probability = (double) source->Positives / 
        (double) (source->Positives + source->Negatives);
    short positive = getWithProbability(probability);
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
    return getWithProbability(probability);
}

LazySource *getLazySource(int size, double probability)
{
    LazySource *res = malloc(sizeof(*res));
    res->InitialPositives = 0;
    res->InitialNegatives = 0;
    for (int i = 0; i < size; i++)
    {
        if (getWithProbability(probability))
        {
            res->InitialPositives++;
        }
        else
        {
            res->InitialNegatives++;
        }        
    }

    reset(res);
    return res;
}

void reset(LazySource *source)
{
    source->Positives = source->InitialPositives;
    source->Negatives = source->InitialNegatives;
}

unsigned long countPositives(LazySource *source)
{
    return source->Positives;
}

unsigned long countNegatives(LazySource *source)
{
    return source->Negatives;
}

