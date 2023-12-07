#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>

using namespace std;

#include "MaxOption.hpp"
#include "jlparser/parser.hpp"

double MaxOption::payoff(const PnlMat *path_val)
{
    PnlVect S = pnl_vect_wrap_mat(path_val);
    double m = pnl_vect_max(&S);
    double sT = GET(&S, S.size - 1);
    return max(K * m - sT, 0.0);
}

MaxOption::MaxOption()
{
}

MaxOption::MaxOption(const IParser &P)
    : Option(P)
{
    m_label = "maximum";
    P.extract("strike", K);
}

void MaxOption::print() const
{
    cout << "**** Maximum Option Characteristics ****" << endl;
    Option::print();
    cout << " strike : " << K << endl;
}

MaxOption::~MaxOption()
{
}
