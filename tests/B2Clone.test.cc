//
// Created by Giorgio Pintaudi on 2021/01/15.
//

#include <string>
#include <thread>
#include <boost/filesystem.hpp>
#include "gtest/gtest.h"
#include "B2Reader.hh"
#include "B2Writer.hh"
#include "B2SpillSummary.hh"
#include "B2HitSummary.hh"

fs::path INPUT_FILE;

namespace fs = boost::filesystem;

TEST(TestB2Clone, CloneTest) {
  Int_t num_hits = 0;
  UInt_t hit_id = 0;
  fs::path output_file(INPUT_FILE.parent_path() / "output.root");
  {
    // Open the input file
    B2Reader reader(INPUT_FILE);
    // Open the output file and link it to the input file
    B2Writer writer(output_file, reader);
    // Every time that an event is read from the input file, the event information is automatically copied to the
    // output file as well.
    reader.ReadNextSpill();
    // Of course you can make modifications to the output event.
    auto &spill_summary = writer.GetSpillSummary();
    // For example here we add a hit
    num_hits = spill_summary.GetNumHits();
    auto &hit = spill_summary.AddHit();
    hit_id = hit.GetHitId();
    ++num_hits;
    std::cout << "INPUT SPILL (modified)\n" << spill_summary << "\n";
    // When the event is read you have to fill the output file with it
    writer.Fill();
  }
  {
    // This part is just to check that we wrote to the output file correctly
    B2Reader reader(output_file);
    reader.ReadNextSpill();
    std::cout << "CLONED SPILL\n" << reader.GetSpillSummary() << "\n";
    ASSERT_EQ(num_hits, reader.GetSpillSummary().GetNumHits());
    ASSERT_TRUE(reader.GetSpillSummary().HasHit(hit_id));
  }

}

int main(int argc, char **argv) {
  std::cout << "Running main() from gtest_main.cc\n";
  ::testing::InitGoogleTest(&argc, argv);
  for (int i = 0; i < argc; i++) {
    std::cout << "Argument " << i << " : " << argv[i] << std::endl;
  }
  assert(argc == 2);
  INPUT_FILE = argv[1];
  return RUN_ALL_TESTS();
}