#ifndef _BASKET_H
#define _BASKET_H

#include "pnl/pnl_matrix.h"
#include "jlparser/parser.hpp"
#include "Option.hpp"

class BasketOption : public Option
{
  public:
    BasketOption();
    BasketOption(const IParser &ParamTab);
    ~BasketOption();
    void print() const;

    double K;
    PnlVect *m_lambda;

    double payoff(const PnlMat *path_val);
};

class PerformanceOption : public Option
{
  public:
    PerformanceOption();
    PerformanceOption(const IParser &ParamTab);
    ~PerformanceOption();
    void print() const;

    double K;
    PnlVect *m_lambda;

    double payoff(const PnlMat *path_val);
};

class BestOfOption : public Option
{
  public:
    BestOfOption();
    BestOfOption(const IParser &ParamTab);
    ~BestOfOption();
    void print() const;

    double K;
    PnlVect *m_lambda;

    double payoff(const PnlMat *path_val);
};

class WorstOfOption : public Option
{
  public:
    WorstOfOption();
    WorstOfOption(const IParser &ParamTab);
    ~WorstOfOption();
    void print() const;

    double K;
    PnlVect *m_lambda;

    double payoff(const PnlMat *path_val);
};

class GeometricBasketOption : public Option
{
  public:
    GeometricBasketOption();
    GeometricBasketOption(const IParser &ParamTab, bool is_call = true);
    ~GeometricBasketOption();
    void print() const;

    double K_;
    bool is_call_;
    double payoff(const PnlMat *path_val);
};
#endif
