#include "pnl/pnl_matrix.h"
#include "GlobalModel.hpp"
#include "../Produit/eurostralProduct.hpp"

class MonteCarlo {
public:
    GlobalModel* model_;
    eurostralProduct* product_;
    double nbrSample_;
    PnlRng *rng_;
    double fdStep_;

    MonteCarlo(double nbSamples, GlobalModel* bsModel, eurostralProduct* product , double dfStep);
    void priceAndDelta(const PnlMat* past, double t, double& price, double& std_dev, PnlVect* deltas, PnlVect* stdDeltas, bool isMonitoringDate);
    ~MonteCarlo()
    {
        delete model_;
        delete product_;
        pnl_rng_free(&rng_);
    }
};

