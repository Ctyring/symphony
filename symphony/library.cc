#include "library.h"

#include <dlfcn.h>
#include "symphony/config.h"
#include "symphony/env.h"
#include "symphony/log.h"

namespace symphony {

static symphony::Logger::ptr g_logger = SYMPHONY_LOG_NAME("system");

typedef Module* (*create_module)();
typedef void (*destory_module)(Module*);

class ModuleCloser {
   public:
    ModuleCloser(void* handle, destory_module d)
        : m_handle(handle), m_destory(d) {}

    void operator()(Module* module) {
        std::string name = module->getName();
        std::string version = module->getVersion();
        std::string path = module->getFilename();
        m_destory(module);
        int rt = dlclose(m_handle);
        if (rt) {
            SYMPHONY_LOG_ERROR(g_logger)
                << "dlclose handle fail handle=" << m_handle << " name=" << name
                << " version=" << version << " path=" << path
                << " error=" << dlerror();
        } else {
            SYMPHONY_LOG_INFO(g_logger)
                << "destory module=" << name << " version=" << version
                << " path=" << path << " handle=" << m_handle << " success";
        }
    }

   private:
    void* m_handle;
    destory_module m_destory;
};

Module::ptr Library::GetModule(const std::string& path) {
    void* handle = dlopen(path.c_str(), RTLD_NOW);
    if (!handle) {
        SYMPHONY_LOG_ERROR(g_logger)
            << "cannot load library path=" << path << " error=" << dlerror();
        return nullptr;
    }

    create_module create = (create_module)dlsym(handle, "CreateModule");
    if (!create) {
        SYMPHONY_LOG_ERROR(g_logger) << "cannot load symbol CreateModule in "
                                     << path << " error=" << dlerror();
        dlclose(handle);
        return nullptr;
    }

    destory_module destory = (destory_module)dlsym(handle, "DestoryModule");
    if (!destory) {
        SYMPHONY_LOG_ERROR(g_logger) << "cannot load symbol DestoryModule in "
                                     << path << " error=" << dlerror();
        dlclose(handle);
        return nullptr;
    }

    Module::ptr module(create(), ModuleCloser(handle, destory));
    module->setFilename(path);
    SYMPHONY_LOG_INFO(g_logger)
        << "load module name=" << module->getName()
        << " version=" << module->getVersion()
        << " path=" << module->getFilename() << " success";
    Config::LoadFromConfDir(symphony::EnvMgr::GetInstance()->getConfigPath(),
                            true);
    return module;
}

}  // namespace symphony