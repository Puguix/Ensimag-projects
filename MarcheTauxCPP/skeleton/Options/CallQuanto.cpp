#include "CallQuanto.hpp"
#include <cmath>

CallQuanto::CallQuanto(double T, vector<int> assetCurrencyMapping, double strike, double domesticInterestRate,
                       vector<double> foreignInterestRates) {
    this->T_ = T;
    this->assetCurrencyMapping_ = assetCurrencyMapping;
    this->strike_ = strike;
    this->domesticInterestRate_ = domesticInterestRate;
    this->foreignInterestRates_ = foreignInterestRates;
}

double CallQuanto::payoff(const PnlMat *path) {
    double asset = pnl_mat_get(path, path->m-1, 0);
    return (asset - this->strike_ > 0) ? asset - this->strike_ : 0;
}
