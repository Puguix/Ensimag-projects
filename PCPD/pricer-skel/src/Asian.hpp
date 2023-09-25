#pragma once
#include "Option.hpp"
#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"
#include "pnl/pnl_mathtools.h"

/// \brief Classe Asian
class Asian : public Option
{
  public:
    double strike; // le Strike
  public:
    Asian(double strike, PnlVect* payoffCoeff, double T, int nbTimeSteps, int size);
    ~Asian();
    double payoff(const PnlMat* path);
};