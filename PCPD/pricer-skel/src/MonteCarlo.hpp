#pragma once

#include "Option.hpp"
#include "pnl/pnl_random.h"
#include "pnl/pnl_mathtools.h"
#include "pnl/pnl_matrix.h"
#include "BlackScholesModel.hpp"
#include "HedgingResults.hpp"

class MonteCarlo
{
  public:
    BlackScholesModel* mod_; /*! pointeur vers le modèle */
    Option* opt_;            /*! pointeur sur l'option */
    PnlRng* rng_;            /*! pointeur sur le générateur */
    double fdStep_;          /*! pas de différence finie */
    long nbSamples_;         /*! nombre de tirages Monte Carlo */

    MonteCarlo(BlackScholesModel* mod, Option* opt, double fdStep, long nbSamples);
    ~MonteCarlo();
    /**
     * Calcule le prix de l'option à la date 0
     *
     * @param[out] prix valeur de l'estimateur Monte Carlo
     * @param[out] std_dev écart type de l'estimateur
     */
    void price(double& prix, double& std_dev);

    /**
     * Calcule le prix de l'option à la date t
     *
     * @param[in]  past contient la trajectoire du sous-jacent
     * jusqu'à l'instant t
     * @param[in] t date à laquelle le calcul est fait
     * @param[out] prix contient le prix
     * @param[out] std_dev contient l'écart type de l'estimateur
     */
    void price(const PnlMat* past, double t, double& prix, double& std_dev);

    /**
     * Calcule le delta de l'option à la date t
     *
     * @param[in] past contient la trajectoire du sous-jacent
     * jusqu'à l'instant t
     * @param[in] t date à laquelle le calcul est fait
     * @param[out] delta contient le vecteur de delta
     * @param[out] std_dev contient l'écart type de l'estimateur
     */
    void delta(const PnlMat* past, double t, PnlVect* delta, PnlVect* std_dev);

    /**
     * Calcule le delta de l'option à la date 0
     *
     * @param[out] delta contient le vecteur de delta
     * @param[out] std_dev contient l'écart type de l'estimateur
     */
    void delta(PnlVect* delta, PnlVect* std_dev);

    /**
     * retourne les profits et les pertes de la couverture
     * le long d’une trajectoire de marché
     * @param[in]  path contient la trajectoire du sous-jacent
     * @param[out] delta contient le vecteur de delta
     * @param[out] std_dev contient l'écart type de l'estimateur
     */
    HedgingResults* profit_loss(const PnlMat* path, int H);
};
