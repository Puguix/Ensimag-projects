// vim: set sw=4 ts=4 sts=4:
#include <iostream>
#include <cmath>
#include "MonteCarlo.hpp"

MonteCarlo::MonteCarlo(BSBarrier &product, size_t samples)
    : m_product(product), m_samples(samples)
{}



void MonteCarlo::mc(double &prix, double &stddev, PnlRng *rng)
{
    double sum = 0.;
    double var = 0.;
    PnlVect *path = pnl_vect_new();
    PnlVect *G = pnl_vect_new();
    for (size_t i = 0; i < m_samples; i++) {
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
