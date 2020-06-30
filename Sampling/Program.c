#include "Lazy_Sampling.h"
#include "correction.h"
#include "Random.h"
#include <stdlib.h>
#include <stdio.h>

// Simulation
static int simulateTest(LazySource *source, double sensitivity, double specificity,
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

// Method to check if File is already open and open it
static FILE *openOrReopen(const char* filename, FILE *file)
{
    if (file != NULL)
    {
        file = freopen(filename, "w", file);
    } else
    {
        file = fopen(filename, "w");
    }
    
    return file;
}

// Simulate the Samples based on everything
static unsigned int simulateSample(unsigned int sampleSize, LazySource *source,
        double sensitivity, double specificity)
{
    unsigned int positives = 0;
    double correctedPercentage;
    unsigned int correctedPositives;

    reset(source);

    for (int i = 0; i < sampleSize; i++)
    {
        positives = simulateTest(source, sensitivity, specificity, positives);
    }

    correctedPercentage = correction((double) positives /
            sampleSize, sensitivity, specificity);
    correctedPositives = correctedPercentage * sampleSize;
    return correctedPositives;
}

// Simulate the Samples based on everything
static unsigned int getSampleSize(unsigned int line, FILE* resultFile,
                                  unsigned int maxSampleSize)
{
    unsigned int sampleSize = 0,
                 index,
                 exitCode = maxSampleSize + 1;
    
    // Check for existing file
    if(resultFile == NULL)
    {
        fprintf(stderr, 
                "Couldn't open file for and no sample size was passed\n");
        return exitCode;
    }
    // Go though the file line by line
    for (index = 0; fscanf(resultFile, "%u\n", &sampleSize) != EOF; index++)
    {
        if (index == line)
        {
            return sampleSize;
        }
    }
    return exitCode;
}

// Everything together 
int main(int argc, char *argv[])
{
    // All the Variables we need
    double       p = 0,
                 sensitivity = 0.909,
                 specificity = 0.991;
    unsigned int populationNumber = 0,
                 sampleNumber = 0, // number of samples to create
                 sampleSize = -1,
                 line = 0,
                 correctedPositives = 0;
    int          seed = 96661;
    LazySource  *source;

    // The output file    
    const char *resultFileName = "sampleResult.tsv";
    FILE *resultFile = NULL;

    // Check for Error and sscanf the Values
    if (argc < 4 || sscanf(argv[1], "%lf", &p) != 1
                 || sscanf(argv[2], "%ud", &populationNumber) != 1
                 || sscanf(argv[3], "%ud", &sampleNumber) != 1
                 || (argc > 4 && sscanf(argv[4], "%ud", &sampleSize) != 1)
                 || (argc > 5 && sscanf(argv[5], "%d", &seed) != 1)
                 || (argc > 6 && sscanf(argv[6], "%lf", &sensitivity) != 1)
                 || (argc > 7 && sscanf(argv[7], "%lf", &specificity) != 1))
    {
        // If wrong input give correct Usage as Output and end
        fprintf(stderr, "Usage: %s <p> <N> <n> [<S>] [<s>] [<se>] [<sp>]\n",
                argv[0]);
        return 1;
    }

    // Open our resultFile
    resultFile = fopen(resultFileName, "r+");
    // Test if our probabilty is beween 1 and 0
    if (p < 0 || p > 1)
    {
        fprintf(stderr, "Probability can't be less than 0 or more than 1\n");
        return 1;
    }

    // Sampling_Init
    initRandom(seed);

    resultFile = openOrReopen(resultFileName, resultFile);
    // check for ExistingFile again
    if (resultFile == NULL)
    {
        fprintf(stderr, "Could not open file");
        return 1;
    }
    
    // create sampling for every sample-size
    source = getLazySource(populationNumber, p);
    printf("Got lazy source\n");
    
    if (sampleSize == -1)
    {
        // read sampleSizes from file
        for(line = 0; line < sampleNumber; line++)
        {
            sampleSize = getSampleSize(line, resultFile, populationNumber);
            // Test for Error
            if (sampleSize > populationNumber)
            {
                fprintf(stderr, "File could not be opened or "
                                "SampleSizes in file are not valid.\n");
                return 1;
            }
            correctedPositives = simulateSample(sampleSize, source, sensitivity,
                                                specificity);
            printf("%uth sample result: %u\t%u\n", line, sampleSize,
                   correctedPositives);
            fprintf(resultFile, "%u\t%u\n", sampleSize, correctedPositives);
        }
        // Line has to be = sampleNumber, if not give Error and close file
        if (line != sampleNumber)
        {
            fprintf(stderr, "Received %u instead of %u sample sizes\n", 
                    line, sampleNumber);
            return 1;
        }
        else
        {
            // if Line = SampleNumber give Status
            printf("Succesfully read %u sample sizes\n", sampleNumber);
        }
    }
    else
    {
        // read sampleSize from input
        for(line = 0; line < sampleNumber; line++)
        {
            printf("Using %u fixed sample sizes\n", sampleNumber);
            correctedPositives = simulateSample(sampleSize, source, sensitivity,
                                                specificity);
            printf("%uth sample result: %u\t%u\n", line, sampleSize,
                   correctedPositives);
            fprintf(resultFile, "%u\t%u\n", sampleSize, correctedPositives);
        }
    }

    fclose(resultFile);
    free(source);

    return 0;
}

