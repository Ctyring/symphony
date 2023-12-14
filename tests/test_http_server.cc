#include "symphony/http/http_server.h"
#include "symphony/log.h"
static symphony::Logger::ptr g_logger = SYMPHONY_LOG_ROOT();
#define XX(...) #__VA_ARGS__

symphony::IOManager::ptr worker;
void run() {
    g_logger->setLevel(symphony::LogLevel::INFO);
    // symphony::http::HttpServer::ptr server(new
    // symphony::http::HttpServer(true, worker.get(),
    // symphony::IOManager::GetThis()));
    symphony::http::HttpServer::ptr server(
        new symphony::http::HttpServer(true));
    symphony::Address::ptr addr =
        symphony::Address::LookupAnyIPAddress("0.0.0.0:8020");
    while (!server->bind(addr)) {
        sleep(2);
    }
    auto sd = server->getServletDispatch();
    sd->addServlet("/symphony/xx",
                   [](symphony::http::HttpRequest::ptr req,
                      symphony::http::HttpResponse::ptr rsp,
                      symphony::http::HttpSession::ptr session) {
                       rsp->setBody(req->toString());
                       return 0;
                   });
    sd->addGlobServlet("/symphony/*",
                       [](symphony::http::HttpRequest::ptr req,
                          symphony::http::HttpResponse::ptr rsp,
                          symphony::http::HttpSession::ptr session) {
                           rsp->setBody("Glob:\r\n" + req->toString());
                           return 0;
                       });
    sd->addGlobServlet("/sylarx/*", [](symphony::http::HttpRequest::ptr req,
                                       symphony::http::HttpResponse::ptr rsp,
                                       symphony::http::HttpSession::ptr
                                           session) {
        rsp->setBody(XX(
            <html><head> < title > 404 Not Found</ title></ head><body>
                <center> < h1 >
                404 Not Found</ h1></ center><hr><center> nginx / 1.16.0 <
                / center > </ body></ html> < !--a padding to disable MSIE and
            Chrome friendly error page-- > < !--a padding to disable MSIE and
            Chrome friendly error page-- > < !--a padding to disable MSIE and
            Chrome friendly error page-- > < !--a padding to disable MSIE and
            Chrome friendly error page-- > < !--a padding to disable MSIE and
            Chrome friendly error page-- > < !--a padding to disable MSIE and
            Chrome friendly error page-- >));
        return 0;
    });
    SYMPHONY_LOG_INFO(g_logger) << "server start";
    server->start();
}

int main(int argc, char** argv) {
    symphony::IOManager iom(1, true, "main");
    worker.reset(new symphony::IOManager(3, false, "worker"));
    iom.schedule(run);
    return 0;
}