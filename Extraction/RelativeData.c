#include "RelativeData.h"
#include <assert.h>
/*
  INFORMATION:
  * number of trials that returned n infected for n in [0, ..., max_infected]
  * results of the singular trials
  GOAL: Welcher Anteil der Versuche hatte einen Anteil an Infizierten im Bereich [Bucket]
*/
// Anteil der Bevölkerung infiziert: (double) n_infected / population_size

// Grenzen der Buckets (10 % infiziert von 0 - 10, 20% infiziert von 10 - 20,
// ...)
// Wie viele Durchläufe haben etwas im Berich von [Bucket] zurückgegeben?
// Welchem Anteil der Versuche entspricht das?
// TODO input checks
// TODO step doesn't need to be calculated in every iteration
// TODO ggf eine Funktion im Interface
void bucket_indices(size_t target[], size_t population_size, size_t n_buckets) {
    for (size_t i = 0; i < n_buckets; ++i) {
        target[i] = (size_t) ((population_size  + 1)/ n_buckets) * i;
        }
}

// TODO target must be 0 initialized!
void percentage_of_trials_in_bucket(double target[], size_t *buckets,
                                    size_t n_buckets,
                                    TYPE *occurences_of_n_infected,
                                    size_t population_size) {

    for (size_t i = 0, bucket = 0; i <= population_size; ++i) {
        // Relies on short circuiting!
        if (bucket + 1 < n_buckets && i >= buckets[bucket+1])
        {
            bucket++;
        }
        target[bucket] += (double) occurences_of_n_infected[i] / population_size;
    }
} // Kann ggf bucket_beginnings selbst aufrufen
