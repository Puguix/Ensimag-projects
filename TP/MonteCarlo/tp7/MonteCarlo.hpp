#pragma once

#include "pnl/pnl_random.h"
#include "Option.hpp"
#include "Model.hpp"

class MonteCarlo
{
protected:
  Option *m_opt;
  Model *m_mod;
  PnlRng *m_rng;

public:
  MonteCarlo(Option *opt, Model *mod, PnlRng *rng);

  /**
   * @brief Run the Monte Carlo computation
   *
   * @param[out] prix Value of the Monte Carlo estimator
   * @param[out] std_dev Standard deviation of the Monte Carlo estimator
   * @param nSamples Number of Monte Carlo samples
   * @param nTimeSteps  Number of time steps to discretize the model.
   */
  void run (double &prix, double &std_dev, long long nSamples, int nTimeSteps);
};