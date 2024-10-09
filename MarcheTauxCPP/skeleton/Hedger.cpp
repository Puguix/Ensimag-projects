#include <iostream>
#include "Tools/Parser.hpp"
#include "Portfolio.hpp"


int main(int argc, char *argv[]) {
    // Retrieve Market Data
    PnlMat *marketData = pnl_mat_create_from_file(argv[2]);

    // Generate the parser and use it to generate the needed objects
    Parser parser(argv[1]);
    Option* option = parser.generateOption();
    GlobalModel* globalModel = new GlobalModel(parser.generateRiskyAssets(), parser.timehandler);
    MonteCarlo* monteCarlo =  new MonteCarlo(parser.sampleNb, globalModel, option, parser.finiteDifferenceStep);
    Oracle* oracle = parser.generateOracle();

    double price, priceStdDev;
    PnlVect *deltas = pnl_vect_create(marketData->n);
    PnlVect *stdDeltas = pnl_vect_create(marketData->n);
    PnlVect *spots = pnl_vect_create(marketData->n);
    pnl_mat_get_row(spots, marketData, 0);
    PnlMat* past= parser.getPastPrices(marketData, 0);

    monteCarlo->priceAndDelta(past, 0, price, priceStdDev, deltas, stdDeltas,
                              parser.timehandler->isMonitoringDate(0));
    PnlVect *deltaPortefeuille= pnl_vect_new();
    pnl_vect_clone(deltaPortefeuille, deltas);
    PnlVect *stdDeltasPortefeuille = pnl_vect_new();
    pnl_vect_clone(stdDeltasPortefeuille,stdDeltas);
    Portfolio hedgingPortfolio(parser.domesticInterestRate, parser.numberOfDaysPerYear, spots, deltaPortefeuille, stdDeltasPortefeuille, price, priceStdDev);
    for(int date = 1; date < marketData->m; date++) {
        if (oracle->IsRebalancingDate(date)) {
            pnl_mat_get_row(spots, marketData, date);
            past = parser.getPastPrices(marketData, date);
            monteCarlo->priceAndDelta(past, date, price, priceStdDev, deltas, stdDeltas,
                                      parser.timehandler->isMonitoringDate(date));

            hedgingPortfolio.positions.push_back(Position(date, price, priceStdDev, pnl_vect_copy(deltas), pnl_vect_copy(stdDeltas),
                                                          hedgingPortfolio.computeValueAndUpdate(date, pnl_vect_copy(deltas), spots)));
        }
    }

    nlohmann::json jsonPortfolio = hedgingPortfolio.positions;
    ofstream ifout(argv[3], ios_base::out);
    if (!ifout.is_open()) {
        cout << "Unable to open file " << argv[3] << endl;
        exit(1);
    }
    ifout << jsonPortfolio.dump(4);
    ifout.close();

    return 0;

}


