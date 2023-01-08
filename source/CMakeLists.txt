set(THIRD_LIB_DIR "${ENGINE_ROOT_DIR}/3rd")
set(THIRD_SOURCE_DIR "${ENGINE_ROOT_DIR}/3rdlib")
set(ENGINE_ASSETS_DIR "${ENGINE_ROOT_DIR}/assets")
set(ENGINE_SCHEMA_DIR "${ENGINE_ROOT_DIR}/schema")

set(APP_COMMON_INCLUDE 	${THIRD_SOURCE_DIR}/glm/
 	${RUNTIME_SOURCE_DIR}/
	${THIRD_SOURCE_DIR}/glad/include/
	${CMAKE_CURRENT_SOURCE_DIR}/source/
	${THIRD_LIB_DIR}/jsoncpp/include/ 
)

add_subdirectory(editor)
add_subdirectory(engine)
#add_subdirectory(game)
add_subdirectory(test)