#include "symphony/daemon.h"
#include "symphony/iomanager.h"
#include "symphony/log.h"

static symphony::Logger::ptr g_logger = SYMPHONY_LOG_ROOT();

symphony::Timer::ptr timer;
int server_main(int argc, char** argv) {
    SYMPHONY_LOG_INFO(g_logger)
        << symphony::ProcessInfoMgr::GetInstance()->toString();
    symphony::IOManager iom(1);
    timer = iom.addTimer(
        1000,
        []() {
            SYMPHONY_LOG_INFO(g_logger) << "onTimer";
            static int count = 0;
            if (++count > 10) {
                exit(1);
            }
        },
        true);
    return 0;
}

int main(int argc, char** argv) {
    return symphony::start_daemon(argc, argv, server_main, argc != 1);
}