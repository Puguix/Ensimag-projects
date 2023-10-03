#include <math.h>
#include <cmath>
#include <iostream>
#include "pnl/pnl_specfun.h"
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

double monteCarloMean(int nbSamples, double a, double T, double N)
{
    // instanciate the variables
    double res = 0;

    // Instanciate the rng
    PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(rng, time(NULL));

    // loop for each sample
    for (int i = 0; i <= nbSamples; i++)
    {
        // Get a brownian motion
        PnlVect *bm = getBrownianMotion(N, T, rng);

        // find ta and add it to res
        double j = 1;
        while (j < N)
        {
            if (a > 0 && GET(bm, j) >= a)
            {
                res += T * j / N;
                break;
            }
            if (a < 0 && GET(bm, j) <= a)
            {
                res += T * j / N;
                break;
            }
            j++;
        }
        if (j == N)
        {
            res += T;
        }

        pnl_vect_free(&bm);
    }

    return res / nbSamples;
}

double getPreciseTA(double a, double x1, double x2, double step, int nbStep, PnlRng *rng)
{
    double UminusS = 0;
    double TminusU = 0;

    int i = 1;
    while (x1 < a && i <= nbStep)
    {
        double UminusS = i * step / nbStep;
        double TminusU = step - UminusS;

        x1 = TminusU / step * x1 + UminusS / step * x2 + sqrt(TminusU * UminusS / step) * pnl_rng_normal(rng);
        i++;
    }
    // std::cout << x1 << " i " << i << "\n";
    // return i * step / nbStep;
    return step;
}

double monteCarloMeanPrecise(int nbSamples, double a, double T, double N, double steps)
{
    // instanciate the variables
    double res = 0;

    // Instanciate the rng
    PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(rng, time(NULL));

    // loop for each sample
    for (int i = 0; i <= nbSamples; i++)
    {
        // Get a brownian motion
        PnlVect *bm = getBrownianMotion(N, T, rng);

        // find ta and add it to res
        double j = 1;
        while (j <= N)
        {
            if (a > 0 && GET(bm, j) >= a)
            {
                res += getPreciseTA(a, GET(bm, j - 1), GET(bm, j), T / N, steps, rng) + (j - 1) * T / N;
                j = N + 2;
            }
            else if (a < 0 && GET(bm, j) <= a)
            {
                res += getPreciseTA(a, GET(bm, j - 1), GET(bm, j), T / N, steps, rng) + (j - 1) * T / N;
                j = N + 2;
            }
            else
            {
                j++;
            };
        }
        if (j == N + 1)
        {
            res += T;
        }

        pnl_vect_free(&bm);
    }

    return res / nbSamples;
}

double mean(double a, double T)
{
    double res = T * (1 - pnl_sf_gamma_inc(0.5, SQR(a) / 2 / T) / sqrt(M_PI));
    res += SQR(a) / 2 / sqrt(M_PI) * pnl_sf_gamma_inc(-0.5, SQR(a) / 2 / T);
    return res;
}

int main(int argc, char const *argv[])
{
    // Instanciate variables
    double a = 2;
    int nbSamples = 5000;
    double nbSteps = 5000;
    double preciseSteps = 100;
    double practicalMean = 0;
    double preciseMean = 0;
    double theoricalMean = 0;

    // Loop for each T value, compute and print the results
    for (double T = 1; T <= 5; T++)
    {
        practicalMean = monteCarloMean(nbSamples, 2, T, nbSteps);
        preciseMean = monteCarloMeanPrecise(nbSamples, a, T, nbSteps, preciseSteps);
        theoricalMean = mean(2, T);
        std::cout.precision(5);
        std::cout << "T = " << T << "\tPractical mean: " << practicalMean << "\t\tPrecise mean: " << preciseMean << "\t\tTheorical mean: " << theoricalMean << "\t\tbiais * sqrt(N): " << abs(practicalMean - theoricalMean) * sqrt(nbSteps) << "\n";
    }

    return 0;
}
