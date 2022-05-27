//
// Created by dylan liang on 2022/5/20.
//

#ifndef BASIC_RUN_SERVER_H
#define BASIC_RUN_SERVER_H


#include <asio/awaitable.hpp>
#include <asio/co_spawn.hpp>
#include <asio/ip/tcp.hpp>
#include <memory>
#include <stdlib.h>
#include "base_component.h"
#include "router.h"
#include "config/config.h"
#include "num_router.h"
#include "session.h"

/*
 *
 * server/client.module.addRouter()
 * different sub router could use different way to redirect request
 *
 *
 *
 */

class Server : BaseComponent {
public:

    Server(){
        ctx_ =std::make_shared<Context>();
    }
    void run(){
        asio::io_context io_context(1);
        asio::co_spawn(io_context, listener(ctx_,
            asio::ip::tcp::acceptor(io_context,{asio::ip::tcp::v4(),
                            static_cast<uint16_t>(atoi(Config::get("port").c_str()))})),
                   asio::detached);
        io_context.run();
    }

    asio::awaitable<void> listener(std::shared_ptr<Context> ctx,asio::ip::tcp::acceptor acceptor){
//        Session session;
        for (;;)
        {
            std::make_shared<Session>(
                    co_await acceptor.async_accept(asio::use_awaitable)
                    ,router_
                    ,ctx
            )->start();
        }
    }

    void setRouter(std::shared_ptr<Router> router){
        this->router_ = router;
    }

    template<class T>
    std::shared_ptr<Router> genTcpRouter(){
        router_ = std::make_shared<TcpRouter<T>>();
        return router_;
    }



private:
    std::shared_ptr<Context> ctx_;
    std::shared_ptr<Router> router_;
};


#endif //BASIC_RUN_SERVER_H
