#include "symphony/http/ws_server.h"
#include "symphony/log.h"

static symphony::Logger::ptr g_logger = SYMPHONY_LOG_ROOT();

void run() {
    symphony::http::WSServer::ptr server(new symphony::http::WSServer);
    symphony::Address::ptr addr =
        symphony::Address::LookupAnyIPAddress("0.0.0.0:8020");
    if (!addr) {
        SYMPHONY_LOG_ERROR(g_logger) << "get address error";
        return;
    }
    auto fun = [](symphony::http::HttpRequest::ptr header,
                  symphony::http::WSFrameMessage::ptr msg,
                  symphony::http::WSSession::ptr session) {
        session->sendMessage(msg);
        return 0;
    };

    server->getWSServletDispatch()->addServlet("/sylar", fun);
    while (!server->bind(addr)) {
        SYMPHONY_LOG_ERROR(g_logger) << "bind " << *addr << " fail";
        sleep(1);
    }
    server->start();
}

int main(int argc, char** argv) {
    symphony::IOManager iom(2);
    iom.schedule(run);
    return 0;
}