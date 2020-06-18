#include "../Extraction/AbsoluteData.h"
#include <stdio.h>
#include <check.h>

START_TEST(test_array_max_value) {
    unsigned int temp, calculated_max, max = 100000;
    unsigned int array[] = {1, 2, 3, 5, 7, 11, 120, 2000, 100000};
    size_t len = sizeof array / sizeof array[0];
    for (unsigned int i = 0; i < len; i++) {
        temp = array[len - 1];
        for (unsigned int j = len - 1; j > 0; j--) {
            array[j] = array[j - 1];
        }
        array[0] = temp;
        calculated_max = array_max_value(array, 9);
        ck_assert(calculated_max == max);
    }
}
END_TEST

START_TEST(test_absolute_frequencies_positive) {
  TYPE trial_results[] = {123, 540, 10004, 540, 540};
  size_t n_simulations = sizeof trial_results / sizeof trial_results[0];
  size_t max_infected = 10004;
  TYPE *frequencies = (TYPE *)calloc((max_infected + 1), sizeof *frequencies);

  absolute_frequencies(trial_results, n_simulations, frequencies);
  ck_assert(frequencies[123] == 1
         && frequencies[540] == 3
         && frequencies[10004] == 1
      );
  free(frequencies);
}
END_TEST
