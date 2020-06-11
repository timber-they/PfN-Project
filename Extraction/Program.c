#include <stdlib.h>
#include "CSV_Output.h"
#include "ConfidenceIntervals.h"
#include "Histograms.h"
#include "Median.h"
#include "Medium.h"
#define CONFIDENCE_LEVEL 0.95

/* Input an array of trial results, which contains the number of infected
 * people given by the sampling, the length of the array and the size of the
 * sampled population.
 * Returns some extracted statistics.
 */
int main(int argc, char *argv[])
{
    unsigned int *trial results, population_size, data_median,
                 *confidence_interval;
    size_t number_of_trials;
    double data_medium, *relative_results, **diagram_data;
    
    /* diagram data: array of 2-arrays containing diagram point {x,y}
     * x-axis: n_infected (= trial_results)
     * y-axis: n_simulations (n_infected) / N_simulations
     */
    
    // TODO check file for format failures
    // TODO read trial_results from file
    
    data_median = median_sort(trial_results, number_of_trials);
    data_medium = medium(trial_results, number_of_trials);
    confidence_interval = conf_itvl (trial_results, number_of_trials,
                                     CONFIDENCE_LEVEL);

    for (int i = 0; i < number_of_trials; i++)
    {
        relative_results[i] = (double) trial_results[i] / population_size;
    }
    
    // TODO accumulate histogram intervals?
    // TODO write data into gnuplot-readable (csv) file
    // TODO paint gnuplot data
    
    return EXIT_SUCCESS;
}

