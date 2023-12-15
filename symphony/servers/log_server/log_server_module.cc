#include "log_server_module.h"
#include "log_server_protocol.h"
#include "symphony/log.h"
namespace symphony {
namespace ls {
static symphony::Logger::ptr g_logger = SYMPHONY_LOG_NAME("system");
LogServerModule::LogServerModule()
    : RockModule("LogServerModule", "1.0.0", "") {}
bool LogServerModule::handleRockRequest(symphony::RockRequest::ptr request,
                                        symphony::RockResponse::ptr response,
                                        symphony::RockStream::ptr stream) {
    switch (request->getCmd()) {
        case (int)LSCommand::TICK: {
            return handleTick(request, response, stream);
        }
        default:
            SYMPHONY_LOG_WARN(g_logger)
                << "invalid cmd=0x" << std::hex << request->getCmd();
            break;
    }
    return true;
}

bool LogServerModule::handleRockNotify(symphony::RockNotify::ptr notify,
                                       symphony::RockStream::ptr stream) {
    return true;
}

bool LogServerModule::onConnect(symphony::Stream::ptr stream) {
    return true;
}

bool LogServerModule::onDisconnect(symphony::Stream::ptr stream) {
    return true;
}

bool LogServerModule::handleTick(symphony::RockRequest::ptr request,
                                 symphony::RockResponse::ptr response,
                                 symphony::RockStream::ptr stream) {
    SYMPHONY_LOG_DEBUG(g_logger) << "handleTick";
    return true;
}

std::string LogServerModule::statusString() {
    std::stringstream ss;
    return ss.str();
}

extern "C" {

symphony::Module* CreateModule() {
    std::cout << "=============CreateModule=================" << std::endl;
    return new LogServerModule;
}

void DestoryModule(symphony::Module* ptr) {
    std::cout << "=============DestoryModule=================" << std::endl;
    delete ptr;
}
}

}  // namespace ls
}  // namespace symphony