#include "../Extraction/Medium.h"

START_TEST(test_medium)
{
    double sample[] = {1,2,3};
    size_t len = sizeof(sample) / sizeof(double);
    ck_assert(medium(sample,len)==2.0);
    sample[0] = 2;
    sample[1] = 1;
    sample[2] = 3;
    ck_assert(medium(sample,len)==2.0);
}
END_TEST
