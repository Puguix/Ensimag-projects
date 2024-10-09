#pragma once

#include <list>
#include <pnl/pnl_matvect.h>
#include <nlohmann/json.hpp>
#include "MonteCarlo.hpp"
using namespace std;

class Position {
public:
    int date;
    PnlVect *deltas;
    PnlVect *deltasStdDev;
    double price;
    double priceStdDev;
    double portfolioValue;

    Position(int date, double price, double priceStdDev, PnlVect* deltas, PnlVect* deltasStdDev, double portfolioValue);
    friend void to_json(nlohmann::json &j, const Position &positions);
    void print() const;

};

class Portfolio {
public:
    list<Position> positions;

    int lastUpdateDate;
    int numberDaysYear;
    double quantiteSansRisque;
    double domesticInterestRate;
    double portfolioValue;
    PnlVect* deltas;

    Portfolio(double domesticInterestRate, int numberDaysYear, PnlVect *spots, PnlVect *deltas, PnlVect* deltasStdDev, double price, double priceStdDev);
    double computeValueAndUpdate(int actualDate, PnlVect* deltas, PnlVect* marketData);
    ~Portfolio(){
        pnl_vect_free(&deltas);
        for (auto& obj : positions) {
            obj.~Position();
        }
    };
};
