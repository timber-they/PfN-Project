#include "../Sampling/correction.h"
#include <stdlib.h>
START_TEST(test_correction)
{
  double f1 = correction(0.9);
  ck_assert(abs(f1 - 0.99) < 0.000001);
  double diff = f1 - 0.99;
  if (diff < 0)
      diff = -diff;
  ck_assert(diff < 0.0000001);
}
END_TEST
