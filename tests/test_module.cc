#include <iostream>
#include "symphony/db/redis.h"
#include "symphony/log.h"
#include "symphony/module.h"
#include "symphony/singleton.h"

static symphony::Logger::ptr g_logger = SYMPHONY_LOG_ROOT();

class A {
   public:
    A() { std::cout << "A::A " << this << std::endl; }

    ~A() { std::cout << "A::~A " << this << std::endl; }
};

class MyModule : public symphony::RockModule {
   public:
    MyModule() : RockModule("hello", "1.0", "") {
        // symphony::Singleton<A>::GetInstance();
    }

    bool onLoad() override {
        symphony::Singleton<A>::GetInstance();
        std::cout << "-----------onLoad------------" << std::endl;
        return true;
    }

    bool onUnload() override {
        symphony::Singleton<A>::GetInstance();
        std::cout << "-----------onUnload------------" << std::endl;
        return true;
    }

    bool onServerReady() {
        registerService("rock", "sylar.top", "blog");
        auto rpy = symphony::RedisUtil::Cmd("local", "get abc");
        if (!rpy) {
            SYMPHONY_LOG_ERROR(g_logger) << "redis cmd get abc error";
        } else {
            SYMPHONY_LOG_ERROR(g_logger)
                << "redis get abc: " << (rpy->str ? rpy->str : "(null)");
        }
        return true;
    }

    bool handleRockRequest(symphony::RockRequest::ptr request,
                           symphony::RockResponse::ptr response,
                           symphony::RockStream::ptr stream) {
        SYMPHONY_LOG_INFO(g_logger)
            << "handleRockRequest " << request->toString();
        response->setResult(0);
        response->setResultStr("ok");
        response->setBody("echo: " + request->getBody());

        usleep(100 * 1000);
        auto addr = stream->getLocalAddressString();
        if (addr.find("8061") != std::string::npos) {
            if (rand() % 100 < 50) {
                usleep(10 * 1000);
            } else if (rand() % 100 < 10) {
                response->setResult(-1000);
            }
        } else {
            // if(rand() % 100 < 25) {
            //     usleep(10 * 1000);
            // } else if(rand() % 100 < 10) {
            //     response->setResult(-1000);
            // }
        }
        return true;
    }

    bool handleRockNotify(symphony::RockNotify::ptr notify,
                          symphony::RockStream::ptr stream) {
        SYMPHONY_LOG_INFO(g_logger)
            << "handleRockNotify " << notify->toString();
        return true;
    }
};

extern "C" {

symphony::Module* CreateModule() {
    symphony::Singleton<A>::GetInstance();
    std::cout << "=============CreateModule=================" << std::endl;
    return new MyModule;
}

void DestoryModule(symphony::Module* ptr) {
    std::cout << "=============DestoryModule=================" << std::endl;
    delete ptr;
}
}