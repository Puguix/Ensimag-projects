#include "RiskyAsset.hpp"

void RiskyAsset::asset(PnlMat* path, int i, int j, double price, double stepDuration, PnlVect* G){
    price *= exp(drift_*stepDuration
                 + sqrt(stepDuration)*pnl_vect_scalar_prod(volatilityVector_, G));
    pnl_mat_set(path, i, j, price);
}