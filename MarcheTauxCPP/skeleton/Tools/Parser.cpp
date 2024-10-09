#include <stdexcept>
#include "json_reader.hpp"
#include "Parser.hpp"

Parser::Parser(char *filePath) {
    std::ifstream ifs(filePath);
    jsonParams = nlohmann::json::parse(ifs);

    // Option's infos
    int assetNb = jsonParams.at("Assets").size();
    int order = 0;
    map<string, int> currenciesOrder;
    jsonParams.at("Correlations").get_to(this->correlationsCholesky);
    pnl_mat_chol(this->correlationsCholesky);

    numberOfDaysPerYear = jsonParams.at("NumberOfDaysInOneYear").get<int>();
    sampleNb = jsonParams.at("SampleNb").get<int>();
    finiteDifferenceStep = jsonParams.at("RelativeFiniteDifferenceStep").get<double>();
    domesticCurrencyId = jsonParams.at("DomesticCurrencyId").get<string>();

    // Currencies
    auto jsonCurrencies = jsonParams.at("Currencies");
    for (auto jsonCurrency: jsonCurrencies) {
        string id = jsonCurrency.at("id").get<string>();
        assetsCurrencies[id] = vector<int>(0);

        if( id == domesticCurrencyId){
            domesticInterestRate = jsonCurrency.at("InterestRate").get<double>();
            currenciesOrder[id] = -1;
        }
        else {
            foreignInterestRates.push_back(jsonCurrency.at("InterestRate").get<double>());
            foreignCurrenciesVols.push_back(jsonCurrency.at("Volatility").get<double>());
            currenciesOrder[id] = assetNb + order;
            order++;
        }
    }

    // Assets
    auto jsonAssets = jsonParams.at("Assets");
    int index = 0;
    for (auto jsonAsset: jsonAssets) {
        assetsRealVols.push_back(jsonAsset.at("Volatility").get<double>());
        assetMapping.push_back(currenciesOrder[jsonAsset.at("CurrencyId").get<string>()]);
        assetsCurrencies[jsonAsset.at("CurrencyId").get<string>()].push_back(index);
        index ++;
    }

}


vector<Currency*> Parser::generateCurrencyVector(){
    vector<Currency*> currencyVect;
    for(int index = 0; index < this->foreignInterestRates.size(); index++){
        PnlVect* corrChol = pnl_vect_create(correlationsCholesky->m);
        pnl_mat_get_row(corrChol, correlationsCholesky, this->assetMapping.size()+index);
        currencyVect.push_back(new Currency(domesticInterestRate, foreignInterestRates[index],
                                            foreignCurrenciesVols[index], corrChol));
    }
    return currencyVect;
}


vector<RiskyAsset*> Parser::generateRiskyAssets(){
    vector<Currency*> currencyVect = generateCurrencyVector();
    vector<RiskyAsset*> riskyassetVect;
    PnlVect *corrChol = pnl_vect_create(correlationsCholesky->n);

    for(int index = 0; index < this->assetMapping.size(); index++) {
        pnl_mat_get_row(corrChol, correlationsCholesky, index);
        if (assetMapping[index] == -1) {
            riskyassetVect.push_back(new Asset(domesticInterestRate, assetsRealVols[index],
                                               corrChol, currencyVect.front(), true));
        }
        else{
            riskyassetVect.push_back(new Asset(domesticInterestRate, assetsRealVols[index],
                                               corrChol, currencyVect[assetMapping[index] - assetMapping.size()], false));
        }
    }

    riskyassetVect.insert(riskyassetVect.end(), currencyVect.begin(), currencyVect.end());
    pnl_vect_free(&corrChol);
    return riskyassetVect;
}


Oracle* Parser::generateOracle(){
    string oracleType = jsonParams.at("PortfolioRebalancingOracleDescription").at("Type").get<string>();

    if(oracleType == "Grid"){
        PnlVect* rebalDates;
        jsonParams.at("PortfolioRebalancingOracleDescription").at("DatesInDays").get_to(rebalDates);
        return new GridOracle(rebalDates);
    }
    else if(oracleType == "Fixed"){
        return new FixedOracle(jsonParams.at("PortfolioRebalancingOracleDescription").at("Period").get<int>());
    }
    else{
        throw invalid_argument("Type d'oracle non reconnu");
    }
}


