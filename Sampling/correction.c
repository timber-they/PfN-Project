#include <stdio.h>
#include <stdlib.h>

// applies correction to lessen bias
double correction(double f)
{
    // input: f = n_measured / n_subjects --> 0 <= f <= 1
    if ((f <= 1) && (f >= 0))
    {
        f = (f + SPECIFICITY - 1) / (SPECIFICITY + SENSITIVITY - 1);
        return f;
    }
    else
    {
        fprintf(stderr, "correction: input f has to obey 0 <= f <= 1\n");
        return f;
    }
}
