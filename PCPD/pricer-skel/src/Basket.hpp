#pragma once
#include "Option.hpp"
#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"
#include "pnl/pnl_mathtools.h"

/// \brief Classe Basket
class Basket : public Option
{
  public:
    double strike;

  public:
    Basket(double strike, PnlVect* payoffCoeff, double T, int nbTimeSteps, int size);
    ~Basket();
    double payoff(const PnlMat* path);
};
