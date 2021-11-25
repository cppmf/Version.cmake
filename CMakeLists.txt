# -------------------------------------------------------------------------------------------------------------------- #
#
# Copyright (c) 2020 C++ Modern Framework
#
# -------------------------------------------------------------------------------------------------------------------- #

#[=====================================================================================================================[

GenerateVersionHeader
---------------------

Function to generation version file to be included a library and application

This module provides the function ``GENERATE_VERSION_HEADER()``.

The ``GENERATE_VERSION_HEADER`` function can be used to generate a file
which contains macros definition of the current version of the target.

   GENERATE_VERSION_HEADER( TARGET
             [BASE_NAME <base_name>]
             [DESCRIPTION <description>]
             [AUTHOR_ORGANIZATION <author_organization>]
             [AUTHOR_DOMAIN <author_domain>]
             [AUTHOR_MAINTAINER <description>]
             [VERSION_MAJOR <version_major>]
             [VERSION_MINOR <version_minor>]
             [VERSION_PATCH <version_patch>]
             [VERSION_REVISION <version_revision>]
             [VERSION_NAME <version_name>]
             [VERSION_STRING <version_string>]
             [VERSION_FILE <version_file>]
             [VERSION_FILE_NAME <version_file_name>]
             [VERSION_RC_FILE <version_rc_file>]
             [VERSION_RC_FILE_NAME <version_rc_file_name>]
             [INCLUDE_GUARD_NAME <include_guard_name>]
   )

By default ``GENERATE_VERSION_HEADER()`` generates a file name determined by
the name of the target. The simplest case will be equivalent to:

   generate_version_header(somelib)
   install(TARGETS somelib DESTINATION ${LIBRARY_INSTALL_DIR})
   install(FILES
    someclass.h
    ${PROJECT_BINARY_DIR}/somelib_version.h DESTINATION ${INCLUDE_INSTALL_DIR}
   )

And in the ABI header files:

   #include "somelib_version.h"

The CMake fragment will generate a file in the ``${CMAKE_CURRENT_BINARY_DIR}``
called ``somelib_version.h``

The ``BASE_NAME`` argument can be used to override the file name:

   add_library(somelib someclass.cpp)
   generate_version_header(somelib
     BASE_NAME other_name
   )

Generates a file called ``other_name_version.h``

#]=====================================================================================================================]


# Root path of this file. It will be used to find the location of version.h.in
get_filename_component(_GENERATE_VERSION_HEADER_MODULE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)


