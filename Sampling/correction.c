#include <stdio.h>
#include <stdlib.h>
#include "correction.h"

// applies correction to lessen bias
double correction(double f, double sensitivity, double specificity)
{
    // input: f = n_measured / n_subjects --> 0 <= f <= 1
    if ((f <= 1) && (f >= 0))
    {
        f = (f + specificity - 1) / (specificity + sensitivity - 1);
        return f;
    }
    else
    {
        fprintf(stderr, "correction: input f has to obey 0 <= f <= 1\n");
        return f;
    }
}
