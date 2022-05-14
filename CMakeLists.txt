#工程名
project(OpenGLStudy)

add_subdirectory(3rd)

#设置 c++ 版本未 c++17
set(CMAKE_CXX_STANDARD 17)
#设置编译的运行程序输出路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/runtime)

#add_definitions("-Wall -lpthread -g")  

#头文件包含目录
INCLUDE_DIRECTORIES(
3rd/glfw/include/
3rd/stb/
3rdlib/glad/include/
3rdlib/glfw/include
3rdlib/glfw/src
3rdlib/glm
source
source/game
source/engine
)

#源代码目录
AUX_SOURCE_DIRECTORY(source DIR_SRCS)

#设置链接的动态库搜索路径
link_directories(
)

#设置要动态链接的动态库
SET(LIBRARIES
)

# set output binary path  
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})  

#找出所有的源代码文件
file(GLOB_RECURSE HEADER_FILES "source/*.h")
file(GLOB_RECURSE SOURCE_FILES "source/*.cpp")
#设置源文件按路径树状格式展示
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES})

#设置工程的所有编译文件
ADD_EXECUTABLE(${PROJECT_NAME} 
${HEADER_FILES}
${SOURCE_FILES}
3rdlib/glad/src/glad.c
Resources/icon/icon.rc
)

#设置项目未默认启动工程
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

#设置链接的库
TARGET_LINK_LIBRARIES(${PROJECT_NAME} 
glfw  
opengl32
${LIBRARIES})