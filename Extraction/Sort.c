#include <math.h>
#include <stdlib.h>

#include "Sort.h"

int comp_int(const void *a, const void *b)
{
    return *((int *)a) - *((int *)b);
}

int comp_double(const void *va, const void *vb) {
  const double a = *(const double *)va, b = *(const double *)vb;

  if (fabs(a - b) < 1.0e-16) {
    return 0;
  }
  return a > b;
}
void sort_int(int *array, size_t n_elems) {
    qsort(array, n_elems, sizeof *array, comp_int);
}

void sort_double(double *array, size_t n_elems) {
    qsort(array, n_elems, sizeof *array, comp_double);
}
