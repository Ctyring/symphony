// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: symphony/proto/msg_base.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_symphony_2fproto_2fmsg_5fbase_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_symphony_2fproto_2fmsg_5fbase_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021006 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_symphony_2fproto_2fmsg_5fbase_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_symphony_2fproto_2fmsg_5fbase_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_symphony_2fproto_2fmsg_5fbase_2eproto;
namespace symphony {
namespace proto {
class ItemData;
struct ItemDataDefaultTypeInternal;
extern ItemDataDefaultTypeInternal _ItemData_default_instance_;
class SkillItem;
struct SkillItemDefaultTypeInternal;
extern SkillItemDefaultTypeInternal _SkillItem_default_instance_;
}  // namespace proto
}  // namespace symphony
PROTOBUF_NAMESPACE_OPEN
template<> ::symphony::proto::ItemData* Arena::CreateMaybeMessage<::symphony::proto::ItemData>(Arena*);
template<> ::symphony::proto::SkillItem* Arena::CreateMaybeMessage<::symphony::proto::SkillItem>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace symphony {
namespace proto {

// ===================================================================

class ItemData final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:symphony.proto.ItemData) */ {
 public:
  inline ItemData() : ItemData(nullptr) {}
  ~ItemData() override;
  explicit PROTOBUF_CONSTEXPR ItemData(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  ItemData(const ItemData& from);
  ItemData(ItemData&& from) noexcept
    : ItemData() {
    *this = ::std::move(from);
  }

  inline ItemData& operator=(const ItemData& from) {
    CopyFrom(from);
    return *this;
  }
  inline ItemData& operator=(ItemData&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const ItemData& default_instance() {
    return *internal_default_instance();
  }
  static inline const ItemData* internal_default_instance() {
    return reinterpret_cast<const ItemData*>(
               &_ItemData_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(ItemData& a, ItemData& b) {
    a.Swap(&b);
  }
  inline void Swap(ItemData* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(ItemData* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  ItemData* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<ItemData>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const ItemData& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const ItemData& from) {
    ItemData::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(ItemData* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "symphony.proto.ItemData";
  }
  protected:
  explicit ItemData(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kItemIDFieldNumber = 1,
    kItemNumFieldNumber = 2,
  };
  // int32 ItemID = 1;
  void clear_itemid();
  int32_t itemid() const;
  void set_itemid(int32_t value);
  private:
  int32_t _internal_itemid() const;
  void _internal_set_itemid(int32_t value);
  public:

  // int32 ItemNum = 2;
  void clear_itemnum();
  int32_t itemnum() const;
  void set_itemnum(int32_t value);
  private:
  int32_t _internal_itemnum() const;
  void _internal_set_itemnum(int32_t value);
  public:

  // @@protoc_insertion_point(class_scope:symphony.proto.ItemData)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    int32_t itemid_;
    int32_t itemnum_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_symphony_2fproto_2fmsg_5fbase_2eproto;
};
// -------------------------------------------------------------------

class SkillItem final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:symphony.proto.SkillItem) */ {
 public:
  inline SkillItem() : SkillItem(nullptr) {}
  ~SkillItem() override;
  explicit PROTOBUF_CONSTEXPR SkillItem(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  SkillItem(const SkillItem& from);
  SkillItem(SkillItem&& from) noexcept
    : SkillItem() {
    *this = ::std::move(from);
  }

  inline SkillItem& operator=(const SkillItem& from) {
    CopyFrom(from);
    return *this;
  }
  inline SkillItem& operator=(SkillItem&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const SkillItem& default_instance() {
    return *internal_default_instance();
  }
  static inline const SkillItem* internal_default_instance() {
    return reinterpret_cast<const SkillItem*>(
               &_SkillItem_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  friend void swap(SkillItem& a, SkillItem& b) {
    a.Swap(&b);
  }
  inline void Swap(SkillItem* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(SkillItem* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  SkillItem* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<SkillItem>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const SkillItem& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const SkillItem& from) {
    SkillItem::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(SkillItem* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "symphony.proto.SkillItem";
  }
  protected:
  explicit SkillItem(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kSkillIDFieldNumber = 1,
    kLevelFieldNumber = 2,
    kKeyPosFieldNumber = 3,
  };
  // uint32 SkillID = 1;
  void clear_skillid();
  uint32_t skillid() const;
  void set_skillid(uint32_t value);
  private:
  uint32_t _internal_skillid() const;
  void _internal_set_skillid(uint32_t value);
  public:

  // int32 Level = 2;
  void clear_level();
  int32_t level() const;
  void set_level(int32_t value);
  private:
  int32_t _internal_level() const;
  void _internal_set_level(int32_t value);
  public:

  // int32 KeyPos = 3;
  void clear_keypos();
  int32_t keypos() const;
  void set_keypos(int32_t value);
  private:
  int32_t _internal_keypos() const;
  void _internal_set_keypos(int32_t value);
  public:

  // @@protoc_insertion_point(class_scope:symphony.proto.SkillItem)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    uint32_t skillid_;
    int32_t level_;
    int32_t keypos_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_symphony_2fproto_2fmsg_5fbase_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// ItemData

// int32 ItemID = 1;
inline void ItemData::clear_itemid() {
  _impl_.itemid_ = 0;
}
inline int32_t ItemData::_internal_itemid() const {
  return _impl_.itemid_;
}
inline int32_t ItemData::itemid() const {
  // @@protoc_insertion_point(field_get:symphony.proto.ItemData.ItemID)
  return _internal_itemid();
}
inline void ItemData::_internal_set_itemid(int32_t value) {
  
  _impl_.itemid_ = value;
}
inline void ItemData::set_itemid(int32_t value) {
  _internal_set_itemid(value);
  // @@protoc_insertion_point(field_set:symphony.proto.ItemData.ItemID)
}

// int32 ItemNum = 2;
inline void ItemData::clear_itemnum() {
  _impl_.itemnum_ = 0;
}
inline int32_t ItemData::_internal_itemnum() const {
  return _impl_.itemnum_;
}
inline int32_t ItemData::itemnum() const {
  // @@protoc_insertion_point(field_get:symphony.proto.ItemData.ItemNum)
  return _internal_itemnum();
}
inline void ItemData::_internal_set_itemnum(int32_t value) {
  
  _impl_.itemnum_ = value;
}
inline void ItemData::set_itemnum(int32_t value) {
  _internal_set_itemnum(value);
  // @@protoc_insertion_point(field_set:symphony.proto.ItemData.ItemNum)
}

// -------------------------------------------------------------------

// SkillItem

// uint32 SkillID = 1;
inline void SkillItem::clear_skillid() {
  _impl_.skillid_ = 0u;
}
inline uint32_t SkillItem::_internal_skillid() const {
  return _impl_.skillid_;
}
inline uint32_t SkillItem::skillid() const {
  // @@protoc_insertion_point(field_get:symphony.proto.SkillItem.SkillID)
  return _internal_skillid();
}
inline void SkillItem::_internal_set_skillid(uint32_t value) {
  
  _impl_.skillid_ = value;
}
inline void SkillItem::set_skillid(uint32_t value) {
  _internal_set_skillid(value);
  // @@protoc_insertion_point(field_set:symphony.proto.SkillItem.SkillID)
}

// int32 Level = 2;
inline void SkillItem::clear_level() {
  _impl_.level_ = 0;
}
inline int32_t SkillItem::_internal_level() const {
  return _impl_.level_;
}
inline int32_t SkillItem::level() const {
  // @@protoc_insertion_point(field_get:symphony.proto.SkillItem.Level)
  return _internal_level();
}
inline void SkillItem::_internal_set_level(int32_t value) {
  
  _impl_.level_ = value;
}
inline void SkillItem::set_level(int32_t value) {
  _internal_set_level(value);
  // @@protoc_insertion_point(field_set:symphony.proto.SkillItem.Level)
}

// int32 KeyPos = 3;
inline void SkillItem::clear_keypos() {
  _impl_.keypos_ = 0;
}
inline int32_t SkillItem::_internal_keypos() const {
  return _impl_.keypos_;
}
inline int32_t SkillItem::keypos() const {
  // @@protoc_insertion_point(field_get:symphony.proto.SkillItem.KeyPos)
  return _internal_keypos();
}
inline void SkillItem::_internal_set_keypos(int32_t value) {
  
  _impl_.keypos_ = value;
}
inline void SkillItem::set_keypos(int32_t value) {
  _internal_set_keypos(value);
  // @@protoc_insertion_point(field_set:symphony.proto.SkillItem.KeyPos)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace proto
}  // namespace symphony

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_symphony_2fproto_2fmsg_5fbase_2eproto
