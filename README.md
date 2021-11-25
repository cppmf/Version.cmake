
<p align="center">
  <img src="https://github.com/cppmf/artwork/raw/master/banner/Version.cmake/Version.png" height="100" />
</p>

<p align="center">
  CMake module to easily generate version.h and version.rc file
</p>

---

## Usage
The easiest way to use [Version.cmake](https://github.com/cppmf/Version.cmake) is by adding [GetCPM.cmake](https://github.com/cppmf/GetCPM.cmake) to your project.

First add GetCPM.cmake module :

```bash
mkdir cmake
wget -O cmake/GetCPM.cmake https://raw.githubusercontent.com/cppmf/GetCPM.cmake/master/GetCPM.cmake
```

Then add the following lines to the project's `CMakeLists.txt`.


```bash
# include CPM.cmake module
include(cmake/GetCPM.cmake)

# add Version.cmake
CPMAddPackage(
  NAME Version.cmake
  GITHUB_REPOSITORY cppmf/Version.cmake
  VERSION 2.0.0
)

# then call ProjectVersion function
generate_version_header(${PROJECT_NAME}
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
```