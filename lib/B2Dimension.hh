#ifndef _B2Dimension_H
#define _B2Dimension_H

// system includes
#include <array>

// BOOST includes
#include <boost/filesystem.hpp>

// ROOT includes
#include <TVector3.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>

// project includes
#include "B2Enum.hh"
#include "B2Const.hh"

namespace fs = boost::filesystem;

const extern fs::path WAGASCI_POSITION_XY;
const extern fs::path WAGASCI_POSITION_Z;
const extern fs::path V1_HORIZONTAL_FROM_CENTER_FILE;
const extern fs::path V1_VERTICAL_FROM_CENTER_FILE;
const extern fs::path SCIN_MOD_POSITION_FILE;
const extern fs::path CORRECTION_FILE;
const extern fs::path YASU_POSITION_FILE;
const extern fs::path BM_VERTICAL_PE_LEFT_FILE;
const extern fs::path BM_VERTICAL_PE_RIGHT_FILE;
const extern fs::path BM_VERTICAL_ZPOS_CORR_FILE;

/**
 * Get the detector-relative position of a channel. The position is always given in mm and
 * is returned as a TVector3 object.
 *
 * Sometimes only the XZ (top view) or YZ (side view) projections are returned and the remaining
 * coordinate is set to zero.
 *
 * Because the word channel can be ambiguosly mistaken for the chip/channel, sometimes it was
 * renamed as "slot" to avoid confusion. Remember that slot number and channel number in the
 * raw data might not be the same thing.
 *
 * The plane number is usually increasing when going towards the downstream direction. The
 * most upstream plane would be zero, and so on.
 *
 * The object need to read some text and ROOT files to be constructed. Currently the MC
 * software needs those files to work. You can configure the path of the folder containing
 * those files in
 */
class B2Dimension {

private:

  std::array<std::array<std::array<double, WGS_NUM_SLOTS>, WGS_NUM_PLANES>, NUM_VIEWS> wg_position_xy_{};
  std::array<std::array<double, WGS_NUM_PLANES>, NUM_VIEWS> wg_position_z_{};

  std::array<double, YASU_NUM_SLOTS_ONE_PLANE> yasu_position_y_{};
  std::array<double, YASU_NUM_PLANES> yasu_position_z_{};
  std::array<double, YASU_NUM_SLOTS_ONE_PLANE> yasu_gap_y_{};

  std::array<double, BM_NUM_VERTICAL_SCINTI_ONE_PLANE> bm_position_x_{};
  std::array<double, BM_NUM_HORIZ_SCINTI_ONE_PLANE> bm_position_y_{};
  std::array<double, BM_NUM_TRACKING_PLANES> bm_position_z_{};

  std::array<double, BM_NUM_TRACKING_PLANES> bm_correction_y_{};

  std::array<double, 13> posx_formap_{};
  std::array<double, 7> posy_formap_{7, 50, 98, 145, 165, 187, 193};
  std::array<std::array<double, 13>, 7> pe_vertical_bm_left_{};
  std::array<std::array<double, 13>, 7> pe_vertical_bm_right_{};

  std::array<std::array<double, 16>, 18> vertical_zpos_corr_{};

  TH1F* time_bottom[30][50];
  TH1F* time_top[30][50];
  TH2F* avt_bottom;
  TH2F* avt_top;
  TH2F* pe_bottom;
  TH2F* pe_top;

  Double_t time_bottom_val[30][50][100] = {};
  Double_t time_top_val[30][50][100] = {};
  Double_t avt_bottom_val[30][50] = {};
  Double_t avt_top_val[30][50] = {};
  Double_t pe_bottom_val[30][50] = {};
  Double_t pe_top_val[30][50] = {};

  /**
   * Read geometry files for WAGASCI. The file names are hardcoded
   * and can be configured in the B2Configuration.cc file.
   *
   * The "wagasci_position_z.root file contains the z position of the 8
   * WAGASCI planes in both top view and side view for a total of 16 entries.
   * The only branches that are read are:
   *  - view : top view is 1, side view is 0
   *  - pln : plane number (from 0 to 7)
   *  - z : z position of the plane in mm
   *
   *  The "wagasci_position_xy.root" file contains the xy position of each
   *  slot (only for the plane scintillators). The only branches that are read are:
   *   - view : top view is 1, side view is 0
   *   - pln : plane number (from 0 to 7)
   *   - ch : slot number (from 0 to 79)
   *   - xy1 : one edge of the scintillator bar
   *   - xy3 : other edge of the scintillator bar
   *
   * @param geometry_dir directory where those files are located.
   */
  void ReadWagasciGeometry(const fs::path &geometry_dir);

