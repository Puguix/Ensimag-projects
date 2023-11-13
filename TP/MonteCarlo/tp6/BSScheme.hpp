// vim: set sw=4 ts=4 sts=4:
#pragma once

#include "pnl/pnl_vector.h"

class BSScheme
{
public:
    BSScheme(double maturity, double volatility, double interest_rate, double spot, int dates);
    double m_maturity;
    double m_volatility;
    double m_interest_rate;
    double m_spot;
    double m_drift_bs;
    double m_dt;
    double m_sqrt_dt;
    double m_discount;

    /**
     * Construire une trajectoire du modèle de Black Scholes sur la grille régulière de pas T/n en
     * utilisant la méthode de simulation exacte.
     *
     * @param G vecteur des accroissements renormalisés (gaussiennes centrées réduites)
     * @param n nombre de pas de temps
     * @param[out] path contient la trajectoire simulée en sortie.
     */
    void simulExact(PnlVect *path, const PnlVect *G, int n) const;

    virtual void simul(PnlVect *path, const PnlVect *G, int n) const = 0;
};

class BSEuler : public BSScheme
{
public:
    BSEuler(double maturity, double volatility, double interest_rate, double spot, int dates);
    /**
     * Construire une trajectoire du modèle de Black Scholes sur la grille régulière de pas T/n en
     * utilisant le schéma d'Euler.
     *
     * @param G vecteur des accroissements renormalisés (gaussiennes centrées réduites)
     * @param n nombre de pas de temps
     * @param[out] path contient la trajectoire simulée en sortie.
     */
    virtual void simul(PnlVect *path, const PnlVect *G, int n) const;
};

class BSMilshtein : public BSScheme
{
public:
    BSMilshtein(double maturity, double volatility, double interest_rate, double spot, int dates);
    /**
     * Construire une trajectoire du modèle de Black Scholes sur la grille régulière de pas T/n en
     * utilisant le schéma de Milshtein.
     *
     * @param G vecteur des accroissements renormalisés (gaussiennes centrées réduites)
     * @param n nombre de pas de temps
     * @param[out] path contient la trajectoire simulée en sortie.
     */
    virtual void simul(PnlVect *path, const PnlVect *G, int n) const;
};
