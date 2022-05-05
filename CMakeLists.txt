#工程名
set(PROJECT_NAME OpenGLStudy)
project(${PROJECT_NAME})

add_subdirectory(3rd/glfw/)
set(CMAKE_CXX_STANDARD 17)
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

link_directories(
${PROJECT_BINARY_DIR}/3rd/glfw/src/
)

#set extern libraries
SET(LIBRARIES
glfw3.lib
opengl32.lib
)

# set output binary path  
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)  

file(GLOB_RECURSE HEADER_FILES "source/*.h")
file(GLOB_RECURSE SOURCE_FILES "source/*.cpp")

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADER_FILES} ${SOURCE_FILES})

#add executable file
ADD_EXECUTABLE(${PROJECT_NAME} 
${HEADER_FILES}
${SOURCE_FILES}
3rdlib/glad/src/glad.c
)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${LIBRARIES})