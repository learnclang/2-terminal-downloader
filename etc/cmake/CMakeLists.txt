project(lc-download)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(../../src/c SRC_LIST)

set(LIBCURL_VERSION 7.37.0-1 
	CACHE STRING "Version of libcurl to use - must be in our lib directory")
set(LIBCURL_INSTALL_DIRECTORY ""
	CACHE PATH "The location of the library installation directory, contains 'lib' and 'include' dirs")

if(NOT LIBCURL_INSTALL_DIRECTORY)
	if(APPLE)
		set(PLATFORM_DESCRIPTOR osx-${_CURRENT_OSX_VERSION}_${CMAKE_HOST_SYSTEM_PROCESSOR})
	else()
		message(SEND_ERROR "Platform ${CMAKE_SYSTEM} is not yet configured - please adjust CMake configuration")
	endif()
	set(LIBCURL_INSTALL_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../../lib/curl/${LIBCURL_VERSION}/${PLATFORM_DESCRIPTOR})
endif() # handle lib-curl auto-setup

include_directories(${LIBCURL_INSTALL_DIRECTORY}/include)
link_directories(${LIBCURL_INSTALL_DIRECTORY}/lib)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} curl)

