#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int getRandomNumbers(unsigned int n)
{
    int i = 0;
    
    srand48(time(NULL)); //Seed Generation based on system Time
    while(i < n) //printing out some values
    {
        printf("%f\n",drand48());
        i++;
    }
    return(EXIT_SUCCESS);
}

double getRandomNumber() {
    srand48(time(NULL)); //Seed Generation based on system Time
    return drand48();
}
