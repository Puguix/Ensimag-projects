#pragma once

#include "pnl/pnl_matrix.h"
#include "pnl/pnl_vector.h"

class Model
{
public:
  const int m_brownianSize; /*!< Dimension of the Brownian motion */
  double m_r;

  Model(int brownianSize, double r);
  /**
   * @brief Return a simulation of S on the regular grid with timestep (maturity / nTimeSteps)
   *
   * @param[out] path contains a simulation of the asset on output. The size of path is (nTimeSteps + 1)
   * @param maturity Time horizon of the discretization
   * @param nTimSteps the number of timesteps of the gid.
   * @param G a matrix of standard normal random variables with size (nTimeSteps x 2)
   */
  virtual void simul(PnlVect *path, double maturity, double nTimSteps, PnlMat *G) = 0;
};
