#include "symphony/iomanager.h"
#include "symphony/log.h"
#include "symphony/tcp_server.h"

symphony::Logger::ptr g_logger = SYMPHONY_LOG_ROOT();

void run() {
    auto addr = symphony::Address::LookupAny("0.0.0.0:8033");
    // auto addr2 = symphony::UnixAddress::ptr(new
    // symphony::UnixAddress("/tmp/unix_addr"));
    std::vector<symphony::Address::ptr> addrs;
    addrs.push_back(addr);
    // addrs.push_back(addr2);

    symphony::TcpServer::ptr tcp_server(new symphony::TcpServer);
    std::vector<symphony::Address::ptr> fails;
    while (!tcp_server->bind(addrs, fails)) {
        sleep(2);
    }
    tcp_server->start();
    sleep(10);
    tcp_server->stop();
}
int main(int argc, char** argv) {
    symphony::IOManager iom(2);
    iom.schedule(run);
    return 0;
}