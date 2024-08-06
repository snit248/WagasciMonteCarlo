include(ExternalProject)
ExternalProject_Add(googletest
  GIT_REPOSITORY    https://github.com/google/googletest.git
  GIT_TAG           main
  SOURCE_DIR        "/home/neo/Code/WAGASCI/WagasciMonteCarlo/cmake-build-debug/external/googletest-src"
  BINARY_DIR        "/home/neo/Code/WAGASCI/WagasciMonteCarlo/cmake-build-debug/external/googletest-build"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)
