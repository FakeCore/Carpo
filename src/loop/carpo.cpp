//
// Created by dylan liang on 2022/5/21.
//

#include "carpo.h"
#include "router.h"


class TestA{
public:
    void func(Context *ctx){

    }
};
//int main(){
//    Carpo carpo;
////    carpo.gen
//   auto server =  carpo.genTcpServer();
//
//    auto router = server->genTcpRouter<TestA>();
//    router->add_request_task(1,&TestA::func);
//
//    router->add_request_task(1,&TestA::func);
//
//    carpo.run();
//
//}