#ifndef CONFIDENCE_INTERVALS_H
#define CONFIDENCE_INTERVALS_H

double gaussConf(double standDev, unsigned int numOfVals, float level);
double *conf(double *sorted, size_t n_elems, float level);
#endif
