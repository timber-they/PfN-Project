#include "AbsoluteData.h"
#include "CSV_Output.h"
#include "ConfidenceIntervals.h"
#include "Histograms.h"
#include "Median.h"
#include "Medium.h"
#include "RelativeData.h"
#include "Sort.h"
#include "InputCheck.h"

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
        line = 0;
    size_t number_of_trials;
    double medium, median, *confidence_interval, confidence_level, *relative_results = NULL;
    /* **diagram_data; */
    FILE *input_data,
        *source;

    // check for bad input

    if (argc < 2)
    {
        fprintf(stderr, "Error: Too few arguments\n");
        return EXIT_FAILURE;
    }
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

    check_input(argc, argv, &number_of_trials, &trial_results, &sample_sizes, &population_size, &relative_results, &confidence_level);


    // read sampling input TODO Message

    input_data = fopen(argv[1], "r");
    if (input_data == NULL)
        return EXIT_FAILURE;
    while (fscanf(input_data, "%u\t%u\n", &sample_sizes[line],
                  &trial_results[line]) != EOF)
        line++;
    fclose(input_data);

    // TODO move to InputCheck.c
    if (number_of_trials == 1)
        number_of_trials = line;
    if (line != number_of_trials)
        fprintf(stderr, "Warning: Given number of trials does not correspond to "
                "received data set.\n");

    // transform absolute samples to percentage of sampled subjects infected
    relative_trial_results(relative_results, trial_results, sample_sizes, number_of_trials);

    // Sort relative results
    sort_double(relative_results, number_of_trials);

    // Statistics
    median = get_median(relative_results, number_of_trials);
    medium = get_medium(relative_results, number_of_trials);
    confidence_interval =
        conf_itvl(relative_results, number_of_trials, confidence_level);

    source = fopen("data.dat", "w+");
    if (source == NULL) {
        fprintf(stderr, "could not open file data.dat");
        return EXIT_FAILURE;
    }

    write_percentages_to_file(relative_results, number_of_trials, source);

    fclose(source);


    createCSV("data.dat", "results.csv");

    // TODO Pascal paint gnuplot data

    paintHistogram("data.dat");
    //remove("data.dat");
    printf("Population Size:%u, median: %lf, medium: %lf, confidence_interval[0]: %lf, confidence_interval[1]: %lf\n", population_size, median, medium,
           confidence_interval[0],
           confidence_interval[1]);

    free(trial_results);
    free(sample_sizes);
    free(relative_results);
    return EXIT_SUCCESS;
}
