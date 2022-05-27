//
// Created by dylan liang on 2022/5/22.
//

#ifndef BASIC_RUN_ROUTER_HANDLE_H
#define BASIC_RUN_ROUTER_HANDLE_H

#include <functional>
#include "common.h"
class Context;
class RouterHandle {

public:
    RouterHandle(){

        default_handle_ = std::bind(&RouterHandle::defaultHandleFunction, this, std::placeholders::_1);
    }

    std::function<void(Context*)>& operator[](const FuncNoType &funcno){
        return default_handle_;
    }

    void defaultHandleFunction(Context*){

    }
private:
    std::function<void(Context(*))> default_handle_;
//    std::shared_ptr<>

};


#endif //BASIC_RUN_ROUTER_HANDLE_H
