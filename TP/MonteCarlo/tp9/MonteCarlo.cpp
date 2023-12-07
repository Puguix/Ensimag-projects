#include <iostream>
#include <cstdlib>
#include <cstring>

#include "pnl/pnl_mathtools.h"
#include "MonteCarlo.hpp"

static void _set_diag_vect(PnlMat *M, const PnlVect *x)
{
    int i;
    for (i = 0; i < M->m; i++) {
        MLET(M, i, i) = GET(x, i);
    }
}

void MonteCarlo::finalize(double &price, double &std_dev, size_t nSamples, double t) const
{
    price = price * std::exp(-mod->m_interest * (opt->m_maturity - t)) / double(nSamples);
    std_dev = std::exp(-2 * mod->m_interest * (opt->m_maturity - t)) * std_dev / double(nSamples) - price * price;
    std_dev = std::sqrt(std_dev / double(nSamples));
}

MonteCarlo::MonteCarlo()
{
    rng = NULL;
    m_nSamples = 0;
}

/**
 * Constructor
 * @param rng a PnlRng
 * @param P a hash map
 */
MonteCarlo::MonteCarlo(PnlRng *rng, const IParser &P)
{
    mod = instantiate_model(P);
    opt = instantiate_option(P);
    m_IsSize = mod->m_brownianSize;
    this->rng = rng;
    P.extract("sample number", m_nSamples);
    m_BT = pnl_vect_new();
}

MonteCarlo::~MonteCarlo()
{
    if (mod != NULL) delete mod;
    if (opt != NULL) delete opt;
    pnl_vect_free(&m_BT);
}

void MonteCarlo::print(bool verbose) const
{
    std::cout << std::endl;
    std::cout << "*************************************" << std::endl;
    if (verbose) {
        mod->print();
        opt->print();
    }
    std::cout << " Number of Samples : " << m_nSamples << std::endl;
    std::cout << " Number of timesteps " << mod->m_nTimeSteps << std::endl;
    std::cout << "*************************************" << std::endl << std::endl;
}

/**
 * Computes the price by a crude Monte--Carlo estimator
 *
 * @param[out] prix price
 * @param[out] std_dev std_dev of the discounted payoff
 */
void MonteCarlo::price(double &prix, double &std_dev)
{
    double payoffVector;
    prix = 0.0;
    std_dev = 0.0;
    for (size_t i = 0; i < m_nSamples; i++) {
        mod->path(rng);
        payoffVector = opt->payoff(mod->m_pathMatrix);
        prix += payoffVector;
        std_dev += payoffVector * payoffVector;
    }
    finalize(prix, std_dev, m_nSamples);
}

/**
 * Compute the price by a crude Monte--Carlo estimator at time t
 *
 * @param t current date
 * @param past market values up to time t
 * @param[out] prix price
 * @param[out] std_dev std_dev of the discounted payoff
 */
void MonteCarlo::price(const PnlMat *past, double t, double &prix, double &std_dev)
{
    double payoffVector;
    prix = 0.0;
    std_dev = 0.0;
    for (size_t i = 0; i < m_nSamples; i++) {
        mod->path(past, t, rng);
        payoffVector = opt->payoff(mod->m_pathMatrix);
        prix += payoffVector;
        std_dev += payoffVector * payoffVector;
    }
    finalize(prix, std_dev, m_nSamples, t);
}
