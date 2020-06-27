#include "Lazy_Sampling.h"
#include "correction.h"
#include "Random.h"
#include <stdlib.h>
#include <stdio.h>

// TODO: Read just in time
unsigned int *getSampleSizes(unsigned int sampleNumber, unsigned int sampleSize,
        FILE* resultFile, unsigned int maxSampleSize)
{    
    unsigned int *sampleSizes = calloc(sampleNumber, sizeof(*sampleSizes));
    if (sampleSize == -1)
    {
        unsigned int line = 0;
        printf("Reading sample sizes from file\n");
        if(resultFile == NULL)
        {
            fprintf(stderr, 
                    "Couldn't open file for and no sample size was passed\n");
            return NULL;
        }
        for (;fscanf(resultFile, "%u\n", &sampleSizes[line]) != EOF; line++)
        {
            if (sampleSizes[line] == 0 || sampleSizes[line] > maxSampleSize)
            {
                fprintf(stderr, 
                        "Invalid sample size: %u; maximum sample size is: %u\n",
                        sampleSizes[line], maxSampleSize);
                return NULL;
            }
        }
        
        if (line != sampleNumber)
        {
            fprintf(stderr, "Received %u instead of %u sample sizes\n", 
                    line, sampleNumber);
            fclose(resultFile);
            return NULL;
        } else
        {
            printf("Succesfully read %u sample sizes\n", sampleNumber);
        }
    }
    else
    {
        printf("Using %u fixed sample sizes\n", sampleNumber);
        // Write fixed sample sizes into array
        for (unsigned int i = 0; i < sampleNumber; i++)
        {
            sampleSizes[i] = sampleSize;
        }
    }

    return sampleSizes;
}

int simulateTest(LazySource *source, double sensitivity, double specificity,
        int positives)
{
    if (takeElement(source))
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

    return positives;
}

int main(int argc, char *argv[])
{
    double p = 0;
    unsigned int populationNumber = 0;
    unsigned int sampleNumber = 0; // number of samples to create
    unsigned int sampleSize = -1;
    int seed = 96661;
    LazySource *source;
    unsigned int positives = 0;
    double correctedPercentage;
    unsigned int correctedPositives;
    double sensitivity = 0.909;
    double specificity = 0.991;
    unsigned int *sampleSizes;
    
        
    const char *resultFileName = "sampleResult.tsv";
    FILE *resultFile = NULL;

    if (argc < 4 || sscanf(argv[1], "%lf", &p) != 1
                 || sscanf(argv[2], "%ud", &populationNumber) != 1
                 || sscanf(argv[3], "%ud", &sampleNumber) != 1
                 || (argc > 4 && sscanf(argv[4], "%ud", &sampleSize) != 1)
                 || (argc > 5 && sscanf(argv[5], "%d", &seed) != 1)
                 || (argc > 6 && sscanf(argv[6], "%lf", &sensitivity) != 1)
                 || (argc > 7 && sscanf(argv[7], "%lf", &specificity)!= 1))
    {
        fprintf(stderr, "Usage: %s <p> <N> <n> [<S>] [<s>] [<se>] [<sp>]\n", argv[0]);
        return 1;
    }

    resultFile = fopen(resultFileName, "r+");
    sampleSizes = getSampleSizes(sampleNumber, sampleSize, resultFile,
            populationNumber);
    if (sampleSizes == NULL)
    {
        return 1;
    }

    if (p < 0 || p > 1)
    {
        fprintf(stderr, "Probability can't be less than 0 or more than 1\n");
        return 1;
    }   
    

    // Sampling_Init
    initRandom(seed);

    if (resultFile != NULL)
    {
        resultFile = freopen(resultFileName, "w", resultFile);
    } else
    {
        resultFile = fopen(resultFileName, "w");
    }
    if (resultFile == NULL)
    {
        fprintf(stderr, "Could not open file");
        return 1;
    }
    
    //create sampling for every sample-size
    source = getLazySource(populationNumber, p);
    printf("Got lazy source\n");
    for(int sample = 0; sample < sampleNumber; sample++)
    {
        sampleSize = sampleSizes[sample];
        positives = 0;
        reset(source);

        // Sampling_Ready -> Sampling_Progressing
        for (int i = 0; i < sampleSize; i++)
        {
            positives = simulateTest(source, sensitivity, specificity,
                    positives);
        }

        correctedPercentage = correction((double) positives /
                                          sampleSize, sensitivity, specificity);
        correctedPositives = correctedPercentage * sampleSize;

        // Sampling_Done
        printf("%uth sample result: %u\t%u\n", sample, sampleSize,
                correctedPositives);
        fprintf(resultFile, "%u\t%u\n", sampleSize, correctedPositives);
    }

    fclose(resultFile);
    free(source);

    return 0;
}
