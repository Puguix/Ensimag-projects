#include <iostream>
#include <iostream>
#include <cstdlib>
#include <cmath>

#include "Model.hpp"
#include "pnl/pnl_matrix.h"
#include "pnl/pnl_mathtools.h"
#include "jlparser/parser.hpp"
#include "BlackScholesModel.hpp"

using namespace std;

Model *instantiate_model(const IParser &P)
{
    Model *mod = NULL;
    string modelType;
    P.extract("model type", modelType);

    if (modelType == "bs")
        mod = new BlackScholesModel(P);
    else {
        cout << "Model " << modelType << " unknown. Abort." << endl;
        abort();
    }

    return mod;
}

Model::Model()
{
    m_nTimeSteps = 1;
    m_workVector = NULL;
    m_workMatrix = NULL;
    m_covChol = NULL;
    m_pathMatrix = NULL;
    m_deltaB = NULL;
    m_deltaB_drift = NULL;
}

void Model::GenericConstructor(const IParser &P)
{
    m_nTimeSteps = 1;
    m_nHedgingDates = 0;
    m_rho = 1.;
    P.extract("maturity", m_maturity);
    P.extract("timestep number", m_nTimeSteps, true);
    P.extract("hedging dates number", m_nHedgingDates, true);
    P.extract("trend", m_trend, m_modelSize, true);
    P.extract("spot", m_init, m_modelSize);
    P.extract("interest rate", m_interest);
    m_rVector = pnl_vect_create_from_double(m_modelSize, m_interest);
    P.extract("dividend rate", m_dividend, m_modelSize, true);
    if (m_dividend == NULL) {
        m_dividend = pnl_vect_create_from_zero(m_modelSize);
    }
    if (!P.extract("correlation", m_rho, true) && (m_modelSize != 1)) {
        perror("correlation is missing");
        exit(1);
    }
    m_sqrt_nTimeSteps = sqrt(double(m_nTimeSteps));
    m_dt = m_maturity / double(m_nTimeSteps);
    m_sqrt_dt = sqrt(m_dt);
    m_covChol = pnl_mat_create(m_brownianSize, m_brownianSize);
    m_pathMatrix = pnl_mat_create(m_nTimeSteps + 1, m_modelSize);
    m_deltaB = pnl_mat_create(m_nTimeSteps, m_brownianSize);
    m_deltaB_drift = pnl_mat_create(m_nTimeSteps, m_brownianSize);

    if (computeCovChol() == PNL_FAIL) {
        perror("Correlation matrix is not positive definite");
        exit(1);
    }

    m_workVector = pnl_vect_new();
    m_workMatrix = pnl_mat_new();
}

Model::Model(const IParser &P)
{
    P.extract("option size", m_modelSize);
    m_brownianSize = m_modelSize;
    GenericConstructor(P);
}

Model::~Model()
{
    if (m_trend) pnl_vect_free(&m_trend);
    pnl_vect_free(&m_rVector);
    pnl_mat_free(&m_covChol);
    pnl_mat_free(&m_pathMatrix);
    pnl_mat_free(&m_deltaB);
    pnl_mat_free(&m_deltaB_drift);
    pnl_vect_free(&m_init);
    pnl_vect_free(&m_dividend);
    pnl_vect_free(&m_workVector);
    pnl_mat_free(&m_workMatrix);
}

/* set the value of the correlation parameter and update the
 * covariance matrix and its derivative */
int Model::computeCovChol()
{
    int i, j;
    for (i = 0; i < m_modelSize; i++) {
        MLET(m_covChol, i, i) = 1.0;
        for (j = 0; j < i; j++) {
            MLET(m_covChol, i, j) = m_rho;
            MLET(m_covChol, j, i) = m_rho;
        }
    }
    return pnl_mat_chol(m_covChol);
}

void Model::print() const
{
    cout << " m_interest rate : " << m_interest << endl;
    cout << " m_dividend rate : ";
    pnl_vect_print_asrow(m_dividend);
    if (m_modelSize > 1) {
        cout << " correlation " << m_rho << endl;
    }
    cout << " Number of m_nTimeSteps : " << m_nTimeSteps << endl;
    cout << " Spot : ";
    pnl_vect_print_asrow(m_init);
}

void Model::fprint_market(FILE *f) const
{
    fprintf(f, "# maturity time: %f\n", m_maturity);
    fprintf(f, "# model size: %d\n", m_modelSize);
    fprintf(f, "# number of dates: %d\n", m_nHedgingDates);
    fprintf(f, "# spot: ");
    pnl_vect_fprint_asrow(f, m_init);
    fprintf(f, "# dividend rate: ");
    pnl_vect_fprint_asrow(f, m_dividend);
    fprintf(f, "# correlation: %f\n", m_rho);
}


