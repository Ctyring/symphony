#include "symphony/symphony.h"
static symphony::Logger::ptr g_logger = SYMPHONY_LOG_ROOT();

void test_fiber() {
    static int s_count = 5;
    SYMPHONY_LOG_INFO(g_logger) << "test in fiber s_count=" << s_count;
    if (--s_count >= 0) {
        // symphony::Fiber::ptr tmp_fiber(new
        // symphony::Fiber(std::bind(test_fiber)));
        symphony::Scheduler::GetThis()->schedule(&test_fiber,
                                                 symphony::GetThreadId());
    }
}

int main(int argc, char** argv) {
    SYMPHONY_LOG_INFO(g_logger) << "main";
    symphony::Scheduler sc(3, false, "test");
    sc.start();
    sleep(2);
    SYMPHONY_LOG_INFO(g_logger) << "schedule";
    sc.schedule(&test_fiber);
    sc.stop();
    SYMPHONY_LOG_INFO(g_logger) << "over";
    return 0;
}