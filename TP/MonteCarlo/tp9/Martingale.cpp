#include <string>
#include "pnl/pnl_specfun.h"
#include "pnl/pnl_cdf.h"
#include "Martingale.hpp"
#include <cmath>

MartingaleIncrement *instantiate_martingale(Model *mod, Option *opt, const IParser &P, int t) {
    MartingaleIncrement *O = NULL;
    std::string mart_type;
    P.extract("martingale type", mart_type);

    if (mart_type == "pol") {
        O = new PolynomialStochasticIntegral(P, mod, opt, t);
    }
    else if (mart_type == "local_asset") {
        O = new LocalAssetStochasticIntegral(P, mod, opt, t);
    }
    else {
        printf("No valid martingale type found. Aborting...\n");
    }
    return O;
}

MartingaleIncrement::MartingaleIncrement(Model *M, Option *O, int t)
    : mod(M), opt(O) ,nbBasisFunctions(0) {
    label = "";
    basis = NULL;
    coefficients = NULL;
    nDates = M->m_nHedgingDates;
    currentDate = t;
}

MartingaleIncrement::~MartingaleIncrement() {
    if (coefficients) {
        pnl_vect_free(&coefficients);
    }
    if (basis) {
        pnl_basis_free(&basis);
    }
}

void MartingaleIncrement::print() const {
    std::cout << std::endl;
    std::cout << "*******************************" << std::endl;
    std::cout << "**** Martingale Characteristics ****" << std::endl;
    std::cout << " Martingale type " << label << std::endl;
    if (coefficients) {
        std::cout << " coefficients " << std::endl;
        pnl_vect_print_asrow(coefficients);
    }
}

double MartingaleIncrement::predict(const PnlMat *p_asset) {
    double res = 0.;
    for (int i = 0; i < nbBasisFunctions; i++) {
        double basis_i = evalBasisFunction_i(p_asset, i);
        res += basis_i * GET(coefficients, i);
    }
    return res;
}

double* MartingaleIncrement::getAssetAtDate(const PnlMat *asset) const {
    return getAssetAtDate(asset, currentDate);
}

/**
 * @brief Return the address of the first value asset at time date
 *
 * @param asset A matrix of the model path
 * @param date the current date
 * @return double*
 */
double* MartingaleIncrement::getAssetAtDate(const PnlMat *asset, int date) const {
    return asset->array + date * mod->m_modelSize;
}


/**
 * @brief Compute \Delta \tile S^d_{t_k} = \tilde S^d_{t_k} - \tilde S^d_{t_{k-1}}
 *
 * @param p_asset A path of the mode
 * @param modelIndex the index d of the asset to consider
 * @return double
 */
double MartingaleIncrement::discountedModelIncrement(const PnlMat *p_asset, int modelIndex) const {
    double hedgingTimeStep = mod->m_maturity / mod->m_nHedgingDates;
    int prevDate = currentDate - 1;
    double *St = getAssetAtDate(p_asset, currentDate);
    double *StPrev = getAssetAtDate(p_asset, prevDate);
    return (mod->discount(currentDate * hedgingTimeStep) * mod->dividendAccount(currentDate * hedgingTimeStep, modelIndex) * St[modelIndex] - mod->discount(prevDate * hedgingTimeStep) * mod->dividendAccount(prevDate * hedgingTimeStep, modelIndex) * StPrev[modelIndex]);
}

/**
 * @brief Compute the optimal martingale increment approximating rhs
 *
 * @param p_asset An array of matrices of model paths. Size n_iterationsMC x subDates x size
 * @param p_rhs A vector of size n_iterationsMC
 */
void MartingaleIncrement::fit(const PnlMat * const *p_asset, const PnlVect *p_rhs) {
    int n_iterationsMC = p_rhs->size;
    PnlMat *A = pnl_mat_create_from_zero(nbBasisFunctions, nbBasisFunctions);
    PnlVect *allBasisFunctions = pnl_vect_create(nbBasisFunctions);
    pnl_vect_resize(coefficients, nbBasisFunctions);
    pnl_vect_set_zero(coefficients);

    for (int l = 0; l < n_iterationsMC; l++) {
        for (int i = 0; i < nbBasisFunctions; i++) {
            LET(allBasisFunctions, i) = evalBasisFunction_i(p_asset[l], i);
            LET(coefficients, i) += GET(allBasisFunctions, i) * GET(p_rhs, l);
        }
        pnl_mat_dger(1., allBasisFunctions, allBasisFunctions, A);
    }
    pnl_mat_ls(A, coefficients);
    pnl_vect_free(&allBasisFunctions);
    pnl_mat_free(&A);
}

