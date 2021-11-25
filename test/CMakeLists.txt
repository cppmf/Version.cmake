# ---------------------------------------------------------------------------- #
# CppMF projects are designed to apply modern CMake practice.
# As such, a decent CMake version is used to benefit from all new features.
#
# Check CMake Release Notes:
#   https://cmake.org/cmake/help/latest/release/3.21.html
# ---------------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.21 FATAL_ERROR)

# Make use of GetCPM.cmake
include(${CMAKE_CURRENT_LIST_DIR}/cmake/GetCPM.cmake)

# Add Version.cmake package
CPMAddPackage(NAME Version.cmake SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

# define project variables
set(PROJECT_NAME TestApp)
set(PROJECT_DESCRIPTION "A test app from Version.cmake")
set(VERSION_MAJOR 3)
set(VERSION_MINOR 2)
set(VERSION_PATCH 12)
set(VERSION_REVISION 0)
set(VERSION_NAME "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH} (${VERSION_REVISION})")


# ---------------------------------------------------------------------------- #
# Project
# ---------------------------------------------------------------------------- #
project(
  ${PROJECT_NAME}
  VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
  DESCRIPTION ${PROJECT_DESCRIPTION}
  LANGUAGES CXX
)


# ---------------------------------------------------------------------------- #
# Add target
# ---------------------------------------------------------------------------- #
add_executable(${PROJECT_NAME} main.cpp)


# ---------------------------------------------------------------------------- #
# Generate version file
# ---------------------------------------------------------------------------- #
generate_version_header(${PROJECT_NAME}
    BASE_NAME App
    # Description of the project
    DESCRIPTION ${PROJECT_DESCRIPTION}
    # Author
    AUTHOR_ORGANIZATION "Cpp Modern Framework"
    # Major version
    VERSION_MAJOR ${VERSION_MAJOR}
    # Minor version
    VERSION_MINOR ${VERSION_MINOR}
    # Patch version
    VERSION_PATCH ${VERSION_PATCH}
    # Revision version
    VERSION_REVISION ${VERSION_REVISION}
    # Version name
    VERSION_NAME ${VERSION_NAME}
    # Use custom config file
    VERSION_FILE ${CMAKE_CURRENT_LIST_DIR}/test_version.h.in
    # Use custom file name
    VERSION_FILE_NAME ${PROJECT_NAME}_version.h
)

# Add version file to the include directories
target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>)

# Add rc file
if(WIN32)
  target_sources(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}_version.rc)
endif()


# ---------------------------------------------------------------------------- #
# Add test
# ---------------------------------------------------------------------------- #
enable_testing()
add_test(NAME test COMMAND ${PROJECT_NAME})
