//
// Created by dylan liang on 2022/5/21.
//

#ifndef BASIC_RUN_NUM_ROUTER_H
#define BASIC_RUN_NUM_ROUTER_H


#include "router.h"
#include "common.h"
template<class T>
class TcpRouter: public Router{

public:
    void addRequest(FuncNoType funcNo,TcpFuncType){

    }

    void add_request_task(FuncNoType fnNo,void *funcPtr){
        tasks_.insert(std::make_pair(fnNo,std::bind(funcPtr,&t_,std::placeholders::_1)));
    }
private:
    std::map<FuncNoType ,TcpFuncType > routerMap_;
    T t_;
};

//int main(){
//    NumRouter<int> d;
////    d.addRequest()
//}




#endif //BASIC_RUN_NUM_ROUTER_H
