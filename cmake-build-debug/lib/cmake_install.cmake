# Install script for directory: /home/neo/Code/WAGASCI/WagasciMonteCarlo/lib

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
  foreach(file
      "$ENV{DESTDIR}/tmp/WAGASCI/lib/wagasci/b2/libB2MC.so.0.2.0"
      "$ENV{DESTDIR}/tmp/WAGASCI/lib/wagasci/b2/libB2MC.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHECK
           FILE "${file}"
           RPATH "/tmp/WAGASCI/lib/wagasci/b2:/home/neo/Programs/ROOT/v6-22-02/lib:/home/neo/Programs/ROOT/current/lib")
    endif()
  endforeach()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/tmp/WAGASCI/lib/wagasci/b2/libB2MC.so.0.2.0;/tmp/WAGASCI/lib/wagasci/b2/libB2MC.so.0")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/tmp/WAGASCI/lib/wagasci/b2" TYPE SHARED_LIBRARY FILES
    "/home/neo/Code/WAGASCI/WagasciMonteCarlo/cmake-build-debug/lib/libB2MC.so.0.2.0"
    "/home/neo/Code/WAGASCI/WagasciMonteCarlo/cmake-build-debug/lib/libB2MC.so.0"
    )
  foreach(file
      "$ENV{DESTDIR}/tmp/WAGASCI/lib/wagasci/b2/libB2MC.so.0.2.0"
      "$ENV{DESTDIR}/tmp/WAGASCI/lib/wagasci/b2/libB2MC.so.0"
      )
    if(EXISTS "${file}" AND
       NOT IS_SYMLINK "${file}")
      file(RPATH_CHANGE
           FILE "${file}"
           OLD_RPATH "/home/neo/Programs/ROOT/v6-22-02/lib:/home/neo/Programs/ROOT/current/lib::::::::::::::::::::::::::::"
           NEW_RPATH "/tmp/WAGASCI/lib/wagasci/b2:/home/neo/Programs/ROOT/v6-22-02/lib:/home/neo/Programs/ROOT/current/lib")
      if(CMAKE_INSTALL_DO_STRIP)
        execute_process(COMMAND "/usr/bin/strip" "${file}")
      endif()
    endif()
  endforeach()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/tmp/WAGASCI/lib/wagasci/b2/libB2MC.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/tmp/WAGASCI/lib/wagasci/b2/libB2MC.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/tmp/WAGASCI/lib/wagasci/b2/libB2MC.so"
         RPATH "/tmp/WAGASCI/lib/wagasci/b2:/home/neo/Programs/ROOT/v6-22-02/lib:/home/neo/Programs/ROOT/current/lib")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/tmp/WAGASCI/lib/wagasci/b2/libB2MC.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/tmp/WAGASCI/lib/wagasci/b2" TYPE SHARED_LIBRARY FILES "/home/neo/Code/WAGASCI/WagasciMonteCarlo/cmake-build-debug/lib/libB2MC.so")
  if(EXISTS "$ENV{DESTDIR}/tmp/WAGASCI/lib/wagasci/b2/libB2MC.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/tmp/WAGASCI/lib/wagasci/b2/libB2MC.so")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}/tmp/WAGASCI/lib/wagasci/b2/libB2MC.so"
         OLD_RPATH "/home/neo/Programs/ROOT/v6-22-02/lib:/home/neo/Programs/ROOT/current/lib::::::::::::::::::::::::::::"
         NEW_RPATH "/tmp/WAGASCI/lib/wagasci/b2:/home/neo/Programs/ROOT/v6-22-02/lib:/home/neo/Programs/ROOT/current/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/tmp/WAGASCI/lib/wagasci/b2/libB2MC.so")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/tmp/WAGASCI/include/wagasci/b2/B2Enum.hh;/tmp/WAGASCI/include/wagasci/b2/B2Const.hh;/tmp/WAGASCI/include/wagasci/b2/B2HitSummary.hh;/tmp/WAGASCI/include/wagasci/b2/B2ClusterSummary.hh;/tmp/WAGASCI/include/wagasci/b2/B2TrackSummary.hh;/tmp/WAGASCI/include/wagasci/b2/B2VertexSummary.hh;/tmp/WAGASCI/include/wagasci/b2/B2EventSummary.hh;/tmp/WAGASCI/include/wagasci/b2/B2BeamSummary.hh;/tmp/WAGASCI/include/wagasci/b2/B2Measurement.hh;/tmp/WAGASCI/include/wagasci/b2/B2SpillSummary.hh;/tmp/WAGASCI/include/wagasci/b2/B2EmulsionSummary.hh;/tmp/WAGASCI/include/wagasci/b2/B2HitsSet.hh;/tmp/WAGASCI/include/wagasci/b2/IB2Reader.hh;/tmp/WAGASCI/include/wagasci/b2/B2Reader.hh;/tmp/WAGASCI/include/wagasci/b2/B2Writer.hh;/tmp/WAGASCI/include/wagasci/b2/B2Pdg.hh;/tmp/WAGASCI/include/wagasci/b2/B2Dimension.hh;/tmp/WAGASCI/include/wagasci/b2/B2Volume.hh;/tmp/WAGASCI/include/wagasci/b2/B2MagneticField.hh;/tmp/WAGASCI/include/wagasci/b2/B2RefArray.hh;/tmp/WAGASCI/include/wagasci/b2/B2Boundary.hh;/tmp/WAGASCI/include/wagasci/b2/B2Sigma.hh;/tmp/WAGASCI/include/wagasci/b2/B2Dial.hh;/tmp/WAGASCI/include/wagasci/b2/B2DialSigmaKey.hh;/tmp/WAGASCI/include/wagasci/b2/B2DialList.hh;/tmp/WAGASCI/include/wagasci/b2/B2SigmaList.hh;/tmp/WAGASCI/include/wagasci/b2/B2ReaderDecorator.hh;/tmp/WAGASCI/include/wagasci/b2/B2McWeightCalculator.hh")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/tmp/WAGASCI/include/wagasci/b2" TYPE FILE FILES
    "/home/neo/Code/WAGASCI/WagasciMonteCarlo/lib/B2Enum.hh"
    "/home/neo/Code/WAGASCI/WagasciMonteCarlo/lib/B2Const.hh"
    "/home/neo/Code/WAGASCI/WagasciMonteCarlo/lib/B2HitSummary.hh"
    "/home/neo/Code/WAGASCI/WagasciMonteCarlo/lib/B2ClusterSummary.hh"
    "/home/neo/Code/WAGASCI/WagasciMonteCarlo/lib/B2TrackSummary.hh"
    "/home/neo/Code/WAGASCI/WagasciMonteCarlo/lib/B2VertexSummary.hh"
    "/home/neo/Code/WAGASCI/WagasciMonteCarlo/lib/B2EventSummary.hh"
    "/home/neo/Code/WAGASCI/WagasciMonteCarlo/lib/B2BeamSummary.hh"
    "/home/neo/Code/WAGASCI/WagasciMonteCarlo/lib/B2Measurement.hh"
    "/home/neo/Code/WAGASCI/WagasciMonteCarlo/lib/B2SpillSummary.hh"
    "/home/neo/Code/WAGASCI/WagasciMonteCarlo/lib/B2EmulsionSummary.hh"
    "/home/neo/Code/WAGASCI/WagasciMonteCarlo/lib/B2HitsSet.hh"
    "/home/neo/Code/WAGASCI/WagasciMonteCarlo/lib/IB2Reader.hh"
    "/home/neo/Code/WAGASCI/WagasciMonteCarlo/lib/B2Reader.hh"
    "/home/neo/Code/WAGASCI/WagasciMonteCarlo/lib/B2Writer.hh"
    "/home/neo/Code/WAGASCI/WagasciMonteCarlo/lib/B2Pdg.hh"
    "/home/neo/Code/WAGASCI/WagasciMonteCarlo/lib/B2Dimension.hh"
    "/home/neo/Code/WAGASCI/WagasciMonteCarlo/lib/B2Volume.hh"
    "/home/neo/Code/WAGASCI/WagasciMonteCarlo/lib/B2MagneticField.hh"
    "/home/neo/Code/WAGASCI/WagasciMonteCarlo/lib/B2RefArray.hh"
    "/home/neo/Code/WAGASCI/WagasciMonteCarlo/lib/B2Boundary.hh"
    "/home/neo/Code/WAGASCI/WagasciMonteCarlo/lib/B2Sigma.hh"
    "/home/neo/Code/WAGASCI/WagasciMonteCarlo/lib/B2Dial.hh"
    "/home/neo/Code/WAGASCI/WagasciMonteCarlo/lib/B2DialSigmaKey.hh"
    "/home/neo/Code/WAGASCI/WagasciMonteCarlo/lib/B2DialList.hh"
    "/home/neo/Code/WAGASCI/WagasciMonteCarlo/lib/B2SigmaList.hh"
    "/home/neo/Code/WAGASCI/WagasciMonteCarlo/lib/B2ReaderDecorator.hh"
    "/home/neo/Code/WAGASCI/WagasciMonteCarlo/lib/B2McWeightCalculator.hh"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/tmp/WAGASCI/lib/wagasci/b2/libB2MCDict_rdict.pcm")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
file(INSTALL DESTINATION "/tmp/WAGASCI/lib/wagasci/b2" TYPE FILE FILES "/home/neo/Code/WAGASCI/WagasciMonteCarlo/cmake-build-debug/lib/libB2MCDict_rdict.pcm")
endif()

