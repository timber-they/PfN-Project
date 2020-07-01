#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "Histograms.h"

//the maximum lenth for the filname of the sources is 32 characters
int paintHistogram(char *source, double *confidence_intervall, double median, double medium)
{
    int bla = confidence_intervall[0];
    bla++;
    int i, numCommands = 11;
    char plotCommand[50], medianCommand[50], mediumCommand[50],
    arrowCommand[100], confidenceCommand[100];
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
    strcpy(medianCommand, "set label \"median = ");
    sprintf(medianCommand + 20, "%.3f", median);
    strcat(medianCommand, "\" at graph 0.03,0.9");
    strcpy(mediumCommand, "set label \"medium = ");
    sprintf(mediumCommand + 20, "%.3f", medium);
    strcat(mediumCommand, "\" at graph 0.03,0.87");
    strcpy(arrowCommand, "set arrow 1 from ");
    sprintf(arrowCommand + 17, "%.3f", confidence_intervall[0]);
    strcat(arrowCommand, ", graph 0.5 to ");
    sprintf(arrowCommand + 37, "%.3f", confidence_intervall[1]);
    strcat(arrowCommand, ", graph 0.5 heads front");
    strcpy(confidenceCommand, "set label \"confidence intervall from ");
    sprintf(confidenceCommand + 37 , "%.3f", confidence_intervall[0]);
    strcat(confidenceCommand, " to ");
    sprintf(confidenceCommand + 46 , "%.3f", confidence_intervall[1]);
    strcat(confidenceCommand, "\" at ");
    sprintf(confidenceCommand + 56 , "%.3f", confidence_intervall[0]);
    strcat(confidenceCommand, ", graph 0.53 front");
    printf("%s", confidenceCommand);
    strcpy(plotCommand, "plot \"");
    strcat(plotCommand, source);
    strcat(plotCommand, "\" w boxes lt rgb \"green\"");
    char * commandsForGnuplot[] = {"set title \"Distribution\"",
        "set xlabel \"population\"",
        "set ylabel \"Probability\"", "set size square",
        "set boxwidth 0.85 relative", "set style fill solid 1.0",
        medianCommand, mediumCommand, arrowCommand, confidenceCommand,
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
