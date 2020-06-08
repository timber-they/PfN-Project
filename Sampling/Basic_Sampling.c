#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* retunrs an array with random booleans */
bool *getSampleArray(int size, double prob, int seed) {
    bool *arr = malloc(size * sizeof(bool));
    srand48(seed);
    for (int i = 0; i < size; i++) {
        if(drand48() < prob) {
            *(arr+i) = true;
        }
    }
    return arr;
}

/* returns the number of positives in a sample without using an array */
int getPositives(int size, double prob, int seed) {
    int pos = 0;
    double rand;
    srand48(seed);
    for (int i = 0; i < size; i++) {
        rand = drand48();
        if(rand > prob) {
            pos++;
        }
    }
    return pos;
}

