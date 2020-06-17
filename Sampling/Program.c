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
    int seed = 96661;
    LazySource source;
    unsigned int positives = 0;
    double correctedPercentage;
    unsigned int correctedPositives;
    int offset = 0;
    
    const char *resultFileName = "sampleResult.tsv";
    FILE *resultFile = NULL;

    if (argc < 4 || sscanf(argv[1], "%lf", &p) != 1
                 || sscanf(argv[2], "%ud", &populationNumber) != 1
                 || sscanf(argv[3], "%ud", &sampleNumber) != 1)
    {
        fprintf(stderr, "Usage: %s <p> <N> <n> [<s>]\n", argv[0]);
        return 1;
    }
    
    //check if seed is one of the parameters
    if(argc - sampleNumber == 5)
    {
        if(sscanf(argv[4], "%d", &seed) != 1)
        {
            fprintf(stderr, "Couldn't read seed");
            return 1;
        }
        offset = 1;
    }
    
    //get #sampleNumber sample-sizes from parameters
    unsigned int sampleSizes[sampleNumber];
    for (int i = 0; i < sampleNumber; i++)
    {
        sscanf(argv[i + 4 + offset], "%ud", &sampleSizes[i]);
        if (sampleSizes[i] > populationNumber)
        {
            fprintf(stderr, "Samplesize can't be larger than Populationsize\n");
            return 1;
        }
    }
    
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
    for(int sample = 0; sample < sampleNumber; sample++)
    {
        positives = 0;
        unsigned int size = sampleSizes[sample];
        source = getLazySource(populationNumber, p);

        // Sampling_Ready -> Sampling_Progressing
        for (int i = 0; i < sampleSizes[sample]; i++)
        {
            if (takeElement(&source))
            {
                if (getWithProbability(SENSITIVITY))
                {
                    positives++;
                }
            }
            else
            {
                if (getWithProbability(1 - SPECIFICITY))
                {
                    positives++;
                }
            }
        }

        correctedPercentage = correction((double) positives / sampleSizes[sample]);
        correctedPositives = correctedPercentage * sampleSizes[sample];

        // Sampling_Done
        printf("Sample result: %u\t%u\n", size, correctedPositives);
        fprintf(resultFile, "%u\t%u\n", size, correctedPositives);
    }
    fclose(resultFile);
    return 0;
}
