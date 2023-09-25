#include "HedgingResults.hpp"
#include <iostream>
#include <nlohmann/json.hpp>

std::ostream&
operator<<(std::ostream& stm, const HedgingResults& res)
{
    nlohmann::json j = {
        { "initialPrice", res.initialPrice },
        { "initialPriceStdDev", res.initialPriceStdDev },
        { "finalPnL", res.finalPnL }
    };
    stm << j << std::endl;
    return stm;
}