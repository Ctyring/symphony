#include "symphony/address.h"
#include "symphony/bytearray.h"
#include "symphony/iomanager.h"
#include "symphony/log.h"
#include "symphony/tcp_server.h"

static symphony::Logger::ptr g_logger = SYMPHONY_LOG_ROOT();
class EchoServer : public symphony::TcpServer {
   public:
    EchoServer(int type);
    void handleClient(symphony::Socket::ptr client);

   private:
    int m_type = 0;
};

EchoServer::EchoServer(int type) : m_type(type) {}

void EchoServer::handleClient(symphony::Socket::ptr client) {
    SYMPHONY_LOG_INFO(g_logger) << "handleClient " << *client;
    symphony::ByteArray::ptr ba(new symphony::ByteArray);
    while (true) {
        ba->clear();
        std::vector<iovec> iovs;
        ba->getWriteBuffers(iovs, 1024);

        int rt = client->recv(&iovs[0], iovs.size());
        if (rt == 0) {
            SYMPHONY_LOG_INFO(g_logger) << "client close: " << *client;
            break;
        } else if (rt < 0) {
            SYMPHONY_LOG_INFO(g_logger)
                << "client error rt=" << rt << " errno=" << errno
                << " errstr=" << strerror(errno);
            break;
        }
        ba->setPosition(ba->getPosition() + rt);
        ba->setPosition(0);
        // SYMPHONY_LOG_INFO(g_logger) << "recv rt=" << rt << " data=" <<
        // std::string((char*)iovs[0].iov_base, rt);
        if (m_type == 1) {                // text
            std::cout << ba->toString();  // << std::endl;
        } else {
            std::cout << ba->toHexString();  // << std::endl;
        }
        std::cout.flush();
    }
}

int type = 1;

void run() {
    SYMPHONY_LOG_INFO(g_logger) << "server type=" << type;
    EchoServer::ptr es(new EchoServer(type));
    auto addr = symphony::Address::LookupAny("0.0.0.0:8020");
    while (!es->bind(addr)) {
        sleep(2);
    }
    es->start();
}

int main(int argc, char** argv) {
    if (argc < 2) {
        SYMPHONY_LOG_INFO(g_logger)
            << "used as[" << argv[0] << " -t] or [" << argv[0] << " -b]";
        return 0;
    }

    if (!strcmp(argv[1], "-b")) {
        type = 2;
    }

    symphony::IOManager iom(2);
    iom.schedule(run);
    return 0;
}