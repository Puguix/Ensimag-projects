#include "pnl/pnl_random.h"
#include "pnl/pnl_mathtools.h"
#include "pnl/pnl_vector.h"
#include "pnl/pnl_specfun.h"
#include "pnl/pnl_finance.h"

#include "MonteCarlo.hpp"
#include "BSCall.hpp"
#include <iostream>
#include <cmath>
#include <math.h>



int main()
{
    PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(rng, time(NULL));

    double prix, prixY, prixZ, stddev, stddevY, stddevZ;
    
    //Exo 1
    BSCall product(1., 0.2, 0.095, 100., 100., 24);
    MonteCarlo pricer(product, 50000);
    pricer.mc(prix, prixY, prixZ, stddev, stddevY, stddevZ, rng);
    std::cout << "prixX : " << prix << " ICX = " << stddev * 1.96 << "\n";
    std::cout << "prixY : " << prixY <<" ICY : " << stddevY * 1.96 << "\n";
    std::cout << "prixZ : " << prixZ <<" ICZ : " << stddevZ * 1.96 << "\n";

    //Exo 2
    BSCall barrier(1., 0.25, 0.02, 100., 105., 90., 24);
    MonteCarlo monte(barrier, 50000);
    monte.mcBar(prix, prixY, stddev, stddevY, rng);
    std::cout << "Barriere Basse : \n";
    std::cout << "prixX : " << prix << " ICX = " << stddev * 1.96 << "\n";
    for (int i = 5; i < 50; i+=5){
        barrier.m_dates = i;
        monte.mcBar(prix, prixY, stddev,stddevY, rng);
        std::cout << "Avec J en standard : " << i << " prixX : " << prix << " ICX = " << stddev * 1.96 << "\n";
        std::cout << "Avec J en avancé : " << i << " prixY : " << prixY << " ICY = " << stddevY * 1.96 << "\n";
    }

}