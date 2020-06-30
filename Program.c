#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>

int getLengthInt(int i)
{
    char str[20];
    int len;
    sprintf(str, "%d", i);
    len = strlen(str);
    return len;
}

int getLengthDouble(double d)
{
    char str[20];
    int len;
    sprintf(str, "%lf", d);
    len = strlen(str);
    return len;
}

char* toString(int i)
{
    char *str = malloc(20);
    sprintf(str, "%d", i);
    return str;
}

int writeSizesToFile(char* fileName, unsigned int sampleSize, unsigned int sampleNumber)
{    
    FILE *resultFile = fopen(fileName, "w");
    if(resultFile == NULL)
    {
        fprintf(stderr, "Could not open file");
        return 1;
    }
    
    printf("Writing %u sample sizes\n", sampleNumber);
    for(int sample = 0; sample < sampleNumber; sample++)
    {
        fprintf(resultFile, "%u\n", sampleSize);
    }

    fclose(resultFile);

    return 0;
}

// TODO: Move to extra file
int run(char* call)
{
    FILE *p = popen(call, "re");
    char buf[256];

    if (p == NULL)
    {
        fprintf(stderr, "Can't run %s; failed with %s", call, strerror(errno));
        return -1;
    }

    printf("Running %s", call);
    while(fgets(buf, sizeof(buf), p) != 0)
    {
        printf("%s", buf);
    }

    return pclose(p);
}

int main (int argc, char *argv[])
{
    unsigned int population_size, sample_size, sample_count;
    double probability;
    double sensitivity = 0.909;
    double specificity = 0.991;
    int seed = 11;
    int return_code;
    char *sampling_call;
    char extration_call[100];
    char trial_results_name[100];
    double confidence_level;
    char *resultsName = "Sampling/sampleResult.tsv";

    if (argc < 5 || argc > 8
                 || sscanf(argv[1], "%ud", &population_size) != 1
                 || sscanf(argv[2], "%ud", &sample_size) != 1
                 || sscanf(argv[3], "%ud", &sample_count) != 1
                 || sscanf(argv[4], "%lf", &probability) != 1
                 || (argc > 5 && sscanf(argv[5], "%d", &seed) != 1)
                 || (argc > 6 && sscanf(argv[6], "%lf", &sensitivity) != 1)
                 || (argc > 7 && sscanf(argv[7], "%lf", &specificity) != 1)) 
    {
        fprintf(stderr, "Usage: %s <Ps> <Ss> <Sc> <p> [<s>] [<se>] [<sp>]\n",
            argv[0]);
        return 1;
    }

    sampling_call = calloc(34 + getLengthDouble(probability) + 1 + 
        getLengthInt(population_size) + 1 + 
        getLengthInt(sample_count) + 1 +
        getLengthInt(-1) + 1 +
        getLengthInt(seed) + 1 +
        getLengthDouble(sensitivity) + 1 +
        getLengthDouble(specificity) + 2, sizeof(char));
        
    sprintf(sampling_call, "cd Sampling && make && ./Program.x %lf %d %d %d %d %lf %lf\n", 
            probability, population_size, sample_count, -1, seed, sensitivity, specificity);

    if (writeSizesToFile(resultsName, sample_size, sample_count) != 0)
    {
        return 1;
    }
    
    printf("Running sampling with %s\n", sampling_call);
    return_code = run(sampling_call);
    if (return_code != 0)
    {
        fprintf(stderr, "Running the sampling program failed with %d\n", 
                return_code);
        return 1;
    }

    // Extraction
    
    strcpy(trial_results_name, resultsName);
    confidence_level = 0.90;

    sprintf(extration_call, "(cd Extraction && make) && Extraction/Program.x"
            " %s %d %d %lf",
            trial_results_name, sample_count, population_size, 
            confidence_level);
            
    return_code = run(extration_call);
    
    if (return_code != 0)
    {
        fprintf(stderr, "Running the extraction program failed with %d\n", 
                return_code);
        return 1;
    }
    
    return 0;
}
