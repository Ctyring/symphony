cmake_miniMum_required(VERSION 3.0)

project(symphony)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include (cmake/utils.cmake)
set(CMAKE_VERBOSE_MAKEFILE ON)

# 指定编译选项
# -rdynamic 将所有符号加入符号表，便于使用dlopen或者backtrace追踪到符号
# -Werror 不区分警告和错误，遇到任何警告都停止编译
# -Wall 开启大部分警告提示
# -Wno-unused-funtion 不要警告未使用函数
# -Wno-deprecated 不要警告过时特性
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -rdynamic -O2 -fPIC -ggdb -std=c++11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined -Wno-deprecated-declarations")
set(CMAKE_C_FLAGS "$ENV{CXXFLAGS} -rdynamic -O2 -fPIC -ggdb -std=c11 -Wall -Wno-deprecated -Werror -Wno-unused-function -Wno-builtin-macro-redefined -Wno-deprecated-declarations")

include_directories(.)
include_directories(/yaml-cpp/include)
include_directories(/usr/local/include)
link_directories(/yaml-cpp/lib)
link_directories(/root/cty/symphony/include)

option(TEST "ON for complile test" ON)

message("***", ${YAMLCPP})

find_package(Protobuf)
if(Protobuf_FOUND)
include_directories(${Protobuf_INCLUDE_DIRS})
endif()

find_package(OpenSSL REQUIRED)
if(OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
endif()

find_package(MySQL REQUIRED)
if(MYSQL_FOUND)
    include_directories(${MYSQL_INCLUDE_DIR})
endif()

find_package(ZLIB REQUIRED)

if(ZLIB_FOUND)
    include_directories(${ZLIB_INCLUDE_DIR})
endif()

set(LIB_SRC 
	symphony/config.cc
	symphony/fiber.cc
	symphony/hook.cc
	symphony/fd_manager.cc
	symphony/iomanager.cc
	symphony/log.cc
	symphony/scheduler.cc
	symphony/timer.cc
	symphony/thread.cc
	symphony/util.cc
	symphony/address.cc
	symphony/socket.cc
	symphony/bytearray.cc
	symphony/http/http.cc
	symphony/http/http_parser.cc
    symphony/http/http11_parser.rl.cc
    symphony/http/httpclient_parser.rl.cc
	symphony/tcp_server.cc
	symphony/streams/socket_stream.cc
    symphony/stream.cc
	symphony/http/http_session.cc
	symphony/http/http_server.cc
	symphony/http/servlet.cc
	symphony/http/http_connection.cc
	symphony/daemon.cc
	symphony/env.cc
	symphony/http/ws_connection.cc
    symphony/http/ws_session.cc
    symphony/http/ws_server.cc
    symphony/http/ws_servlet.cc
	symphony/util/hash_util.cc
	symphony/db/redis.cc
	symphony/application.cc
	symphony/util/time.cc
	symphony/worker.cc
	symphony/mutex.cc
	symphony/module.cc
	symphony/library.cc
	symphony/util/json_util.cc
	symphony/streams/zlib_stream.cc
	symphony/streams/async_socket_stream.cc
	symphony/protocol.cc
    symphony/rock/rock_protocol.cc
	symphony/util/crypto_util.cc
	symphony/rock/rock_server.cc
	symphony/db/sqlite3.cc
	symphony/streams/load_balance.cc
	symphony/rock/rock_stream.cc
	symphony/email/email.cc
	symphony/email/smtp.cc
	symphony/db/mysql.cc
	symphony/http/session_data.cc
	symphony/http/servlets/config_servlet.cc
    symphony/http/servlets/status_servlet.cc
	symphony/ns/name_server_module.cc
    symphony/ns/ns_client.cc
    symphony/ns/ns_protocol.cc
	symphony/ds/bitmap.cc
	symphony/zk_client.cc
	symphony/streams/service_discovery.cc
	symphony/db/fox_thread.cc
	symphony/ds/roaring_bitmap.cc
    symphony/ds/roaring.c
	symphony/ds/util.cc
	symphony/servers/log_server/ls_client.cc
	# symphony/servers/log_server/log_server_module.cc
	)

ragelmaker(symphony/http/http11_parser.rl LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/symphony/http)
ragelmaker(symphony/http/httpclient_parser.rl LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/symphony/http)
ragelmaker(symphony/uri.rl LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR}/symphony)

protobufmaker(symphony/ns/ns_protobuf.proto LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR})
protobufmaker(symphony/proto/log_protobuf.proto LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR})
protobufmaker(symphony/proto/msg_role.proto LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR})
protobufmaker(symphony/proto/msg_login_db.proto LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR})

# protobufmaker(symphony/test.proto LIB_SRC ${CMAKE_CURRENT_SOURCE_DIR})

add_library(symphony SHARED ${LIB_SRC})
force_redefine_file_macro_for_sources(symphony)

find_library(YAMLCPP yaml-cpp)
find_library(PTHREAD pthread)

set(LIBS
        symphony
		dl
        pthread
        yaml-cpp
		${PROTOBUF_LIBRARIES}
		${OPENSSL_LIBRARIES}
		libjsoncpp_static.a
		${ZLIB_LIBRARIES}
		sqlite3
		tinyxml2
		mysqlclient
		mysqlclient_r
		zookeeper_mt
		event
        hiredis_vip
		jemalloc
		)

