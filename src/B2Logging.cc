//
// Created by Giorgio Pintaudi on 7/10/20.
//

#include "B2Logging.hh"

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>

#include "B2Settings.hh"

namespace logging = boost::log;
namespace keywords = boost::log::keywords;
namespace express = boost::log::expressions;

void preinit_logging() {
  logging::core::get()->set_filter
      (
          logging::trivial::severity >= logging::trivial::warning
      );
}

void init_logging(const B2Settings &settings) {

  // Remove all sinks

  logging::core::get()->remove_all_sinks();

  // Common attributes

  logging::add_common_attributes();

  // Severity level

  logging::register_simple_formatter_factory<logging::trivial::severity_level, char>("Severity");

  logging::trivial::severity_level level;
  auto level_string = boost::any_cast<std::string>(settings.At(B2Settings::DebugLevel));
  if (level_string == "trace")
    level = logging::trivial::trace;
  else if (level_string == "debug")
    level = logging::trivial::debug;
  else if (level_string == "info")
    level = logging::trivial::info;
  else if (level_string == "warning")
    level = logging::trivial::warning;
  else if (level_string == "error")
    level = logging::trivial::error;
  else if (level_string == "fatal")
    level = logging::trivial::fatal;
  else
    throw std::invalid_argument("level string not recognized : " + level_string);
    
  logging::core::get()->set_filter
      (
          logging::trivial::severity >= level
      );

  // Log formatter
  // [TimeStamp] [ThreadId] [Severity Level] Log message
  auto fmt_time_stamp = express::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f");
  auto fmt_thread_id = express::attr<logging::attributes::current_thread_id::value_type>("ThreadID");
  auto fmt_severity = express::attr<logging::trivial::severity_level>("Severity");
  logging::formatter log_format = express::format("[%1%] (%2%) [%3%] %4%")
                                  % fmt_time_stamp % fmt_thread_id % fmt_severity % express::smessage;

  // Console sink
  auto console_sink = logging::add_console_log(std::clog);
  console_sink->set_formatter(log_format);

  // File sink
  std::string filepath = boost::any_cast<std::string>(settings.At(B2Settings::LogFilePath));
  auto start_pos = filepath.find(".log");
  if(start_pos != std::string::npos)
    filepath.replace(start_pos, filepath.length(), "_%Y-%m-%d.%N.log");
  auto fs_sink = boost::log::add_file_log(
      boost::log::keywords::file_name = filepath,
      boost::log::keywords::rotation_size = 10 * 1024 * 1024,
      boost::log::keywords::min_free_space = 30 * 1024 * 1024,
      boost::log::keywords::open_mode = std::ios_base::app);
  fs_sink->set_formatter(log_format);
  fs_sink->locked_backend()->auto_flush(true);
}