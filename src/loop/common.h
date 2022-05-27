//
// Created by dylan liang on 2022/5/21.
//

#pragma once
#include <stdlib.h>
#include <functional>

class Context;

using FuncNoType = uint64_t ;
using TcpFuncType = std::function<void(Context*)>;