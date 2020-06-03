#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

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
    printf("Lazy: %u von %u positiv\n", pos, size);
    return pos;
}

void testBasicSampling(int size, double prob, int seed) {
    int posArr, posLazy;
    posLazy = getPositives(size, prob, seed);
    bool *sampleArray = getSampleArray(size, prob, seed);
    posArr = 0;
    for (int i = 0; i < size; i++) {
        if(!*(sampleArray + i)) {
            posArr++;
        }
    }
    printf("Array: %u von %u positiv\n", posArr, size);
    assert(posArr == posLazy);
}

int main(int argc, char *argv[])
{
    int sample_size = 1000;
    double probability = 0.5;
    int seed = 101;
    //getPositives(sample_size, probability, seed);
    testBasicSampling(sample_size, probability, seed);
}

