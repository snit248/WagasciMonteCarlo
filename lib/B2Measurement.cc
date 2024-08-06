//
// Created by Giorgio Pintaudi on 8/5/20.
//

#include "B2Measurement.hh"
#include "B2Const.hh"

////////////////////////////////////////////////////////////// B2Measurement1D

B2Measurement1D::B2Measurement1D() :
    value_((Double_t) B2_NON_INITIALIZED_VALUE),
    error_((Double_t) B2_NON_INITIALIZED_VALUE) {}

Double_t B2Measurement1D::GetValue() const {
  return value_;
}

Double_t B2Measurement1D::GetError() const {
  return error_;
}

void B2Measurement1D::SetValue(Double_t v) {
  value_ = v;
}

void B2Measurement1D::SetError(Double_t e) {
  error_ = e;
}

void B2Measurement1D::Clear(Option_t *option) {
  value_ = B2_NON_INITIALIZED_VALUE;
  error_ = B2_NON_INITIALIZED_VALUE;
  TObject::Clear(option);
}

void B2Measurement1D::Set(Double_t v, Double_t e) {
  value_ = v;
  error_ = e;
}

B2Measurement1D::B2Measurement1D(Double_t val, Double_t err) : value_(val), error_(err) {}

std::ostream &operator<<(std::ostream &os, const B2Measurement1D &obj) {
  if (obj.IsInitialized()) {
    os << obj.value_;
    if (obj.error_ != B2_NON_INITIALIZED_VALUE)
      os << " ± " << obj.error_;
  } else {
    os << "not initialized";
  }
  return os;
}

B2Measurement1D::B2Measurement1D(Double_t val) : value_(val), error_(B2_NON_INITIALIZED_VALUE) {}

B2Measurement1D &B2Measurement1D::operator=(Double_t val) {
  value_ = val;
  return *this;
}

bool B2Measurement1D::IsInitialized() const {
  return value_ != B2_NON_INITIALIZED_VALUE;
}

B2Measurement1D &B2Measurement1D::operator+=(const B2Measurement1D &rhs) {
  SetValue(GetValue() + rhs.GetValue());
  SetError(std::sqrt(std::pow(rhs.GetError(), 2) + std::pow(GetError(), 2)));
  return *this;
}

B2Measurement1D &B2Measurement1D::operator-=(const B2Measurement1D &rhs) {
  SetValue(GetValue() - rhs.GetValue());
  SetError(std::sqrt(std::pow(rhs.GetError(), 2) + std::pow(GetError(), 2)));
  return *this;
}

ClassImp(B2Measurement1D)

////////////////////////////////////////////////////////////// B2Measurement2D

B2Measurement2D::B2Measurement2D() :
    value_((Double_t) B2_NON_INITIALIZED_VALUE, (Double_t) B2_NON_INITIALIZED_VALUE),
    error_((Double_t) B2_NON_INITIALIZED_VALUE, (Double_t) B2_NON_INITIALIZED_VALUE) {}

const TVector2 &B2Measurement2D::GetValue() const {
  return value_;
}

const TVector2 &B2Measurement2D::GetError() const {
  return error_;
}

TVector2 &B2Measurement2D::GetValue() {
  return value_;
}

TVector2 &B2Measurement2D::GetError() {
  return error_;
}

void B2Measurement2D::SetValue(Double_t x, Double_t y) {
  value_.SetX(x);
  value_.SetY(y);
}

void B2Measurement2D::SetValue(const TVector2 &val) {
  value_ = val;
}

void B2Measurement2D::SetError(const TVector2 &err) {
  error_ = err;
}

void B2Measurement2D::SetError(Double_t x, Double_t y) {
  error_.SetX(x);
  error_.SetY(y);
}

void B2Measurement2D::Clear(Option_t *option) {
  value_.Set((Double_t) B2_NON_INITIALIZED_VALUE, (Double_t) B2_NON_INITIALIZED_VALUE);
  error_.Set((Double_t) B2_NON_INITIALIZED_VALUE, (Double_t) B2_NON_INITIALIZED_VALUE);
  TObject::Clear(option);
}

void B2Measurement2D::Set(Double_t x, Double_t y, Double_t ex, Double_t ey) {
  value_.SetX(x);
  value_.SetY(y);
  error_.SetX(ex);
  error_.SetY(ey);
}

B2Measurement2D::B2Measurement2D(Double_t x, Double_t y, Double_t ex, Double_t ey) :
    value_(x, y), error_(ex, ey) {}

B2Measurement2D::B2Measurement2D(const TVector2 &val, const TVector2 &err) : value_(val), error_(err) {}