  /**
   * Read geometry files for BabyMIND. The file names are hardcoded
   * and can be configured in the B2Configuration.cc file.
   * @param geometry_dir directory where those files are located.
   */
  void ReadBabyMindGeometry(const fs::path &geometry_dir);

  /**
   * Read geometry files for WallMRD. The file names are hardcoded
   * and can be configured in the B2Configuration.cc file.
   * @param geometry_dir directory where those files are located.
   */
  void ReadWallMrdGeometry(const fs::path &geometry_dir);

public:
  explicit B2Dimension(const std::string &geometry_dir_path);

  explicit B2Dimension(const fs::path &geometry_dir_path);

  /**
   *
   * @param detector_id Detector ID
   * @param view view
   * @param plane plane number
   * @param slot slot number
   * @param pos position in mm
   * @return true in case of success, false in case of failure
   */
  bool GetPosition(B2Detector detector_id, B2View view, unsigned int plane, unsigned int slot, TVector3 &pos) const;

  /**
   *
   * @param detector_id Detector ID
   * @param view view
   * @param plane plane number
   * @param slot slot number
   * @param error error in mm
   * @return true in case of success, false in case of failure
   */
  static bool GetError(B2Detector detector_id, B2View view, unsigned int plane, unsigned int slot, TVector3 &error);

  /**
   * Get position of Proton Module channel
   *
   * @param view view
   * @param plane plane number
   * @param channel channel number
   * @param pos position in mm
   * @return true in case of success, false in case of failure
   */
  static bool GetPosPm(B2View view, unsigned int plane, unsigned int channel, TVector3 &pos);

  /**
   * Get position of Proton Module VETO channel
   *
   * @param view side view or top view
   * @param plane plane number
   * @param channel channel number
   * @param pos position in mm
   * @return true in case of success, false in case of failure
   */
  static bool GetPosVetoPm(B2View view, unsigned int plane, unsigned int channel, TVector3 &pos);

  /**
   * Get position error of Proton Module VETO channel
   *
   * @param view side view or top view
   * @param plane plane number
   * @param channel channel number
   * @param error position in mm
   * @return true in case of success, false in case of failure
   */
  static bool GetErrorVetoPm(B2View view, unsigned int plane, unsigned int channel, TVector3 &error);

  /**
   * Get position error of Proton Module channel (including VETO ones)
   *
   * @param view side view or top view
   * @param plane plane number
   * @param channel channel number
   * @param error position in mm
   * @return true in case of success, false in case of failure
   */
  static bool GetErrorPm(B2View view, unsigned int plane, unsigned int channel, TVector3 &error);

  /**
   * Get position of WAGASCI channel (center of scintillator bar)
   *
   * @param view side view or top view
   * @param plane plane number
   * @param grid_slot slot number
   * @param grid grid number
   * @param pos position in mm
   * @return true in case of success, false in case of failure
   */
  bool GetPosWgs(B2View view, unsigned int plane, unsigned int grid_slot,
                 B2GridPlane grid, TVector3 &pos) const;

  /**
   * Get position of WAGASCI channel (center of scintillator bar)
   *
   * @param view side view or top view
   * @param plane plane number
   * @param slot slot number
   * @param pos position in mm
   * @return true in case of success, false in case of failure
   */
  bool GetPosWgs(B2View view, unsigned plane, unsigned slot,
                 TVector3 &pos) const;

  /**
   * Get position of WAGASCI channel (MPPC position)
   *
   * @param view side view or top view
   * @param plane plane number
   * @param slot slot number
   * @param pos position in mm
   * @return true in case of success, false in case of failure
   */
  bool GetPosWgsMppc(B2View view, unsigned plane, unsigned slot,
                     TVector3 &pos) const;

