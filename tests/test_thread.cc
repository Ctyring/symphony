#include <unistd.h>
#include <iostream>
#include "symphony/symphony.h"

symphony::Logger::ptr g_logger = SYMPHONY_LOG_ROOT();

int count = 0;
symphony::Mutex s_mutex;

void fun1() {
    SYMPHONY_LOG_INFO(g_logger)
        << "name: " << symphony::Thread::GetName()
        << " this.name: " << symphony::Thread::GetThis()->getName()
        << " id: " << symphony::GetThreadId()
        << " this.id: " << symphony::Thread::GetThis()->getId();

    for (int i = 0; i < 100000; ++i) {
        symphony::Mutex::Lock lock(
            s_mutex);  // 定义lock对象，类型为symphony::Mutex::Lock，传入互斥量，在构造函数中完成加锁操作，如果该锁已经被持有，那构造lock时就会阻塞，直到锁被释放
        ++count;
    }
}

void fun2() {
    // while (true) {
    SYMPHONY_LOG_INFO(g_logger) << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
    // }
}

void fun3() {
    // while (true) {
    SYMPHONY_LOG_INFO(g_logger) << "========================================";
    // }
}

int main(int argc, char** argv) {
    // symphony::Thread::ptr thr(
    //     new symphony::Thread(&fun2, "name_" + std::to_string(1)));
    // thr->join();
    std::cout << "test_thread" << std::endl;
    SYMPHONY_LOG_INFO(g_logger) << "thread test begin";
    std::cout << "ok" << std::endl;
    YAML::Node root = YAML::LoadFile("/root/cty/symphony/bin/conf/log.yml");
    symphony::Config::LoadFromYaml(root);

    std::vector<symphony::Thread::ptr> thrs;
    for (int i = 0; i < 2; ++i) {
        symphony::Thread::ptr thr(
            new symphony::Thread(&fun2, "name_" + std::to_string(i * 2)));
        symphony::Thread::ptr thr2(
            new symphony::Thread(&fun3, "name_" + std::to_string(i * 2 + 1)));
        thrs.push_back(thr);
        thrs.push_back(thr2);
    }
    for (size_t i = 0; i < thrs.size(); ++i) {
        thrs[i]->join();
    }
    SYMPHONY_LOG_INFO(g_logger) << "thread test end";
    SYMPHONY_LOG_INFO(g_logger) << "count=" << count;
    return 0;
}