#include "thread.h"
#include "log.h"
namespace sylar {
static thread_local Thread* t_thread = nullptr;
static thread_local std::string t_thread_name = "UNKNOW";

static sylar::Logger::ptr g_logger = SYLAR_LOG_NAME("system");

Semaphore::Semaphore(uint32_t count) {
    // 三个参数：初始化对象，信号量类型(0代表线程间，其他代表进程间)，信号量大小
    if (sem_init(&m_semaphore, 0, count)) {
        throw std::logic_error("sem_init error");
    }
}
Semaphore::~Semaphore() {
    // 销毁信号量
    sem_destroy(&m_semaphore);
}
void Semaphore::wait() {
    // 信号量减一(如果信号量为0，阻塞等待)
    if (sem_wait(&m_semaphore)) {
        throw std::logic_error("sem_wait error");
    }
}
void Semaphore::notify() {
    // 信号量加一
    if (sem_post(&m_semaphore)) {
        throw std::logic_error("sem_post error");
    }
}

// 获取自己当前的线程
Thread* Thread::GetThis() {
    return t_thread;
}
const std::string& Thread::GetName() {
    return t_thread_name;
}
void Thread::SetName(const std::string& name) {
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
        SYLAR_LOG_ERROR(g_logger)
            << "pthread_create thread fail, rt=" << rt << " name=" << name;
        throw std::logic_error("pthread_create error");
    }
    m_semaphore.wait();
}
Thread::~Thread() {
    if (m_thread) {
        // 分离线程
        pthread_detach(m_thread);
    }
}

void Thread::join() {
    if (m_thread) {
        int rt = pthread_join(m_thread, nullptr);
        if (rt) {
            SYLAR_LOG_ERROR(g_logger)
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
    thread->m_id = sylar::GetThreadId();
    // 对线程命名 参数：线程本身 线程名称
    pthread_setname_np(pthread_self(), thread->m_name.substr(0, 15).c_str());

    std::function<void()> cb;
    // 清掉m_cb，防止线程内有智能指针等导致内存不释放问题。
    cb.swap(thread->m_cb);
    thread->m_semaphore.notify();
    cb();
    return 0;
}
}  // namespace sylar
