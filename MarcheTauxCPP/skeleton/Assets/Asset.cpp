#include "Asset.hpp"

Asset::Asset(double domesticInterestRate, double volatilite, PnlVect* CorrLine, Currency* currency, bool isDomestic){
    domesticInterestRate_ = domesticInterestRate;
    volatilityVector_= pnl_vect_new();
    pnl_vect_clone(volatilityVector_, CorrLine);
    pnl_vect_mult_scalar(volatilityVector_, volatilite);
    if(not isDomestic) {
        pnl_vect_plus_vect(volatilityVector_, currency->volatilityVector_);
    }
    double norm = pnl_vect_norm_two(volatilityVector_);
    drift_= domesticInterestRate - norm*norm/2 ;
}