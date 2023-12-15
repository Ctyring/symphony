#pragma once
#include "symphony/rock/rock_stream.h"

namespace symphony {
namespace ls {
class LSClient : public RockConnection {
   public:
    typedef std::shared_ptr<LSClient> ptr;
    LSClient();
    ~LSClient();

    void init();
    void uninit();

    void onQueryDomainChange();
    bool onConnect(symphony::AsyncSocketStream::ptr stream);
    void onDisconnect(symphony::AsyncSocketStream::ptr stream);
    bool onNotify(symphony::RockNotify::ptr, symphony::RockStream::ptr);
    void onTimer();
};
}  // namespace ls
}  // namespace symphony