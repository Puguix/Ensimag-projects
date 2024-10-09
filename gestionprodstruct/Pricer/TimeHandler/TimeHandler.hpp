#pragma once

#include <pnl/pnl_vector.h>

class TimeHandler {
public:
    PnlVect *ConstatationDates_;
    int nbDaysInYear_;
    int nbrDates_;

    TimeHandler(PnlVect* constatationDates, int nbDaysInYear);
    double get_date_t_i(int i);
    int getNextIndexConstatation(double t);
    bool isMonitoringDate(double date);
    int pastMatrixLastIndex(bool isMonitoringDate, int index);
    ~TimeHandler(){
        pnl_vect_free(&ConstatationDates_);
    }
};