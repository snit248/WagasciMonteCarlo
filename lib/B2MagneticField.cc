#include "B2MagneticField.hh"

// system includes
#include <iostream>
#include <fstream>
#include <string>

// Geant4 includes
#include <G4SystemOfUnits.hh>

B2MagneticField::B2MagneticField(const std::string& magfield_table_file_path) :
  xmin_(-2. * CLHEP::m), xmax_(2. * CLHEP::m),
  ymin_(-1.5 * CLHEP::m), ymax_(1.5 * CLHEP::m),
  zmin_(0 * CLHEP::m), zmax_(4 * CLHEP::m) {
  double ignore;
  std::ifstream data(magfield_table_file_path);
  for (std::size_t i = 0; i < xbins_; i++) {
    for (std::size_t j = 0; j < ybins_; j++) {
      data >> ignore >> ignore >> ignore >> bx_[i][j] >> by_[i][j] >> bz_[i][j];
    }
  }
}

TVector3 B2MagneticField::GetFieldValue(const TVector3 &point) const {

  Double_t factor = 1.0;
  TVector3 magnetic_field;
  magnetic_field.SetX(0. * CLHEP::tesla);
  magnetic_field.SetY(0. * CLHEP::tesla);
  magnetic_field.SetZ(0. * CLHEP::tesla);

  double x = point.X() - BABYMIND_POS_X;
  double y = point.Y() - BABYMIND_POS_Y;
  double z = point.Z() - (BABYMIND_POS_Z + BABYMIND_OFFSET_Z);

  double iron_module_z[33] = {7, 14.2, 21, 49.7, 60.7, 71.7,
                                95.9, 102.9, 113.7, 121, 145.2, 151.9,
                                163.1, 170, 193.8, 200.8, 207.8, 214.8,
                                243.7, 250.6, 257.8, 286.5, 293.7, 300.4,
                                307.4, 331.3, 338.3, 345.4, 352.1, 376,
                                383.3, 390.2, 397.1};

  //std::cout << "x = " << x << " y = " << y << " z = " << z << '\n';

  if (x > xmin_ && x < xmax_ && y > ymin_ && y < ymax_ && z > zmin_ && z < zmax_) {

    auto xint = (int) ((double) (x - xmin_) / (xmax_ - xmin_) * xbins_);
    auto yint = (int) ((double) (y - ymin_) / (ymax_ - ymin_) * ybins_);

    for (double i : iron_module_z) {
      if (z > i * CLHEP::cm - 3.0 * CLHEP::cm / 2 && z < i * CLHEP::cm + 3.0 * CLHEP::cm / 2) {
        // The minus sign is there to correct for the fact that the magnetic field simulation is reversed with
        // respect to the actual detector
        magnetic_field.SetX(-bx_[xint][yint] * CLHEP::tesla * factor);
        magnetic_field.SetY(by_[xint][yint] * CLHEP::tesla * factor);
        magnetic_field.SetZ(bz_[xint][yint] * CLHEP::tesla * factor);
	
	//std::cout << "x = " << x << " y = " << y << " z = " << z << " field x : " << -bx_[xint][yint] << " xint/yint = " << xint << " / " << yint << '\n';
        break;
      }
    }
  }
  return magnetic_field;
}


/*

TVector3 B2MagneticField::GetFieldValue(const TVector3 &point) const {
  
  TVector3 magnetic_field;
  magnetic_field.SetX(1.5 * CLHEP::tesla);
  magnetic_field.SetY(0.0 * CLHEP::tesla);
  magnetic_field.SetZ(0.0 * CLHEP::tesla);

  return magnetic_field;
}

*/