void Model::path(PnlRng *rng)
{
    pnl_mat_rng_normal(m_deltaB, m_nTimeSteps, m_brownianSize, rng);
    pnl_mat_set_row(m_pathMatrix, m_init, 0);
    path(m_init, 0, 0, m_nTimeSteps, m_rVector, m_deltaB, m_pathMatrix);
}

void Model::path(const PnlMat *past, double t)
{
    int last_index = getLastTimeStep(t);
    for (int i = 0; i <= last_index; i++) {
        PnlVect s = pnl_vect_wrap_mat_row(past, i);
        pnl_mat_set_row(m_pathMatrix, &s, i);
    }
    PnlVect St = pnl_vect_wrap_mat_row(past, past->m - 1);
    path(&St, t, last_index, m_nTimeSteps, m_rVector, m_deltaB_drift, m_pathMatrix);
}

void Model::path(const PnlMat *past, double t, PnlRng *rng)
{
    pnl_mat_rng_normal(m_deltaB, m_nTimeSteps - getLastTimeStep(t), m_brownianSize, rng);
    pnl_mat_clone(m_deltaB_drift, m_deltaB);
    path(past, t);
}

/**
 * Computes one path of the model under the historical probability
 *
 * @param rng random number generator
 * @param[out] market a matrix with size (m_nTimeSteps + 1) x m_modelSize
 */
void Model::simul_market(PnlRng *rng, PnlMat *market)
{
    if (m_nHedgingDates == 0) {
        cout << "Number of hedging dates not specified. Returning." << endl;
        return;
    }
    if (m_trend == NULL) {
        cout << "Trend not specified. Returning." << endl;
        return;
    }
    PnlMat *G = pnl_mat_new();
    pnl_mat_resize(market, m_nHedgingDates + 1, m_modelSize);
    pnl_mat_set_row(market, m_init, 0);
    pnl_mat_rng_normal(G, m_nHedgingDates, m_brownianSize, rng);
    path(m_init, 0., 0, m_nHedgingDates, m_trend, G, market);
    pnl_mat_free(&G);
}

void Model::simul_market(int nbAssets, const char *marketFile, PnlMat *market)
{
    if (m_nHedgingDates == 0) {
        cout << "Number of hedging dates not specified. Returning." << endl;
        return;
    }
    if (m_trend == NULL) {
        cout << "Trend not specified. Returning." << endl;
        return;
    }
    if (nbAssets != m_modelSize) {
        cout << "Argument nbAssets conflicts with m_modelSize. Returning." << endl;
        return;
    }

    PnlMat *market_from_file = pnl_mat_create_from_file(marketFile);
    if (m_nHedgingDates + 1 != market_from_file->m) {
        cout << "the Number of hedging dates conflicts with the number of rows of " << marketFile << endl;
        pnl_mat_free(&market_from_file);
        return;
    }
    pnl_mat_extract_subblock(market, market_from_file, 0, market_from_file->m, 0, nbAssets);
    pnl_mat_free(&market_from_file);
}

/**
 * Compute one sample of the model under the risk neutral probability and store it in m_pathMatrix
 */
void Model::path()
{
    pnl_mat_set_row(m_pathMatrix, m_init, 0);
    path(m_init, 0, 0, m_nTimeSteps, m_rVector, m_deltaB_drift, m_pathMatrix);
}

/**
 * Compute one sample of the model under the risk neutral probability with m_nHedgingDates and store it in m_pathMatrix
 *
 * @param rng random number generator
 */
void Model::pathForHedging(PnlRng *rng)
{
    pnl_mat_rng_normal(m_deltaB, m_nHedgingDates, m_brownianSize, rng);
    pnl_mat_set_row(m_pathMatrix, m_init, 0);
    path(m_init, 0, 0, m_nHedgingDates, m_rVector, m_deltaB, m_pathMatrix);
}


int Model::getLastTimeStep(double t) const
{
    int index = t / m_dt;
    return index;
}

int Model::getNextTimeStep(double t) const
{
    int prev_index = t / m_dt;
    if (fabs(prev_index * m_dt - t) < 1E-10) {
        return prev_index;
    }
    return prev_index + 1;
}

/**
 * Compute the discount factor
 *
 * @param t current time
 */
double Model::discount(double t) const {
    return exp(-m_interest * t);
}

/**
 * Compute the accumulated dividends
 *
 * @param t current time
 * @param modelIndex the asset component
 */
double Model::dividendAccount(double t, int modelIndex) const {
    return exp(GET(m_dividend, modelIndex) * t);
}