#include <stdlib.h>
#include <stdio.h>

#define PARAMETERS "0.4 1000000 10000"
#define PROPABILITY 0.4
#define SAMPLESIZE 10000


START_TEST(test_sampling)
{
    FILE *resultFile = NULL;
    const char *resultFileName = "../Sampling/sampleResult.txt";
    int return_code;
    // maximum of 10 chars
    char *resultChar = malloc(sizeof(char) * 10);
    int result = -1;
    
    return_code = system("cd .. && cd Sampling && make && ./Program.x "PARAMETERS);

    if (return_code != 0)
    {
        ck_abort_msg("Running the program failed with %d", return_code);
    }
    
    resultFile = fopen(resultFileName, "r");
    if(resultFile == NULL)
    {
        ck_abort_msg("Could not open file");
    }
    else
    {
        if (fgets(resultChar, 10, resultFile) == NULL)
        {
            ck_abort_msg("Reading from the file failed");
        }
        result = atoi(resultChar);
    }
    
    // Check for interval +- 10 around the expected value %
    ck_assert(result > (int) (SAMPLESIZE * (PROPABILITY - 0.1)));
    ck_assert(result < (int) (SAMPLESIZE * (PROPABILITY + 0.1)));
    free(resultChar);
}
END_TEST
