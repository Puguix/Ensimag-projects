#pragma once

#include <string>
#include "pnl/pnl_matrix.h"
#include "pnl/pnl_basis.h"

#include "jlparser/parser.hpp"
#include "Model.hpp"
#include "Option.hpp"

/**
 * @class MartingaleIncrement
 * @brief Interface for the martingale increment implementation
 *
 */
class MartingaleIncrement {
public:
    virtual void print() const;
    MartingaleIncrement(Model *M, Option *O, int t);
    virtual ~MartingaleIncrement();

    virtual double predict(const PnlMat *asset);
    virtual double evalBasisFunction_i(const PnlMat *asset, int i) = 0;
    virtual void fit(const PnlMat * const *asset, const PnlVect *rhs);
    virtual void getPortfolioComposition(PnlVect *composition, const PnlMat *asset) = 0;
    void setCoefficients(const PnlVect *p_coefficients);
    PnlVect* getCoefficients() const;

protected:
    Model *mod;
    Option *opt;
    std::string label; //!< Martingale type name.
    int nbBasisFunctions; //!< number of functions in the basis.
    int currentDate; //!< The end of the current time interval.
    int nDates; //!< The number of hedging dates.
    PnlBasis *basis;
    PnlVect *coefficients; //!< Only available after calling fit.
    double discountedModelIncrement(const PnlMat *p_asset, int regressorIndex) const;
    double* getAssetAtDate(const PnlMat *asset) const;
    double* getAssetAtDate(const PnlMat *asset, int date) const;
};


/**
 * @class PolynomialStochasticIntegral.
 * @brief Stochastic integral of polynomials
 *
 * Implementation of a family of stochastic integrals of multivariate polynomials of the assets with respect to every discounted underlying asset.
 */
class PolynomialStochasticIntegral: public MartingaleIncrement {
public:
    PolynomialStochasticIntegral(const IParser &P, Model *M, Option *O, int t);
    virtual ~PolynomialStochasticIntegral();
    void print() const;
    virtual double evalBasisFunction_i(const PnlMat *asset, int i);
    virtual void getPortfolioComposition(PnlVect *composition, const PnlMat *asset);

protected:
    int order; //!< polynomial order
};

/**
 * @class ILocalStochasticIntegral.
 * @brief Stochastic integral of local functions
 *
 * Implementation a family of stochastic integrals of local functions of the assets with respect to every discounted underlying asset.
 */
class ILocalStochasticIntegral: public MartingaleIncrement {
public:
    ILocalStochasticIntegral(const IParser &P, Model *M, Option *O, int t);
    virtual ~ILocalStochasticIntegral();
    void print() const;
    virtual double predict(const PnlMat *asset);
    virtual double evalBasisFunction_i(const PnlMat *asset, int i);
    virtual void fit(const PnlMat * const*asset, const PnlVect *rhs);
    virtual void getPortfolioComposition(PnlVect *composition, const PnlMat *asset);

protected:
    typedef struct {
        /** Index the local function */
        int local;
        /** Index of the asset*/
        int model;
    } GlobalIndex;
    GlobalIndex computeGlobalIndex(int linearIndex) const;
    int computeLinearIndex(GlobalIndex globalIndex) const;
    int computeLinearIndex(int localIndex, int regressorIndex) const;
    virtual double* getRegressor(const PnlMat *asset) = 0;
    int regressor_size;
    int nIntervals; //!< Number of interval per dimension
    virtual double nonLinear(const PnlMat *p_asset, int modelIndex) const;
    void computeQuadraticCovariation(PnlMat *quadCov, const PnlMat *path) const;
};

class LocalAssetStochasticIntegral: public ILocalStochasticIntegral {
public:
    LocalAssetStochasticIntegral(const IParser &P, Model *M, Option *O, int t);
    virtual ~LocalAssetStochasticIntegral();

protected:
    virtual double* getRegressor(const PnlMat *asset);

};

MartingaleIncrement *instantiate_martingale(Model *mod, Option *opt, const IParser &P, int t);
