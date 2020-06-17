#include <stdlib.h>
#include <stdio.h>

#define PARAMETERS " 0.3 1000000 1 10000"
#define SAMPLESIZE 10000


START_TEST(test_sampling)
{
    FILE *resultFile = NULL;
    const char *resultFileName = "../Sampling/sampleResult.tsv";
    int return_code;
    // maximum of 20 chars
    char *resultChar = malloc(sizeof(char) * 20);
    char *seperator = "\t";
    int result = -1;
    char *sizeptr;
    
    return_code = system("cd .. && cd Sampling && make && ./Program.x"PARAMETERS);

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
        if (fgets(resultChar, 20, resultFile) == NULL)
        {
            ck_abort_msg("Reading from the file failed");
        }
        sizeptr = strtok(resultChar, seperator);
        sizeptr = strtok(NULL, seperator);
        result = atoi(sizeptr);
    }
    
    // Check for interval +- 10 around the expected value %
    ck_assert(result > (int) (SAMPLESIZE * 0.212));
    ck_assert(result < (int) (SAMPLESIZE * 0.434));
    free(resultChar);
}
END_TEST
