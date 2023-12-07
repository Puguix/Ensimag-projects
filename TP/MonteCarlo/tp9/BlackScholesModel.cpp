#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

#include "BlackScholesModel.hpp"
#include "jlparser/parser.hpp"
#include "pnl/pnl_matrix.h"
#include "pnl/pnl_mathtools.h"

BlackScholesModel::BlackScholesModel() : Model()
{
}

BlackScholesModel::~BlackScholesModel()
{
    if (m_sigma) pnl_vect_free(&m_sigma);
}

BlackScholesModel::BlackScholesModel(const IParser &P)
    : Model(P)
{
    P.extract("volatility", m_sigma, m_modelSize);
}

void BlackScholesModel::path(const PnlVect *St, double t, int last_index, int nTimeSteps, PnlVect *drift, PnlMat *G, PnlMat *sample)
{

    int nSteps = G->m;
    double dt = m_maturity / nTimeSteps;
    // Test if t == m_maturity
    if (last_index == nTimeSteps) return;
    pnl_mat_resize(m_pathMatrix, nTimeSteps + 1, m_modelSize);
    pnl_mat_dgemm('N', 'T', 1., m_covChol, G, 0., m_workMatrix);

    // Step between t and t_{i+1}
    double dt_0 = (last_index + 1) * dt - t;
    double sqrt_dt_0 = sqrt(dt_0);
    for (int i = 0; i < m_modelSize; i++) {
        MLET(sample, last_index + 1, i) = GET(St, i) * exp((GET(drift, i) - GET(m_dividend, i) - GET(m_sigma, i) * GET(m_sigma, i) / 2.0) * dt_0 + sqrt_dt_0 * GET(m_sigma, i) * MGET(m_workMatrix, i, 0));
    }

    // Go on with the regular grid
    double sqrt_dt_local = sqrt(dt);
    for (int j = last_index + 2; j < last_index + 1 + nSteps; j++) {
        for (int i = 0; i < m_modelSize; i++) {
            MLET(sample, j, i) = MGET(sample, j - 1, i) * exp((GET(drift, i) - GET(m_dividend, i) - GET(m_sigma, i) * GET(m_sigma, i) / 2.0) * dt + sqrt_dt_local * GET(m_sigma, i) * MGET(m_workMatrix, i, j - (last_index + 1)));
        }
    }
}

void BlackScholesModel::print() const
{
    cout << "**** BS Model Characteristics ****" << endl;
    cout << " volatility : ";
    pnl_vect_print_asrow(m_sigma);
    Model::print();
}

void BlackScholesModel::fprint_market(FILE *f) const
{
    Model::fprint_market(f);
    fprintf(f, "# volatility: ");
    pnl_vect_fprint_asrow(f, m_sigma);
}

PnlVect* BlackScholesModel::getMin(double t) const {
    PnlVect *min_v = pnl_vect_create(m_modelSize);
    for (int i = 0; i < m_modelSize; i++) {
        double sig = GET(m_sigma, i);
        LET(min_v, i) = GET(m_init, i) * exp((m_interest - sig * sig / 2) * t - sig * 3.0 * sqrt(t));
    }
    return min_v;
}

PnlVect* BlackScholesModel::getMax(double t) const {
    PnlVect *max_v = pnl_vect_create(m_modelSize);
    for (int i = 0; i < m_modelSize; i++) {
        double sig = GET(m_sigma, i);
        LET(max_v, i) = GET(m_init, i) * exp((m_interest - sig * sig / 2) * t + sig * 3.0 * sqrt(t));
    }
    return max_v;
}

void BlackScholesModel::computeQuadraticCovariation(PnlMat *quadCov, const PnlMat *path, int t) const {
    pnl_mat_resize(quadCov, m_modelSize, m_modelSize);
    double hedgingTimeStep = m_maturity / m_nHedgingDates;
    double current_discount =  discount(t * hedgingTimeStep);
    double squared_discount = current_discount * current_discount;

    for (int i = 0; i< m_modelSize; i++) {
            MLET(quadCov, i, i) = MGET(path, t, i) * MGET(path, t, i) * squared_discount * (exp(hedgingTimeStep * GET(m_sigma, i) * GET(m_sigma, i)) - 1.);
        for (int j = 0; j < i; j++) {
            double quadCov_ij = MGET(path, t, i) * MGET(path, t, j) * squared_discount * (exp(hedgingTimeStep * GET(m_sigma, i) * GET(m_sigma, j) * m_rho) - 1.);
            MLET(quadCov, i, j) = quadCov_ij;
            MLET(quadCov, j, i) = quadCov_ij;

        }
    }
}
