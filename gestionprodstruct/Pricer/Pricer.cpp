#include "Pricer.hpp"
#include <fstream>
#include "MonteCarlo/GlobalModel.hpp"
#include "Produit/eurostralProduct.hpp"

Pricer::Pricer(char* jsonFileName){
    std::ifstream ifs(jsonFileName);
    nlohmann::json jsonParams = nlohmann::json::parse(ifs);
    jsonParams.at("InterestRates").get_to(interestRates);
    jsonParams.at("Volatilities_X").get_to(volatilities_X);
    jsonParams.at("Volatilities_Assets").get_to(volatilities_Assets);
    jsonParams.at("Correlations").get_to(correlationsCholesky);
    pnl_mat_chol(correlationsCholesky);
    jsonParams.at("constatationDates").get_to(constatationDates);
    jsonParams.at("maturity").get_to(maturity);
    TimeHandler* timeHandler = new TimeHandler(constatationDates, 260);
    nAssets = volatilities_Assets->size;

    //generate riskyAsset Objects
    vector<RiskyAsset*> riskyAssetVector;
    vector<Currency*> currencyVect;
    PnlVect *corrLine = pnl_vect_create(correlationsCholesky->n);
    // 1. generate currencies vector
    for(int i =1; i<volatilities_X->size; i++){
        pnl_mat_get_row(corrLine, correlationsCholesky, i+nAssets-1);
        currencyVect.push_back(new Currency(GET(interestRates,0), GET(interestRates,i),GET(volatilities_X,i),corrLine));
    }
    // 2.generate domestic Assets
    pnl_mat_get_row(corrLine, correlationsCholesky, 0);
    riskyAssetVector.push_back(new Asset(GET(interestRates,0), GET(volatilities_Assets,0), corrLine,currencyVect[0], true));
    // 3.generate foreign Assets
    for(int i=1; i<nAssets; i++){
        pnl_mat_get_row(corrLine, correlationsCholesky, i);
        riskyAssetVector.push_back(new Asset(GET(interestRates,i), GET(volatilities_Assets, i), corrLine, currencyVect[i-1], false));
    }
    // 4. add the currencies Vector to the riskyAsset vector
    riskyAssetVector.insert(riskyAssetVector.end(), currencyVect.begin(),currencyVect.end());
    pnl_vect_free(&corrLine);
    nRiskyAsset= riskyAssetVector.size();

    //generate pricer
    GlobalModel* model = new GlobalModel(riskyAssetVector, timeHandler);
    eurostralProduct* product = new eurostralProduct(maturity, interestRates, timeHandler);
    pricer = new MonteCarlo(10000, model, product, 0.1);
}

Pricer::~Pricer(){
    delete pricer;
}

void Pricer::priceAndDeltas(const PnlMat *past, double currentDate, bool isMonitoringDate, double &price,
                            double &priceStdDev, PnlVect *&deltas, PnlVect *&deltasStdDev) {
    deltas = pnl_vect_create_from_zero(nRiskyAsset);
    deltasStdDev= pnl_vect_create_from_zero(nRiskyAsset);
    pricer->priceAndDelta(past, currentDate, price, priceStdDev,deltas, deltasStdDev, isMonitoringDate);
}
