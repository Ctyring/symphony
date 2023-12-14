#include "my_module.h"
#include "symphony/config.h"
#include "symphony/log.h"

namespace name_space {

static symphony::Logger::ptr g_logger = SYMPHONY_LOG_ROOT();

MyModule::MyModule() : symphony::Module("project_name", "1.0", "") {}

bool MyModule::onLoad() {
    SYMPHONY_LOG_INFO(g_logger) << "onLoad";
    return true;
}

bool MyModule::onUnload() {
    SYMPHONY_LOG_INFO(g_logger) << "onUnload";
    return true;
}

bool MyModule::onServerReady() {
    SYMPHONY_LOG_INFO(g_logger) << "onServerReady";
    return true;
}

bool MyModule::onServerUp() {
    SYMPHONY_LOG_INFO(g_logger) << "onServerUp";
    return true;
}

}  // namespace name_space

extern "C" {

symphony::Module* CreateModule() {
    symphony::Module* module = new name_space::MyModule;
    SYMPHONY_LOG_INFO(name_space::g_logger) << "CreateModule " << module;
    return module;
}

void DestoryModule(symphony::Module* module) {
    SYMPHONY_LOG_INFO(name_space::g_logger) << "CreateModule " << module;
    delete module;
}
}