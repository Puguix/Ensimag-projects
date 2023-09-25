#include "Asian.hpp"
#include <iostream>

Asian::Asian(double strike, PnlVect* payoffCoeff, double T, int nbTimeSteps, int size)
{
    this->strike = strike;
    this->payoffCoeff_ = payoffCoeff;
    this->T_ = T;
    this->nbTimeSteps_ = nbTimeSteps;
    this->size_ = size;
}

Asian::~Asian()
{
    pnl_vect_free(&this->payoffCoeff_);
}

double
Asian ::payoff(const PnlMat* path)
{
    // Compute the first sum
    PnlVect* col = pnl_vect_create(this->size_);
    pnl_mat_sum_vect(col, path, 'c');

    // Compute the payoff
    double res = MAX(pnl_vect_scalar_prod(col, payoffCoeff_) / (this->nbTimeSteps_ + 1) - strike, 0);
    pnl_vect_free(&col);

    return res;
}