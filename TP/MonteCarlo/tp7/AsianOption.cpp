#include "AsianOption.hpp"
#include "pnl/pnl_mathtools.h"

AsianOption::AsianOption(double strike, double maturity)
{
  m_maturity = maturity;
  m_strike = strike;
}

/**
 * @brief Evaluate the payoff function on the given path
 *
 * @param path a simulation of the model S_0, ..., S_T
 */
double AsianOption::payoff(const PnlVect *path)
{
  double average = (pnl_vect_sum(path) - (GET(path, 0) + GET(path, path->size - 1)) / 2.) / (path->size - 1);
  return MAX(average - m_strike, 0.);
}