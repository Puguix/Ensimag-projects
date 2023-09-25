#include "MonteCarlo.hpp"
#include <iostream>
#include <cmath>
#include <math.h>

MonteCarlo::MonteCarlo(BlackScholesModel* mod, Option* opt, double fdStep, long nbSamples)
{
    this->opt_ = opt;
    this->mod_ = mod;
    this->fdStep_ = fdStep;
    this->nbSamples_ = nbSamples;
    this->rng_ = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(this->rng_, time(NULL));
}

MonteCarlo::~MonteCarlo()
{
    delete mod_;
    delete opt_;
    pnl_rng_free(&this->rng_);
}

void
MonteCarlo::price(double& price, double& std_dev)
{
    // Initialize price and std_dev
    double somme = 0;
    double estim = 0;

    // Create path for BSM
    PnlMat* path = pnl_mat_create(this->opt_->size_, this->opt_->nbTimeSteps_ + 1);

    // Calcul of the price and std_dev
    for (int i = 0; i < nbSamples_; i++) {
        mod_->asset(path, opt_->T_, opt_->nbTimeSteps_, rng_);
        double payoff = opt_->payoff(path);
        somme += payoff;
        estim += SQR(payoff);
    }

    // Actualize result for std-dev
    estim = estim / (double)nbSamples_ - SQR(somme / (double)nbSamples_);
    estim = estim * exp(-2 * this->mod_->r_ * this->opt_->T_);

    // Actualize result for price
    somme = somme * exp(-this->mod_->r_ * this->opt_->T_) / (double)nbSamples_;

    // Assign results into variable
    std_dev = sqrt(estim) / sqrt(nbSamples_);
    price = somme;

    // Free PNL
    pnl_mat_free(&path);
}

void
MonteCarlo::price(const PnlMat* past, double t, double& price, double& std_dev)
{
    // Initialize price and std_dev
    double somme = 0;
    double estim = 0;

    // Create path for BSM
    PnlMat* path = pnl_mat_create(this->opt_->size_, this->opt_->nbTimeSteps_ + 1);

    // Calcul of the price and std_dev
    for (int i = 0; i < nbSamples_; i++) {
        mod_->asset(path, t, opt_->T_, opt_->nbTimeSteps_, rng_, past);

        double payoff = opt_->payoff(path);

        somme += payoff;
        estim += SQR(payoff);
    }

    // Actualize result for std-dev
    estim = estim / (double)nbSamples_ - SQR(somme / (double)nbSamples_);
    estim = estim * exp(-2 * mod_->r_ * (opt_->T_ - t));

    // Actualize result for price
    somme = somme * exp(-mod_->r_ * (opt_->T_ - t)) / (double)nbSamples_;

    // Assign results into variable
    std_dev = sqrt(estim) / sqrt(nbSamples_);
    price = somme;

    // Free path
    pnl_mat_free(&path);
}

void
MonteCarlo::delta(const PnlMat* past, double t, PnlVect* delta, PnlVect* std_dev)
{
    // Instanciate variables
    double somme;
    double estim;
    double diff_payoff;

    // Instanciate path and shift_path
    PnlMat* path = pnl_mat_create(opt_->size_, opt_->nbTimeSteps_ + 1);
    PnlMat* shift_path;

    // Compute time index
    double dt = opt_->T_ / opt_->nbTimeSteps_;
    int last_rank_past = std::floor(t / dt);
    if (std::fabs(last_rank_past * dt - t) >= 1E-12) {
        last_rank_past = (t / dt) + 1;
    }

    for (int i = 0; i < nbSamples_; i++) {

        // Compute path and instanciate shift_path
        mod_->BlackScholesModel::asset(path, t, opt_->T_, opt_->nbTimeSteps_, rng_, past);
        shift_path = pnl_mat_copy(path);

        // Loop for each asset
        for (int d = 0; d < opt_->size_; d++) {

            // Get previous delta
            somme = GET(delta, d);
            estim = GET(std_dev, d);

            mod_->BlackScholesModel::shiftAsset(shift_path, path, d, this->fdStep_, t, dt);

            diff_payoff = opt_->payoff(shift_path);
            mod_->BlackScholesModel::shiftAsset(shift_path, path, d, 1 / (1 + this->fdStep_) - 1, t, dt);

            mod_->BlackScholesModel::shiftAsset(shift_path, path, d, -this->fdStep_, t, dt);
            diff_payoff -= opt_->payoff(shift_path);
            mod_->BlackScholesModel::shiftAsset(shift_path, path, d, 1 / (1 - this->fdStep_) - 1, t, dt);

            somme += diff_payoff;
            estim += SQR(diff_payoff);

            // Update the vects
            pnl_vect_set(delta, d, somme);
            pnl_vect_set(std_dev, d, estim);
        }

        // Free shift_path
        pnl_mat_free(&shift_path);
    }

    // Loop for each asset
    for (int d = 0; d < opt_->size_; d++) {

        // Update variables
        estim = GET(std_dev, d);
        somme = GET(delta, d);

        // Compute variables and assign them in vects
        somme = somme / (double)nbSamples_;
        estim = estim / (double)nbSamples_;
        estim -= SQR(somme);
        estim = estim * exp(-2 * mod_->r_ * (opt_->T_ - t)) / (double)SQR(MGET(past, d, last_rank_past)) / (double)SQR(this->fdStep_) / 4.0;
        pnl_vect_set(std_dev, d, sqrt(estim / (double)nbSamples_));
        somme = somme * exp(-mod_->r_ * (opt_->T_ - t)) / (double)MGET(past, d, last_rank_past) / (double)this->fdStep_ / 2.0;
        pnl_vect_set(delta, d, somme);
    }

    pnl_mat_free(&path);
    pnl_mat_free(&shift_path);
}

