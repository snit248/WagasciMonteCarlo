//
// Created by Giorgio Pintaudi on 2020/11/12.
//

#include <string>
#include <boost/filesystem.hpp>
#include <TKey.h>
#include "gtest/gtest.h"
#include "B2EmulsionSummary.hh"
#include "B2HitSummary.hh"
#include "B2Writer.hh"
#include "B2Reader.hh"

TEST(TestB2Writer, HitSummary) {
  {
    boost::filesystem::remove("/tmp/test.root");
    B2Writer writer("/tmp/test.root");
    auto &spill_summary = writer.GetSpillSummary();
    auto &hit_summary = spill_summary.AddHit();
    hit_summary.SetDetector(B2Detector::kWagasciUpstream);
    auto id = hit_summary.GetHitId();
    ASSERT_EQ(spill_summary.GetHit(id).GetDetectorId(), B2Detector::kWagasciUpstream);
    writer.Fill();
  }
  {
    B2Reader reader("/tmp/test.root");
    reader.ReadSpill(0);
    auto &spill_summary = reader.GetSpillSummary();
    auto &hit_summary = spill_summary.AddHit();
    hit_summary.SetDetector(B2Detector::kWagasciUpstream);
    auto id = hit_summary.GetHitId();
    ASSERT_EQ(spill_summary.GetHit(id).GetDetectorId(), B2Detector::kWagasciUpstream);
  }
}

TEST(TestB2Writer, TestCopy) {
  boost::filesystem::remove("/tmp/test_output.root");
  B2Reader reader("/tmp/test_input.root");
  B2Writer writer("/tmp/test_output.root", reader);
  for (int i = 0; i < 3; ++i) {
    reader.ReadNextSpill();
    writer.Fill();
  }
}


TEST(TestB2Writer, DialsAndSigmas) {
  {
    boost::filesystem::remove("/tmp/test_output.root");
    B2Reader reader("/tmp/test_input.root");
    B2Writer writer("/tmp/test_output.root", reader);
  }
  std::map<std::string, int> input_bytes;
  {
    std::cout << "input\n";
    TFile input("/tmp/test_input.root");
    auto *dir = input.GetDirectory("dials");
    TKey *key;
    TIter nextkey(dir->GetListOfKeys());
    while ((key = (TKey *) nextkey())) {
      std::cout << key->GetClassName() << " " <<  key->GetName() << " " << key->GetNbytes() << " bytes\n";
      input_bytes[key->GetName()] = key->GetNbytes();
    }
  }
  std::map<std::string, int> output_bytes;
  {
    std::cout << "output\n";
    TFile output("/tmp/test_input.root");
    auto *dir = output.GetDirectory("dials");
    TKey *key;
    TIter nextkey(dir->GetListOfKeys());
    while ((key = (TKey *) nextkey())) {
      std::cout << key->GetClassName() << " " <<  key->GetName() << " " << key->GetNbytes() << " bytes\n";
      output_bytes[key->GetName()] = key->GetNbytes();
    }
  }
  ASSERT_EQ(input_bytes, output_bytes);
}

#ifdef NINJA
TEST(TestB2Writer, EmulsionSummary) {
  {
    boost::filesystem::remove("/tmp/test.root");
    B2Writer writer("/tmp/test.root");
    auto &spill_summary = writer.GetSpillSummary();
    auto &emulsion_summary = spill_summary.AddEmulsion();
    emulsion_summary.SetEmulsionTrackId(1);
    emulsion_summary.SetEcc(1);
    ASSERT_EQ(spill_summary.GetNumEmulsions(), 1);
    ASSERT_EQ(spill_summary.GetEmulsion(1).GetEcc(), 1);
    writer.Fill();
  }
  {
    B2Reader reader("/tmp/test.root");
    reader.ReadSpill(0);
    auto &spill_summary = reader.GetSpillSummary();
    ASSERT_EQ(spill_summary.GetNumEmulsions(), 1);
    ASSERT_EQ(spill_summary.GetEmulsion(1).GetEcc(), 1);
  }
}
#endif