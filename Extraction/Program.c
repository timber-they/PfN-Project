#include "AbsoluteData.h"
#include "CSV_Output.h"
#include "ConfidenceIntervals.h"
#include "Histograms.h"
#include "Median.h"
#include "Medium.h"
#include "RelativeData.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


/* Input a file name containing trial results data, size_t  number of trials
 * (should be number of lines of trial results file), int basic population size
 * and double confidence level.
 * Writes statistics into csv for gnuplot.
 */
int main(int argc, char *argv[]) {
    unsigned int *trial_results = NULL, population_size, *confidence_interval,
        line = 0;
    size_t number_of_trials;
    double medium, median, confidence_level, *relative_results = NULL;
        /* **diagram_data; */
    FILE *input_data;

    /* diagram data: array of 2-arrays containing diagram point {x,y}
     * x-axis: n_infected (= trial_results)
     * y-axis: n_simulations (n_infected) / N_simulations
     */

    // Done Julius check parameters for format failures
    // check argument counter
    if (argc > 5) {
        fprintf(stderr, "Usage: {} <file name: trial results data> ");
        fprintf(stderr, "[int: number of trials] [int: basic population size] ");
        fprintf(stderr, "[double: confidence level]\n");
        fprintf(stderr, "Error: Too many arguments\n");
        return EXIT_FAILURE;
    }

    if (argc < 2)
        fprintf(stderr, "Error: Too little arguments\n");
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
            trial_results = (unsigned int *)malloc(1000 * sizeof(unsigned int));
            relative_results = (double *)malloc(1000 * sizeof(double));
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
        trial_results =
            (unsigned int *)malloc(number_of_trials * sizeof(unsigned int));
        relative_results = (double *)malloc(number_of_trials * sizeof(double));
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
    while (fscanf(input_data, "%u\n", &trial_results[line]) != EOF)
        line++;
    fclose(input_data);

    if (number_of_trials == 1)
        number_of_trials = line;
    if (line != number_of_trials)
        fprintf(stderr, "Warning: Given number of trials does not correspond to "
                "received data set.");
    // TODO Wenn wir das eh auslesen, warum brauchen wir dann das Arguement? -
    // Hannes

    // Done Julius check file for format failures (done by fscanf)
    // Done Julius parse start parameters

    // Done Julius read trial_results from file

    median = get_median(trial_results, number_of_trials);
    medium = get_medium(trial_results, number_of_trials);
    // TODO conf_itvl expects an array of doubles - Hannes
    confidence_interval =
        conf_itvl(trial_results, number_of_trials, confidence_level); 

    for (int i = 0; i < number_of_trials; i++) {
        relative_results[i] = (double)trial_results[i] / population_size;
    }

    // Done Hannes count trial_results to get n_simulations > extract diagram data
    // Done Hannes accumulate histogram intervals?
    // TODO Pascal write data into gnuplot-readable (csv) file

    // Actual data for the histogram - For absolute and relative data histograms

    unsigned int max_infected = array_max_value(trial_results, number_of_trials);

    // Actual data for the histogram - Absolute values

    unsigned int *x_a = (unsigned int *)malloc((max_infected + 1) * sizeof *x_a);
    unsigned int *y_a =
        (unsigned int *)malloc((max_infected + 1) * sizeof *x_a);

    for (size_t i = 0; i <= max_infected; ++i) {
      x_a[i] = i;
    }
    absolute_frequencies(trial_results, number_of_trials, y_a);

    // Actual data for the histogram - Relative values

    // TODO Where should this value be determined?
    // and what happens, when N_BUCKETS > number_of_trials?
    size_t n_buckets = 10;
    double *x_r = (double *)malloc(n_buckets * sizeof *x_a);
    double *y_r = (double *)malloc(n_buckets * sizeof *x_a);
    size_t *buckets = (size_t *)malloc(n_buckets * sizeof *x_a);

    bucket_indices(buckets, population_size, n_buckets);
    percentage_of_trials_in_bucket(y_r, buckets, n_buckets, y_a, population_size);
    for (size_t i = 0; i < n_buckets; ++i) {
        x_r[i] = (double) (population_size / n_buckets) * i;
    }

    // adjustment for imagined number_of_trials for first version (should be
    // removed later) (TODO)
    number_of_trials = 10;
    
    // Array containing x values (infected), should be filled with real data
    double *x = (double *)malloc(number_of_trials * sizeof(double));
    // Array containing y values (appearance of infected), should be filled with
    // real data
    double *y = (double *)malloc(number_of_trials * sizeof(double));
    // imagined data, no meaning
    int i; // TODO Variables should be declred at top
    for (i = 0; i < number_of_trials; i++) {
        x[i] = (double)i;
        y[i] = (double)10 / i;
    }
    // source data created
    FILE *source; // TODO Variables should be declared at top
    source = fopen("data.dat", "w+");
    if (source == NULL)
        return EXIT_FAILURE;
    for (i = 0; i < number_of_trials; i++) {
        fprintf(source, "%lf %lf\n", x[i], y[i]);
    }
    fclose(source);
    createCSV("data.dat", "results.csv");

    // TODO Pascal paint gnuplot data

    paintHistogram("data.dat");
    remove("data.dat");
    free(x);
    free(y);

    printf("%lf, %lf, %u, %u\n", median, medium, confidence_interval[0],
    confidence_interval[1]);

    return EXIT_SUCCESS;
}
