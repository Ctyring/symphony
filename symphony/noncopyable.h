#ifndef __SYMPHONY_NONCOPYABLE_H__
#define __SYMPHONY_NONCOPYABLE_H__
namespace symphony {
class Noncopyable {
   public:
    Noncopyable() = default;
    ~Noncopyable() = default;
    Noncopyable(const Noncopyable&) = delete;
    Noncopyable& operator=(const Noncopyable&) = delete;
};
}  // namespace symphony
#endif