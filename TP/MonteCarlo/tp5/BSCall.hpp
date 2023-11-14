// vim: set sw=4 ts=4 sts=4:
#pragma once
#include "pnl/pnl_vector.h"

class BSCall {
public:
    BSCall(double maturity, double volatility, double interest_rate, double spot, double strike, double barrier, int dates);
    BSCall(double maturity, double volatility, double interest_rate, double spot, double strike, int dates);
    double m_maturity;
    double m_volatility;
    double m_interest_rate;
    double m_spot;
    double m_strike;
    int m_dates;
    double m_barrier=0.;
    double m_discount;


    /// Calculer une valeur de S_T
    double asset(double G, double theta = 0.);
    /// Calculer psi(G)
    double payoff(double G, double theta = 0.);
    /// Calculer exp(- theta G + theta^2/2)
    double weight_plus(double G, double theta);
    /// Calculer exp(- theta G - theta^2/2)
    double weight_minus(double G, double theta);
    // Calculer la dérivée de weight_plus
    double d_weight_plus(double G, double theta);
    // Calculer la trajectoire d'un sous jacent
    void sousJacent(PnlVect* sousJ);
    // Calculer le log de la trajectoire du sous jacent
    void logsousJacent(PnlVect* sousJ, PnlVect* brownien);
    //Calcule le payoff avec un barriere basse
    double payoffBarrier(PnlVect *path);
    //Calcule le payoff avec un barriere basse avec version amélioré
    double payoffBarrierAm(PnlVect *path);
};

