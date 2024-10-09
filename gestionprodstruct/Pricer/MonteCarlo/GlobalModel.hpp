#ifndef GLOBALMODEL_HPP
#define GLOBALMODEL_HPP

#include "pnl/pnl_random.h"
#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"
#include "../RiskyAssets/Asset.hpp"
#include "../TimeHandler/TimeHandler.hpp"
#include <vector>
#include <cmath>
using namespace  std;

class GlobalModel {
public:
    TimeHandler* timeHandler_;
    vector<RiskyAsset*> riskyAssets_; // ça englobe les actifs XS (actifs risqués en dom) et XB (les actifs sans risque en dom)

    GlobalModel(const vector<RiskyAsset*> riskyAssets, TimeHandler* timeHandler);
    void asset(PnlMat* path, double t, const PnlMat* past, PnlRng* rng, bool isMonitoringDate);
    void shiftAsset(PnlMat* shift_path, const PnlMat* path, int d, double h, double t, bool isMonitoringDate);
    ~GlobalModel(){
        delete timeHandler_;
        for (auto& obj : riskyAssets_) {
            obj->~RiskyAsset();
        }
    };
private:
    static void copyMatrixValues(PnlMat* matrixTarget , const PnlMat* matrixToCopy, int nDate, int nAsset);
};

#endif
