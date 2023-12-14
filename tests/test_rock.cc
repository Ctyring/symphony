#include "symphony/rock/rock_stream.h"
#include "symphony/symphony.h"

static symphony::Logger::ptr g_logger = SYMPHONY_LOG_ROOT();

symphony::RockConnection::ptr conn(new symphony::RockConnection);
void run() {
    conn->setAutoConnect(true);
    symphony::Address::ptr addr =
        symphony::Address::LookupAny("127.0.0.1:8061");
    if (!conn->connect(addr)) {
        SYMPHONY_LOG_INFO(g_logger) << "connect " << *addr << " false";
    }
    conn->start();

    symphony::IOManager::GetThis()->addTimer(
        1000,
        []() {
            symphony::RockRequest::ptr req(new symphony::RockRequest);
            static uint32_t s_sn = 0;
            req->setSn(++s_sn);
            req->setCmd(100);
            req->setBody("hello world sn=" + std::to_string(s_sn));

            auto rsp = conn->request(req, 300);
            if (rsp->response) {
                SYMPHONY_LOG_INFO(g_logger) << rsp->response->toString();
            } else {
                SYMPHONY_LOG_INFO(g_logger) << "error result=" << rsp->result;
            }
        },
        true);
}

int main(int argc, char** argv) {
    symphony::IOManager iom(1);
    iom.schedule(run);
    return 0;
}