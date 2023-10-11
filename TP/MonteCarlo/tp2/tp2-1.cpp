#include <tuple>
#include <cmath>
#include <iostream>
#include "pnl/pnl_mathtools.h"
#include "pnl/pnl_vector.h"
#include "pnl/pnl_random.h"

PnlVect *getBrownianMotion(double N, double T, PnlRng *rng)
{
    // Instanciate the vector describing the Brownian motion
    PnlVect *res = pnl_vect_new();

    // Generate a gaussian vector
    pnl_vect_rng_normal(res, N + 1, rng);

    // Compute the root of the time step
    double root = sqrt(T / N);

    // Compute the motion: Xn+1 = Xn + root * Gn+1
    pnl_vect_set(res, 0, 0);
    for (int i = 1; i <= N; i++)
    {
        pnl_vect_set(res, i, GET(res, i - 1) + root * GET(res, i));
    }

    return res;
}

PnlVect *simuAsset(double spot, PnlVect *bm, double r, double vol, double T, int J)
{
    // Get the brownian motion
    PnlVect *asset = pnl_vect_copy(bm);

    // Intanciate useful variables
    double t = 0;
    double step = T / J;
    double mulT = (r - SQR(vol)) / 2;

    // Compute the values of the asset
    for (int i = 0; i <= J; i++)
    {
        pnl_vect_set(asset, i, spot * exp(mulT * t + vol * GET(asset, i)));
        t += step;
    }
    return asset;
}

double payoff(PnlVect *asset, double K, double J)
{
    // std::cout << std::max(K * pnl_vect_max(asset) - GET(asset, J), 0.) << "\n";
    return std::max(K * pnl_vect_max(asset) - GET(asset, J), 0.);
}

std::tuple<double, double> pricerMC(int M, double spot, double K, double r, double vol, double T, double J, PnlRng *rng)
{

    // Instanciate and compute the mean and the variance
    double mean = 0;
    double var = 0;
    double tmp = 0;
    PnlVect *bm;
    PnlVect *asset;

    // Loop for each simulation
    for (int i = 0; i < M; i++)
    {
        bm = getBrownianMotion(J + 1, T, rng);
        asset = simuAsset(spot, bm, r, vol, T, J);
        tmp = exp(-T * r) * payoff(asset, K, J);
        mean += tmp;
        var += SQR(tmp);
        pnl_vect_free(&asset);
    }

    mean /= M;
    return std::make_tuple(mean, var / M - SQR(mean));
}

void mirror(PnlVect *bm)
{
    pnl_vect_mult_scalar(bm, -1.);
}

std::tuple<double, double> pricerVarAnti(int M, double spot, double K, double r, double vol, double T, double J, PnlRng *rng)
{

    // Instanciate the means and the variances
    double tmp1 = 0;
    double mean1 = 0;
    double var1 = 0;
    double tmp2 = 0;
    double mean2 = 0;
    double var2 = 0;
    double cov = 0;
    PnlVect *bm;
    PnlVect *asset;
    PnlVect *assetMirror;

    // Loop for each simulation
    for (int i = 0; i < M; i++)
    {
        bm = getBrownianMotion(J + 1, T, rng);
        asset = simuAsset(spot, bm, r, vol, T, J);
        mirror(bm);
        assetMirror = simuAsset(spot, bm, r, vol, T, J);

        tmp1 = exp(-T * r) * payoff(asset, K, J);
        tmp2 = exp(-T * r) * payoff(assetMirror, K, J);

        mean1 += tmp1;
        mean2 += tmp2;

        var1 += SQR(tmp1);
        var2 += SQR(tmp2);

        cov += tmp1 * tmp2;

        pnl_vect_free(&bm);
        pnl_vect_free(&asset);
        pnl_vect_free(&assetMirror);
    }

    // Compute the results
    double mean = (mean1 + mean2) / 2 / M;
    cov = cov - mean1 / M * mean2 / M;
    var1 = var1 / M - SQR(mean1 / M);
    var2 = var2 / M - SQR(mean2 / M);

    return std::make_tuple(mean, (var1 + var2 + 2 * cov) / 2 / M);
}

std::tuple<double, double> pricerControl(int M, double spot, double K, double r, double vol, double T, double J, PnlRng *rng)
{

    // Instanciate the means and the variances
    double tmp1 = 0;
    double mean1 = 0;
    double var1 = 0;
    double tmp2 = 0;
    double mean2 = 0;
    double var2 = 0;
    double cov = 0;
    PnlVect *bm1;
    PnlVect *asset1;
    PnlVect *bm2;
    PnlVect *asset2;

    // Loop for each simulation
    for (int i = 0; i < M; i++)
    {
        bm1 = getBrownianMotion(J + 1, T, rng);
        asset1 = simuAsset(spot, bm1, r, vol, T, J);
        bm2 = getBrownianMotion(J + 1, T, rng);
        asset2 = simuAsset(spot, bm2, r, vol, T, J);

        tmp1 = exp(-T * r) * payoff(asset1, K, J);
        tmp2 = GET(asset2, asset2->size - 1) - spot * exp(T * r);

        mean1 += tmp1;
        mean2 += tmp2;

        var1 += SQR(tmp1);
        var2 += SQR(tmp2);

        cov += tmp1 * tmp2;

        pnl_vect_free(&bm1);
        pnl_vect_free(&asset1);
        pnl_vect_free(&bm2);
        pnl_vect_free(&asset2);
    }

    // Compute the results
    mean1 /= M;
    mean2 /= M;
    var1 = var1 / M - SQR(mean1);
    var2 = var2 / M - SQR(mean2);
    cov = cov - mean1 * mean2;
    double mean = 100 - spot * exp(r * T) + mean1 - mean2;
    std::cout << spot * exp(r * T) << " " << mean1 << " " << mean2 << "\n";

    return std::make_tuple(mean, (1. - SQR(cov) / var1 / var2) * var1);
}

int main(int argc, char const *argv[])
{
    // Instanciate values
    double spot = 100;
    double K = 0.95;
    double r = 0.02;
    double vol = 0.25;
    double T = 2;
    int J = 24;
    int M = 50000;

    // Instanciate the rng
    PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(rng, time(NULL));

    // Tests

    // Instanciate results value
    double mean, var;

    // Pricer
    std::tie(mean, var) = pricerMC(M, spot, K, r, vol, T, J, rng);
    std::cout << "Pricer Monte Carlo\t\tMean: " << mean << "\tStandard deviation: " << sqrt(var) << "\n";

    std::tie(mean, var) = pricerVarAnti(M, spot, K, r, vol, T, J, rng);
    std::cout << "Pricer Variables antithétiques\tMean: " << mean << "\tStandard deviation: " << sqrt(var) << "\n";

    std::tie(mean, var) = pricerControl(M, spot, K, r, vol, T, J, rng);
    std::cout << "Pricer Variable de contrôle\tMean: " << mean << "\tStandard deviation: " << sqrt(var) << "\n";

    pnl_rng_free(&rng);

    return 0;
}
