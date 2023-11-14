// vim: set sw=4 ts=4 sts=4:
#include <iostream>
#include <cmath>
#include "MonteCarlo.hpp"
#include "pnl/pnl_cdf.h"

MonteCarlo::MonteCarlo(BSCall &product, int samples)
    : m_product(product), m_samples(samples)
{}

void MonteCarlo::brownien(PnlVect* g, PnlVect* gPrime){
    double ecart = sqrt(m_product.m_maturity/gPrime->size);
    pnl_vect_set (gPrime, 0, 0.0);
    for (int i = 1; i < gPrime->size; i++){
        pnl_vect_set (gPrime, i, pnl_vect_get(gPrime, i-1)+ecart*pnl_vect_get(g,i-1));
    }
}

double MonteCarlo::trapeze(PnlVect* sousJacent, double T){ /* J pas de temps*/
    double somme = 0;
    double pas =  T / (sousJacent->size - 1);
    for (int i = 1; i< sousJacent->size; i++){
        somme += (pnl_vect_get(sousJacent,i-1)+pnl_vect_get(sousJacent,i))/2*pas;
    }
    return somme/T;
}

double MonteCarlo::trapezelog(PnlVect* sousJacent, double T){ /* J pas de temps*/
    double somme = 0;
    double pas =  T / (sousJacent->size - 1);
    for (int i = 1; i< sousJacent->size; i++){
        somme += (std::log(pnl_vect_get(sousJacent,i-1))+std::log(pnl_vect_get(sousJacent,i)))/2*pas;
    }
    return somme/T;
}


void MonteCarlo::mc(double &prixX, double &prixY, double &prixZ, double &stddev, double &stddevY, double &stddevZ, PnlRng *rng)
{
    double sumX = 0.;
    double sumY = 0.;
    double sumZ = 0.;
    double varY = 0.;
    double var = 0.;
    double varZ = 0.;
    double truuc = 0.;
    PnlVect *path = pnl_vect_create(m_product.m_dates + 1);
    PnlVect *G = pnl_vect_new();
    for (size_t i = 0; i < m_samples; i++) {
        pnl_vect_rng_normal(G, m_product.m_dates, rng);
        brownien(G, path);
        m_product.sousJacent(path);
        double flow = trapeze(path, m_product.m_maturity);
        double payoffX =std::max(flow - m_product.m_strike, 0.)* std::exp(-m_product.m_interest_rate * m_product.m_maturity);
        double payoffY = std::exp(trapezelog(path, m_product.m_maturity));
        double payoffZ =std::max(payoffY - m_product.m_strike, 0.)* std::exp(-m_product.m_interest_rate * m_product.m_maturity);
        sumX += payoffX;
        sumY += payoffX - payoffY;
        sumZ += payoffX - payoffZ;
        var += pow(payoffX, 2);
        varY += pow(payoffX - payoffY, 2);
        varZ += pow(payoffX - payoffZ, 2);
        truuc += payoffZ;
    }
    double esperanceY = m_product.m_spot * std::exp(m_product.m_interest_rate * m_product.m_maturity / 2 - m_product.m_volatility*m_product.m_volatility*m_product.m_maturity/12);

    
    double d1 = -1/m_product.m_volatility * std::sqrt(3/m_product.m_maturity)*(std::log(m_product.m_strike/m_product.m_spot) - (m_product.m_interest_rate - pow(m_product.m_volatility, 2)/2)*m_product.m_maturity/2);
    double d2 = d1 + m_product.m_volatility * std::sqrt(m_product.m_maturity/3);
    int which = 1; double bound = 2; int status = 0; double mean = 0; double std = 1; double q; double p1; double p2;

    double part1 = -m_product.m_strike*cdf_nor(d1);
    double part2 = m_product.m_spot*std::exp((m_product.m_interest_rate - pow(m_product.m_volatility,2)/6)*m_product.m_maturity/2)*cdf_nor(d2);
    double esperanceZ = m_product.m_discount*(part1+part2);
    prixX = sumX / m_samples;
    prixY =  esperanceY +  sumY / m_samples;
    prixZ = esperanceZ + sumZ / m_samples; //TODO : remplacer truuc/m_samples par esperanceZ. Pour l'instant esperanceZ est faux.

    stddev = std::sqrt((var / m_samples - pow(prixX, 2))/m_samples);
    stddevY = std::sqrt((varY / m_samples - pow(sumY/m_samples, 2))/m_samples);
    stddevZ = std::sqrt((varZ / m_samples - pow(sumZ/m_samples, 2))/m_samples);

    pnl_vect_free(&path);
    pnl_vect_free(&G);
}


void MonteCarlo::mcBar(double &prixX, double &prixY, double &stddevX, double &stddevY, PnlRng *rng){
    double sumX = 0.;
    double sumY = 0.;
    double varX = 0.;
    double varY = 0.;
    PnlVect *path = pnl_vect_create(m_product.m_dates + 1);
    PnlVect *G = pnl_vect_new();
    for (size_t i = 0; i < m_samples; i++) {
        pnl_vect_rng_normal(G, m_product.m_dates, rng);
        brownien(G, path);
        m_product.sousJacent(path);
        double payoffX = m_product.payoffBarrier(path);
        sumX += payoffX;
        varX += pow(payoffX, 2);

        double payoffY = m_product.payoffBarrierAm(path);
        sumY += payoffY;
        varY += pow(payoffY, 2);
    }

    prixX = sumX / m_samples;
    prixY = sumY / m_samples;

    stddevX = std::sqrt((varX / m_samples - pow(prixX, 2))/m_samples);
    stddevY = std::sqrt((varY / m_samples - pow(prixY, 2))/m_samples);

    pnl_vect_free(&path);
    pnl_vect_free(&G);
}