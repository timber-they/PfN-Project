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
    res.Positives = 0;
    res.Negatives = 0;
    for (int i = 0; i < size; i++)
    {
        if (getWithProbability(probability))
        {
            res.Positives++;
        }
        else
        {
            res.Negatives++;
        }        
    }

    return res;
}

