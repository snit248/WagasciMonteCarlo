//
// Created by Giorgio Pintaudi on 8/5/20.
//

#ifndef WAGASCIBABYMINDMONTECARLO_B2MEASUREMENT_HH
#define WAGASCIBABYMINDMONTECARLO_B2MEASUREMENT_HH

// system includes
#include <sstream>

// ROOT includes
#include <TObject.h>
#include <TVector3.h>

// project includes
#include "B2Enum.hh"


/**
 * Virtual class for generic one dimensional measurement
 */
class B2Measurement1D : public TObject {

protected:
  Double_t value_;
  Double_t error_;

public:
  B2Measurement1D();

  B2Measurement1D(Double_t val, Double_t err);

  explicit B2Measurement1D(Double_t val);

  virtual B2Measurement1D &operator=(Double_t val);

  ~B2Measurement1D() override = default;

  virtual Double_t GetValue() const;

  virtual Double_t GetError() const;

  virtual void SetValue(Double_t v);

  virtual void SetError(Double_t e);

  virtual void Set(Double_t v, Double_t e);

  friend std::ostream &operator<<(std::ostream &os, const B2Measurement1D &obj);

  void Clear(Option_t *option) override;

  inline friend bool operator==(const B2Measurement1D &lhs, const B2Measurement1D &rhs) {
    return lhs.value_ == rhs.value_ && lhs.error_ == rhs.error_;
  }

  B2Measurement1D &operator+=(const B2Measurement1D &rhs);

  B2Measurement1D &operator-=(const B2Measurement1D &rhs);

  inline friend B2Measurement1D operator+(B2Measurement1D lhs, const B2Measurement1D &rhs) {
    lhs += rhs;
    return lhs;
  }

  inline friend B2Measurement1D operator-(B2Measurement1D lhs, const B2Measurement1D &rhs) {
    lhs -= rhs;
    return lhs;
  }

  bool IsInitialized() const;

ClassDefOverride(B2Measurement1D, 1)

};

/**
 * Virtual class for generic three dimensional measurement
 */
class B2Measurement2D : public TObject {

protected:
  TVector2 value_;
  TVector2 error_;

public:
  B2Measurement2D();

  B2Measurement2D(Double_t x, Double_t y, Double_t ex, Double_t ey);

  B2Measurement2D(const TVector2 &val, const TVector2 &err);

  explicit B2Measurement2D(const TVector2 &val);

  virtual B2Measurement2D &operator=(const TVector2 &val);

  ~B2Measurement2D() override = default;

  virtual const TVector2 &GetValue() const;

  virtual const TVector2 &GetError() const;

  virtual TVector2 &GetValue();

  virtual TVector2 &GetError();

  virtual void SetValue(const TVector2 &val);

  virtual void SetError(const TVector2 &val);

  virtual void SetValue(Double_t x, Double_t y);

  virtual void SetError(Double_t x, Double_t y);

  virtual void Set(Double_t x, Double_t y, Double_t ex, Double_t ey);

  friend std::ostream &operator<<(std::ostream &os, const B2Measurement2D &obj);

  B2Measurement2D &operator+=(const B2Measurement2D &rhs);

  B2Measurement2D &operator-=(const B2Measurement2D &rhs);

  void Clear(Option_t *option) override;

  inline friend bool operator==(const B2Measurement2D &lhs, const B2Measurement2D &rhs) {
    return lhs.value_.X() == rhs.value_.X() &&
           lhs.value_.Y() == rhs.value_.Y() &&
           lhs.error_.X() == rhs.error_.X() &&
           lhs.error_.Y() == rhs.error_.Y();
  }

  inline friend B2Measurement2D operator+(B2Measurement2D lhs, const B2Measurement2D &rhs) {
    lhs += rhs;
    return lhs;
  }

  inline friend B2Measurement2D operator-(B2Measurement2D lhs, const B2Measurement2D &rhs) {
    lhs -= rhs;
    return lhs;
  }

  bool IsInitialized() const;

  virtual B2Measurement1D Mag() const;

ClassDefOverride(B2Measurement2D, 1)

};

/**
 * Virtual class for generic three dimensional measurement
 */
class B2Measurement3D : public TObject {

protected:
  TVector3 value_;
  TVector3 error_;

public:
  B2Measurement3D();

  B2Measurement3D(Double_t x, Double_t y, Double_t z, Double_t ex, Double_t ey, Double_t ez);

  B2Measurement3D(const TVector3 &val, const TVector3 &err);

  explicit B2Measurement3D(const TVector3 &val);

  virtual B2Measurement3D &operator=(const TVector3 &val);

  ~B2Measurement3D() override = default;

  virtual const TVector3 &GetValue() const;

  virtual const TVector3 &GetError() const;

  virtual void SetValue(Double_t x, Double_t y, Double_t z);

  virtual void SetError(Double_t x, Double_t y, Double_t z);

