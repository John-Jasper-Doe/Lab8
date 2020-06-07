# Root CMake file for TIMUS Project
#
# Copyright John Doe 2020
# Distributed under the OSI-approved BSD 3-Clause License. See accompanying
# file LICENSE.txt or https://opensource.org/licenses/BSD-3-Clause for details.

cmake_minimum_required(VERSION 3.8)

# Setting name for this project.
set(PROJECT_NAME timus)

# Adding a path with "cmake" modules to the system search paths.
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Setting up a project version.
include(version)
if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
  set(TIMUS_PATCH ENV{TRAVIS_BUILD_NUMBER})
endif ()
set(TIMUS_VERSION ${TIMUS_MAJOR}.${TIMUS_MINOR}.${TIMUS_PATCH})

# Setting up a project.
include(print)
include(function)

project(${PROJECT_NAME} CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Setting options on project
option(CLANG_FORMAT "Enable clang-format target" ON)

if(CLANG_FORMAT)
  include(clang-format)
endif()

# Added source directory
add_subdirectory(src)


