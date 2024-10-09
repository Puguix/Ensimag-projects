#pragma once

#include "TimeHandler.hpp"

class GridTime : public TimeHandler{
public:
    int lastClosestIndex;

    GridTime(PnlVect* constatationDates, int nbDaysInYear);
    double get_date_t_i(int i) override;
    int getClosestIndexConstatation(double t) override;
    bool isMonitoringDate(int date) override;
    ~GridTime(){};
};
