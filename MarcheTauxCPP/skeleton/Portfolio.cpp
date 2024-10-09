#include <iostream>
#include "Portfolio.hpp"
#include "Tools/json_reader.hpp"


Position::Position(int date, double price, double priceStdDev, PnlVect* deltas, PnlVect* deltasStdDev, double portfolioValue){
    this->date = date;
    this->price = price;
    this->priceStdDev = priceStdDev;
    this->deltas = deltas;
    this->deltasStdDev = deltasStdDev;
    this->portfolioValue = portfolioValue;
}

void to_json(nlohmann::json &j, const Position &position) {
    j["date"] = position.date;
    j["value"] = position.portfolioValue;
    j["price"] = position.price;
    j["priceStdDev"] = position.priceStdDev;
    j["deltas"] = position.deltas;
    j["deltasStdDev"] = position.deltasStdDev;
}

void Position::print() const {
    nlohmann::json j = *this;
    std::cout << j.dump(4);
}

Portfolio::Portfolio(double domesticInterestRate, int numberDaysYear, PnlVect *spots,
                     PnlVect *deltas, PnlVect* deltasStdDev, double price, double priceStdDev) {
    this->lastUpdateDate = 0;
    this->numberDaysYear = numberDaysYear;
    this->domesticInterestRate = domesticInterestRate;
    this-> portfolioValue = price;
    this->deltas = deltas;
    this->quantiteSansRisque = price - pnl_vect_scalar_prod(spots, deltas) ;
    positions.push_back(Position(0, price, priceStdDev, pnl_vect_copy(deltas), pnl_vect_copy(deltasStdDev), price));
}

double Portfolio::computeValueAndUpdate(int actualDate, PnlVect *newDelta, PnlVect *marketData) {
    pnl_vect_minus_vect(this->deltas, newDelta);
    this->quantiteSansRisque = pnl_vect_scalar_prod(this->deltas, marketData) + this->quantiteSansRisque*exp(domesticInterestRate*(actualDate-this->lastUpdateDate)/numberDaysYear);
    this->deltas = newDelta;
    this->lastUpdateDate = actualDate;
    this->portfolioValue = pnl_vect_scalar_prod(this->deltas, marketData) + this->quantiteSansRisque;
    return this->portfolioValue;
}
