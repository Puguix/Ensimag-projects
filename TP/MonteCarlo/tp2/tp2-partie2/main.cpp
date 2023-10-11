// vim: set sw=4 ts=4 sts=4:

#include <iostream>
#include <ctime>
#include "MonteCarlo.hpp"
#include "BSCall.hpp"

int main()
{
    double prix, stddev;
    BSCall product(2., 0.2, 0.03, 100., 120.);
    MonteCarlo pricer(product, 50000);

    PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(rng, std::time(NULL));

    double gamma = 0.01;
    int n = 200;

    PnlVect *lambda = pnl_vect_create(n);
    pricer.is(lambda, gamma, n, rng);

    // Print lambda values
    // for (int i = 0; i < n; i++)
    // {
    //     std::cout << GET(lambda, i) << "\n";
    // }

    pricer.mcis(prix, stddev, GET(lambda, lambda->size - 1), rng);
    std::cout << "prix mcis: " << prix << " (IC = " << stddev * 1.96 << ")\n";

    pricer.mc(prix, stddev, rng);
    std::cout << "prix mc: " << prix << " (IC = " << stddev * 1.96 << ")\n";
    pnl_rng_free(&rng);
    exit(0);
}
