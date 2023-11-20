#include "Model.hpp"
#include "Option.hpp"
#include "pnl/pnl_random.h"
#include "pnl/pnl_mathtools.h"

class MultiLevelMonteCarlo
{
protected:
  Option *m_opt;
  Model *m_mod;
  PnlRng *m_rng;
  /**
   * @brief Return the number of samples to use in a given level
   *
   * @param level index of the level
   * @param m number of time steps of level 1
   * @param L maximum number of levels
   */
  long long nSamples(int level, int m, int L);

  /**
   * @brief Collapse the normal random variable of Gfine columnwise by block of m to fill Gcrude
   *
   * @param[out] Gcrude Renormalised Brownian increments on the cruder grid. Has size m^{l -1} x ...
   * @param[in] Gfine Renormalised Brownian increments on the finer grid. Has size m^l x ...
   * @param m Number of timesteps of level 1
   */
  void collapse(PnlMat *Gcrude, PnlMat *Gfine, int m);

public:
  MultiLevelMonteCarlo(Option *opt, Model *mod, PnlRng *rng);

  /**
   * @brief Run the MultiLevel Monte Carlo computation
   *
   * @param[out] prix Value of the Monte Carlo estimator
   * @param[out] std_dev Standard deviation of the Monte Carlo estimator
   * @param m Number of timesteps of level 1
   * @param nTimeSteps  Number of levels
   */
  void run(double &prix, double &std_dev, int m, int L);
};
