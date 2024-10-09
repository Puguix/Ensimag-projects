#pragma once

#include "Oracle.hpp"
#include "pnl/pnl_vector.h"


class GridOracle : public Oracle
{
public:
    PnlVect* rebalDates_; /*! Dates de rebalancement */

    GridOracle(PnlVect* rebalDates);
    bool IsRebalancingDate(int date) override;
    ~GridOracle(){
        pnl_vect_free(&rebalDates_);
    }

};
