#include "RelativeData.h"
#include <stdio.h> // TODO delete
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
// TODO GGF config struct

void bucket_indices(size_t target[], size_t population_size, size_t n_buckets) {
    printf("%p\n", (void *) target);
    printf("%zu\n", population_size);
    printf("%zu\n", n_buckets);
}

void percentage_of_trials_in_bucket(double target[], size_t *buckets,
                                    size_t n_buckets,
                                    TYPE *occurences_of_n_infected,
                                    size_t population_size) {
  printf("%p\n", (void *)target);
  printf("%p\n", (void *)buckets);
  printf("%zu\n", n_buckets);
  printf("%p\n", (void *)occurences_of_n_infected);
  printf("%zu\n", population_size);
} // Kann ggf bucket_beginnings selbst aufrufen
