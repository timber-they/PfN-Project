#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[])
{
    unsigned int population_size, sample_size, sample_count;
    double probability, specificity, selectivity;
    int seed;

    if (argc < 5 || argc > 8
                 || sscanf(argv[1], "%ud", &population_size) != 1
                 || sscanf(argv[2], "%ud", &sample_size) != 1
                 || sscanf(argv[3], "%ud", &sample_count) != 1
                 || sscanf(argv[4], "%lf", &probability) != 1
                 || (argc > 5 && sscanf(argv[5], "%lf", &specificity) != 1)
                 || (argc > 6 && sscanf(argv[6], "%lf", &selectivity) != 1)
                 || (argc > 7 && sscanf(argv[7], "%d", &seed) != 1))
    {
        fprintf(stderr, "Usage: <Ps> <Ss> <Sc> <p> [<sp>] [<se>] [<s>]");
        return 1;
    }


    


    // Extraction

    return 0;
}