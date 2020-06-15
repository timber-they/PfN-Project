#include <stdio.h>

#include "Median.h"

int comp_int(const void *a, const void *b)
{
  return *((int*) a) - *((int*) b);
}

/*
the median is the middle element of a sorted array.
If the length is even, the average of the 2 middle elements is taken.
*/
double get_median(int *sorted, size_t n_elems)
{
    if (n_elems == 0)
    {
        fprintf(stderr, "Please input an array of at least length 1");
    }
    if (n_elems % 2 == 0)
    {
      return ((double) sorted[(n_elems -1)/ 2] + (double) sorted[n_elems / 2]) / 2;
    }
    else
    {
        return sorted[n_elems / 2];
    }
}
