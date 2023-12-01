#pragma once

#include "pnl/pnl_matrix.h"
#include "pnl/pnl_vector.h"

class BlackScholesModel
{
public:
  double m_r;
  double m_spot;
  double m_sigma;

  BlackScholesModel(double r, double spot, double sigma);

  /**
   * @brief Return a simulation of S on the regular grid with timestep (maturity / nTimeSteps)
   *
   * @param[out] path contains a simulation of the asset on output. The size of path is (nTimeSteps + 1)
   * @param maturity Time horizon of the discretization
   * @param nTimSteps the number of timesteps of the gid.
   * @param G a vector of standard normal random variables with size nTimeSteps
   */
  void simul(PnlVect *path, double maturity, double nTimSteps, PnlVect *G);

private:
  double m_log_drift;
};