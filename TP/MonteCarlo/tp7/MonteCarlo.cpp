#include "MonteCarlo.hpp"
#include <iostream>
#include <cmath>

MonteCarlo::MonteCarlo(Option *opt, Model *mod, PnlRng *rng)
{
  m_opt = opt;
  m_mod = mod;
  m_rng = rng;
}

void MonteCarlo::run(double &prix, double &std_dev, long long nSamples, int nTimeSteps)
{
  prix = 0.;
  std_dev = 0.;
  double h = 0;
  PnlVect *path = pnl_vect_create(nTimeSteps);
  PnlMat *G = pnl_mat_create(nTimeSteps, 2);

  for (long long i = 0; i < nSamples; i++)
  {
    // std::cout << "AHAHHHAHH ici\n";
    pnl_mat_rng_normal(G, nTimeSteps, 2, m_rng);
    m_mod->simul(path, m_opt->m_maturity, nTimeSteps, G);
    // pnl_vect_print(path);
    // std::cout << "simulfini\n";
    h = m_opt->payoff(path);
    // std::cout << "payoff ici\n";
    prix += h;
    std_dev += h * h;
  }
  pnl_mat_free(&G);
  pnl_vect_free(&path);

  prix /= nSamples;
  std_dev = std::sqrt((std_dev / nSamples - prix * prix) / nSamples);
}