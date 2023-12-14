#include "symphony/iomanager.h"
#include "symphony/log.h"
#include "symphony/rock/rock_stream.h"
#include "symphony/streams/service_discovery.h"
#include "symphony/worker.h"

symphony::ZKServiceDiscovery::ptr zksd(
    new symphony::ZKServiceDiscovery("127.0.0.1:21812"));
symphony::RockSDLoadBalance::ptr rsdlb(new symphony::RockSDLoadBalance(zksd));

static symphony::Logger::ptr g_logger = SYMPHONY_LOG_ROOT();

std::atomic<uint32_t> s_id;
void on_timer() {
    g_logger->setLevel(symphony::LogLevel::INFO);
    // SYMPHONY_LOG_INFO(g_logger) << "on_timer";
    symphony::RockRequest::ptr req(new symphony::RockRequest);
    req->setSn(++s_id);
    req->setCmd(100);
    req->setBody("hello");

    auto rt = rsdlb->request("sylar.top", "blog", req, 1000);
    if (!rt->response) {
        if (req->getSn() % 50 == 0) {
            SYMPHONY_LOG_ERROR(g_logger)
                << "invalid response: " << rt->toString();
        }
    } else {
        if (req->getSn() % 1000 == 0) {
            SYMPHONY_LOG_INFO(g_logger) << rt->toString();
        }
    }
}

void run() {
    zksd->setSelfInfo("127.0.0.1:2222");
    zksd->setSelfData("aaaa");

    std::unordered_map<std::string,
                       std::unordered_map<std::string, std::string> >
        confs;
    confs["sylar.top"]["blog"] = "fair";
    rsdlb->start(confs);
    // SYMPHONY_LOG_INFO(g_logger) << "on_timer---";

    symphony::IOManager::GetThis()->addTimer(1, on_timer, true);
}

int main(int argc, char** argv) {
    symphony::WorkerMgr::GetInstance()->init(
        {{"service_io", {{"thread_num", "1"}}}});
    symphony::IOManager iom(1);
    iom.addTimer(
        1000, []() { std::cout << rsdlb->statusString() << std::endl; }, true);
    iom.schedule(run);
    return 0;
}