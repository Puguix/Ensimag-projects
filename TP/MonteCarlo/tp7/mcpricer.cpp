#include <ctime>
#include <iostream>

#include "AsianOption.hpp"
#include "Heston.hpp"
#include "MonteCarlo.hpp"

int main(int argc, char **argv)
{
  HestonModel hestonModel = HestonModel(0.03, 100, 0.04, 0.01, 2, 0.04, -0.2);
  AsianOption asianOption = AsianOption(110, 2);
  PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
  pnl_rng_sseed(rng, std::time(NULL));
  MonteCarlo mc = MonteCarlo(&asianOption, &hestonModel, rng);

  double prix, std_dev;
  int nTimeSteps = 50;
  long long nSamples = 1E5;
  mc.run(prix, std_dev, nSamples, nTimeSteps);

  // PnlMat *G = pnl_mat_create(nTimeSteps, 2);
  // pnl_mat_rng_normal(G, nTimeSteps, 2, rng);
  // PnlVect *path = pnl_vect_create(nTimeSteps);
  // hestonModel.simul(path, asianOption.m_maturity, nTimeSteps, G);
  // pnl_vect_print(path);

  std::cout << "Price: " << prix << "\n";
  std::cout << "CI width: " << std_dev * 1.96 * 2 << "\n";

  pnl_rng_free(&rng);
  return 0;
}