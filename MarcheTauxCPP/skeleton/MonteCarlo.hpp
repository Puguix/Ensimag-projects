#include "pnl/pnl_matrix.h"
#include "GlobalModel.hpp"
#include "Options/Option.hpp"

class MonteCarlo {
public:
    GlobalModel* model_;
    Option* option_;
    double nbrSample_;
    PnlRng *rng_;
    double fdStep_;

    MonteCarlo(double nbSamples, GlobalModel* bsModel, Option* opt, double dfStep);
    void priceAndDelta(const PnlMat* past, double t, double& prix, double& std_dev, PnlVect* deltas, PnlVect* stdDeltas, bool isMonitoringDate);
    ~MonteCarlo()
    {
        delete model_;
        delete option_;
        pnl_rng_free(&rng_);
    }
};
