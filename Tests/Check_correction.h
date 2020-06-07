#include "../Sampling/correction.h"

START_TEST(test_correction)
{
  double f1 = correction(0.9);
  ck_assert_double_eq(f1, 0.99);
}
END_TEST