void MartingaleIncrement::setCoefficients(const PnlVect *p_coefficients) {
    pnl_vect_clone(this->coefficients, p_coefficients);
}

PnlVect* MartingaleIncrement::getCoefficients() const {
    return this->coefficients;
}

/**
 * @brief Construct a new ChaosMartingaleIncrement object
 *
 * @param P a IParser map
 * @param M The underlying model for the asset
 * @param t the current time index computed on the subDates grid.
 */
PolynomialStochasticIntegral::PolynomialStochasticIntegral(const IParser &P, Model *M, Option *O, int t)
    : MartingaleIncrement(M, O, t) {
    int basisType = PNL_BASIS_CANONICAL;
    label = "polynomial_stochastic_integral";
    P.extract("polynomial order", order);
    coefficients = pnl_vect_new();

    basis = pnl_basis_create_from_degree(basisType, order, mod->m_modelSize);
    double hedgingTimeStep = mod->m_maturity / mod->m_nHedgingDates;
    PnlVect *assetMin = mod->getMin(t * hedgingTimeStep);
    PnlVect *assetMax = mod->getMax(t * hedgingTimeStep);
    pnl_basis_set_domain(basis, assetMin, assetMax);
    pnl_vect_free(&assetMin);
    pnl_vect_free(&assetMax);
    nbBasisFunctions = basis->nb_func * mod->m_modelSize;
}

PolynomialStochasticIntegral::~PolynomialStochasticIntegral() { }

void PolynomialStochasticIntegral::print() const
{
    MartingaleIncrement::print();
    std::cout << " polynomial order " << order << std::endl;
    std::cout << "*******************************" << std::endl;

}

double PolynomialStochasticIntegral::evalBasisFunction_i(const PnlMat *p_asset, int p_i) {
    std::div_t euclidean_div = std::div(p_i, mod->m_modelSize);
    int pol_index = euclidean_div.quot;
    euclidean_div = std::div(euclidean_div.rem, mod->m_modelSize);
    int prevTick = euclidean_div.quot;
    int model_index = euclidean_div.rem;
    int prevDate = currentDate - 1;
    double *StPrev = getAssetAtDate(p_asset, prevDate + prevTick);
    return pnl_basis_i(basis, StPrev, pol_index) * discountedModelIncrement(p_asset, model_index);
}

/**
 * @brief Compute the portfolio composition at time currentDate - 1 to be applied at time currentDate.
 *
 * @param[out] p_composition The vector of positions
 * @param p_asset The corresponding model path
 * @param p_signed_Z The corresponding signed payoff path
 */
void PolynomialStochasticIntegral::getPortfolioComposition(PnlVect *p_composition, const PnlMat *p_asset) {
    pnl_vect_resize(p_composition, mod->m_modelSize);
    pnl_vect_set_zero(p_composition);
    for (int i = 0; i < this->nbBasisFunctions; i++) {
        std::div_t euclidean_div = std::div(i, mod->m_modelSize);
        int pol_index = euclidean_div.quot;
        int model_index = euclidean_div.rem;
        double *StPrev = getAssetAtDate(p_asset, currentDate - 1);
        LET(p_composition, model_index) += GET(coefficients, i) * pnl_basis_i(basis, StPrev, pol_index);
    }
}


/**
 * @brief Construct a new ILocalStochasticIntegral object
 *
 * @param P a IParser map
 * @param M The underlying model for the asset
 * @param t the current time index computed on the subDates grid.
 */
ILocalStochasticIntegral::ILocalStochasticIntegral(const IParser &P, Model *M, Option *O, int t)
    : MartingaleIncrement(M, O, t) {
    label = "local_stochastic_integral";
    P.extract("number of intervals for local martingale", nIntervals);
    coefficients = pnl_vect_new();

    basis = NULL;
    regressor_size = 0;
    nbBasisFunctions = 0;
}

