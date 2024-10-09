#pragma once

#include "TimeHandler.hpp"

class FixedTime : public TimeHandler {
public:
    int period_;
    FixedTime(int period, int nbrConstationDates, int nbDaysInYear);
    double get_date_t_i(int i) override;
    int getClosestIndexConstatation(double t) override;
    bool isMonitoringDate(int date) override;
    ~FixedTime(){};
};
