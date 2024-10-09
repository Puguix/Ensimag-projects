#pragma once

#include "pnl/pnl_vector.h"
#include "pnl/pnl_random.h"

class Oracle
{
public:
    virtual bool IsRebalancingDate(int date) = 0;
    virtual ~Oracle(){};
};
