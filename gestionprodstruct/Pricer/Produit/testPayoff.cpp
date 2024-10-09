//#include <iostream>
//#include "eurostralProduct.hpp"
//
//using namespace std;
//
//
//int main(int argc, char *argv[]) {
//
//    PnlVect* constaDates = pnl_vect_create_from_zero(4);
//    pnl_vect_set(constaDates, 0, 13);
//    pnl_vect_set(constaDates, 1, 27);
//    pnl_vect_set(constaDates, 2, 33);
//    pnl_vect_set(constaDates, 3, 40);
//
//    PnlVect* interestRates = pnl_vect_create_from_scalar(2, 0.2);
//
//    eurostralProduct product = eurostralProduct(50, 0.1, 252, constaDates, interestRates);
//
////    Scenario 1
//    PnlMat* path = pnl_mat_create_from_list(6, 3,
//    17134.93, 6961.73, 10323.75,
//    14352.77, 6056.84,  7748.32,
//    10845.63,  4195.95, 7013.39,
//    13310.47,  3241.04, 6990.3,
//    21568.36,  3998.77, 8487.31,
//    24674.77,  4603.65, 10075.13);
//
////    Scenario 2
////    PnlMat* path = pnl_mat_create_from_list(6, 3,
////    24848.04, 4290.5, 9142.98,
////    35002.37, 5523.62, 11501.48,
////    44019.77, 6674.4, 12553.6,
////
////    61036.61, 7808.69, 13778.58,
////
////    41518.66, 4983.99,  9285.51,
////    70045.08, 6048.3,  11866.9);
//
//
////    Scenario 3
////    PnlMat* path = pnl_mat_create_from_list(6, 3,
////    41518.66, 4983.99, 9285.51,
////    70045.08, 6048.3, 11866.9,
////    70317.79, 6975.35, 13402.31,
////    59364.95, 6111.55, 12226.47,
////    62523.06, 7776.37, 12540.81,
////    50973.62, 9428.0, 13495.54);
//    cout << "Path" <<  endl;
//    pnl_mat_print(path);
//
//    cout << "constat dates" <<  endl;
//    pnl_vect_print(constaDates);
//    cout <<  endl;
//
//    double dividend1 = product.dividend(path, 13);
//    double dividend2 = product.dividend(path, 27);
//    double dividend3 = product.dividend(path, 33);
//    double dividend4 = product.dividend(path, 40);
//
//    double payoffMaturity = product.payoff(path, 50);
//
//    cout <<  endl;
//    cout << "Dividend: " << endl;
//    cout << dividend1 << endl;
//    cout << dividend2 << endl;
//    cout << dividend3 << endl;
//    cout << dividend4 << endl;
//    cout <<  endl;
//
//
//    cout << "Payoff at Maturity: " << endl;
//    cout << payoffMaturity << endl;
//
//}