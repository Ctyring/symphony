// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: symphony/proto/msg_ret_code.proto

#include "symphony/proto/msg_ret_code.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

static const ::_pb::EnumDescriptor* file_level_enum_descriptors_symphony_2fproto_2fmsg_5fret_5fcode_2eproto[1];
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_symphony_2fproto_2fmsg_5fret_5fcode_2eproto = nullptr;
const uint32_t TableStruct_symphony_2fproto_2fmsg_5fret_5fcode_2eproto::offsets[1] = {};
static constexpr ::_pbi::MigrationSchema* schemas = nullptr;
static constexpr ::_pb::Message* const* file_default_instances = nullptr;

const char descriptor_table_protodef_symphony_2fproto_2fmsg_5fret_5fcode_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n!symphony/proto/msg_ret_code.proto*\234\013\n\016"
  "MessageRetCode\022\021\n\rMRC_SUCCESSED\020\000\022\024\n\020MRC"
  "_UNKNOW_ERROR\020\001\022\022\n\016MRC_DISCONNECT\020\002\022\027\n\023M"
  "RC_INVALID_ACCNAME\020d\022\025\n\021MRC_INVALID_ACCI"
  "D\020e\022\030\n\024MRC_INVALID_PASSWORD\020f\022\024\n\020MRC_INV"
  "ALID_NAME\020g\022\026\n\022MRC_INVALID_ROLEID\020h\022\026\n\022M"
  "RC_INVALID_ITEMID\020i\022\026\n\022MRC_INVALID_COPYI"
  "D\020j\022\025\n\021MRC_INVALID_PETID\020k\022\031\n\025MRC_INVALI"
  "D_PARTNERID\020l\022\030\n\024MRC_INVALID_EQUIP_ID\020m\022"
  "\030\n\024MRC_INVALID_CARRERID\020n\022\030\n\024MRC_INVALID"
  "_SKILL_ID\020o\022\031\n\025MRC_INVALID_TARGET_ID\020p\022\031"
  "\n\025MRC_INVALID_SERVER_ID\020q\022\031\n\025MRC_INVALID"
  "_GIFT_CODE\020r\022\032\n\025MRC_NOT_ENOUGH_ACTOIN\020\310\001"
  "\022\031\n\024MRC_NOT_ENOUGH_MONEY\020\311\001\022\030\n\023MRC_NOT_E"
  "NOUGH_ITEM\020\312\001\022\031\n\024MRC_NOT_ENOUGH_TIMES\020\313\001"
  "\022\031\n\024MRC_NOT_ENOUGH_LEVEL\020\314\001\022\031\n\024MRC_NOT_E"
  "NOUGH_VIPLV\020\315\001\022\030\n\023MRC_ERROR_SEAL_ROLE\020\316\001"
  "\022\027\n\022MRC_NAME_ERROR_FMT\020\317\001\022\025\n\020MRC_REPEAT_"
  "LOGIN\020\320\001\022\033\n\026MRC_ACCOUNT_NAME_EXIST\020\254\002\022\037\n"
  "\032MRC_ACCOUNT_NAME_NOT_EXIST\020\255\002\022\035\n\030MRC_AC"
  "COUNT_NAME_ERR_FMT\020\256\002\022\030\n\023MRC_ROLE_NAME_E"
  "XIST\020\257\002\022\027\n\022MRC_ACCOUNT_SEALED\020\260\002\022\036\n\031MRC_"
  "ACCOUNT_WRONG_VERSION\020\261\002\022\037\n\032MRC_ACCOUNT_"
  "WRONG_PASSWORD\020\262\002\022\034\n\027MRC_ROLE_NAME_MUST_"
  "UTF8\020\264\002\022\024\n\017MRC_ROLE_SEALED\020\265\002\022\025\n\020MRC_ROL"
  "E_DELETED\020\266\002\022\032\n\025MRC_ILLEGAL_LOGIN_REQ\020\267\002"
  "\022\031\n\024MRC_KICKOUT_BY_OTHER\020\270\002\022\034\n\027MRC_SERVE"
  "R_NOT_OPENTIME\020\271\002\022\035\n\030MRC_SERVER_NOT_AVAI"
  "LABLE\020\272\002\022\030\n\023MRC_SERVER_MAINTAIN\020\273\002\022\033\n\026MR"
  "C_SERVER_NO_NEW_ROLE\020\274\002\022\031\n\024MRC_CANNOT_RE"
  "CONNECT\020\275\002\022\027\n\022MRC_SKILL_CD_ERROR\020\221\003\022\027\n\022M"
  "RC_SKILL_DEAD_OBJ\020\222\003\022\034\n\027MRC_DUPLICATED_O"
  "RDER_ID\020\223\003\022\035\n\030MRC_GIFTCODE_AREADY_USED\020\364"
  "\003\022\037\n\032MRC_GIFTCODE_INVALIDE_CODE\020\365\003\022\034\n\027MR"
  "C_GIFTCODE_UNASSIGNED\020\366\003\022\037\n\032MRC_GIFTCODE"
  "_WRONG_CHANNEL\020\367\003\022\034\n\027MRC_GIFTCODE_WRONG_"
  "AREA\020\370\003\022\031\n\024MRC_GIFTCODE_NO_MORE\020\371\003b\006prot"
  "o3"
  ;
static ::_pbi::once_flag descriptor_table_symphony_2fproto_2fmsg_5fret_5fcode_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_symphony_2fproto_2fmsg_5fret_5fcode_2eproto = {
    false, false, 1482, descriptor_table_protodef_symphony_2fproto_2fmsg_5fret_5fcode_2eproto,
    "symphony/proto/msg_ret_code.proto",
    &descriptor_table_symphony_2fproto_2fmsg_5fret_5fcode_2eproto_once, nullptr, 0, 0,
    schemas, file_default_instances, TableStruct_symphony_2fproto_2fmsg_5fret_5fcode_2eproto::offsets,
    nullptr, file_level_enum_descriptors_symphony_2fproto_2fmsg_5fret_5fcode_2eproto,
    file_level_service_descriptors_symphony_2fproto_2fmsg_5fret_5fcode_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_symphony_2fproto_2fmsg_5fret_5fcode_2eproto_getter() {
  return &descriptor_table_symphony_2fproto_2fmsg_5fret_5fcode_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_symphony_2fproto_2fmsg_5fret_5fcode_2eproto(&descriptor_table_symphony_2fproto_2fmsg_5fret_5fcode_2eproto);
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* MessageRetCode_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_symphony_2fproto_2fmsg_5fret_5fcode_2eproto);
  return file_level_enum_descriptors_symphony_2fproto_2fmsg_5fret_5fcode_2eproto[0];
}
bool MessageRetCode_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 100:
    case 101:
    case 102:
    case 103:
    case 104:
    case 105:
    case 106:
    case 107:
    case 108:
    case 109:
    case 110:
    case 111:
    case 112:
    case 113:
    case 114:
    case 200:
    case 201:
    case 202:
    case 203:
    case 204:
    case 205:
    case 206:
    case 207:
    case 208:
    case 300:
    case 301:
    case 302:
    case 303:
    case 304:
    case 305:
    case 306:
    case 308:
    case 309:
    case 310:
    case 311:
    case 312:
    case 313:
    case 314:
    case 315:
    case 316:
    case 317:
    case 401:
    case 402:
    case 403:
    case 500:
    case 501:
    case 502:
    case 503:
    case 504:
    case 505:
      return true;
    default:
      return false;
  }
}


// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