void
MonteCarlo::delta(PnlVect* delta, PnlVect* std_dev)
{
    double somme;
    double estim;
    double diff_payoff;
    PnlMat* path = pnl_mat_create(opt_->size_, opt_->nbTimeSteps_ + 1);
    PnlMat* shift_path;
    double dt = opt_->T_ / opt_->nbTimeSteps_;

    for (int i = 0; i < nbSamples_; i++) {
        mod_->BlackScholesModel::asset(path, opt_->T_, opt_->nbTimeSteps_, rng_);
        shift_path = pnl_mat_copy(path);

        for (int d = 0; d < opt_->size_; d++) {
            somme = GET(delta, d);
            estim = GET(std_dev, d);

            mod_->BlackScholesModel::shiftAsset(shift_path, path, d, this->fdStep_, 0, dt);
            diff_payoff = opt_->payoff(shift_path);
            mod_->BlackScholesModel::shiftAsset(shift_path, path, d, 1 / (1 + this->fdStep_) - 1, 0, dt);

            mod_->BlackScholesModel::shiftAsset(shift_path, path, d, -this->fdStep_, 0, dt);
            diff_payoff -= opt_->payoff(shift_path);
            mod_->BlackScholesModel::shiftAsset(shift_path, path, d, 1 / (1 - this->fdStep_) - 1, 0, dt);

            somme += diff_payoff;
            estim += SQR(diff_payoff);

            pnl_vect_set(delta, d, somme);
            pnl_vect_set(std_dev, d, estim);
        }
        pnl_mat_free(&shift_path);
    }

    for (int d = 0; d < opt_->size_; d++) {
        estim = GET(std_dev, d);
        somme = GET(delta, d);
        somme = somme / (double)nbSamples_;
        estim = estim / (double)nbSamples_;
        estim -= SQR(somme);
        estim = estim * exp(-2 * mod_->r_ * (opt_->T_)) / (double)SQR(GET(mod_->spot_, d)) / (double)SQR(this->fdStep_) / 4.0;
        pnl_vect_set(std_dev, d, sqrt(estim / (double)nbSamples_));
        somme = somme * exp(-mod_->r_ * (opt_->T_)) / (double)GET(mod_->spot_, d) / (double)this->fdStep_ / 2.0;
        pnl_vect_set(delta, d, somme);
    }

    pnl_mat_free(&path);
    pnl_mat_free(&shift_path);
}

HedgingResults*
MonteCarlo::profit_loss(const PnlMat* dataMarket, int H)
{
    // Instanciate variables
    double prix = 0;
    double std_dev = 0;

    // Create vects
    PnlVect* currentDelta = pnl_vect_create(this->mod_->size_);
    PnlVect* std_devVect = pnl_vect_create(this->mod_->size_);
    PnlVect* previousDelta = pnl_vect_create(this->mod_->size_);
    PnlVect* resultMinus = pnl_vect_create(this->mod_->size_);
    PnlVect* CurrentStock = pnl_vect_create(this->mod_->size_);

    // on calcule la valeur du portefeuille en 0
    price(prix, std_dev);
    double ValuePortfolio = prix;
    delta(currentDelta, std_devVect);

    ValuePortfolio -= pnl_vect_scalar_prod(currentDelta, this->mod_->spot_);

    // on copie les ancienns valeurs de delta pour le calcul de la boucle
    previousDelta = pnl_vect_copy(currentDelta);
    // on créé la matrice past et on remplie les prix en 0
    PnlMat* past = pnl_mat_create_from_zero(opt_->size_, opt_->nbTimeSteps_ + 1);
    pnl_mat_set_col(past, this->mod_->spot_, 0);

    // on stock à quel rang de past on rempli
    int rang_remplissage = 1;

    double step = opt_->T_ / (double)H;
    double t;
    double dt = opt_->T_ / opt_->nbTimeSteps_;

    for (int i = 1; i < H + 1; i++) {
        t = step * i;

        rang_remplissage = std::floor(t / dt);
        if (std::fabs(rang_remplissage * dt - t) >= 1E-12) {
            rang_remplissage = (t / dt) + 1;
        }
        pnl_mat_get_col(CurrentStock, dataMarket, i);
        // on remplis la matrice past
        pnl_mat_set_col(past, CurrentStock, rang_remplissage);

        // on actualise les delta
        delta(past, t, currentDelta, std_devVect);

        // on copie le vecteur delta actuel
        resultMinus = pnl_vect_copy(currentDelta);
        pnl_vect_minus_vect(resultMinus, previousDelta);

        ValuePortfolio = ValuePortfolio * exp(mod_->r_ * opt_->T_ / H) - pnl_vect_scalar_prod(resultMinus, CurrentStock);

        // on conserve les valeurs de delta pour le prochain tour de boucle
        pnl_vect_free(&previousDelta);
        previousDelta = pnl_vect_copy(currentDelta);
        pnl_vect_free(&resultMinus);
    }

    // Compute results
    double payoff = this->opt_->payoff(past);
    double error = ValuePortfolio + pnl_vect_scalar_prod(currentDelta, CurrentStock) - payoff;

    // Create results
    HedgingResults* hedgingResults = new HedgingResults(prix, std_dev, error);

    // Free vects and mats
    pnl_vect_free(&currentDelta);
    pnl_vect_free(&std_devVect);
    pnl_vect_free(&previousDelta);
    pnl_vect_free(&resultMinus);
    pnl_vect_free(&CurrentStock);
    pnl_mat_free(&past);

    return hedgingResults;
}