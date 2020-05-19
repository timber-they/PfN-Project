/* Code by Julius Bittner 2020
 * Use under CC-BY-SA 4.0
 * Part of PfN-Project 2020
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// conf: calculate confidence interval of given numbers with given level
// give: standard deviation
// give: number of values as unsigned int
// give: confidence level to use. Choose from 0.8, 0.85, 0.9, 0.95, 0.99, 0.995, 0.999
// return: confidence as deviation from medium, to the upside as well as to the downside!
double conf(double standDev, unsigned int numOfVals, float level)
{
    float Z;
    unsigned int Level = level * 1000;
    //printf("%i\n", Level);
    switch (Level) {
	    case 800: Z = 1.282; break;
	    case 850: Z = 1.440; break;
	    case 900: Z = 1.645; break;
	    case 950: Z = 1.960; break;
            case 990: Z = 2.576; break;
            case 995: Z = 2.807; break;
	    case 999: Z = 3.291; break;
	    default: 
		printf("Please choose level of confidence from 0.8, 0.85, 0.9, 0.95, 0.99, 0.995, 0.999"); 
		return EXIT_FAILURE;
    }
    
    double s = sqrt(numOfVals);
    double c = Z * standDev / s;
    return c;
}

int main(int argc,char *argv[])
{
    printf("%f\n", conf(20, 40, 0.95));
    return EXIT_SUCCESS;
}
