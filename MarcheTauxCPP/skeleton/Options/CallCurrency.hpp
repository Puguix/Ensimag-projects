#include "Option.hpp"

class CallCurrency: public Option
{
public:
    double strike_; /*! strike de l'option */

    CallCurrency(double T, vector<int> assetCurrencyMapping, double strike,
                 double domesticInterestRate, vector<double> foreignInterestRates);
    double payoff(const PnlMat *path) override;
    ~CallCurrency(){};
};