#include "../Sampling/Basic_Sampling.h"

START_TEST(test_basic_sampling)
{
    int posArr, posLazy;
    posLazy = getPositives(1000, 0.5, 101);
    bool *sampleArray = getSampleArray(1000, 0.5, 101);
    posArr = 0;
    for (int i = 0; i < 1000; i++) {
        if(!*(sampleArray + i)) {
            posArr++;
        }
    }
    ck_assert_int_eq(posArr, posLazy);
}