std::ostream &operator<<(std::ostream &os, const B2Measurement2D &obj) {
  if (obj.IsInitialized()) {
    os << obj.value_.X();
    if (obj.error_.X() != B2_NON_INITIALIZED_VALUE)
      os << " ± " << obj.error_.X();
    os << ", " << obj.value_.Y();
    if (obj.error_.Y() != B2_NON_INITIALIZED_VALUE)
      os << " ± " << obj.error_.Y();
  } else {
    os << "not initialized";
  }
  return os;
}

B2Measurement2D::B2Measurement2D(const TVector2 &val) :
    value_(val), error_(B2_NON_INITIALIZED_VALUE, B2_NON_INITIALIZED_VALUE) {}

B2Measurement2D &B2Measurement2D::operator=(const TVector2 &val) {
  value_ = val;
  return *this;
}

bool B2Measurement2D::IsInitialized() const {
  return value_.X() != B2_NON_INITIALIZED_VALUE ||
         value_.Y() != B2_NON_INITIALIZED_VALUE;
}

B2Measurement2D &B2Measurement2D::operator+=(const B2Measurement2D &rhs) {
  SetValue(GetValue() + rhs.GetValue());
  SetError(std::sqrt(std::pow(rhs.GetError().X(), 2) + std::pow(GetError().X(), 2)),
           std::sqrt(std::pow(rhs.GetError().Y(), 2) + std::pow(GetError().Y(), 2)));
  return *this;
}

B2Measurement2D &B2Measurement2D::operator-=(const B2Measurement2D &rhs) {
  SetValue(GetValue() - rhs.GetValue());
  SetError(std::sqrt(std::pow(rhs.GetError().X(), 2) + std::pow(GetError().X(), 2)),
           std::sqrt(std::pow(rhs.GetError().Y(), 2) + std::pow(GetError().Y(), 2)));
  return *this;
}

B2Measurement1D B2Measurement2D::Mag() const {
  B2Measurement1D mag;
  mag.SetValue(GetValue().Mod());
  double tmp = 0;
  tmp += std::pow(GetValue().X(), 2) * std::pow(GetError().X(), 2);
  tmp += std::pow(GetValue().Y(), 2) * std::pow(GetError().Y(), 2);
  mag.SetError(std::sqrt(tmp) / mag.GetValue());
  return mag;
}

ClassImp(B2Measurement2D)

////////////////////////////////////////////////////////////// B2Measurement3D

B2Measurement3D::B2Measurement3D() :
    value_((Double_t) B2_NON_INITIALIZED_VALUE,
           (Double_t) B2_NON_INITIALIZED_VALUE,
           (Double_t) B2_NON_INITIALIZED_VALUE),
    error_((Double_t) B2_NON_INITIALIZED_VALUE,
           (Double_t) B2_NON_INITIALIZED_VALUE,
           (Double_t) B2_NON_INITIALIZED_VALUE) {}

const TVector3 &B2Measurement3D::GetValue() const {
  return value_;
}

const TVector3 &B2Measurement3D::GetError() const {
  return error_;
}

void B2Measurement3D::SetValue(Double_t x, Double_t y, Double_t z) {
  value_.SetX(x);
  value_.SetY(y);
  value_.SetZ(z);
}

void B2Measurement3D::SetError(Double_t x, Double_t y, Double_t z) {
  error_.SetX(x);
  error_.SetY(y);
  error_.SetZ(z);
}

void B2Measurement3D::Clear(Option_t *option) {
  value_.SetXYZ((Double_t) B2_NON_INITIALIZED_VALUE,
                (Double_t) B2_NON_INITIALIZED_VALUE,
                (Double_t) B2_NON_INITIALIZED_VALUE);
  error_.SetXYZ((Double_t) B2_NON_INITIALIZED_VALUE,
                (Double_t) B2_NON_INITIALIZED_VALUE,
                (Double_t) B2_NON_INITIALIZED_VALUE);
  TObject::Clear(option);
}

void B2Measurement3D::Set(Double_t x, Double_t y, Double_t z, Double_t ex, Double_t ey, Double_t ez) {
  value_.SetX(x);
  value_.SetY(y);
  value_.SetZ(z);
  error_.SetX(ex);
  error_.SetY(ey);
  error_.SetZ(ez);
}

void B2Measurement3D::SetValue(const TVector3 &vec) {
  value_ = vec;
}

void B2Measurement3D::SetError(const TVector3 &vec) {
  error_ = vec;
}

void B2Measurement3D::Set(const TVector3 &val, const TVector3 &err) {
  value_ = val;
  error_ = err;
}

