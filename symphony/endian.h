#pragma once
#define SYMPHONY_LITTLE_ENDIAN 1
#define SYMPHONY_BIG_ENDIAN 2
#include <byteswap.h>
#include <stdint.h>
#include <type_traits>
namespace symphony {
template <class T>
typename std::enable_if<sizeof(T) == sizeof(uint64_t), T>::type byteswap(
    T value) {
    return (T)bswap_64((uint64_t)value);
}

template <class T>
typename std::enable_if<sizeof(T) == sizeof(uint32_t), T>::type byteswap(
    T value) {
    return (T)bswap_32((uint32_t)value);
}

template <class T>
typename std::enable_if<sizeof(T) == sizeof(uint16_t), T>::type byteswap(
    T value) {
    return (T)bswap_16((uint16_t)value);
}

#if BYTE_ORDER == BIG_ENDIAN
#define SYMPHONY_BYTE_ORDER SYMPHONY_BIG_ENDIAN
#else
#define SYMPHONY_BYTE_ORDER SYMPHONY_LITTLE_ENDIAN
#endif

#if SYMPHONY_BYTE_ORDER == SYMPHONY_BIG_ENDIAN
template <class T>
T byteswapOnLittleEndian(T t) {
    return t;
}

template <class T>
T byteswapOnBigEndian(T t) {
    return byteswap(t);
}

#else

template <class T>
T byteswapOnLittleEndian(T t) {
    return byteswap(t);
}

template <class T>
T byteswapOnBigEndian(T t) {
    return t;
}

#endif
}  // namespace symphony