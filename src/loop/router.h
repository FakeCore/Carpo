#pragma once
//
// Created by dylan liang on 2022/5/15.
//
#include <map>
#include <queue>
class Context{

public:
    std::vector<uint8_t > send_msg_buffer_;
};

enum TimerTaskMode{
    INFINITE,
    LIMITED,
};
struct TimerTask{
    uint64_t delay;
    uint32_t times;
    enum TimerTaskMode mode;
    std::function<void(Context*)> fn;
};

struct timer_expire_cmp{
    bool operator()(TimerTask& r,TimerTask& l){
        return r.delay > l.delay;
    }
};

class Router{
protected:
    using FnNo = uint64_t;
    std::map<FnNo ,std::function<void(Context*)>> tasks_;
//    std::map<FnNo ,std::function<void(Context*)>> timer_tasks_;
    std::priority_queue<TimerTask ,std::vector<TimerTask>,timer_expire_cmp> timer_tasks_;
public:

    void add_timer_task(uint64_t delay,std::function<void(Context*)> f){
        TimerTask timer_task;
        timer_task.delay = delay;
        timer_task.mode = INFINITE;
        timer_task.times = 0;
        timer_task.fn = f;
        timer_tasks_.emplace(timer_task);
    }

    void add_timer_task(uint64_t delay,uint32_t execute_times,std::function<void(Context*)> f){
        TimerTask timer_task;
        timer_task.delay = delay;
        timer_task.fn = f;
        timer_task.times = execute_times;
        if(execute_times == 0){
            timer_task.mode = INFINITE;
        }else{
            timer_task.mode = LIMITED;
        }
        timer_tasks_.emplace(timer_task);
    }
    void add_request_task(FnNo fn_no,std::function<void(Context*)> f){
        tasks_.insert(std::make_pair(fn_no,f));
    }

};


//class BasicServer:public Router{
//public:
//    void start() override{
////        room_.join(shared_from_this());
////
////        co_spawn(socket_.get_executor(),
////                 [self = shared_from_this()]{ return self->reader(); },
////                 detached);
////
////        co_spawn(socket_.get_executor(),
////                 [self = shared_from_this()]{ return self->writer(); },
////                 detached);
//    }
//    void add_task() override{
//
//    }
//};

//class BasicClient:public Router{
//public:
//    void start() override{
////        room_.join(shared_from_this());
////
////        co_spawn(socket_.get_executor(),
////                 [self = shared_from_this()]{ return self->reader(); },
////                 detached);
////
////        co_spawn(socket_.get_executor(),
////                 [self = shared_from_this()]{ return self->writer(); },
////                 detached);
//    }
//};


//user mode
//class TaskA{
//public:
//    void func1();
//    void func2();
//    void reqfunc1();
//};
//
//basic_run.add_timer_task();
//basic_run.add_task();
