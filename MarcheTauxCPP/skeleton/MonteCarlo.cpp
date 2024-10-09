#include <cmath>
#include "MonteCarlo.hpp"
#include "pnl/pnl_random.h"
#include <ctime>
using namespace std;

MonteCarlo::MonteCarlo(double nbSamples, GlobalModel* bsModel, Option *opt, double dfStep) {
    nbrSample_ = nbSamples;
    model_ = bsModel;
    option_ = opt;
    fdStep_ = dfStep;
    rng_ = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(rng_, time(NULL));
}


void MonteCarlo::priceAndDelta(const PnlMat* past, double t, double& prix, double& std_dev, PnlVect* deltas, PnlVect* std_deltas, bool isMonitoringDate)
{
    ///initialisations paths
    PnlMat* path = pnl_mat_create(model_->timeHandler_->nbrDates_ , past->n);
    PnlMat* shift_path_plus = pnl_mat_create(model_->timeHandler_->nbrDates_, past->n);
    PnlMat* shift_path_minus = pnl_mat_create(model_->timeHandler_->nbrDates_, past->n);
    prix = 0;
    std_dev = 0;
    double optionPayoff;
    double payoffsShifted;
    /// Pricing and deltas for t>0
    for (int i = 0; i < nbrSample_; i++) {
        model_->asset(path, t,past, rng_, isMonitoringDate);
        optionPayoff =model_->discount(option_->payoff(path),option_->T_, t, option_->domesticInterestRate_);
        prix += optionPayoff;
        std_dev += optionPayoff * optionPayoff;
        /// for deltas
        for(int asset  = 0; asset < past->n ;asset++) {
            model_->shiftAsset(shift_path_plus, path, asset, fdStep_, t, isMonitoringDate);
            model_->shiftAsset(shift_path_minus, path, asset, - fdStep_, t, isMonitoringDate);
            payoffsShifted= model_->discount(option_->payoff(shift_path_plus) - option_->payoff(shift_path_minus), option_->T_, t, option_->domesticInterestRate_);
            pnl_vect_set(deltas, asset, pnl_vect_get(deltas, asset) + payoffsShifted);
            //for std_deltas computation
            pnl_vect_set(std_deltas, asset, pnl_vect_get(std_deltas, asset) + payoffsShifted*payoffsShifted);
        }
    }
    prix /= nbrSample_;
    std_dev= sqrt(abs(std_dev/nbrSample_ - prix*prix)/nbrSample_) ;

    PnlVect* st = pnl_vect_create(past->n);
    pnl_mat_get_row(st, past,  past->m -1);
    for (int asset = 0; asset< past->n; asset++) {
        pnl_vect_set(deltas, asset, GET(deltas,asset)/(2*nbrSample_* GET(st, asset)*fdStep_));
        double variance = GET(std_deltas,asset)/(4*nbrSample_*fdStep_ *fdStep_* GET(st, asset) * GET(st, asset))- GET(deltas, asset)*
                                                                                                                  GET(deltas, asset);
        pnl_vect_set(std_deltas, asset, sqrt(abs(variance)/ nbrSample_));
    }
    pnl_mat_free(&shift_path_minus);
    pnl_mat_free(&shift_path_plus);
    pnl_mat_free(&path);
    pnl_vect_free(&st);
}


