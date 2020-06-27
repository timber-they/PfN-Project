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
#include <math.h>

int compare_double( const void* va , const void* vb )
{
    const double a = *( const double* )va,
                 b = *( const double* )vb;

    if (fabs(a - b) < 1.0e-16)
    {
        return 0;
    }
    if (a > b)
    {
        return 1;
    }
    return -1;
}

static void sort_double(double *array, size_t n_elems) {
    qsort(array, n_elems, sizeof *array, compare_double);
}


/* Input a file name containing trial results data, size_t  number of trials
 * (should be number of lines of trial results file), int basic population size
 * and double confidence level.
 * Writes statistics into csv for gnuplot.
 */
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
        fprintf(stderr, "Warning: Given number of trials (%lu) does not correspond to "
                "received data set (%u).\n", number_of_trials, line);
    // TODO Wenn wir das eh auslesen, warum brauchen wir dann das Arguement? -
    // Hannes

    // Done Julius check file for format failures (done by fscanf)
    // Done Julius parse start parameters

    // Done Julius read trial_results from file

    //sort_uint(trial_results, number_of_trials);

    // FIXME doesn't work with variable sample sizes, cconvert get_median and
    // get_medium back to double again and apply them to relative_results
    //median = get_median(trial_results, number_of_trials);
    //medium = get_medium(trial_results, number_of_trials);
    // TODO conf_itvl expects an array of doubles - Hannes
    /*
     confidence_interval =
        conf_itvl(trial_results, number_of_trials, confidence_level);
     */
    for (i = 0; i < number_of_trials; i++) {
        relative_results[i] = (double)trial_results[i] / sample_sizes[i];
        //printf("%d\n",sample_sizes[i]);
    }

    // This is where we should do the statistics for relative_results

    // Round to two decimal places, i.e. whole percents
    for(i= 0 ; i < number_of_trials; i++) {
        relative_results[i] = ceilf(relative_results[i]  * 100) / 100;
        //printf("%lf\n",relative_results[i]);
    }

    sort_double(relative_results, number_of_trials);
    median = get_median(relative_results, number_of_trials);
    medium = get_medium(relative_results, number_of_trials);
    confidence_interval =
    conf_itvl(relative_results, number_of_trials, confidence_level);
    /*
    for(i= 0 ; i < number_of_trials; i++) {
        printf("%lf\n",relative_results[i]);
    }
    */
    /*
    // Done Hannes count trial_results to get n_simulations > extract diagram data
    // Done Hannes accumulate histogram intervals?
    // TODO Pascal write data into gnuplot-readable (csv) file

    // Actual data for the histogram - For absolute and relative data histograms

    unsigned int max_infected = array_max_value(trial_results, number_of_trials);

    // Actual data for the histogram - Absolute values

    unsigned int *x_a = malloc((max_infected + 1) * sizeof *x_a);
    unsigned int *y_a = malloc((max_infected + 1) * sizeof *y_a);

    for (size_t i = 0; i <= max_infected; ++i) {
      x_a[i] = i;
    }
    absolute_frequencies(trial_results, number_of_trials, y_a);

    // Actual data for the histogram - Relative values

    // TODO Where should this value be determined?
    // and what happens, when N_BUCKETS > number_of_trials?
    size_t n_buckets = 10;
    double *x_r = malloc(n_buckets * sizeof *x_r);
    double *y_r = malloc(n_buckets * sizeof *y_r);
    size_t *buckets = malloc(n_buckets * sizeof *buckets);

    bucket_indices(buckets, population_size, n_buckets);
    percentage_of_trials_in_bucket(y_r, buckets, n_buckets, y_a, population_size);
    for (size_t i = 0; i < n_buckets; ++i) {
        x_r[i] = (double) (population_size / n_buckets) * i;
    }
    */
    // adjustment for imagined number_of_trials for first version (should be
    // removed later) (TODO)
    /*
    number_of_trials = 10;
    // Array containing x values (infected), should be filled with real data
    double *x = (double *)malloc(number_of_trials * sizeof(double));
    // Array containing y values (appearance of infected), should be filled with
    // real data
    double *y = (double *)malloc(number_of_trials * sizeof(double));
    // imagined data, no meaning

    for (i = 0; i < number_of_trials; i++) {
        x[i] = (double)i;
        y[i] = (double)10 / i;
    }
    */
    // source data created
    source = fopen("data.dat", "w+");
    if (source == NULL)
        return EXIT_FAILURE;

    // Count occurences of each value in relative_results
    unsigned int count = 1;
    double rel_count = (double) 1/number_of_trials;
    for (i = 0; i < number_of_trials - 1; i++) {
        if (relative_results[i] < relative_results[i+1]) {
            //printf("%lf\t%lu",relative_results[i],count);
            //printf("%lf %lf\n",relative_results[i],rel_count);
            fprintf(source, "%lf %lf\n",relative_results[i],rel_count);
            count = 1;
            rel_count = (double) count/number_of_trials;
        }
        else {
            count++;
            // Probably wrong for variable sample sizes
            rel_count = (double) count/number_of_trials;
        }
    }
    fprintf(source, "%lf %lf\n",relative_results[number_of_trials-1],
                                rel_count);
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
