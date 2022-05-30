################# CONFIG ##################

#set cmake version required
cmake_minimum_required(VERSION 3.16)

#create project with name, language and version
project(IndieStudio LANGUAGES CXX VERSION 1)

#set c++ version, flags and other important variables
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fexceptions")
if (WIN32)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /EHsc")
endif (WIN32)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(DirectX_D3DX9_LIBRARY "")

#add some color
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options(-fdiagnostics-color=always)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options(-fcolor-diagnostics)
endif()

################## BUILD ##################

#set result executable (target) name
set(EXEC_NAME
  bomberman
)

#fetch include directories
set(INC
  include/
  include/Communication/
  include/Audio/
  include/Core/
  include/Graphics/
  include/Input/
  include/Loader/
  include/Animation/
  include/Scene/
  include/GraphicObject/
)

#fetch source files
set(SRC
  src/Communication/Packet.cpp
  src/Communication/Message.cpp
  src/Communication/MessageBus.cpp
  src/Communication/Node.cpp
  src/PlayerConfig.cpp
  src/Camera.cpp
  src/mappings.cpp
  src/GameObject.cpp
  src/GraphicObject/GraphicObject.cpp
  src/GraphicObject/ModelObj.cpp
  src/GraphicObject/AnimatedModelObj.cpp
  src/GraphicObject/RectangleObj.cpp
  src/GraphicObject/SpriteObj.cpp
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

#fetch libraries
find_package(assimp REQUIRED)
find_package(glew REQUIRED)
find_package(glm REQUIRED)
find_package(OpenGL REQUIRED)
find_package(raylib REQUIRED)

#set includes
include_directories(${INC} ${glew_SOURCE_DIR}/include)

#set source files
add_executable(${EXEC_NAME}
  ${SRC}
  src/main.cpp
)

#set libraries
target_link_libraries(${EXEC_NAME} PUBLIC assimp)
target_link_libraries(${EXEC_NAME} PUBLIC glew)
target_link_libraries(${EXEC_NAME} PUBLIC glm)
target_link_libraries(${EXEC_NAME} PUBLIC raylib)

################## POST BUILD ##################

#copy executable and its dlls to root for resources (only on windows)
if(WIN32)
  add_custom_command(
    TARGET ${EXEC_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/${EXEC_NAME}.exe ${CMAKE_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/_deps/assimp-build/bin/assimp-vc143-mtd.dll ${CMAKE_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/bin/glew32d.dll ${CMAKE_SOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/_deps/raylib-build/raylib/raylibd.dll ${CMAKE_SOURCE_DIR}
  )
else()
  add_custom_command(
    TARGET ${EXEC_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/${EXEC_NAME} ${CMAKE_SOURCE_DIR}
  )
endif()
