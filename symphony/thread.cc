#include "thread.h"
#include "log.h"
namespace symphony {
static thread_local Thread* t_thread = nullptr;
static thread_local std::string t_thread_name = "UNKNOW";

static symphony::Logger::ptr g_logger = SYMPHONY_LOG_NAME("system");

// 获取自己当前的线程
Thread* Thread::GetThis() {
    return t_thread;
}
const std::string& Thread::GetName() {
    return t_thread_name;
}
void Thread::SetName(const std::string& name) {
    if (name.empty()) {
        return;
    }
    if (t_thread) {
        t_thread->m_name = name;
    }
    t_thread_name = name;
}
Thread::Thread(std::function<void()> cb, const std::string& name)
    : m_cb(cb), m_name(name) {
    if (name.empty()) {
        m_name = "UNKNOW";
    }
    int rt = pthread_create(&m_thread, nullptr, &Thread::run, this);
    if (rt) {
        SYMPHONY_LOG_ERROR(g_logger)
            << "pthread_create thread fail, rt=" << rt << " name=" << name;
        throw std::logic_error("pthread_create error");
    }
    m_semaphore.wait();
}
Thread::~Thread() {
    // SYMPHONY_LOG_DEBUG(g_logger) << "线程销毁";
    if (m_thread) {
        // 将线程分离(因为线程类已经没了，但线程还没结束)，将该线程的状态设置为detached,则该线程运行结束后会自动释放所有资源。
        pthread_detach(m_thread);
    }
}

void Thread::join() {
    if (m_thread) {
        // 以阻塞的方式等待线程结束并回收
        // SYMPHONY_LOG_DEBUG(g_logger) << "线程回收";
        int rt = pthread_join(m_thread, nullptr);
        if (rt) {
            SYMPHONY_LOG_ERROR(g_logger)
                << "pthread_join thread fail, rt=" << rt << " name=" << m_name;
            throw std::logic_error("pthread_join error");
        }
        m_thread = 0;
    }
}

void* Thread::run(void* arg) {
    Thread* thread = (Thread*)arg;
    t_thread = thread;
    t_thread_name = thread->m_name;
    thread->m_id = symphony::GetThreadId();
    // 对线程命名 参数：线程本身 线程名称
    pthread_setname_np(pthread_self(), thread->m_name.substr(0, 15).c_str());

    std::function<void()> cb;
    // 清掉m_cb，防止线程内有智能指针等导致内存不释放问题。
    cb.swap(thread->m_cb);
    thread->m_semaphore.notify();
    cb();
    return 0;
}
}  // namespace symphony
