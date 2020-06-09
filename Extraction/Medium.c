#include <stdlib.h>
#include <stdio.h>

double medium(double* sample, size_t n_elems)
{
    int i;
    double sum=0, medium;

    for(i=0; i<n_elems; i++)
    {
        sum+=sample[i];
    }
    medium = sum/n_elems;

    return medium;
}

