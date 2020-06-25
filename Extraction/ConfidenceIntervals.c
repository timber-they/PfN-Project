/* Code by Julius Bittner 2020
 * Use under CC-BY-SA 4.0
 * Part of PfN-Project 2020
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "ConfidenceIntervals.h"

// conf_itvl: calculate confidence interval of given data with given level
// give: data as sorted array of doubles
// give: desired confidence level in (0.0, 1.0]
// return: 2-array with minimum and maximum of confidence interval
double *conf_itvl(double *sorted, size_t n_elems, float level)
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
	unsigned int min, max;
	max = (unsigned int) ((0.5 + level / 2) * n_elems - 1);
	min = (unsigned int) ((0.5 - level / 2) * n_elems);

	intervals[0] = sorted[min];
	intervals[1] = sorted[max];

	return intervals;
}

/* int main() */
/* { */
/* 	double vals[] = { 1, 4, 4, 5, 9, 10, 11, 11, 12, 14, 14, 17, 18, 19, 21, 25, 25, 25, 30, 31, 38, 40, 45, 49, 90 }; */
/* 	size_t size = sizeof vals/sizeof vals[0]; */
/* 	float level = 0.8; */

/* 	double* c; */
/* 	c = conf_itvl(vals, size, level); */

/* 	printf("%f of %li values lies in [%f, %f]\n", level, size, c[0], c[1]); */
/* } */
