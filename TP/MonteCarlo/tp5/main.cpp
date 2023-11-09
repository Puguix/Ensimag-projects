#include <tuple>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <ctime>
#include "pnl/pnl_finance.h"
#include "pnl/pnl_vector.h"
#include "pnl/pnl_random.h"
#include "pnl/pnl_cdf.h"

PnlVect *simuAsset(double spot, double r, double vol, int T, double J, PnlRng *rng)
{
    double ecart = sqrt(T / J);
    PnlVect *asset = pnl_vect_create(J + 1);
    pnl_vect_rng_normal(asset, J + 1, rng);
    pnl_vect_set(asset, 0, 0.0);
    for (int i = 1; i < asset->size; i++)
    {
        pnl_vect_set(asset, i, pnl_vect_get(asset, i - 1) + ecart * pnl_vect_get(asset, i - 1));
    }

    pnl_vect_set(asset, 0, spot);

    for (int i = 1; i <= J; i++)
    {
        double value = pnl_vect_get(asset, i);
        pnl_vect_set(asset, i, spot * exp((r - pow(vol, 2) / 2) * i * T / J + vol * value));
    }
}

double integrale(PnlVect *asset, double T)
{
    double res = 0;
    double pas = T / (asset->size - 1);

    for (int i = 1; i < asset->size; i++)
    {
        res += (GET(asset, i - 1) + GET(asset, i)) / 2 * pas;
    }

    return res / T;
}

std::tuple<double, double> asian(double spot, double vol, double r, double T, double K, int N, int J, PnlRng *rng)
{
    double mean = 0;
    double var = 0;
    PnlVect *asset;
    double I;
    double tmp;

    for (int i = 0; i < N; i++)
    {
        asset = simuAsset(spot, r, vol, T, J, rng);
        I = integrale(asset, T);
        tmp = std::exp(-r * T) * std::max(I - K, 0.);
        // std::cout << tmp << "\n";
        mean += tmp;
        var += SQR(tmp);
        pnl_vect_free(&asset);
    }
    mean /= N;

    return std::make_tuple(mean, var / N - SQR(mean));
}

double meanY(double spot, double vol, double r, double T)
{
    return spot * std::exp(r * T / 2 - vol * vol * T / 12);
}

double integraleLog(PnlVect *asset, double T)
{
    double res = 0;
    double pas = T / (asset->size - 1);

    for (int i = 1; i < asset->size; i++)
    {
        res += (std::log(GET(asset, i - 1)) + std::log(GET(asset, i))) / 2 * pas;
    }

    return res / T;
}

double lambdaY(double spot, double vol, double r, double T, int N, int J, PnlRng *rng)
{
    double meanXY = 0;
    double meanYY = 0;
    PnlVect *asset;

    for (int i = 0; i < N; i++)
    {
        asset = simuAsset(spot, r, vol, T, J, rng);
        double X = integrale(asset, T);
        double Y = std::exp(integraleLog(asset, T));
        meanXY += X * Y;
        meanYY += Y * Y;
        pnl_vect_free(&asset);
    }
    return meanXY / meanYY;
}

std::tuple<double, double> controlY(double spot, double vol, double r, double T, double K, int N, int J, PnlRng *rng)
{
    double mean = 0;
    double meanLog = 0;
    double var = 0;
    PnlVect *asset;
    double I;
    double Ilog;
    double tmp;
    double l = lambdaY(spot, vol, r, T, N, J, rng);
    std::cout << "lambda " << l << "\n";

    for (int i = 0; i < N; i++)
    {
        asset = simuAsset(spot, r, vol, T, J, rng);
        I = integrale(asset, T);
        Ilog = integraleLog(asset, T);
        tmp = std::exp(-r * T) * std::max(I - K, 0.) - l * std::exp(Ilog);
        mean += tmp;
        meanLog += std::exp(Ilog);
        var += SQR(tmp);
        pnl_vect_free(&asset);
    }
    std::cout << "mealong " << meanLog / N << "\n";
    mean = l * meanY(spot, vol, r, T) + mean / N;

    return std::make_tuple(mean, var / N - SQR(mean));
}