macro(_DO_GENERATE_VERSION_HEADER TARGET)

  # Option overrides
  set(options DEFINE_NO_DEPRECATED)
  set(oneValueArgs BASE_NAME DESCRIPTION
          AUTHOR_ORGANIZATION AUTHOR_DOMAIN AUTHOR_MAINTAINER
          VERSION_MAJOR VERSION_MINOR VERSION_PATCH VERSION_REVISION VERSION_NAME VERSION_STRING
          VERSION_FILE VERSION_FILE_NAME
          VERSION_RC_FILE VERSION_RC_FILE_NAME
          INCLUDE_GUARD_NAME)
  set(multiValueArgs)

  # Parsing function arguments
  cmake_parse_arguments(_GEV "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  # Check for unparsed arguments
  if(_GEV_UNPARSED_ARGUMENTS)
    message(FATAL_ERROR "Unknown keywords given to GENERATE_VERSION_HEADER(): \"${_GEV_UNPARSED_ARGUMENTS}\"")
  endif()

  # Get the target type
  get_target_property(target_type ${TARGET} TYPE)

  # Default options
  set(DESCRIPTION ${_GEV_DESCRIPTION})
  set(AUTHOR_ORGANIZATION ${_GEV_AUTHOR_ORGANIZATION})
  set(AUTHOR_DOMAIN ${_GEV_AUTHOR_DOMAIN})
  set(AUTHOR_MAINTAINER ${_GEV_AUTHOR_MAINTAINER})
  set(VERSION_MAJOR 0)
  set(VERSION_MINOR 0)
  set(VERSION_PATCH 0)
  set(VERSION_REVISION 0)

  # Define base name
  set(BASE_NAME "${TARGET}")

  if(_GEV_BASE_NAME)
    set(BASE_NAME ${_GEV_BASE_NAME})
  endif()

  string(TOUPPER ${BASE_NAME} BASE_NAME_UPPER)
  string(TOLOWER ${BASE_NAME} BASE_NAME_LOWER)

  # Default files
  set(VERSION_FILE "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/version.h.in")
  set(VERSION_RC_FILE "${CMAKE_CURRENT_FUNCTION_LIST_DIR}/version.rc.in")
  set(VERSION_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/${BASE_NAME_LOWER}_version.h")
  set(VERSION_RC_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/${BASE_NAME_LOWER}_version.rc")

  # Version default values
  if(_GEV_VERSION_MAJOR)
    set(VERSION_MAJOR ${_GEV_VERSION_MAJOR})
  endif()
  if(_GEV_VERSION_MINOR)
    set(VERSION_MINOR ${_GEV_VERSION_MINOR})
  endif()
  if(_GEV_VERSION_PATCH)
    set(VERSION_PATCH ${_GEV_VERSION_PATCH})
  endif()
  if(_GEV_VERSION_REVISION)
    set(VERSION_REVISION ${_GEV_VERSION_REVISION})
  endif()

  # Define VERSION_STRING which is used in version.h.in
  if(_GEV_VERSION_STRING)
    set(VERSION_STRING ${_GEV_VERSION_STRING})
  else()
    set(VERSION_STRING "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
  endif()

  # Define VERSION_NAME which is used in version.h.in
  if(_GEV_VERSION_NAME)
    set(VERSION_NAME ${_GEV_VERSION_NAME})
  else()
    set(VERSION_NAME ${VERSION_STRING})
  endif()

  # Define VERSION_FILE
  if(_GEV_VERSION_FILE)
    set(VERSION_FILE ${_GEV_VERSION_FILE})
  endif()

  # Define VERSION_FILE_NAME
  if(_GEV_VERSION_FILE_NAME)
    if(IS_ABSOLUTE ${_GEV_VERSION_FILE_NAME})
      set(VERSION_FILE_NAME ${_GEV_VERSION_FILE_NAME})
    else()
      set(VERSION_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/${_GEV_VERSION_FILE_NAME}")
    endif()
  endif()

  # Define VERSION_RC_FILE
  if(_GEV_VERSION_RC_FILE)
    set(VERSION_RC_FILE ${_GEV_VERSION_RC_FILE})
  endif()

  # Define VERSION_RC_FILE_NAME
  if(_GEV_VERSION_RC_FILE_NAME)
    if(IS_ABSOLUTE ${_GEV_VERSION_RC_FILE_NAME})
      set(VERSION_RC_FILE_NAME ${_GEV_VERSION_RC_FILE_NAME})
    else()
      set(VERSION_RC_FILE_NAME "${CMAKE_CURRENT_BINARY_DIR}/${_GEV_VERSION_RC_FILE_NAME}")
    endif()
  endif()

  # Define INCLUDE_GUARD_NAME which is used in version.h.in
  if(_GEV_INCLUDE_GUARD_NAME)
    set(INCLUDE_GUARD_NAME ${_GEV_INCLUDE_GUARD_NAME})
  else()
    set(INCLUDE_GUARD_NAME "__${BASE_NAME_UPPER}_VERSION_H__")
  endif()
  string(MAKE_C_IDENTIFIER ${INCLUDE_GUARD_NAME} INCLUDE_GUARD_NAME)

  # generate the version file
  configure_file("${VERSION_FILE}" "${VERSION_FILE_NAME}" @ONLY)

  # generate the RC version file
  if(WIN32)
    if(${target_type} STREQUAL "SHARED_LIBRARY" OR ${target_type} STREQUAL "EXECUTABLE")
      if(${target_type} STREQUAL "SHARED_LIBRARY")
        set(TARGET_EXT dll)
      else()
        set(TARGET_EXT exe)
      endif()
      configure_file("${VERSION_RC_FILE}" "${VERSION_RC_FILE_NAME}" @ONLY)
    endif()
  endif()

endmacro()

function(GENERATE_VERSION_HEADER TARGET)
  _do_generate_version_header(${TARGET} ${ARGN})
endfunction()