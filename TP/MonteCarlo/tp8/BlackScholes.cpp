#include "BlackScholes.hpp"

#include <cmath>

BlackScholesModel::BlackScholesModel(double r, double spot, double sigma)
  : m_r(r), m_spot(spot), m_sigma(sigma)
{
  m_log_drift = r - sigma * sigma / 2.;
}

void BlackScholesModel::simul(PnlVect *path, double maturity, double nTimeSteps, PnlVect *G)
{
  pnl_vect_resize(path, nTimeSteps + 1);
  double dt = maturity / nTimeSteps;
  double sqrt_dt = std::sqrt(dt);
  LET(path, 0) = m_spot;
  for (int i = 0; i < nTimeSteps; i++) {
    LET(path, i + 1) = GET(path, i) * std::exp(m_log_drift * dt + m_sigma * sqrt_dt * GET(G, i));
  }
}