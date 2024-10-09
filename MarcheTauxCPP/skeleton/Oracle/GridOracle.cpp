#include "GridOracle.hpp"


GridOracle::GridOracle(PnlVect* rebalDates) : rebalDates_(rebalDates){}

bool GridOracle::IsRebalancingDate(int date) {
    for(int i = 0; i < this->rebalDates_->size; i++){
        if (pnl_vect_get(rebalDates_, i) == date){
            return true;
        }
    }
    return false;
}

