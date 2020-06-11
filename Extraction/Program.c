#include <stdlib.h>
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
    // TODO Pascal paint gnuplot data
    
    return EXIT_SUCCESS;
}

