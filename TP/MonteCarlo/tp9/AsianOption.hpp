#ifndef _ASIAN_H
#define _ASIAN_H

#include "pnl/pnl_matrix.h"
#include "jlparser/parser.hpp"
#include "Option.hpp"

class AsianCallOption : public Option
{
  public:
    AsianCallOption();
    AsianCallOption(const IParser &P);
    ~AsianCallOption();
    void print() const;

    double K;
    PnlVect *m_lambda;

    double payoff(const PnlMat *path_val);

  private:
    PnlVect *ones;
};

#endif
