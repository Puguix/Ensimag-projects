#ifndef _DIGITAL_H
#define _DIGITAL_H

#include "pnl/pnl_matrix.h"
#include "jlparser/parser.hpp"
#include "Option.hpp"

/** implements a digital option
 */
class DigitalFinalOption : public Option
{
  public:
    DigitalFinalOption();
    DigitalFinalOption(const IParser &ParamTab);
    ~DigitalFinalOption();
    void print() const;

    /** the barriers can be different for each component */
    PnlVect *lower_barrier; /*!< the asset should be above this
                             barrier */
    PnlVect *upper_barrier; /*!< the asset should remain below  this
                             barrier */

    double payoff(const PnlMat *path_val);
};

/** implements a digital option combined with a put/call option
 */
class DigitalBasketOption : public Option
{
  public:
    DigitalBasketOption();
    DigitalBasketOption(const IParser &ParamTab);
    ~DigitalBasketOption();
    void print() const;

    double K;
    PnlVect *m_lambda;
    /** the barriers can be different for each component */
    PnlVect *lower_barrier; /*!< the asset should be above this
                             barrier */
    PnlVect *upper_barrier; /*!< the asset should remain below  this
                             barrier */

    double payoff(const PnlMat *path_val);
};

/** implements a digital option
 */
class DigitalOption : public Option
{
  public:
    DigitalOption();
    DigitalOption(const IParser &ParamTab);
    ~DigitalOption();
    void print() const;

    /** the barriers can be different for each component */
    PnlVect *lower_barrier; /*!< the asset should be above this
                             barrier */
    PnlVect *upper_barrier; /*!< the asset should remain below  this
                             barrier */

    double payoff(const PnlMat *path_val);
};

/** implements a barrier baskeet option
 */
class BarrierOption : public Option
{
  public:
    BarrierOption();
    BarrierOption(const IParser &ParamTab);
    ~BarrierOption();
    void print() const;

    /** the barriers can be different for each component */
    PnlVect *lower_barrier; /*!< the asset should be above this
                             barrier */
    PnlVect *upper_barrier; /*!< the asset should remain below  this
                             barrier */
    double K;
    PnlVect *m_lambda;

    double payoff(const PnlMat *path_val);
};

#endif
