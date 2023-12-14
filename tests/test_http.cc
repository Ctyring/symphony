#include "symphony/http/http.h"
#include "symphony/log.h"
void test() {
    symphony::http::HttpRequest::ptr req(new symphony::http::HttpRequest);
    req->setHeader("host", "www.sylar.top");
    req->setBody("hello world!");
    req->dump(std::cout) << std::endl;
}

void test_response() {
    symphony::http::HttpResponse::ptr resp(new symphony::http::HttpResponse);
    resp->setHeader("X-X", "sylar");
    resp->setBody("hello world!");
    resp->setStatus(symphony::http::HttpStatus::BAD_REQUEST);
    resp->setClose(false);
    // 设置长连接
    resp->setHeader("Connection", "keep-alive");
    resp->dump(std::cout) << std::endl;
}
int main(int argc, char** argv) {
    test_response();
    return 0;
}