Option* Parser::generateOption() {
    double maturityInYears = (double) jsonParams.at("Option").at("MaturityInDays").get<int>() /numberOfDaysPerYear ;
    string optionType = jsonParams.at("Option").at("Type").get<string>();

    PnlVect* optionDatesInDays;

    if(jsonParams.at("Option").at("FixingDatesInDays").at("Type").get<string>() == "Grid"){
        jsonParams.at("Option").at("FixingDatesInDays").at("DatesInDays").get_to(optionDatesInDays);
        timehandler = new GridTime(optionDatesInDays, numberOfDaysPerYear);
    }
    else if(jsonParams.at("Option").at("FixingDatesInDays").at("Type").get<string>() == "Fixed"){
        timehandler = new FixedTime(jsonParams.at("Option").at("FixingDatesInDays").at("Period").get<int>(),
                                    jsonParams.at("Option").at("MaturityInDays").get<int>()/jsonParams.at("Option").at("FixingDatesInDays").at("Period").get<int>()+1,
                                    numberOfDaysPerYear);
    }
    else{
        throw invalid_argument("FixingDatesInDays type non reconnu");
    }


    if(optionType == "call_quanto"){
        double strike = jsonParams.at("Option").at("Strike").get<double>();
        return new CallQuanto(maturityInYears, assetMapping, strike, domesticInterestRate, foreignInterestRates);
    }
    else if(optionType == "call_currency"){
        double strike = jsonParams.at("Option").at("Strike").get<double>();
        return new CallCurrency(maturityInYears, assetMapping, strike, domesticInterestRate, foreignInterestRates);
    }
    else if(optionType == "quanto_exchange"){
        double strike = jsonParams.at("Option").at("Strike").get<double>();
        return new QuantoExchange(maturityInYears, assetMapping, strike, domesticInterestRate, foreignInterestRates);
    }
    else if(optionType == "foreign_asian"){
        return new ForeignAsian(maturityInYears, assetMapping, domesticInterestRate, foreignInterestRates);
    }
    else if(optionType == "foreign_perf_basket"){
        double strike = jsonParams.at("Option").at("Strike").get<double>();
        return new ForeignPerfBasket(domesticCurrencyId, maturityInYears, assetMapping, assetsCurrencies,
                                     strike, domesticInterestRate, foreignInterestRates, timehandler->ConstatationDates_, numberOfDaysPerYear );
    }
    else{
        throw invalid_argument("Type d'option non reconnu");
    }

}


PnlMat* Parser::getPastPrices(PnlMat* marketData, int actualDate){
    int pastSize = 0, index=0;

    while(pastSize < timehandler->ConstatationDates_->size && pnl_vect_get(timehandler->ConstatationDates_, pastSize) < actualDate){
        pastSize++;
    }
    PnlMat *past = pnl_mat_create_from_zero(pastSize+1, marketData->n);
    PnlVect * dates = pnl_vect_create_from_zero(pastSize+1);
    PnlVect *actualRow = pnl_vect_create_from_zero(marketData->n);
    for (int date = 0; date < marketData->m; ++date) {
        if ( (date == actualDate) || (date < actualDate && containsValue(timehandler->ConstatationDates_, date)) ) {
            pnl_vect_set(dates, index, date);
            pnl_mat_get_row(actualRow, marketData, date);
            pnl_mat_set_row(past, actualRow, index);
            index++;
        }
    }

    adjustPastMatrix(past, dates);
    pnl_vect_free(&dates);
    pnl_vect_free(&actualRow);
    return past;
}

void Parser::adjustPastMatrix(PnlMat* past, PnlVect* dates){
    PnlVect* exchangeRate = pnl_vect_create_from_zero(past->m);
    PnlVect* actualCol  = pnl_vect_create_from_zero(past->m);
    PnlVect* datesForComputation;
    for(int i = 0; i < assetMapping.size(); i++){
        if(assetMapping[i] != -1) {
            pnl_mat_get_col(actualCol, past, i);
            pnl_mat_get_col(exchangeRate, past, assetMapping[i]);
            pnl_vect_mult_vect_term(actualCol, exchangeRate);
            pnl_mat_set_col(past, actualCol, i);
        }
    }

    for(int i = 0; i < foreignInterestRates.size(); i++){
        datesForComputation = pnl_vect_copy(dates);
        pnl_mat_get_col(actualCol, past, i+assetMapping.size());
        generateForeignRiskFreeAsset(datesForComputation, foreignInterestRates[i]);
        pnl_vect_mult_vect_term(actualCol, datesForComputation);
        pnl_mat_set_col(past, actualCol, i+assetMapping.size());
    }

    pnl_vect_free(&exchangeRate);
    pnl_vect_free(&actualCol);
    pnl_vect_free(&datesForComputation);
}

bool Parser::containsValue(PnlVect* vect, int value){
    for(int i = 0; i < vect->size; i++){
        if(pnl_vect_get(vect, i) == value){
            return true;
        }
    }
    return false;
}


void Parser::generateForeignRiskFreeAsset(PnlVect* dates, double interestRate) {
    for (int i = 0; i < dates->size; i++) {
        pnl_vect_set(dates, i, exp(interestRate* (double)pnl_vect_get(dates, i)/numberOfDaysPerYear));
    }
}

