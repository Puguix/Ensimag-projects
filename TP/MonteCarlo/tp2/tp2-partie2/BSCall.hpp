// vim: set sw=4 ts=4 sts=4:
#pragma once

class BSCall {
public:
    BSCall(double maturity, double volatility, double interest_rate, double spot, double strike);
    double m_maturity;
    double m_volatility;
    double m_interest_rate;
    double m_spot;
    double m_strike;

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

};

