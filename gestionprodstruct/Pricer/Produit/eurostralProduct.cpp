#include <stdexcept>
#include <cmath>
#include "eurostralProduct.hpp"

#include <iostream>
using namespace std;

eurostralProduct::eurostralProduct(int maturity, PnlVect *interestRates, TimeHandler* timeHandler) {
    this->maturity = maturity;
    this->numberDaysYear = timeHandler->nbDaysInYear_;
    this->constaDates = pnl_vect_create_from_zero(4);
    for(int i =1; i<5; i++){
        pnl_vect_set(constaDates, i-1, GET(timeHandler->ConstatationDates_,i));
    }
    this->interestRates = interestRates;
    this->domesticRate = GET(interestRates,0);
}

double eurostralProduct::payoff(const PnlMat *currentPath, int currentDate) {
    PnlMat* path = adjustPathMatrix(currentPath);

    double finalMeanPerf = 0;
    double totalDiscountedDividends = 0;
    double dividend;
    PnlVect* perfs = pnl_vect_create_from_zero(3);

    for(int dateIndex = 1; dateIndex < path->m; dateIndex++){
        for(int assetIndex = 0; assetIndex < 3; assetIndex++) {
            pnl_vect_set(perfs, assetIndex,
                         pnl_mat_get(path, dateIndex, assetIndex)/pnl_mat_get(path, 0, assetIndex) - 1
                         );
        }

        pnl_vect_qsort(perfs, 'd');
        finalMeanPerf += 0.5 * pnl_vect_get(perfs, 0) + 0.3 * pnl_vect_get(perfs, 1) + 0.2 * pnl_vect_get(perfs, 2);

        if(dateIndex < 4 && pnl_vect_get(constaDates, dateIndex-1) >= currentDate) {
            dividend = 100 * pnl_vect_get(perfs, 1) / (2 * (dateIndex));
            totalDiscountedDividends += (dividend > 0 )? discount(100 * pnl_vect_get(perfs, 1) / (2 * dateIndex),
                                                                  pnl_vect_get(constaDates, dateIndex-1), currentDate) : 0;
        }
    }

    finalMeanPerf /= constaDates->size + 1;
    finalMeanPerf = (finalMeanPerf > 0)? finalMeanPerf : 0;

    return discount((0.9 + 0.3*finalMeanPerf)*1000, maturity, currentDate) + totalDiscountedDividends;

}


double eurostralProduct::dividend(const PnlMat *path, int currentDate){

    int currentDateIndex = -1;
    PnlVect* perfs = pnl_vect_create_from_zero(3);
    currentDate = int(currentDate);

    for (int i = 0; i < constaDates->size; i++) {
        if (int(pnl_vect_get(constaDates, i)) == currentDate) {
            currentDateIndex = i+1;
            break;
        }
    }

    if(currentDateIndex == -1 ){
        throw std::invalid_argument("Ce n'est pas une date de versement de dividende");
    }

    for(int assetIndex = 0; assetIndex < 3; assetIndex++) {
        pnl_vect_set(perfs, assetIndex,
                     pnl_mat_get(path, currentDateIndex, assetIndex)/pnl_mat_get(path, 0, assetIndex) - 1);
    }
    pnl_vect_qsort(perfs, 'd');

    double dividend = 100 * pnl_vect_get(perfs, 1) / (2 * currentDateIndex);
    return  (dividend > 0)? dividend : 0;
}



double eurostralProduct::discount(double value, double maturityDay, double date){

    return exp(-domesticRate* (double)(maturityDay - date)/numberDaysYear )* value;
}


PnlMat* eurostralProduct::adjustPathMatrix(const PnlMat *path) {
    PnlVect* dates = pnl_vect_copy(constaDates);
    int size = dates -> size;
    pnl_vect_resize(dates, size + 2);
    pnl_vect_set(dates, size, 0);
    pnl_vect_set(dates, size + 1, maturity);

    pnl_vect_qsort(dates, 'i');

    PnlMat* adjustedPath = pnl_mat_copy(path);

    for(int i = 0; i < adjustedPath->m; i++){
        for(int j = 1; j <= 2; j++){
            pnl_mat_set(adjustedPath, i, j,
                        pnl_mat_get(adjustedPath, i, j) / pnl_mat_get(adjustedPath, i, j+2) * exp(-pnl_vect_get(interestRates, j) * pnl_vect_get(dates, i)/numberDaysYear ) );
        }
    }

    return adjustedPath;
}





