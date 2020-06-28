#ifndef INPUTCHECK_H
#define INPUTCHECK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void check_input(int argc, char *argv[], size_t *number_of_trials,
                 unsigned int **trial_results, unsigned int **sample_sizes,
                 unsigned int *population_size, double **relative_results,
                 double *confidence_level);

#endif
