#ifndef _OPT_H
#define _OPT_H

#include "pnl/pnl_matrix.h"
#include "Model.hpp"
#include "jlparser/parser.hpp"

#include <cmath>
#include <string>

class Option
{
  public:
    std::string m_label;
    double m_maturity; /*!< m_maturity of the option */
    /* duplicates Model::m_modelSize, no other solution found sofar */
    int m_optionSize;
    /* duplicates Model::m_nTimeSteps, no other solution found sofar */
    int m_nTimeSteps;

    Option();
    Option(const IParser &ParamTab);
    virtual ~Option(){};

    /**  Matrix path has size columns and
     * (m_nTimeSteps + 1) rows be careful this not
     * natural.
     */
    virtual double payoff(const PnlMat *) = 0;
    virtual void print() const;
};

extern Option *instantiate_option(const IParser &ParamMap);

#endif
