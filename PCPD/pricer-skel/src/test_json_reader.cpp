#include <iostream>
#include <fstream>
#include "json_helper.hpp"

int
main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "Wrong number of arguments. Exactly one argument is required" << std::endl;
        std::exit(0);
    }
    std::ifstream ifs(argv[1]);
    nlohmann::json j = nlohmann::json::parse(ifs);
    int size;
    std::string option_type;
    PnlVect* volatility;
    option_type = j.at("option type").get<std::string>();
    j.at("model size").get_to(size);
    j.at("volatility").get_to(volatility);
    if (volatility->size == 1 && size > 1) {
        pnl_vect_resize_from_scalar(volatility, size, GET(volatility, 0));
    }

    nlohmann::json jout = {
        { "model size", size },
        { "option type", option_type },
        { "vol", volatility }
    };
    std::cout << jout << std::endl;
    pnl_vect_free(&volatility);
    exit(0);
}