#include <stdlib.h>
#include <stdio.h>

#include "Medium.h"

double get_medium(double* sample, size_t n_elems)
{
    unsigned int i, sum=0;
    double medium;

    for(i=0; i<n_elems; i++)
    {
        sum+=sample[i];
    }
    medium = (double) sum/n_elems;

    return medium;
}

