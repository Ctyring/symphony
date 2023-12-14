#include "symphony/iomanager.h"
#include "symphony/log.h"
#include "symphony/socket.h"

static symphony::Logger::ptr g_logger = SYMPHONY_LOG_ROOT();

void run() {
    symphony::IPAddress::ptr addr =
        symphony::Address::LookupAnyIPAddress("0.0.0.0:8050");
    symphony::Socket::ptr sock = symphony::Socket::CreateUDP(addr);
    if (sock->bind(addr)) {
        SYMPHONY_LOG_INFO(g_logger) << "udp bind : " << *addr;
    } else {
        SYMPHONY_LOG_ERROR(g_logger) << "udp bind : " << *addr << " fail";
        return;
    }
    while (true) {
        char buff[1024];
        symphony::Address::ptr from(new symphony::IPv4Address);
        int len = sock->recvFrom(buff, 1024, from);
        if (len > 0) {
            buff[len] = '\0';
            SYMPHONY_LOG_INFO(g_logger)
                << "recv: " << buff << " from: " << *from;
            len = sock->sendTo(buff, len, from);
            if (len < 0) {
                SYMPHONY_LOG_INFO(g_logger)
                    << "send: " << buff << " to: " << *from << " error=" << len;
            }
        }
    }
}

int main(int argc, char** argv) {
    symphony::IOManager iom(1);
    iom.schedule(run);
    return 0;
}