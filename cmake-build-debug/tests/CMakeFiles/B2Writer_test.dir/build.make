# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/neo/Code/WAGASCI/WagasciMonteCarlo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/neo/Code/WAGASCI/WagasciMonteCarlo/cmake-build-debug

# Include any dependencies generated for this target.
include tests/CMakeFiles/B2Writer_test.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/B2Writer_test.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/B2Writer_test.dir/flags.make

tests/CMakeFiles/B2Writer_test.dir/B2Writer.test.cc.o: tests/CMakeFiles/B2Writer_test.dir/flags.make
tests/CMakeFiles/B2Writer_test.dir/B2Writer.test.cc.o: ../tests/B2Writer.test.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/neo/Code/WAGASCI/WagasciMonteCarlo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object tests/CMakeFiles/B2Writer_test.dir/B2Writer.test.cc.o"
	cd /home/neo/Code/WAGASCI/WagasciMonteCarlo/cmake-build-debug/tests && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/B2Writer_test.dir/B2Writer.test.cc.o -c /home/neo/Code/WAGASCI/WagasciMonteCarlo/tests/B2Writer.test.cc

tests/CMakeFiles/B2Writer_test.dir/B2Writer.test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/B2Writer_test.dir/B2Writer.test.cc.i"
	cd /home/neo/Code/WAGASCI/WagasciMonteCarlo/cmake-build-debug/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/neo/Code/WAGASCI/WagasciMonteCarlo/tests/B2Writer.test.cc > CMakeFiles/B2Writer_test.dir/B2Writer.test.cc.i

tests/CMakeFiles/B2Writer_test.dir/B2Writer.test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/B2Writer_test.dir/B2Writer.test.cc.s"
	cd /home/neo/Code/WAGASCI/WagasciMonteCarlo/cmake-build-debug/tests && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/neo/Code/WAGASCI/WagasciMonteCarlo/tests/B2Writer.test.cc -o CMakeFiles/B2Writer_test.dir/B2Writer.test.cc.s

# Object files for target B2Writer_test
B2Writer_test_OBJECTS = \
"CMakeFiles/B2Writer_test.dir/B2Writer.test.cc.o"

# External object files for target B2Writer_test
B2Writer_test_EXTERNAL_OBJECTS =

