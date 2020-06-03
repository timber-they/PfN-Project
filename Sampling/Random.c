#include <stdlib.h>	
#include <stdio.h>	
#include <time.h>

int getRandomNumbers(unsigned int n, int temp_seed)
{
    int i = 1;
    int seed = 100;
    if(temp_seed > 0)
    {
    	seed = temp_seed;
    }
    srand48(seed); // Seed Generation seed variable
    while(i <= n) // printing out some values
    {
        printf("%f\n",drand48());
        i++;
    }
    return(EXIT_SUCCESS);
}

void intoArray(unsigned int n, int temp_seed)
{
    //only usable for low n
    int seed = 100;
    if(temp_seed > 0)
    {
    	seed = temp_seed;
    }
    double arr[n];
    int idx = 0;
    srand48(seed);
    while(idx <= n)
    {
            arr[idx] = drand48();
            printf("%f\n",arr[idx]);
            idx++;
    }
}

void getRandomNumber(unsigned int n, int temp_seed)
{
	int seed = 100;
	if(temp_seed > 0)
    {
    	seed = temp_seed;
    }
    srand48(seed); // Seed Generation based on seed variable
    printf("%f\n",drand48());
}


int main(int argc, char *argv[])
{
    int n;
    int seed;
    if(argc > 4 || (sscanf(argv[1], "%u", &n)) != 1)	
      {	
          fprintf(stderr, "Not a valid Argument");	
          exit(EXIT_FAILURE);	
      }
    if(argc == 3)
    {
    	(sscanf(argv[2], "%u", &seed));
    }
    getRandomNumbers(n, seed);
  }