#include <fstream>
#include "Pricer.hpp"

int main(int argc, char *argv[]) {
    Pricer* pricer = new Pricer(argv[1]);
    PnlMat* past = pnl_mat_create(1,5);
    past->array[0] = 6961.73;
    past->array[1] = 17134.93;
    past->array[2]= 10323.75;
    past->array[3]= 0.582368513710527;
    past->array[4]= 0.704787146881377;
    double price, priceStdDev;
    PnlVect *delta, *deltaStdDev;

    pricer->priceAndDeltas(past, 0, true, price, priceStdDev, delta, deltaStdDev);
    std::cout << price << endl;
    pnl_vect_print(delta);
}