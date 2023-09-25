#include "Basket.hpp"
#include <iostream>

Basket::Basket(double strike, PnlVect* payoffCoeff, double T, int nbTimeSteps, int size)
{
    this->strike = strike;
    this->payoffCoeff_ = payoffCoeff;
    this->T_ = T;
    this->nbTimeSteps_ = nbTimeSteps;
    this->size_ = size;
}

Basket::~Basket()
{
    pnl_vect_free(&this->payoffCoeff_);
}

double
Basket ::payoff(const PnlMat* path)
{
    // Compute the first sum
    PnlVect* col = pnl_vect_create(this->size_);
    pnl_mat_get_col(col, path, this->nbTimeSteps_);

    // Compute the payoff
    double res = MAX(pnl_vect_scalar_prod(col, payoffCoeff_) - strike, 0);
    pnl_vect_free(&col);

    return res;
}