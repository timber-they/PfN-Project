#ifndef RELATIVE_DATA_H
#define RELATIVE_DATA_H

#include <stddef.h>

#define TYPE unsigned int
/*
  get:
  - target: allocated space of n_buckets * sizeof *target to store the indices
  - population_size: the amount of people in the population
  - n_buckets: the number of equal-size buckets the data should be divided into
 */
// give: the indices where a new bucket starts
void bucket_indices(size_t target[], size_t population_size, size_t n_buckets);

void percentage_of_trials_in_bucket(double target[], size_t *buckets, size_t n_buckets,
                                    TYPE *occurences_of_n_infected, size_t population_size);
#endif