  /**
   * Get grid number and grid slot from slot number.
   * It is not clear what all these numbers mean.
   *
   * @param slot slot number
   * @param grid_slot grid/slot number
   * @param grid grid number
   * @return true in case of success, false in case of failure
   */
  static bool GetGridWgs(unsigned slot, unsigned &grid_slot, B2GridPlane &grid);

  /**
   * Get the error of a hit inside WAGASCI scintillators
   *
   * @param error error
   * @return  true in case of success, false in case of failure
   */
  static bool GetErrorWgs(B2View view, unsigned slot, TVector3 &error);

  /**
   * Get the position of a WallMRD channel
   *
   * @param detector B2Detector::kWallMrdNorth or B2Detector::kWallMrdSouth
   * @param plane plane number
   * @param slot slot number
   * @param pos position in mm
   * @return true in case of success, false in case of failure
   */
  static bool GetPosWallMrd(B2Detector detector, unsigned plane, unsigned slot, TVector3 &pos);

  /**
   * Get the error of a hit inside WallMRD scintillators
   *
   * @param error error
   * @return  true in case of success, false in case of failure
   */
  static bool GetErrorWallMrd(TVector3 &error);

  /**
   * Get WallMRD direction from detector ID
   * @param detector detector ID
   * @return direction enum
   */
  static B2WallMrdDirection GetWallMrdDirection(B2Detector detector);

  /**
   * Get position of a BabyMIND channel
   *
   * @param view can be top or side
   * @param plane plane number
   * @param slot slot number
   * @param pos position in mm
   * @return true in case of success, false in case of failure
   */
  bool GetPosBm(B2View view, unsigned plane, unsigned slot, TVector3 &pos) const;

  /**
   * Get position error of a Baby MIND channel
   *
   * @param view can be top or side
   * @param error position error in mm
   * @return true in case of success, false in case of failure
   */
  static bool GetErrorBm(B2View view, TVector3 &error);

  /**
   * Get position of YASU tracker channel
   *
   * @param plane plane number
   * @param slot slot number
   * @param pos position in mm
   * @return true in case of success, false in case of failure
   */
  bool GetPosYasu(unsigned plane, unsigned slot, TVector3 &pos) const;

  /**
   * Get position error of a YASU tracker channel
   *
   * @param view can only be side
   * @param error position error in mm
   * @return true in case of success, false in case of failure
   */
  static bool GetErrorYasu(B2View view, TVector3 &error);

  /**
   * Get position of NINJA tracker
   *
   * @param view view
   * @param plane plane
   * @param slot slot (same as channel)
   * @param pos position in mm
   * @return true in case of success, false in case of failure
   */
  static bool GetPosNinjaTracker(B2View view, unsigned int plane, unsigned int slot, TVector3 &pos);

  /**
   * Get the type of VETO plane from plane number
   * @param plane plane number
   * @return type of VETO
   */
  static B2VetoPlane GetVetoPlanePm(unsigned int plane);

  /**
   * Get readout type of YASU tracker
   * @param slot slot number
   * @return readout type
   */
  static B2Readout GetReadoutYasu(unsigned int slot);

  /**
   * Get scintillator type of YASU tracker
   * @param slot slot number
   * @return scintillator type
   */
  static B2ScintillatorType GetScintillatorTypeYasu(unsigned int slot);

  /**
   * Get error on position of one NINJA tracker channel
   * @param view view
   * @param error error on position in mm
   * @return true in case of success, false in case of failure
   */
  static bool GetErrorNinja(B2View view, TVector3 &error);

  /**
   * @param detector which WallMRD (south or north)
   * @param plane plane number
   * @param pos position of iron plane
   * @return true in case of success, false in case of failure
   */
  static bool GetPosWallMrdIron(B2Detector detector, unsigned int plane, TVector3 &pos);

  static bool CheckDeadChannel(B2Detector detector, B2View view, unsigned int readout, unsigned int plane, unsigned int slot);

  double GetBMVerticalPE(double posx, double posy, B2Readout ireadout) const;

  double GetAverageTime(double posy, double posz, B2Readout readout) const;

  double GetAveragePe(double posy, double posz, B2Readout readout) const;

  double GetRondomTime(double posy, double posz, B2Readout readout) const;
};

#endif