  virtual void SetValue(const TVector3 &vec);

  virtual void SetError(const TVector3 &vec);

  virtual void Set(Double_t x, Double_t y, Double_t z, Double_t ex, Double_t ey, Double_t ez);

  virtual void Set(const TVector3 &val, const TVector3 &err);

  friend std::ostream &operator<<(std::ostream &os, const B2Measurement3D &obj);

  B2Measurement3D &operator+=(const B2Measurement3D &rhs);

  B2Measurement3D &operator-=(const B2Measurement3D &rhs);

  void Clear(Option_t *option) override;

  inline friend bool operator==(const B2Measurement3D &lhs, const B2Measurement3D &rhs) {
    return lhs.value_.X() == rhs.value_.X() &&
           lhs.value_.Y() == rhs.value_.Y() &&
           lhs.value_.Z() == rhs.value_.Z() &&
           lhs.error_.X() == rhs.error_.X() &&
           lhs.error_.Y() == rhs.error_.Y() &&
           lhs.error_.Z() == rhs.error_.Z();
  }

  inline friend B2Measurement3D operator+(B2Measurement3D lhs, const B2Measurement3D &rhs) {
    lhs += rhs;
    return lhs;
  }

  inline friend B2Measurement3D operator-(B2Measurement3D lhs, const B2Measurement3D &rhs) {
    lhs -= rhs;
    return lhs;
  }

  virtual B2Measurement1D Mag() const;

  bool IsInitialized() const;

ClassDefOverride(B2Measurement3D, 1)
};

template<typename T>
class B2VectorDoubleReadout : public TObject {

protected:
  T value[2];
  T error[2];

public:
  B2VectorDoubleReadout();

  ~B2VectorDoubleReadout() override = default;

  const T &GetValue(B2Readout readout) const;

  const T &GetError(B2Readout readout) const;

  const T &GetMinimumValue() const;

  const T &GetMaximumValue() const;

  void Set(B2Readout readout, T x_value, T x_error);

  void Set(B2Readout readout, T x_value);

  friend std::ostream &operator<<(std::ostream &os, const B2VectorDoubleReadout &obj) {
    if (obj.value[0] != B2_NON_INITIALIZED_VALUE)
      os << obj.value[0];
    else
      os << "not initialized";
    if (obj.error[0] != B2_NON_INITIALIZED_VALUE)
      os << " ± " << obj.error[0];
    os << ", ";
    if (obj.value[1] != B2_NON_INITIALIZED_VALUE)
      os << obj.value[1];
    else
      os << "not initialized";
    if (obj.error[1] != B2_NON_INITIALIZED_VALUE)
      os << " ± " << obj.error[1];
    return os;
  }

  inline friend bool operator==(const B2VectorDoubleReadout &lhs, const B2VectorDoubleReadout &rhs) {
    return lhs.value[0] == rhs.value[0] &&
           lhs.value[1] == rhs.value[1] &&
           lhs.error[0] == rhs.error[0] &&
           lhs.error[1] == rhs.error[1];
  }

ClassDefOverride(B2VectorDoubleReadout, 1)
};

/**
 * Energy in MeV
 */
class B2Energy : public B2Measurement1D {
public:
  B2Energy();

  B2Energy(Double_t val, Double_t err);

  explicit B2Energy(Double_t val);

  B2Energy &operator=(Double_t val) override;

  ~B2Energy() override = default;

ClassDefOverride(B2Energy, 1)
};

/**
 * Momentum in MeV/c
 */
class B2Momentum : public B2Measurement3D {
public:
  B2Momentum();

  B2Momentum(Double_t x, Double_t y, Double_t z, Double_t ex, Double_t ey, Double_t ez);

  B2Momentum(const TVector3 &val, const TVector3 &err);

  explicit B2Momentum(const TVector3 &val);

  B2Momentum &operator=(const TVector3 &val) override;

  ~B2Momentum() override = default;

ClassDefOverride(B2Momentum, 1)
};

/**
 * Angle in degrees with respect to the zeta axis
 */
class B2Angle : public B2Measurement1D {
public:
  B2Angle();

  B2Angle(Double_t val, Double_t err);

  explicit B2Angle(Double_t val);

  B2Angle &operator=(Double_t val) override;

  ~B2Angle() override = default;

ClassDefOverride(B2Angle, 1)
};

/**
 * Time in ns
 */
class B2Time : public B2Measurement1D {
public:
  B2Time();

  B2Time(Double_t val, Double_t err);

  explicit B2Time(Double_t val);

  B2Time &operator=(Double_t val) override;

  ~B2Time() override = default;

ClassDefOverride(B2Time, 1)
};

/**
 * Distance in mm
 */
class B2Distance : public B2Measurement1D {
public:
  B2Distance();

  explicit B2Distance(const B2Measurement1D &obj);

  B2Distance(Double_t val, Double_t err);

  explicit B2Distance(Double_t val);

