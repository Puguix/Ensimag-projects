#pragma once

#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"
#include "../TimeHandler/TimeHandler.hpp"

using namespace std;


class eurostralProduct
{
public:

    int maturity;
    double domesticRate;
    double numberDaysYear;
    PnlVect* constaDates;
    PnlVect* interestRates;


    eurostralProduct(int maturity, PnlVect* interestRates, TimeHandler* timeHandler);

    /**
     * Calcule la valeur du payoff sur la trajectoire
     *
     * @param[in] path est une matrice de taille (dates_+1) x size_
     * contenant une trajectoire du modèle telle que créée
     * par la fonction asset.
     * @return payoff
     */
    double payoff(const PnlMat *currentPath, int currentDate);

    double dividend(const PnlMat *currentPath, int currentDate);

    double discount(double value, double maturityInDays, double date);

    int getCurrentDateIndex(const PnlMat* path, int currentDate);

    PnlMat* adjustPathMatrix(const PnlMat* path);

    ~eurostralProduct() {}
};


