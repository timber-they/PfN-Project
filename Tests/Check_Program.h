#include <stdlib.h>
#include <stdio.h>

#define PARAMETERS "0.4 1000000 10000"
#define PROPABILITY 0.4
#define SAMPLESIZE 10000


START_TEST(test_program)
{
    FILE *resultFile = NULL;
    const char *resultFileName = "../Sampling/sampleResult.txt";
    // maximum of 10 chars
    char *resultChar = malloc(sizeof(char) * 10);
    int result = -1;
    
    system("cd .. && cd Sampling && make && ./Program.x "PARAMETERS);
    
    resultFile = fopen(resultFileName, "r");
    if(resultFile == NULL)
    {
        fprintf(stderr, "Could not open file");
    }
    else
    {
        fgets(resultChar, 10, resultFile);
        result = atoi(resultChar);
    }
    
    // Check for interval +- 10 around the expected value %
    ck_assert(result > (int) (SAMPLESIZE * (PROPABILITY - 0.1)));
    ck_assert(result < (int) (SAMPLESIZE * (PROPABILITY + 0.1)));
    free(resultChar);
}
END_TEST
