#include "config_servlet.h"
#include "symphony/config.h"

namespace symphony {
namespace http {

ConfigServlet::ConfigServlet() : Servlet("ConfigServlet") {}

int32_t ConfigServlet::handle(symphony::http::HttpRequest::ptr request,
                              symphony::http::HttpResponse::ptr response,
                              symphony::http::HttpSession::ptr session) {
    std::string type = request->getParam("type");
    if (type == "json") {
        response->setHeader("Content-Type", "text/json charset=utf-8");
    } else {
        response->setHeader("Content-Type", "text/yaml charset=utf-8");
    }
    YAML::Node node;
    symphony::Config::Visit([&node](ConfigVarBase::ptr base) {
        YAML::Node n;
        try {
            n = YAML::Load(base->toString());
        } catch (...) {
            return;
        }
        node[base->getName()] = n;
        node[base->getName() + "$description"] = base->getDescription();
    });
    if (type == "json") {
        Json::Value jvalue;
        if (YamlToJson(node, jvalue)) {
            response->setBody(JsonUtil::ToString(jvalue));
            return 0;
        }
    }
    std::stringstream ss;
    ss << node;
    response->setBody(ss.str());
    return 0;
}

}  // namespace http
}  // namespace symphony