ILocalStochasticIntegral::~ILocalStochasticIntegral() {
}

void ILocalStochasticIntegral::print() const
{
    MartingaleIncrement::print();
    std::cout << " number of intervals " << nIntervals << std::endl;
    std::cout << "*******************************" << std::endl;

}

ILocalStochasticIntegral::GlobalIndex ILocalStochasticIntegral::computeGlobalIndex(int linearIndex) const {
    GlobalIndex globalIndex;
    std::div_t euclidean_div = std::div(linearIndex, mod->m_modelSize);
    globalIndex.local = euclidean_div.quot;
    globalIndex.model = euclidean_div.rem;
    return globalIndex;
}

/**
 * @brief Compute the linear index of the basis function within the stochastic integrals
 *
 * @param localIndex the index of the local function
 * @param modelIndex the index of the model
 * @return int
 */
int ILocalStochasticIntegral::computeLinearIndex(int localIndex, int modelIndex) const {
    if (localIndex < 0) {
        return -1;
    }
    int linearIndex = 0;
    linearIndex += modelIndex;
    linearIndex += mod->m_modelSize * localIndex;
    return linearIndex;
}

int ILocalStochasticIntegral::computeLinearIndex(ILocalStochasticIntegral::GlobalIndex globalIndex) const {
    return computeLinearIndex(globalIndex.local, globalIndex.model);
}

/**
 * @brief Non linear function added to the stochastic integrals
 *
 * @param p_asset A path of the mode
 * @param modelIndex the index d of the asset to consider
 * @return double
 */
double ILocalStochasticIntegral::nonLinear(const PnlMat *p_asset, int modelIndex) const {
    return 1.;
}

/**
 * @brief Compute the local prediction
 *
 * @param p_asset The corresponding model path
 * @return double
 */
double ILocalStochasticIntegral::predict(const PnlMat *p_asset) {
    double value = 0.;
    int localIndex = pnl_basis_local_get_index(basis, getRegressor(p_asset));
    if (localIndex < 0) return 0.;
    for (int d = 0; d < mod->m_modelSize; d++) {
        int linearIndex = computeLinearIndex(localIndex, d);
        value += GET(coefficients, linearIndex) * nonLinear(p_asset, d) * discountedModelIncrement(p_asset, d);
    }
    return value;
}

/**
 * @brief Evaluate the i-th basis function
 *
 * @param p_asset The corresponding model path
 * @param p_i the index of the function to evaluation
 * @return double
 */
double ILocalStochasticIntegral::evalBasisFunction_i(const PnlMat *p_asset, int p_i) {
    GlobalIndex globalIndex = computeGlobalIndex(p_i);
    double *regressorPrev = getRegressor(p_asset);
    return pnl_basis_i(basis, regressorPrev, globalIndex.local) * nonLinear(p_asset, globalIndex.model) * discountedModelIncrement(p_asset, globalIndex.model);
}

/**
 * @brief Compute the portfolio composition
 *
 * @param[out] p_composition The vector of positions
 * @param p_asset The corresponding model path
 */
void ILocalStochasticIntegral::getPortfolioComposition(PnlVect *p_composition, const PnlMat *p_asset) {
    pnl_vect_resize(p_composition, mod->m_modelSize);
    pnl_vect_set_zero(p_composition);
    int localIndex = pnl_basis_local_get_index(basis, getRegressor(p_asset));
    if (localIndex < 0) return;
    for (int d = 0; d < mod->m_modelSize; d++) {
        int linearIndex = computeLinearIndex(localIndex, d);
        LET(p_composition, d) = GET(coefficients, linearIndex) * nonLinear(p_asset, d);
    }
}

void ILocalStochasticIntegral::computeQuadraticCovariation(PnlMat *quadCov, const PnlMat *path) const {
    mod->computeQuadraticCovariation(quadCov, path, currentDate - 1);
    for (int i = 0; i < mod->m_modelSize; i++) {
        for (int j = 0; j < mod->m_modelSize; j++) {
            MLET(quadCov, i, j) *= nonLinear(path, i) * nonLinear(path, j);
        }
    }
}

