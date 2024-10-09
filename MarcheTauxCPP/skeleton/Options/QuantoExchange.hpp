#include "Option.hpp"

class QuantoExchange: public Option
{
public:
    double strike_; /*! strike de l'option */

    QuantoExchange(double T, vector<int> assetCurrencyMapping, double strike,
                   double domesticInterestRate, vector<double> foreignInterestRates);
    double payoff(const PnlMat *path) override;
    ~QuantoExchange(){};
};