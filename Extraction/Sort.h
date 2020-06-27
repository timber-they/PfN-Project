#ifndef SORT_H
#define SORT_H

int comp_int(const void *a, const void *b);

int comp_double(const void *va, const void *vb);

void sort_int(int *array, size_t n_elems);

void sort_double(double *array, size_t n_elems);
#endif
