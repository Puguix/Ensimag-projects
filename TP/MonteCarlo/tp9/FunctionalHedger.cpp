#include "FunctionalHedger.hpp"

FunctionalHedger::FunctionalHedger(MonteCarlo *mc, const IParser &ParamTab)
    : mod(mc->mod), opt(mc->opt), mc(mc), paramTab(&ParamTab)
{
    martingaleIncrements = new MartingaleIncrement*[mod->m_nHedgingDates];
}

FunctionalHedger::~FunctionalHedger() {
    delete [] martingaleIncrements;
}

void FunctionalHedger::print() const {
    for (int t = 0; t < mod->m_nHedgingDates; t++) {
        std::cout << "Coefficients at time " << t << std::endl;
        pnl_vect_print_asrow(martingaleIncrements[t]->getCoefficients());
    }
}

/**
 * @brief Compute the martingale paths
 *
 * @param p_asset An array of the model paths, length \a m_nSamples.
 * @param p_M An array of the martingale path, length \a m_nSamples. Each element of the array must already be allocated.
 */
void FunctionalHedger::computeMartingale(PnlMat **p_asset, PnlVect **p_M) {
    for (int l = 0; l < mc->m_nSamples; l++) {
        LET(p_M[l], 0) = 0.;
        for (int k = 0; k < mod->m_nHedgingDates; k++) {
            double deltaM_kl = martingaleIncrements[k]->predict(p_asset[l]);
            LET(p_M[l], k + 1) = GET(p_M[l], k) + deltaM_kl;
        }
    }
}

void FunctionalHedger::compute() {
    PnlMat **asset = new PnlMat*[mc->m_nSamples];
    PnlVect **M = new PnlVect*[mc->m_nSamples];
    PnlVect *Z = pnl_vect_create(mc->m_nSamples);

   // Initialization
    for (int l = 0; l < mc->m_nSamples; l++) {
        mod->pathForHedging(mc->rng);
        asset[l] = pnl_mat_copy(mod->m_pathMatrix);
        M[l] = pnl_vect_create(mod->m_nHedgingDates + 1);
        LET(Z, l) = opt->payoff(asset[l]) * mod->discount(mod->m_maturity);
    }

    // Initialize the martingale increments
    for (int t = 1; t < mod->m_nHedgingDates + 1; t++) {
        martingaleIncrements[t - 1] = instantiate_martingale(mod, opt, *paramTab, t);
    }

    // Solve the sequence of optimization problems
    for (int t = 1; t < mod->m_nHedgingDates + 1; t++) {
        martingaleIncrements[t - 1]->fit(asset, Z);
    }

    for (int l = 0; l < mod->m_nHedgingDates; l++) {
        pnl_mat_free(&asset[l]);
        pnl_vect_free(&M[l]);
    }
    pnl_vect_free(&Z);
    delete [] asset;
    delete [] Z;
    delete [] M;
}

/**
 * @brief Compute the P&L on a single asset path
 *
 * @param p_asset The model path
 */
double FunctionalHedger::pnl(double price0, const PnlMat *p_asset) const {
    double portfolioValue = 0; // Risky part only.
    PnlVect *composition = pnl_vect_create_from_zero(mod->m_modelSize);
    double hedgingTimeStep = mod->m_maturity / mod->m_nHedgingDates;
    for (int date = 0; date < mod->m_nHedgingDates; date++ ) {
        PnlVect assetAtNextDate = pnl_vect_wrap_mat_row(p_asset, date + 1);
        PnlVect assetAtDate = pnl_vect_wrap_mat_row(p_asset, date);
        martingaleIncrements[date]->getPortfolioComposition(composition, p_asset);
        portfolioValue -= pnl_vect_scalar_prod(composition, &assetAtDate) * mod->discount(date * hedgingTimeStep);
        portfolioValue += pnl_vect_scalar_prod(composition, &assetAtNextDate) * mod->discount((date + 1) * hedgingTimeStep);
    }
    double PnL = (portfolioValue + price0) / mod->discount(mod->m_maturity) - opt->payoff(p_asset);

    pnl_vect_free(&composition);
    return PnL;
}
