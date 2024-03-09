#include "str_util.h"
#include <string>
namespace symphony {
bool str_util::HasSymbol(const char* pStr, const char* pszSymbol) {
    if (pStr == nullptr || pszSymbol == nullptr) {
        return false;
    }

    const char* pSym = pszSymbol;
    while (*pSym != '\0') {
        const char* pTemp = pStr;
        while (*pTemp != '\0') {
            if (*pTemp == *pSym) {
                return true;
            }

            pTemp += 1;
        }

        pSym += 1;
    }

    return false;
}

bool str_util::stringTrim(std::string& strValue) {
    if (!strValue.empty()) {
        strValue.erase(0, strValue.find_first_not_of((" \n\r\t\v\f")));
        strValue.erase(strValue.find_last_not_of((" \n\r\t\v\f")) + 1);
    }
    return true;
}
}  // namespace symphony