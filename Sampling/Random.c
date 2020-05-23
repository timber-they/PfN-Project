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

int main(int argc, char *argv[])
{
	int n;
	if(argc != 2 || (sscanf(argv[1], "%u", &n)) != 1)	
  	{	
  		fprintf(stderr, "Not a valid Argument");	
  		exit(EXIT_FAILURE);	
  	}
  	getRandomNumbers(n);
  }