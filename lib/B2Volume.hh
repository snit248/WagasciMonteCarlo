//
// Created by Giorgio Pintaudi on 2020/10/17.
//

#ifndef WAGASCIBABYMINDMONTECARLO_B2VOLUME_HH
#define WAGASCIBABYMINDMONTECARLO_B2VOLUME_HH

#include <list>
#include <utility>
#include <string>
#include <TVector3.h>
#include "B2Enum.hh"

class B2Volume {

protected:

  TVector3 position_;
  TVector3 dimensions_;
  B2Detector detector_;
  std::string name_;

public:

  /**
   * @param position position of the center of the volume in mm
   * @param dimensions (X, Y, Z) dimensions of the volume in mm
   * @param detector detector which the volume belongs to
   * @param name name of the volume
   */
  B2Volume(const TVector3 &position, const TVector3 &dimensions, B2Detector detector, std::string name);

  /**
   * Default destructor
   */
  virtual ~B2Volume() = default;

  /**
   * @return position of the center of the volume in mm
   */
  const TVector3 &GetPosition() const;

  /**
   * @return (X, Y, Z) dimensions of the volume in mm
   */
  const TVector3 &GetDimensions() const;

  /**
   * @return name of the volume
   */
  const std::string &GetName() const;

  /**
   * @return detector which the volume belongs to
   */
  B2Detector GetDetector() const;

  /**
   * @return true if the volume is a fiducial volume, false if it is a generic volume
   */
  virtual bool IsFiducialVolume() const;

  /**
   * @param point point whose coordinates in mm are relative to the center of the detector
   * @return true if the point is contained inside the volume
   */
  bool IsRelativePointContained(const TVector3 &point) const;

  /**
   * @param point point in absolute coordinates in mm
   * @return true if the point is contained inside the volume
   */
  bool IsAbsolutePointContained(const TVector3 &point) const;
};

//////////////////////////////////////////////////////////////////////////////////////

class B2FiducialVolume : public B2Volume {

  /**
   * @param position position of the center of the detector in mm
   * @param dimensions dimensions of the 3 edges of the detector in mm
   * @param detector detector ID
   * @param name volume name
   */
  B2FiducialVolume(const TVector3 &position, const TVector3 &dimensions, B2Detector detector, std::string name);

  /**
   * @return  true if the volume is a fiducial volume, false if it is a generic volume
   */
  bool IsFiducialVolume() const override;
};

//////////////////////////////////////////////////////////////////////////////////////

class B2DetectorVolume : public B2Volume {

private:

  std::list<B2FiducialVolume> fiducial_volumes_;

  /**
   * Calculate the intersection between a line and the volume in 2D for each view. If the interception
   * is not found a std::runtime_error is thrown
   * @param p0 first line point 1
   * @param p1 first line point 2
   * @param p2 second line point 1
   * @param p3 second line point 2
   * @return 2D interception point
   */
  static bool GetLineIntersection(const TVector2 &p0, const TVector2 &p1,
                                  const TVector2 &p2, const TVector2 &p3,
                                  TVector2 &i);

public:

  B2DetectorVolume(const TVector3 &position, const TVector3 &dimensions, B2Detector detector, std::string name);

  /**
   * Add a fiducial volume to the list of fiducial volumes
   * @param fiducial_volume fiducial volume
   */
  void AddFiducialVolume(B2FiducialVolume fiducial_volume);

  /**
   * @return first fiducial volume
   */
  const B2FiducialVolume &GetFiducialVolume() const;

  /**
   * @return first fiducial volume
   */
  B2FiducialVolume &GetFiducialVolume();

  /**
   * @param name fiducial volume name
   * @return fiducial volume
   */
  const B2FiducialVolume &GetFiducialVolume(const std::string &name) const;

  /**
   * @param name fiducial volume name
   * @return fiducial volume
   */
  B2FiducialVolume &GetFiducialVolume(const std::string &name);

  /**
   * Calculate the 2D intersection point between a line and the volume
   * @param view view
   * @param start edge of the line in relative coordinates
   * @param direction direction vector of the line
   * @return 2D intersection point for that particular view in relative coordinates
   */
  bool IntersectionPointRelative(B2View view, const TVector3 &start, const TVector3 &direction,
                                 TVector2 &intersection) const;

  /**
   * Calculate the 2D intersection point between a line and the volume
   * @param view view
   * @param start edge of the line in absolute coordinates
   * @param direction direction vector of the line
   * @return 2D intersection point for that particular view in absolute coordinates
   */
  bool IntersectionPointAbsolute(B2View view, const TVector3 &start, const TVector3 &direction,
                                 TVector2 &intersection) const;
};

/**
 * Volumes of the detectors (including fiducial volumes)
 */

extern const std::unordered_map<B2Detector, B2DetectorVolume, EnumClassHash> DETECTOR_VOLUMES;

#endif //WAGASCIBABYMINDMONTECARLO_B2VOLUME_HH
