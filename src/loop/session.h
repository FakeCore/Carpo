//
// Created by dylan liang on 2022/5/21.
//

#ifndef BASIC_RUN_SESSION_H
#define BASIC_RUN_SESSION_H

#include <asio/detached.hpp>
#include <memory>
#include <asio/read_until.hpp>
#include <asio/redirect_error.hpp>
#include <asio/write.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/co_spawn.hpp>
#include "router_handle.h"
#include "base/codec.h"
#include "router.h"


class Session:
        public std::enable_shared_from_this<Session>
{
public:
    Session(asio::ip::tcp::socket socket,std::shared_ptr<Router> r,std::shared_ptr<Context> context)
        : socket_(std::move(socket))
        ,router_(r)
        ,ctx_(context)
        , timer_(socket.get_executor())
    {
        timer_.expires_at(std::chrono::steady_clock::time_point::max());
    }

    void start(){
        asio::co_spawn(socket_.get_executor(),
                 [self = shared_from_this()]{ return self->reader(); },
                 asio::detached);

        asio::co_spawn(socket_.get_executor(),
                 [self = shared_from_this()]{ return self->writer(); },
                 asio::detached);
    }

private:
    asio::awaitable<void> reader()
    {
        try
        {
            for (std::vector<uint8_t> data;;)
            {
                std::size_t n = co_await asio::async_read_until(socket_,
                //TODO read buffer size from config file
                asio::dynamic_buffer(data, 1024),"", asio::use_awaitable);
                codec_.addData(data);
                while(codec_.dataReady()){
                    auto [fnNo,msgContent] =  codec_.decode(data);
                    try{
                        routerHandle_[fnNo](ctx_.get());
                    }catch (std::exception e){
                    }
                    data.clear();
                }
            }
        }
        catch (std::exception&)
        {
            stop();
        }
    }

    asio::awaitable<void> writer()
    {
        try
        {
            while (socket_.is_open())
            {
                if (ctx_->send_msg_buffer_.empty())
                {
                    printf("hi");
                    asio::error_code ec;
                    co_await timer_.async_wait(asio::redirect_error(asio::use_awaitable, ec));
                }
                else
                {
                    printf("hsshi");
                    co_await asio::async_write(socket_,
                       asio::buffer(ctx_->send_msg_buffer_), asio::use_awaitable);
                }
            }
        }
        catch (std::exception&)
        {
            stop();
        }
    }

    void stop()
    {
//        room_.leave(shared_from_this());
        socket_.close();
//        timer_.cancel();
    }

private:
    std::shared_ptr<Router> router_;
    asio::ip::tcp::socket socket_;
    RouterHandle routerHandle_;
    std::shared_ptr<Context> ctx_;
    asio::steady_timer timer_;
    Codec codec_;

};


#endif //BASIC_RUN_SESSION_H
