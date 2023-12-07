#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>

using namespace std;

#include "AsianOption.hpp"
#include "jlparser/parser.hpp"

double AsianCallOption::payoff(const PnlMat *path_val)
{
    double sum = pnl_mat_scalar_prod(path_val, ones, m_lambda);
    sum /= path_val->m;
    return max(sum - K, 0.0);
}

AsianCallOption::AsianCallOption() : m_lambda(NULL), ones(NULL) {}

AsianCallOption::AsianCallOption(const IParser &P) : Option(P)
{
    m_label = "asian";
    P.extract("strike", K);
    if ((!P.extract("payoff coefficients", m_lambda, m_optionSize, true)) && (m_optionSize == 1)) {
        m_lambda = pnl_vect_create_from_scalar(1, 1.);
    }
    ones = pnl_vect_create_from_scalar(m_nTimeSteps + 1, 1.);
}

void AsianCallOption::print() const
{
    cout << "**** Asian Option Characteristics ****" << endl;
    Option::print();
    cout << " strike : " << K << endl;
    cout << " payoff coefficients : ";
    pnl_vect_print_asrow(m_lambda);
    cout << endl;
}

AsianCallOption::~AsianCallOption()
{
    pnl_vect_free(&m_lambda);
    pnl_vect_free(&ones);
}
