// vim: set sw=4 ts=4 sts=4:
#include <iostream>
#include <cmath>
#include "BSScheme.hpp"

BSScheme::BSScheme(double maturity, double volatility, double interest_rate, double spot)
    : m_maturity(maturity), m_volatility(volatility), m_interest_rate(interest_rate),
    m_spot(spot)
{
}

void BSScheme::simulExact(PnlVect *path, const PnlVect *G, int n) const
{
    double m_dt = m_maturity / (double)n;
    double m_sqrt_dt = std::sqrt(m_dt);
    double m_drift_bs = (m_interest_rate - m_volatility * m_volatility / 2) * m_dt;
    double m_discount = std::exp(-m_interest_rate * m_maturity);
    pnl_vect_resize(path, n + 1);
    LET(path, 0) = m_spot;
    for (int l = 1; l <= n; l++) {
        LET(path, l) = GET(path, l - 1) * std::exp(m_drift_bs + m_volatility * m_sqrt_dt * (GET(G, l - 1)));
    }
}

void BSScheme::brownien(PnlVect* g, PnlVect* gPrime){
    double ecart = sqrt(m_maturity/gPrime->size);
    pnl_vect_set (gPrime, 0, 0.0);
    for (int i = 1; i < gPrime->size; i++){
        pnl_vect_set (gPrime, i, pnl_vect_get(gPrime, i-1)+ecart*pnl_vect_get(g,i-1));
    }
}

BSEuler::BSEuler(double maturity, double volatility, double interest_rate, double spot)
    : BSScheme(maturity, volatility, interest_rate, spot)
{}


void BSEuler::simul(PnlVect *path, const PnlVect *G, int n) const
{   
    double m_dt = m_maturity / (double)n;
    pnl_vect_resize(path, n + 1);
    LET(path, 0) = m_spot;
    for (int l = 1; l <= n; l++) {
        LET(path, l) = GET(path, l - 1) + m_dt * m_interest_rate * GET(path, l - 1) + GET(path, l - 1) * m_volatility *(GET(G, l) - GET(G, l-1));
    }

}

BSMilshtein::BSMilshtein(double maturity, double volatility, double interest_rate, double spot)
    : BSScheme(maturity, volatility, interest_rate, spot)
{}


void BSMilshtein::simul(PnlVect *path, const PnlVect *G, int n) const
{
    double m_dt = m_maturity / (double)n;

    pnl_vect_resize(path, n + 1);
    LET(path, 0) = m_spot;
    for (int l = 1; l <= n; l++) {
        double value = GET(path, l - 1) + m_dt * m_interest_rate * GET(path, l - 1) + GET(path, l - 1) * m_volatility *(GET(G, l) - GET(G, l-1));
        value += 0.5 * GET(path, l - 1) * SQR(m_volatility) * (SQR(GET(G, l) - GET(G, l-1))-m_dt);
        LET(path, l) = value;
    }
}

