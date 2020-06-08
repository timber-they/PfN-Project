#include "../Sampling/correction.h"
#include <stdlib.h>

START_TEST(test_correction)
{
  double f1 = correction(0.9);
  ck_assert(abs(f1 - 0.99) < 0.000001);
}
END_TEST
