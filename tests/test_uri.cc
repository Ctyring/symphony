#include <iostream>
#include "symphony/uri.h"

int main(int argc, char** argv) {
    // symphony::Uri::ptr uri =
    // symphony::Uri::Create("http://www.sylar.top/test/uri?id=100&name=sylar#frg");
    symphony::Uri::ptr uri = symphony::Uri::Create(
        "http://admin@www.sylar.top/test/中文/"
        "uri?id=100&name=sylar&vv=中文#frg中文");
    // symphony::Uri::ptr uri =
    // symphony::Uri::Create("http://admin@www.sylar.top"); symphony::Uri::ptr
    // uri = symphony::Uri::Create("http://www.sylar.top/test/uri");
    std::cout << uri->toString() << std::endl;
    auto addr = uri->createAddress();
    std::cout << *addr << std::endl;
    return 0;
}