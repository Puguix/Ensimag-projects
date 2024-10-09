#pragma once

#include "Oracle.hpp"

class FixedOracle : public Oracle
{
public:
    int period_; /*! Période du rebalancement */

    FixedOracle(int period);
    bool IsRebalancingDate(int date) override;
    ~FixedOracle(){};

private:
    int compteur_ = 0; /*! Compteur du rebalanceur */
};
