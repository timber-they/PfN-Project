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
                                    size_t population_size)
                                    {

    for (size_t i = 0, bucket = 0; i <= population_size; ++i) {
        // Relies on short circuiting!
        if (bucket + 1 < n_buckets && i >= buckets[bucket+1])
        {
            bucket++;
        }
        target[bucket] += (double) occurences_of_n_infected[i] / population_size;
    }
} // Kann ggf bucket_beginnings selbst aufrufen
