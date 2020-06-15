#include <check.h>
#include "Check_Lazy_Sampling.h"
#include "Check_Histograms.h"
#include "Check_Random.h"
#include "Check_correction.h"
#include "Check_Basic_Sampling.h"
#include "Check_Median.h"
#include "Check_Medium.h"
#include "Check_ConfidenceIntervals.h"
#include "Check_Program.h"

int main (void)
{
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, test_create_source_non_empty);
  tcase_add_test(tc1_1, test_take_well_distributed);
  tcase_add_test(tc1_1, test_painting_errors);
  tcase_add_test(tc1_1, test_random);
  tcase_add_test(tc1_1, test_correction);
  tcase_add_test(tc1_1, test_basic_sampling);
  tcase_add_test(tc1_1, test_median_sorted);
  tcase_add_test(tc1_1, test_medium);
  tcase_add_test(tc1_1, test_conf_itvl_same_values);
  tcase_add_test(tc1_1, test_conf_itvl_negative);
  tcase_add_test(tc1_1, test_program);

  srunner_run_all(sr, CK_NORMAL);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
