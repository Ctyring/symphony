// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: symphony/proto/game_define.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_symphony_2fproto_2fgame_5fdefine_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_symphony_2fproto_2fgame_5fdefine_2eproto

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
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_symphony_2fproto_2fgame_5fdefine_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_symphony_2fproto_2fgame_5fdefine_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_symphony_2fproto_2fgame_5fdefine_2eproto;
PROTOBUF_NAMESPACE_OPEN
PROTOBUF_NAMESPACE_CLOSE
namespace symphony {
namespace proto {

enum EObjectType : int {
  OT_NONE = 0,
  OT_PLAYER = 1,
  OT_NPC = 2,
  OT_MONSTER = 3,
  OT_PET = 4,
  OT_MOUNT = 5,
  OT_MACHINE = 6,
  OT_PARTNER = 7,
  OT_SUMMON = 8,
  EObjectType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  EObjectType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool EObjectType_IsValid(int value);
constexpr EObjectType EObjectType_MIN = OT_NONE;
constexpr EObjectType EObjectType_MAX = OT_SUMMON;
constexpr int EObjectType_ARRAYSIZE = EObjectType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* EObjectType_descriptor();
template<typename T>
inline const std::string& EObjectType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, EObjectType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function EObjectType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    EObjectType_descriptor(), enum_t_value);
}
inline bool EObjectType_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, EObjectType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<EObjectType>(
    EObjectType_descriptor(), name, value);
}
enum EActionType : int {
  AT_NONE = 0,
  AT_IDLE = 1,
  AT_FIXBODY = 2,
  AT_WALK = 3,
  AT_RUN = 4,
  AT_FLY = 5,
  AT_SKILL = 6,
  AT_MINE = 7,
  AT_ROLL = 8,
  AT_JUMP = 9,
  AT_BORN = 10,
  AT_DANCE = 11,
  AT_DEAD = 12,
  AT_WOUND = 13,
  AT_BEATBACK = 14,
  AT_BEATDOWN = 15,
  AT_BEATFLY = 16,
  EActionType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  EActionType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool EActionType_IsValid(int value);
constexpr EActionType EActionType_MIN = AT_NONE;
constexpr EActionType EActionType_MAX = AT_BEATFLY;
constexpr int EActionType_ARRAYSIZE = EActionType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* EActionType_descriptor();
template<typename T>
inline const std::string& EActionType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, EActionType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function EActionType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    EActionType_descriptor(), enum_t_value);
}
inline bool EActionType_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, EActionType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<EActionType>(
    EActionType_descriptor(), name, value);
}
enum EActionStatue : int {
  AS_NONE = 0,
  AS_HURT = 1,
  AS_START = 2,
  AS_END = 268435455,
  EActionStatue_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  EActionStatue_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool EActionStatue_IsValid(int value);
constexpr EActionStatue EActionStatue_MIN = AS_NONE;
constexpr EActionStatue EActionStatue_MAX = AS_END;
constexpr int EActionStatue_ARRAYSIZE = EActionStatue_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* EActionStatue_descriptor();
template<typename T>
inline const std::string& EActionStatue_Name(T enum_t_value) {
  static_assert(::std::is_same<T, EActionStatue>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function EActionStatue_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    EActionStatue_descriptor(), enum_t_value);
}
inline bool EActionStatue_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, EActionStatue* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<EActionStatue>(
    EActionStatue_descriptor(), name, value);
}
enum ECopyType : int {
  CPT_NONE = 0,
  CPT_LOGIN = 1,
  CPT_SELROLE = 2,
  CPT_CITY = 3,
  CPT_MAIN = 4,
  CPT_WORLD = 5,
  CPT_END = 100,
  ECopyType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  ECopyType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool ECopyType_IsValid(int value);
constexpr ECopyType ECopyType_MIN = CPT_NONE;
constexpr ECopyType ECopyType_MAX = CPT_END;
constexpr int ECopyType_ARRAYSIZE = ECopyType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* ECopyType_descriptor();
template<typename T>
inline const std::string& ECopyType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, ECopyType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function ECopyType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    ECopyType_descriptor(), enum_t_value);
}
inline bool ECopyType_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, ECopyType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<ECopyType>(
    ECopyType_descriptor(), name, value);
}
enum EObjectStatus : int {
  EOS_NONE = 0,
  EOS_DEAD = 1,
  EOS_NOT_MOVE = 2,
  EOS_NOT_CAST = 3,
  EOS_NOT_BEHURT = 4,
  EOS_NOT_BECONTROL = 5,
  EOS_STEALTH = 6,
  EOS_BLIND = 7,
  EObjectStatus_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  EObjectStatus_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool EObjectStatus_IsValid(int value);
constexpr EObjectStatus EObjectStatus_MIN = EOS_NONE;
constexpr EObjectStatus EObjectStatus_MAX = EOS_BLIND;
constexpr int EObjectStatus_ARRAYSIZE = EObjectStatus_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* EObjectStatus_descriptor();
template<typename T>
inline const std::string& EObjectStatus_Name(T enum_t_value) {
  static_assert(::std::is_same<T, EObjectStatus>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function EObjectStatus_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    EObjectStatus_descriptor(), enum_t_value);
}
inline bool EObjectStatus_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, EObjectStatus* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<EObjectStatus>(
    EObjectStatus_descriptor(), name, value);
}
enum EItemType : int {
  EIT_NONE = 0,
  EIT_MONEY = 1,
  EIT_ACTION = 2,
  EIT_ITEM = 3,
  EIT_EQUIP = 4,
  EIT_GEM = 5,
  EIT_RELICS = 6,
  EIT_MOUNT = 7,
  EIT_PET = 8,
  EIT_PARTNER = 9,
  EIT_FASHION = 10,
  EIT_BOX = 11,
  EIT_ACTBOX = 12,
  EIT_CHIP = 13,
  EIT_RUNE = 14,
  EIT_DRUG = 15,
  EItemType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  EItemType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool EItemType_IsValid(int value);
constexpr EItemType EItemType_MIN = EIT_NONE;
constexpr EItemType EItemType_MAX = EIT_DRUG;
constexpr int EItemType_ARRAYSIZE = EItemType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* EItemType_descriptor();
template<typename T>
inline const std::string& EItemType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, EItemType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function EItemType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    EItemType_descriptor(), enum_t_value);
}
inline bool EItemType_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, EItemType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<EItemType>(
    EItemType_descriptor(), name, value);
}
enum EBagType : int {
  EBT_NONE = 0,
  EBT_ITEM = 1,
  EBT_GEM = 2,
  EBT_FASHION = 3,
  EBT_CHIP = 4,
  EBT_RUNE = 5,
  EBT_TASK = 6,
  EBT_SOUL = 7,
  EBT_CARD = 8,
  EBagType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  EBagType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool EBagType_IsValid(int value);
constexpr EBagType EBagType_MIN = EBT_NONE;
constexpr EBagType EBagType_MAX = EBT_CARD;
constexpr int EBagType_ARRAYSIZE = EBagType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* EBagType_descriptor();
template<typename T>
inline const std::string& EBagType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, EBagType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function EBagType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    EBagType_descriptor(), enum_t_value);
}
inline bool EBagType_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, EBagType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<EBagType>(
    EBagType_descriptor(), name, value);
}
enum EFunctionType : int {
  FUNC_BEGIN_ID = 0,
  FUNC_END_ID = 150,
  EFunctionType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  EFunctionType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool EFunctionType_IsValid(int value);
constexpr EFunctionType EFunctionType_MIN = FUNC_BEGIN_ID;
constexpr EFunctionType EFunctionType_MAX = FUNC_END_ID;
constexpr int EFunctionType_ARRAYSIZE = EFunctionType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* EFunctionType_descriptor();
template<typename T>
inline const std::string& EFunctionType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, EFunctionType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function EFunctionType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    EFunctionType_descriptor(), enum_t_value);
}
inline bool EFunctionType_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, EFunctionType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<EFunctionType>(
    EFunctionType_descriptor(), name, value);
}
enum EAttrID : int {
  EA_HP = 0,
  EA_MP = 1,
  EA_HP_MAX = 2,
  EA_MP_MAX = 3,
  EA_SPEED = 4,
  EA_ATTACK = 5,
  EA_ELEMENT = 6,
  EA_MAGIC_DEF = 7,
  EA_PHYSIC_DEF = 8,
  EA_HIT_RATE = 9,
  EA_DODGE = 10,
  EA_MORE_HURT = 11,
  EA_LESS_HURT = 12,
  EA_CRIT_HIT = 13,
  EA_CRIT_DEF = 14,
  EA_CRIT_HURT = 15,
  EA_ATTR_NUM = 16,
  EAttrID_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  EAttrID_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool EAttrID_IsValid(int value);
constexpr EAttrID EAttrID_MIN = EA_HP;
constexpr EAttrID EAttrID_MAX = EA_ATTR_NUM;
constexpr int EAttrID_ARRAYSIZE = EAttrID_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* EAttrID_descriptor();
template<typename T>
inline const std::string& EAttrID_Name(T enum_t_value) {
  static_assert(::std::is_same<T, EAttrID>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function EAttrID_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    EAttrID_descriptor(), enum_t_value);
}
inline bool EAttrID_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, EAttrID* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<EAttrID>(
    EAttrID_descriptor(), name, value);
}
enum EShip : int {
  ES_NEUTRAL = 0,
  ES_FRIEND = 1,
  ES_ENEMY = 2,
  EShip_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  EShip_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool EShip_IsValid(int value);
constexpr EShip EShip_MIN = ES_NEUTRAL;
constexpr EShip EShip_MAX = ES_ENEMY;
constexpr int EShip_ARRAYSIZE = EShip_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* EShip_descriptor();
template<typename T>
inline const std::string& EShip_Name(T enum_t_value) {
  static_assert(::std::is_same<T, EShip>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function EShip_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    EShip_descriptor(), enum_t_value);
}
inline bool EShip_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, EShip* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<EShip>(
    EShip_descriptor(), name, value);
}
enum EHitShipType : int {
  EHST_ALL = 0,
  EHST_FRIEND = 1,
  EHST_ENEMY = 2,
  EHitShipType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  EHitShipType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool EHitShipType_IsValid(int value);
constexpr EHitShipType EHitShipType_MIN = EHST_ALL;
constexpr EHitShipType EHitShipType_MAX = EHST_ENEMY;
constexpr int EHitShipType_ARRAYSIZE = EHitShipType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* EHitShipType_descriptor();
template<typename T>
inline const std::string& EHitShipType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, EHitShipType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function EHitShipType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    EHitShipType_descriptor(), enum_t_value);
}
inline bool EHitShipType_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, EHitShipType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<EHitShipType>(
    EHitShipType_descriptor(), name, value);
}
enum EBuffType : int {
  BFT_NONE = 0,
  EBuffType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  EBuffType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool EBuffType_IsValid(int value);
constexpr EBuffType EBuffType_MIN = BFT_NONE;
constexpr EBuffType EBuffType_MAX = BFT_NONE;
constexpr int EBuffType_ARRAYSIZE = EBuffType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* EBuffType_descriptor();
template<typename T>
inline const std::string& EBuffType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, EBuffType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function EBuffType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    EBuffType_descriptor(), enum_t_value);
}
inline bool EBuffType_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, EBuffType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<EBuffType>(
    EBuffType_descriptor(), name, value);
}
enum EChatChannel : int {
  CHL_NONE = 0,
  CHL_WORLD = 1,
  CHL_PRIVATE = 2,
  CHL_GUILD = 3,
  CHL_ROLLTIP = 4,
  EChatChannel_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  EChatChannel_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool EChatChannel_IsValid(int value);
constexpr EChatChannel EChatChannel_MIN = CHL_NONE;
constexpr EChatChannel EChatChannel_MAX = CHL_ROLLTIP;
constexpr int EChatChannel_ARRAYSIZE = EChatChannel_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* EChatChannel_descriptor();
template<typename T>
inline const std::string& EChatChannel_Name(T enum_t_value) {
  static_assert(::std::is_same<T, EChatChannel>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function EChatChannel_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    EChatChannel_descriptor(), enum_t_value);
}
inline bool EChatChannel_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, EChatChannel* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<EChatChannel>(
    EChatChannel_descriptor(), name, value);
}
enum EEquipPos : int {
  EEP_NONE = 0,
  EEP_HELMET = 1,
  EEP_NECKLACE = 2,
  EEP_ARMOR = 3,
  EEP_SHOES = 4,
  EEP_WRIST = 5,
  EEP_RING = 6,
  EEP_TALISMAN = 7,
  EEP_WEAPON = 8,
  EEquipPos_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  EEquipPos_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool EEquipPos_IsValid(int value);
constexpr EEquipPos EEquipPos_MIN = EEP_NONE;
constexpr EEquipPos EEquipPos_MAX = EEP_WEAPON;
constexpr int EEquipPos_ARRAYSIZE = EEquipPos_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* EEquipPos_descriptor();
template<typename T>
inline const std::string& EEquipPos_Name(T enum_t_value) {
  static_assert(::std::is_same<T, EEquipPos>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function EEquipPos_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    EEquipPos_descriptor(), enum_t_value);
}
inline bool EEquipPos_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, EEquipPos* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<EEquipPos>(
    EEquipPos_descriptor(), name, value);
}
enum ETaskStatus : int {
  ETS_INIT = 0,
  ETS_ACCEPT = 1,
  ETS_FINISH = 2,
  ETS_COMMIT = 3,
  ETaskStatus_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  ETaskStatus_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool ETaskStatus_IsValid(int value);
constexpr ETaskStatus ETaskStatus_MIN = ETS_INIT;
constexpr ETaskStatus ETaskStatus_MAX = ETS_COMMIT;
constexpr int ETaskStatus_ARRAYSIZE = ETaskStatus_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* ETaskStatus_descriptor();
template<typename T>
inline const std::string& ETaskStatus_Name(T enum_t_value) {
  static_assert(::std::is_same<T, ETaskStatus>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function ETaskStatus_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    ETaskStatus_descriptor(), enum_t_value);
}
inline bool ETaskStatus_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, ETaskStatus* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<ETaskStatus>(
    ETaskStatus_descriptor(), name, value);
}
enum ECopyResult : int {
  ECR_NONE = 0,
  ECR_WIN = 1,
  ECR_LOST = 2,
  ECR_DRAW = 3,
  ECopyResult_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  ECopyResult_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool ECopyResult_IsValid(int value);
constexpr ECopyResult ECopyResult_MIN = ECR_NONE;
constexpr ECopyResult ECopyResult_MAX = ECR_DRAW;
constexpr int ECopyResult_ARRAYSIZE = ECopyResult_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* ECopyResult_descriptor();
template<typename T>
inline const std::string& ECopyResult_Name(T enum_t_value) {
  static_assert(::std::is_same<T, ECopyResult>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function ECopyResult_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    ECopyResult_descriptor(), enum_t_value);
}
inline bool ECopyResult_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, ECopyResult* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<ECopyResult>(
    ECopyResult_descriptor(), name, value);
}
enum EGuildPos : int {
  EGP_MEMBER = 0,
  EGP_LEADER = 1,
  EGP_VICELEADER = 2,
  EGuildPos_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  EGuildPos_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool EGuildPos_IsValid(int value);
constexpr EGuildPos EGuildPos_MIN = EGP_MEMBER;
constexpr EGuildPos EGuildPos_MAX = EGP_VICELEADER;
constexpr int EGuildPos_ARRAYSIZE = EGuildPos_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* EGuildPos_descriptor();
template<typename T>
inline const std::string& EGuildPos_Name(T enum_t_value) {
  static_assert(::std::is_same<T, EGuildPos>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function EGuildPos_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    EGuildPos_descriptor(), enum_t_value);
}
inline bool EGuildPos_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, EGuildPos* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<EGuildPos>(
    EGuildPos_descriptor(), name, value);
}
enum EMailType : int {
  EMT_BEGIN = 0,
  EMT_CUSTOM = 1,
  EMailType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  EMailType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool EMailType_IsValid(int value);
constexpr EMailType EMailType_MIN = EMT_BEGIN;
constexpr EMailType EMailType_MAX = EMT_CUSTOM;
constexpr int EMailType_ARRAYSIZE = EMailType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* EMailType_descriptor();
template<typename T>
inline const std::string& EMailType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, EMailType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function EMailType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    EMailType_descriptor(), enum_t_value);
}
inline bool EMailType_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, EMailType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<EMailType>(
    EMailType_descriptor(), name, value);
}
enum EMailStatus : int {
  EMS_NEWMAIL = 0,
  EMS_RECEIVED = 1,
  EMailStatus_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::min(),
  EMailStatus_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<int32_t>::max()
};
bool EMailStatus_IsValid(int value);
constexpr EMailStatus EMailStatus_MIN = EMS_NEWMAIL;
constexpr EMailStatus EMailStatus_MAX = EMS_RECEIVED;
constexpr int EMailStatus_ARRAYSIZE = EMailStatus_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* EMailStatus_descriptor();
template<typename T>
inline const std::string& EMailStatus_Name(T enum_t_value) {
  static_assert(::std::is_same<T, EMailStatus>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function EMailStatus_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    EMailStatus_descriptor(), enum_t_value);
}
inline bool EMailStatus_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, EMailStatus* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<EMailStatus>(
    EMailStatus_descriptor(), name, value);
}
// ===================================================================


// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace proto
}  // namespace symphony

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::symphony::proto::EObjectType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::symphony::proto::EObjectType>() {
  return ::symphony::proto::EObjectType_descriptor();
}
template <> struct is_proto_enum< ::symphony::proto::EActionType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::symphony::proto::EActionType>() {
  return ::symphony::proto::EActionType_descriptor();
}
template <> struct is_proto_enum< ::symphony::proto::EActionStatue> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::symphony::proto::EActionStatue>() {
  return ::symphony::proto::EActionStatue_descriptor();
}
template <> struct is_proto_enum< ::symphony::proto::ECopyType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::symphony::proto::ECopyType>() {
  return ::symphony::proto::ECopyType_descriptor();
}
template <> struct is_proto_enum< ::symphony::proto::EObjectStatus> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::symphony::proto::EObjectStatus>() {
  return ::symphony::proto::EObjectStatus_descriptor();
}
template <> struct is_proto_enum< ::symphony::proto::EItemType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::symphony::proto::EItemType>() {
  return ::symphony::proto::EItemType_descriptor();
}
template <> struct is_proto_enum< ::symphony::proto::EBagType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::symphony::proto::EBagType>() {
  return ::symphony::proto::EBagType_descriptor();
}
template <> struct is_proto_enum< ::symphony::proto::EFunctionType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::symphony::proto::EFunctionType>() {
  return ::symphony::proto::EFunctionType_descriptor();
}
template <> struct is_proto_enum< ::symphony::proto::EAttrID> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::symphony::proto::EAttrID>() {
  return ::symphony::proto::EAttrID_descriptor();
}
template <> struct is_proto_enum< ::symphony::proto::EShip> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::symphony::proto::EShip>() {
  return ::symphony::proto::EShip_descriptor();
}
template <> struct is_proto_enum< ::symphony::proto::EHitShipType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::symphony::proto::EHitShipType>() {
  return ::symphony::proto::EHitShipType_descriptor();
}
template <> struct is_proto_enum< ::symphony::proto::EBuffType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::symphony::proto::EBuffType>() {
  return ::symphony::proto::EBuffType_descriptor();
}
template <> struct is_proto_enum< ::symphony::proto::EChatChannel> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::symphony::proto::EChatChannel>() {
  return ::symphony::proto::EChatChannel_descriptor();
}
template <> struct is_proto_enum< ::symphony::proto::EEquipPos> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::symphony::proto::EEquipPos>() {
  return ::symphony::proto::EEquipPos_descriptor();
}
template <> struct is_proto_enum< ::symphony::proto::ETaskStatus> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::symphony::proto::ETaskStatus>() {
  return ::symphony::proto::ETaskStatus_descriptor();
}
template <> struct is_proto_enum< ::symphony::proto::ECopyResult> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::symphony::proto::ECopyResult>() {
  return ::symphony::proto::ECopyResult_descriptor();
}
template <> struct is_proto_enum< ::symphony::proto::EGuildPos> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::symphony::proto::EGuildPos>() {
  return ::symphony::proto::EGuildPos_descriptor();
}
template <> struct is_proto_enum< ::symphony::proto::EMailType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::symphony::proto::EMailType>() {
  return ::symphony::proto::EMailType_descriptor();
}
template <> struct is_proto_enum< ::symphony::proto::EMailStatus> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::symphony::proto::EMailStatus>() {
  return ::symphony::proto::EMailStatus_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_symphony_2fproto_2fgame_5fdefine_2eproto
