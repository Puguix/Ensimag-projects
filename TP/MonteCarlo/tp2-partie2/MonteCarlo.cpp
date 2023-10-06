// vim: set sw=4 ts=4 sts=4:
#include <iostream>
#include <cmath>
#include "MonteCarlo.hpp"

MonteCarlo::MonteCarlo(BSCall &product, size_t samples)
    : m_product(product), m_samples(samples)
{
}

void MonteCarlo::mc(double &prix, double &stddev, PnlRng *rng)
{
    double sum = 0.;
    double var = 0.;
    for (size_t i = 0; i < m_samples; i++)
    {
        double g = pnl_rng_normal(rng);
        double flow = m_product.payoff(g);
        sum += flow;
        var += flow * flow;
    }
    prix = sum / m_samples;
    var = var / m_samples - prix * prix;
    stddev = std::sqrt(var / m_samples);
}

void MonteCarlo::is(PnlVect *lambda, double gamma, int n, PnlRng *rng)
{

    // alpha & beta & teta
    double a = 0.;
    double b = 0.75;
    double t = 0.;

    PnlVect *g = pnl_vect_new();
    pnl_vect_rng_normal(g, n, rng);

    for (int i = 1; i <= n; i++)
    {
        t = t - (gamma / pow(i + 1, b)) * this->m_product.d_weight_plus(t, GET(g, i - 1));
        if (SQR(t) > log(a + 1))
        {
            a++;
            t = 0;
        }
        pnl_vect_set(lambda, i - 1, t);
    }
    pnl_vect_free(&g);
}

void MonteCarlo::mcis(double &prix, double &stddev, double theta, PnlRng *rng)
{
    double sum = 0.;
    double var = 0.;
    for (size_t i = 0; i < m_samples; i++)
    {
        double g = pnl_rng_normal(rng);
        double flow = m_product.payoff(g, theta) * m_product.weight_minus(g, theta);
        sum += flow;
        var += flow * flow;
    }
    prix = sum / m_samples;
    var = var / m_samples - prix * prix;
    stddev = sqrt(var / m_samples);
}