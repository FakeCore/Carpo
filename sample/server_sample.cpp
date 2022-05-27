//
// Created by dylan liang on 2022/5/27.
//

#include "loop/carpo.h"

class TestA{

    void funcEcho(Context*ctx){
        printf("eeee");
    }
};

int main(){
    Carpo carpo;

    auto server = carpo.genTcpServer();
    auto router = server->genTcpRouter<TestA>();
    server->run();
}