tests/B2Writer_test: tests/CMakeFiles/B2Writer_test.dir/B2Writer.test.cc.o
tests/B2Writer_test: tests/CMakeFiles/B2Writer_test.dir/build.make
tests/B2Writer_test: lib/libgtest.a
tests/B2Writer_test: lib/libgmock.a
tests/B2Writer_test: lib/libgtest_main.a
tests/B2Writer_test: tests/libTMP.a
tests/B2Writer_test: lib/libgtest.a
tests/B2Writer_test: /opt/geant4/lib/libG4Tree.so
tests/B2Writer_test: /opt/geant4/lib/libG4GMocren.so
tests/B2Writer_test: /opt/geant4/lib/libG4FR.so
tests/B2Writer_test: /opt/geant4/lib/libG4visHepRep.so
tests/B2Writer_test: /opt/geant4/lib/libG4RayTracer.so
tests/B2Writer_test: /opt/geant4/lib/libG4VRML.so
tests/B2Writer_test: /opt/geant4/lib/libG4vis_management.so
tests/B2Writer_test: /opt/geant4/lib/libG4modeling.so
tests/B2Writer_test: /opt/geant4/lib/libG4interfaces.so
tests/B2Writer_test: /usr/lib/x86_64-linux-gnu/libQt5PrintSupport.so.5.12.8
tests/B2Writer_test: /usr/lib/x86_64-linux-gnu/libQt5Widgets.so.5.12.8
tests/B2Writer_test: /usr/lib/x86_64-linux-gnu/libQt5Gui.so.5.12.8
tests/B2Writer_test: /usr/lib/x86_64-linux-gnu/libQt5Core.so.5.12.8
tests/B2Writer_test: /usr/lib/x86_64-linux-gnu/libXm.so
tests/B2Writer_test: /usr/lib/x86_64-linux-gnu/libXmu.so
tests/B2Writer_test: /usr/lib/x86_64-linux-gnu/libXext.so
tests/B2Writer_test: /usr/lib/x86_64-linux-gnu/libXt.so
tests/B2Writer_test: /usr/lib/x86_64-linux-gnu/libSM.so
tests/B2Writer_test: /usr/lib/x86_64-linux-gnu/libICE.so
tests/B2Writer_test: /usr/lib/x86_64-linux-gnu/libX11.so
tests/B2Writer_test: /opt/geant4/lib/libG4persistency.so
tests/B2Writer_test: /usr/lib/x86_64-linux-gnu/libxerces-c.so
tests/B2Writer_test: /opt/geant4/lib/libG4error_propagation.so
tests/B2Writer_test: /opt/geant4/lib/libG4readout.so
tests/B2Writer_test: /opt/geant4/lib/libG4physicslists.so
tests/B2Writer_test: /opt/geant4/lib/libG4run.so
tests/B2Writer_test: /opt/geant4/lib/libG4event.so
tests/B2Writer_test: /opt/geant4/lib/libG4tracking.so
tests/B2Writer_test: /opt/geant4/lib/libG4parmodels.so
tests/B2Writer_test: /opt/geant4/lib/libG4processes.so
tests/B2Writer_test: /opt/geant4/lib/libG4analysis.so
tests/B2Writer_test: /usr/lib/x86_64-linux-gnu/libz.so
tests/B2Writer_test: /usr/lib/x86_64-linux-gnu/libexpat.so
tests/B2Writer_test: /opt/geant4/lib/libG4digits_hits.so
tests/B2Writer_test: /opt/geant4/lib/libG4track.so
tests/B2Writer_test: /opt/geant4/lib/libG4particles.so
tests/B2Writer_test: /opt/geant4/lib/libG4geometry.so
tests/B2Writer_test: /opt/geant4/lib/libG4materials.so
tests/B2Writer_test: /opt/geant4/lib/libG4graphics_reps.so
tests/B2Writer_test: /opt/geant4/lib/libG4intercoms.so
tests/B2Writer_test: /opt/geant4/lib/libG4global.so
tests/B2Writer_test: /opt/geant4/lib/libG4clhep.so
tests/B2Writer_test: lib/libB2MC.so.0.2.0
tests/B2Writer_test: /home/neo/Programs/ROOT/current/lib/libCore.so
tests/B2Writer_test: /home/neo/Programs/ROOT/current/lib/libImt.so
tests/B2Writer_test: /home/neo/Programs/ROOT/current/lib/libRIO.so
tests/B2Writer_test: /home/neo/Programs/ROOT/current/lib/libNet.so
tests/B2Writer_test: /home/neo/Programs/ROOT/current/lib/libHist.so
tests/B2Writer_test: /home/neo/Programs/ROOT/current/lib/libGraf.so
tests/B2Writer_test: /home/neo/Programs/ROOT/current/lib/libGraf3d.so
tests/B2Writer_test: /home/neo/Programs/ROOT/current/lib/libGpad.so
tests/B2Writer_test: /home/neo/Programs/ROOT/current/lib/libROOTDataFrame.so
tests/B2Writer_test: /home/neo/Programs/ROOT/current/lib/libTree.so
tests/B2Writer_test: /home/neo/Programs/ROOT/current/lib/libTreePlayer.so
tests/B2Writer_test: /home/neo/Programs/ROOT/current/lib/libRint.so
tests/B2Writer_test: /home/neo/Programs/ROOT/current/lib/libPostscript.so
tests/B2Writer_test: /home/neo/Programs/ROOT/current/lib/libMatrix.so
tests/B2Writer_test: /home/neo/Programs/ROOT/current/lib/libPhysics.so
tests/B2Writer_test: /home/neo/Programs/ROOT/current/lib/libMathCore.so
tests/B2Writer_test: /home/neo/Programs/ROOT/current/lib/libThread.so
tests/B2Writer_test: /home/neo/Programs/ROOT/current/lib/libMultiProc.so
tests/B2Writer_test: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.71.0
tests/B2Writer_test: /usr/lib/x86_64-linux-gnu/libboost_program_options.so.1.71.0
tests/B2Writer_test: /usr/lib/x86_64-linux-gnu/libboost_unit_test_framework.so.1.71.0
tests/B2Writer_test: /usr/lib/x86_64-linux-gnu/libboost_log_setup.so.1.71.0
tests/B2Writer_test: /usr/lib/x86_64-linux-gnu/libboost_log.so.1.71.0
tests/B2Writer_test: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so.1.71.0
tests/B2Writer_test: /usr/lib/x86_64-linux-gnu/libboost_chrono.so.1.71.0
tests/B2Writer_test: /usr/lib/x86_64-linux-gnu/libboost_date_time.so.1.71.0
tests/B2Writer_test: /usr/lib/x86_64-linux-gnu/libboost_regex.so.1.71.0
tests/B2Writer_test: /usr/lib/x86_64-linux-gnu/libboost_thread.so.1.71.0
tests/B2Writer_test: /usr/lib/x86_64-linux-gnu/libboost_atomic.so.1.71.0
tests/B2Writer_test: tests/CMakeFiles/B2Writer_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/neo/Code/WAGASCI/WagasciMonteCarlo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable B2Writer_test"
	cd /home/neo/Code/WAGASCI/WagasciMonteCarlo/cmake-build-debug/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/B2Writer_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/B2Writer_test.dir/build: tests/B2Writer_test

.PHONY : tests/CMakeFiles/B2Writer_test.dir/build

tests/CMakeFiles/B2Writer_test.dir/clean:
	cd /home/neo/Code/WAGASCI/WagasciMonteCarlo/cmake-build-debug/tests && $(CMAKE_COMMAND) -P CMakeFiles/B2Writer_test.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/B2Writer_test.dir/clean

tests/CMakeFiles/B2Writer_test.dir/depend:
	cd /home/neo/Code/WAGASCI/WagasciMonteCarlo/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/neo/Code/WAGASCI/WagasciMonteCarlo /home/neo/Code/WAGASCI/WagasciMonteCarlo/tests /home/neo/Code/WAGASCI/WagasciMonteCarlo/cmake-build-debug /home/neo/Code/WAGASCI/WagasciMonteCarlo/cmake-build-debug/tests /home/neo/Code/WAGASCI/WagasciMonteCarlo/cmake-build-debug/tests/CMakeFiles/B2Writer_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/B2Writer_test.dir/depend

