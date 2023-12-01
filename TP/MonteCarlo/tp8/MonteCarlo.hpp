#pragma once

#include "pnl/pnl_random.h"
#include "Option.hpp"
#include "AsianOption.hpp"
#include "BlackScholes.hpp"

class MonteCarlo
{
protected:
  Option *m_opt;
  BlackScholesModel *m_mod;
  PnlRng *m_rng;

public:
  MonteCarlo(Option *opt, BlackScholesModel *mod, PnlRng *rng);

  /**
   * @brief Run the Monte Carlo computation
   *
   * @param[out] prix Value of the Monte Carlo estimator
   * @param[out] std_dev Standard deviation of the Monte Carlo estimator
   * @param nSamples Number of Monte Carlo samples
   * @param nTimeSteps  Number of time steps to discretize the model.
   */
  void run(double &prix, double &std_dev, long long nSamples, int nTimeSteps);

  /**
   * @brief Run the Monte Carlo computation
   *
   * @param[out] prix Value of the Monte Carlo estimator
   * @param[out] std_dev Standard deviation of the Monte Carlo estimator
   * @param nSamples Number of Monte Carlo samples
   * @param nTimeSteps  Number of time steps to discretize the model.
   */
  void runNested(double &prix, double &std_dev, double alpha, long long N, long long M, int nTimeSteps);
};