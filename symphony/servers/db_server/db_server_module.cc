#include "db_server_module.h"

namespace symphony {
namespace db {
DBServerModule::DBServerModule() : RockModule("DBServerModule", "1.0.0", "") {}
bool DBServerModule::onServerReady() {}
bool DBServerModule::handleRockRequest(symphony::RockRequest::ptr request,
                                       symphony::RockResponse::ptr response,
                                       symphony::RockStream::ptr stream) {}
bool handleMsgRoleListReq(symphony::RockRequest::ptr request,
                          symphony::RockResponse::ptr response,
                          symphony::RockStream::ptr stream) {}
bool handleMsgRoleLoginReq(symphony::RockRequest::ptr request,
                           symphony::RockResponse::ptr response,
                           symphony::RockStream::ptr stream) {}
bool handleMsgRoleDeleteReq(symphony::RockRequest::ptr request,
                            symphony::RockResponse::ptr response,
                            symphony::RockStream::ptr stream) {}
bool handleMsgExeSqlReq(symphony::RockRequest::ptr request,
                        symphony::RockResponse::ptr response,
                        symphony::RockStream::ptr stream) {}
bool handleMsgLogicSvrRegReq(symphony::RockRequest::ptr request,
                             symphony::RockResponse::ptr response,
                             symphony::RockStream::ptr stream) {}

bool DBServerModule::handleRockNotify(symphony::RockNotify::ptr notify,
                                      symphony::RockStream::ptr stream) {}
bool DBServerModule::onConnect(symphony::Stream::ptr stream) {}
bool DBServerModule::onDisconnect(symphony::Stream::ptr stream) {}
std::string DBServerModule::statusString() {
    std::stringstream ss;
    return ss.str();
}

extern "C" {

symphony::Module* CreateModule() {
    std::cout << "=============DBServerModule Start================="
              << std::endl;
    return new DBServerModule;
}

void DestoryModule(symphony::Module* ptr) {
    std::cout << "=============Destory DBServerModule================="
              << std::endl;
    delete ptr;
}
}
}  // namespace db
}  // namespace symphony