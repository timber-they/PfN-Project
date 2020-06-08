#include "../Extraction/ConfidenceIntervals.h"
#include <check.h>

START_TEST(test_conf_itvl_same_values) {
  double all_nines[5] = {9, 9, 9, 9, 9};
  double *conf_eighty = conf_itvl(all_nines, 5, 0.8);
  double *conf_hundred = conf_itvl(all_nines, 5, 1.0);
  double *conf_point_1 = conf_itvl(all_nines, 5, 0.1);
  ck_assert(*conf_eighty == 9.0);
  ck_assert(*(conf_eighty + 1) == 9.0);
  ck_assert(*conf_hundred == 9.0);
  ck_assert(*(conf_hundred + 1) == 9.0);
  ck_assert(*conf_point_1 == 9.0);
  ck_assert(*(conf_point_1 + 1) == 9.0);
}
END_TEST

START_TEST(test_conf_itvl_negative){
  double all_negative[6] = {-4.0, -3.0, -2.0, -2.0, -1.0, -1.0};
  double *conf_fifty = conf_itvl(all_negative, 6, 0.5);
  double *conf_hundred = conf_itvl(all_negative, 6, 1.0);
  ck_assert(*conf_fifty < 0.0);
  ck_assert(*(conf_fifty + 1) == -1.0);
  ck_assert(*conf_hundred == -4);
  ck_assert(*(conf_hundred + 1) == -1.0);
}
