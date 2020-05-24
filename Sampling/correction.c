#include <stdio.h>
#include <stdlib.h>

#define SPECIFICITY 0.991
#define SENSITIVITY 0.909

//applies correction to lessen bias
double correct(double f)
{
  f = (f + SPECIFICITY - 1) / (SPECIFICITY + SENSITIVITY - 1);
  return f;
}

//input: f = n_measured / n_subjects --> 0 < f < 1
int main(int argc, char *argv[])
{
  double f;
  switch (argc)
  {
    case 2:
      if((sscanf(argv[1], "%lf", &f) == 1) && (argv[1] < 1) && (argv[1] > 0))
      {
        correct(f);
        break;
      }
    default:
      fprintf(stderr, "Usage: %s <fraction of positive tests>", argv[0]);
      return EXIT_FAILURE;
  }
  printf("successfully applied correction!\n");
  return EXIT_SUCCESS;
}
