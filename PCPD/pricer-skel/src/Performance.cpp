#include "Performance.hpp"
#include <iostream>
Performance::Performance(PnlVect* payoffCoeff, double T, int nbTimeSteps, int size)
{
    this->payoffCoeff_ = payoffCoeff;
    this->T_ = T;
    this->nbTimeSteps_ = nbTimeSteps;
    this->size_ = size;
}

Performance::~Performance()
{
    pnl_vect_free(&this->payoffCoeff_);
}

double
Performance ::payoff(const PnlMat* path)
{
    // col1 is for the top sum and col2 for the bottom sum
    double sum = 1;
    PnlVect* col1 = pnl_vect_create(this->size_);
    PnlVect* col2 = pnl_vect_create(this->size_);

    // Loop for each time step
    for (int i = 1; i < this->nbTimeSteps_ + 1; i++) {

        // Update columns
        pnl_mat_get_col(col1, path, i);
        pnl_mat_get_col(col2, path, i - 1);

        // Compute the sum
        sum += MAX(pnl_vect_scalar_prod(col1, payoffCoeff_) / pnl_vect_scalar_prod(col2, payoffCoeff_) - 1, 0);
    }

    // Free vects
    pnl_vect_free(&col1);
    pnl_vect_free(&col2);

    return sum;
}