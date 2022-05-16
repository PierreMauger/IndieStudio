# Usage:
# FIND_PACKAGE(glew REQUIRED)
# [...]
# TARGET_LINK_LIBRARIES(target_name glew)

CMAKE_MINIMUM_REQUIRED(VERSION 3.11)
if (NOT glew_FOUND)
	INCLUDE(FetchContent)
	FetchContent_Declare(glew URL https://github.com/nigels-com/glew/archive/refs/tags/glew-2.2.0.tar.gz)
	FetchContent_GetProperties(glew)
	if (NOT glew_POPULATED)
		SET(FETCHCONTENT_QUIET NO)
		FetchContent_Populate(glew)
		SET(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
		ADD_SUBDIRECTORY(${glew_SOURCE_DIR} ${glew_BINARY_DIR})
		SET(glew_FOUND TRUE)
	endif()
endif()