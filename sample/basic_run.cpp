//
// Created by dylan liang on 2022/5/12.
//


#include <experimental/coroutine>
#include <iostream>
#include <tuple>
#include <stdexcept>
#include <thread>

using namespace std::experimental;
template<typename Future>
class coroutine_base {
    Future& get_future() { return static_cast<Future&>(*this); }
protected:
    using suspend_never = std::experimental::suspend_never;
    using suspend_always = std::experimental::suspend_always;
    template<typename... U>
    using coroutine_handle = std::experimental::coroutine_handle<U...>;

    template<typename Promise>
    struct promise_base_type {
        auto initial_suspend() { return suspend_never{}; }
        auto final_suspend() noexcept { return suspend_always{}; }
        Future get_return_object() {
            return coroutine_handle<Promise>::from_promise(static_cast<Promise&>(*this));
        }
        void unhandled_exception() { std::terminate(); }
    };

    void resume() { if (! get_future().co_handle_.done()) get_future().co_handle_.resume(); }

public:
    ~coroutine_base() { get_future().co_handle_.destroy(); }

};

struct FiboFuture: coroutine_base<FiboFuture> {
    struct promise_type: promise_base_type<promise_type> {
        int value_;
        auto yield_value(int value) {
            value_ = value;
            return suspend_always{};
        }
        void return_void() {}
    };

    FiboFuture(coroutine_handle<promise_type> handle): co_handle_(handle) {}
    using coroutine_base::resume;

    operator int() { return co_handle_.promise().value_; }

    coroutine_handle<promise_type> co_handle_{};
};

FiboFuture generate_fibo() {
    int i = 0, j = 1;
    while (true) {
        co_yield j;
        std::tie(i, j) = std::make_pair(j, i + j);
    }
}

int main(int argc, char** argv) {
    for (auto x = generate_fibo(); x < 1000; x.resume()) {
        std::cout << "fibo: " << x << std::endl;
    }

    return 0;
}