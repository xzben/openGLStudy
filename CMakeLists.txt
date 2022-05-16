cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

#工程名
project(OpenGLStudy VERSION 0.1.0)

#设置 c++ 版本未 c++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BUILD_SHARED_LIBS OFF)

add_subdirectory(3rd)

set(ENGINE_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_INSTALL_PREFIX "${ENGINE_ROOT_DIR}/runtime")
set(BINARY_ROOT_DIR "${CMAKE_INSTALL_PREFIX}/")
set(RUNTIME_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source/engine/")

set(BUILD_RESOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source/editor/resources/")

add_subdirectory(source)