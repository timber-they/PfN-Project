#include <stdlib.h>
#include <stdio.h>

//static int compareFiles(FILE *file1, FILE *file2)
static int compareFiles(const char* f1, const char *f2)
{
    FILE *file1 = fopen(f1, "r"); 
    FILE *file2 = fopen(f2, "r"); 

    if (file1 == NULL || file2 == NULL) 
    { 
        ck_abort_msg("Could not open file(s)");
    }

    char ch1 = getc(file1);
    char ch2 = getc(file2);

    while (ch1 != EOF && ch2 != EOF)
    {
       if (ch1 != ch2)
       {
          return 1;
       }
       ch1 = getc(file1);
       ch2 = getc(file2);
    }
    return 0;
}

static void run_program(const char* program_call)
{
    int return_code;
    return_code = system(program_call);

    if (return_code != 0)
    {
        ck_abort_msg("Running the program failed with %d", return_code);
    }
}

START_TEST(test_extraction)
{
    if (system("cd ../Extraction && make clean && make") != 0 )
    {
        ck_abort_msg("Extraction: Compilation failed.");
    }

    run_program(
        "../Extraction/Program.x test_data/test_sample1.tsv 10 82000000 0.95");
    ck_assert(compareFiles("test_data/test_results1.csv","results.csv") == 0);

    run_program(
        "../Extraction/Program.x test_data/test_sample2.tsv 10 82000000 0.95");
    ck_assert(compareFiles("test_data/test_results2.csv","results.csv") == 0);

    run_program(
        "../Extraction/Program.x test_data/test_sample3.tsv 10 82000000 0.95");
    ck_assert(compareFiles("test_data/test_results3.csv","results.csv") == 0);
}
END_TEST
