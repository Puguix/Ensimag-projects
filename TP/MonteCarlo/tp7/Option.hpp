#pragma once

#include "pnl/pnl_vector.h"

class Option
{
public:
  double m_maturity;

  virtual double payoff(const PnlVect *path) = 0;
  virtual ~Option() {}
};