#include "../Extraction/Histograms.h"

START_TEST(test_painting_errors)
{
    double conf[2];
    conf[0] = 0;
    conf[1] = 0;
    int try1 = paintHistogram("da ta.dat", conf, 0, 0, 0, 0, 0);
    ck_assert_int_eq(try1, 1);
    int try2 = paintHistogram("nobodywouldcallafilelikethisbecauseitsnameiswaytoolongandthisisridiculous", conf, 0, 0, 0, 0, 0);
    ck_assert_int_eq(try2, 1);
}
END_TEST
