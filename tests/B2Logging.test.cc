//
// Created by Giorgio Pintaudi on 7/10/20.
//

#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE B2Logging

#include <fstream>
#include <streambuf>

#include <wordexp.h>

#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/attributes/named_scope.hpp>

#include "B2Logging.hh"
#include "B2Configuration.hh"

namespace fs = boost::filesystem;

void remove_all_with_ext(const fs::path &p, const std::string &ext) {
  if (fs::exists(p) && fs::is_directory(p)) {
    fs::directory_iterator end;
    for (fs::directory_iterator it(p); it != end; ++it) {
      try {
        if (fs::is_regular_file(it->status()) && (it->path().extension().compare(ext) == 0)) {
          fs::remove(it->path());
        }
      } catch (const std::exception &ex) {}
    }
  }
}

fs::path find_first_with_ext(const fs::path &p, const std::string &ext) {
  if (fs::exists(p) && fs::is_directory(p)) {
    fs::directory_iterator end;
    for (fs::directory_iterator it(p); it != end; ++it) {
      try {
        if (fs::is_regular_file(it->status()) && (it->path().extension().compare(ext) == 0)) {
          return it->path();
        }
      } catch (const std::exception &ex) {}
    }
  }
  return {};
}

struct LoggingTestFixture {

  fs::path logfile_ = "test.log";
  B2Settings settings_{};

  LoggingTestFixture() {
    remove_all_with_ext(fs::current_path(), ".log");
    wordexp_t word_exp{};
    std::string cli_arguments("program_name -p " + logfile_.string() + " -l info");
    wordexp(cli_arguments.c_str(), &word_exp, 0);
    B2Configuration configuration(static_cast<int>(word_exp.we_wordc), word_exp.we_wordv);
    settings_ = configuration.GetSettings();
    wordfree(&word_exp);
  }

  ~LoggingTestFixture() {
    remove_all_with_ext(fs::current_path(), ".log");
  }
};

BOOST_FIXTURE_TEST_SUITE(LoggingTest, LoggingTestFixture)

  static void Test() {
    BOOST_LOG_TRIVIAL(info) << "Info Log in Test()";
  }

  BOOST_AUTO_TEST_CASE(Logging) {

    init_logging(settings_);
    std::string message = "This is an informational severity message";
    BOOST_LOG_TRIVIAL(info) << message;
    Test();

    auto logfile_path = find_first_with_ext(fs::current_path(), ".log");
    BOOST_CHECK(fs::exists(logfile_path));
    std::ifstream logfile(logfile_path.string());
    std::string log((std::istreambuf_iterator<char>(logfile)), std::istreambuf_iterator<char>());
    BOOST_CHECK(log.find(message) != std::string::npos);
  }

BOOST_AUTO_TEST_SUITE_END()