#pragma once

#include "pnl/pnl_matrix.h"
#include "pnl/pnl_vector.h"

#include "Model.hpp"

class HestonModel : public Model
{
public:
  double m_spot;
  double m_initVol;
  double m_sigma;
  double m_kappa;
  double m_theta;
  double m_rho;

  HestonModel(double r, double spot, double initVol, double sigma, double kappa, double theta, double rho);

  /**
   * @brief Return a simulation of S on the regular grid with timestep (maturity / nTimeSteps)
   *
   * @param[out] path contains a simulation of the asset on output. The size of path is (nTimeSteps + 1)
   * @param maturity Time horizon of the discretization
   * @param nTimSteps the number of timesteps of the gid.
   * @param G a matrix of standard normal random variables with size (nTimeSteps x 2)
   */
  void simul(PnlVect *path, double maturity, double nTimSteps, PnlMat *G);
};