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
    //calculate the index i of t where t_i <= t< t_i+1 (index i starting from 1)
    int  indiceConstat = timeHandler_->getClosestIndexConstatation(t);
    //copy values of the past Matrix until the last monitoring date lower than t: t_i
    copyMatrixValues(path , past, indiceConstat , nbAssets);
    //handle the last index of the past Matrix for simulation
    int lastIdx = timeHandler_->monitoringHandleIndex(isMonitoringDate, indiceConstat);
    //Simulate asset of t_(i+1) from t
    pnl_vect_rng_normal(G, nbAssets, rng);
    if(indiceConstat < timeHandler_->nbrDates_) {
        stepDuration = (timeHandler_->get_date_t_i(indiceConstat)-t)/timeHandler_->nbDaysInYear_;
        for (int j=0; j<nbAssets; j++) {
            riskyAssets_[j]->asset(path, indiceConstat, j, pnl_mat_get(past, lastIdx, j), stepDuration, G);
        }
    }
    //Simulate the rest of the path
    for(int i= indiceConstat + 1; i<timeHandler_->nbrDates_; i++){
        stepDuration = (timeHandler_->get_date_t_i(i)- timeHandler_->get_date_t_i(i-1))/timeHandler_->nbDaysInYear_;
        pnl_vect_rng_normal(G, nbAssets, rng);
        for (int j=0; j<nbAssets; j++){
            riskyAssets_[j]->asset(path, i, j, pnl_mat_get(path, i-1, j), stepDuration, G);
        }
    }
    pnl_vect_free(&G);

}

void GlobalModel::shiftAsset(PnlMat* shift_path, const PnlMat* path, int d, double h, double t, bool isMonitoringDate){
    int lastIdx = timeHandler_->monitoringHandleIndex(isMonitoringDate,timeHandler_->getClosestIndexConstatation(t));
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

double GlobalModel::discount(double value, double maturityInYears, double t, double rate){

    return exp(-rate* (maturityInYears -  ((double)t/timeHandler_->nbDaysInYear_)))* value;
}


void GlobalModel::copyMatrixValues(PnlMat* matrixTarget , const PnlMat* matrixToCopy, int nDate, int nAsset){
    for(int i=0; i< nDate ; i++){
        for (int j=0; j<nAsset; j++){
            pnl_mat_set(matrixTarget, i, j, pnl_mat_get(matrixToCopy, i, j));
        }
    }
}

