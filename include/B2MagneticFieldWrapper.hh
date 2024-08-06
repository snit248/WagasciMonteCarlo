#ifndef WAGASCIBABYMINDMONTECARLO_B2MAGNETICFIELDWRAPPER_HH
#define WAGASCIBABYMINDMONTECARLO_B2MAGNETICFIELDWRAPPER_HH

// system includes
#include <string>

// Geant4 includes
#include "B2MagneticField.hh"
#include <G4MagneticField.hh>
#include <G4SystemOfUnits.hh>

class B2MagneticFieldWrapper : public G4MagneticField {

public:

  explicit B2MagneticFieldWrapper(const std::string &magfield_table_file_path);

  void GetFieldValue(const G4double point[3], G4double *magnetic_field) const override;

private:

  B2MagneticField magnetic_field_;
};

#endif // WAGASCIBABYMINDMONTECARLO_B2MAGNETICFIELDWRAPPER_HH