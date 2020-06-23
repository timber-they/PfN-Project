#include "../Extraction/RelativeData.h"

double fabs(double f)
{
    return f < 0 ? -f : f;
}

START_TEST(test_bucket_indices_pos) {
    size_t n_buckets = 4;
    size_t population_size = 99;
    size_t *indices = (size_t*) malloc(n_buckets * sizeof *indices);

    bucket_indices(indices, population_size, n_buckets);

    ck_assert(indices[0] == 0 && indices[1] == 25 && indices[2] == 50 &&
              indices[3] == 75);
    free(indices);

    population_size = 3;
    n_buckets = 4;

    indices = (size_t *)malloc(n_buckets * sizeof *indices);
    bucket_indices(indices, population_size, n_buckets);

    ck_assert(indices[0] == 0 && indices[1] == 1 && indices[2] == 2 &&
              indices[3] == 3 
        );
    free(indices);
        }
END_TEST

START_TEST(test_percentage_of_trials) {
    size_t n_buckets = 4;
    size_t population_size = 100;
    size_t *indices = (size_t *)malloc(n_buckets * sizeof *indices);

    double *pc_per_bucket = (double *)calloc(n_buckets, sizeof *pc_per_bucket);
    TYPE occurences_of_n_infected[101] = {0};

    double tol = 0.00001;

    occurences_of_n_infected[0] = 50;
    occurences_of_n_infected[100] = 50;

    bucket_indices(indices, population_size, n_buckets);
    percentage_of_trials_in_bucket(pc_per_bucket, indices, n_buckets,
                                   occurences_of_n_infected, population_size);
    // half of the trials have 0 infected, and half have the maximum number infected
    ck_assert(
              fabs(pc_per_bucket[0] - 0.5) < tol
              && fabs(pc_per_bucket[n_buckets - 1] - 0.5) < tol
        );
    // all but the extremes never occur
    for (size_t i = 1; i < n_buckets - 2; ++i) {
        ck_assert(pc_per_bucket[i] == 0);
    }
    free(pc_per_bucket);
    free(indices);
}
END_TEST
