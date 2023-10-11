// vim: set sw=4 ts=4 sts=4:
#pragma once

#include "BSBarrier.hpp"
#include "pnl/pnl_random.h"
#include "pnl/pnl_mathtools.h"

class MonteCarlo
{
private:
    // Une instance de BSCall
    BSBarrier &m_product;
    // nombre de tirages
    size_t m_samples;

public:
    PnlVect *getBrownianMotion(PnlVect *g, double N, double T, PnlRng *rng);
    MonteCarlo(BSBarrier &product, size_t samples);
    void mc(double &prix, double &stddev, PnlRng *rng);
    void mc2(double &prix, double &stddev, double l, PnlRng *rng);
};
