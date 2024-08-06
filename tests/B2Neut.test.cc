//
// Created by Giorgio Pintaudi on 31/07/2020.
//

#include <string>
#include <thread>
#include "gtest/gtest.h"
#include "B2Neut.hh"

std::string NEUT_FILE;

TEST(TestB2Neut, DumpTest) {
  B2Neut neut(NEUT_FILE);
  neut.ReadNextEvent();
  neut.DumpEvent();
  neut.ReadNextEvent();
  neut.DumpEvent();
  std::chrono::seconds sleep(1);
  std::this_thread::sleep_for(sleep);
}

int main(int argc, char **argv) {
  std::cout << "Running main() from gtest_main.cc\n";
  ::testing::InitGoogleTest(&argc, argv);
  for (int i = 0; i < argc; i++) {
    std::cout << "Argument " << i << " : " << argv[i] << std::endl;
  }
  assert(argc == 2);
  NEUT_FILE = argv[1];
  return RUN_ALL_TESTS();
}