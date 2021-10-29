
<p align="center">
  <img src="https://github.com/cppmf/artwork/raw/master/banner/Version.cmake/Version.png" height="100" />
</p>

<p align="center">
  CMake module to easily generate version.h file
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
  VERSION 1.0.0
)

# then call ProjectVersion function
ProjectVersion(
    # Name of the project
    PROJECT_NAME ${PROJECT_NAME}
    # Description of the project
    PROJECT_DESCRIPTION ${PROJECT_DESCRIPTION}
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
    INPUT_FILE_PATH ${CMAKE_CURRENT_LIST_DIR}/my_version.h.in
    # Use custom file name
    OUTPUT_FILE_NAME ${PROJECT_NAME}_version.h
)
```

## Available parameters

List of available parameters while calling ProjectVersion function

parameter | description
---------|------------
PROJECT_NAME | project name
PROJECT_DESCRIPTION | project description
VERSION_MAJOR | version major
VERSION_MINOR | version minor
VERSION_PATCH | version patch
VERSION_REVISION | revision
VERSION_NAME | version name
INPUT_FILE_PATH | full path to a custom version.h.in file (default: version.h.in)
OUTPUT_FILE_NAME | name of the generated file (default: version.h)

