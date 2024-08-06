//
// Created by Giorgio Pintaudi on 7/8/20.
//

#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE B2Configuration

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <boost/any.hpp>
#include <wordexp.h>
#include <B2Const.hh>
#include "B2Configuration.hh"

namespace fs = boost::filesystem;

struct ConfigurationTestFixture {
  fs::path non_existing_conf_file_;
  fs::path existing_conf_file_;
  std::string cli_arguments_;
  std::string cli_empty_arguments_;
  wordexp_t wordexp_{};
  wordexp_t wordexp_empty_{};

  ConfigurationTestFixture() :
      non_existing_conf_file_("test_non_existent.conf"),
      existing_conf_file_("test_existent.conf"),
      cli_arguments_("program_name -c " + non_existing_conf_file_.string() + " -f 3 -l info -m"),
      cli_empty_arguments_("program_name -c " + existing_conf_file_.string()) {
    wordexp(cli_arguments_.c_str(), &wordexp_, 0);
    wordexp(cli_empty_arguments_.c_str(), &wordexp_empty_, 0);
    fs::remove_all(non_existing_conf_file_);
    fs::remove_all(existing_conf_file_);
    std::ofstream ofs(existing_conf_file_.string());
    std::string content = R"(
neutrino-flavor-settings=AntiElectronNeutrino
magnetic-field=false
debug-level=error
)";
    ofs << content;
  }

  ~ConfigurationTestFixture() {
    fs::remove_all(non_existing_conf_file_);
    fs::remove_all(existing_conf_file_);
    wordfree(&wordexp_);
    wordfree(&wordexp_empty_);
  }
};

BOOST_FIXTURE_TEST_SUITE(ConfigurationTest, ConfigurationTestFixture)

  BOOST_AUTO_TEST_CASE(EmptyConstructor) {
    B2Configuration configuration(false);
    B2Settings settings = configuration.GetSettings();
    BOOST_CHECK(!boost::any_cast<std::string>(settings.At(B2Settings::DebugLevel)).empty());
    BOOST_CHECK(!boost::any_cast<std::string>(settings.At(B2Settings::OutputFilePath)).empty());
  }

  BOOST_AUTO_TEST_CASE(ReadShellArguments) {
    B2Configuration configuration(static_cast<int>(wordexp_.we_wordc), wordexp_.we_wordv, false);
    B2Settings settings = configuration.GetSettings();
    BOOST_CHECK(boost::any_cast<std::string>(settings.At(B2Settings::DebugLevel)) == "info");
    BOOST_CHECK(boost::any_cast<B2NeutrinoFlavor>(settings.At(B2Settings::NeutrinoFlavorSettings)) ==
                B2NeutrinoFlavor::kPrimaryElectronNeutrino);
    BOOST_CHECK(boost::any_cast<bool>(settings.At(B2Settings::MagneticField)));
    BOOST_CHECK(!fs::exists(non_existing_conf_file_));
  }

  BOOST_AUTO_TEST_CASE(ReadConfigurationFile) {
    B2Configuration configuration(static_cast<int>(wordexp_empty_.we_wordc), wordexp_empty_.we_wordv, false);
    B2Settings settings = configuration.GetSettings();
    BOOST_CHECK(boost::any_cast<std::string>(settings.At(B2Settings::DebugLevel)) == "error");
    BOOST_CHECK(boost::any_cast<B2NeutrinoFlavor>(settings.At(B2Settings::NeutrinoFlavorSettings)) ==
                B2NeutrinoFlavor::kPrimaryAntiElectronNeutrino);
    BOOST_CHECK(!boost::any_cast<bool>(settings.At(B2Settings::MagneticField)));
    BOOST_CHECK(fs::exists(existing_conf_file_));
  }

  BOOST_AUTO_TEST_CASE(CreateConfigurationFile) {
    B2Configuration::CreateConfigurationFile(non_existing_conf_file_);
    BOOST_CHECK(fs::is_regular_file(non_existing_conf_file_));
    BOOST_CHECK_THROW(B2Configuration::CreateConfigurationFile(existing_conf_file_), std::runtime_error);
  }

BOOST_AUTO_TEST_SUITE_END()