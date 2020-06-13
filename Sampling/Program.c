#include "Lazy_Sampling.h"
#include "correction.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    double p = 0;
    unsigned int populationNumber = 0, sampleNumber = 0;
    int s = 96661;
    LazySource source;
    unsigned int positives;
    double observedPositives;
    double correctedPercentage;
    unsigned int correctedPositives;

    if (argc < 4 || argc > 5
                 || sscanf(argv[1], "%lf", &p) != 1
                 || sscanf(argv[2], "%ud", &populationNumber) != 1
                 || sscanf(argv[3], "%ud", &sampleNumber) != 1
                 || (argc == 5 && sscanf(argv[4], "%d", &s) != 1))
    {
        fprintf(stderr, "Usage: %s <p> <N> <n> [<s>]", argv[0]);
        return 1;
    }    

    source = getLazySource(populationNumber, p);
    for (int i = 0; i < sampleNumber; i++)
    {
        if (takeElement(&source))
        {
            positives++;
        }
    }

    observedPositives = (positives * SENSITIVITY);
    correctedPercentage = correction(observedPositives / sampleNumber);
    correctedPositives = correctedPercentage * sampleNumber;

    printf("Sample result: %ud", correctedPositives);

    return 0;
}
