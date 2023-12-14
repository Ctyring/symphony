#ifndef __SYMPHONY_LIBRARY_H__
#define __SYMPHONY_LIBRARY_H__

#include <memory>
#include "module.h"

namespace symphony {

class Library {
   public:
    static Module::ptr GetModule(const std::string& path);
};

}  // namespace symphony

#endif