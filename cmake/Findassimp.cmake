CMAKE_MINIMUM_REQUIRED(VERSION 3.11)
if (NOT assimp_FOUND)
	INCLUDE(FetchContent)
	FetchContent_Declare(assimp URL https://github.com/assimp/assimp/archive/refs/tags/v5.2.4.tar.gz)
	FetchContent_GetProperties(assimp)
	if (NOT assimp_POPULATED)
		SET(FETCHCONTENT_QUIET NO)
		FetchContent_Populate(assimp)
		SET(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
		ADD_SUBDIRECTORY(${assimp_SOURCE_DIR} ${assimp_BINARY_DIR})
		SET(assimp_FOUND TRUE)
	endif()
endif()
