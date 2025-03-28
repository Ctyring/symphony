#ifndef __SYMPHONY_ENV_H__
#define __SYMPHONY_ENV_H__

#include <map>
#include <vector>
#include "symphony/singleton.h"
#include "symphony/thread.h"

namespace symphony {

class Env {
   public:
    typedef RWMutex RWMutexType;
    bool init(int argc, char** argv);

    void add(const std::string& key, const std::string& val);
    bool has(const std::string& key);
    void del(const std::string& key);
    std::string get(const std::string& key,
                    const std::string& default_value = "");

    void addHelp(const std::string& key, const std::string& desc);
    void removeHelp(const std::string& key);
    void printHelp();

    const std::string& getExe() const { return m_exe; }
    const std::string& getCwd() const { return m_cwd; }

    bool setEnv(const std::string& key, const std::string& val);
    std::string getEnv(const std::string& key,
                       const std::string& default_value = "");

    std::string getAbsolutePath(const std::string& path) const;
    std::string getAbsoluteWorkPath(const std::string& path) const;
    std::string getConfigPath();

   private:
    RWMutexType m_mutex;
    std::map<std::string, std::string> m_args;
    std::vector<std::pair<std::string, std::string> > m_helps;

    // 控制台输入的命令地址
    std::string m_program;
    // 可执行文件的绝对地址
    std::string m_exe;
    // 可执行文件的绝对地址(不包含文件名)
    std::string m_cwd;
};

typedef symphony::Singleton<Env> EnvMgr;

}  // namespace symphony

#endif