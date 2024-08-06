//
// Created by Giorgio Pintaudi on 7/8/20.
//

#include "B2Configuration.hh"

#include <cstdlib>

#include <boost/algorithm/string.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes.hpp>

#include "B2Enum.hh"
#include "B2Pdg.hh"

#define xstr(a) str(a)
#define str(a) #a

namespace po = boost::program_options;
namespace al = boost::algorithm;

const fs::path HOME_DIRECTORY(std::getenv("HOME"));
const fs::path DEFAULT_CONFIGURATION_FILE(HOME_DIRECTORY / ".wagasci" / "B2MC_conf.ini");
const fs::path DEFAULT_LOG_FILE(fs::path("data") / "log" / "B2MC.log");
const fs::path DEFAULT_GDML_FILE(fs::path("data") / "myGDML.gdml");
const fs::path DEFAULT_OUTPUT_FILE(fs::path("data") / "output.root");
const fs::path DEFAULT_INPUT_FILE(fs::path("data") / "input.root");
#ifdef INSTALL_DATADIR
const fs::path INSTALL_DATADIR_PATH(xstr(INSTALL_DATADIR));
const fs::path DEFAULT_GEOMETRY_DIRECTORY(INSTALL_DATADIR_PATH / "geometry");
#else
const fs::path DEFAULT_GEOMETRY_DIRECTORY(fs::path("data") / "geometry");
#endif
const fs::path DEFAULT_KINK_FILE(fs::path("data") / "kink_input.root");
const fs::path MAGFIELD_TABLE_FILE("magfield.table");


B2Configuration::B2Configuration(int argc, char *argv[], bool create) :
    create_(create) {
  PopulateOptionsDescription();
  ReadShellArguments(argc, argv);
  if (fs::is_regular_file(ini_path_)) {
    ReadConfigurationFile(ini_path_);
  } else if (create_) {
    CreateConfigurationFile(ini_path_);
  }
}

B2Configuration::B2Configuration(fs::path &path, bool create) :
    ini_path_(path), create_(create) {
  PopulateOptionsDescription();
  ReadShellArguments(0, nullptr);
  if (fs::is_regular_file(path)) {
    ReadConfigurationFile(path);
  } else if (create_) {
    CreateConfigurationFile(path);
  }
}

B2Configuration::B2Configuration(bool create) :
    B2Configuration(0, nullptr, create) {}

std::ostream &operator<<(std::ostream &os, const std::vector<int> &vec) {
  for (auto item : vec) {
    os << item << " ";
  }
  return os;
}

