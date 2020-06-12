#include "../Sampling/double_with_error.h"
#include "../Sampling/correction.h"
#include <stdlib.h>

START_TEST(test_correction)
{
    double_with_error f1, f2;
    f1->d = 0.9;
    f1->err = EXIT_SUCCESS;
    f2->d = 0.1;
    f2->err = EXIT_SUCCESS;
    f1 = correction(f1);
    f2 = correction(f2);
    double diff1 = f1->d - 0.99, diff2 = f2->d - 0.10111111;
    if (diff1 < 0)
        diff1 = -diff1;
    if (diff2 < 0)
        diff2 = -diff2;
    ck_assert(diff1 < 0.0000001);
    ck_assert(diff2 < 0.0000001);
}
END_TEST
