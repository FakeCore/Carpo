//
// Created by dylan liang on 2022/5/13.
//
#pragma once

#include <asio/io_context.hpp>
#include <asio/co_spawn.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/detached.hpp>
#include <asio/redirect_error.hpp>
#include <asio/signal_set.hpp>
#include "run_module.h"


using asio::ip::tcp;
using asio::awaitable;
using asio::detached;
using asio::co_spawn;
using asio::redirect_error;
using asio::use_awaitable;

class Loop{
public:
    void run(){
        try{
            asio::io_context io_ctx(1);
            for(auto &module:run_module_components_){
                co_spawn(io_ctx,module.run(io_ctx),detached);
            }
            asio::signal_set signals(io_ctx, SIGINT, SIGTERM);
            signals.async_wait([&](auto, auto){ io_ctx.stop(); });
            io_ctx.run();
        }catch (std::exception e){
            printf("log:%s\n",e.what());
        }
    }

    asio::awaitable<void> timer_task_scan(tcp::acceptor acceptor){
        for (;;)
        {
//            std::make_shared<chat_session>(
//                    co_await acceptor.async_accept(use_awaitable),
//            )->start();
        }
    }

    asio::awaitable<void> listener(tcp::acceptor acceptor){
//        chat_room room;
//        for (;;)
//        {
//            std::make_shared<chat_session>(
//                    co_await acceptor.async_accept(use_awaitable),
//                    room
//            )->start();
//        }
    }
private:
    std::vector<RunModule> run_module_components_;
};

