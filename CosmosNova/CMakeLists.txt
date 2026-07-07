#﻿
project(Cosmos VERSION 0.1)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/Cosmos/*.cpp CMAKE_CONFIGURE_DEPENDS)
add_library(${PROJECT_NAME} SHARED ${SRC_FILES})

set_target_properties(Cosmos PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
find_package(OpenGL REQUIRED)

target_include_directories(${PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/vendors/glad
	${CMAKE_SOURCE_DIR}/vendors/stb
)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw glm spdlog::spdlog assimp OpenGL::GL)
target_precompile_headers(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Cosmos/CosmosBase.h)