// vim: set sw=4 ts=4 sts=4:
#include <iostream>
#include <cmath>
#include <algorithm>
#include "BSBarrier.hpp"

BSBarrier::BSBarrier(double maturity, double volatility, double interest_rate, double spot, double strike, double barrier, int dates)
    : m_maturity(maturity), m_volatility(volatility), m_interest_rate(interest_rate),
    m_spot(spot), m_strike(strike), m_barrier(barrier), m_dates(dates)
{
    m_dt = maturity / dates;
    m_sqrt_dt = std::sqrt(m_dt);
    m_drift_bs = (interest_rate - volatility * volatility / 2) * m_dt;
    m_discount = std::exp(-m_interest_rate * m_maturity);
}

void BSBarrier::asset(PnlVect *path, const PnlVect *G, double theta)
{
    pnl_vect_resize(path, m_dates + 1);
    LET(path, 0) = m_spot;
    for (int l = 1; l <= m_dates; l++) {
        LET(path, l) = GET(path, l - 1) * std::exp(m_drift_bs + m_volatility * m_sqrt_dt * (GET(G, l - 1) + theta * m_sqrt_dt));
    }
}

double BSBarrier::payoff(PnlVect *path)
{
    for (int l = 0; l < m_dates + 1; l++) {
        if (GET(path, l) < m_barrier) return 0.;
    }
    double ST = GET(path, m_dates);
    return m_discount * std::max(ST - m_strike, 0.);
}

double BSBarrier::weight_plus(const PnlVect *G, double theta)
{
    double BT = compute_BT(G);
    return std::exp(-theta * BT + theta * theta  * m_maturity / 2);
}

double BSBarrier::weight_minus(const PnlVect *G, double theta)
{
    double BT = compute_BT(G);
    return std::exp(-theta * BT - theta * theta  * m_maturity / 2);
}

double BSBarrier::d_weight_plus(const PnlVect *G, double theta)
{
    double BT = compute_BT(G);
    return (theta * m_maturity - BT) * std::exp(-theta * BT + theta * theta  * m_maturity / 2);
}

double BSBarrier::compute_BT(const PnlVect *G)
{
    return pnl_vect_sum(G) * m_sqrt_dt;
}
