// Tests de la fonction asset de BlackScholesModel en t=0

#include "../src/MonteCarlo.hpp"
#include "../src/BlackScholesModel.hpp"
#include "../src/Basket.hpp"
#include "../src/Asian.hpp"
#include "../src/Performance.hpp"
#include "../src/json_helper.hpp"
#include "../src/PricingResults.hpp"
#include <iostream>
#include <fstream>

int
main(int argc, char const* argv[])
{
    // Verify we have a file passed as argument

    if (argc != 2) {
        std::cerr << "Wrong number of arguments. Exactly two argument is required" << std::endl;
        std::cerr << "Use: ./<name> <inputFile.json> <outputFile.json>" << std::endl;
        std::exit(1);
    }

    // Open and parse the json
    std::ifstream ifs(argv[1]);
    nlohmann::json j = nlohmann::json::parse(ifs);

    // Instanciate the option
    std::string option_type;
    j.at("option type").get_to(option_type);
    PnlVect* coef;
    j.at("payoff coefficients").get_to(coef);
    if (coef->size == 1) {
        pnl_vect_resize_from_scalar(coef, j.at("option size").get<double>(), GET(coef, 0));
    }

    Option* o;
    if (option_type == "basket") {
        o = new Basket(j.at("strike").get<double>(), coef, j.at("maturity").get<double>(), j.at("timestep number").get<int>(), j.at("option size").get<int>());
    } else if (option_type == "asian") {
        o = new Asian(j.at("strike").get<double>(), coef, j.at("maturity").get<double>(), j.at("timestep number").get<int>(), j.at("option size").get<int>());
    } else {
        o = new Performance(coef, j.at("maturity").get<double>(), j.at("timestep number").get<int>(), j.at("option size").get<int>());
    }

    // Instanciate the BlackScholes model
    PnlVect* vol;
    j.at("volatility").get_to(vol);
    if (vol->size == 1) {
        pnl_vect_resize_from_scalar(vol, j.at("option size").get<double>(), GET(vol, 0));
    }
    PnlVect* spot;
    j.at("spot").get_to(spot);
    if (spot->size == 1) {
        pnl_vect_resize_from_scalar(spot, j.at("option size").get<double>(), GET(spot, 0));
    }
    BlackScholesModel* bsm = new BlackScholesModel(j.at("option size").get<double>(), j.at("interest rate").get<double>(), j.at("correlation").get<double>(), vol, spot);

    // Instanciate the Monte Carlo method
    MonteCarlo* mc = new MonteCarlo(bsm, o, j.at("fd step").get<double>(), j.at("sample number").get<int>());

    // Put here the main computations
    double prix;
    double priceStd;
    mc->price(prix, priceStd);
    PnlVect* delta = pnl_vect_create(j.at("option size").get<int>());
    PnlVect* deltaStd = pnl_vect_create(j.at("option size").get<int>());
    mc->delta(delta, deltaStd);

    // Create the result
    PricingResults res(prix, priceStd, delta, deltaStd);
    std::cout << res << std::endl;

    delete mc;

    exit(0);
}
