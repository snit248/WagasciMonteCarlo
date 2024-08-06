#ifndef B2Boundary_H
#define B2Boundary_H

// system includes
#include <iostream>
#include <vector>

// ROOT includes
#include <TObject.h>
#include <TRef.h>


class B2Boundary : public TObject {

public:

  B2Boundary();

  virtual Bool_t CheckBoundaryCondition(Double_t value);

  virtual Bool_t CheckBoundaryCondition(std::vector<Double_t> value);

private:

ClassDefOverride(B2Boundary, 0) // B2 Boundary
};

template<typename T>
class B2SingleBoundary : public B2Boundary {

public:

  explicit B2SingleBoundary(T bound);

  Bool_t CheckBoundaryCondition(Double_t value) override;

  Bool_t CheckBoundaryCondition(std::vector<Double_t> value) override;

  T GetBound() { return boundarycondition_; }

private:

  T boundarycondition_{0};

ClassDefOverride(B2SingleBoundary, 0) // B2 SingleBoundary
};

template<typename T>
class B2DoubleBoundary : public B2Boundary {

public:

  explicit B2DoubleBoundary(T &bound);

  Bool_t CheckBoundaryCondition(Double_t value) override;

  Bool_t CheckBoundaryCondition(std::vector<Double_t> value) override;

  T GetBound() { return boundarycondition_; }

private:

  T boundarycondition_{};

ClassDefOverride(B2DoubleBoundary, 0) // B2 DoubleBoundary
};

template<typename T>
class B2PointLikeBoundary : public B2Boundary {

public:

  explicit B2PointLikeBoundary(T &bound);

  Bool_t CheckBoundaryCondition(Double_t value) override;

  Bool_t CheckBoundaryCondition(std::vector<Double_t> value) override;

  T GetBound() { return boundarycondition_; }

private:

  T boundarycondition_{};

ClassDefOverride(B2PointLikeBoundary, 0) // B2 PointLikeBoundary
};

class B2DoubleBoundarySet : public B2Boundary {

public:

  explicit B2DoubleBoundarySet(std::vector<B2DoubleBoundary<std::vector<double>>> bounds, const std::string logic);

  Bool_t CheckBoundaryCondition(std::vector<double> value) override;

private:

  std::vector<B2DoubleBoundary<std::vector<double>>> boundarycondition_{};

  std::string logic_;

ClassDefOverride(B2DoubleBoundarySet, 0) // B2 SingleBoundary
};


#endif // B2Boundary_H
////////////////////////////////////////////////////////////////////////
