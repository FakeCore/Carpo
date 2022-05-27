//
// Created by dylan liang on 2022/5/15.
//

#include <asio/high_resolution_timer.hpp>
#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/write.hpp>
#include <asio/redirect_error.hpp>
#include <deque>
#include "router.h"

using asio::ip::tcp;
using asio::awaitable;
using asio::co_spawn;
using asio::detached;
using asio::use_awaitable;

//class chat_room
//{
//public:
//    void join(chat_participant_ptr participant)
//    {
//        participants_.insert(participant);
//        for (auto msg: recent_msgs_)
//            participant->deliver(msg);
//    }
//
//    void leave(chat_participant_ptr participant)
//    {
//        participants_.erase(participant);
//    }
//
//    void deliver(const std::string& msg)
//    {
//        recent_msgs_.push_back(msg);
//        while (recent_msgs_.size() > max_recent_msgs)
//            recent_msgs_.pop_front();
//
//        for (auto participant: participants_)
//            participant->deliver(msg);
//    }
//
//private:
//    std::set<chat_participant_ptr> participants_;
//    enum { max_recent_msgs = 100 };
//    std::deque<std::string> recent_msgs_;
//};
//
//class chat_session
//        : public chat_participant,
//          public std::enable_shared_from_this<chat_session>
//{
//public:
//    chat_session(tcp::socket socket, chat_room& room)
//            : socket_(std::move(socket)),
//              timer_(socket_.get_executor()),
//              room_(room)
//    {
//        timer_.expires_at(std::chrono::steady_clock::time_point::max());
//    }
//
//    void start()
//    {
//        room_.join(shared_from_this());
//
//        co_spawn(socket_.get_executor(),
//                 [self = shared_from_this()]{ return self->reader(); },
//                 detached);
//
//        co_spawn(socket_.get_executor(),
//                 [self = shared_from_this()]{ return self->writer(); },
//                 detached);
//    }
//
//    void deliver(const std::string& msg)
//    {
//        write_msgs_.push_back(msg);
//        timer_.cancel_one();
//    }
//
//private:
//    awaitable<void> reader()
//    {
//        try
//        {
//            for (std::string read_msg;;)
//            {
//                std::size_t n = co_await asio::async_read_until(socket_,
//                                                                asio::dynamic_buffer(read_msg, 1024), "\n", use_awaitable);
//
//                room_.deliver(read_msg.substr(0, n));
//                read_msg.erase(0, n);
//            }
//        }
//        catch (std::exception&)
//        {
//            stop();
//        }
//    }
//
//    awaitable<void> writer()
//    {
//        try
//        {
//            while (socket_.is_open())
//            {
//                if (write_msgs_.empty())
//                {
//                    asio::error_code ec;
//                    co_await timer_.async_wait(redirect_error(asio::use_awaitable, ec));
//                }
//                else
//                {
//                    co_await asio::async_write(socket_,
//                                               asio::buffer(write_msgs_.front()), asio::use_awaitable);
//                    write_msgs_.pop_front();
//                }
//            }
//        }
//        catch (std::exception&)
//        {
//            stop();
//        }
//    }
//
//    void stop()
//    {
//        room_.leave(shared_from_this());
//        socket_.close();
//        timer_.cancel();
//    }
//
//    tcp::socket socket_;
//    asio::steady_timer timer_;
//    chat_room& room_;
//    std::deque<std::string> write_msgs_;
//};


//class Context{
//    asio::high_resolution_timer timer_;
//    asio::io_context ctx_;
//    uint16_t port_;
//
//    asio::awaitable<void> timeout(){
//        for(;;){
////            co_await timer_.async_wait();
//        }
//    }
//
//    asio::awaitable<void> read(){
//        for(;;){
////            co_await timer_.async_wait();
//        }
//    }
//
//    asio::awaitable<void> write(){
//        for(;;){
////            co_await timer_.async_wait();
//        }
//    }
//
//    asio::awaitable<void> listener(asio::ip::tcp::acceptor acceptor){
//        chat_room room;
//        std::make_shared<Router>(
//                co_await acceptor.async_accept(asio::use_awaitable),
//                room
//        )->start();
//    }
//
//    asio::awaitable<void> start_server(){
//        co_spawn(ctx_,
//                 listener(asio::ip::tcp::acceptor(ctx_, {asio::ip::tcp::v4(), port_})),
//                 asio::detached);
//    }
//
//    void run(){
//        asio::co_spawn(ctx_,timeout(),asio::detached);
//        asio::co_spawn(ctx_,start_server(),asio::detached);
//        asio::co_spawn(ctx_,read(),asio::detached);
//        asio::co_spawn(ctx_,write(),asio::detached);
//    }
//
//};
