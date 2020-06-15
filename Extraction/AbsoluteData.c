#include "AbsoluteData.h"

// get: trial_results: unsigned int array with number of infected people per simulation
// get: n_simulations: size_t length of trial_results
// get: target: unsigned int array with length trial_results
// get: min, max: unsigned int pointers to save minimum and maximum number of infected people
// give: array with the number of occurences of each number of infected people
// give: fill min, max with highest and lowest non 0 entry
void absolute_frequencies(unsigned int* trial_results,
                          size_t n_simulations,
                          unsigned int* target,
                          unsigned int* min,
                          unsigned int* max,
                          )
{
  unsigned int max_infected = get_max_value(trial_results, n_simulations);
  unsigned int* temp = malloc((sizeof *temp) * max_infected);
  free(temp);
}

unsigned int get_max_value(unsigned int* array, size_t n_elems)
{
  unsigned int max_value;
  for(unsigned int i = 0; i < n_elems; i++)
    {
      max_value = max(max_value, trial_results[i]);
    }
  return max_value;
}

unsigned int max(unsigned int a, unsigned int b)
{
  return a > b ? a : b;
}