void B2Configuration::PopulateOptionsDescription() {
  desc_.add_options()
      ("help,h", "Print this help message.\n")
#ifdef VERSION
      ("version", po::bool_switch()->default_value(false), "Print version number and exit.\n")
#endif
      ("command,d", po::value<std::string>()->default_value(""),
       ".mac file to execute when in batch mode (optional).\n")
      ("gui,u", po::bool_switch()->default_value(false), "GUI mode.\n")
      ("output-file-path,o", po::value<std::string>()->default_value(DEFAULT_OUTPUT_FILE.string()),
       "Path to the output ROOT file.\n")
      ("output-gdml-file-path,a", po::value<std::string>()->default_value(DEFAULT_GDML_FILE.string()),
       "Path to the output GDML file.\n")
      ("input-file-path,i", po::value<std::string>()->default_value(DEFAULT_INPUT_FILE.string()),
       "Path to the input ROOT file.\n")
      ("neutrino-interaction-settings,v", po::value<std::string>()->default_value("WagasciUpstream"),
       "Neutrino interaction position. You can select either the number or the B2Detector enum name "
       "without initial k.\n"
       "  -v 0: \"ProtonModule\": Neutrino interaction in Proton Module\n"
       "  -v 1: \"WagasciUpstream\": Neutrino interaction in WAGASCI Upstream\n"
       "  -v 2: \"WagasciDownstream\": Neutrino interaction in WAGASCI Downstream\n"
       "  -v 3: \"WallMrdSouth\": Neutrino interaction in WallMRD South\n"
       "  -v 4: \"WallMrdNorth\": Neutrino interaction in WallMRD North\n"
       "  -v 5: \"BabyMind\": Neutrino interaction in Baby MIND\n"
       "  -v 7: \"Ninja\": Neutrino interaction in NINJA\n"
       "  -v 9: \"Wall\": Neutrino interaction in B2 Wall\n"
       "  -v 10: \"PillarSouth\" : Neutrino interaction in B2 Pillar South\n"
       "  -v 11: \"PillarNorth\" : Neutrino interaction in B2 Pillar North")
      ("neutrino-interaction-material,q", po::value<std::string>()->default_value("Water"),
          "material where the vertex should be generated (only NINJA)\n"
          "  -q -2: \"UnknownMaterial\": material not specified\n"
          "  -q 0: \"Water\": interaction in water\n"
          "  -q 2: \"Iron\": interaction in iron (SUS316L)\n")
      ("water-settings,w", po::value<std::string>()->default_value("WgupInWgdownIn"),
       "Water settings. You can select either the number or the B2WaterSettings enum name without initial k.\n"
       "  -w 1: \"WgupOutWgdownOut\": WAGASCI upstream: water out, WAGASCI downstream: water out\n"
       "  -w 2: \"WgupInWgdownOut\": WAGASCI upstream: water in,  WAGASCI downstream: water out\n"
       "  -w 3: \"WgupOutWgdownIn\": WAGASCI upstream: water out, WAGASCI downstream: water in\n"
       "  -w 4: \"WgupInWgdownIn\": WAGASCI upstream: water in,  WAGASCI downstream: water in\n")
      ("neutrino-flavor-settings,f", po::value<std::string>()->default_value("MuonNeutrino"),
       "Flavor of the primary neutrino. You can select either the number or the B2NeutrinoFlavor enum name "
       "without initial k.\n"
       "  -f 1: \"MuonNeutrino\": Muon neutrino\n"
       "  -f 2: \"AntiMuonNeutrino\": Anti-muon neutrino\n"
       "  -f 3: \"ElectronNeutrino\": Electron neutrino\n"
       "  -f 4: \"AntiElectronNeutrino\": Anti-electron neutrino\n")
      ("magnetic-field,m", po::bool_switch()->default_value(true), "Switch on the magnetic field in BabyMIND.\n")
      ("michel-electrons", po::bool_switch()->default_value(false), "Switch on the Michel electrons finder.\n")
      ("secondary-tracks", po::bool_switch()->default_value(false), "Enable the recording of secondary tracks.\n")
      ("number-of-spills,n", po::value<int>()->default_value(10000),
          "Number of spills to simulate in cosmic muons mode or pencil beam mode.\n")
      ("cosmic-muons,j", po::bool_switch()->default_value(false), "Switch on the cosmic muons generator.\n")
      ("pencil-beam,e", po::bool_switch()->default_value(false), "Switch on the pencil beam.\n")
      ("pencil-beam-random-direction,b", po::bool_switch()->default_value(false), "Generate random pencil beam.\n")
      ("pencil-beam-particle-pdg,r", po::value<int>()->default_value(PDG_t::kMuonMinus),
       "PDG ID of the pencil beam particle.\n")
      ("pencil-beam-momentum,k", po::value<double>()->default_value(1000),
       "Momentum of pencil beam in MeV.\n")
      ("pencil-beam-x,x", po::value<double>()->default_value(0), "X position in mm of the pencil beam.\n")
      ("pencil-beam-y,y", po::value<double>()->default_value(0), "Y position in mm of the pencil beam.\n")
      ("pencil-beam-z,z", po::value<double>()->default_value(0), "Z position in mm of the pencil beam.\n")
      ("pencil-beam-angle-top,t", po::value<double>()->default_value(0),
       "Angle in top view of the pencil beam (degrees).\n")
      ("pencil-beam-angle-side,s", po::value<double>()->default_value(0),
       "Angle in side view of the pencil beam (degrees).\n")
      ("debug-level,l", po::value<std::string>()->default_value("info"),
       "Debug log level. Can be trace, debug, info, warning, error or fatal. Default is info.\n")
      ("log-file-path,p", po::value<std::string>()->default_value(DEFAULT_LOG_FILE.string()),
       "Path to the application log file.\n")
      ("geometry-dir-path,g",
       po::value<std::string>()->default_value(DEFAULT_GEOMETRY_DIRECTORY.string()),
       "Path to the directory where all the geometry files are located.\n")
      ("configuration-file-path,c", po::value<std::string>()->default_value(DEFAULT_CONFIGURATION_FILE.string()),
       "Path to the configuration INI file.\n")
      ("ninja-kink-study", po::bool_switch()->default_value(false), "Switch on the NINJA kink study mode.\n")
      ("kink-file-path",
       po::value<std::string>()->default_value(DEFAULT_KINK_FILE.string()),
       "Path to the kink input files.\n");
}

