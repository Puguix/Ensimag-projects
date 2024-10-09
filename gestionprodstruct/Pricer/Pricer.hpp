#pragma once

#include <iostream>
#include <nlohmann/json.hpp>
#include "pnl/pnl_vector.h"
#include "pnl/pnl_matrix.h"
#include "Tools/json_reader.hpp"
#include "MonteCarlo/MonteCarlo.hpp"

class Pricer {
public:
    PnlMat *correlationsCholesky;
    PnlVect *interestRates;
    PnlVect *volatilities_X;
    PnlVect *volatilities_Assets;
    int nAssets;
    int nRiskyAsset;
    PnlVect *constatationDates;
    double maturity;
    MonteCarlo* pricer;

    explicit Pricer(char* jsonFileName);

    ~Pricer();

    /**
     * Compute price and the deltas for hedging
     * @param past
     * @param currentDate
     * @param isMonitoringDate
     * @param price
     * @param priceStdDev
     * @param deltas
     * @param deltasStdDev
     */
    void priceAndDeltas(const PnlMat *past, double currentDate, bool isMonitoringDate,
                        double &price, double &priceStdDev, PnlVect *&deltas, PnlVect *&deltasStdDev);
};