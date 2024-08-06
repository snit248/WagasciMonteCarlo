//
// Created by Giorgio Pintaudi on 8/13/20.
//

#include <string>

#include "gtest/gtest.h"
#include "B2Measurement.hh"

TEST(TestB2Measurement, DoubleReadout) {
  B2DoubleReadoutD test_dr_d;
  Double_t value1 = 42;
  Double_t value2 = 666;
  Double_t error1 = 2;
  Double_t error2 = 6;
  test_dr_d.Set(B2Readout::kTopReadout, value1, error1);
  test_dr_d.Set(B2Readout::kSideReadout, value2, error2);

  EXPECT_DOUBLE_EQ(test_dr_d.GetValue(B2Readout::kTopReadout), value1);
  EXPECT_DOUBLE_EQ(test_dr_d.GetError(B2Readout::kTopReadout), error1);
  EXPECT_DOUBLE_EQ(test_dr_d.GetValue(B2Readout::kSideReadout), value2);
  EXPECT_DOUBLE_EQ(test_dr_d.GetError(B2Readout::kSideReadout), error2);
}

TEST(TestB2Measurement, IntReadout) {
  B2DoubleReadoutI test_dr_i;
  Int_t value1 = 42;
  Int_t value2 = 666;
  Int_t error1 = 2;
  Int_t error2 = 6;
  test_dr_i.Set(B2Readout::kLeftReadout, value1, error1);
  test_dr_i.Set(B2Readout::kRightReadout, value2, error2);

  EXPECT_EQ(test_dr_i.GetValue(B2Readout::kLeftReadout), value1);
  EXPECT_EQ(test_dr_i.GetError(B2Readout::kLeftReadout), error1);
  EXPECT_EQ(test_dr_i.GetValue(B2Readout::kRightReadout), value2);
  EXPECT_EQ(test_dr_i.GetError(B2Readout::kRightReadout), error2);
}

TEST(TestB2Measurement, ReadoutEnum) {
  EXPECT_NE(B2Readout::kLeftReadout, B2Readout::kRightReadout);
  EXPECT_NE(B2Readout::kTopReadout, B2Readout::kBottomReadout);
  EXPECT_NE(B2Readout::kTopReadout, B2Readout::kSideReadout);
}

TEST(TestB2Measurement, B2Energy) {
  Double_t value = 42;
  Double_t error = 2;
  B2Energy test_energy(value, error);
  EXPECT_DOUBLE_EQ(test_energy.GetValue(), value);
  EXPECT_DOUBLE_EQ(test_energy.GetError(), error);
  test_energy.Clear("C");
  test_energy.Set(value, error);
  EXPECT_DOUBLE_EQ(test_energy.GetValue(), value);
  EXPECT_DOUBLE_EQ(test_energy.GetError(), error);
  test_energy.Clear("C");
  test_energy.SetValue(value);
  test_energy.SetError(error);
  EXPECT_DOUBLE_EQ(test_energy.GetValue(), value);
  EXPECT_DOUBLE_EQ(test_energy.GetError(), error);
}

TEST(TestB2Measurement, B2Time) {
  Double_t value = 42;
  Double_t error = 2;
  B2Time test_time(value, error);
  EXPECT_DOUBLE_EQ(test_time.GetValue(), value);
  EXPECT_DOUBLE_EQ(test_time.GetError(), error);
  test_time.Clear("C");
  test_time.Set(value, error);
  EXPECT_DOUBLE_EQ(test_time.GetValue(), value);
  EXPECT_DOUBLE_EQ(test_time.GetError(), error);
  test_time.Clear("C");
  test_time.SetValue(value);
  test_time.SetError(error);
  EXPECT_DOUBLE_EQ(test_time.GetValue(), value);
  EXPECT_DOUBLE_EQ(test_time.GetError(), error);
}

TEST(TestB2Measurement, B2Position) {
  Double_t value1 = 42;
  Double_t value2 = 666;
  Double_t value3 = 17;
  TVector3 value(value1, value2, value3);
  Double_t error1 = 2;
  Double_t error2 = 6;
  Double_t error3 = 5;
  TVector3 error(error1, error2, error3);

  B2Position test_pos1(value1, value2, value3, error1, error2, error3);
  EXPECT_EQ(test_pos1.GetValue(), value);
  EXPECT_EQ(test_pos1.GetError(), error);

  test_pos1.Clear("C");
  test_pos1.SetValue(value1, value2, value3);
  test_pos1.SetError(error1, error2, error3);
  EXPECT_EQ(test_pos1.GetValue(), value);
  EXPECT_EQ(test_pos1.GetError(), error);

  test_pos1.Clear("C");
  test_pos1.Set(value1, value2, value3, error1, error2, error3);
  EXPECT_EQ(test_pos1.GetValue(), value);
  EXPECT_EQ(test_pos1.GetError(), error);

  test_pos1.Clear("C");
  test_pos1.Set(value, error);
  EXPECT_EQ(test_pos1.GetValue(), value);
  EXPECT_EQ(test_pos1.GetError(), error);

  B2Position test_pos2(value, error);
  EXPECT_EQ(test_pos1.GetValue(), value);
  EXPECT_EQ(test_pos1.GetError(), error);
}

TEST(TestB2Measurement, B2Direction) {
  TVector3 value(1, 0, 0);
  TVector3 error(0.1, 0.1, 0.1);

  B2Direction test_dir(value, error);
  EXPECT_EQ(test_dir.GetValue(), value);
  EXPECT_EQ(test_dir.GetError(), error);

  test_dir.Clear("C");
  test_dir.SetValue(value);
  test_dir.SetError(error);
  EXPECT_EQ(test_dir.GetValue(), value);
  EXPECT_EQ(test_dir.GetError(), error);

  value.SetXYZ(2, 2, 2);
  test_dir.Clear("C");
  EXPECT_THROW(test_dir.Set(value, error), std::invalid_argument);
}

