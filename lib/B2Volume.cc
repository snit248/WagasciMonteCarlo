//
// Created by Giorgio Pintaudi on 2020/10/17.
//

#include "B2Volume.hh"
#include "B2Const.hh"

B2Volume::B2Volume(const TVector3 &position, const TVector3 &dimensions, B2Detector detector, std::string name) :
    position_(position), dimensions_(dimensions), detector_(detector), name_(std::move(name)) {
  if (dimensions_.x() <= 0 || dimensions_.y() <= 0 || dimensions_.z() <= 0) {
    throw std::invalid_argument("Volume dimensions must be strictly positive");
  }
}

const TVector3 &B2Volume::GetPosition() const {
  return position_;
}

const TVector3 &B2Volume::GetDimensions() const {
  return dimensions_;
}

const std::string &B2Volume::GetName() const {
  return name_;
}

B2Detector B2Volume::GetDetector() const {
  return detector_;
}

bool B2Volume::IsFiducialVolume() const {
  return false;
}

bool B2Volume::IsRelativePointContained(const TVector3 &point) const {
  if (std::fabs(point.x()) < 0.5 * dimensions_.x() &&
      std::fabs(point.y()) < 0.5 * dimensions_.y() &&
      std::fabs(point.z()) < 0.5 * dimensions_.z())
    return true;
  return false;
}

bool B2Volume::IsAbsolutePointContained(const TVector3 &point) const {
  if (std::fabs(point.x() - position_.x()) < 0.5 * dimensions_.x() &&
      std::fabs(point.y() - position_.y()) < 0.5 * dimensions_.y() &&
      std::fabs(point.z() - position_.z()) < 0.5 * dimensions_.z())
    return true;
  return false;
}

bool B2FiducialVolume::IsFiducialVolume() const {
  return true;
}

B2FiducialVolume::B2FiducialVolume(const TVector3 &position, const TVector3 &dimensions, B2Detector detector,
                                   std::string name) :
    B2Volume(position, dimensions, detector, std::move(name)) {}

void B2DetectorVolume::AddFiducialVolume(B2FiducialVolume fiducial_volume) {
  fiducial_volumes_.push_back(std::move(fiducial_volume));
}

const B2FiducialVolume &B2DetectorVolume::GetFiducialVolume() const {
  return fiducial_volumes_.front();
}

B2FiducialVolume &B2DetectorVolume::GetFiducialVolume() {
  return fiducial_volumes_.front();
}

const B2FiducialVolume &B2DetectorVolume::GetFiducialVolume(const std::string &name) const {
  for (const auto &vol : fiducial_volumes_)
    if (vol.GetName() == name)
      return vol;
  throw std::out_of_range("Fiducial volume with name " + name + " not found");
}

B2FiducialVolume &B2DetectorVolume::GetFiducialVolume(const std::string &name) {
  return const_cast<B2FiducialVolume &>(static_cast<const B2DetectorVolume &>(*this).GetFiducialVolume(name));
}

B2DetectorVolume::B2DetectorVolume(const TVector3 &position, const TVector3 &dimensions, B2Detector detector,
                                   std::string name) :
    B2Volume(position, dimensions, detector, std::move(name)) {}

bool B2DetectorVolume::GetLineIntersection(const TVector2 &p0, const TVector2 &p1,
                                           const TVector2 &p2, const TVector2 &p3,
                                           TVector2 &i) {

  if ((p0.X() == p1.X() && p0.Y() == p1.Y()) || (p2.X() == p3.X() && p2.Y() == p3.Y()))
    return false;

  double s1_x, s1_y, s2_x, s2_y;
  s1_x = p1.X() - p0.X();
  s1_y = p1.Y() - p0.Y();
  s2_x = p3.X() - p2.X();
  s2_y = p3.Y() - p2.Y();

  double u, t;
  u = (-s1_y * (p0.X() - p2.X()) + s1_x * (p0.Y() - p2.Y())) / (-s2_x * s1_y + s1_x * s2_y);
  t = (s2_x * (p0.Y() - p2.Y()) - s2_y * (p0.X() - p2.X())) / (-s2_x * s1_y + s1_x * s2_y);

  if (u >= 0 && u <= 1 && t >= 0 && t <= 1) {
    i.SetX(p0.X() + (t * s1_x));
    i.SetY(p0.Y() + (t * s1_y));
    return true;
  }
  return false;
}

