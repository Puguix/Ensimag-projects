#include "Heston.hpp"
#include <iostream>
#include <cmath>

HestonModel::HestonModel(double r, double spot, double initVol, double sigma, double kappa, double theta, double rho)
    : Model(2, r), m_spot(spot), m_initVol(initVol), m_sigma(sigma), m_kappa(kappa), m_theta(theta), m_rho(rho)
{
}

void HestonModel::simul(PnlVect *path, double maturity, double nTimeSteps, PnlMat *G)
{
  pnl_vect_resize(path, nTimeSteps + 1);
  pnl_vect_set(path, 0, m_spot);
  double dt = maturity / nTimeSteps;
  double sqrt_dt = std::sqrt(dt);
  double v = m_initVol;
  double s = m_spot;

  for (int i = 1; i <= nTimeSteps; i++)
  {
    // std::cout << "boucle ici\n";
    v += m_kappa * (m_theta - v) * dt + m_sigma * std::sqrt(std::max(v, 0.)) * pnl_mat_get(G, i - 1, 0) * sqrt_dt;
    // std::cout << "pbm ici\n";
    s += m_r * s * dt + std::sqrt(v) * s * pnl_mat_get(G, i - 1, 1) * sqrt_dt;
    // std::cout << "pbm la\n";
    pnl_vect_set(path, i, s);
    // std::cout << "pbm tout court\n";
  }
}