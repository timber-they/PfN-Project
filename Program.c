#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

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

int main (int argc, char *argv[])
{
    unsigned int population_size, sample_size, sample_count;
    double probability;
    double sensitivity = 0.909;
    double specificity = 0.991;
    int seed, return_code;
    char *sampling_call;
    char extration_call[100];
    char trial_results_name[100];
    double confidence_level;

    if (argc < 5 || argc > 8
                 || sscanf(argv[1], "%ud", &population_size) != 1
                 || sscanf(argv[2], "%ud", &sample_size) != 1
                 || sscanf(argv[3], "%ud", &sample_count) != 1
                 || sscanf(argv[4], "%lf", &probability) != 1
                 || (argc > 5 && sscanf(argv[5], "%d", &seed) != 1)
                 || (argc > 6 && sscanf(argv[6], "%lf", &sensitivity) != 1)
                 || (argc > 7 && sscanf(argv[7], "%lf", &specificity) != 1)) 
    {
        fprintf(stderr, "Usage: %s <Ps> <Ss> <Sc> <p> <sS> [<s>] [<se>] [<sp>]\n",
            argv[0]);
        return 1;
    }

    sampling_call = calloc(34 + getLengthDouble(probability) + 1 + 
        getLengthInt(population_size) + 1 + 
        getLengthInt(sample_count) + 1 +
        sample_count * (getLengthInt(sample_size) + 1) + 1, sizeof(char));
        
    sprintf(sampling_call, "cd Sampling && make && ./Program.x %lf %d %d %d %d %lf %lf", 
            probability, population_size, sample_count,sample_size ,  seed, sensitivity, specificity);
    /*
    for (int i = 0; i < sample_count; i++)
    {
        strcat(sampling_call, " ");
        strcat(sampling_call, toString(sample_size));
    }
    */
    printf("Running sampling with %s\n", sampling_call);
    return_code = system(sampling_call);

    if (return_code != 0)
    {
        fprintf(stderr, "Running the sampling program failed with %d\n",
                return_code);
        return 1;
    }



    // Extraction
    
    strcpy(trial_results_name, "../Sampling/sampleResult.tsv");
    confidence_level = 0.90;

    sprintf(extration_call, "cd Extraction && make && ./Program.x"
            " %s %d %d %lf",
            trial_results_name, sample_count, population_size, 
            confidence_level);
            
    return_code = system(extration_call);
    
    if (return_code != 0)
    {
        fprintf(stderr, "Running the extraction program failed with %d\n", 
                return_code);
        return 1;
    }
    
    return 0;
}
