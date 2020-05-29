#include <check.h>
#include "../Sampling/Lazy_Sampling.h"

START_TEST(test_create_source)
{
    LazySource source = getLazySource(100, 0.5);
    ck_assert_int_gt(source.Positives, 0);
    ck_assert_int_gt(source.Negatives, 0);
}

int main (void)
{
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, test_create_source);

    srunner_run_all(sr, CK_NORMAL);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
