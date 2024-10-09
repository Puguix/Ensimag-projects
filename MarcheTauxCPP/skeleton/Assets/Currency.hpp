#pragma once

#include "RiskyAsset.hpp"

class Currency : public RiskyAsset{
public:
    double interestRate_;
    Currency(double domesticInterestRate, double interestRate, double volatilite, PnlVect* CorrLine);
    ~Currency(){};
};
