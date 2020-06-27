#include "../Sampling/Lazy_Sampling.h"

START_TEST(test_create_source_non_empty)
{
    LazySource *source = getLazySource(100, 0.5);
    ck_assert_int_gt(countPositives(source), 0);
    ck_assert_int_gt(countNegatives(source), 0);
    source = getLazySource(100, 0.1);
    ck_assert_int_gt(countPositives(source), 0);
    ck_assert_int_gt(countNegatives(source), 0);
    source = getLazySource(100, 0.9);
    ck_assert_int_gt(countPositives(source), 0);
    ck_assert_int_gt(countNegatives(source), 0);
}
END_TEST

// Please note that it's possible (but improbable) that this test fails,
// even though the behaviour is correct
START_TEST(test_take_well_distributed)
{
    int positives = 0;
    int negatives = 0;
    LazySource *source = getLazySource(1000, 0.5);

    for (int i = 0; i < 500; i++)
    {
        if (takeElement(source))
            positives++;
        else
            negatives++;
    }

    ck_assert_int_ge(positives, 100);
    ck_assert_int_ge(negatives, 100);
}
END_TEST

// TODO: Test reset functionality

