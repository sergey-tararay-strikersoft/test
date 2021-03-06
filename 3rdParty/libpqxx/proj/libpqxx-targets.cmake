# Generated by CMake

if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" LESS 2.5)
   message(FATAL_ERROR "CMake >= 2.6.0 required")
endif()
cmake_policy(PUSH)
cmake_policy(VERSION 2.6)
#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Protect against multiple inclusion, which would fail when already imported targets are added once more.
set(_targetsDefined)
set(_targetsNotDefined)
set(_expectedTargets)
foreach(_expectedTarget libpqxx::pqxx_shared libpqxx::pqxx_static)
  list(APPEND _expectedTargets ${_expectedTarget})
  if(NOT TARGET ${_expectedTarget})
    list(APPEND _targetsNotDefined ${_expectedTarget})
  endif()
  if(TARGET ${_expectedTarget})
    list(APPEND _targetsDefined ${_expectedTarget})
  endif()
endforeach()
if("${_targetsDefined}" STREQUAL "${_expectedTargets}")
  unset(_targetsDefined)
  unset(_targetsNotDefined)
  unset(_expectedTargets)
  set(CMAKE_IMPORT_FILE_VERSION)
  cmake_policy(POP)
  return()
endif()
if(NOT "${_targetsDefined}" STREQUAL "")
  message(FATAL_ERROR "Some (but not all) targets in this export set were already defined.\nTargets Defined: ${_targetsDefined}\nTargets not yet defined: ${_targetsNotDefined}\n")
endif()
unset(_targetsDefined)
unset(_targetsNotDefined)
unset(_expectedTargets)


# Create imported target libpqxx::pqxx_shared
add_library(libpqxx::pqxx_shared SHARED IMPORTED)

set_target_properties(libpqxx::pqxx_shared PROPERTIES
  INTERFACE_COMPILE_DEFINITIONS "PQXX_SHARED"
  INTERFACE_INCLUDE_DIRECTORIES "D:/dev/work/sandbox/test/3rdParty/libpqxx/include;D:/dev/work/sandbox/test/3rdParty/libpqxx/proj/include"
  INTERFACE_LINK_LIBRARIES "wsock32;ws2_32"
)

# Create imported target libpqxx::pqxx_static
add_library(libpqxx::pqxx_static STATIC IMPORTED)

set_target_properties(libpqxx::pqxx_static PROPERTIES
  INTERFACE_INCLUDE_DIRECTORIES "D:/dev/work/sandbox/test/3rdParty/libpqxx/include;D:/dev/work/sandbox/test/3rdParty/libpqxx/proj/include"
  INTERFACE_LINK_LIBRARIES "C:/Program Files (x86)/PostgreSQL/10/lib/libpq.lib;wsock32;ws2_32"
)

# Import target "libpqxx::pqxx_shared" for configuration "Debug"
set_property(TARGET libpqxx::pqxx_shared APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(libpqxx::pqxx_shared PROPERTIES
  IMPORTED_IMPLIB_DEBUG "D:/dev/work/sandbox/test/3rdParty/libpqxx/proj/src/Debug/pqxx.lib"
  IMPORTED_LOCATION_DEBUG "D:/dev/work/sandbox/test/3rdParty/libpqxx/proj/src/Debug/pqxx.dll"
  )

# Import target "libpqxx::pqxx_static" for configuration "Debug"
set_property(TARGET libpqxx::pqxx_static APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(libpqxx::pqxx_static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "D:/dev/work/sandbox/test/3rdParty/libpqxx/proj/src/Debug/pqxx.lib"
  )

# Import target "libpqxx::pqxx_shared" for configuration "Release"
set_property(TARGET libpqxx::pqxx_shared APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(libpqxx::pqxx_shared PROPERTIES
  IMPORTED_IMPLIB_RELEASE "D:/dev/work/sandbox/test/3rdParty/libpqxx/proj/src/Release/pqxx.lib"
  IMPORTED_LOCATION_RELEASE "D:/dev/work/sandbox/test/3rdParty/libpqxx/proj/src/Release/pqxx.dll"
  )

# Import target "libpqxx::pqxx_static" for configuration "Release"
set_property(TARGET libpqxx::pqxx_static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(libpqxx::pqxx_static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "D:/dev/work/sandbox/test/3rdParty/libpqxx/proj/src/Release/pqxx.lib"
  )

# Import target "libpqxx::pqxx_shared" for configuration "MinSizeRel"
set_property(TARGET libpqxx::pqxx_shared APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(libpqxx::pqxx_shared PROPERTIES
  IMPORTED_IMPLIB_MINSIZEREL "D:/dev/work/sandbox/test/3rdParty/libpqxx/proj/src/MinSizeRel/pqxx.lib"
  IMPORTED_LOCATION_MINSIZEREL "D:/dev/work/sandbox/test/3rdParty/libpqxx/proj/src/MinSizeRel/pqxx.dll"
  )

# Import target "libpqxx::pqxx_static" for configuration "MinSizeRel"
set_property(TARGET libpqxx::pqxx_static APPEND PROPERTY IMPORTED_CONFIGURATIONS MINSIZEREL)
set_target_properties(libpqxx::pqxx_static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_MINSIZEREL "CXX"
  IMPORTED_LOCATION_MINSIZEREL "D:/dev/work/sandbox/test/3rdParty/libpqxx/proj/src/MinSizeRel/pqxx.lib"
  )

# Import target "libpqxx::pqxx_shared" for configuration "RelWithDebInfo"
set_property(TARGET libpqxx::pqxx_shared APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(libpqxx::pqxx_shared PROPERTIES
  IMPORTED_IMPLIB_RELWITHDEBINFO "D:/dev/work/sandbox/test/3rdParty/libpqxx/proj/src/RelWithDebInfo/pqxx.lib"
  IMPORTED_LOCATION_RELWITHDEBINFO "D:/dev/work/sandbox/test/3rdParty/libpqxx/proj/src/RelWithDebInfo/pqxx.dll"
  )

# Import target "libpqxx::pqxx_static" for configuration "RelWithDebInfo"
set_property(TARGET libpqxx::pqxx_static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(libpqxx::pqxx_static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELWITHDEBINFO "CXX"
  IMPORTED_LOCATION_RELWITHDEBINFO "D:/dev/work/sandbox/test/3rdParty/libpqxx/proj/src/RelWithDebInfo/pqxx.lib"
  )

# This file does not depend on other imported targets which have
# been exported from the same project but in a separate export set.

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
cmake_policy(POP)
