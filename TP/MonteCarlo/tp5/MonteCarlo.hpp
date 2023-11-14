// vim: set sw=4 ts=4 sts=4:
#pragma once

#include "BSCall.hpp"
#include "pnl/pnl_random.h"

class MonteCarlo
{
private:
    // Une instance de BSCall
    BSCall &m_product;
    // nombre de tirages
    int m_samples;

public:
    MonteCarlo(BSCall &product, int samples);
    void mc(double &prixX, double &prixY, double &prixZ, double &stddev, double &stddevY, double &stddevZ, PnlRng *rng);
    void mcBar(double &prix,  double &prixY, double &stddev, double &stddevY,PnlRng *rng);
    double trapeze(PnlVect* sousJacent, double T); /* J pas de temps*/
    double trapezelog(PnlVect* sousJacent, double T);
    void brownien(PnlVect* g, PnlVect* gPrime);

};
