#include "Currency.hpp"

Currency::Currency(double domesticInterestRate, double interestRate, double volatilite, PnlVect* CorrLine){
    domesticInterestRate_ = domesticInterestRate; //r_d
    interestRate_ = interestRate; //r_f
    volatilityVector_ = pnl_vect_new();
    pnl_vect_clone(volatilityVector_,CorrLine);
    pnl_vect_mult_scalar(volatilityVector_, volatilite);
    double norm = pnl_vect_norm_two(volatilityVector_);
    drift_= domesticInterestRate - norm*norm/2 ; //drift de X*e**(r_f*t)
}