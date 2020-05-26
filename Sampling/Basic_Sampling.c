#include <stdio.h>
#include <stdbool.h>
#include "random.h"

int sample_size = 1000;
double probability = 0.5;

bool *getSampleArray(int size, int prob) {
    bool *arr = malloc(size * sizeof(bool));
    double rand;
    for (int i = 0; i < size; i++) {
        rand = getRandomNumber();
        if(rand < prob) {
            *(arr+i) = true;
        }
    }
    return arr;
}

int getPositives(int size, int prob) {
    int pos = 0;
    double rand;
    for (int i = 0; i < size; i++) {
        rand = getRandomNumber();
        printf("%f\n",rand);
        if(rand < prob) {
            pos++;
        }
    }
    printf("%u von %u positiv", pos, sample_size);
    return pos;
}

int main(int argc, char *argv[])
{
    getPositives(sample_size, probability);
}

