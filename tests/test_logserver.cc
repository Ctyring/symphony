#include "symphony/servers/log_server/log_server_module.h"
#include "symphony/servers/log_server/log_server_protocol.h"
#include "symphony/servers/log_server/ls_client.h"

static symphony::Logger::ptr g_logger = SYMPHONY_LOG_ROOT();

void run() {
    auto addr = symphony::IPAddress::Create("127.0.0.1", 8051);
    symphony::ls::LSClient::ptr lsClient(new symphony::ls::LSClient);
    lsClient->init();
    if (lsClient->connect(addr)) {
        SYMPHONY_LOG_INFO(g_logger)
            << "connect " << addr->toString() << " success";
    } else {
        SYMPHONY_LOG_ERROR(g_logger)
            << "connect " << addr->toString() << " failed";
        return;
    }
    lsClient->start();
    SYMPHONY_LOG_INFO(g_logger) << "LSClient start";
}

int main(int argc, char** argv) {
    symphony::IOManager iom(2);
    iom.schedule(run);
    return 0;
}