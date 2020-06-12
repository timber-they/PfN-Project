#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "Histograms.h"

//the maximum lenth for the filname of the sources is 32 characters
int paintHistogram(char *source)
{
    int i, numCommands = 8;
    char plotCommand[50];
    if (strlen(source) > 32)
    {
        // filename is too long
        fprintf(stderr, "Histograms: name of source file ist too long (max 32 characters)\n");
        return 1;
    }
    if (access(source, F_OK) == -1 )
    {
        // file doesn't exist
        fprintf(stderr, "Histograms: invalid name of source for histograms function, or source doesnt exist.\n");
        return 1;
    }
    strcpy(plotCommand, "plot \"");
    strcat(plotCommand, source);
    strcat(plotCommand, "\" w boxes");
    char * commandsForGnuplot[] = {"set title \"Distribution\"", "set xlabel \"x\"",
        "set ylabel \"Probability\"", "set xrange [-0.1:1.1]", "set size square",
        "set boxwidth 0.85 relative", "set style fill solid 1.0",
        plotCommand};
    /*
    Opens an interface that one can use to send commands as if they were typing into the
    gnuplot command line.  "The -persistent" keeps the plot open even after your
    C program terminates.
    */
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
    if (gnuplotPipe == NULL)
    {
        fprintf(stderr, "Histograms: Unable to create gnuplot pipe to paint histogram\n");
        return 1;
    }
    for (i=0; i < numCommands; i++)
    {
        // Send commands to gnuplot one by one.
        fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]);
    }
    return 0;
}
