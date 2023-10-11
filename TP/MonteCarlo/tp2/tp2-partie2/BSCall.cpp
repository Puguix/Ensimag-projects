// vim: set sw=4 ts=4 sts=4:
#include <iostream>
#include <cmath>
#include <algorithm>
#include "BSCall.hpp"

BSCall::BSCall(double maturity, double volatility, double interest_rate, double spot, double strike)
    : m_maturity(maturity), m_volatility(volatility), m_interest_rate(interest_rate),
    m_spot(spot), m_strike(strike)
{}

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
