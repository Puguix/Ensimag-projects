#pragma once

#include "Model.hpp"
#include "Option.hpp"
#include "Martingale.hpp"
#include "MonteCarlo.hpp"
#include "pnl/pnl_matrix.h"
#include "pnl/pnl_random.h"
#include "jlparser/parser.hpp"

class FunctionalHedger {
public:
    FunctionalHedger(MonteCarlo *mc, const IParser& ParamTab);
    ~FunctionalHedger();
    void compute();
    double pnl(double price0, const PnlMat *p_asset) const;
    void print() const;

private:
    const IParser *paramTab;
    Model *mod;
    Option *opt;
    MonteCarlo *mc;
    MartingaleIncrement **martingaleIncrements; //!< An array of size mod->m_nHedgingDates
    void computeMartingale(PnlMat **p_asset, PnlVect **p_M);

};
