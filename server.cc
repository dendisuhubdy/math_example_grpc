#include <string>

#include <grpcpp/grpcpp.h>
#include "mathtest.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using mathtest::MathTest;
using mathtest::MathRequest;
using mathtest::MathReply;

class MathServiceImplementation final : public MathTest::Service {
    Status sendRequest(
        ServerContext* context, 
        const MathRequest* request, 
        MathReply* reply
    ) override {
        // Example computation on server
        // requesting value of a
        int a = request->a();
        // requesting value of b
        int b = request->b();
        // computing result
        int result = a + b;
        // send result back to client
        reply->set_result(result);
        // return an OK status
        return Status::OK;
    } 
};

void Run() {
    std::string address("0.0.0.0:5000");
    MathServiceImplementation service;

    ServerBuilder builder;

    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on port: " << address << std::endl;

    server->Wait();
}

int main(int argc, char** argv) {
    Run();

    return 0;
}