bool B2DetectorVolume::IntersectionPointRelative(B2View view, const TVector3 &start, const TVector3 &direction,
                                                 TVector2 &intersection) const {
  TVector2 point1, point2;
  TVector2 lb, lu, rb, ru;
  switch (view) {
    case B2View::kSideView:
      point1.Set(start.z(), start.y());
      point2.Set(start.z() + 20 * m * direction.z(), start.y() + 20 * m * direction.y());
      lb.Set(-0.5 * dimensions_.z(), -0.5 * dimensions_.y());
      lu.Set(-0.5 * dimensions_.z(), 0.5 * dimensions_.y());
      rb.Set(0.5 * dimensions_.z(), -0.5 * dimensions_.y());
      ru.Set(0.5 * dimensions_.z(), 0.5 * dimensions_.y());
      break;
    case B2View::kTopView:
      point1.Set(start.z(), start.x());
      point2.Set(start.z() + 20 * m * direction.z(), start.x() + 20 * m * direction.x());
      lb.Set(-0.5 * dimensions_.z(), -0.5 * dimensions_.x());
      lu.Set(-0.5 * dimensions_.z(), 0.5 * dimensions_.x());
      rb.Set(0.5 * dimensions_.z(), -0.5 * dimensions_.x());
      ru.Set(0.5 * dimensions_.z(), 0.5 * dimensions_.x());
      break;
    case B2View::kUnknownView:
      throw std::invalid_argument("Invalid view");
  }

  if (GetLineIntersection(lb, rb, point1, point2, intersection))
    return true;
  if (GetLineIntersection(rb, ru, point1, point2, intersection))
    return true;
  if (GetLineIntersection(ru, lu, point1, point2, intersection))
    return true;
  if (GetLineIntersection(lu, lb, point1, point2, intersection))
    return true;
  return false;
}

bool B2DetectorVolume::IntersectionPointAbsolute(B2View view, const TVector3 &start, const TVector3 &direction,
                                                 TVector2 &intersection) const {
  TVector3 offset_start = start - position_;
  auto result = IntersectionPointRelative(view, offset_start, direction, intersection);
  if (result) {
    switch (view) {
      case B2View::kSideView:
        intersection.SetX(intersection.X() + position_.Z());
        intersection.SetY(intersection.Y() + position_.Y());
        break;
      case B2View::kTopView:
        intersection.SetX(intersection.X() + position_.Z());
        intersection.SetY(intersection.Y() + position_.X());
        break;
      case B2View::kUnknownView:
        throw std::invalid_argument("Invalid view");
    }
  }
  return result;
}

const std::unordered_map<B2Detector, B2DetectorVolume, EnumClassHash> DETECTOR_VOLUMES = {
    {B2Detector::kProtonModule,
        B2DetectorVolume(TVector3(PROTON_MODULE_POS_X, PROTON_MODULE_POS_Y, PROTON_MODULE_POS_Z),
                         TVector3(PM_BOX_WIDTH, PM_BOX_HEIGHT, PM_BOX_DEPTH),
                         B2Detector::kProtonModule, "ProtonModule")},
    {B2Detector::kWagasciUpstream,
        B2DetectorVolume(TVector3(WAGASCI_UPSTREAM_POS_X, WAGASCI_UPSTREAM_POS_Y, WAGASCI_UPSTREAM_POS_Z),
                         TVector3(WGS_BOX_WIDTH, WGS_BOX_HEIGHT, WGS_BOX_DEPTH),
                         B2Detector::kWagasciUpstream, "WagasciUpstream")},
    {B2Detector::kWagasciDownstream,
        B2DetectorVolume(TVector3(WAGASCI_DOWNSTREAM_POS_X, WAGASCI_DOWNSTREAM_POS_Y, WAGASCI_DOWNSTREAM_POS_Z),
                         TVector3(WGS_BOX_WIDTH, WGS_BOX_HEIGHT, WGS_BOX_DEPTH),
                         B2Detector::kWagasciDownstream, "WagasciDownstream")},
    {B2Detector::kWallMrdNorth,
        B2DetectorVolume(TVector3(WALLMRD_NORTH_POS_X, WALLMRD_POS_Y, WALLMRD_NORTH_POS_Z),
                         TVector3(WM_BOX_WIDTH, WM_BOX_HEIGHT, WM_BOX_DEPTH),
                         B2Detector::kWallMrdNorth, "WallMrdNorth")},
    {B2Detector::kWallMrdSouth,
        B2DetectorVolume(TVector3(WALLMRD_SOUTH_POS_X, WALLMRD_POS_Y, WALLMRD_SOUTH_POS_Z),
                         TVector3(WM_BOX_WIDTH, WM_BOX_HEIGHT, WM_BOX_DEPTH),
                         B2Detector::kWallMrdSouth, "WallMrdSouth")},
    {B2Detector::kBabyMind,
        B2DetectorVolume(TVector3(BABYMIND_POS_X, BABYMIND_POS_Y, BABYMIND_POS_Z),
                         TVector3(BM_BOX_WIDTH, BM_BOX_HEIGHT, BM_BOX_DEPTH),
                         B2Detector::kBabyMind, "BabyMind")},
    {B2Detector::kNinja,
        B2DetectorVolume(TVector3(NINJA_POS_X, NINJA_POS_Y, NINJA_POS_Z),
                         TVector3(NINJA_BOX_WIDTH, NINJA_BOX_HEIGHT, NINJA_BOX_DEPTH),
                         B2Detector::kNinja, "Ninja")}
};