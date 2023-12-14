#include "symphony/address.h"
#include "symphony/log.h"

symphony::Logger::ptr g_logger = SYMPHONY_LOG_ROOT();

void test() {
    std::vector<symphony::Address::ptr> addrs;

    SYMPHONY_LOG_INFO(g_logger) << "begin";
    bool v = symphony::Address::Lookup(addrs, "localhost:3080");
    SYMPHONY_LOG_INFO(g_logger) << "end";
    if (!v) {
        SYMPHONY_LOG_ERROR(g_logger) << "lookup fail";
        return;
    }

    for (size_t i = 0; i < addrs.size(); ++i) {
        SYMPHONY_LOG_INFO(g_logger) << i << " - " << addrs[i]->toString();
    }

    auto addr = symphony::Address::LookupAny("localhost:4080");
    if (addr) {
        SYMPHONY_LOG_INFO(g_logger) << *addr;
    } else {
        SYMPHONY_LOG_ERROR(g_logger) << "error";
    }
}

void test_iface() {
    std::multimap<std::string, std::pair<symphony::Address::ptr, uint32_t>>
        results;

    bool v = symphony::Address::GetInterfaceAddresses(results);
    if (!v) {
        SYMPHONY_LOG_ERROR(g_logger) << "GetInterfaceAddresses fail";
        return;
    }

    for (auto& i : results) {
        SYMPHONY_LOG_INFO(g_logger)
            << i.first << " - " << i.second.first->toString() << " - "
            << i.second.second;
    }
}

void test_ipv4() {
    // auto addr = symphony::IPAddress::Create("www.sylar.top");
    auto addr = symphony::IPAddress::Create("127.0.0.8");
    if (addr) {
        SYMPHONY_LOG_INFO(g_logger) << addr->toString();
    }
}

int main(int argc, char** argv) {
    // test_ipv4();
    // test_iface();
    test();
    return 0;
}