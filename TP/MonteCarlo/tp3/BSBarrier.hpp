// vim: set sw=4 ts=4 sts=4:
#pragma once

#include "pnl/pnl_vector.h"

class BSBarrier {
public:
    BSBarrier(double maturity, double volatility, double interest_rate, double spot, double strike, double barrier, int dates);
    double m_maturity;
    double m_volatility;
    double m_interest_rate;
    double m_spot;
    double m_strike;
    double m_barrier;
    int m_dates;

    // Calculer une trajectoire
    // @param path contient une trajectoire de taille m_dates en sortie
    // @param G vecteur des v.a. de loi normales centrées réduites servant à construire les
    // incréments brownien
    // @param theta le drift linéaire utilisté dans le brownien, ie W_t + theta t
    void asset(PnlVect *path, const PnlVect *G, double theta = 0.);
    /// Calculer le payoff sur une trajectoire
    double payoff(PnlVect *path);
    /// Calculer exp(- theta B_T + theta^2 T/2)
    double weight_plus(const PnlVect *G, double theta);
    /// Calculer exp(- theta B_T - theta^2 T/2)
    double weight_minus(const PnlVect *G, double theta);
    // Calculer la dérivée de weight_plus
    double d_weight_plus(const PnlVect *G, double theta);

private:
    /// r - sigma^2 / 2 * dt
    double m_drift_bs;
    /// pas de temps;
    double m_dt;
    /// racine du pas de temps
    double m_sqrt_dt;
    /// Actualisation sur [0,T]
    double m_discount;

    /// Calculer la valeur de B_T à partir des incréments
    double compute_BT(const PnlVect *G);

};

