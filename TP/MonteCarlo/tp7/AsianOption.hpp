#pragma once

#include "Option.hpp"

class AsianOption : public Option
{
public:
  double m_strike;

public:
  AsianOption(double strike, double maturity);
  double payoff(const PnlVect *path);
  ~AsianOption() {}
};