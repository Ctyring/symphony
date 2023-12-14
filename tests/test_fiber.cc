#include "symphony/symphony.h"

symphony::Logger::ptr g_logger = SYMPHONY_LOG_ROOT();

void run_in_fiber() {
    SYMPHONY_LOG_INFO(g_logger) << "run_in_fiber begin";
    symphony::Fiber::YieldToHold();
    SYMPHONY_LOG_INFO(g_logger) << "run_in_fiber end";
    symphony::Fiber::YieldToHold();
}

void test_fiber() {
    SYMPHONY_LOG_INFO(g_logger) << "main begin -1";
    {
        symphony::Fiber::GetThis();
        SYMPHONY_LOG_INFO(g_logger) << "main begin";
        symphony::Fiber::ptr fiber(new symphony::Fiber(run_in_fiber));
        fiber->call();
        // SYMPHONY_LOG_INFO(g_logger) << "main after swapIn";
        // fiber->swapIn();
        // SYMPHONY_LOG_INFO(g_logger) << "main after end";
        // fiber->swapIn();
    }
    SYMPHONY_LOG_INFO(g_logger) << "main after end2";
}

int main(int argc, char** argv) {
    symphony::Thread::SetName("main");

    std::vector<symphony::Thread::ptr> thrs;
    for (int i = 0; i < 3; ++i) {
        thrs.push_back(symphony::Thread::ptr(
            new symphony::Thread(&test_fiber, "name_" + std::to_string(i))));
    }
    for (auto i : thrs) {
        i->join();
    }
    return 0;
}