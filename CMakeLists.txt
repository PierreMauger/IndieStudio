################# CONFIG ##################

cmake_minimum_required(VERSION 3.16)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Project name
project(indie_project LANGUAGES CXX)

# find packages
find_package(GLEW REQUIRED)

# Set c++ version
set(CMAKE_CXX_STANDARD 17)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options(-fdiagnostics-color=always)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options(-fcolor-diagnostics)
endif()

################## BUILD ##################

set(EXEC_NAME
  bomberman
)

set(INC
  include/
  include/Audio/
  include/Core/
  include/Graphics/
  include/Input/
  include/Loader/
  include/Animation/
  include/Scene/
)

set(SRC
  src/Packet.cpp
  src/Message.cpp
  src/MessageBus.cpp
  src/Node.cpp
  src/PlayerConfig.cpp
  src/Camera.cpp
  src/mappings.cpp
  src/Audio/Audio.cpp
  src/Core/Core.cpp
  src/Scene/ConfigScene.cpp
  src/Scene/GameScene.cpp
  src/Scene/MenuScene.cpp
  src/Graphics/Graphics.cpp
  src/Input/Input.cpp
  src/Loader/Loader.cpp
  src/Animation/Shader.cpp
  src/Animation/Mesh.cpp
  src/Animation/Bone.cpp
  src/Animation/Model.cpp
  src/Animation/Animation.cpp
  src/Animation/Animator.cpp
  src/Neo.cpp
)

set(CMAKE_EXE_LINKER_FLAGS -fexceptions)

add_executable(${EXEC_NAME}
  ${SRC}
  src/main.cpp
)

target_include_directories(${EXEC_NAME} PUBLIC
  ${INC}
)

# link with libs
find_package(raylib REQUIRED)
target_link_libraries(${EXEC_NAME} PUBLIC raylib)
target_link_libraries(${EXEC_NAME} PUBLIC GLEW)
target_link_libraries(${EXEC_NAME} PUBLIC assimp)
################## MISC ###################

add_custom_command(
  TARGET ${EXEC_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_BINARY_DIR}/${EXEC_NAME}
    ${CMAKE_CURRENT_BINARY_DIR}/../${EXEC_NAME}
)
