#pragma once
#include "Option.hpp"
#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"
#include "pnl/pnl_mathtools.h"

/// \brief Classe Performance
class Performance : public Option
{
  public:
    Performance(PnlVect* payoffCoeff, double T, int nbTimeSteps, int size);
    ~Performance();
    double payoff(const PnlMat* path);
};