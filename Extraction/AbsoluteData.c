#include "AbsoluteData.h"
#include <stdlib.h>
#include <assert.h>

TYPE max(TYPE a, TYPE b) { return a > b ? a : b; }

TYPE array_max_value(TYPE *array, size_t n_elems) {
  assert(array != NULL);
  assert(n_elems > 0);

  TYPE max_value = 0;
  for (TYPE i = 0; i < n_elems; i++) {
    max_value = max(max_value, array[i]);
  }
  return max_value;
}

/* get: trial_results: TYPE array
   with number of infected people per simulation

   get: n_simulations: size_t length of
   trial_results
  get: target: TYPE array
   with length trial_results

   // TODO
   get: min, max:
   TYPE pointers to save minimum and
   maximum number of infected people

   give: array with the number of occurences of
   each number of infected people give: fill min,
   max with highest and lowest non 0 entry
*/

// TODO useful trimming could be applied here
// so the returned array is not full of zeros
void absolute_frequencies(TYPE *trial_results, size_t n_simulations,
                          TYPE *target//, size_t target_length
                          /* TYPE *min, */
                          /* TYPE *max */
    )
{
    /* size_t max_infected = target_length; */
    TYPE n_infected;
   for (TYPE i = 0; i < n_simulations; i++) {
        n_infected = trial_results[i];
        target[n_infected]++;
    }
}

