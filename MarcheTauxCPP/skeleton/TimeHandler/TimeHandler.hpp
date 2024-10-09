#pragma once

#include <pnl/pnl_vector.h>

class TimeHandler {
public:
    PnlVect *ConstatationDates_;
    int nbDaysInYear_;
    int nbrDates_;

    virtual double get_date_t_i(int i) = 0;
    virtual int getClosestIndexConstatation(double t) = 0;
    virtual bool isMonitoringDate(int date) = 0;
    static int monitoringHandleIndex(bool isMonitoringDate, int indiceConstat);
    virtual ~TimeHandler(){
        pnl_vect_free(&ConstatationDates_);
    }
};
