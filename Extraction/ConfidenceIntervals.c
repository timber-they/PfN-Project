/* Code by Julius Bittner 2020
 * Use under CC-BY-SA 4.0
 * Part of PfN-Project 2020
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ConfidenceIntervals.h"

// gaussConf: calculate confidence interval of some data with given standard deviation, number of values and level assuming gauss distribution
// give: standard deviation
// give: number of values as unsigned int
// give: confidence level to use. Choose from 0.8, 0.85, 0.9, 0.95, 0.99, 0.995, 0.999
// return: confidence as deviation from medium, to the upside as well as to the downside!
double gaussConf(double standDev, unsigned int numOfVals, float level)
{
    float Z;
    unsigned int Level = level * 1000;
    //printf("%i\n", Level);
    switch (Level) {
	    case 800: Z = 1.282; break;
	    case 850: Z = 1.440; break;
	    case 900: Z = 1.645; break;
	    case 950: Z = 1.960; break;
            case 990: Z = 2.576; break;
            case 995: Z = 2.807; break;
	    case 999: Z = 3.291; break;
	    default:
		printf("Please choose level of confidence from 0.8, 0.85, 0.9, 0.95, 0.99, 0.995, 0.999");
		return EXIT_FAILURE;
    }

    double s = sqrt(numOfVals);
    double c = Z * standDev / s;
    return c;
}

// conf_itvl: calculate confidence interval of given data with given level
// give: data as sorted array of doubles
// give: desired confidence level in (0.0, 1.0]
// return: 2-array with minimum and maximum of confidence interval
double * conf_itvl(double *sorted, size_t n_elems, float level)
{
	if (n_elems == 0)
	{
		fprintf(stderr, "Please input array of at least length 1");
	}
	if (level <= 0 || level > 1)
	{
		fprintf(stderr, "Please input level greater than 0 and 1 at maximum");
	}

	static double intervals[2];
	int min, max;
	max = (int) ((0.5 + level / 2) * n_elems - 1);
	min = (int) ((0.5 - level / 2) * n_elems);

	intervals[0] = sorted[min];
	intervals[1] = sorted[max];

	return intervals;
}

int main()
{
	double vals[] = { 1, 4, 4, 5, 9, 10, 11, 11, 12, 14, 14, 17, 18, 19, 21, 25, 25, 25, 30, 31, 38, 40, 45, 49, 90 };
	size_t size = sizeof vals/sizeof vals[0];
	float level = 0.8;

	double* c;
	c = conf_itvl(vals, size, level);

	printf("%f of %li values lies in [%f, %f]\n", level, size, c[0], c[1]);
}
