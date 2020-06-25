#include "../Extraction/Median.h"

START_TEST(test_median_sorted) {
  double odd_sorted[5] = {1, 2, 4, 6, 7}; // median is 4.0
  double even_sorted[4] = {1, 2, 3, 4};     // median is 2.5

  double test_odd_sorted = get_median(odd_sorted, 5);
  double diff = test_odd_sorted - 4.0;
  ck_assert(diff < 0.001 && diff > - 0.001);
  double test_even_sorted = get_median(even_sorted, 4);
  diff = test_even_sorted - 2.5;
  ck_assert(diff < 0.001 && diff > - 0.001);
}
END_TEST

