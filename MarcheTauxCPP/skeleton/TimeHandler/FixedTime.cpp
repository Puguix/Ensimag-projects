#include "FixedTime.hpp"

FixedTime::FixedTime(int period, int nbrConstationDates, int nbDaysInYear) {
    period_ = period;
    nbrDates_= nbrConstationDates;
    nbDaysInYear_=nbDaysInYear;
    this->ConstatationDates_ = pnl_vect_create(nbrConstationDates);
    for(int i = 0; i < nbrDates_; i++){
        pnl_vect_set(ConstatationDates_, i,  i*period);
    }
}

double FixedTime::get_date_t_i(int i) {
    return i*period_;
}

int FixedTime::getClosestIndexConstatation(double t) {
    return (int) (t/period_)+1;
}

bool FixedTime::isMonitoringDate(int date) {
    return (date%period_) == 0;
}
