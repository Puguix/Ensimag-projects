#include <ctime>
#include <iostream>

#include "AsianOption.hpp"
#include "Heston.hpp"
#include "MultiLevelMonteCarlo.hpp"

int main(int argc, char **argv)
{
  HestonModel hestonModel = HestonModel(0.03, 100, 0.04, 0.01, 2, 0.04, -0.2);
  AsianOption asianOption = AsianOption(110, 2);
  PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
  pnl_rng_sseed(rng, std::time(NULL));
  MultiLevelMonteCarlo mc = MultiLevelMonteCarlo(&asianOption, &hestonModel, rng);

  double prix, std_dev;
  mc.run(prix, std_dev, 4, 3);

  std::cout << "Price: " << prix << "\n";
  std::cout << "CI width: " << std_dev * 1.96 * 2 << "\n";

  pnl_rng_free(&rng);
  return 0;
}
