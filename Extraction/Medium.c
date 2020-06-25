#include <stdlib.h>
#include <stdio.h>

#include "Medium.h"

double get_medium(double* sample, size_t n_elems)
{
    unsigned int i;
    double medium, sum=0;

    for(i=0; i<n_elems; i++)
    {
        sum+=sample[i];
    }
    medium = (double) sum/n_elems;

    return medium;
}