B2Measurement3D::B2Measurement3D(Double_t x, Double_t y, Double_t z, Double_t ex, Double_t ey, Double_t ez) :
    value_(x, y, z), error_(ex, ey, ez) {}

B2Measurement3D::B2Measurement3D(const TVector3 &val, const TVector3 &err) : value_(val), error_(err) {}

std::ostream &operator<<(std::ostream &os, const B2Measurement3D &obj) {
  if (obj.IsInitialized()) {
    os << obj.value_.X();
    if (obj.error_.X() != B2_NON_INITIALIZED_VALUE)
      os << " ± " << obj.error_.X();
    os << ", " << obj.value_.Y();
    if (obj.error_.Y() != B2_NON_INITIALIZED_VALUE)
      os << " ± " << obj.error_.Y();
    os << ", " << obj.value_.Z();
    if (obj.error_.Z() != B2_NON_INITIALIZED_VALUE)
      os << " ± " << obj.error_.Z();
  } else {
    os << "not initialized";
  }
  return os;
}

B2Measurement3D::B2Measurement3D(const TVector3 &val) :
    value_(val), error_(B2_NON_INITIALIZED_VALUE, B2_NON_INITIALIZED_VALUE, B2_NON_INITIALIZED_VALUE) {}

B2Measurement3D &B2Measurement3D::operator=(const TVector3 &val) {
  value_ = val;
  return *this;
}

bool B2Measurement3D::IsInitialized() const {
  return value_.X() != B2_NON_INITIALIZED_VALUE ||
         value_.Y() != B2_NON_INITIALIZED_VALUE ||
         value_.Z() != B2_NON_INITIALIZED_VALUE;
}

B2Measurement3D &B2Measurement3D::operator+=(const B2Measurement3D &rhs) {
  SetValue(GetValue() + rhs.GetValue());
  SetError(std::sqrt(std::pow(rhs.GetError().X(), 2) + std::pow(GetError().X(), 2)),
           std::sqrt(std::pow(rhs.GetError().Y(), 2) + std::pow(GetError().Y(), 2)),
           std::sqrt(std::pow(rhs.GetError().Z(), 2) + std::pow(GetError().Z(), 2)));
  return *this;
}

B2Measurement3D &B2Measurement3D::operator-=(const B2Measurement3D &rhs) {
  SetValue(GetValue() - rhs.GetValue());
  SetError(std::sqrt(std::pow(rhs.GetError().X(), 2) + std::pow(GetError().X(), 2)),
           std::sqrt(std::pow(rhs.GetError().Y(), 2) + std::pow(GetError().Y(), 2)),
           std::sqrt(std::pow(rhs.GetError().Z(), 2) + std::pow(GetError().Z(), 2)));
  return *this;
}

B2Measurement1D B2Measurement3D::Mag() const {
  B2Measurement1D mag;
  mag.SetValue(GetValue().Mag());
  double tmp = 0;
  for (int i = 0; i < 3; ++i) {
    tmp += std::pow(GetValue()[i], 2) * std::pow(GetError()[i], 2);
  }
  mag.SetError(std::sqrt(tmp) / mag.GetValue());
  return mag;
}

ClassImp(B2Measurement3D)

////////////////////////////////////////////////////////////// B2VectorDoubleReadout

template<typename T>
B2VectorDoubleReadout<T>::B2VectorDoubleReadout() {
  value[0] = B2_NON_INITIALIZED_VALUE;
  value[1] = B2_NON_INITIALIZED_VALUE;
  error[0] = B2_NON_INITIALIZED_VALUE;
  error[1] = B2_NON_INITIALIZED_VALUE;
}

template<typename T>
const T &B2VectorDoubleReadout<T>::GetValue(B2Readout readout) const {
  return value[READOUT_MAP.at(readout)];
}

template<typename T>
const T &B2VectorDoubleReadout<T>::GetError(B2Readout readout) const {
  return error[READOUT_MAP.at(readout)];
}

template<typename T>
void B2VectorDoubleReadout<T>::Set(B2Readout readout, T x_value, T x_error) {
  value[READOUT_MAP.at(readout)] = x_value;
  error[READOUT_MAP.at(readout)] = x_error;
}

template<typename T>
void B2VectorDoubleReadout<T>::Set(B2Readout readout, T x_value) {
  this->Set(readout, x_value, T(B2_NON_INITIALIZED_VALUE));
}

template<typename T>
const T &B2VectorDoubleReadout<T>::GetMinimumValue() const {
  if (value[0] == B2_NON_INITIALIZED_VALUE) return value[1];
  else if (value[1] == B2_NON_INITIALIZED_VALUE) return value[0];
  else return value[0] < value[1] ? value[0] : value[1];
}

