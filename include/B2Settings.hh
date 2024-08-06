//
// Created by Giorgio Pintaudi on 7/8/20.
//

#ifndef WAGASCIBABYMINDMONTECARLO_SETTINGS_HPP
#define WAGASCIBABYMINDMONTECARLO_SETTINGS_HPP

#include <unordered_map>
#include <string>
#include <ostream>
#include <boost/any.hpp>
#include "B2Enum.hh"

/**
 * This class contains all the settings for the application. It is implemented with an unordered_map. The keys of
 * the map are elements of a Enum to enforce typos checking at compile time. The map values are boost::any objects,
 * so the user should remember to cast to the correct type when read-accessing them, using boost::any_cast<T>();
 */

  class B2Settings {

  public:

    /**
     * Enum that lists all the setting names. Used as a key in the SettingsCollection map.
     */
    typedef enum {
      Command,
      GUI,
      PrintVersion,
      InputFilePath,
      OutputFilePath,
#ifdef WITH_GDML
      OutputGdmlFilePath,
#endif
      GeometryDirPath,
      DebugLevel,
      LogFilePath,
      NeutrinoInteractionSettings,
      NeutrinoInteractionMaterial,
      WaterSettings,
      NeutrinoFlavorSettings,
      MagneticField,
      MichelElectrons,
      SecondaryTracks,
      NumberOfSpills,
      CosmicMuons,
      PencilBeam,
      PencilBeamRandomDirection,
      PencilBeamParticlePdg,
      PencilBeamMomentum,
      PencilBeamX,
      PencilBeamY,
      PencilBeamZ,
      PencilBeamAngleTop,
      PencilBeamAngleSide,
      NinjaKinkStudy,
      KinkFilePath
    } B2SettingName;

  private:
    typedef std::unordered_map<B2SettingName, boost::any, EnumClassHash> SettingCollection;

    SettingCollection settings_; ///> Unordered map containing all the settings

  public:
    /**
     * Get read/write access to the settings using the [] operator. If the setting is not found an empty setting value
     * is created.
     * @param name setting name
     * @return setting value (empty string if name is not found)
     */
    boost::any &operator[](const B2SettingName &name);

    /**
     * Get read/write access to the settings using the at method. If the setting is not found a std::out_of_range
     * exception is thrown.
     * @param name setting name
     * @return setting value
     */
    boost::any &At(const B2SettingName &name);

    const boost::any &At(const B2SettingName &name) const;

    /**
     * Print the settings to the output stream formatted as <name> = <value>. Each line is separated by line break.
     * @param os output stream
     * @param obj settings object
     * @return output stream
     */
    friend std::ostream &operator<<(std::ostream &os, const B2Settings &obj);


    /** Return true if the setting with name *name* exists.
     *
     * @param name setting name
     * @return true if setting exists otherwise false
     */
    bool Has(const B2SettingName &name);

    bool Has(const B2SettingName &name) const;
  };

  std::ostream &operator<<(std::ostream &os, const B2Settings &obj);

#endif //WAGASCIBABYMINDMONTECARLO_SETTINGS_HPP
