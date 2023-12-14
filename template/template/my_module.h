#include "symphony/module.h"

namespace name_space {

class MyModule : public symphony::Module {
   public:
    typedef std::shared_ptr<MyModule> ptr;
    MyModule();
    bool onLoad() override;
    bool onUnload() override;
    bool onServerReady() override;
    bool onServerUp() override;
};

}  // namespace name_space