/**
 * @brief Compute the optimal martingale increment approximating rhs
 *
 * @param p_asset An array of matrices of model paths. Size n_iterationsMC x subDates x size
 * @param p_rhs A vector of size n_iterationsMC
 */
void ILocalStochasticIntegral::fit(const PnlMat * const*p_asset, const PnlVect *p_rhs) {
    int n_iterationsMC = p_rhs->size;
    int prevDate = currentDate - 1;
    pnl_vect_resize(coefficients, nbBasisFunctions);
    pnl_vect_set_zero(coefficients);
    PnlMat **A_block = new PnlMat*[basis->nb_func];
    PnlVect **rhs_block = new PnlVect*[basis->nb_func];
    PnlVect *localIntegralAllDimensions = pnl_vect_create(mod->m_modelSize);
    PnlMat *quadraticCovariation = pnl_mat_create(mod->m_modelSize, mod->m_modelSize);

    for (int i = 0; i < basis->nb_func; i++) {
        A_block[i] = pnl_mat_create_from_zero(mod->m_modelSize, mod->m_modelSize);
        rhs_block[i] = pnl_vect_create_from_zero(mod->m_modelSize);
    }

    for (int l = 0; l < n_iterationsMC; l++) {
        pnl_vect_set_zero(localIntegralAllDimensions);
        int localIndex = pnl_basis_local_get_index(basis, getRegressor(p_asset[l]));
        if (localIndex < 0) continue;
        for (int d = 0; d < mod->m_modelSize; d++) {
            LET(localIntegralAllDimensions, d) = nonLinear(p_asset[l], d) * discountedModelIncrement(p_asset[l], d);
        }
        pnl_vect_axpby(GET(p_rhs, l), localIntegralAllDimensions, 1., rhs_block[localIndex]);
        // Use an inner conditioning to make the system definite positive instead of calling directly
        // pnl_mat_dger(1., localIntegralAllDimensions, localIntegralAllDimensions, A_block[localIndex]);
        computeQuadraticCovariation(quadraticCovariation, p_asset[l]);
        pnl_mat_axpy(1.0, quadraticCovariation, A_block[localIndex]);
    }
    for (int i = 0; i < basis->nb_func; i++) {
        int linear_index = computeLinearIndex(i, 0);
        PnlVect alpha_block = pnl_vect_wrap_subvect(coefficients, linear_index, mod->m_modelSize);
        pnl_vect_clone(&alpha_block, rhs_block[i]);
        pnl_mat_ls(A_block[i], &alpha_block);
    }

    for (int i = 0; i < basis->nb_func; i++) {
        pnl_mat_free(&A_block[i]);
        pnl_vect_free(&rhs_block[i]);
    }
    pnl_vect_free(&localIntegralAllDimensions);
    pnl_mat_free(&quadraticCovariation);
    delete[] A_block;
    delete[] rhs_block;

}

LocalAssetStochasticIntegral::LocalAssetStochasticIntegral(const IParser &P, Model *M, Option *O, int t)
    : ILocalStochasticIntegral(P, M, 0, t) {
    label = "local_asset_stochastic_integral";

    regressor_size = mod->m_modelSize;
    basis = pnl_basis_local_create_regular(nIntervals, mod->m_modelSize);
    double hedgingTimeStep = mod->m_maturity / mod->m_nHedgingDates;
    PnlVect *assetMin = mod->getMin(t * hedgingTimeStep);
    PnlVect *assetMax = mod->getMax(t * hedgingTimeStep);
    pnl_basis_set_domain(basis, assetMin, assetMax);
    pnl_vect_free(&assetMin);
    pnl_vect_free(&assetMax);
    nbBasisFunctions = basis->nb_func * regressor_size;
}

LocalAssetStochasticIntegral::~LocalAssetStochasticIntegral() { }

/**
 * @brief Return the actual regressor, ie. the asset at the current date
 *
 * @param asset A trajectory of the model
 * @return double*
 */
double* LocalAssetStochasticIntegral::getRegressor(const PnlMat *asset) {
    return getAssetAtDate(asset, currentDate - 1);
}

