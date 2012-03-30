
# Copyright (c) 2012 Daniel Nachbaur <daniel.nachbaur@epfl.ch>

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project(codash)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake)
list(APPEND CMAKE_PREFIX_PATH ${SystemDrive}:/cygwin/bin)

set(VERSION_MAJOR "0")
set(VERSION_MINOR "1")
set(VERSION_PATCH "0")

set(VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH})
if(VERSION_MINOR VERSION_LESS 10)
  set(VERSION_ABI ${VERSION_MAJOR}0${VERSION_MINOR})
else()
  set(VERSION_ABI ${VERSION_MAJOR}${VERSION_MINOR})
endif()

enable_testing()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT AND NOT MSVC)
  set(CMAKE_INSTALL_PREFIX "/usr" CACHE PATH "codash install prefix" FORCE)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(MSVC)
  option(Boost_USE_STATIC_LIBS "Use boost static libs" ON)
endif()
if(BOOST_ROOT)
  set(Boost_NO_SYSTEM_PATHS TRUE)
endif()
find_package(Boost 1.41 REQUIRED serialization)
link_directories(${Boost_LIBRARY_DIRS})
add_definitions(-DBOOST_ALL_NO_LIB) # Don't use 'pragma lib' on Windows

find_package(DASH 0.1.0 REQUIRED)
find_package(Collage 0.5.0 REQUIRED)
find_package(Lunchbox 0.9.0 REQUIRED)

include_directories(BEFORE ${codash_SOURCE_DIR} ${CMAKE_BINARY_DIR})
include_directories( ${Boost_INCLUDE_DIRS}
                     ${COLLAGE_INCLUDE_DIRS}
                     ${DASH_INCLUDE_DIRS}
                     ${LUNCHBOX_INCLUDE_DIRS})

if(CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Winvalid-pch -Wnon-virtual-dtor -Wsign-promo -Wshadow -Winit-self -Wno-unknown-pragmas -Wno-unused-parameter -Wno-write-strings")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wuninitialized")
  if(NOT WIN32 AND NOT XCODE_VERSION)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
  endif()
endif(CMAKE_COMPILER_IS_GNUCXX)

if(LINUX)
  add_definitions(-fPIC) # 64bit Linux wants this
endif(LINUX)

if(APPLE)
  set(CMAKE_OSX_ARCHITECTURES "i386;x86_64")
endif(APPLE)

function(INSTALL_SYMLINK FROM TO WHERE)
  install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${FROM} ${TO} WORKING_DIRECTORY \$ENV{DESTDIR}\${CMAKE_INSTALL_PREFIX}/${WHERE})" )
endfunction()

add_subdirectory(codash)
add_subdirectory(tests)

include(CTest)
add_custom_target(package COMMENT "Packaging not done yet")
# include(CPackConfig)