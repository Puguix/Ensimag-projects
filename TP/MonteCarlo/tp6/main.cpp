// vim: set sw=4 ts=4 sts=4:

#include <iostream>
#include <ctime>
#include "BSScheme.hpp"
#include "pnl/pnl_random.h"

int main()
{
    int N = 24;
    double eurlerError, milshteinError;
    BSEuler euler(2., 0.2, 0.03, 100., N);
    BSMilshtein milshtein(2., 0.2, 0.03, 100., N);
    PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(rng, std::time(NULL));

    PnlVect *path = pnl_vect_new();
    PnlVect *G = pnl_vect_create(N);
    pnl_vect_rng_normal(G, N, rng);

    euler.simulExact(path, G, N);
    std::cout << "\tSimu exacte:\n";
    pnl_vect_print(path);

    std::cout << "\tSimu Euler:\n";
    euler.simul(path, G, N);
    pnl_vect_print(path);

    std::cout << "\tSimu Milshtein:\n";
    milshtein.simul(path, G, N);
    pnl_vect_print(path);

    pnl_rng_free(&rng);
    pnl_vect_free(&path);
    pnl_vect_free(&G);
    exit(0);
}
