#include <iostream>
#include "symphony/log.h"
#include "symphony/util.h"

int main(int argc, char const* argv[]) {
    symphony::Logger::ptr logger(new symphony::Logger);
    logger->addAppender(
        symphony::LogAppender::ptr(new symphony::StdoutLogAppender));

    symphony::FileLogAppender::ptr file_appender(
        new symphony::FileLogAppender("./log.txt"));
    symphony::LogFormatter::ptr fmt(new symphony::LogFormatter("%d%T%p%T%m%n"));
    file_appender->setFormatter(fmt);
    file_appender->setLevel(symphony::LogLevel::ERROR);
    // logger->addAppender(file_appender);

    symphony::TimeSlicingFileLogAppender::ptr ts_file_appender(
        new symphony::TimeSlicingFileLogAppender(".", "test", ".log", 1));
    logger->addAppender(ts_file_appender);
    // symphony::LogEvent::ptr event(new symphony::LogEvent(__FILE__, __LINE__,
    // 0, symphony::GetThreadId(), symphony::GetFiberId(), 2, time(0)));
    // logger->log(symphony::LogLevel::DEBUG, event);
    for (int i = 0; i < 10; i++) {
        SYMPHONY_LOG_INFO(logger) << "test macro";
        SYMPHONY_LOG_FMT_ERROR(logger, "test macro fmt error %s", "aa");
        sleep(10);
    }

    // auto l = symphony::LoggerMgr::GetInstance()->getLogger("xx");
    // SYMPHONY_LOG_INFO(l) << "xxx";
    return 0;
}