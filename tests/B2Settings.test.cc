//
// Created by Giorgio Pintaudi on 7/8/20.
//

#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE B2Settings

#include <iostream>

#include <boost/test/unit_test.hpp>

#include "B2Settings.hh"
#include "B2Const.hh"
#include "B2Enum.hh"
#include "B2Pdg.hh"

namespace ut = boost::unit_test;

struct SettingsTestFixture {
  SettingsTestFixture() : string_value("value1"), enum_value(B2NeutrinoFlavor::kPrimaryAntiElectronNeutrino) {}

  B2Settings settings_;
  std::string string_value;
  B2NeutrinoFlavor enum_value;
};

BOOST_FIXTURE_TEST_SUITE(SettingsTest, SettingsTestFixture)

  BOOST_AUTO_TEST_CASE(SetterGetter) {
    settings_[B2Settings::B2SettingName::OutputFilePath] = string_value;
    BOOST_CHECK(boost::any_cast<std::string>(settings_[B2Settings::B2SettingName::OutputFilePath]) == string_value);
    settings_[B2Settings::B2SettingName::NeutrinoFlavorSettings] = enum_value;
    BOOST_CHECK(boost::any_cast<B2NeutrinoFlavor>(settings_[B2Settings::B2SettingName::NeutrinoFlavorSettings]) == enum_value);
  }

  BOOST_AUTO_TEST_CASE(EmptySetting) {
    BOOST_CHECK(boost::any_cast<std::string>(settings_[B2Settings::B2SettingName::OutputFilePath]).empty());
  }

  BOOST_AUTO_TEST_CASE(OutOfRange) {
    BOOST_CHECK_THROW(settings_.At(B2Settings::B2SettingName::OutputFilePath), std::out_of_range);
  }

  BOOST_AUTO_TEST_CASE(Dump) {

    std::string test_string("test");
    settings_[B2Settings::GUI] = true;
    settings_[B2Settings::Command] = test_string;
    settings_[B2Settings::InputFilePath] = test_string;
    settings_[B2Settings::OutputFilePath] = test_string;
    settings_[B2Settings::GeometryDirPath] = test_string;
    settings_[B2Settings::DebugLevel] = test_string;
    settings_[B2Settings::LogFilePath] = test_string;
    settings_[B2Settings::NeutrinoInteractionSettings] = B2Detector::kBabyMind;
    settings_[B2Settings::WaterSettings] = B2WaterSettings::kWgupInWgdownIn;
    settings_[B2Settings::NeutrinoFlavorSettings] = B2NeutrinoFlavor::kPrimaryElectronNeutrino;
    settings_[B2Settings::MagneticField] = true;
    settings_[B2Settings::CosmicMuons] = true;
#ifdef WITH_GDML
    settings_[B2Settings::OutputGdmlFilePath] = test_string;
#endif
    settings_[B2Settings::PencilBeam] = true;
    settings_[B2Settings::PencilBeamX] = 1.;
    settings_[B2Settings::PencilBeamY] = 1.;
    settings_[B2Settings::PencilBeamZ] = 1.;
    settings_[B2Settings::PencilBeamParticlePdg] = PDG_t ::kMuonPlus;
    settings_[B2Settings::PencilBeamAngleTop] = 1.;
    settings_[B2Settings::PencilBeamAngleSide] = 1.;

    std::cout << settings_;
  }

BOOST_AUTO_TEST_SUITE_END()
