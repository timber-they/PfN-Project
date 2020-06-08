#include "../Extraction/Median.h"

START_TEST(test_median_sorted) {
  double odd_sorted[5] = {1.0, 2.0, 4.0, 6.0, 7.0}; // median is 4.0
  double even_sorted[4] = {1.0, 2.0, 3.0, 4.0};     // median is 2.5

  double test_odd_sorted = median_sort(odd_sorted, 5);
  ck_assert(test_odd_sorted == 4.0);
  double test_even_sorted = median_sort(even_sorted, 4);
  double diff = test_even_sorted - 2.5;
  ck_assert(diff<0.1 && diff> - 0.1);
}
END_TEST

START_TEST(test_median_unsorted) {
  double odd_unsorted[5] = {2.0, 1.0, 6.0, 4.0, 7.0}; // median is 4.0
  double even_unsorted[4] = {4.0, 2.0, 3.0, 1.0};     // median is 2.5

  double test_odd_unsorted = median_sort(odd_unsorted, 5);
  ck_assert(test_odd_unsorted == 4.0);
  double test_even_unsorted = median_sort(even_unsorted, 4);
  double diff = test_even_unsorted - 2.5;
  ck_assert(diff < 0.1 && diff > -0.1);
}
END_TEST
