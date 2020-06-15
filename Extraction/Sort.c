#include <stdlib.h>

#include "Sort.h"

int comp_int(const void *a, const void *b)
{
    return *((int *)a) - *((int *)b);
}

void sort_int(int *array, size_t n_elems) {
    qsort(array, n_elems, sizeof *array, comp_int);
}
