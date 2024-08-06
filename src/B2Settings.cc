//
// Created by Giorgio Pintaudi on 7/8/20.
//

#include "B2Settings.hh"
#include <iterator> // for ostream_iterator
#include "B2Enum.hh"
#include "B2Pdg.hh"

boost::any &B2Settings::operator[](const B2SettingName &name) {
  if (!this->Has(name))
    settings_[name] = std::string();
  return settings_[name];
}

bool B2Settings::Has(const B2SettingName &name) {
  return static_cast<const B2Settings &>(*this).Has(name);
}

bool B2Settings::Has(const B2SettingName &name) const {
  return settings_.find(name) != settings_.end();
}

boost::any &B2Settings::At(const B2SettingName &name) {
  return const_cast<boost::any &>(static_cast<const B2Settings &>(*this).At(name));
}

const boost::any &B2Settings::At(const B2SettingName &name) const {
  return settings_.at(name);
}

std::ostream &operator<<(std::ostream &os, const B2Settings &obj) {
  os << "  GUI = "
     << std::boolalpha << boost::any_cast<bool>(obj.At(B2Settings::GUI)) << "\n"
     << "  Command = "
     << boost::any_cast<std::string>(obj.At(B2Settings::Command)) << "\n"
     << "  OutputFilePath = "
     << boost::any_cast<std::string>(obj.At(B2Settings::OutputFilePath)) << "\n"
     << "  InputFilePath = "
     << boost::any_cast<std::string>(obj.At(B2Settings::InputFilePath)) << "\n"
#ifdef WITH_GDML
     << "  OutputGdmlFilePath = "
     << boost::any_cast<std::string>(obj.At(B2Settings::OutputGdmlFilePath)) << "\n"
#endif
     << "  GeometryDirPath = "
     << boost::any_cast<std::string>(obj.At(B2Settings::GeometryDirPath)) << "\n"
     << "  DebugLevel = "
     << boost::any_cast<std::string>(obj.At(B2Settings::DebugLevel)) << "\n"
     << "  LogFilePath = "
     << boost::any_cast<std::string>(obj.At(B2Settings::LogFilePath)) << "\n"
     << "  NeutrinoInteractionSettings = "
     << boost::any_cast<B2Detector>(obj.At(B2Settings::NeutrinoInteractionSettings)) << "\n"
     << "  NeutrinoInteractionMaterial = "
     << boost::any_cast<B2Material>(obj.At(B2Settings::NeutrinoInteractionMaterial)) << "\n"
     << "  WaterSettings = "
     << boost::any_cast<B2WaterSettings>(obj.At(B2Settings::WaterSettings)) << "\n"
     << "  NetrinoFlavorSettings = "
     << boost::any_cast<B2NeutrinoFlavor>(obj.At(B2Settings::NeutrinoFlavorSettings)) << "\n"
     << "  MagneticField = "
     << std::boolalpha << boost::any_cast<bool>(obj.At(B2Settings::MagneticField)) << "\n"
     << "  MichelElectrons = "
     << std::boolalpha << boost::any_cast<bool>(obj.At(B2Settings::MichelElectrons)) << "\n"
     << "  SecondaryTracks = "
     << std::boolalpha << boost::any_cast<bool>(obj.At(B2Settings::SecondaryTracks)) << "\n"
     << "  NumberOfSpills = "
     << boost::any_cast<int>(obj.At(B2Settings::NumberOfSpills)) << "\n"
     << "  CosmicMuons = "
     << std::boolalpha << boost::any_cast<bool>(obj.At(B2Settings::CosmicMuons)) << "\n"
     << "  PencilBeam = "
     << std::boolalpha << boost::any_cast<bool>(obj.At(B2Settings::PencilBeam)) << "\n"
     << "  PencilBeamRandomDirection = "
     << std::boolalpha << boost::any_cast<bool>(obj.At(B2Settings::PencilBeamRandomDirection)) << "\n"
     << "  PencilBeamParticlePdg = "
     << boost::any_cast<PDG_t>(obj.At(B2Settings::PencilBeamParticlePdg)) << "\n"
     << "  PencilBeamMomentum = "
     << boost::any_cast<double>(obj.At(B2Settings::PencilBeamMomentum)) << "\n"
     << "  PencilBeamX = "
     << boost::any_cast<double>(obj.At(B2Settings::PencilBeamX)) << "\n"
     << "  PencilBeamY = "
     << boost::any_cast<double>(obj.At(B2Settings::PencilBeamY)) << "\n"
     << "  PencilBeamZ = "
     << boost::any_cast<double>(obj.At(B2Settings::PencilBeamZ)) << "\n"
     << "  PencilBeamAngleTop = "
     << boost::any_cast<double>(obj.At(B2Settings::PencilBeamAngleTop)) << "\n"
     << "  PencilBeamAngleSide = "
     << boost::any_cast<double>(obj.At(B2Settings::PencilBeamAngleSide)) << "\n"
     << "  NinjaKinkStudy = "
     << std::boolalpha << boost::any_cast<bool>(obj.At(B2Settings::NinjaKinkStudy)) << "\n"
     << "  KinkFilePath = "
     << boost::any_cast<std::string>(obj.At(B2Settings::KinkFilePath));
  return os;
}
