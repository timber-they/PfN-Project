#include "../Extraction/Medium.h"

START_TEST(test_medium)
{
    int i,j;
    unsigned int sample[] = {1,2,3,4,5}, temp;
    double med = 3.0;
    size_t len = sizeof(sample) / sizeof(sample[0]);

    for(i = 0; i<len; i++)
    {
        temp = sample[len-1];
        for (j = len-1; j > 0; j--)
        {
            sample[j] = sample[j-1];
        }
        sample[0]=temp;
        ck_assert(get_medium(sample,len)==med);
    }
}
END_TEST
