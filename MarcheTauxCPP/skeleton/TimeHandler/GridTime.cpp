#include "GridTime.hpp"

GridTime::GridTime(PnlVect* constatationDates, int nbDaysInYear){
    ConstatationDates_ = constatationDates;
    nbrDates_ = constatationDates->size;
    nbDaysInYear_=nbDaysInYear;
    lastClosestIndex = 0;
}

double GridTime::get_date_t_i(int i) {
    return GET(ConstatationDates_, i);
}

int GridTime::getClosestIndexConstatation(double t) {
    while(lastClosestIndex < ConstatationDates_->size && t>= GET(ConstatationDates_,lastClosestIndex)){
        lastClosestIndex +=1;
    }
    return lastClosestIndex;
}

bool GridTime::isMonitoringDate(int date) {
    for(int i = 0; i < ConstatationDates_->size; i++){
        if(pnl_vect_get(ConstatationDates_, i) == date){
            return true;
        }
    }
    return false;
}