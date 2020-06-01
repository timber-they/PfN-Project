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

int main(void)
{
    double sample[] = {1,2,3,4,5,6,7,8,9,10,11};
    size_t len = sizeof(sample) / sizeof(double);
    double avg = medium(sample,len);
    printf("avg: %lf\n",avg);

    return EXIT_SUCCESS;
}
