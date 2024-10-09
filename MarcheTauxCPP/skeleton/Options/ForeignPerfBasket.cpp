#include "ForeignPerfBasket.hpp"
#include <limits>
#include <cmath>


ForeignPerfBasket::ForeignPerfBasket(string domesticCurrencyId, double T, vector<int> assetCurrencyMapping,
                                     map<string, vector<int>> marketsAssets, double strike, double domesticInterestRate,
                                     vector<double> foreignInterestRates, PnlVect* constatDates, int nbOfDaysPerYear) {
    this->assetCurrencyMapping_ = assetCurrencyMapping;
    this->domesticInterestRate_ = domesticInterestRate;
    this->foreignInterestRates_ = foreignInterestRates;
    this->domesticCurrencyId_ = domesticCurrencyId;
    this->nbOfDaysPerYear_ = nbOfDaysPerYear;
    this->marketsAssets_ = marketsAssets;
    this->constatDates_ = constatDates;
    this->strike_ = strike;
    this->T_ = T;
}


double ForeignPerfBasket::payoff(const PnlMat *path) {
    double max_ratio = - numeric_limits<float>::infinity(), mean_dom = 0, mean_foreign = 0;
    int nbAssets = assetCurrencyMapping_.size();
    string maxRatioCurrencyId;

    for(auto market : marketsAssets_){

        // Sommes des valeurs des actifs aux temps t1 et t2
        double sum_foreign_t1 = 0;
        double sum_foreign_t2 = 0;
        // Boucle sur les actifs de la devise i
        for(int index : market.second){
            // Pour récuperer le bon foreign interest rate il suffit de savoir la position du taux de change
            // dans la matrice past: assetCurrencyMapping_[index] et la soustraire du nombre total des assets
            // ce qui nous donnera sa position dans le vecteur des foreign interest rates
            if(assetCurrencyMapping_[index] != -1) {
                sum_foreign_t1 += (double) pnl_mat_get(path, 0, index) /
                                  (  pnl_mat_get(path, 0, assetCurrencyMapping_[index]) *
                                        exp( (double) -foreignInterestRates_[assetCurrencyMapping_[index] - nbAssets] *
                                        pnl_vect_get(constatDates_, 0) / nbOfDaysPerYear_
                                            )
                                   );
                sum_foreign_t2 += (double) pnl_mat_get(path, 1, index) /
                                  (pnl_mat_get(path, 1, assetCurrencyMapping_[index]) *
                                        exp((double) -foreignInterestRates_[assetCurrencyMapping_[index] - nbAssets] *
                                        pnl_vect_get(constatDates_, 1) / nbOfDaysPerYear_
                                            )
                                   );
            }
        }

        double ratio = sum_foreign_t2 / sum_foreign_t1;
        if(ratio > max_ratio){
            max_ratio = ratio;
            maxRatioCurrencyId = market.first;
        }
    }
    for(int index : marketsAssets_[domesticCurrencyId_]){
        mean_dom += pnl_mat_get(path, path->m - 1, index);
    }
    mean_dom /= marketsAssets_[domesticCurrencyId_].size();

    for(int index : marketsAssets_[maxRatioCurrencyId]){
        mean_foreign += pnl_mat_get(path, path->m - 1, index);
    }
    mean_foreign /= marketsAssets_[maxRatioCurrencyId].size();

    return (mean_foreign - mean_dom - strike_ > 0)? mean_foreign - mean_dom - strike_ : 0;
}


