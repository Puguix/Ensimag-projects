#include <pnl/pnl_vector.h>
#include <pnl/pnl_matrix.h>
#include <cmath>

class RiskyAsset {
public:
    double drift_;
    PnlVect* volatilityVector_;
    double domesticInterestRate_;

    void asset(PnlMat* path, int i, int j, double price, double stepDuration, PnlVect* G);
    virtual ~RiskyAsset(){
        pnl_vect_free(&volatilityVector_);
    }
};
