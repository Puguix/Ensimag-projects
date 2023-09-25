#include "BlackScholesModel.hpp"
#include <iostream>

BlackScholesModel::BlackScholesModel(int size, double r, double rho, PnlVect* sigma, PnlVect* spot)
{
    this->size_ = size;
    this->r_ = r;
    this->rho_ = rho;
    this->sigma_ = sigma;
    this->spot_ = spot;
    this->trend = pnl_vect_new();
}

BlackScholesModel::~BlackScholesModel()
{
    pnl_vect_free(&this->sigma_);
    pnl_vect_free(&this->spot_);
    pnl_vect_free(&this->trend);
}

void
BlackScholesModel::asset(PnlMat* path, double T, int nbTimeSteps, PnlRng* rng)
{
    // Instanciate the random number generator and the vector G
    PnlVect* gPrime = pnl_vect_new();
    PnlVect* g = pnl_vect_new();

    // Create the correlation matrix
    PnlMat* l = pnl_mat_create_from_scalar(this->size_, this->size_, this->rho_);
    pnl_mat_set_diag(l, 1, 0);

    // Compute the Cholesky decomposition of the correlation matrix
    pnl_mat_chol(l);

    // Calculate the step
    double step = T / nbTimeSteps;

    // Initiate a result value
    double res = 0;

    // Copy the spot value into path
    pnl_mat_set_col(path, this->spot_, 0);

    // Loop for each time step
    for (int i = 1; i <= nbTimeSteps; i++) {

        // Generate the gaussian vector
        pnl_vect_rng_normal(g, this->size_, rng);

        // Compute the product of the L x G
        pnl_mat_mult_vect_inplace(gPrime, l, g);

        // Loop for each asset
        for (int d = 0; d < this->size_; d++) {

            // Compute the left part of the sum
            res = (this->r_ - SQR(GET(this->sigma_, d)) / 2) * step;

            // Sum the right part of the sum
            res += GET(this->sigma_, d) * sqrt(step) * GET(gPrime, d);

            // Compute the final result
            res = exp(res) * MGET(path, d, i - 1);

            // Update the result in the output matrix
            pnl_mat_set(path, d, i, res);
        }
    }
    // Free memory
    pnl_mat_free(&l);
    pnl_vect_free(&g);
    pnl_vect_free(&gPrime);
}

void
BlackScholesModel::asset(PnlMat* path, double t, double T, int nbTimeSteps, PnlRng* rng, const PnlMat* past)
{
    // Instanciate the output matrix
    PnlVect* g = pnl_vect_new();
    PnlVect* gPrime = pnl_vect_new();

    // Create the correlation matrix
    PnlMat* l = pnl_mat_create_from_scalar(this->size_, this->size_, this->rho_);
    pnl_mat_set_diag(l, 1, 0);

    // Compute the Cholesky decomposition of the correlation matrix
    pnl_mat_chol(l);

    // Calculate the step
    double step = T / nbTimeSteps;
    // Compute the number of time steps already passed
    // int pastSteps = t / step;
    int pastSteps;
    // Initiate a result value
    double res = 0;
    double dt = T / nbTimeSteps;
    int last_rank_past = std::floor(t / dt);
    if (std::fabs(last_rank_past * dt - t) >= 1E-12) {
        last_rank_past = (t / dt) + 1;
    }

    // Set the first part of the output matrix to past values
    PnlMat* tmp = pnl_mat_create(this->size_, last_rank_past + 1);
    pnl_mat_extract_subblock(tmp, past, 0, this->size_, 0, last_rank_past + 1);
    pnl_mat_set_subblock(path, tmp, 0, 0);

    // Loop for each time step
    for (int i = last_rank_past + 1; i <= nbTimeSteps; i++) {

        // Generate the gaussian vector
        pnl_vect_rng_normal(g, this->size_, rng);

        // Compute the product of the L x G

        pnl_mat_mult_vect_inplace(gPrime, l, g);

        // Loop for each asset
        for (int d = 0; d < this->size_; d++) {

            // Compute the left part of the sum
            res = (this->r_ - SQR(GET(this->sigma_, d)) / 2) * step;

            // Sum the right part of the sum
            res += GET(this->sigma_, d) * sqrt(step) * GET(gPrime, d);

            res = exp(res) * MGET(path, d, i - 1);

            // Update the result in the output matrix
            pnl_mat_set(path, d, i, res);
        }
    }

    // Free memory
    pnl_mat_free(&l);
    pnl_vect_free(&g);
    pnl_vect_free(&gPrime);
    pnl_mat_free(&tmp);
}

void
BlackScholesModel::shiftAsset(PnlMat* shift_path, const PnlMat* path, int d, double h, double t, double timestep)
{
    // Copy the original trajectory matrix
    // shift_path = pnl_mat_copy(path);

    // Calculate the date
    int date = std::floor(t / timestep);
    if (std::fabs(date * timestep - t) >= 1E-12) {
        date = (t / timestep);
    }

    // Loop for each date
    for (int i = date; i < shift_path->n; i++) {

        // Shift the the value of the asset d at time i by (1+h)
        pnl_mat_set(shift_path, d, i, MGET(shift_path, d, i) * (1 + h));
    }
}

void
BlackScholesModel::simul_market(PnlMat* path, double T, int H, PnlRng* rng)
{
    // Instanciate the vects
    PnlVect* g = pnl_vect_new();
    PnlVect* gPrime = pnl_vect_new();

    // Create the correlation matrix
    PnlMat* l = pnl_mat_create_from_scalar(this->size_, this->size_, this->rho_);
    pnl_mat_set_diag(l, 1, 0);

    // Compute the Cholesky decomposition of the correlation matrix
    pnl_mat_chol(l);

    // Calculate the step
    double step = T / H;

    // Initiate a result value
    double res = 0;

    // copy the spot value into path

    pnl_mat_set_col(path, this->spot_, 0);

    // Loop for each time step
    for (int i = 1; i < H + 1; i++) {

        // Generate the gaussian vector
        pnl_vect_rng_normal(g, this->size_, rng);

        // Compute the product of the L x G
        pnl_mat_mult_vect_inplace(gPrime, l, g);

        // Loop for each asset
        for (int d = 0; d < this->size_; d++) {

            // Compute the left part of the sum
            res = (GET(this->trend, d) - SQR(GET(this->sigma_, d)) / 2) * step;

            // Sum the right part of the sum
            res += GET(this->sigma_, d) * sqrt(step) * GET(gPrime, d);

            // Compute the final result
            res = exp(res) * MGET(path, d, i - 1);

            // Update the result in the output matrix
            pnl_mat_set(path, d, i, res);
        }
    }

    // Free memory
    pnl_mat_free(&l);
    pnl_vect_free(&g);
    pnl_vect_free(&gPrime);
}
