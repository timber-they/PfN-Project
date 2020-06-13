#include <stdio.h>
#include "Lazy_Sampling.h"
#include "Random.h"

int takeElement(LazySource *source, int seed)
{
    if (source->Positives == 0 && source->Negatives == 0) 
    {
        // No elements left
        return -1;
    }

    double probability = (double) source->Positives / 
        (double) (source->Positives + source->Negatives);
    double randomNumber = getRandomNumber(seed);
    short positive = randomNumber < probability;
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
    double randomNumber = getRandomNumber(seed);
    return randomNumber < probability;
}

LazySource getLazySource(int size, double probability)
{
    LazySource res;
    res.Positives = 0;
    res.Negatives = 0;
    for (int i = 0; i < size; i++)
    {
        double randomNumber = getRandomNumber(seed);
        if (randomNumber < probability)
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

