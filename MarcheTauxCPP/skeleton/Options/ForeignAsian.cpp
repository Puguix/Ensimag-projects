#include "ForeignAsian.hpp"


ForeignAsian::ForeignAsian(double T, vector<int> assetCurrencyMapping,
                           double domesticInterestRate, vector<double> foreignInterestRates) {
    this->T_ = T;
    this->assetCurrencyMapping_ = assetCurrencyMapping;
    this->domesticInterestRate_ = domesticInterestRate;
    this->foreignInterestRates_ = foreignInterestRates;
}

double ForeignAsian::payoff(const PnlMat *path) {
    PnlVect* assetCol = pnl_vect_create(path->m);
    pnl_mat_get_col(assetCol, path, path->n-2);

    double payoff = (double) 1/path->m * pnl_vect_sum(assetCol);
    double strike = pnl_mat_get(path, path->m - 1, 0);
    return (payoff - strike > 0) ? payoff - strike : 0;
}
