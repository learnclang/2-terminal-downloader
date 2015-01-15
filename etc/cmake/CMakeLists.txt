project(lc-download)
cmake_minimum_required(VERSION 2.8)
aux_source_directory(../../src/c SRC_LIST)

set(LIBCURL_VERSION 7.37.0-1 
	CACHE STRING "Version of libcurl to use - must be in our lib directory")
set(PLATFORM_ID ""
	CACHE STRING "Platform specifier, like win7-msvc9_x86_64")
set(LIBCURL_INSTALL_DIRECTORY ""
	CACHE PATH "The location of the library installation directory, contains 'lib' and 'include' dirs")

if(NOT LIBCURL_INSTALL_DIRECTORY)
	if(APPLE AND NOT PLATFORM_ID)
		set(PLATFORM_ID osx-${_CURRENT_OSX_VERSION}_${CMAKE_HOST_SYSTEM_PROCESSOR})
	elseif(NOT PLATFORM_ID)
		message(SEND_ERROR "On this platform '${PLATFORM}', please specify the LIBCURL_INSTALL_DIRECTORY or PLATFORM_ID. Configure one of them on the commandline or using cmake-gui")
	endif()
	set(LIBCURL_INSTALL_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/../../lib/curl/${LIBCURL_VERSION}/${PLATFORM_ID})
endif() # handle lib-curl auto-setup

include_directories(${LIBCURL_INSTALL_DIRECTORY}/include)
link_directories(${LIBCURL_INSTALL_DIRECTORY}/lib)
# Yes, we expect curl to be statically compiled - see curl-config.sh for the flags used
add_definitions(-DCURL_STATICLIB)

add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} curl)

# Windows specific libraries
if(WIN32)
	target_link_libraries(${PROJECT_NAME} ws2_32)
endif()

