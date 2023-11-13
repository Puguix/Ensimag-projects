// vim: set sw=4 ts=4 sts=4:
#include <iostream>
#include <cmath>
#include "BSScheme.hpp"
#include "pnl/pnl_mathtools.h"

BSScheme::BSScheme(double maturity, double volatility, double interest_rate, double spot, int dates)
    : m_maturity(maturity), m_volatility(volatility), m_interest_rate(interest_rate),
      m_spot(spot)
{
    m_dt = maturity / (double)dates;
    m_sqrt_dt = std::sqrt(m_dt);
    m_drift_bs = (interest_rate - volatility * volatility / 2) * m_dt;
    m_discount = std::exp(-m_interest_rate * m_maturity);
}

void BSScheme::simulExact(PnlVect *path, const PnlVect *G, int n) const
{
    pnl_vect_resize(path, n + 1);
    LET(path, 0) = m_spot;
    for (int i = 1; i <= n; i++)
    {
        LET(path, i) = GET(path, i - 1) * std::exp(m_drift_bs + m_volatility * m_sqrt_dt * GET(G, i - 1));
    }
}

BSEuler::BSEuler(double maturity, double volatility, double interest_rate, double spot, int dates)
    : BSScheme(maturity, volatility, interest_rate, spot, dates)
{
}

void BSEuler::simul(PnlVect *path, const PnlVect *G, int n) const
{
    pnl_vect_resize(path, n + 1);
    LET(path, 0) = m_spot;
    for (int i = 1; i <= n; i++)
    {
        LET(path, i) = GET(path, i - i) + GET(path, i - 1) * m_interest_rate * m_dt + GET(path, i - 1) * m_volatility * (m_sqrt_dt * GET(G, i - 1));
    }
}

BSMilshtein::BSMilshtein(double maturity, double volatility, double interest_rate, double spot, int dates)
    : BSScheme(maturity, volatility, interest_rate, spot, dates)
{
}

void BSMilshtein::simul(PnlVect *path, const PnlVect *G, int n) const
{
    pnl_vect_resize(path, n + 1);
    LET(path, 0) = m_spot;
    for (int i = 1; i <= n; i++)
    {
        LET(path, i) = GET(path, i - 1) + GET(path, i - 1) * m_interest_rate * m_dt + GET(path, i - 1) * m_volatility * m_sqrt_dt * GET(G, i - 1) + 1 / 2 * SQR(m_volatility) * GET(path, i - 1) * (SQR(m_sqrt_dt * GET(G, i - 1)) - m_dt);
    }
}
