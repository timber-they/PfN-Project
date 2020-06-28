#include "InputCheck.h"

void check_input(int argc, char *argv[],
                 size_t *number_of_trials,
                 unsigned int **trial_results,
                 unsigned int **sample_sizes,
                 unsigned int *population_size,
                 double **relative_results,
                 double *confidence_level
    )
{
    if (argc > 5) {
        fprintf(stderr, "Usage: {} <file name: trial results data> ");
        fprintf(stderr, "[int: number of trials] [int: basic population size] ");
        fprintf(stderr, "[double: confidence level]\n");
        fprintf(stderr, "Error: Too many arguments\n");
        exit(EXIT_FAILURE);
    }

    if (argc > 2 && sscanf(argv[2], "%zu", number_of_trials) < 1) {
        fprintf(stderr,
                "Error: Could not parse argument 2: number of trials must be "
                "positive integer. Input: %s\n",
                argv[2]);
        exit(EXIT_FAILURE);
    }
    if (*number_of_trials < 1) {
        fprintf(stderr, "Error: Number of trials must be positive. Input: %zu\n",
                *number_of_trials);
        exit(EXIT_FAILURE);
    } else if (*number_of_trials > 1) {
        *trial_results = malloc(*number_of_trials * sizeof(trial_results));
        *sample_sizes = malloc(*number_of_trials * sizeof(sample_sizes));
        *relative_results = malloc(*number_of_trials * sizeof(relative_results));
    }
    if (argc > 3 && sscanf(argv[3], "%u", population_size) < 1) {
        fprintf(stderr,
                "Error: Could not parse argument 3: population size must be "
                "positive integer. Input: %s\n",
                argv[3]);
        exit(EXIT_FAILURE);
    }
    if (*population_size < 1) {
        fprintf(stderr, "Error: Population size must be positive. Input: %s\n",
                argv[3]);
        exit(EXIT_FAILURE);
    }
    if (argc > 4 && sscanf(argv[4], "%lf", confidence_level) < 1) {
        fprintf(stderr,
                "Error: Could not parse argument 4: confidence level must be "
                "floating point number. Input: %s\n",
                argv[4]);
        exit(EXIT_FAILURE);
    }
    if (*confidence_level < 0 || *confidence_level > 1) {
        fprintf(stderr, "Error: Confidence level must be in [0; 1]. Input: %f\n",
                *confidence_level);
        exit(EXIT_FAILURE);
    }
    if (strlen(argv[1]) > 32) {
        fprintf(stderr,
                "Error: Could not read file name. Must be shorter than 32 chars. "
                "Input: %s\n",
                argv[1]);
        exit(EXIT_FAILURE);
    }
    if (access(argv[1], F_OK) == -1) {
        fprintf(stderr, "Error: File %s could not be read or does not exist.\n",
                argv[1]);
        exit(EXIT_FAILURE);
    }


}
