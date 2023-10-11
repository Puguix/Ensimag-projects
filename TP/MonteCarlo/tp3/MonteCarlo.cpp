// vim: set sw=4 ts=4 sts=4:
#include <iostream>
#include <cmath>
#include "MonteCarlo.hpp"

MonteCarlo::MonteCarlo(BSBarrier &product, size_t samples)
    : m_product(product), m_samples(samples)
{
}

PnlVect *MonteCarlo::getBrownianMotion(PnlVect *g, double N, double T, PnlRng *rng)
{
    // Instanciate the vector describing the Brownian motion
    PnlVect *res = pnl_vect_create(N + 1);

    // Compute the root of the time step
    double root = sqrt(T / N);

    // Compute the motion: Xn+1 = Xn + root * Gn+1
    pnl_vect_set(res, 0, 0);
    for (int i = 1; i <= N; i++)
    {
        pnl_vect_set(res, i, GET(res, i - 1) + root * GET(g, i - 1));
    }

    return res;
}

void MonteCarlo::mc(double &prix, double &stddev, PnlRng *rng)
{
    double sum = 0.;
    double var = 0.;
    PnlVect *path = pnl_vect_new();
    PnlVect *G = pnl_vect_new();
    for (size_t i = 0; i < m_samples; i++)
    {
        pnl_vect_rng_normal(G, m_product.m_dates, rng);
        m_product.asset(path, G);
        double flow = m_product.payoff(path);
        sum += flow;
        var += flow * flow;
    }
    prix = sum / m_samples;
    var = var / m_samples - prix * prix;
    stddev = std::sqrt(var / m_samples);
    pnl_vect_free(&path);
    pnl_vect_free(&G);
}

void MonteCarlo::mc2(double &prix, double &stddev, double l, PnlRng *rng)
{
    double ePlus = 0;
    double eMinus = 0;
    double mean1 = 0.;
    double mean2 = 0.;
    double mean3 = 0.;
    double tmp = 0;
    PnlVect *path = pnl_vect_new();
    PnlVect *G = pnl_vect_new();

    PnlVect *lambda = pnl_vect_create(m_product.m_dates);
    for (int i = 0; i < lambda->size - 1; i++)
    {
        pnl_vect_set(lambda, i, l * (i + 1) / m_product.m_dates / m_product.m_maturity);
    }

    for (size_t i = 0; i < m_samples; i++)
    {
        pnl_vect_rng_normal(G, m_product.m_dates, rng);

        eMinus = m_product.weight_minus(G, l);
        ePlus = m_product.weight_plus(G, l);

        m_product.asset(path, G);
        tmp = m_product.payoff(path);

        mean3 += tmp;
        mean2 += SQR(tmp) * ePlus;

        pnl_vect_plus_vect(G, lambda);
        m_product.asset(path, G);
        tmp = m_product.payoff(path);
        mean1 += tmp * eMinus;
    }
    prix = mean1 / m_samples;
    double var = mean2 / m_samples - SQR(mean3 / m_samples);
    stddev = std::sqrt(var);
    pnl_vect_free(&path);
    pnl_vect_free(&G);
}
