#include "symphony/http/http_server.h"
#include "symphony/log.h"

symphony::Logger::ptr g_logger = SYMPHONY_LOG_ROOT();
symphony::IOManager::ptr worker;
void run() {
    g_logger->setLevel(symphony::LogLevel::INFO);
    symphony::Address::ptr addr =
        symphony::Address::LookupAnyIPAddress("0.0.0.0:8020");
    if (!addr) {
        SYMPHONY_LOG_ERROR(g_logger) << "get address error";
        return;
    }

    symphony::http::HttpServer::ptr http_server(
        new symphony::http::HttpServer(true, worker.get()));
    while (!http_server->bind(addr)) {
        SYMPHONY_LOG_ERROR(g_logger) << "bind " << *addr << " fail";
        sleep(1);
    }

    http_server->start();
}

int main(int argc, char** argv) {
    symphony::IOManager iom(1);
    worker.reset(new symphony::IOManager(4, false));
    iom.schedule(run);
    return 0;
}