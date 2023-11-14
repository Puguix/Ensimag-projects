// vim: set sw=4 ts=4 sts=4:

#include <iostream>
#include <ctime>
#include "BSScheme.hpp"
#include "pnl/pnl_random.h"

int main()
{
    double eurlerError, milshteinError;
    BSEuler euler(2., 0.2, 0.03, 100.);
    BSMilshtein milshtein(2., 0.2, 0.03, 100.);
    PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(rng, std::time(NULL));

    int m_samples = 50000;
    int J = 24;

    
    //creation du vecteur brownien
    PnlVect *brow = pnl_vect_create(J + 1);
    //creation du vecteur des lois normales
    PnlVect *G;
    PnlVect *exact;
    PnlVect *simu;
    PnlVect *milstein;

    double eulerErr = 0.;
    double milshteinErr = 0.;
    for (size_t i = 0; i < m_samples; i++) {
        G = pnl_vect_new();
        pnl_vect_rng_normal(G, J, rng);
        euler.brownien(G,brow);

        exact = pnl_vect_create(J + 1);
        euler.simulExact(exact, G, J);
        //pnl_vect_print(exact);

        simu = pnl_vect_create(J + 1);
        euler.simul(simu, brow, J);
        //pnl_vect_print(simu);

        milstein = pnl_vect_create(J + 1);
        milshtein.simul(milstein, brow, J);

        eulerErr += pow(GET(simu, J) - GET(exact, J), 4);
        milshteinErr += pow(GET(milstein, J) - GET(exact, J), 4);
    }
    eurlerError = eulerErr / m_samples / pow(J, 2);
    milshteinError = milshteinErr / m_samples / pow(J,4);

    std::cout << "Erreur Euler : " << eurlerError << "\n";
    std::cout << "Erreur Milstein : " << milshteinError << "\n";

    pnl_rng_free(&rng);
    exit(0);
}
