set(TEST_COMMON_INCLUDE ${THIRD_SOURCE_DIR}/glm/
	${RUNTIME_SOURCE_DIR}/
	${THIRD_SOURCE_DIR}/glad/include/
	${CMAKE_CURRENT_SOURCE_DIR}/source/
	${THIRD_LIB_DIR}/jsoncpp/include/)

set(TEST_RESOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/resources/)

add_subdirectory(source/reflex)
add_subdirectory(source/test)