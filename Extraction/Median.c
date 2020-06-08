#include <stdlib.h>
/* This can overflow? */
int comp_double(const void *a, const void *b)
{
  return *((double*) a) - *((double*) b);
}

/*
the median is the middle element of a sorted array.
If the length is even, the average of the 2 middle elements is taken.
*/
double median_sort(double *array, size_t n_elems)
{
    if (n_elems == 0)
    {
        fprintf(stderr, "Please input an array of at least length 1");
    }
    qsort(array, n_elems, sizeof *array, comp_double);
    if (n_elems % 2 == 0)
    {
        return (array[(n_elems -1)/ 2] + array[n_elems / 2]) / 2;
    }
    else
    {
        return array[n_elems / 2];
    }
}
