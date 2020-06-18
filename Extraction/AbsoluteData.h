#ifndef ABSOLUTE_DATA_H
#define ABSOLUTE_DATA_H

#define TYPE unsigned int
void absolute_frequencies(TYPE *trial_results, size_t n_simulations,
                          TYPE *target, size_t target_length);

TYPE array_max_value(TYPE *array, size_t n_elems);
#endif
