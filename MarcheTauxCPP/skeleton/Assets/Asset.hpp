#pragma once

#include "Currency.hpp"


class Asset : public RiskyAsset {
public:
    Asset(double domesticInterestRate, double volatilite, PnlVect* CorrLine, Currency* currency, bool isDomestic);
    ~Asset(){};
};
