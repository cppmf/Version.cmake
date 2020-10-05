# ---------------------------------------------------------------------------- #
#
# Copyright (c) 2020 C++ Modern Framework
#
# ---------------------------------------------------------------------------- #


# Set the root path of Version.cmake
# this will be used to find the location of version.h.in
set(VERSION_CMAKE_ROOT_PATH "${CMAKE_CURRENT_LIST_DIR}" CACHE INTERNAL "The path to Version.cmake directory")

# This is the main function to call in project CMakeLists.txt
function(ProjectVersion)

  # Parsing ProjectVersion function arguments
  cmake_parse_arguments(
    "VERSION"
    ""
    "PROJECT_NAME;VERSION_MAJOR;VERSION_MINOR;VERSION_PATCH;INPUT_FILE_PATH;OUTPUT_FILE_NAME;INSTALL_DESTINATION"
    ""
    ${ARGN}
  )

  # define the location where the version file will be generated
  set(VERSION_CMAKE_INCLUDE_DIR ${PROJECT_BINARY_DIR}/VersionCmakeInclude)

  # define the input file to use.
  # if VERSION_INPUT_FILE_PATH is not defined, then it will be set to ${PACKAGE_PROJECT_ROOT_PATH}/version.h.in
  if(NOT DEFINED VERSION_INPUT_FILE_PATH)
    set(VERSION_INPUT_FILE_PATH ${VERSION_CMAKE_ROOT_PATH}/version.h.in)
  endif()

  # define the name of the generated output file
  # if VERSION_OUTPUT_FILE_NAME is not defined, then it will be set to version.h
  if(NOT DEFINED VERSION_OUTPUT_FILE_NAME)
    set(VERSION_OUTPUT_FILE_NAME version.h)
  endif()

  # define the output file path
  set(VERSION_OUTPUT_FILE_PATH ${VERSION_CMAKE_INCLUDE_DIR}/${VERSION_OUTPUT_FILE_NAME})

  # define VERSION_PROJECT_ID which is used in version.h.in
  string(MAKE_C_IDENTIFIER "${VERSION_PROJECT_NAME}" VERSION_PROJECT_ID)
  string(TOUPPER ${VERSION_PROJECT_ID} VERSION_PROJECT_ID)

  # generate the config file
  configure_file(${VERSION_INPUT_FILE_PATH}  ${VERSION_OUTPUT_FILE_PATH}  @ONLY)

  # include the generated file to project target
  # first get the target type to define the scope to use when adding include directory
  get_target_property(target_type ${VERSION_PROJECT_NAME} TYPE)
  if(target_type STREQUAL "INTERFACE_LIBRARY")
    set(SCOPE INTERFACE)
  else()
    set(SCOPE PUBLIC)
  endif()
  # then add the directory to include
  target_include_directories(${VERSION_PROJECT_NAME} ${SCOPE} $<BUILD_INTERFACE:${VERSION_CMAKE_INCLUDE_DIR}>)

   # Specify version file location at install time.
  if(DEFINED VERSION_INSTALL_DESTINATION)
    install(
      DIRECTORY ${VERSION_CMAKE_INCLUDE_DIR}/
      DESTINATION ${VERSION_INSTALL_DESTINATION}
    )
  endif()
endfunction()
