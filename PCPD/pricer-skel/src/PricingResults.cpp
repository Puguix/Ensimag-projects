#include <iostream>
#include "PricingResults.hpp"
#include "json_helper.hpp"

// PricingResults::~PricingResults(){
//     pnl_vect_free(&this->delta);
//     pnl_vect_free(&this->deltaStdDev);
// }

std::ostream&
operator<<(std::ostream& stm, const PricingResults& res)
{

    nlohmann::json j = {
        { "price", res.price },
        { "priceStdDev", res.priceStdDev },
        { "delta", res.delta },
        { "deltaStdDev", res.deltaStdDev }
    };
    stm << j << std::endl;
    return stm;
}