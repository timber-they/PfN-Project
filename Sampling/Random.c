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

void intoArray(unsigned int n)
{
	//only usable for low n
	double arr[n];
	int idx = 0;
	srand48(time(NULL));
	while(idx <= n)
	{
			arr[idx] = drand48();
			printf("%f\n",arr[idx]);
			idx++;
	}
}

void getRandomNumber(unsigned int n)
{
	srand48(time(NULL)); //Seed Generation based on system Time
	printf("%f\n",drand48());
}


int main(int argc, char *argv[])
{
	int n;
	if(argc != 2 || (sscanf(argv[1], "%u", &n)) != 1)	
  	{	
  		fprintf(stderr, "Not a valid Argument");	
  		exit(EXIT_FAILURE);	
  	}
  	intoArray(n);
  }