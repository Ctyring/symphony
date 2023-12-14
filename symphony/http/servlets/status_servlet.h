#ifndef __SYMPHONY_HTTP_SERVLETS_STATUS_SERVLET_H__
#define __SYMPHONY_HTTP_SERVLETS_STATUS_SERVLET_H__

#include "symphony/http/servlet.h"

namespace symphony {
namespace http {

class StatusServlet : public Servlet {
   public:
    StatusServlet();
    virtual int32_t handle(symphony::http::HttpRequest::ptr request,
                           symphony::http::HttpResponse::ptr response,
                           symphony::http::HttpSession::ptr session) override;
};

}  // namespace http
}  // namespace symphony

#endif