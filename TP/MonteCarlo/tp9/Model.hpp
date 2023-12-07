#ifndef _MOD_H
#define _MOD_H

#include "jlparser/parser.hpp"
#include "pnl/pnl_matrix.h"
#include "pnl/pnl_random.h"

class Model
{
  public:
    double m_maturity;        /*!< m_maturity of the option */
    int m_brownianSize;       /*!< size of the Brownian motion, default is model size */
    int m_nTimeSteps;         /*!< step for time discretisation : default value 1*/
    int m_nHedgingDates;      /*!< Number of hedging dates */
    double m_interest;        /*!< instantaneous m_interest rate */
    PnlVect *m_trend;         /*!< market trend, only useful when under the historical probability */
    PnlVect *m_dividend;      /*!< instantaneous m_dividend rate */
    int m_modelSize;          /*!< size of the model */
    double m_rho;             /*!< correlation of the model, assumed * constant between the different dimensions */
    PnlMat *m_covChol;        /*!< Cholesky factorisation of the * covariance matrix */
    PnlVect *m_init;          /*!< spot values */
    double m_sqrt_nTimeSteps; /*!< sqrt(m_nTimeSteps) */
    double m_dt;              /*!< m_maturity / m_nTimeSteps */
    double m_sqrt_dt;         /*!< sqrt(dt) */

    PnlMat *m_pathMatrix;   /*!< To store a path of the model. (m_nTimeSteps + 1) x size */
    PnlMat *m_deltaB;       /*!< renormalized Brownian increments with size m_nTimeSteps x size */
    PnlMat *m_deltaB_drift; /*!< renormalized and drifted Brownian increments with size m_nTimeSteps x size */

    Model();
    Model(const IParser &ParamTab);
    virtual ~Model();

    /**
     * Print the model parameters to a file
     *
     * @param f FILE descriptor
     */
    virtual void fprint_market(FILE *f) const;

    /**
     * Compute one path of the model.
     * Draw the relevant random variables and call path()
     *
     * @param rng PnlRng
     */
    virtual void path(PnlRng *rng);

    /**
     * Conditional sampling the model using the r.v. from m_deltaB_drift.
     *
     * @param past a matrix containing the path up to time t (S_{t_0}, ..., S_{t_i}, S_t)
     * @param t current date
     * @param rng PnlRng
     */
    virtual void path(const PnlMat *past, double t, PnlRng *rng);


    /**
     * @brief Sample a path of the model under the risk neutral measure with m_nHedgingDates dates
     * 
     */
    void pathForHedging(PnlRng *rng);

    /**
     * Generate a path of the model under the historical probability
     *
     * @param rng PnlRng
     * @param[out] market contains historical values on output.
     */
    virtual void simul_market(PnlRng *rng, PnlMat *market);

    /**
     * Generate a path of the model under the historical probability
     *
     * @param nbAssets number of assets
     * @param marketFile name of the file containing the historical values
     * @param[out] market contains historical values on output.
     */
    virtual void simul_market(int nbAssets, const char *marketFile, PnlMat *market);

    /** Prints a model description
     *  To be implemented in each class inherited from Model
     */
    virtual void print() const = 0;
    double discount(double t) const;
    double dividendAccount(double t, int modelIndex) const;
    virtual PnlVect *getMin(double t) const = 0;
    virtual PnlVect *getMax(double t) const = 0;

    /**
     * @brief Compute the quadratic covariation of the discounted asset increments between time t and t +1
     *
     * @param[out] quadCov A matrix of size @p m_modelSize x @p m_modelSize.
     * @param path A path of the model with @p m_hedgingDates time steps.
     * @param t The index of the current time on the hedging grid : t = 0, 1, ..., m_hedgingDates
     */
    virtual void computeQuadraticCovariation(PnlMat *quadCov, const PnlMat *path, int t) const = 0;

  protected:
    PnlVect *m_rVector;    /*!< A vector view of the m_interest rate */
    PnlVect *m_workVector; /*!< Workspace for intermediate computations */
    PnlMat *m_workMatrix;  /*!< Workspace for intermediate computations */

    /**
     * Compute the Cholesky factorization of the correlation and store it into
     * m_covChol
     */
    virtual int computeCovChol();
    void GenericConstructor(const IParser &ParamTab);
    /**
     * Compute one path using m_deltaB_ISDrift for the Brownian increments
     */
    virtual void path();
    /**
     * Compute one path of the model with a single ISDrift vector for all the
     * time steps.
     *
     * @param ISDrift : the importance sampling vector
     *      (same ISDrift for all time steps)
     */
    void path(const PnlVect *ISDrift);
    /**
     * Compute one conditional path using m_deltaB_drift for the Brownian increments
     *
     * @param past a matrix containing the path up to time t (S_{t_0}, ..., S_{t_i}, S_t)
     * @param t current date
     */
    virtual void path(const PnlMat *past, double t);
    /**
     * Compute one conditional path of the model with a single ISDrift vector for all the
     * time steps.
     *
     * @param past a matrix containing the path up to time t (S_{t_0}, ..., S_{t_i}, S_t)
     * @param t current date
     * @param ISDrift : the importance sampling vector
     *      (same ISDrift for all time steps)
     */
    void path(const PnlMat *past, double t, const PnlVect *ISDrift);
    /**
     * Conditional simulation of the the model
     *
     * @param St current value of the asset
     * @param t current time
     * @param last_index index of the last time step before t
     * @param nTimeSteps number of timesteps on [0,T]
     * @param drift drift vector of the underlying asset (typically r or mu)
     * @param G a matrix of normal r.v. with size (m_nTimeSteps - last_index) x size
     * @param[in,out] sample A matrix with size m_nTimeSteps x size. On input, sample already contains
     *          (S_{t_0}, ..., S_{t_i}) if t_i <= t < t_{i+1}
     * On output, samples contains a conditional simulation of the model.
     */
    virtual void path(const PnlVect *St, double t, int last_index, int nTimeSteps, PnlVect *drift, PnlMat *G, PnlMat *sample) = 0;

    int getLastTimeStep(double t) const;
    int getNextTimeStep(double t) const;
};

Model *instantiate_model(const IParser &P);

#endif
