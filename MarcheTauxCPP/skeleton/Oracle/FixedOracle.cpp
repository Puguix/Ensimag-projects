#include "FixedOracle.hpp"


FixedOracle::FixedOracle(int period) : period_(period){}

bool FixedOracle::IsRebalancingDate(int date) {
    this->compteur_++;
    if(compteur_ == period_){
        compteur_ = 0;
        return true;
    }
    return false;
}

