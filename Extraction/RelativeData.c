#include "RelativeData.h"
#include <assert.h>
/*
  get:
  - target: allocated space of n_buckets * sizeof *target to store the indices
  - population_size: the amount of people in the population
  - n_buckets: the number of equal-size buckets the data should be divided into
  give: the indices where a new bucket starts
 */
// TODO input checks
// TODO step doesn't need to be calculated in every iteration
// TODO ggf eine Funktion im Interface
void bucket_indices(size_t target[], size_t population_size, size_t n_buckets)
{
    for (size_t i = 0; i < n_buckets; ++i)
    {
        target[i] = (size_t) ((population_size  + 1)/ n_buckets) * i;
    }
}

/*
  get:
  - target: 0-initialized, allocated space of at
    least n_buckets * sizeof *buckets bytes
  - buckets: array containing the start indices of the buckets
  - n_buckets: length of the buckets-array
  - occurences_of_n_infected: occurences_of_n_infected[i] contains
    the number of samples that returned i infected people
 */
void percentage_of_trials_in_bucket(double target[], size_t *buckets,
                                    size_t n_buckets,
                                    TYPE *occurences_of_n_infected,
                                    size_t *sample_sizes, size_t n_samples)
{
    for (size_t i = 0, bucket = 0; i <= n_samples; ++i) {
    // Relies on short circuiting!
        if (bucket + 1 < n_buckets && i >= buckets[bucket + 1]) {
            bucket++;
        }
        target[bucket] += (double)occurences_of_n_infected[i] / sample_sizes[i];
    }
}

void relative_trial_results(double *target, unsigned int *trial_results,
                            unsigned int *sample_sizes, size_t n_trials) {
    for (size_t i = 0; i < n_trials; ++i) {
        target[i] = (double)trial_results[i] / sample_sizes[i];
    }
}

void write_percentages_to_file(double *relative_results, size_t n_samples,
                               FILE *file)
{
    if (file == NULL)
    {
        fprintf(stderr, "write_percentages_to_file: no valid file was given.");
    }

    // round to percentages
    double *percentage_points = malloc(n_samples * sizeof *percentage_points);

    for (size_t i = 0; i < n_samples; i++) {
        percentage_points[i] = round(relative_results[i] * 100);
    }

    // write to file
    unsigned int count = 1;
    double rel_count = 1/n_samples;

    for (size_t i = 0; i < n_samples - 1; i++) {

        if (percentage_points[i] < percentage_points[i + 1]) {
            // TODO if sample sizes are not constant, multiply with a weight
            rel_count = (double) count / n_samples;
            fprintf(file, "%lf %lf\n", percentage_points[i] / 100, rel_count);
            count = 1;
        }
        else {
            count++;
            rel_count = (double) count/n_samples;
        }
    }
    rel_count = (double)count / n_samples;
    fprintf(file, "%lf %lf\n", percentage_points[n_samples - 1] / 100, rel_count);
}
