#include "symphony/email/email.h"
#include "symphony/email/smtp.h"

void test() {
    symphony::EMail::ptr email =
        symphony::EMail::Create("caotiyuan@163.com", "password", "hello world",
                                "<B>hi </B>hello world", {"173479693@qq.com"});
    symphony::EMailEntity::ptr entity =
        symphony::EMailEntity::CreateAttach("symphony/symphony.h");
    if (entity) {
        email->addEntity(entity);
    }

    entity = symphony::EMailEntity::CreateAttach("symphony/address.cc");
    if (entity) {
        email->addEntity(entity);
    }

    auto client = symphony::SmtpClient::Create("smtp.163.com", 465, true);
    if (!client) {
        std::cout << "connect smtp.163.com:25 fail" << std::endl;
        return;
    }

    auto result = client->send(email, true);
    std::cout << "result=" << result->result << " msg=" << result->msg
              << std::endl;
    std::cout << client->getDebugInfo() << std::endl;
    // result = client->send(email, true);
    // std::cout << "result=" << result->result << " msg=" << result->msg <<
    // std::endl; std::cout << client->getDebugInfo() << std::endl;
}

int main(int argc, char** argv) {
    symphony::IOManager iom(1);
    iom.schedule(test);
    iom.stop();
    return 0;
}