#include "TimeHandler.hpp"

TimeHandler::TimeHandler(PnlVect* constatationDates, int nbDaysInYear){
    ConstatationDates_ = constatationDates; // [t_0, t_1, t_2, t_3, t_4, t_c]
    nbrDates_ = constatationDates->size;  //= 6
    nbDaysInYear_=nbDaysInYear;
}

double TimeHandler::get_date_t_i(int i) {
    return GET(ConstatationDates_, i);
}

int TimeHandler::getNextIndexConstatation(double t) {
    int index = 0;
    while(index < ConstatationDates_->size && t>= GET(ConstatationDates_,index)){
        index +=1;
    }
    return index;
}

bool TimeHandler::isMonitoringDate(double date) {
    for(int i = 0; i < ConstatationDates_->size; i++){
        if(pnl_vect_get(ConstatationDates_, i) == date){
            return true;
        }
    }
    return false;
}

int TimeHandler::pastMatrixLastIndex(bool isMonitoringDate, int index) {
    if(isMonitoringDate) {
        return index-1;
    } else {
        return index;
    }
}