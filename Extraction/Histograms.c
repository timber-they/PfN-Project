#include <stdlib.h>
#include <stdio.h>
#define NUM_COMMANDS 8

int main()
{
    int i;
    char * commandsForGnuplot[] = {"set title \"Distribution\"", "set xlabel \"x\"",
        "set ylabel \"Probability\"", "set xrange [-0.1:1.1]", "set size square",
        "set boxwidth 0.85 relative", "set style fill solid 1.0",
        "plot \"data.dat\"  w boxes"};
    /*
    Opens an interface that one can use to send commands as if they were typing into the
    gnuplot command line.  "The -persistent" keeps the plot open even after your
    C program terminates.
    */
    FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");

    for (i=0; i < NUM_COMMANDS; i++)
    {
    fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); // Send commands to gnuplot one by one.
    }
    return 0;
}
