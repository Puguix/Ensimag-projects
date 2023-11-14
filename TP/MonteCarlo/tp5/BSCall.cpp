// vim: set sw=4 ts=4 sts=4:
#include <iostream>
#include <cmath>
#include <math.h>
#include <algorithm>
#include "BSCall.hpp"

BSCall::BSCall(double maturity, double volatility, double interest_rate, double spot, double strike, double barrier, int dates)
    : m_maturity{maturity}, m_volatility{volatility}, m_interest_rate{interest_rate},
    m_spot{spot}, m_strike{strike}, m_dates{dates}, m_barrier{barrier}
{
    m_discount = std::exp(-m_interest_rate * m_maturity);
}

BSCall::BSCall(double maturity, double volatility, double interest_rate, double spot, double strike, int dates)
    : m_maturity{maturity}, m_volatility{volatility}, m_interest_rate{interest_rate},
    m_spot{spot}, m_strike{strike}, m_dates{dates}
{
    m_discount = std::exp(-m_interest_rate * m_maturity);
}

double BSCall::asset(double G, double theta)
{
    return m_spot * std::exp((m_interest_rate - m_volatility * m_volatility / 2.) * m_maturity + m_volatility * std::sqrt(m_maturity) * (G + theta));
}


double BSCall::payoff(double G, double theta)
{
    double ST = asset(G, theta);
    return std::exp(-m_interest_rate * m_maturity) * std::max(ST - m_strike, 0.);
}

double BSCall::weight_plus(double G, double theta)
{
    return std::exp(-G * theta + theta * theta / 2);
}

double BSCall::weight_minus(double G, double theta)
{
    return std::exp(-G * theta - theta * theta / 2);
}

double BSCall::d_weight_plus(double G, double theta)
{
    return (theta - G) * std::exp(-G * theta + theta * theta / 2);
}


void BSCall::sousJacent(PnlVect* sousJ){
    pnl_vect_set(sousJ, 0, m_spot);

    for (int i = 1; i<=m_dates; i++){
        double value = pnl_vect_get(sousJ, i);
        pnl_vect_set(sousJ, i, m_spot * exp((m_interest_rate - pow(m_volatility,2)/2)*i*m_maturity/m_dates+m_volatility*value));
    }
}

void BSCall::logsousJacent(PnlVect* sousJ, PnlVect* brownien){
    pnl_vect_set(sousJ, 0, m_spot);

    for (int i = 1; i<=m_dates; i++){
        double value = pnl_vect_get(brownien, i-1);
        pnl_vect_set(sousJ, i, std::log(m_spot * exp((m_interest_rate - pow(m_volatility,2)/2)*i*m_maturity/m_dates+m_volatility*value)));
    }
}

double BSCall::payoffBarrier(PnlVect *path)
{
    for (int l = 0; l < m_dates + 1; l++) {
        if (GET(path, l) < m_barrier) return 0.;
    }
    double ST = GET(path, m_dates);
    return m_discount * std::max(ST - m_strike, 0.);
}

double BSCall::payoffBarrierAm(PnlVect *path)
{
    double prod = 1.;
    double pas = m_maturity/m_dates;
    for (int l = 1; l < m_dates + 1; l++) {
        if (GET(path, l-1) < m_barrier || GET(path, l) < m_barrier){return 0.;}
        double valeur = (1 - std::exp(-2*std::log(m_barrier/GET(path, l-1))*std::log(m_barrier/GET(path, l))/pow(m_volatility,2)/pas));
        prod *= valeur;
    }
    double ST = GET(path, m_dates);
    return m_discount * std::max(ST - m_strike, 0.) * prod;
}