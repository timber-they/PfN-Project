#include "../Sampling/random.h"
 
START_TEST(test_random)
{
    int seed = 100;
	float test1 = getRandomNumber(seed);
	float test2 = getRandomNumber(seed);
	ck_assert_uint_eq(test1, test2);
}
END_TEST
