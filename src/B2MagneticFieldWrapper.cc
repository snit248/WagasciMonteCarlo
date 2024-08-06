#include "B2MagneticFieldWrapper.hh"

// system includes
#include <string>

B2MagneticFieldWrapper::B2MagneticFieldWrapper(const std::string& magfield_table_file_path) :
  magnetic_field_(magfield_table_file_path) {}

void B2MagneticFieldWrapper::GetFieldValue(const G4double point[3], G4double *magnetic_field) const {
  const TVector3 vec = magnetic_field_.GetFieldValue(point);
  magnetic_field[0] = vec.X();
  magnetic_field[1] = vec.Y();
  magnetic_field[2] = vec.Z();
}

