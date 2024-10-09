#include "Option.hpp"
#include <fstream>
#include <map>

class ForeignPerfBasket: public Option
{
public:
    int nbOfDaysPerYear_; /*! nombre de jours par année */
    double strike_; /*! strike de l'option */
    string domesticCurrencyId_;  /*! id (nom) de la devise du marché domestique */
    map<string, vector<int>> marketsAssets_; /*! associe à chaque devise une liste des indices de ses actifs */
    PnlVect* constatDates_; /*! dates de constations (pour mesure les performances) */

    ForeignPerfBasket(string domesticCurrencyId, double T, vector<int> assetCurrencyMapping,
                      map<string, vector<int>> marketsAssets, double strike, double domesticInterestRate,
                      vector<double> foreignInterestRates, PnlVect* constatDates, int nbOfDaysPerYear);
    double payoff(const PnlMat *path) override;
    ~ForeignPerfBasket(){
        pnl_vect_free(&constatDates_);
    }
};