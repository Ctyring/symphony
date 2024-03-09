#ifndef __COMMAND_LINE_H__
#define __COMMAND_LINE_H__
#include <stdint.h>
#include <map>
#include <string>
class CCommandLine {
   public:
    CCommandLine(int32_t argc, char* argv[]);

    ~CCommandLine();

    int32_t GetIntValue(const std::string& strKey) const;

    std::string GetStrValue(const std::string& strKey) const;

    int64_t GetLongValue(const std::string& strKey) const;

    float GetFloatValue(const std::string& strKey) const;

   protected:
    std::map<std::string, std::string> m_ParameterMap;
};

#endif /* __COMMAND_LINE_H__*/