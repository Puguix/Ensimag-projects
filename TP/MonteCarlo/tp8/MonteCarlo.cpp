#include <cmath>
#include "MonteCarlo.hpp"
#include "pnl/pnl_mathtools.h"

MonteCarlo::MonteCarlo(Option *opt, BlackScholesModel *mod, PnlRng *rng)
{
  m_opt = opt;
  m_mod = mod;
  m_rng = rng;
}

void MonteCarlo::run(double &prix, double &std_dev, long long nSamples, int nTimeSteps)
{
  PnlVect *G = pnl_vect_new();
  PnlVect *path = pnl_vect_new();
  double sum = 0.;
  double sum_sq = 0.;
  for (int n = 0; n < nSamples; n++)
  {
    pnl_vect_rng_normal(G, nTimeSteps, m_rng);
    m_mod->simul(path, m_opt->m_maturity, nTimeSteps, G);
    double payoff = m_opt->payoff(path);
    sum += payoff;
    sum_sq += payoff * payoff;
  }
  prix = std::exp(-m_mod->m_r * m_opt->m_maturity) * sum / nSamples;
  std_dev = std::sqrt((std::exp(-2 * m_mod->m_r * m_opt->m_maturity) * sum_sq / nSamples - prix * prix) / nSamples);
}

void MonteCarlo::runNested(double &prix, double &std_dev, double alpha, long long N, long long M, int nTimeSteps)
{
  double V0, tmp;
  run(V0, tmp, N, nTimeSteps);
  prix = 0;

  PnlVect *G1 = pnl_vect_new();
  PnlVect *G2 = pnl_vect_new();
  PnlVect *path = pnl_vect_new();
  for (int m = 0; m < M; m++)
  {
    double Vt = 0;
    pnl_vect_rng_normal(G1, nTimeSteps / 2, m_rng);
    pnl_vect_resize(G1, nTimeSteps);
    double sum = 0.;
    for (int n = 0; n < N; n++)
    {
      pnl_vect_rng_normal(G2, nTimeSteps / 2, m_rng);
      pnl_vect_set_subblock(G1, G2, nTimeSteps / 2);

      m_mod->simul(path, m_opt->m_maturity, nTimeSteps, G1);
      double payoff = m_opt->payoff(path);
      sum += payoff;
    }
    Vt += std::exp(-m_mod->m_r) * sum / N;
    double payoffOpt = MAX(Vt - alpha * V0, 0.);
    prix += payoffOpt;
    std_dev += payoffOpt * payoffOpt;
  }
  prix *= std::exp(-m_mod->m_r) / M;
  std_dev = std::sqrt((std::exp(-2 * m_mod->m_r) * std_dev / M - prix * prix) / M);
}
