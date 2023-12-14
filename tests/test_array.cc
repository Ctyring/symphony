#include "symphony/ds/array.h"
#include "symphony/symphony.h"

static symphony::Logger::ptr g_logger = SYMPHONY_LOG_ROOT();

struct PidVid {
    PidVid(uint32_t p = 0, uint32_t v = 0) : pid(p), vid(v) {}
    uint32_t pid;
    uint32_t vid;

    bool operator<(const PidVid& o) const {
        return memcmp(this, &o, sizeof(o)) < 0;
    }
};

void gen() {
    symphony::ds::Array<int> tmp;
    std::vector<int> vs;
    for (int i = 0; i < 10000; ++i) {
        int v = rand();
        tmp.insert(v);
        vs.push_back(v);
        SYMPHONY_ASSERT(tmp.isSorted());
    }

    std::ofstream ofs("./array.data");
    tmp.writeTo(ofs);

    for (auto& i : vs) {
        auto idx = tmp.exists(i);
        SYMPHONY_ASSERT(idx >= 0);
        tmp.erase(idx);
        SYMPHONY_ASSERT(tmp.isSorted());
    }
    SYMPHONY_ASSERT(tmp.size() == 0);
}

void test() {
    for (int i = 0; i < 10000; ++i) {
        SYMPHONY_LOG_INFO(g_logger) << "i=" << i;
        std::ifstream ifs("./array.data");
        symphony::ds::Array<int> tmp;
        if (!tmp.readFrom(ifs)) {
            SYMPHONY_LOG_INFO(g_logger) << "error";
        }
        SYMPHONY_ASSERT(tmp.isSorted());
        if (i % 100 == 0) {
            SYMPHONY_LOG_INFO(g_logger) << "over..." << (i + 1);
        }
    }
}

int main(int argc, char** argv) {
    gen();
    test();
    return 0;
}