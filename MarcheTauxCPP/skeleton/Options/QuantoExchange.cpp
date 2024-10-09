#include "QuantoExchange.hpp"


QuantoExchange::QuantoExchange(double T, vector<int> assetCurrencyMapping, double strike, double domesticInterestRate, vector<double> foreignInterestRates) {
    this->T_ = T;
    this->assetCurrencyMapping_ = assetCurrencyMapping;
    this->domesticInterestRate_ = domesticInterestRate;
    this->foreignInterestRates_ = foreignInterestRates;
    this->strike_ = strike;
}

double QuantoExchange::payoff(const PnlMat *path) {
    double payoff = pnl_mat_get(path, path->m-1, 0);
    payoff -= pnl_mat_get(path, path->m-1, 1);
    return (payoff - this->strike_ > 0) ? payoff - this->strike_ : 0;
}
