#include <iostream>
#include <string>
#include <fstream>

#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <nlohmann/json.hpp>

#include "pnl/pnl_matrix.h"
#include "GrpcPricer.grpc.pb.h"
#include "Pricer.hpp"
#include "Portfolio.hpp"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

PnlMat* convertPastToPnlMat(const PricingInput *input) {
    // Find size
    int m, n;
    m = input->past_size();
    if (m == 0) {
        return NULL;
    }
    n = input->past(0).value_size();
    for (int i = 0; i < input->past_size(); i++) {
        const PastLines &pastLine = input->past(i);
        if (pastLine.value_size() !=n) {
            std::cerr << "size mismatch in past" << std::endl;
            return NULL;
        }
    }
    // Parse data
    PnlMat *past = pnl_mat_create(m, n);
    for (int i = 0; i < input->past_size(); i++) {
        const PastLines &pastLine = input->past(i);
        for (int j = 0; j < pastLine.value_size(); j++) {
            MLET(past, i, j ) = pastLine.value(j);
        }
    }
    return past;
}


PnlMat* convertPastToPnlMat(const HedgingInput *input) {
    // Find size
    int m, n;
    m = input->past_size();
    if (m == 0) {
        return NULL;
    }
    n = input->past(0).value_size();
    for (int i = 0; i < input->past_size(); i++) {
        const PastLines &pastLine = input->past(i);
        if (pastLine.value_size() !=n) {
            std::cerr << "size mismatch in past" << std::endl;
            return NULL;
        }
    }
    // Parse data
    PnlMat *past = pnl_mat_create(m, n);
    for (int i = 0; i < input->past_size(); i++) {
        const PastLines &pastLine = input->past(i);
        for (int j = 0; j < pastLine.value_size(); j++) {
            MLET(past, i, j ) = pastLine.value(j);
        }
    }
    return past;
}


// Logic and data behind the server's behavior.
class GrpcPricerImpl final : public GrpcPricer::Service {
private:
    int maturity;
    PnlVect *interestRates;
public:
    GrpcPricerImpl() {}

    Status PriceAndDeltas(ServerContext *context, const PricingInput *input, PricingOutput *output) override {
        double price, priceStdDev;
        double div;
        PnlVect *delta, *deltaStdDev;
        bool isMonitoringDate = input->monitoringdatereached();
        double currentDate = input->time();
        const char* jsonFilePath = input->jsonfile().c_str();

        PnlMat *past = convertPastToPnlMat(input);
        if (past == NULL) {
            return Status(grpc::StatusCode::INVALID_ARGUMENT, "Cannot read past");
        }

        Pricer pricer(const_cast<char*>(jsonFilePath));

        pricer.priceAndDeltas(past, currentDate, isMonitoringDate, price, priceStdDev, delta, deltaStdDev);

        output->set_price(price);
        output->set_pricestddev(priceStdDev);
        for (int i = 0; i < delta->size; i++) {
            output->add_deltas(GET(delta, i));
            output->add_deltasstddev(GET(deltaStdDev, i));
        }
        pnl_mat_free(&past);
        pnl_vect_free(&delta);
        pnl_vect_free(&deltaStdDev);
        return Status::OK;
    }

    Status Hedging(ServerContext *context, const HedgingInput *input, HedgingOutput *output) override {
        

        bool isMonitoringDate = input->monitoringdatereached();
        int currentDate = static_cast<int>(input->time());
        
        const char* jsonFilePath = input->jsonfile().c_str();

        std::ifstream ifs(jsonFilePath);
        nlohmann::json jsonParams = nlohmann::json::parse(ifs);

        jsonParams.at("maturity").get_to(maturity);
        jsonParams.at("InterestRates").get_to(interestRates);


        PnlMat *past = convertPastToPnlMat(input);
        if (past == NULL) {
            return Status(grpc::StatusCode::INVALID_ARGUMENT, "Cannot read past");
        }

        Pricer pricer(const_cast<char*>(jsonFilePath));

        double price, priceStdDev;
        PnlVect *deltas = pnl_vect_create(past->n);
        PnlVect *stdDeltas = pnl_vect_create(past->n);
        PnlVect *spots = pnl_vect_create(past->n);
        pnl_mat_get_row(spots, past, 0);

        pricer.priceAndDeltas(past, currentDate, isMonitoringDate, price, priceStdDev, deltas, stdDeltas);

        PnlVect *deltaPortefeuille= pnl_vect_new();
        pnl_vect_clone(deltaPortefeuille, deltas);
        PnlVect *stdDeltasPortefeuille = pnl_vect_new();
        pnl_vect_clone(stdDeltasPortefeuille,stdDeltas);

        double domesticInterestRate = GET(interestRates, 0);
        
        Portfolio hedgingPortfolio(domesticInterestRate, 255, spots, deltaPortefeuille, stdDeltasPortefeuille, price, priceStdDev);

        for (int i = currentDate + 1; i < maturity; i++){
            //Daily Rebalancing
            pricer.priceAndDeltas(past, i, isMonitoringDate, price, priceStdDev, deltas, stdDeltas);
            //TODO
        }

        nlohmann::json jsonPortfolio = hedgingPortfolio.positions;
        ofstream ifout("res_hedging.json", ios_base::out);
        if (!ifout.is_open()) {
            cout << "Unable to open file " << "res_hedging.json"<< endl;
            exit(1);
        }
        ifout << jsonPortfolio.dump(4);
        ifout.close();

        pnl_mat_free(&past);
        pnl_vect_free(&deltas);
        pnl_vect_free(&stdDeltas);
        pnl_vect_free(&deltaPortefeuille);
        pnl_vect_free(&stdDeltasPortefeuille);

        return Status::OK;
    }

};

void RunServer() {
    std::string server_address("0.0.0.0:50051");
    GrpcPricerImpl service;
    grpc::EnableDefaultHealthCheckService(true);
    grpc::reflection::InitProtoReflectionServerBuilderPlugin();
    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to a *synchronous* service.
    builder.RegisterService(&service);
    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
}

int main(int argc, char **argv) {
    if (argc != 1) {
        std::cout << "No argument" << std::endl;

    }
    RunServer();

    return 0;
}