  B2Distance &operator=(Double_t val) override;

  ~B2Distance() override = default;

ClassDefOverride(B2Distance, 1)
};

/**
 * Position vector in mm
 */
class B2Position : public B2Measurement3D {
public:
  B2Position();

  explicit B2Position(const B2Measurement3D &obj);

  B2Position(Double_t x, Double_t y, Double_t z, Double_t ex, Double_t ey, Double_t ez);

  B2Position(const TVector3 &val, const TVector3 &err);

  explicit B2Position(const TVector3 &val);

  B2Position &operator=(const TVector3 &val) override;

  ~B2Position() override = default;

  inline friend B2Position operator+(B2Position lhs, const B2Position &rhs) {
    lhs += rhs;
    return lhs;
  }

  inline friend B2Position operator-(B2Position lhs, const B2Position &rhs) {
    lhs -= rhs;
    return lhs;
  }

ClassDefOverride(B2Position, 1)
};

/**
 * 2D Angles in degrees. The polar angle theta is the angle from the zeta axis in side view, while the azimuthal angle
 * phi is the angle from the zeta axis in top view. Both angles are increasing when rotating in anticlockwise
 * direction and go from zero to 360 degrees.
 */
class B2ViewAngle : public B2Measurement2D {
public:
  B2ViewAngle();

  B2ViewAngle(Double_t theta, Double_t phi, Double_t e_theta, Double_t e_phi);

  B2ViewAngle(const TVector2 &val, const TVector2 &err);

  void SetPolarAngle(Double_t theta);

  void SetPolarAngle(Double_t theta, Double_t e_theta);

  Double_t GetPolarAngle() const;

  Double_t GetPolarAngleError() const;

  void SetAzimuthalAngle(Double_t phi);

  void SetAzimuthalAngle(Double_t phi, Double_t e_phi);

  Double_t GetAzimuthalAngle() const;

  Double_t GetAzimuthalAngleError() const;

  B2ViewAngle &operator=(const TVector2 &val) override;

  ~B2ViewAngle() override = default;

  friend std::ostream &operator<<(std::ostream &os, const B2ViewAngle &obj);

ClassDefOverride(B2ViewAngle, 1)
};

/**
 * Direction versor (of unit magnitude)
 */
class B2Direction : public B2Measurement3D {
public:
  B2Direction();

  B2Direction(Double_t x, Double_t y, Double_t z, Double_t ex, Double_t ey, Double_t ez);

  B2Direction(const TVector3 &val, const TVector3 &err);

  explicit B2Direction(const TVector3 &val);

  B2Direction &operator=(const TVector3 &val) override;

  ~B2Direction() override = default;

  void SetValue(Double_t x, Double_t y, Double_t z) override;

  void SetValue(const TVector3 &vec) override;

  void Set(const TVector3 &val, const TVector3 &err) override;

  B2Angle ToAngle() const;

  B2ViewAngle ToViewAngle() const;

ClassDefOverride(B2Direction, 2)
};


/**
 * Streamable and comparable TVector3
 */
class B2Vector3 : public TVector3 {

public:
  B2Vector3();

  B2Vector3(double x, double y, double z);

  explicit B2Vector3(double i);

  friend std::ostream &operator<<(std::ostream &os, const B2Vector3 &obj);

  B2Vector3 &operator=(double rhs);

  inline friend bool operator==(const B2Vector3 &lhs, Double_t rhs) {
    return lhs.X() == rhs && lhs.Y() == rhs && lhs.Z() == rhs;
  }

  inline friend bool operator!=(const B2Vector3 &lhs, Double_t rhs) {
    return !(lhs == rhs);
  }

  inline friend bool operator<(const B2Vector3 &lhs, const B2Vector3 &rhs) {
    return lhs.Mag() < rhs.Mag();
  }

  inline friend bool operator>(const B2Vector3 &lhs, const B2Vector3 &rhs) {
    return operator<(rhs, lhs);
  }

  inline friend bool operator<=(const B2Vector3 &lhs, const B2Vector3 &rhs) {
    return !operator>(lhs, rhs);
  }

  inline friend bool operator>=(const B2Vector3 &lhs, const B2Vector3 &rhs) {
    return !operator<(lhs, rhs);
  }

ClassDef(B2Vector3, 1)
};

/**
 * Class to store a measurement made on a double readout scintillator bar
 * of integer type
 */
typedef B2VectorDoubleReadout<Int_t> B2DoubleReadoutI;

/**
 * Class to store a measurement made on a double readout scintillator bar
 * of double floating point type
 */
typedef B2VectorDoubleReadout<Double_t> B2DoubleReadoutD;

/**
 * Class to store a measurement made on a double readout scintillator bar
 * of TVector3 type
 */
typedef B2VectorDoubleReadout<B2Vector3> B2DoubleReadout3;

#endif //WAGASCIBABYMINDMONTECARLO_B2MEASUREMENT_HH