template<typename T>
const T &B2VectorDoubleReadout<T>::GetMaximumValue() const {
  if (value[0] == B2_NON_INITIALIZED_VALUE) return value[1];
  else if (value[1] == B2_NON_INITIALIZED_VALUE) return value[0];
  else return value[0] > value[1] ? value[0] : value[1];
}

templateClassImp(B2VectorDoubleReadout)

// Explicit instantiation for Int_t and Double_t and TVector3
template
class B2VectorDoubleReadout<Int_t>;

template
class B2VectorDoubleReadout<Double_t>;

template
class B2VectorDoubleReadout<B2Vector3>;

////////////////////////////////////////////////////////////// B2Energy

B2Energy::B2Energy() : B2Measurement1D() {}

B2Energy::B2Energy(Double_t val, Double_t err) : B2Measurement1D(val, err) {}

B2Energy::B2Energy(Double_t val) : B2Measurement1D(val, B2_NON_INITIALIZED_VALUE) {}

B2Energy &B2Energy::operator=(Double_t val) {
  B2Measurement1D::operator=(val);
  return *this;
}

ClassImp(B2Energy)

////////////////////////////////////////////////////////////// B2Momentum

B2Momentum::B2Momentum() : B2Measurement3D() {}

B2Momentum::B2Momentum(Double_t x, Double_t y, Double_t z, Double_t ex, Double_t ey, Double_t ez) :
    B2Measurement3D(x, y, z, ex, ey, ez) {}

B2Momentum::B2Momentum(const TVector3 &val, const TVector3 &err) : B2Measurement3D(val, err) {}

B2Momentum::B2Momentum(const TVector3 &val) : B2Measurement3D(val) {}

B2Momentum &B2Momentum::operator=(const TVector3 &val) {
  B2Measurement3D::operator=(val);
  return *this;
}

ClassImp(B2Momentum)

////////////////////////////////////////////////////////////// B2Angle

B2Angle::B2Angle() : B2Measurement1D() {}

B2Angle::B2Angle(Double_t val, Double_t err) : B2Measurement1D(val, err) {}

B2Angle::B2Angle(Double_t val) : B2Measurement1D(val) {}

B2Angle &B2Angle::operator=(Double_t val) {
  B2Measurement1D::operator=(val);
  return *this;
}

ClassImp(B2Angle)

////////////////////////////////////////////////////////////// B2Time

B2Time::B2Time() : B2Measurement1D() {}

B2Time::B2Time(Double_t val, Double_t err) : B2Measurement1D(val, err) {}

B2Time::B2Time(Double_t val) : B2Measurement1D(val) {}

B2Time &B2Time::operator=(Double_t val) {
  B2Measurement1D::operator=(val);
  return *this;
}

ClassImp(B2Time)

////////////////////////////////////////////////////////////// B2Distance

B2Distance::B2Distance() : B2Measurement1D() {}

B2Distance::B2Distance(Double_t val, Double_t err) : B2Measurement1D(val, err) {}

B2Distance::B2Distance(Double_t val) : B2Measurement1D(val) {}

B2Distance &B2Distance::operator=(Double_t val) {
  B2Measurement1D::operator=(val);
  return *this;
}

B2Distance::B2Distance(const B2Measurement1D &obj) {
  value_ = obj.GetValue();
  error_ = obj.GetError();
}

ClassImp(B2Distance)

////////////////////////////////////////////////////////////// B2Position

B2Position::B2Position() : B2Measurement3D() {}

B2Position::B2Position(Double_t x, Double_t y, Double_t z, Double_t ex, Double_t ey, Double_t ez) :
    B2Measurement3D(x, y, z, ex, ey, ez) {}

B2Position::B2Position(const TVector3 &val, const TVector3 &err) : B2Measurement3D(val, err) {}

B2Position::B2Position(const TVector3 &val) : B2Measurement3D(val) {}

B2Position &B2Position::operator=(const TVector3 &val) {
  B2Measurement3D::operator=(val);
  return *this;
}

B2Position::B2Position(const B2Measurement3D &obj) {
  value_ = obj.GetValue();
  error_ = obj.GetError();
}

ClassImp(B2Position)

////////////////////////////////////////////////////////////// B2Direction

B2Direction::B2Direction() : B2Measurement3D() {}

void B2Direction::SetValue(Double_t x, Double_t y, Double_t z) {
  B2Direction::SetValue(TVector3(x, y, z));
}

