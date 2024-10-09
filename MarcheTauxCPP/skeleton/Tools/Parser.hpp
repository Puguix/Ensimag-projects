#include <fstream>
#include <nlohmann/json.hpp>
#include "pnl/pnl_vector.h"
#include <vector>
#include <map>
#include "../Options/CallCurrency.hpp"
#include "../Options/CallQuanto.hpp"
#include "../Options/ForeignAsian.hpp"
#include "../Options/ForeignPerfBasket.hpp"
#include "../Options/QuantoExchange.hpp"
#include "../GlobalModel.hpp"
#include "../Oracle/FixedOracle.hpp"
#include "../Oracle/GridOracle.hpp"
#include "../TimeHandler/GridTime.hpp"
#include "../TimeHandler/FixedTime.hpp"

using namespace std;


class Parser {
public:
    nlohmann::json jsonParams;
    string domesticCurrencyId;
    int sampleNb;
    int numberOfDaysPerYear;
    double domesticInterestRate;
    double finiteDifferenceStep;
    vector<int> assetMapping; /*! Pour chaque actif contient l'indice du taux de change dans la matrice de corrélation */
    vector<double> foreignInterestRates;
    vector<double> foreignCurrenciesVols;
    vector<double> assetsRealVols;
    map<string, vector<int>> assetsCurrencies; /*! Pour chaque devise contient la liste des indices de ses actifs dans la matrice de corrélation  */
    PnlMat* correlationsCholesky;
    TimeHandler* timehandler;


    /**
     * Constructeur de la classe
     * @param[in] filePath chemin vers les paramètres de l'option
     */
    Parser(char *filePath);


    /**
     * Construit le vecteur des "Currency"
     * @return vector<Currency*>
     */
    vector<Currency*> generateCurrencyVector();


    /**
     * Construit la liste des "RiskyAsset" (les actifs risqués étrangers)
     * @return vector<RiskyAsset*>
     */
    vector<RiskyAsset*> generateRiskyAssets();


    /**
     * Construit l'oracle
     * @return Oracle*
     */
    Oracle* generateOracle();


    /**
     * Construit l'option considérée
     * @return Option*
     */
    Option* generateOption();


    /**
     * Construit la matrice "past" contenant les données historiques
     * @param[in] marketData données du marché
     * @param[in] constaDates les dates de constations
     * @param[in] actualDate date actuelle
     * @param[out] past matrice contenant les données historiques
     * @return PnlMat*
     */
    PnlMat* getPastPrices(PnlMat* marketData, int actualDate);



    bool containsValue(PnlVect* vect, int value);

    ~Parser(){
        pnl_mat_free(&correlationsCholesky);
        delete timehandler;
    }

private:
    void adjustPastMatrix(PnlMat* past, PnlVect* dates);
    void generateForeignRiskFreeAsset(PnlVect* vect, double interestRate);
};