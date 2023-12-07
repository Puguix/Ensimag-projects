#ifndef _BS_H
#define _BS_H

#include "Model.hpp"
#include "pnl/pnl_matrix.h"
#include "pnl/pnl_random.h"

class BlackScholesModel : public Model
{
public:
    PnlVect *m_sigma;
    BlackScholesModel();
    BlackScholesModel(const IParser &P);
    ~BlackScholesModel();
    void print() const;
    void fprint_market(FILE *f) const;
    /**
     * Conditional simulation of the the model
     *
     * @param St current value of the asset
     * @param t current time
     * @param last_index index of the last time step before t
     * @param nTimeStepis number of timesteps on [0,T]
     * @param drift drift vector of the underlying asset (typically r or mu)
     * @param G a matrix of normal r.v. with size (m_nTimeSteps - last_index) x size
     * @param[in,out] sample A matrix with size m_nTimeSteps x size. On input, sample already contains
     *          (S_{t_0}, ..., S_{t_i}) if t_i <= t < t_{i+1}
     * On output, samples contains a conditional simulation of the model.
     */
    virtual void path(const PnlVect *St, double t, int last_index, int nTimeSteps, PnlVect *drift, PnlMat *G, PnlMat *sample);
    virtual PnlVect *getMin(double t) const;
    virtual PnlVect *getMax(double t) const;
    virtual void computeQuadraticCovariation(PnlMat *quadCov, const PnlMat *path, int t) const;

};

#endif
