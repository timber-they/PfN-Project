#include "../Extraction/Histograms.h"

START_TEST(test_painting_errors)
{
    int try1 = paintHistogram("da ta.dat");
    ck_assert_int_eq(try1, 1);
    int try2 = paintHistogram("nobodywouldcallafilelikethisbecauseitsnameiswaytoolongandthisisridiculous");
    ck_assert_int_eq(try2, 1);
}
END_TEST
