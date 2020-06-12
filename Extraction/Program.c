#include <stdlib.h>
#include <stdio.h>
#include "CSV_Output.h"
#include "ConfidenceIntervals.h"
#include "Histograms.h"
#include "Median.h"
#include "Medium.h"

/* Input a file name containing trial results data, int with number of trials
 * (should be number of lines of trial results file), int basic population size
 * and double confidence level.
 * Writes statistics into csv for gnuplot.
 */
int main(int argc, char *argv[])
{
    unsigned int *trial_results, population_size, data_median,
                 *confidence_interval;
    size_t number_of_trials;
    double data_medium, confidence_level, *relative_results, **diagram_data;
    
    /* diagram data: array of 2-arrays containing diagram point {x,y}
     * x-axis: n_infected (= trial_results)
     * y-axis: n_simulations (n_infected) / N_simulations
     */
    
    // TODO Julius check file for format failures
    // TODO Julius parse start parameters
    // TODO Julius read trial_results from file
    
    data_median = median_sort(trial_results, number_of_trials);
    data_medium = medium(trial_results, number_of_trials);
    confidence_interval = conf_itvl (trial_results, number_of_trials,
                                     CONFIDENCE_LEVEL);

    for (int i = 0; i < number_of_trials; i++)
    {
        relative_results[i] = (double) trial_results[i] / population_size;
    }
    
    // TODO Hannes count trial_results to get n_simulations > extract diagram data
    // TODO Hannes accumulate histogram intervals?
    // TODO Pascal write data into gnuplot-readable (csv) file
    
    // adjustment for imagined number_of_trials for first version (should be removed later)
    number_of_trials = 10;
    // Array containing x values (infected), should be filled with real data
    double *x = (double *) malloc (number_of_trials * sizeof(double));
    // Array containing y values (appearance of infected), should be filled with real data
    double *y = (double *) malloc (number_of_trials * sizeof(double));
    // imagined data, no meaning
    int i;
    for (i = 0; i < number_of_trials; i++)
    {
        x[i] = (double) i;
        y[i] = (double) 10/i;
    }
    // source data created
    FILE *source;
    source  = fopen ("data.dat", "w+");
    for (i = 0; i < number_of_trials; i++)
    {
        fprintf(source, "%lf %lf\n", x[i], y[i]);
    }
    fclose(source);
    createCSV("data.dat", "results.csv");
    
    // TODO Pascal paint gnuplot data
    
    paintHistogram("data.dat");
    remove("data.dat");
    
    return EXIT_SUCCESS;
}

