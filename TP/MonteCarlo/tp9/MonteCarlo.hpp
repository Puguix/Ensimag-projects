#ifndef _MONTECARLO_H
#define _MONTECARLO_H

#include "Model.hpp"
#include "Option.hpp"
#include "Martingale.hpp"
#include "pnl/pnl_matrix.h"
#include "pnl/pnl_random.h"
#include "jlparser/parser.hpp"

#define NUMBER_OF_SAMPLES_SAA_MAX 5E5

/**
 * Monte Carlo class.
 */
class MonteCarlo
{
public:
    Model *mod;
    Option *opt;
    int m_IsSize;
    PnlRng *rng;
    size_t m_nSamples; /*!< number of simulations */

    MonteCarlo();
    MonteCarlo(PnlRng *, const IParser &ParamTab);
    ~MonteCarlo();

    void print(bool verbose = false) const;
    void price(double &prix, double &stdDev);
    void price(const PnlMat *past, double t, double &prix, double &stdDev);

protected:
    /**
     * Reduce the price and the variance
     *
     * @param[in, out] price
     * @param[in, out] stdDev On output, it contains the variance of the estimator
     * @param nSamples number of samples used in the estimator
     * @param t current date
     */
    void finalize(double &price, double &stdDev, size_t nSamples, double t = 0) const;

    PnlVect *m_BT;
};

#endif