void B2Configuration::ReadShellArguments(int argc, char **argv) {
  BOOST_LOG_TRIVIAL(info) << "Reading configuration from console arguments";
  po::store(po::command_line_parser(argc, argv).options(desc_).run(), vm_);
  po::notify(vm_);
  if (vm_.count("help")) {
    BOOST_LOG_TRIVIAL(fatal) << "USAGE: " << fs::basename(argv[0]) << desc_ << std::endl;
    std::exit(EXIT_SUCCESS);
  }
  ini_path_ = vm_["configuration-file-path"].as<std::string>();
  BOOST_LOG_TRIVIAL(debug) << "Configuration file path is " << ini_path_;
  BOOST_LOG_TRIVIAL(debug) << "Log file path is " << vm_["log-file-path"].as<std::string>();
}

void B2Configuration::ReadConfigurationFile(fs::path &path) {
  BOOST_LOG_TRIVIAL(info) << "Reading configuration from file " << path;
  if (!fs::is_regular_file(path)) {
    throw std::runtime_error("Configuration file " + path.string() + " not found!");
  }
  std::ifstream ifs(path.string());
  po::store(po::parse_config_file(ifs, desc_), vm_);
  po::notify(vm_);
}

void B2Configuration::CreateConfigurationFile(fs::path &path) {
  BOOST_LOG_TRIVIAL(warning) << "Creating new configuration file at " << path;
  if (fs::exists(path)) {
    throw std::runtime_error("Configuration file " + path.string() + " already exists!");
  }
  if (!path.parent_path().empty() && !fs::exists(path.parent_path())) {
    boost::system::error_code error_code;
    fs::create_directories(path.parent_path(), error_code);
    if (error_code) {
      throw std::runtime_error("Could not create " + path.parent_path().string() +
                               " directory : " + error_code.message());
    }
  }
  std::ofstream ofs(path.string());

  std::string content = R"(# General
gui=false
command=
neutrino-interaction-settings=WagasciUpstream
neutrino-interaction-material=Water
water-settings=WgupInWgdownIn
neutrino-flavor-settings=MuonNeutrino
magnetic-field=true
michel-electrons=false
secondary-tracks=false
cosmic-muons=false
number-of-spills=10000

# Input/Output
output-file-path=)" + DEFAULT_OUTPUT_FILE.string() + R"(
input-file-path=)" + DEFAULT_INPUT_FILE.string() + R"(
output-gdml-file-path=)" + DEFAULT_GDML_FILE.string() + R"(

# Geometry
geometry-dir-path=)" + DEFAULT_GEOMETRY_DIRECTORY.string() + R"(

# Pencil beam
pencil-beam=false
pencil-beam-particle-pdg=)" + std::to_string(PDG_t::kMuonMinus) + R"(
pencil-beam-momentum=1000
pencil-beam-x=0
pencil-beam-y=0
pencil-beam-z=0
pencil-beam-angle-top=0
pencil-beam-angle-side=0

# Log
debug-level=info
log-file-path=)" + DEFAULT_LOG_FILE.string() + R"(

# Kink
ninja-kink-study=false
kink-file-path=)" + DEFAULT_KINK_FILE.string();

  ofs << content;
}

//al::to_lower_copy(

