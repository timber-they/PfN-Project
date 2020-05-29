#include "Lazy_Sampling.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    int size;
    double probability;
    switch (argc)
    {
       case 1:
           size = 100;
           probability = 0.5;
           break;
       case 3:
           if (sscanf(argv[1], "%d", &size) == 1 &&
                   sscanf(argv[2], "%lf", &probability) == 1)
           {
               break;
           }
           fprintf(stderr, "Couldn't parse entries %s %s\n", argv[1], argv[2]);
           return 1;
       default:
           fprintf(stderr, "Invalid entry\n");
           return 1;
    }

    LazySource source = getLazySource(size, probability);
    for (int i = 0; i < size; i++)
    {
        printf("Pick %d got %d\n", i, takeElement(&source));
    }

    return 0;
}

