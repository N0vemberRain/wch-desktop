cmake_minimum_required(VERSION 3.21)

project(wch-desktop LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS
    Widgets
    Protobuf
    Grpc
)

qt_standard_project_setup()

set(BUILD_SHARED_LIBS OFF)

qt_add_protobuf(wch_proto
    PROTO_FILES
        api/auth/v1/auth.proto
        api/msgs/v1/msgs.proto
        api/users/v1/users.proto
        api/chats/v1/chats_types.proto
        api/chats/v1/chats.proto
)

qt_add_grpc(wch_grpc CLIENT
    PROTO_FILES
        api/auth/v1/auth.proto
        api/msgs/v1/msgs.proto
        api/users/v1/users.proto
        api/chats/v1/chats_types.proto
        api/chats/v1/chats.proto
)

target_sources(wch_grpc
  PRIVATE
    api/users/v1/users.proto
    api/chats/v1/chats_types.proto
)

get_target_property(TYPE1 wch_proto TYPE)
message(STATUS "wch_proto type=${TYPE1}")

get_target_property(TYPE2 wch_grpc TYPE)
message(STATUS "wch_grpc type=${TYPE2}")

target_link_libraries(wch_grpc PUBLIC wch_proto)

add_subdirectory(src)