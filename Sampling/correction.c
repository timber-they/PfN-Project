#include <stdio.h>
#include <stdlib.h>
#include "double_with_error.h"

#define SPECIFICITY 0.991
#define SENSITIVITY 0.909

// applies correction to lessen bias
double_with_error correction(double_with_error f)
{
    double_with_error new_f;
    // input: f->d = n_measured / n_subjects --> 0 <= f->d <= 1
    if ((f->err == EXIT_SUCCESS) && (f->d <= 1) && (f->d >= 0))
    {
        new_f->d = (f->d + SPECIFICITY - 1) / (SPECIFICITY + SENSITIVITY - 1);
        new_f->err = EXIT_SUCCESS;
        return new_f;
    }
    else
    {
        // In case of an error f stays undisturbed, but the error-flag is set
        if (f->err == EXIT_SUCCESS)
        {
            fprintf(stderr, "correction: input f has to obey 0 <= f->d <= 1\n");
        }
        else
        {
            fprintf(stderr, "correction: input f had errorflag set\n");
        }
        new_f->d = f->d;
        new_f->err = EXIT_FAILURE;
        return new_f;
    }
}
