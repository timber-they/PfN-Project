#include "Lazy_Sampling.h"
#include "correction.h"
#include "Random.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    double p = 0;
    unsigned int populationNumber = 0;
    unsigned int sampleNumber = 0; // number of samples to create
    unsigned int sampleSize = 0;
    int seed = 96661;
    LazySource source;
    unsigned int positives = 0;
    double correctedPercentage;
    unsigned int correctedPositives;
    double sensitivity = 0.909;
    double specificity = 0.991;

    
    const char *resultFileName = "sampleResult.tsv";
    FILE *resultFile = NULL;

    if (argc < 5 || sscanf(argv[1], "%lf", &p) != 1
                 || sscanf(argv[2], "%ud", &populationNumber) != 1
                 || sscanf(argv[3], "%ud", &sampleNumber) != 1
                 || sscanf(argv[4], "%ud", &sampleSize) != 1
                 || (argc > 5 && sscanf(argv[5], "%d", &seed) != 1)
                 || (argc > 6 && sscanf(argv[6], "%lf", &sensitivity) != 1)
                 || (argc > 7 && sscanf(argv[7], "%lf", &specificity)!= 1))
    {
        fprintf(stderr, "Usage: %s <p> <N> <n> <S> [<s>] [<se>] [<sp>]\n", argv[0]);
        return 1;
    }

    /*
    offset = argc - sampleNumber;
    
    //get #sampleNumber sample-sizes from parameters
    unsigned int sampleSizes[sampleNumber];
    for (int i = 0; i < sampleNumber; i++)
    {
        sscanf(argv[i + offset], "%ud", &sampleSizes[i]);
        if (sampleSizes[i] > populationNumber)
        {
            fprintf(stderr,
                    "Samplesize can't be larger than Populationsize\n");
            return 1;
        }
    }
    */

    if (p < 0 || p > 1)
    {
        fprintf(stderr, "Probability can't be less than 0 or more than 1\n");
        return 1;
    }
    
    

    // Sampling_Init
    initRandom(seed);
    
    resultFile = fopen(resultFileName, "w");
    if(resultFile == NULL)
    {
        fprintf(stderr, "Could not open file");
        return 1;
    }
    
    //create sampling for every sample-size
    source = getLazySource(populationNumber, p);
    for(int sample = 0; sample < sampleNumber; sample++)
    {
        positives = 0;
        reset(&source);

        // Sampling_Ready -> Sampling_Progressing
        for (int i = 0; i < sampleSize; i++)
        {
            if (takeElement(&source))
            {
                if (getWithProbability(sensitivity))
                {
                    positives++;
                }
            }
            else
            {
                if (getWithProbability(1 - specificity))
                {
                    positives++;
                }
            }
        }

        correctedPercentage = correction((double) positives /
                                          sampleSize, sensitivity, specificity);
        correctedPositives = correctedPercentage * sampleSize;

        // Sampling_Done
        printf("Sample result: %u\t%u\n", sampleSize, correctedPositives);
        fprintf(resultFile, "%u\t%u\n", sampleSize, correctedPositives);
    }
    fclose(resultFile);
    return 0;
}
