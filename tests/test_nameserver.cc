#include "symphony/ns/ns_client.h"
#include "symphony/ns/ns_protocol.h"
#include "symphony/symphony.h"

static symphony::Logger::ptr g_logger = SYMPHONY_LOG_ROOT();

int type = 0;

void run() {
    g_logger->setLevel(symphony::LogLevel::INFO);
    auto addr = symphony::IPAddress::Create("127.0.0.1", 8072);
    // if(!conn->connect(addr)) {
    //     SYMPHONY_LOG_ERROR(g_logger) << "connect to: " << *addr << " fail";
    //     return;
    // }
    if (type == 0) {
        for (int i = 0; i < 5000; ++i) {
            symphony::RockConnection::ptr conn(new symphony::RockConnection);
            conn->connect(addr);
            symphony::IOManager::GetThis()->addTimer(
                3000,
                [conn, i]() {
                    symphony::RockRequest::ptr req(new symphony::RockRequest);
                    req->setCmd((int)symphony::ns::NSCommand::REGISTER);
                    auto rinfo =
                        std::make_shared<symphony::ns::RegisterRequest>();
                    auto info = rinfo->add_infos();
                    info->set_domain(std::to_string(rand() % 2) + "domain.com");
                    info->add_cmds(rand() % 2 + 100);
                    info->add_cmds(rand() % 2 + 200);
                    info->mutable_node()->set_ip("127.0.0.1");
                    info->mutable_node()->set_port(1000 + i);
                    info->mutable_node()->set_weight(100);
                    req->setAsPB(*rinfo);

                    auto rt = conn->request(req, 100);
                    SYMPHONY_LOG_INFO(g_logger)
                        << "[result=" << rt->result << " response="
                        << (rt->response ? rt->response->toString() : "null")
                        << "]";
                },
                true);
            conn->start();
        }
    } else {
        for (int i = 0; i < 1000; ++i) {
            symphony::ns::NSClient::ptr nsclient(new symphony::ns::NSClient);
            nsclient->init();
            nsclient->addQueryDomain(std::to_string(i % 2) + "domain.com");
            nsclient->connect(addr);
            nsclient->start();
            SYMPHONY_LOG_INFO(g_logger) << "NSClient start: i=" << i;

            if (i == 0) {
                // symphony::IOManager::GetThis()->addTimer(1000, [nsclient](){
                //     auto domains = nsclient->getDomains();
                //     domains->dump(std::cout, "    ");
                // }, true);
            }
        }

        // conn->setConnectCb([](symphony::AsyncSocketStream::ptr ss) {
        //     auto conn =
        //     std::dynamic_pointer_cast<symphony::RockConnection>(ss);
        //     symphony::RockRequest::ptr req(new symphony::RockRequest);
        //     req->setCmd((int)symphony::ns::NSCommand::QUERY);
        //     auto rinfo = std::make_shared<symphony::ns::QueryRequest>();
        //     rinfo->add_domains("0domain.com");
        //     req->setAsPB(*rinfo);
        //     auto rt = conn->request(req, 1000);
        //     SYMPHONY_LOG_INFO(g_logger) << "[result="
        //         << rt->result << " response="
        //         << (rt->response ? rt->response->toString() : "null")
        //         << "]";
        //     return true;
        // });

        // conn->setNotifyHandler([](symphony::RockNotify::ptr
        // nty,symphony::RockStream::ptr stream){
        //         auto nm = nty->getAsPB<symphony::ns::NotifyMessage>();
        //         if(!nm) {
        //             SYMPHONY_LOG_ERROR(g_logger) << "invalid notify message";
        //             return true;
        //         }
        //         SYMPHONY_LOG_INFO(g_logger) << symphony::PBToJsonString(*nm);
        //         return true;
        // });
    }
}

int main(int argc, char** argv) {
    if (argc > 1) {
        type = 1;
    }
    symphony::IOManager iom(5);
    iom.schedule(run);
    return 0;
}