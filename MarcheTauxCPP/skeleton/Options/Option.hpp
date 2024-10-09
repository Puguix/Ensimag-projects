#pragma once

#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"
#include "vector"
using namespace std;

/// \brief Classe Option abstraite
class Option
{
public:
    double T_; /*! maturité en années */
    double domesticInterestRate_; /*! le taux d'intérêts domestique */
    vector<double> foreignInterestRates_; /*! les taux d'intérêts étrangers */
    vector<int> assetCurrencyMapping_;

    /**
     * Calcule la valeur du payoff sur la trajectoire
     *
     * @param[in] path est une matrice de taille (dates_+1) x size_
     * contenant une trajectoire du modèle telle que créée
     * par la fonction asset.
     * @return payoff
     */
    virtual double payoff(const PnlMat *path) = 0;

    virtual ~Option() {}
};


