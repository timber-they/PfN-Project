#include "AbsoluteData.h"
#include "CSV_Output.h"
#include "ConfidenceIntervals.h"
#include "Histograms.h"
#include "Median.h"
#include "Medium.h"
#include "RelativeData.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    unsigned int *trial_results = NULL,
                 *sample_sizes = NULL,
                 population_size,
                 line = 0,
                 i;
    size_t number_of_trials;
    double medium, median, *confidence_interval, confidence_level, *relative_results = NULL;
        /* **diagram_data; */
    FILE *input_data,
         *source;

    if (argc > 5) {
        fprintf(stderr, "Usage: {} <file name: trial results data> ");
        fprintf(stderr, "[int: number of trials] [int: basic population size] ");
        fprintf(stderr, "[double: confidence level]\n");
        fprintf(stderr, "Error: Too many arguments\n");
        return EXIT_FAILURE;
    }

    if (argc < 2)
        fprintf(stderr, "Error: Too few arguments\n");
    else if (argc < 5) {
        // TODO was soll diese Nachricht sagen? - Hannes
        printf("Warning: Interpreting input as {} <file name> ");
        printf("[number of trials = (read from input)] [basic population size");
        printf(" = 8.2e7] [confidence level = 0.95]\n");
        confidence_level = 0.95;
        if (argc < 4)
            population_size = 82000000;
        if (argc < 3) {
            number_of_trials = 1; // bad guessing
            trial_results = malloc(1000 * sizeof(trial_results));
            sample_sizes = malloc(1000 * sizeof(sample_sizes));
            relative_results = malloc(1000 * sizeof(relative_results));
        }
    }

    if (argc > 2 && sscanf(argv[2], "%zu", &number_of_trials) < 1) {
        fprintf(stderr,
                "Error: Could not parse argument 2: number of trials must be "
                "positive integer. Input: %s\n",
                argv[2]);
        return EXIT_FAILURE;
    }
    if (number_of_trials < 1) {
        fprintf(stderr, "Error: Number of trials must be positive. Input: %zu\n",
                number_of_trials);
        return EXIT_FAILURE;
    } else if (number_of_trials > 1) {
        trial_results = malloc(number_of_trials * sizeof(trial_results));
        sample_sizes = malloc(number_of_trials * sizeof(sample_sizes));
        relative_results = malloc(number_of_trials * sizeof(relative_results));
    }
    if (argc > 3 && sscanf(argv[3], "%u", &population_size) < 1) {
        fprintf(stderr,
                "Error: Could not parse argument 3: population size must be "
                "positive integer. Input: %s\n",
                argv[3]);
        return EXIT_FAILURE;
    }
    if (population_size < 1) {
        fprintf(stderr, "Error: Population size must be positive. Input: %s\n",
                argv[3]);
        return EXIT_FAILURE;
    }
    if (argc > 4 && sscanf(argv[4], "%lf", &confidence_level) < 1) {
        fprintf(stderr,
                "Error: Could not parse argument 4: confidence level must be "
                "floating point number. Input: %s\n",
                argv[4]);
        return EXIT_FAILURE;
    }
    if (confidence_level < 0 || confidence_level > 1) {
        fprintf(stderr, "Error: Confidence level must be in [0; 1]. Input: %f\n",
                confidence_level);
        return EXIT_FAILURE;
    }
    if (strlen(argv[1]) > 32) {
        fprintf(stderr,
                "Error: Could not read file name. Must be shorter than 32 chars. "
                "Input: %s\n",
                argv[1]);
        return EXIT_FAILURE;
    }
    if (access(argv[1], F_OK) == -1) {
        fprintf(stderr, "Error: File %s could not be read or does not exist.\n",
                argv[1]);
        return EXIT_FAILURE;
    }

    input_data = fopen(argv[1], "r");

    if (input_data == NULL)
        return EXIT_FAILURE;
    while (fscanf(input_data, "%u\t%u\n", &sample_sizes[line], &trial_results[line]) != EOF)
        line++;
    fclose(input_data);

    if (number_of_trials == 1)
        number_of_trials = line;
    if (line != number_of_trials)
        fprintf(stderr, "Warning: Given number of trials does not correspond to "
                "received data set.\n");

    // transform absolute samples to percentage of sampled subjects infected
    // TODO round results?
    relative_trial_results(relative_results, trial_results, sample_sizes, number_of_trials);

    // Sort relative results
    sort_double(relative_results, number_of_trials);

    // Statistics
    median = get_median(relative_results, number_of_trials);
    medium = get_medium(relative_results, number_of_trials);
    confidence_interval =
    conf_itvl(relative_results, number_of_trials, confidence_level);

    // Prepare histogram data
    const size_t n_buckets = 100;
    size_t buckets[n_buckets];
    double percentages[n_buckets];
    bucket_indices(buckets, population_size, n_buckets);
}
