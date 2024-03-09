#pragma once
namespace symphony {

class str_util {
   public:
    static bool HasSymbol(const char* pStr, const char* pszSymbol);
    static bool stringTrim(std::string& strValue);
};
}  // namespace symphony