double meanZ(double spot, double vol, double r, double T, double K)
{
    double n1, n2, q;
    int which = 2;
    double d1 = -std::sqrt(3 / T) * (std::log(K / spot) - (r - vol * vol / 2) * T / 2) / vol;
    double d2 = d1 + vol * std::sqrt(T / 3);
    double mean = 0.;
    double stdDev = 1.;
    int status;
    double bound;
    pnl_cdf_nor(&which, &n1, &q, &d1, &mean, &stdDev, &status, &bound);
    pnl_cdf_nor(&which, &n2, &q, &d2, &mean, &stdDev, &status, &bound);
    return std::exp(-r * T) * (-K * n1 + spot * std::exp((r - vol * vol / 6) * T / 2) * n2);
}

double lambdaZ(double spot, double vol, double r, double T, int N, int J, PnlRng *rng)
{
    double meanXY = 0;
    double meanYY = 0;
    PnlVect *asset;

    for (int i = 0; i < N; i++)
    {
        asset = simuAsset(spot, r, vol, T, J, rng);
        double X = integrale(asset, T);
        double Y = integraleLog(asset, T);
        meanXY += X * Y;
        meanYY += Y * Y;
        pnl_vect_free(&asset);
    }
    return meanXY / meanYY;
}

std::tuple<double, double> controlZ(double spot, double vol, double r, double T, double K, int N, int J, PnlRng *rng)
{
    double mean = 0;
    double var = 0;
    PnlVect *asset;
    double I;
    double Ilog;
    double tmp;
    double l = lambdaZ(spot, vol, r, T, N, J, rng);
    std::cout << "lambda " << l << "\n";

    for (int i = 0; i < N; i++)
    {
        asset = simuAsset(spot, r, vol, T, J, rng);
        I = integrale(asset, T);
        Ilog = integraleLog(asset, T);
        tmp = std::exp(-r * T) * std::max(I - K, 0.) - l * std::exp(Ilog);
        mean += tmp;
        var += SQR(tmp);
        pnl_vect_free(&asset);
    }
    mean = l * meanZ(spot, vol, r, T, K) + mean / N;

    return std::make_tuple(mean, var / N - SQR(mean));
}

int main(int argc, char const *argv[])
{
    // Instanciate parameters
    double spot = 100;
    double K = 100;
    double r = 0.095;
    double vol = 0.2;
    double T = 1.;
    int J = 100;
    int nbSample = 50000;

    PnlRng *rng = pnl_rng_create(PNL_RNG_MERSENNE);
    pnl_rng_sseed(rng, std::time(NULL));

    // PnlVect *asset = simuAsset(spot, r, vol, T, J, rng);
    // std::cout << "Prix sous jacent:\n";
    // pnl_vect_print(asset);

    // double I = integrale(asset, T);
    // std::cout << "Integrale: " << I << "\n";

    double price, var;
    std::tie(price, var) = asian(spot, vol, r, T, K, nbSample, J, rng);
    std::cout << "Prix option asiatique: " << price << "\n";
    std::cout << "Ecart type option asiatique: " << std::sqrt(var) << "\n";

    double espY = meanY(spot, vol, r, T);
    std::cout << "Esperance de Y: " << espY << "\n";

    std::tie(price, var) = controlY(spot, vol, r, T, K, nbSample, J, rng);
    std::cout << "Prix option asiatique controlé par Y: " << price << "\n";
    std::cout << "Ecart type option asiatique controlé par Y: " << std::sqrt(var) << "\n";

    // double espZ = meanZ(spot, vol, r, T, K);
    // std::cout << "Esperance de Z: " << espZ << "\n";

    // std::tie(price, var) = controlZ(spot, vol, r, T, K, nbSample, J, rng);
    // std::cout << "Prix option asiatique controlé par Z: " << price << "\n";
    // std::cout << "Ecart type option asiatique controlé par Z: " << std::sqrt(var) << "\n";

    return 0;
}
