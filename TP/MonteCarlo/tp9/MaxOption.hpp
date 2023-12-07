#ifndef _MAXIMUM_H
#define _MAXIMUM_H

#include "pnl/pnl_matrix.h"
#include "jlparser/parser.hpp"
#include "Option.hpp"

class MaxOption : public Option
{
  public:
    MaxOption();
    MaxOption(const IParser &ParamTab);
    ~MaxOption();
    void print() const;

    double K;

    double payoff(const PnlMat *path_val);
};

#endif
