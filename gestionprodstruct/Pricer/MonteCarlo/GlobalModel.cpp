#include "GlobalModel.hpp"


GlobalModel::GlobalModel(const vector<RiskyAsset*> riskyAssets, TimeHandler* timeHandler)
{
    riskyAssets_ = riskyAssets;
    timeHandler_ = timeHandler;
}

void GlobalModel::asset(PnlMat* path, double t, const PnlMat* past, PnlRng* rng, bool isMonitoringDate){
    double stepDuration;
    int nbAssets = riskyAssets_.size();
    PnlVect* G= pnl_vect_create(nbAssets);
    //calculate the index i+1 of t where t_i <= t< t_i+1
    int  nextIndiceConstat = timeHandler_->getNextIndexConstatation(t);
    //copy values of the past Matrix until the last monitoring date lower than t: t_i
    copyMatrixValues(path , past, nextIndiceConstat , nbAssets);
    //handle the last index of the past Matrix for simulation
    int lastIdx = timeHandler_->pastMatrixLastIndex(isMonitoringDate, nextIndiceConstat);
    //Simulate asset of t_(i+1) from t
    pnl_vect_rng_normal(G, nbAssets, rng);
    if(nextIndiceConstat < timeHandler_->nbrDates_) {
        stepDuration = (timeHandler_->get_date_t_i(nextIndiceConstat)-t)/timeHandler_->nbDaysInYear_;
        for (int j=0; j<nbAssets; j++) {
            riskyAssets_[j]->asset(path, nextIndiceConstat, j, pnl_mat_get(past, lastIdx, j), stepDuration, G);
        }
    }
    //Simulate the rest of the path
    for(int i= nextIndiceConstat + 1; i<timeHandler_->nbrDates_; i++){
        stepDuration = (timeHandler_->get_date_t_i(i)- timeHandler_->get_date_t_i(i-1))/timeHandler_->nbDaysInYear_;
        pnl_vect_rng_normal(G, nbAssets, rng);
        for (int j=0; j<nbAssets; j++){
            riskyAssets_[j]->asset(path, i, j, pnl_mat_get(path, i-1, j), stepDuration, G);
        }
    }
    pnl_vect_free(&G);

}

void GlobalModel::shiftAsset(PnlMat* shift_path, const PnlMat* path, int d, double h, double t, bool isMonitoringDate){
    int lastIdx = timeHandler_->pastMatrixLastIndex(isMonitoringDate,timeHandler_->getNextIndexConstatation(t));
    if(t==0){ lastIdx+=1;}
    copyMatrixValues(shift_path, path, lastIdx, path->n);

    for(int i=lastIdx; i < path->m; i++){
        for(int j=0; j<path->n; j++) {
            if (j == d) {
                pnl_mat_set(shift_path, i, j, (1 + h) * pnl_mat_get(path, i, j));
            } else {
                pnl_mat_set(shift_path, i,j, pnl_mat_get(path, i,j));
            }
        }
    }
}

void GlobalModel::copyMatrixValues(PnlMat* matrixTarget , const PnlMat* matrixToCopy, int nDate, int nAsset){
    for(int i=0; i< nDate ; i++){
        for (int j=0; j<nAsset; j++){
            pnl_mat_set(matrixTarget, i, j, pnl_mat_get(matrixToCopy, i, j));
        }
    }
}

