#ifndef HISTOGRAMS
#define HISTOGRAMS

//paints a histogram based on source data. the maximum lenth for the filname of the sources is 32 characters
int paintHistogram(char *source, double *confidence_intervall, double median, double medium, double confidence_level, int population_size, int number_of_trials);

#endif
