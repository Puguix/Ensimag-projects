// vim: set sw=4 ts=4 sts=4:

#include <iostream>
#include <ctime>
#include "MonteCarlo.hpp"
#include "BSBarrier.hpp"
#include "pnl/pnl_mathtools.h"

double u(int n, double l, PnlMat *W, PnlVect *fSquared)
{
    double tmp;
    double wi;
    double s1 = 0;
    double s2 = 0;
    double s3 = 0;
    // std::cout << fSquared->size << "\n";
    for (int i = 0; i < fSquared->size; i++)
    {
        // std::cout << i << "\n";
        // wi = MGET(W, W->m - 1, i);
        // std::cout << "test\n";
        wi = MGET(W, i, W->n - 1);
        tmp = exp(-l * wi) * GET(fSquared, i);
        s1 += tmp;
        s2 -= tmp * wi;
        s1 += tmp * SQR(wi);
    }
    return (l + s2 / s1) / (1 + (s3 * s1 - SQR(s2)) / SQR(s1));
}

int main()
{
    // Instanciate parameters
    double spot = 100;
    double K = 110;
    double r = 0.05;
    double vol = 0.2;
    double T = 2.;
    double L = 80;
    double J = 24;
    int nbSample = 50000;
    int n = 50;
    double prix, stddev;

    BSBarrier product(T, vol, r, spot, K, L, J);
    MonteCarlo pricer(product, nbSample);

    PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(rng, std::time(NULL));

    // Construct W matrix and f² vector
    PnlMat *W = pnl_mat_create(n, J + 1);
    PnlVect *payoff_square = pnl_vect_create(n);

    PnlVect *g;
    PnlVect *tmpW;
    PnlVect *tmpAsset;
    for (int i = 0; i < n; i++)
    {
        g = pnl_vect_create(J);
        pnl_vect_rng_normal(g, J, rng);
        tmpW = pricer.getBrownianMotion(g, J, T, rng);

        pnl_mat_set_row(W, tmpW, i);

        tmpAsset = pnl_vect_create(J + 1);
        product.asset(tmpAsset, g);
        pnl_vect_set(payoff_square, i, SQR(product.payoff(tmpAsset)));

        free(g);
        free(tmpW);
        free(tmpAsset);
    }

    // pnl_mat_print(W);
    // pnl_vect_print(payoff_square);

    // Compute lambdas
    PnlVect *lambda = pnl_vect_create(n + 1);
    pnl_vect_set(lambda, 0, 0);
    double tmp;
    for (int i = 1; i <= n; i++)
    {
        tmp = GET(lambda, i - 1);
        pnl_vect_set(lambda, i, tmp - u(n, tmp, W, payoff_square));
    }

    pnl_vect_print(lambda);

    pricer.mc(prix, stddev, rng);
    std::cout << "(Méthode classique) prix : " << prix << " (half-IC = " << stddev * 1.96 << ")\n";

    pricer.mc2(prix, stddev, GET(lambda, lambda->size - 1), rng);
    std::cout << "(Méthode avec réduction de variance) prix : " << prix << " (half-IC = " << stddev * 1.96 << ")\n";

    pnl_rng_free(&rng);
    pnl_mat_free(&W);
    pnl_vect_free(&payoff_square);
    pnl_vect_free(&lambda);

    exit(0);
}
