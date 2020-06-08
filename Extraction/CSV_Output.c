#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "CSV_Output.h"

//the maximum lenth for the filnames (source and target) is 32 characters
int createCSV (char * sourceName, char * targetName)
{
    FILE *target, *source;
    double x, y;
    if (strlen(sourceName) > 32)
    {
        // filename is too long
        fprintf(stderr, "CSV Output: name of source file ist too long (max 32 characters)\n");
        return 1;
    }
    if (strlen(targetName) > 32)
    {
        // filename is too long
        fprintf(stderr, "CSV Output: name of target file ist too long (max 32 characters)\n");
        return 1;
    }
    if (access(sourceName, F_OK) == -1 )
    {
        // file doesn't exist
        fprintf(stderr, "CSV Output: invalid name of source for data, or source doesnt exist.\n");
        return 1;
    }
    source = fopen(sourceName, "r");
    if (source == NULL)
    {
        fprintf(stderr, "CSV Output: Unable to read source file\n");
        return 1;
    }
    target = fopen(targetName, "w+");
    if (target == NULL)
    {
        fprintf(stderr, "CSV Output: Unable to create CSV File to save data\n");
        return 1;
    }
    while (fscanf(source, "%lf %lf\n", &x, &y) != EOF)
    {
        fprintf(target,"%lf, %lf\n", x, y);
    }
    return 0;
}
