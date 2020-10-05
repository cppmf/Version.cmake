# ---------------------------------------------------------------------------- #
# CppMF projects are designed to apply modern CMake practice.
# As such, a decent CMake version is used to benefit from all new features.
# ---------------------------------------------------------------------------- #
cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# Add the directory containing the main CMakeLists file
# and declare the output directory
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/.. ${CMAKE_CURRENT_BINARY_DIR}/VersionCmake)

# define project variables
set(PROJECT_NAME test_app)
set(VERSION_MAJOR 10)
set(VERSION_MINOR 2)
set(VERSION_PATCH 64)


# ---------------------------------------------------------------------------- #
# Project
# ---------------------------------------------------------------------------- #
project(
  ${PROJECT_NAME}
  VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
  LANGUAGES CXX
)


# ---------------------------------------------------------------------------- #
# Add target
# ---------------------------------------------------------------------------- #
add_executable(${PROJECT_NAME} main.cpp)


# ---------------------------------------------------------------------------- #
# Generate version file
# ---------------------------------------------------------------------------- #
ProjectVersion(
    # Name of the project
    PROJECT_NAME ${PROJECT_NAME}
    # Major version
    VERSION_MAJOR ${VERSION_MAJOR}
    # Minor version
    VERSION_MINOR ${VERSION_MINOR}
    # Patch version
    VERSION_PATCH ${VERSION_PATCH}
    # Use custom config file
    INPUT_FILE_PATH ${CMAKE_CURRENT_LIST_DIR}/test_version.h.in
    # Use custom file name
    OUTPUT_FILE_NAME ${PROJECT_NAME}_version.h
)
