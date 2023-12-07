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
#include "FunctionalHedger.hpp"

#include "cxxopts.hpp"

using namespace std;

double hedgeWrapper(const char *marketFile, const IParser &map, const FunctionalHedger &functionalHedger, PnlRng *rng)
{
    PnlMat *market = pnl_mat_new();
    MonteCarlo mc(rng, map);
    if (marketFile == NULL)
        mc.mod->simul_market(rng, market);
    else
        mc.mod->simul_market(mc.mod->m_modelSize, marketFile, market);
    double price0, var0;
    mc.price(price0, var0);
    double PnL = functionalHedger.pnl(price0, market);
    pnl_mat_free(&market);
    return PnL;
}

void pnlSampleWrapper(string pnlFile, int nPnlSamples, const IParser &map, const FunctionalHedger &functionalHedger, PnlRng *rng)
{
    PnlMat *market = pnl_mat_new();
    MonteCarlo mc(rng, map);
    double price0, stdDev0;
    mc.price(price0, stdDev0);
    printf("mc price: %f\n", price0);
    printf("price std_dev: %f\n", stdDev0);
    fstream out(pnlFile);
    for (int i = 0; i < nPnlSamples; i++) {
        mc.mod->simul_market(rng, market);
        out << functionalHedger.pnl(price0, market) << std::endl;
    }
    pnl_mat_free(&market);
}

int main(int argc, char **argv)
{
    bool hedge = false, verbose = false;
    bool sample_average = false;
    int seed = 0, n_paths = 1;
    string infile, market, pnlFile;

    cxxopts::Options options("functional-hedge", "Functional hedge tool");

    options.add_options()("help", "Print help message")
    ("n,n-paths", "Compute the PNL on n generated market paths.", cxxopts::value<int>()->default_value("1"))
    ("seed", "Fix the seed for the random generator. If none is given, use time(NULL).", cxxopts::value<int>()->default_value("0"))
    ("verbose", "Be more verbose.", cxxopts::value<bool>())
    ("i,infile", "Path to the data file", cxxopts::value<std::string>())
    ("market", "Path to the market file", cxxopts::value<std::string>())
    ("pnlfile", "Path to the PNL file", cxxopts::value<std::string>());

    auto vm = options.parse(argc, argv);
    if (vm.count("help") || !vm.count("infile")) {
        std::cout << options.help();
        return 1;
    }

    n_paths = vm["n-paths"].as<int>();
    verbose = vm["verbose"].as<bool>();
    infile = vm["infile"].as<std::string>();
    if (vm.count("market")) {
        market = vm["market"].as<std::string>();
        hedge = true;
    }
    if (vm.count("pnlfile")) {
        pnlFile = vm["pnlfile"].as<std::string>();
    }
    seed = vm["seed"].as<int>();

    PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
    if (seed == 0) seed = time(NULL);
    pnl_rng_sseed(rng, seed);

    // model and option initialisation
    IParser map = IParser(infile.c_str());
    MonteCarlo mc(rng, map);
    FunctionalHedger functionalHedger(&mc, map);
    functionalHedger.compute();

    if (hedge) {
        hedgeWrapper(market.c_str(), map, functionalHedger, rng);
    } else {
        pnlSampleWrapper(pnlFile, n_paths, map, functionalHedger, rng);
    }

    pnl_rng_free(&rng);
    exit(0);
}
