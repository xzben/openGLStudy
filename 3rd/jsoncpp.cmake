set(jsoncpp_SOURCE_DIR_ ${CMAKE_CURRENT_SOURCE_DIR}/jsoncpp/src/lib_json)
set(jsoncpp_HEAD_DIR_ ${CMAKE_CURRENT_SOURCE_DIR}/jsoncpp/include/json)

file(GLOB jsoncpp_sources CONFIGURE_DEPENDS  "${jsoncpp_SOURCE_DIR_}/*")

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/jsoncpp/include)
add_library(jsoncpp STATIC ${jsoncpp_sources} )

target_include_directories(jsoncpp PUBLIC $<BUILD_INTERFACE:${jsoncpp_SOURCE_DIR_}>)
target_include_directories(jsoncpp PUBLIC $<BUILD_INTERFACE:${jsoncpp_HEAD_DIR_}>)