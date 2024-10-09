#include "Option.hpp"

class CallQuanto: public Option
{
public:
    double strike_; /*! strike de l'option */

    CallQuanto(double T, vector<int> assetCurrencyMapping, double strike,
               double domesticInterestRate, vector<double> foreignInterestRates);
    double payoff(const PnlMat *path) override;
    ~CallQuanto(){};
};