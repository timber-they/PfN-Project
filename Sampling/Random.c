#include <stdlib.h>	
#include <stdio.h>	
#include <time.h>

float getRandomNumber()
{
    return(drand48());
}

void initRandom(int temp_seed)
{
    int seed;
	if(temp_seed > 0)
    {
    	seed = temp_seed;
    }
    else
    {
    	fprintf(stderr, "%s: The Seed has to be postive! \n",__FILE__);
    	exit(EXIT_FAILURE);
    }
    srand48(seed); // Seed Generation based on seed variable
}

// TODO: Unit test
int getWithProbability(float probability)
{
    return getRandomNumber() < probability;
}

/*
int main(int argc, char *argv[])
{
    int n;
    int seed = 0;
    if(argc > 4 || (sscanf(argv[1], "%u", &n)) != 1)	
      {	
          fprintf(stderr, "Not a valid Argument");	
          exit(EXIT_FAILURE);	
      }
    if(argc == 3)
    {
    	sscanf(argv[2], "%u", &seed);
    }
    getRandomNumbers(n, seed);
}*/
