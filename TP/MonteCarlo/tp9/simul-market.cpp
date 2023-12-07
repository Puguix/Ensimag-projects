#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cstdio>

#include "Model.hpp"
#include "Option.hpp"
#include "jlparser/parser.hpp"
#include "MonteCarlo.hpp"

#include "cxxopts.hpp"

using namespace std;
typedef IParser Parser;


int main(int argc, char **argv)
{
    int seed = 0;
    string infile, marketFile;

    cxxopts::Options options("simul-market", "Market simulation");
    options.add_options()
        ("help", "Print help message")
        ("seed", "Fix the seed for the random generator. If none is given, use time(NULL).", cxxopts::value<int>()->default_value("0"))
        ("infile", "Path of the input file", cxxopts::value<std::string>())
        ("market", "Path to the file to store the market simulation", cxxopts::value<std::string>())
    ;

    auto vm = options.parse(argc, argv);
    if (vm.count("help") || !vm.count("infile") || !vm.count("market")) {
        std::cout << options.help();
        return 1;
    }

    infile = vm["infile"].as<std::string>();
    marketFile = vm["market"].as<std::string>();
    seed = vm["seed"].as<int>();

    PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
    if (seed == 0) seed = time(NULL);
    pnl_rng_sseed(rng, seed);

    // model and option initialisation
    Parser map = Parser(infile.c_str());
    Model *mod = instantiate_model(map);
    PnlMat *marketMat = pnl_mat_new();
    mod->simul_market(rng, marketMat);
    FILE *OUT;
    if ((OUT = fopen(marketFile.c_str(), "w")) == NULL) {
        std::cout << "Cannot open file " << marketFile << std::endl;
        abort();
    }
    mod->fprint_market(OUT);
    pnl_mat_fprint(OUT, marketMat);
    fclose(OUT);
    delete mod;
    pnl_mat_free(&marketMat);
    pnl_rng_free(&rng);
    exit(0);
}
