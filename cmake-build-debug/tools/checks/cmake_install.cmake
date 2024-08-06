# Install script for directory: /home/neo/Code/WAGASCI/WagasciMonteCarlo/tools/checks

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/tmp/WAGASCI")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/tmp/WAGASCI/bin/check_timing" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/tmp/WAGASCI/bin/check_timing")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/tmp/WAGASCI/bin/check_timing"
         RPATH "/tmp/WAGASCI/lib/wagasci/b2:/home/neo/Programs/ROOT/v6-22-02/lib:/home/neo/Programs/ROOT/current/lib")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/tmp/WAGASCI/bin/check_timing")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/tmp/WAGASCI/bin" TYPE EXECUTABLE FILES "/home/neo/Code/WAGASCI/WagasciMonteCarlo/cmake-build-debug/tools/checks/check_timing")
  if(EXISTS "$ENV{DESTDIR}/tmp/WAGASCI/bin/check_timing" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/tmp/WAGASCI/bin/check_timing")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/tmp/WAGASCI/bin/check_timing"
         OLD_RPATH "/home/neo/Programs/ROOT/v6-22-02/lib:/home/neo/Programs/ROOT/current/lib:/home/neo/Code/WAGASCI/WagasciMonteCarlo/cmake-build-debug/lib:"
         NEW_RPATH "/tmp/WAGASCI/lib/wagasci/b2:/home/neo/Programs/ROOT/v6-22-02/lib:/home/neo/Programs/ROOT/current/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/tmp/WAGASCI/bin/check_timing")
    endif()
  endif()
endif()

