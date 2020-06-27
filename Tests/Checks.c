#include <check.h>
#include "Check_Lazy_Sampling.h"
#include "Check_Histograms.h"
#include "Check_Random.h"
#include "Check_correction.h"
#include "Check_Basic_Sampling.h"
#include "Check_Median.h"
#include "Check_Medium.h"
#include "Check_ConfidenceIntervals.h"
#include "Check_AbsoluteData.h"
#include "Check_RelativeData.h"
#include "Check_Sampling.h"

int main (void)
{
    Suite *s1 = suite_create("Sampling");
    Suite *s2 = suite_create("Extraction");
    TCase *tc1_1 = tcase_create("Unit tests");
    TCase *tc2_1 = tcase_create("Unit tests");
    TCase *tc1_2 = tcase_create("Integration tests");
    TCase *tc2_2 = tcase_create("Integration tests");
    SRunner *sr = srunner_create(s1);
    srunner_add_suite(sr, s2);
    int nf;

    suite_add_tcase(s1, tc1_1);
    suite_add_tcase(s2, tc2_1);
    suite_add_tcase(s1, tc1_2);
    suite_add_tcase(s2, tc2_2);

    tcase_add_test(tc1_1, test_create_source_non_empty);
    tcase_add_test(tc1_1, test_take_well_distributed);
    tcase_add_test(tc1_1, test_random);
    tcase_add_test(tc1_1, test_correction);
    tcase_add_test(tc1_1, test_basic_sampling);
    tcase_add_test(tc1_2, test_sampling);
    tcase_add_test(tc2_1, test_painting_errors);
    tcase_add_test(tc2_1, test_median_sorted);
    tcase_add_test(tc2_1, test_medium);
    tcase_add_test(tc2_1, test_conf_itvl_same_values);
    tcase_add_test(tc2_1, test_array_max_value);
    tcase_add_test(tc2_1, test_absolute_frequencies_positive);
    tcase_add_test(tc2_1, test_bucket_indices_pos);
    tcase_add_test(tc2_1, test_percentage_of_trials);

    srunner_run_all(sr, CK_NORMAL);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
