#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "Histograms.h"

int labelCommand(char *command, int idx, const char *name, int name_length,
                 int value, int value_length)
{
    double ypos = (double) 0.9 - 0.03 * idx;
    strcpy(command, "set label \"");
    strcat(command, name);
    strcat(command, " = ");
    sprintf(command + 14 + name_length, "%d", value);
    strcat(command, "\" at graph 0.03,");
    sprintf(command + 30 + name_length + value_length, "%.3f", ypos);
    return 0;
}

int labelCommandDbl(char *command, int idx, const char *name,
                    int name_length, double value)
{
    double ypos = (double) 0.9 - 0.03 * idx;
    strcpy(command, "set label \"");
    strcat(command, name);
    strcat(command, " = ");
    sprintf(command + 14 + name_length, "%.3f", value);
    strcat(command, "\" at graph 0.03,");
    sprintf(command + 35 + name_length, "%.3f", ypos);
    return 0;
}

int coloredLabelCommand(char *command, int idx, const char *name,
                        int name_length, double value, const char *color)
{
    labelCommandDbl(command, idx, name, name_length, value);
    strcat(command, " textcolor rgb \"");
    strcat(command, color);
    strcat(command, "\"");
    return 0;
}

//the maximum lenth for the filname of the sources is 32 characters
int paintHistogram(char *source, double *confidence_intervall,
                   double median, double medium, double confidence_level,
                   int population_size, int number_of_trials)
{
    int i, numCommands = 18;
    char populationCommand[100], trialsCommand[100],
    medianCommand[100], medianCommand2[100],
    mediumCommand[100], mediumCommand2[100],
    arrowCommand[100], confidenceCommand[100], confidenceCommand2[100],
    plotCommand[50];
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
    labelCommand(populationCommand, 0, "population", 10, population_size,
                 floor(log10(abs(population_size))) + 1);
    labelCommand(trialsCommand, 1, "trials", 6, number_of_trials,
                 floor(log10(abs(number_of_trials))) + 1);
    coloredLabelCommand(medianCommand, 3, "median", 6, median, "red");
    coloredLabelCommand(mediumCommand, 4, "medium", 6, medium, "blue");
    labelCommandDbl(confidenceCommand, 5, "confidence level", 16, confidence_level);
    strcpy(arrowCommand, "set arrow 1 from ");
    sprintf(arrowCommand + 17, "%.3f", confidence_intervall[0]);
    strcat(arrowCommand, ", graph 0.5 to ");
    sprintf(arrowCommand + 37, "%.3f", confidence_intervall[1]);
    strcat(arrowCommand, ", graph 0.5 heads front");
    strcpy(confidenceCommand2, "set label \"confidence intervall from ");
    sprintf(confidenceCommand2 + 37 , "%.3f", confidence_intervall[0]);
    strcat(confidenceCommand2, " to ");
    sprintf(confidenceCommand2 + 46 , "%.3f", confidence_intervall[1]);
    strcat(confidenceCommand2, " (");
    sprintf(confidenceCommand2 + 53 , "%2.0f", confidence_level * 100);
    strcat(confidenceCommand2, "%)\" at ");
    sprintf(confidenceCommand2 + 62 , "%.3f", confidence_intervall[0]);
    strcat(confidenceCommand2, ", graph 0.53 front");
    strcpy(medianCommand2, "set arrow 3 from first ");
    sprintf(medianCommand2 + 23, "%.3f", median);
    strcat(medianCommand2, ", graph 0.0 to first ");
    sprintf(medianCommand2 + 49, "%.3f", median);
    strcat(medianCommand2, ", graph 0.4 nohead front lc \"red\"");
    strcpy(mediumCommand2, "set arrow 2 from first ");
    sprintf(mediumCommand2 + 23, "%.3f", medium);
    strcat(mediumCommand2, ", graph 0.0 to first ");
    sprintf(mediumCommand2 + 49, "%.3f", medium);
    strcat(mediumCommand2, ", graph 0.4 nohead front lc \"blue\"");
    printf("%s", medianCommand2);
    strcpy(plotCommand, "plot \"");
    strcat(plotCommand, source);
    strcat(plotCommand, "\" w boxes lt rgb \"green\"");
    char * commandsForGnuplot[] = {"set title \"Distribution\"",
        "set xlabel \"population\"",
        "set ylabel \"Probability\"", "set size square",
        "set boxwidth 0.85 relative", "set style fill solid 1.0",
        populationCommand, trialsCommand,
        medianCommand, medianCommand2, mediumCommand, mediumCommand2,
        arrowCommand, confidenceCommand, confidenceCommand2,
        plotCommand,
        "set terminal png size 800,800; set output \"Histogram.png\"",
        "replot"};
    
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
