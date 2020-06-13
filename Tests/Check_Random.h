#include "../Sampling/Random.h"
 
START_TEST(test_random)
{
    int seed = 100;
	initRandom(seed);
	float test1 = getRandomNumber();
	initRandom(seed);
	float test2 = getRandomNumber();
	ck_assert(test1 == test2);
}
END_TEST
