#include<exception>
#pragma once
// Workaround for VSCode to do syntax hylighting
//#ifndef __cpp_impl_coroutine
//#define __cpp_impl_coroutine 1
//#endif
#include<coroutine>
#include<iostream>

struct Suspendable {
    struct promise_type {
        promise_type() {
        }
        ~promise_type() {
        }
        auto initial_suspend() {
            return std::suspend_always{};
        }
        auto final_suspend() {
            return std::suspend_always{};
        }
        auto get_return_object() {
            return Suspendable{handle_type::from_promise(*this)};
        }
        void unhandled_exception() {
            std::rethrow_exception(std::current_exception());
        }
        auto return_void() {
            return std::suspend_never{};
        }
    };
    using handle_type =
        std::coroutine_handle<promise_type>;
    handle_type coro;

    Suspendable(handle_type h): coro(h) {
    }

    bool done() const
    {
        return coro.done();
    }
    void resume() const
    {
        coro.resume();
    }
    bool await_ready() const {
        return !done();
    }
    void await_suspend(handle_type t) const {
    }
    void await_resume() const {
        resume();
    }
    void operator=(const Suspendable& other)
    {
        coro = other.coro;
    }
    Suspendable(const Suspendable& other)
    {
        coro = other.coro;
    }
    Suspendable(const Suspendable&& other)
    {
        coro = other.coro;
    }
    void operator=(const Suspendable&& other)
    {
        coro = other.coro;
    }
};

#define SUSPEND co_await std::suspend_always
#define NOSUSPEND co_await std::suspend_never
#define WAIT_FOR(x) { Suspendable s=x; while(!s.done()) { SUSPEND(); co_await s; } }