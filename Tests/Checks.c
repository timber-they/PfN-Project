#include <check.h>
#include "Check_Lazy_Sampling.h"
#include "Check_Medium.h"

int main (void)
{
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, test_create_source_non_empty);
    tcase_add_test(tc1_1, test_take_well_distributed);
    tcase_add_test(tc1_1, test_medium);

    srunner_run_all(sr, CK_NORMAL);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