void B2Direction::SetValue(const TVector3 &value) {
  B2Measurement3D::SetValue(value);
  if (std::fabs(value.Mag() - 1) > 0.01) {
    std::stringstream ss;
    ss << "Direction verson is not of unit magnitude : X = " << value.X() << ", Y = " << value.Y()
       << ", Z = " << value.Z();
    throw std::invalid_argument(ss.str());
  }
}

void B2Direction::Set(const TVector3 &val, const TVector3 &err) {
  B2Direction::SetValue(val);
  B2Direction::SetError(err);
}

B2Direction::B2Direction(const TVector3 &val, const TVector3 &err) {
  B2Direction::Set(val, err);
}

B2Direction::B2Direction(const TVector3 &val) {
  B2Direction::Set(val, TVector3(B2_NON_INITIALIZED_VALUE, B2_NON_INITIALIZED_VALUE, B2_NON_INITIALIZED_VALUE));
}

B2Direction::B2Direction(Double_t x, Double_t y, Double_t z, Double_t ex, Double_t ey, Double_t ez) {
  B2Direction::SetValue(x, y, z);
  B2Direction::SetError(ex, ey, ez);
}

B2Direction &B2Direction::operator=(const TVector3 &val) {
  B2Measurement3D::operator=(val);
  return *this;
}

B2Angle B2Direction::ToAngle() const {
  TVector3 zeta(0, 0, 1);
  return B2Angle(180 / CLHEP::pi * GetValue().Angle(zeta));
}

B2ViewAngle B2Direction::ToViewAngle() const {
  Double_t theta = std::asin(GetValue().y());
  Double_t phi = (180 / CLHEP::pi) * (std::acos(GetValue().z() / std::cos(theta)));
  theta *= 180 / CLHEP::pi;
  B2ViewAngle angle;
  angle.SetPolarAngle(theta);
  angle.SetAzimuthalAngle(phi);
  return angle;
}

ClassImp(B2Direction)

////////////////////////////////////////////////////////////// B2ViewAngle

B2ViewAngle::B2ViewAngle() : B2Measurement2D() {}

B2ViewAngle::B2ViewAngle(Double_t theta, Double_t phi, Double_t e_theta, Double_t e_phi) :
    B2Measurement2D(theta, phi, e_theta, e_phi) {}

B2ViewAngle::B2ViewAngle(const TVector2 &val, const TVector2 &err) : B2Measurement2D(val, err) {}

B2ViewAngle &B2ViewAngle::operator=(const TVector2 &val) {
  B2Measurement2D::operator=(val);
  return *this;
}

void B2ViewAngle::SetPolarAngle(Double_t theta) {
  value_.SetX(theta);
}

void B2ViewAngle::SetPolarAngle(Double_t theta, Double_t e_theta) {
  value_.SetX(theta);
  error_.SetX(e_theta);
}

Double_t B2ViewAngle::GetPolarAngle() const {
  return value_.X();
}

Double_t B2ViewAngle::GetPolarAngleError() const {
  return error_.Y();
}

void B2ViewAngle::SetAzimuthalAngle(Double_t phi) {
  value_.SetY(phi);
}

void B2ViewAngle::SetAzimuthalAngle(Double_t phi, Double_t e_phi) {
  value_.SetY(phi);
  error_.SetY(e_phi);
}

Double_t B2ViewAngle::GetAzimuthalAngle() const {
  return value_.Y();
}

Double_t B2ViewAngle::GetAzimuthalAngleError() const {
  return error_.Y();
}

std::ostream &operator<<(std::ostream &os, const B2ViewAngle &obj) {
  os << "top view angle " << obj.GetAzimuthalAngle() << " deg, side view angle " << obj.GetPolarAngle() << " deg";
  return os;
}


ClassImp(B2ViewAngle)

////////////////////////////////////////////////////////////// B2Vector3

std::ostream &operator<<(std::ostream &os, const B2Vector3 &obj) {
  os << "(" << obj.X() << ", " << obj.Y() << ", " << obj.Z() << ")";
  return os;
}

B2Vector3::B2Vector3(double x, double y, double z) : TVector3(x, y, z) {}

B2Vector3::B2Vector3() : TVector3(B2_NON_INITIALIZED_VALUE, B2_NON_INITIALIZED_VALUE, B2_NON_INITIALIZED_VALUE) {}

B2Vector3::B2Vector3(double i) : TVector3(i, i, i) {}

B2Vector3 &B2Vector3::operator=(double rhs) {
  this->SetX(rhs);
  this->SetY(rhs);
  this->SetZ(rhs);
  return *this;
}

ClassImp(B2Vector3)
