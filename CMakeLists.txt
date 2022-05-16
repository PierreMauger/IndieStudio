################# CONFIG ##################

cmake_minimum_required(VERSION 3.16)

# Project name
project(plazza_project LANGUAGES CXX)

# Set c++ version
set(CMAKE_CXX_STANDARD 17)

# find packages
find_package(GLEW REQUIRED)

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
  include/Game/
  include/Graphics/
  include/Input/
  include/Loader/
  include/Animation/
)

set(SRC
  src/Packet.cpp
  src/Message.cpp
  src/MessageBus.cpp
  src/Node.cpp
  src/Audio/Audio.cpp
  src/Game/Game.cpp
  src/Graphics/Graphics.cpp
  src/Input/Input.cpp
  src/Loader/Loader.cpp
  src/Animation/Shader.cpp
  src/Animation/Mesh.cpp
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
# target_link_libraries(${EXEC_NAME} PUBLIC ${CMAKE_THREAD_LIBS_INIT})
# find_library(LIBRT rt)
# if(LIBRT)
#    target_link_libraries(${EXEC_NAME} PUBLIC ${LIBRT})
# endif()
target_link_libraries(${EXEC_NAME} PUBLIC raylib)
target_link_libraries(${EXEC_NAME} PUBLIC GLEW)
target_link_libraries(${EXEC_NAME} PUBLIC GL)
################## MISC ###################

add_custom_command(
  TARGET ${EXEC_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_BINARY_DIR}/${EXEC_NAME}
    ${CMAKE_CURRENT_BINARY_DIR}/../${EXEC_NAME}
)
