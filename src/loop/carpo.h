//
// Created by dylan liang on 2022/5/21.
//

#ifndef BASIC_RUN_CARPO_H
#define BASIC_RUN_CARPO_H


#include "router.h"
#include "num_router.h"
#include "server.h"

class Carpo {
public:
    void run();

    template<class T>
    Router* genTcpRouter(){
        return new TcpRouter<T>();
    }
    Router* genHttpRouter();

    Server* genTcpServer(){
        return new Server();
    }

private:
//    RouterManage routerManage;
};


#endif //BASIC_RUN_CARPO_H
