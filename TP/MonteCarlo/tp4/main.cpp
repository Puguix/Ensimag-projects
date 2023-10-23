#include <algorithm>
#include <cmath>
#include <iostream>
#include <ctime>
#include "pnl/pnl_finance.h"
#include "pnl/pnl_random.h"

double payoff(double S0, double sigma, double r, double T, double K, double g)
{
    double ST = S0 * std::exp((r - sigma * sigma / 2.) * T + sigma * std::sqrt(T) * g);
    return std::exp(-r * T) * std::max(ST - K, 0.);
}

double delta_df(double S0, double sigma, double r, double T, double K, PnlRng *rng, int N)
{
    double epsilon = 1 / pow((double)N, 0.2);
    std::cout << "Epsilon: " << epsilon << "\n";
    double mean1 = 0;
    double mean2 = 0;

    for (int i = 0; i < N; i++)
    {
        double g = pnl_rng_normal(rng);
        mean1 += payoff(S0 + epsilon, sigma, r, T, K, g);
        mean2 += payoff(S0 - epsilon, sigma, r, T, K, g);
    }
    mean1 /= N;
    mean2 /= N;

    return (mean1 - mean2) / 2 / epsilon;
}

double delta_likelihood(double S0, double sigma, double r, double T, double K, PnlRng *rng, int N)
{
    double mean = 0;

    for (int i = 0; i < N; i++)
    {
        double g = pnl_rng_normal(rng);
        mean += payoff(S0, sigma, r, T, K, g) * g / sigma / S0 / std::sqrt(T);
    }
    return mean / N;
}

double delta_pathwise(double S0, double sigma, double r, double T, double K, PnlRng *rng, int N) {}

int main(int argc, char const *argv[])
{
    // Instanciate parameters
    double spot = 100;
    double K = 110;
    double r = 0.05;
    double vol = 0.2;
    double T = 2.;
    int nbSample = 50000;

    PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(rng, std::time(NULL));

    double payoffValue = payoff(spot, vol, r, T, K, pnl_rng_normal(rng));

    double deltaDf = delta_df(spot, vol, r, T, K, rng, nbSample);
    double deltaLikelihood = delta_likelihood(spot, vol, r, T, K, rng, nbSample);

    double price;
    double delta;
    pnl_cf_call_bs(spot, K, T, r, 0., vol, &price, &delta);

    std::cout << "Payoff: " << payoffValue << "\n";
    std::cout << "Price: " << price << "\n";
    std::cout << "Delta: " << delta << "\n";
    std::cout << "Delta DF: " << deltaDf << "\n";
    std::cout << "Delta likelihood: " << deltaLikelihood << "\n";

    return 0;
}
