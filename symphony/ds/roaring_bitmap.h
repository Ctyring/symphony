#ifndef __SYMPHONY_DS_ROARING_BITMAP_H__
#define __SYMPHONY_DS_ROARING_BITMAP_H__

#include <stdint.h>
#include <functional>
#include <memory>
#include <string>
#include <vector>
#include "roaring.hh"
#include "symphony/bytearray.h"

namespace symphony {
namespace ds {

class RoaringBitmap {
   public:
    typedef std::shared_ptr<RoaringBitmap> ptr;

    RoaringBitmap();
    RoaringBitmap(const RoaringBitmap& b);
    ~RoaringBitmap();

    RoaringBitmap& operator=(const RoaringBitmap& b);

    std::string toString() const;
    bool get(uint32_t idx) const;
    void set(uint32_t idx, bool v);

    void set(uint32_t from, uint32_t size, bool v);
    bool get(uint32_t from, uint32_t size, bool v) const;

    RoaringBitmap& operator&=(const RoaringBitmap& b);
    RoaringBitmap& operator|=(const RoaringBitmap& b);

    RoaringBitmap operator&(const RoaringBitmap& b);
    RoaringBitmap operator|(const RoaringBitmap& b);

    // RoaringBitmap& operator~();

    bool operator==(const RoaringBitmap& b) const;
    bool operator!=(const RoaringBitmap& b) const;

    RoaringBitmap::ptr compress() const;
    RoaringBitmap::ptr uncompress() const;

    bool any() const;

    void listPosAsc(std::vector<uint32_t>& pos);

    void foreach (std::function<bool(uint32_t)> cb);
    void rforeach(std::function<bool(uint32_t)> cb);

    void writeTo(symphony::ByteArray::ptr ba) const;
    bool readFrom(symphony::ByteArray::ptr ba);

    // uncompress to compress
    // uncompress to uncompress
    bool cross(const RoaringBitmap& b) const;

    float getCompressRate() const;

    uint32_t getCount() const;

   public:
    typedef RoaringSetBitForwardIterator iterator;
    typedef RoaringSetBitReverseIterator reverse_iterator;

    iterator begin() const { return m_bitmap.begin(); }
    iterator end() const { return m_bitmap.end(); }

    reverse_iterator rbegin() const { return m_bitmap.rbegin(); }
    reverse_iterator rend() const { return m_bitmap.rend(); }

   private:
    Roaring m_bitmap;
};

}  // namespace ds
}  // namespace symphony

#endif