//
// Created by dylan liang on 2022/5/14.
//


#include <memory>
#include <asio/awaitable.hpp>
#include <asio.hpp>
#include <asio/high_resolution_timer.hpp>



using asio::awaitable;

class TimerScan:
public std::enable_shared_from_this<TimerScan>
{
    asio::high_resolution_timer timer_;
    using duration = asio::high_resolution_timer::duration;
public:
    template<class Executor>
    TimerScan(Executor&& executor):timer_(executor){
    }

    template<typename Executor,typename Func>
    TimerScan(Executor&& executor,const duration& timeout, Func&& on_timeout):timer_(executor){
        set(timeout,on_timeout);
    }

    template <typename Func>
    void set(const duration& timeout, Func&& on_timeout) {
        timer_.expires_after(timeout);  // cancels outstanding timeouts
        timer_.async_wait([&](std::error_code ec) {
            if (ec) return;
            printf("cancelling\n");
            on_timeout();
        });
    }
    void cancel() { timer_.cancel(); }

    ~TimerScan() { this->cancel(); }

    void start(){

    }

    void timeout(){

    }

    //start execute task
    awaitable<void> on_timeout(){
        for(;;){
            co_await timeout();
            //execute timeout_task
        }
    }

//    void deliver(const)

};