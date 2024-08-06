//
// Created by Giorgio Pintaudi on 7/8/20.
//

#ifndef WAGASCIBABYMINDMONTECARLO_CONFIGURATION_HPP
#define WAGASCIBABYMINDMONTECARLO_CONFIGURATION_HPP

#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include "B2Settings.hh"

/**
 * Class to read the initial configuration from the shell arguments or from a ini file. The shell arguments have
 * priority over the ones from the ini file. If a parameter is not found, a default value is always assumed. In this
 * sense this application does not need any particular initial configuration to work.
 *
 * @warning However, if you do not specify any configuration the output might not make sense (if the connected GPIO
 * pins are disabled for example)
 *
 * If a configuration file is not given or found, a new configuration file can be created. The default location of the
 * configuration file is controlled by the DEFAULT_CONFIGURATION_FILE macro that can be optionally set during
 * compilation.
 *
 * This class is implemented using the boost program_options library. Its only output is an object of the Settings
 * class @see[Settings] that can then be injected into all other classes of the application.
 */

namespace fs = boost::filesystem;
namespace po = boost::program_options;

const extern fs::path DEFAULT_CONFIGURATION_FILE;
const extern fs::path DEFAULT_LOG_FILE;
const extern fs::path DEFAULT_GEOMETRY_DIRECTORY;
const extern fs::path DEFAULT_OUTPUT_FILE;
const extern fs::path DEFAULT_GDML_FILE;
const extern fs::path DEFAULT_INPUT_FILE;
const extern fs::path DEFAULT_KINK_FILE;
const extern fs::path MAGFIELD_TABLE_FILE;

  class B2Configuration {

  private:
    ///< path to the configuration ini file
    fs::path ini_path_{};
    ///< if true a new configuration file will with default values will be created if not found.
    bool create_;
    ///< list of configuration variables
    po::variables_map vm_{};
    ///< description of configuration variables
    po::options_description desc_{" allowed options", 200};

    /**
     * Populate the description of configuration variables. It is here that the default values are stored.
     */
    void PopulateOptionsDescription();

  public:

    /**
     * Read shell arguments and configuration file. The configuration file location can be the default one or can be set
     * through the command line arguments.
     *
     * @param argc Number of arguments
     * @param argv List of arguments
     * @param create If set to true a new configuration file will be created if not found
     * @param settings Reference to settings object that will be overwritten with the initial configuration
     * */

    B2Configuration(int argc, char *argv[], bool create = false);

    /**
     * Read configuration file only.
     *
     * @param path to the configuration file
     * @param create If set to true a new configuration file will be created if not found
     */
    explicit B2Configuration(fs::path &path, bool create = false);

    /**
     * Empty constructor does not read anything. The settings will be empty.
     *
     * @param create If set to true a new configuration file will be created if not found
     */

    explicit B2Configuration(bool create = false);

    /**
      * Read shell arguments and store them into a boost::program_options::variables_map
      *
      * @param argc Number of arguments
      * @param argv List of arguments
      * @return parsed variables in the form of a po::variables_map
      * */

    void ReadShellArguments(int argc, char **argv);

    /**
     * Append the information found in the configuration file to the boost::program_options::variables_map
     *
     * @param path to the configuration file
     */

    void ReadConfigurationFile(fs::path &path);

    /**
     * Create a configuration file at ini_path_ and fill it with the default values
     *
     * @param path to the configuration file
     */

    static void CreateConfigurationFile(fs::path &path);

    /**
     * Return a settings object containing the state of the configuration
     *
     * @return settings object
     */
    B2Settings GetSettings();
  };


#endif //WAGASCIBABYMINDMONTECARLO_CONFIGURATION_HPP