B2Settings B2Configuration::GetSettings() {
  BOOST_LOG_TRIVIAL(debug) << "Generating settings object";
  B2Settings settings;
  try {
    settings[B2Settings::PrintVersion] = vm_["version"].as<bool>();
    settings[B2Settings::Command] = vm_["command"].as<std::string>();
    settings[B2Settings::GUI] = vm_["gui"].as<bool>();
    settings[B2Settings::InputFilePath] = vm_["input-file-path"].as<std::string>();
    settings[B2Settings::OutputFilePath] = vm_["output-file-path"].as<std::string>();
#ifdef WITH_GDML
    settings[B2Settings::OutputGdmlFilePath] = vm_["output-gdml-file-path"].as<std::string>();
#endif
    settings[B2Settings::GeometryDirPath] = vm_["geometry-dir-path"].as<std::string>();
    settings[B2Settings::DebugLevel] = al::to_lower_copy(vm_["debug-level"].as<std::string>());
    settings[B2Settings::LogFilePath] = vm_["log-file-path"].as<std::string>();
    settings[B2Settings::MagneticField] = vm_["magnetic-field"].as<bool>();
    settings[B2Settings::MichelElectrons] = vm_["michel-electrons"].as<bool>();
    settings[B2Settings::SecondaryTracks] = vm_["secondary-tracks"].as<bool>();
    settings[B2Settings::CosmicMuons] = vm_["cosmic-muons"].as<bool>();
    settings[B2Settings::NumberOfSpills] = vm_["number-of-spills"].as<int>();

    auto neutrino_interaction_settings = al::to_lower_copy(vm_["neutrino-interaction-settings"].as<std::string>());
    boost::erase_all(neutrino_interaction_settings, " ");
    boost::erase_all(neutrino_interaction_settings, "_");
    boost::erase_all(neutrino_interaction_settings, "-");
    if (neutrino_interaction_settings == "protonmodule" || neutrino_interaction_settings == "0")
      settings[B2Settings::NeutrinoInteractionSettings] = B2Detector::kProtonModule;
    else if (neutrino_interaction_settings == "wagasciupstream" || neutrino_interaction_settings == "1")
      settings[B2Settings::NeutrinoInteractionSettings] = B2Detector::kWagasciUpstream;
    else if (neutrino_interaction_settings == "wagascidownstream" || neutrino_interaction_settings == "2")
      settings[B2Settings::NeutrinoInteractionSettings] = B2Detector::kWagasciDownstream;
    else if (neutrino_interaction_settings == "wallmrdsouth" || neutrino_interaction_settings == "wmrdsouth" ||
             neutrino_interaction_settings == "3")
      settings[B2Settings::NeutrinoInteractionSettings] = B2Detector::kWallMrdSouth;
    else if (neutrino_interaction_settings == "wallmrdnorth" || neutrino_interaction_settings == "wmrdnorth" ||
             neutrino_interaction_settings == "4")
      settings[B2Settings::NeutrinoInteractionSettings] = B2Detector::kWallMrdNorth;
    else if (neutrino_interaction_settings == "babymind" || neutrino_interaction_settings == "5")
      settings[B2Settings::NeutrinoInteractionSettings] = B2Detector::kBabyMind;
    else if (neutrino_interaction_settings == "ninja" || neutrino_interaction_settings == "7")
      settings[B2Settings::NeutrinoInteractionSettings] = B2Detector::kNinja;
    else if (neutrino_interaction_settings == "wall" || neutrino_interaction_settings == "9")
      settings[B2Settings::NeutrinoInteractionSettings] = B2Detector::kWall;
    else if (neutrino_interaction_settings == "pillarsouth" || neutrino_interaction_settings == "10")
      settings[B2Settings::NeutrinoInteractionSettings] = B2Detector::kPillarSouth;
    else if (neutrino_interaction_settings == "pillarnorth" || neutrino_interaction_settings == "11")
      settings[B2Settings::NeutrinoInteractionSettings] = B2Detector::kPillarNorth;
    else
      throw std::invalid_argument("Neutrino interaction settings not recognized : " +
                                  vm_["neutrino-interaction-settings"].as<std::string>());

    auto neutrino_interaction_material = al::to_lower_copy(vm_["neutrino-interaction-material"].as<std::string>());
    boost::erase_all(neutrino_interaction_material, " ");
    boost::erase_all(neutrino_interaction_material, "_");
    boost::erase_all(neutrino_interaction_material, "-");
    if (neutrino_interaction_material == "water" || neutrino_interaction_material == "0")
      settings[B2Settings::NeutrinoInteractionMaterial] = B2Material::kWater;
    else if (neutrino_interaction_material == "iron" || neutrino_interaction_material == "2")
      settings[B2Settings::NeutrinoInteractionMaterial] = B2Material::kIron;
    else if (neutrino_interaction_material == "unknownmaterial" ||
             neutrino_interaction_material == "-2" ||
             neutrino_interaction_material.empty())
      settings[B2Settings::NeutrinoInteractionMaterial] = B2Material::kUnknownMaterial;
    else
      throw std::invalid_argument("Neutrino interaction material not recognized : " +
                                  vm_["neutrino-interaction-material"].as<std::string>());

    auto water_settings = al::to_lower_copy(vm_["water-settings"].as<std::string>());
    boost::erase_all(water_settings, " ");
    boost::erase_all(water_settings, "_");
    boost::erase_all(water_settings, "-");
    if (water_settings == "wgupoutwgdownout" || water_settings == "1")
      settings[B2Settings::WaterSettings] = B2WaterSettings::kWgupOutWgdownOut;
    else if (water_settings == "wgupinwgdownout" || water_settings == "2")
      settings[B2Settings::WaterSettings] = B2WaterSettings::kWgupInWgdownOut;
    else if (water_settings == "wgupoutwgdownin" || water_settings == "3")
      settings[B2Settings::WaterSettings] = B2WaterSettings::kWgupOutWgdownIn;
    else if (water_settings == "wgupinwgdownin" || water_settings == "4")
      settings[B2Settings::WaterSettings] = B2WaterSettings::kWgupInWgdownIn;
    else
      throw std::invalid_argument("Water settings not recognized : " + vm_["water-settings"].as<std::string>());

    auto neutrino_flavor_settings = al::to_lower_copy(vm_["neutrino-flavor-settings"].as<std::string>());
    boost::erase_all(neutrino_flavor_settings, " ");
    boost::erase_all(neutrino_flavor_settings, "_");
    boost::erase_all(neutrino_flavor_settings, "-");
    if (neutrino_flavor_settings == "muonneutrino" || neutrino_flavor_settings == "1")
      settings[B2Settings::NeutrinoFlavorSettings] = B2NeutrinoFlavor::kPrimaryMuonNeutrino;
    else if (neutrino_flavor_settings == "antimuonneutrino" || neutrino_flavor_settings == "2")
      settings[B2Settings::NeutrinoFlavorSettings] = B2NeutrinoFlavor::kPrimaryAntiMuonNeutrino;
    else if (neutrino_flavor_settings == "electronneutrino" || neutrino_flavor_settings == "3")
      settings[B2Settings::NeutrinoFlavorSettings] = B2NeutrinoFlavor::kPrimaryElectronNeutrino;
    else if (neutrino_flavor_settings == "antielectronneutrino" || neutrino_flavor_settings == "4")
      settings[B2Settings::NeutrinoFlavorSettings] = B2NeutrinoFlavor::kPrimaryAntiElectronNeutrino;
    else
      throw std::invalid_argument("Neutrino flavor settings not recognized : " +
                                  vm_["neutrino-flavor-settings"].as<std::string>());

    settings[B2Settings::PencilBeam] = vm_["pencil-beam"].as<bool>();
    settings[B2Settings::PencilBeamRandomDirection] = vm_["pencil-beam-random-direction"].as<bool>();
    settings[B2Settings::PencilBeamParticlePdg] = static_cast<PDG_t>(vm_["pencil-beam-particle-pdg"].as<int>());
    settings[B2Settings::PencilBeamMomentum] = vm_["pencil-beam-momentum"].as<double>();
    settings[B2Settings::PencilBeamX] = vm_["pencil-beam-x"].as<double>();
    settings[B2Settings::PencilBeamY] = vm_["pencil-beam-y"].as<double>();
    settings[B2Settings::PencilBeamZ] = vm_["pencil-beam-z"].as<double>();
    settings[B2Settings::PencilBeamAngleTop] = vm_["pencil-beam-angle-top"].as<double>();
    settings[B2Settings::PencilBeamAngleSide] = vm_["pencil-beam-angle-side"].as<double>();

    settings[B2Settings::NinjaKinkStudy] = vm_["ninja-kink-study"].as<bool>();
    settings[B2Settings::KinkFilePath] = vm_["kink-file-path"].as<std::string>();

  } catch (const boost::bad_any_cast &except) {
    throw std::runtime_error("Check the command line arguments for typos!");
  }
  return settings;
}