message("***", ${LIBS})
if(TEST)
symphony_add_executable(test1 "tests/test.cc" symphony "${LIBS}")
symphony_add_executable(test_config "tests/test_config.cc" symphony "${LIBS}")
symphony_add_executable(test_thread "tests/test_thread.cc" symphony "${LIBS}")
symphony_add_executable(test_util "tests/test_util.cc" symphony "${LIBS}")
symphony_add_executable(test_hashmultimap "tests/test_hashmultimap.cc" symphony "${LIBS}")
symphony_add_executable(test_hashmap "tests/test_hashmap.cc" symphony "${LIBS}")
symphony_add_executable(test_dict "tests/test_dict.cc" symphony "${LIBS}")
symphony_add_executable(test_array "tests/test_array.cc" symphony "${LIBS}")
symphony_add_executable(test_fiber "tests/test_fiber.cc" symphony "${LIBS}")
symphony_add_executable(test_scheduler "tests/test_scheduler.cc" symphony "${LIBS}")
symphony_add_executable(test_iomanager "tests/test_iomanager.cc" symphony "${LIBS}")
symphony_add_executable(test_hook "tests/test_hook.cc" symphony "${LIBS}")
symphony_add_executable(test_address "tests/test_address.cc" symphony "${LIBS}")
symphony_add_executable(test_socket "tests/test_socket.cc" symphony "${LIBS}")
symphony_add_executable(test_bytearray "tests/test_bytearray.cc" symphony "${LIBS}")

symphony_add_executable(test_http "tests/test_http.cc" symphony "${LIBS}")
symphony_add_executable(test_http_parser "tests/test_http_parser.cc" symphony "${LIBS}")
symphony_add_executable(test_tcp_server "tests/test_tcp_server.cc" symphony "${LIBS}")
symphony_add_executable(echo_server "examples/echo_server.cc" symphony "${LIBS}")
symphony_add_executable(test_http_server "tests/test_http_server.cc" symphony "${LIBS}")
# symphony_add_executable(test_http_connection "tests/test_http_connection.cc" symphony "${LIBS}")
symphony_add_executable(test_uri "tests/test_uri.cc" symphony "${LIBS}")
symphony_add_executable(my_http_server "samples/my_http_server.cc" symphony "${LIBS}")
symphony_add_executable(test_daemon "tests/test_daemon.cc" symphony "${LIBS}")
symphony_add_executable(test_env "tests/test_env.cc" symphony "${LIBS}")
symphony_add_executable(test_ws_server "tests/test_ws_server.cc" symphony "${LIBS}")
symphony_add_executable(test_ws_client "tests/test_ws_client.cc" symphony "${LIBS}")
symphony_add_executable(test_application "tests/test_application.cc" symphony "${LIBS}")

symphony_add_executable(test_http_connection "tests/test_http_connection.cc" symphony "${LIBS}")
symphony_add_executable(test_lru "tests/test_lru.cc" symphony "${LIBS}")
symphony_add_executable(test_timed_cache "tests/test_timed_cache.cc" symphony "${LIBS}")
symphony_add_executable(test_timed_lru_cache "tests/test_timed_lru_cache.cc" symphony "${LIBS}")
symphony_add_executable(test_zlib_stream "tests/test_zlib_stream.cc" symphony "${LIBS}")

symphony_add_executable(test_crypto "tests/test_crypto.cc" symphony "${LIBS}")

symphony_add_executable(test_sqlite3 "tests/test_sqlite3.cc" symphony "${LIBS}")
symphony_add_executable(test_rock "tests/test_rock.cc" symphony "${LIBS}")
symphony_add_executable(test_email "tests/test_email.cc" symphony "${LIBS}")
symphony_add_executable(test_mysql "tests/test_mysql.cc" symphony "${LIBS}")
symphony_add_executable(test_log_server "tests/test_logserver.cc" symphony "${LIBS}")

set(ORM_SRCS
    symphony/orm/table.cc
    symphony/orm/column.cc
    symphony/orm/index.cc
    symphony/orm/orm.cc
    symphony/orm/util.cc
    )
symphony_add_executable(orm "${ORM_SRCS}" symphony "${LIBS}")

add_library(test_module SHARED tests/test_module.cc)

symphony_add_executable(bin_symphony "symphony/main.cc" symphony "${LIBS}")
set_target_properties(bin_symphony PROPERTIES OUTPUT_NAME "symphony")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/orm_out)
set(OLIBS ${LIBS})
set(OLIBS ${OLIBS} orm_data)
symphony_add_executable(test_orm "tests/test_orm.cc" orm_data "${OLIBS}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/orm_out)
set(LS_SRCS
	symphony/servers/log_server/account_create_info.cc
	symphony/servers/log_server/account_login_info.cc
	symphony/servers/log_server/role_chat_info.cc
	symphony/servers/log_server/role_create_info.cc
	symphony/servers/log_server/role_login_info.cc
	symphony/servers/log_server/role_logout_info.cc
	symphony/servers/log_server/log_server_module.cc
)
add_library(log_server SHARED ${LS_SRCS})

symphony_add_executable(test_nameserver "tests/test_nameserver.cc" symphony "${LIBS}")
symphony_add_executable(test_bitmap "tests/test_bitmap.cc" symphony "${LIBS}")
endif()
symphony_add_executable(test_zookeeper "tests/test_zookeeper.cc" symphony "${LIBS}")
symphony_add_executable(test_service_discovery "tests/test_service_discovery.cc" symphony "${LIBS}")

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)