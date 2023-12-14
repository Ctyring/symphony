#include <unistd.h>
#include <fstream>
#include <iostream>
#include "symphony/env.h"

struct A {
    A() {
        std::ifstream ifs("/proc/" + std::to_string(getpid()) + "/cmdline",
                          std::ios::binary);
        std::string content;
        content.resize(4096);

        ifs.read(&content[0], content.size());
        content.resize(ifs.gcount());

        for (size_t i = 0; i < content.size(); ++i) {
            std::cout << i << " - " << content[i] << " - " << (int)content[i]
                      << std::endl;
        }
    }
};

A a;

int main(int argc, char** argv) {
    std::cout << "argc=" << argc << std::endl;
    symphony::EnvMgr::GetInstance()->addHelp("s", "start with the terminal");
    symphony::EnvMgr::GetInstance()->addHelp("d", "run as daemon");
    symphony::EnvMgr::GetInstance()->addHelp("p", "print help");
    if (!symphony::EnvMgr::GetInstance()->init(argc, argv)) {
        symphony::EnvMgr::GetInstance()->printHelp();
        return 0;
    }

    std::cout << "exe=" << symphony::EnvMgr::GetInstance()->getExe()
              << std::endl;
    std::cout << "cwd=" << symphony::EnvMgr::GetInstance()->getCwd()
              << std::endl;

    std::cout << "path="
              << symphony::EnvMgr::GetInstance()->getEnv("PATH", "xxx")
              << std::endl;
    std::cout << "test=" << symphony::EnvMgr::GetInstance()->getEnv("TEST", "")
              << std::endl;
    std::cout << "set env "
              << symphony::EnvMgr::GetInstance()->setEnv("TEST", "yy")
              << std::endl;
    std::cout << "test=" << symphony::EnvMgr::GetInstance()->getEnv("TEST", "")
              << std::endl;
    if (symphony::EnvMgr::GetInstance()->has("p")) {
        symphony::EnvMgr::GetInstance()->printHelp();
    }
    return 0;
}