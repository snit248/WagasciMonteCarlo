################ Generic settings ################

# Be verbose
# set(CMAKE_VERBOSE_MAKEFILE ON)

# Summary of Build types :
# RelWithDebInfo [-O2 –g] (default)
# Debug [-g -O0 -ggdb]
# Release [-O3]

if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "DO NOT BUILD in-tree.")
endif ()

# CMAKE 3.10.2 is the default version in the Ubuntu 18.04 repositories
cmake_minimum_required(VERSION 3.10.2)

# Name of the project
project(WagasciBabyMindMonteCarlo
        DESCRIPTION "WAGASCI-BabyMIND Monte Carlo simulation software"
        LANGUAGES CXX)

# Build type
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Release' as none was specified.")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
            "MinSizeRel" "RelWithDebInfo")
endif ()

# The version number
set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 2)
set(PROJECT_VERSION_PATCH 0)

set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")
add_compile_definitions(VERSION=${PROJECT_VERSION})

# Set default install path
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "/usr/local" CACHE PATH "default install path" FORCE)
endif ()

# install namespace
set(B2_INSTALL_NAMESPACE wagasci/b2)
set(CMAKE_INSTALL_BINDIR ${CMAKE_INSTALL_PREFIX}/bin)
set(CMAKE_INSTALL_LIBDIR ${CMAKE_INSTALL_PREFIX}/lib/${B2_INSTALL_NAMESPACE})
set(CMAKE_INSTALL_INCDIR ${CMAKE_INSTALL_PREFIX}/include/${B2_INSTALL_NAMESPACE})
set(CMAKE_INSTALL_DATADIR ${CMAKE_INSTALL_PREFIX}/etc/${B2_INSTALL_NAMESPACE})
add_definitions(-DINSTALL_DATADIR=${CMAKE_INSTALL_DATADIR})

# Additional include directories for MacOS
if (APPLE)
    include_directories(/usr/local/include)
    include_directories(/opt/local/include)
    link_directories(/usr/local/lib)
    link_directories(/opt/local/lib)
    link_directories(/opt/local/libexec)
endif ()

option(BUILD_TESTS "Build the unit and integration tests" OFF)
option(BUILD_TOOLS "Build the optional tools" OFF)
option(BUILD_EXAMPLES "Build the optional sample programs" OFF)
option(WITH_G4VIS "Enable Geant4 visualization" OFF)
option(WITH_GDML "Enable GDML file creation" OFF)
option(NINJA "Enable NINJA detector simulation" OFF)

################ Find packages ################

# where to look first for cmake modules
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules")

# Geant4
# for a nice description of how to include Geant4 in a CMake project
# refer to this web page: http://www.sixiangguo.net/code/geant4/AppDevelop/apas02.html
find_package(Geant4 REQUIRED OPTIONAL_COMPONENTS ui_tcsh PATHS /opt/local/lib/Geant4/Geant4.10.6)
include(${Geant4_USE_FILE})
message(STATUS "Found Geant4: ${Geant4_INCLUDE_DIRS}")
if (${Geant4_ui_tcsh_FOUND})
    message(STATUS "Found Geant4 UI tcsh: ${Geant4_ui_tcsh_FOUND}")
endif ()

if (${WITH_G4VIS})
    find_package(Geant4 REQUIRED COMPONENTS qt)
    if (${Geant4_qt_FOUND})
        message(STATUS "Found Geant4 QT: ${Geant4_qt_FOUND}")
        add_compile_definitions(WITH_G4VIS=${WITH_G4VIS})
    else()
        message(ERROR "Geant4 QT not found")
    endif ()

endif ()

if (${WITH_GDML})
    find_package(Geant4 REQUIRED COMPONENTS gdml)
    if (${Geant4_gdml_FOUND})
        message(STATUS "Found Geant4 GDML: ${Geant4_gdml_FOUND}")
        add_compile_definitions(WITH_GDML=${WITH_GDML})
    else()
        message(ERROR "Geant4 GDML not found")
    endif ()

endif ()

if (${NINJA})
    message(STATUS "Enable NINJA detector simulation : ${NINJA}")
    add_compile_definitions(NINJA=${NINJA})
endif ()

# ROOT
list(APPEND CMAKE_PREFIX_PATH $ENV{ROOTSYS})
find_package(ROOT 6.18 CONFIG REQUIRED)
include(${ROOT_USE_FILE})
message(STATUS "Found ROOT: ${ROOT_INCLUDE_DIRS}")

# boost program_options, system, filesystem and log are required
set(Boost_USE_STATIC_LIBS OFF)
add_definitions(-DBOOST_TEST_DYN_LINK)
add_definitions(-DBOOST_LOG_DYN_LINK)
find_package(Boost 1.69 COMPONENTS system filesystem program_options unit_test_framework log_setup log REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
if (APPLE)
  set(Boost_LIBRARIES ${Boost_LIBRARIES} Boost::system Boost::filesystem Boost::program_options
          Boost::unit_test_framework Boost::log_setup Boost::log)
endif ()
message(STATUS "BOOST version : ${Boost_VERSION_MAJOR}.${Boost_VERSION_MINOR}.${Boost_VERSION_PATCH}")
message(STATUS "BOOST library directory : ${Boost_LIBRARY_DIRS}")
message(STATUS "BOOST include directory : ${Boost_INCLUDE_DIRS}")

################ Compiler flags ################

# Set C++11 standard
if (NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 11 CACHE STRING "")
endif ()
if (CMAKE_CXX_STANDARD LESS 11)
    message(WARNING "Incompatible C++ standard ${CMAKE_CXX_STANDARD}. ${PROJECT_NAME} requires C++11")
endif ()

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PLATFORM_INDEPENDENT_CODE ON)
message(STATUS "Compiler ID : ${CMAKE_CXX_COMPILER_ID}")

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=0")
    set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0 -ggdb -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wno-overloaded-virtual -Wno-shadow \
                                            -Wno-deprecated-copy -Wno-unused-parameter -Wno-unused-variable")
endif ()

################ Linker flags ################

set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

################ includes ################

# MC include directory
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

################ Sub Directories ################

add_subdirectory(lib)
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(external)
add_subdirectory(tools)
add_subdirectory(examples)
add_subdirectory(data)
