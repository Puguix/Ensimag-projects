#include "Option.hpp"

class ForeignAsian: public Option
{
public:

    ForeignAsian(double T, vector<int> assetCurrencyMapping, double domesticInterestRate, vector<double> foreignInterestRates);
    double payoff(const PnlMat *path) override;
    ~ForeignAsian(){};
};