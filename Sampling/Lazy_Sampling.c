#include <stdio.h>
#include "Lazy_Sampling.h"
#include "Random.h"

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

LazySource getLazySource(int size, double probability)
{
    LazySource res;
    res.InitialPositives = 0;
    res.InitialNegatives = 0;
    for (int i = 0; i < size; i++)
    {
        if (getWithProbability(probability))
        {
            res.InitialPositives++;
        }
        else
        {
            res.InitialNegatives++;
        }        
    }

    reset(&res);
    return res;
}

void reset(LazySource *source)
{
    source->Positives = source->InitialPositives;
    source->Negatives = source->InitialNegatives;
}

