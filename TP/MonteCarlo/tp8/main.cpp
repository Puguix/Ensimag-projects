#include <ctime>
#include <iostream>

#include "AsianOption.hpp"
#include "BlackScholes.hpp"
#include "MonteCarlo.hpp"

int main(int argc, char **argv)
{
  BlackScholesModel bs = BlackScholesModel(0.03, 100., 0.3);
  AsianOption asianOption = AsianOption(110, 2);
  PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
  pnl_rng_sseed(rng, std::time(NULL));
  MonteCarlo mc = MonteCarlo(&asianOption, &bs, rng);

  double prix, std_dev;
  int nTimeSteps = 50;
  long long nSamples = 1E5;
  double alpha = 0.8;
  long long mSamples = 100;
  mc.run(prix, std_dev, nSamples, nTimeSteps);

  std::cout << "Monte Carlo:\n";
  std::cout << "\tPrice: " << prix << "\n";
  std::cout << "\tCI width: " << std_dev * 1.96 * 2 << "\n";

  mc.runNested(prix, std_dev, alpha, nSamples, mSamples, nTimeSteps);

  std::cout << "Nested Monte Carlo:\n";
  std::cout << "\tPrice: " << prix << "\n";
  std::cout << "\tCI width: " << std_dev * 1.96 * 2 << "\n";

  pnl_rng_free(&rng);
  return 0;
}