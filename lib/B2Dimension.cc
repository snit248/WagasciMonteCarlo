#include "B2Dimension.hh"

// system includes
#include <array>

// BOOST includes
#include <boost/log/trivial.hpp>
#include <boost/filesystem.hpp>

// ROOT includes
#include <TFile.h>
#include <TTree.h>
#include <TVector3.h>
#include <sstream>

// project includes
#include "B2Enum.hh"

const fs::path WAGASCI_POSITION_XY("wagasci_position_xy.root");
const fs::path WAGASCI_POSITION_Z("wagasci_position_z.root");
const fs::path V1_HORIZONTAL_FROM_CENTER_FILE("v1_horizontal_from_center.txt");
const fs::path V1_VERTICAL_FROM_CENTER_FILE("v1_vertical_from_center.txt");
const fs::path SCIN_MOD_POSITION_FILE("Scin_Mod_position.txt");
const fs::path CORRECTION_FILE("correction.txt");
const fs::path YASU_POSITION_FILE("yasuposition.txt");
const fs::path BM_VERTICAL_PE_LEFT_FILE("bm_verticalpe_map_left.txt");
const fs::path BM_VERTICAL_PE_RIGHT_FILE("bm_verticalpe_map_right.txt");
const fs::path BM_VERTICAL_ZPOS_CORR_FILE("bm_vertical_zpos_corr.txt");
const fs::path WMRD_TIME_LY_FILE("wmrdopt.root");

B2Dimension::B2Dimension(const std::string &geometry_dir_path) {

  fs::path geometry_dir(geometry_dir_path);

  ReadWagasciGeometry(geometry_dir);

  ReadBabyMindGeometry(geometry_dir);

  ReadWallMrdGeometry(geometry_dir);

  BOOST_LOG_TRIVIAL(info) << "B2Dimension is initialized";
}

B2Dimension::B2Dimension(const fs::path &geometry_dir_path) : B2Dimension(geometry_dir_path.string()) {}

void B2Dimension::ReadWagasciGeometry(const fs::path &geometry_dir) {
  {
    const std::string ac_path = (geometry_dir / WAGASCI_POSITION_XY).string();
    if (!fs::exists(ac_path))
      throw std::runtime_error("WAGASCI " + WAGASCI_POSITION_XY.string()
                               + " file not found : " + ac_path);
    TFile ac_file(ac_path.c_str());
    auto *ac_ttree = (TTree *) ac_file.Get("tree");
    Double_t xy_offset = 0, xy1, xy3;
    Int_t view, plane, slot;
    ac_ttree->SetBranchAddress("xy1", &xy1);
    ac_ttree->SetBranchAddress("xy3", &xy3);
    ac_ttree->SetBranchAddress("view", &view);
    ac_ttree->SetBranchAddress("pln", &plane);
    ac_ttree->SetBranchAddress("ch", &slot);
    for (Long64_t i = 0; i < ac_ttree->GetEntries(); ++i) {
      ac_ttree->GetEntry(i);
      if (slot == 0) {
        // Slot 0 is start point and the other positions are distance from it
        xy_offset = 0.5 * (xy1 + xy3) * mm;
      }
      if (slot < WGS_NUM_SLOTS_PLANE) {
        wg_position_xy_[view][plane][slot] = 0.5 * (xy1 + xy3) * mm - xy_offset;
      } else {
        wg_position_xy_[view][plane][slot] = 0;
      }
    }
    ac_file.Close();
  }
  {
    const std::string pmz_path = (geometry_dir / WAGASCI_POSITION_Z).string();
    if (!fs::exists(pmz_path))
      throw std::runtime_error("WAGASCI " + WAGASCI_POSITION_Z.string() +
                               " file not found : " + pmz_path);
    TFile pmz_tfile(pmz_path.c_str());
    auto pmz_ttree = (TTree *) pmz_tfile.Get("tree");
    Double_t z_offset = 0, z;
    Int_t view, plane;
    pmz_ttree->SetBranchAddress("z", &z);
    pmz_ttree->SetBranchAddress("view", &view);
    pmz_ttree->SetBranchAddress("pln", &plane);
    for (Long64_t i = 0; i < pmz_ttree->GetEntries(); i++) {
      pmz_ttree->GetEntry(i);
      if (i == 0) {
        // First plane is start point and the other positions are distance from it
        z_offset = z;
      }
      wg_position_z_[view][plane] = z - z_offset;
    }
    pmz_tfile.Close();
  }
}

void B2Dimension::ReadBabyMindGeometry(const fs::path &geometry_dir) {
  {
    const std::string corr_path = (geometry_dir / CORRECTION_FILE).string();
    std::ifstream corr_file(corr_path);
    if (!corr_file.is_open())
      throw std::runtime_error("BabyMIND " + CORRECTION_FILE.string() +
                               " file found : " + corr_path);
    double index, value;
    for (double &correction_y : bm_correction_y_) {
      corr_file >> index >> value;
      correction_y = value * mm;
    }
    corr_file.close();
  }
  {
    const std::string hfc_path = (geometry_dir / V1_HORIZONTAL_FROM_CENTER_FILE).string();
    std::ifstream hfc_file((geometry_dir / V1_HORIZONTAL_FROM_CENTER_FILE).string());
    if (!hfc_file.is_open())
      throw std::runtime_error("BabyMIND " + V1_HORIZONTAL_FROM_CENTER_FILE.string() +
                               " file found : " + hfc_path);
    double index, ignore, value;
    for (double &position_y : bm_position_y_) {
      hfc_file >> index >> ignore >> ignore >> ignore >> value;
      position_y = value * mm;
    }
    hfc_file.close();
  }
  {
    const std::string vfc_path = (geometry_dir / V1_VERTICAL_FROM_CENTER_FILE).string();
    std::ifstream vfc_file((geometry_dir / V1_VERTICAL_FROM_CENTER_FILE).string());
    if (!vfc_file.is_open())
      throw std::runtime_error("BabyMIND " + V1_VERTICAL_FROM_CENTER_FILE.string() +
                               " file found : " + vfc_path);
    double index, ignore, value;
    for (std::size_t i = 0; i < bm_position_x_.size() * 2; i++) {
      vfc_file >> index >> ignore >> ignore >> ignore >> value;
      if (i % 2 == 0) {
        bm_position_x_[i / 2] = value * mm;
      }
    }
  }
  {
    const std::string smp_path = (geometry_dir / SCIN_MOD_POSITION_FILE).string();
    std::ifstream smp_file((geometry_dir / SCIN_MOD_POSITION_FILE).string());
    if (!smp_file.is_open())
      throw std::runtime_error("BabyMIND " + SCIN_MOD_POSITION_FILE.string() +
                               " file found : " + smp_path);
    double index, ignore, value;
    for (double &position_z : bm_position_z_) {
      smp_file >> index >> ignore >> ignore >> value;
      position_z = value * mm;
    }
    smp_file.close();
  }

  {
    const std::string yasu_path = (geometry_dir / YASU_POSITION_FILE).string();
    std::ifstream yasu_file((geometry_dir / YASU_POSITION_FILE).string());
    if (!yasu_file.is_open())
      throw std::runtime_error("BabyMIND " + YASU_POSITION_FILE.string() +
                               " file found : " + yasu_path);
    double position_y, gap_y;
    for (std::size_t i = 0; i < yasu_position_y_.size(); i++) {
      yasu_file >> position_y >> gap_y;
      yasu_position_y_[i] = position_y * cm;
      yasu_gap_y_[i] = gap_y * cm;
    }
    yasu_position_z_[0] = YASU_POS_Z0;
    yasu_position_z_[1] = YASU_POS_Z1;
    yasu_file.close();
  }

  const std::string vertical_pe_left_path = (geometry_dir / BM_VERTICAL_PE_LEFT_FILE).string();
  const std::string vertical_pe_right_path = (geometry_dir / BM_VERTICAL_PE_RIGHT_FILE).string();
  std::ifstream vertical_pe_right_file((geometry_dir / BM_VERTICAL_PE_LEFT_FILE).string());
  std::ifstream vertical_pe_left_file((geometry_dir / BM_VERTICAL_PE_RIGHT_FILE).string());
  if (!vertical_pe_left_file.is_open())
    throw std::runtime_error("BabyMIND " + BM_VERTICAL_PE_LEFT_FILE.string() +
                             " file found : " + vertical_pe_left_path);

  if (!vertical_pe_right_file.is_open())
    throw std::runtime_error("BabyMIND " + BM_VERTICAL_PE_RIGHT_FILE.string() +
                             " file found : " + vertical_pe_right_path);

  for (std::size_t i = 0; i < 13; i++) {
    vertical_pe_right_file >> posx_formap_[i] >> pe_vertical_bm_right_[0][i] >> pe_vertical_bm_right_[1][i]
                           >> pe_vertical_bm_right_[2][i]
                           >> pe_vertical_bm_right_[3][i] >> pe_vertical_bm_right_[4][i] >> pe_vertical_bm_right_[5][i]
                           >> pe_vertical_bm_right_[6][i];
  }

  for (std::size_t i = 0; i < 13; i++) {
    vertical_pe_left_file >> posx_formap_[i] >> pe_vertical_bm_left_[0][i] >> pe_vertical_bm_left_[1][i]
                          >> pe_vertical_bm_left_[2][i]
                          >> pe_vertical_bm_left_[3][i] >> pe_vertical_bm_left_[4][i] >> pe_vertical_bm_left_[5][i]
                          >> pe_vertical_bm_left_[6][i];
  }

  vertical_pe_right_file.close();
  vertical_pe_left_file.close();


  {
    const std::string zpos_corr_path = (geometry_dir / BM_VERTICAL_ZPOS_CORR_FILE).string();
    std::ifstream zpos_corr_file((geometry_dir / BM_VERTICAL_ZPOS_CORR_FILE).string());
    if (!zpos_corr_file.is_open())
      throw std::runtime_error("BabyMIND " + BM_VERTICAL_ZPOS_CORR_FILE.string() +
                               " file found : " + zpos_corr_path);
    double temp[16];
    for (std::size_t i = 0; i < 18; i++) {
      zpos_corr_file >> temp[0] >> temp[1] >> temp[2] >> temp[3] >> temp[4] >> temp[5] >> temp[6] >> temp[7] >> temp[8]
                     >> temp[9] >> temp[10]
                     >> temp[11] >> temp[12] >> temp[13] >> temp[14] >> temp[15];

      for (int j = 0; j < 16; j++) {
        vertical_zpos_corr_[i][j] = temp[j];
      }
    }
    zpos_corr_file.close();
  }


}

void B2Dimension::ReadWallMrdGeometry(const fs::path &geometry_dir) {
  {
    const std::string  wallmrd_time_ly_path = (geometry_dir / WMRD_TIME_LY_FILE).string();
    TFile file(wallmrd_time_ly_path.c_str(), "READ");
    avt_bottom = (TH2F*)file.Get("lavt");
    avt_top = (TH2F*)file.Get("ravt");
    pe_bottom = (TH2F*)file.Get("lpe");
    pe_top = (TH2F*)file.Get("rpe");

    for(int iy=1; iy<=30; iy++)
      for(int iz=1; iz<=50; iz++){
        time_bottom[iy-1][iz-1] = (TH1F*)file.Get(Form("ltime_%d_%d", iy-1, iz-1));
        time_top[iy-1][iz-1] = (TH1F*)file.Get(Form("rtime_%d_%d", iy-1, iz-1));

        for(int ibin=0; ibin<100; ibin++){
          time_bottom_val[iy-1][iz-1][ibin] = time_bottom[iy-1][iz-1]->GetBinContent(ibin+1);
          time_top_val[iy-1][iz-1][ibin] = time_top[iy-1][iz-1]->GetBinContent(ibin+1);
        }

        avt_bottom_val[iy-1][iz-1] = avt_bottom->GetBinContent(iy, iz);
        avt_top_val[iy][iz-1] = avt_top->GetBinContent(iy, iz);

        pe_bottom_val[iy-1][iz-1] = pe_bottom->GetBinContent(iy, iz);
        pe_top_val[iy-1][iz-1] = pe_top->GetBinContent(iy, iz);
      }
  }
}

bool B2Dimension::GetPosPm(B2View view, unsigned int plane, unsigned int channel, TVector3 &pos) {

  // PLANE == 0 (front veto), 18 <= PLANE <= 21 (other VETO planes)
  if (plane == 0 ||
      (plane >= PM_NUM_FRONT_VETO_PLANES + PM_NUM_TRACKING_PLANES &&
       plane < PM_NUM_PLANES)) {
    return B2Dimension::GetPosVetoPm(view, plane, channel, pos);
  }
    // 1 <= PLANE <= 17 (tracking planes)
  else if (plane < PM_NUM_FRONT_VETO_PLANES + PM_NUM_TRACKING_PLANES) {
    if (channel >= PM_NUM_CHANNELS_ONE_TRACK_PLANE) {
      BOOST_LOG_TRIVIAL(error) << "GetPosVetoPm : channel number exceeds "
                               << PM_NUM_CHANNELS_ONE_TRACK_PLANE - 1 << " : " << channel;
      return false;
    }
    switch (view) {
      case B2View::kSideView :
        pos.SetX(0.);
        if (channel < 8) {
          pos.SetY(-PM_SCINTI_START_XY + PM_INGRID_SCINTI_LARGE * channel + 0.5 * PM_INGRID_SCINTI_LARGE);
          pos.SetZ(PM_FRONT_VETO_START_Z + PM_NEXT_PLANE_DISTANCE + PM_0Y_1X_PLANE_DISTANCE
                   + 2 * PM_NEXT_PLANE_DISTANCE * (plane - 1) + 0.5 * PM_INGRID_SCINTI_THICK);
        } else if (channel < 24) {
          pos.SetY(-PM_SCINTI_START_XY + PM_INGRID_SCINTI_LARGE * 8 + PM_SCIBAR_SCINTI_LARGE * (channel - 8)
                   + 0.5 * PM_SCIBAR_SCINTI_LARGE);
          pos.SetZ(PM_FRONT_VETO_START_Z + PM_NEXT_PLANE_DISTANCE + PM_0Y_1X_PLANE_DISTANCE
                   + 2 * PM_NEXT_PLANE_DISTANCE * (plane - 1) + 0.5 * PM_INGRID_SCINTI_THICK);
        } else {
          pos.SetY(-PM_SCINTI_START_XY + PM_INGRID_SCINTI_LARGE * 8 + PM_SCIBAR_SCINTI_LARGE * 16
                   + PM_INGRID_SCINTI_LARGE * (channel - 24) + 0.5 * PM_INGRID_SCINTI_LARGE);
          pos.SetZ(PM_FRONT_VETO_START_Z + PM_NEXT_PLANE_DISTANCE + PM_0Y_1X_PLANE_DISTANCE
                   + 2 * PM_NEXT_PLANE_DISTANCE * (plane - 1) + 0.5 * PM_INGRID_SCINTI_THICK);
        }
        break;
      case B2View::kTopView :
        pos.SetY(0.);
        if (channel < 8) {
          pos.SetX(-PM_SCINTI_START_XY + PM_INGRID_SCINTI_LARGE * channel + 0.5 * PM_INGRID_SCINTI_LARGE);
          pos.SetZ(PM_FRONT_VETO_START_Z + PM_NEXT_PLANE_DISTANCE + PM_0Y_1X_PLANE_DISTANCE
                   + 2 * PM_NEXT_PLANE_DISTANCE * (plane - 1) + PM_NEXT_PLANE_DISTANCE
                   + 0.5 * PM_INGRID_SCINTI_THICK);
        } else if (channel < 24) {
          pos.SetX(-PM_SCINTI_START_XY + PM_INGRID_SCINTI_LARGE * 8 + PM_SCIBAR_SCINTI_LARGE * (channel - 8)
                   + 0.5 * PM_SCIBAR_SCINTI_LARGE);
          pos.SetZ(PM_FRONT_VETO_START_Z + PM_NEXT_PLANE_DISTANCE + PM_0Y_1X_PLANE_DISTANCE
                   + 2 * PM_NEXT_PLANE_DISTANCE * (plane - 1) + PM_NEXT_PLANE_DISTANCE
                   + 0.5 * PM_INGRID_SCINTI_THICK);
        } else {
          pos.SetX(-PM_SCINTI_START_XY + PM_INGRID_SCINTI_LARGE * 8 + PM_SCIBAR_SCINTI_LARGE * 16
                   + PM_INGRID_SCINTI_LARGE * (channel - 24) + 0.5 * PM_INGRID_SCINTI_LARGE);
          pos.SetZ(PM_FRONT_VETO_START_Z + PM_NEXT_PLANE_DISTANCE + PM_0Y_1X_PLANE_DISTANCE
                   + 2 * PM_NEXT_PLANE_DISTANCE * (plane - 1) + PM_NEXT_PLANE_DISTANCE
                   + 0.5 * PM_INGRID_SCINTI_THICK);
        }
        break;
      case B2View::kUnknownView :
        BOOST_LOG_TRIVIAL(error) << "Unknown view";
        return false;
    }
  }
    // Invalid PLANE
  else {
    BOOST_LOG_TRIVIAL(error) << "Invalid plane number : " << plane;
    return false;
  }

  return true;
}

bool B2Dimension::GetPosVetoPm(B2View view, unsigned int plane, unsigned int channel, TVector3 &pos) {

  if (plane != 0 && !(plane >= PM_NUM_FRONT_VETO_PLANES + PM_NUM_TRACKING_PLANES && plane < PM_NUM_PLANES)) {
    BOOST_LOG_TRIVIAL(error) << "GetPosVetoPm : non veto plane : " << plane;
    return false;
  }

  if ((plane == 0 && channel >= PM_NUM_CHANNELS_FRONT_VETO) ||
      ((plane >= PM_NUM_FRONT_VETO_PLANES + PM_NUM_TRACKING_PLANES && plane <= PM_NUM_PLANES) &&
       channel >= PM_NUM_TRACKING_PLANES)) {
    BOOST_LOG_TRIVIAL(error) << "GetPosVetoPm : wrong channel " << channel;
    return false;
  }

  // Veto z position (other than front veto)
  pos.SetZ(PM_NON_FRONT_VETO_START_Z + PM_INGRID_SCINTI_LARGE * channel
           + 0.5 * PM_INGRID_SCINTI_LARGE);

  switch (view) {
    case B2View::kSideView :
      switch (GetVetoPlanePm(plane)) {
        case B2VetoPlane::kUpstreamVeto :
          pos.SetX(0.);
          pos.SetY(-PM_SCINTI_START_XY + PM_INGRID_SCINTI_LARGE * channel
                   + 0.5 * PM_INGRID_SCINTI_LARGE);
          pos.SetZ(PM_FRONT_VETO_START_Z + 0.5 * PM_INGRID_SCINTI_THICK);
          break;
        case B2VetoPlane::kBottomVeto :
          pos.SetX(PM_VETO_BOTTOM_X);
          pos.SetY(PM_VETO_BOTTOM_Y);
          break;
        case B2VetoPlane::kUpVeto :
          pos.SetX(0.);
          pos.SetY(PM_VETO_UP_Y);
          break;
        case B2VetoPlane::kLeftVeto :
        case B2VetoPlane::kRightVeto :
          BOOST_LOG_TRIVIAL(error) << "Not a side view VETO plane : " << plane;
          return false;
        default :
          BOOST_LOG_TRIVIAL(error) << "Not a VETO plane : " << plane;
          return false;
      }
      break;
    case B2View::kTopView :
      switch (GetVetoPlanePm(plane)) {
        case B2VetoPlane::kUpstreamVeto :
          pos.SetX(-PM_SCINTI_START_XY + PM_INGRID_SCINTI_LARGE * channel
                   + 0.5 * PM_INGRID_SCINTI_LARGE);
          pos.SetY(0.);
          pos.SetZ(PM_FRONT_VETO_START_Z + PM_NEXT_PLANE_DISTANCE
                   + 0.5 * PM_INGRID_SCINTI_THICK);
          break;
        case B2VetoPlane::kLeftVeto :
          pos.SetX(PM_VETO_LEFT_X);
          pos.SetY(0.);
          break;
        case B2VetoPlane::kRightVeto :
          pos.SetX(PM_VETO_RIGHT_X);
          pos.SetY(0.);
          break;
        case B2VetoPlane::kUpVeto :
        case B2VetoPlane::kBottomVeto :
          BOOST_LOG_TRIVIAL(error) << "Not a top view VETO plane : " << plane;
          return false;
        default :
          BOOST_LOG_TRIVIAL(error) << "Not a VETO plane : " << plane;
          return false;
      }
      break;
    case B2View::kUnknownView :
      BOOST_LOG_TRIVIAL(error) << "Unknown view";
      return false;
  }

  return true;
}

bool B2Dimension::GetErrorPm(B2View view, unsigned int plane, unsigned int channel, TVector3 &error) {
  // PLANE == 0 (front veto), 18 <= PLANE <= 21 (other VETO planes)
  if (plane == 0 || plane >= PM_NUM_FRONT_VETO_PLANES + PM_NUM_TRACKING_PLANES) {
    return B2Dimension::GetErrorVetoPm(view, plane, channel, error);
    // 1 <= PLANE <= 17 (tracking planes)
  } else if (plane <= PM_NUM_FRONT_VETO_PLANES + PM_NUM_TRACKING_PLANES) {
    if (channel >= PM_NUM_CHANNELS_ONE_TRACK_PLANE) {
      BOOST_LOG_TRIVIAL(error) << "GetErrorPm : channel number exceeds "
                               << PM_NUM_CHANNELS_ONE_TRACK_PLANE - 1 << " : " << channel;
      return false;
    }
    switch (view) {
      case B2View::kSideView:
        if (channel <= 7 || channel >= 24) {
          error.SetX(0.5 * PM_SCINTI_BAR_LENGTH);
          error.SetY(0.5 * PM_INGRID_SCINTI_LARGE);
          error.SetZ(0.5 * PM_INGRID_SCINTI_THICK);
        } else {
          error.SetX(0.5 * PM_SCINTI_BAR_LENGTH);
          error.SetY(0.5 * PM_SCIBAR_SCINTI_LARGE);
          error.SetZ(0.5 * PM_SCIBAR_SCINTI_THICK);
        }
        break;
      case B2View::kTopView:
        if (channel <= 7 || channel >= 24) {
          error.SetX(0.5 * PM_INGRID_SCINTI_LARGE);
          error.SetY(0.5 * PM_SCINTI_BAR_LENGTH);
          error.SetZ(0.5 * PM_INGRID_SCINTI_THICK);
        } else {
          error.SetX(0.5 * PM_SCIBAR_SCINTI_LARGE);
          error.SetY(0.5 * PM_SCINTI_BAR_LENGTH);
          error.SetZ(0.5 * PM_SCIBAR_SCINTI_THICK);
        }
        break;
      case B2View::kUnknownView:
        BOOST_LOG_TRIVIAL(error) << "Unknown view";
        return false;
    }
  } else {
    BOOST_LOG_TRIVIAL(error) << "Invalid plane number : " << plane;
    return false;
  }
  return true;
}

bool B2Dimension::GetErrorVetoPm(B2View view, unsigned int plane, unsigned int channel, TVector3 &error) {
  if (plane != 0 && !(plane >= PM_NUM_FRONT_VETO_PLANES + PM_NUM_TRACKING_PLANES && plane < PM_NUM_PLANES)) {
    BOOST_LOG_TRIVIAL(error) << "GetErrorVetoPm : non veto plane : " << plane;
    return false;
  }
  if ((plane == 0 && channel >= PM_NUM_CHANNELS_FRONT_VETO) ||
      ((plane >= PM_NUM_FRONT_VETO_PLANES + PM_NUM_TRACKING_PLANES && plane <= PM_NUM_PLANES) &&
       channel >= PM_NUM_TRACKING_PLANES)) {
    BOOST_LOG_TRIVIAL(error) << "GetErrorVetoPm : wrong channel " << channel;
    return false;
  }
  switch (view) {
    case B2View::kSideView:
      switch (GetVetoPlanePm(plane)) {
        case B2VetoPlane::kUpstreamVeto:
          error.SetX(0.5 * PM_SCINTI_BAR_LENGTH);
          error.SetY(0.5 * PM_INGRID_SCINTI_LARGE);
          error.SetZ(0.5 * PM_INGRID_SCINTI_THICK);
          break;
        case B2VetoPlane::kBottomVeto:
          error.SetX(0.5 * PM_SHORT_VETO_SCINTI_LENGTH);
          error.SetY(0.5 * PM_INGRID_SCINTI_THICK);
          error.SetZ(0.5 * PM_INGRID_SCINTI_LARGE);
          break;
        case B2VetoPlane::kUpVeto:
          error.SetX(0.5 * PM_LONG_VETO_SCINTI_LENGTH);
          error.SetY(0.5 * PM_INGRID_SCINTI_THICK);
          error.SetZ(0.5 * PM_INGRID_SCINTI_LARGE);
          break;
        default:
          BOOST_LOG_TRIVIAL(error) << "Wrong VETO plane : " << plane;
          return false;
      }
      break;
    case B2View::kTopView:
      switch (GetVetoPlanePm(plane)) {
        case B2VetoPlane::kUpstreamVeto:
          error.SetX(0.5 * PM_INGRID_SCINTI_LARGE);
          error.SetY(0.5 * PM_SCINTI_BAR_LENGTH);
          error.SetZ(0.5 * PM_INGRID_SCINTI_THICK);
          break;
        case B2VetoPlane::kLeftVeto:
        case B2VetoPlane::kRightVeto:
          error.SetX(0.5 * PM_INGRID_SCINTI_THICK);
          error.SetY(0.5 * PM_LONG_VETO_SCINTI_LENGTH);
          error.SetZ(0.5 * PM_INGRID_SCINTI_LARGE);
          break;
        default:
          BOOST_LOG_TRIVIAL(error) << "Wrong VETO plane : " << plane;
          return false;
      }
      break;
    case B2View::kUnknownView:
      BOOST_LOG_TRIVIAL(error) << "Unknown view";
      return false;
  }
  return true;
}

B2VetoPlane B2Dimension::GetVetoPlanePm(unsigned plane) {
  switch (plane) {
    case 0:
      return B2VetoPlane::kUpstreamVeto;
    case 18:
      return B2VetoPlane::kBottomVeto;
    case 19:
      return B2VetoPlane::kLeftVeto;
    case 20:
      return B2VetoPlane::kUpVeto;
    case 21:
      return B2VetoPlane::kRightVeto;
    default:
      return B2VetoPlane::kNotVeto;
  }
}

bool B2Dimension::GetPosWgs(B2View view, unsigned plane, unsigned grid_slot, B2GridPlane grid, TVector3 &pos) const {

  if (plane >= WGS_NUM_PLANES) {
    BOOST_LOG_TRIVIAL(error) << "GetPosWgs : plane number exceeds " << WGS_NUM_PLANES - 1 << " : " << plane;
    return false;
  }
  if (grid_slot >= WGS_NUM_SLOTS) {
    BOOST_LOG_TRIVIAL(error) << "GetPosWgs : slot number exceeds " << WGS_NUM_SLOTS - 1 << " : " << grid_slot;
    return false;
  }
  if (grid > WGS_MAX_GRID_NUMBER) {
    BOOST_LOG_TRIVIAL(error) << "GetPosWgs : grid number exceeds " << WGS_MAX_GRID_NUMBER << " : " << grid;
    return false;
  }

  // X/Y position is in the sub-module coordinate, offsets are applied at last
  // Z position is in water box
  switch (view) {
    case B2View::kSideView: {
      pos.SetX(0);

      switch (grid) {
        case kPlaneScintillator:
          // offset + half of scintillator width + wg_position_xy_
          pos.SetY(WGS_OFFSET_XY_PLANE + 0.5 * WGS_SCINTI_LARGE + wg_position_xy_[view][plane][grid_slot]);
          // offset + half of scintillator width + wg_position_z_
          pos.SetZ(WGS_OFFSET_Z + 0.5 * WGS_SCINTI_THICK + wg_position_z_[view][plane]);
          break;
        case kGridLeftScintillator:
          // center of the first cut from scintillator edge + loop
          pos.SetY(WGS_OFFSET_XY_GRID + WGS_GRID_SPACING * grid_slot);
          // offset + thickness of the plane scintillator in front + half of the scinti width + wg_position_z_ of the
          // side view plane scintillator
          pos.SetZ(WGS_OFFSET_Z + WGS_SCINTI_THICK + 0.5 * WGS_SCINTI_LARGE +
                   wg_position_z_[B2View::kSideView][plane]);
          break;
        case kGridRightScintillator:
          // center of the first cut from scintillator edge + loop
          pos.SetY(WGS_OFFSET_XY_GRID + WGS_GRID_SPACING * grid_slot);
          // offset + thickness of the plane scintillator in front + half of the scinti width + wg_position_z_ of the
          // side view plane scintillator
          pos.SetZ(WGS_OFFSET_Z + WGS_SCINTI_THICK + 0.5 * WGS_SCINTI_LARGE +
                   wg_position_z_[B2View::kTopView][plane]);
          break;
        case kUnknownScintillator:
          break;
      }
      break;
    }
    case B2View::kTopView: {
      pos.SetY(0);

      switch (grid) {
        case kPlaneScintillator:
          // offset + half of scintillator width + wg_position_xy_
          pos.SetX(WGS_OFFSET_XY_PLANE + 0.5 * WGS_SCINTI_LARGE + wg_position_xy_[view][plane][grid_slot]);
          // offset + half of scintillator width + wg_position_z_
          pos.SetZ(WGS_OFFSET_Z + 0.5 * WGS_SCINTI_THICK + wg_position_z_[view][plane]);
          break;
        case kGridLeftScintillator:
          // center of the first cut from scintillator edge + loop
          pos.SetX(WGS_OFFSET_XY_GRID + WGS_GRID_SPACING * grid_slot);
          // offset + thickness of the plane scintillator in front + half of the scinti width + wg_position_z_ of the
          // side view plane scintillator
          pos.SetZ(WGS_OFFSET_Z + WGS_SCINTI_THICK + 0.5 * WGS_SCINTI_LARGE +
                   wg_position_z_[B2View::kSideView][plane]);
          break;
        case kGridRightScintillator:
          // center of the first cut from scintillator edge + loop
          pos.SetX(WGS_OFFSET_XY_GRID + WGS_GRID_SPACING * grid_slot);
          // offset + thickness of the plane scintillator in front + half of the scinti width + wg_position_z_ of the
          // side view plane scintillator
          pos.SetZ(WGS_OFFSET_Z + WGS_SCINTI_THICK + 0.5 * WGS_SCINTI_LARGE +
                   wg_position_z_[B2View::kTopView][plane]);
          break;
        case kUnknownScintillator:
          break;
      }
      break;
    }
    case B2View::kUnknownView: {
      BOOST_LOG_TRIVIAL(error) << "Unknown view";
      return false;
    }

  }

  // submodules are not in the center of the water box
  // X/Y offsets should be applied
  pos.SetX(pos.X() - WGS_SCI_OFFSET_TO_WATER_X);
  pos.SetY(pos.Y() - WGS_SCI_OFFSET_TO_WATER_Y);

  return true;

}

bool B2Dimension::GetGridWgs(unsigned slot, unsigned &grid_slot, B2GridPlane &grid) {
  if (slot < 40) {
    grid = B2GridPlane::kPlaneScintillator;
    grid_slot = slot;
  } else if (slot >= 40 && slot < 60) {
    grid = B2GridPlane::kGridLeftScintillator;
    grid_slot = slot - 40;
  } else if (slot >= 60 && slot < 80) {
    grid = B2GridPlane::kGridRightScintillator;
    grid_slot = slot - 60;
  } else {
    BOOST_LOG_TRIVIAL(error) << "GetGridWgs : slot number exceeds " << WGS_NUM_SLOTS << " : " << slot;
    return false;
  }
  return true;
}

bool B2Dimension::GetPosWgs(B2View view, unsigned plane, unsigned slot, TVector3 &pos) const {
  B2GridPlane grid;
  unsigned grid_slot;
  if (!this->GetGridWgs(slot, grid_slot, grid))
    return false;
  return this->GetPosWgs(view, plane, grid_slot, grid, pos);
}


bool B2Dimension::GetPosWgsMppc(B2View view, unsigned int plane, unsigned int slot, TVector3 &pos) const {
  if (!GetPosWgs(view, plane, slot, pos))
    return false;
  switch (view) {
    case B2View::kTopView :
      pos.SetY(pos.Y() + 0.5 * WGS_SCINTI_BAR_LENGTH + WGS_FIBER_BUNDLE_LENGTH);
      break;
    case B2View::kSideView :
      pos.SetX(pos.X() + 0.5 * WGS_SCINTI_BAR_LENGTH + WGS_FIBER_BUNDLE_LENGTH);
      break;
    default :
      throw std::invalid_argument("Error : view value is not valid : " + std::to_string(view));
  }
  return true;
}

B2WallMrdDirection B2Dimension::GetWallMrdDirection(B2Detector detector) {
  switch (detector) {
    case B2Detector::kWallMrdSouth:
      return B2WallMrdDirection::kWallMrdSouthDirection;
    case B2Detector::kWallMrdNorth:
      return B2WallMrdDirection::kWallMrdNorthDirection;
    default:
      std::stringstream ss;
      ss << "GetWallMrdDirection : wrong detector number  : " << detector
         << " (" << DETECTOR_NAMES.at(detector) << ")";
      throw std::invalid_argument(ss.str());
  }
}

bool B2Dimension::GetPosWallMrdIron(B2Detector detector, unsigned plane, TVector3 &pos) {
  if (detector != B2Detector::kWallMrdNorth && detector != B2Detector::kWallMrdSouth) {
    BOOST_LOG_TRIVIAL(error) << "GetPosWallMrdIron : detector can only be a WallMRD : " << detector;
    return false;
  }
  if (plane >= WM_NUM_IRON_PLANES) {
    BOOST_LOG_TRIVIAL(error) << "GetPosWallMrdIron : plane number exceeds "
                             << WM_NUM_IRON_PLANES - 1 << " : " << plane;
    return false;
  }

  const auto direction = B2Dimension::GetWallMrdDirection(detector);

  if (plane == 0 || plane == 10) { // front iron plates
    pos.SetX((WM_START_IRON_X + WM_PLANES_GAP * plane) * direction);
    pos.SetY(0.);
    pos.SetZ(0.);
  } else if (plane < 1 + WM_NUM_INNER_IRON_PLANES) { // inner iron plates
    pos.SetX((WM_START_IRON_X + WM_PLANES_GAP * plane) * direction);
    pos.SetY(WM_INNER_OFFSET_Y);
    pos.SetZ(0.);
  } else if (plane == 11) { // upstream iron plate
    pos.SetX(0.);
    pos.SetY(WM_SIDE_IRON_OFFSET_Y);
    pos.SetZ(-WM_SIDE_IRON_OFFSET_Z);
  } else { // downstream iron plate
    pos.SetX(0.);
    pos.SetY(WM_SIDE_IRON_OFFSET_Y);
    pos.SetZ(WM_SIDE_IRON_OFFSET_Z);
  }

  return true;
}

bool B2Dimension::GetPosWallMrd(B2Detector detector, unsigned plane, unsigned slot, TVector3 &pos) {
  if (detector != B2Detector::kWallMrdNorth && detector != B2Detector::kWallMrdSouth) {
    BOOST_LOG_TRIVIAL(error) << "GetPosWallMrdIron : detector can only be a WallMRD : " << detector;
    return false;
  }
  if (plane >= WM_NUM_SCINTI_PLANES) {
    BOOST_LOG_TRIVIAL(error) << "GetPosWallMrd : plane number exceeds "
                             << WM_NUM_SCINTI_PLANES - 1 << " : " << plane;
    return false;
  }
  if (slot >= WM_NUM_SCINTI_IN_ONE_PLANE) {
    BOOST_LOG_TRIVIAL(error) << "GetPosWallMrd : slot number exceeds "
                             << WM_NUM_SCINTI_IN_ONE_PLANE - 1 << " : " << slot;
    return false;
  }

  const auto direction = B2Dimension::GetWallMrdDirection(detector);
  pos.SetX(WM_PLANES_GAP * plane * direction);
  pos.SetY(0);
  pos.SetZ(WM_SCINTI_LARGE * slot);
  // Apply offset
  pos.SetX(pos.X() + direction * WM_GLOBAL_OFFSET_X);
  pos.SetY(pos.Y() + WM_INNER_OFFSET_Y);
  pos.SetZ(pos.Z() + WM_GLOBAL_OFFSET_Z);
  return true;
}

bool B2Dimension::GetPosBm(B2View view, unsigned plane, unsigned slot, TVector3 &pos) const {
  if (plane >= BM_NUM_TRACKING_PLANES) {
    BOOST_LOG_TRIVIAL(error) << "GetPosBm : plane number exceeds "
                             << BM_NUM_TRACKING_PLANES - 1 << " : " << plane;
    return false;
  }

  switch (view) {
    case B2View::kSideView:
      if (slot > BM_NUM_HORIZ_SCINTI_ONE_PLANE) {
        BOOST_LOG_TRIVIAL(error) << "GetPosBm : channel number exceeds "
                                 << BM_NUM_HORIZ_SCINTI_ONE_PLANE - 1 << " : " << slot;
        return false;
      }
      pos.SetX(0);
      pos.SetZ(bm_position_z_[plane] + (slot % 2 + 1) * 1. * cm + 5. * cm);
      pos.SetY(bm_position_y_[slot] + bm_correction_y_[plane]);
      break;
    case B2View::kTopView:
      if (slot > BM_NUM_VERTICAL_SCINTI_ONE_PLANE) {
        BOOST_LOG_TRIVIAL(error) << "GetPosBm : channel number exceeds "
                                 << BM_NUM_VERTICAL_SCINTI_ONE_PLANE - 1 << " : " << slot;
        return false;
      }

      pos.SetY(0);
      pos.SetZ(bm_position_z_[plane] + (slot % 2) * 3. * cm + 5. * cm + vertical_zpos_corr_[plane][slot]);
      //pos.SetZ(bm_position_z_[plane] + (slot % 2) * 3. * cm + 5. * cm);
      pos.SetX(bm_position_x_[slot]);
      break;
    default:
      return false;
  }
  pos.SetZ(pos.Z() + BABYMIND_OFFSET_Z);
  return true;
}

B2Readout B2Dimension::GetReadoutYasu(unsigned slot) {
  return slot < 0.5 * YASU_NUM_SLOTS_ONE_PLANE ? B2Readout::kLeftReadout : B2Readout::kRightReadout;
}

B2ScintillatorType B2Dimension::GetScintillatorTypeYasu(unsigned slot) {
  switch (GetReadoutYasu(slot)) {
    case B2Readout::kLeftReadout:
      return B2ScintillatorType::kLeft;
    case B2Readout::kRightReadout:
      return B2ScintillatorType::kRight;
    default:
      return B2ScintillatorType::kUnknownScintillatorType;
  }
}

bool B2Dimension::GetPosYasu(unsigned plane, unsigned slot, TVector3 &pos) const {
  if (plane >= YASU_NUM_PLANES) {
    BOOST_LOG_TRIVIAL(error) << "GetPosYasu : YASU plane number exceeds "
                             << YASU_NUM_PLANES - 1 << " : " << plane;
    return false;
  }
  if (slot >= YASU_NUM_SLOTS_ONE_PLANE) {
    BOOST_LOG_TRIVIAL(error) << "GetPosYasu : YASU slot number exceeds "
                             << YASU_NUM_SLOTS_ONE_PLANE - 1 << " : " << slot;
    return false;
  }

  switch (GetReadoutYasu(slot)) {
    case B2Readout::kLeftReadout:
      pos.SetX(-0.5 * WM_SCINTI_LENGTH);
      pos.SetY(yasu_position_y_[slot] + yasu_gap_y_[slot]);
      pos.SetZ(yasu_position_z_[plane]);
      break;
    case B2Readout::kRightReadout:
      pos.SetX(0.5 * WM_SCINTI_LENGTH);
      pos.SetY(yasu_position_y_[slot] + yasu_gap_y_[slot]);
      pos.SetZ(yasu_position_z_[plane]);
      break;
    default:
      return false;
  }
  pos.SetZ(pos.Z() + BABYMIND_OFFSET_Z);
  return true;
}

bool B2Dimension::GetPosNinjaTracker(B2View view, unsigned int plane, unsigned int slot, TVector3 &pos) {

  double offsetxy[4] = {NINJA_SCI_GAP * 5 / 6., NINJA_SCI_GAP / 6., NINJA_SCI_GAP * 2 / 3., 0.};
  double pvctot[4] = {0.0 * cm, 0.3 * cm, 0.3 * cm, 0.6 * cm};

  switch (view) {
    case B2View::kTopView:
      pos.SetX(-NINJA_SCI_OFFSET_Y - 0.5 * NINJA_SCI_WIDTH - NINJA_SCI_GAP * 4 / 3. * slot - offsetxy[3 - plane]);
      pos.SetY(-NINJA_SCI_OFFSET_X + 0.5 * NINJA_VERTI_SCI_LENGTH);
      break;
    case B2View::kSideView:
      pos.SetX(NINJA_SCI_OFFSET_X - 0.5 * NINJA_HORIZ_SCI_LENGTH);
      pos.SetY(NINJA_SCI_OFFSET_Y + 0.5 * NINJA_SCI_WIDTH + NINJA_SCI_GAP * 4 / 3. * slot + offsetxy[plane]);
      break;
    case B2View::kUnknownView:
      BOOST_LOG_TRIVIAL(error) << "Unknown view";
      return false;
  }

  pos.SetZ(2. * cm * view + 1. * mm + NINJA_SCI_THICK * plane + pvctot[plane]
           + NINJA_SCI_THICK / 2. - 0.5 * NINJA_TRACKER_FRAME_THICK);

  return true;
}

bool B2Dimension::GetErrorWallMrd(TVector3 &error) {
  error.SetX(0.5 * WM_SCINTI_THICK);
  error.SetY(0.5 * WM_SCINTI_LENGTH);
  error.SetZ(0.5 * WM_SCINTI_LARGE);
  return true;
}

bool B2Dimension::GetErrorWgs(B2View view, unsigned int slot, TVector3 &error) {
  switch (view) {
    case B2View::kSideView:
      if (slot <= 39u) {
        error.SetX(0.5 * WGS_SCINTI_BAR_LENGTH);
        error.SetY(0.5 * WGS_SCINTI_LARGE);
        error.SetZ(0.5 * WGS_SCINTI_THICK);
      } else {
        error.SetX(0.5 * WGS_SCINTI_BAR_LENGTH);
        error.SetY(0.5 * WGS_SCINTI_THICK);
        error.SetZ(0.5 * WGS_SCINTI_LARGE);
      }
      break;
    case B2View::kTopView:
      if (slot <= 39u) {
        error.SetX(0.5 * WGS_SCINTI_LARGE);
        error.SetY(0.5 * WGS_SCINTI_BAR_LENGTH);
        error.SetZ(0.5 * WGS_SCINTI_THICK);
      } else {
        error.SetX(0.5 * WGS_SCINTI_THICK);
        error.SetY(0.5 * WGS_SCINTI_BAR_LENGTH);
        error.SetZ(0.5 * WGS_SCINTI_LARGE);
      }
      break;
    default:
      return false;
  }
  return true;
}

bool B2Dimension::GetErrorBm(B2View view, TVector3 &error) {
  switch (view) {
    case B2View::kSideView:
      error.SetX(0.5 * BM_HORIZONTAL_SCINTI_LENGTH);
      error.SetZ(0.5 * BM_HORIZONTAL_SCINTI_THICK);
      error.SetY(0.5 * BM_HORIZONTAL_SCINTI_LARGE);
      break;
    case B2View::kTopView:
      error.SetX(0.5 * BM_VERTICAL_SCINTI_LARGE);
      error.SetY(0.5 * BM_VERTICAL_SCINTI_LENGTH);
      error.SetZ(0.5 * BM_VERTICAL_SCINTI_THICK);
      break;
    default:
      return false;
  }
  return true;
}

bool B2Dimension::GetErrorYasu(B2View view, TVector3 &error) {
  switch (view) {
    case B2View::kSideView:
      error.SetX(0.5 * WM_SCINTI_LENGTH);
      error.SetY(0.5 * WM_SCINTI_LARGE);
      error.SetZ(0.5 * WM_SCINTI_THICK);
      break;
    default:
      return false;
  }
  return true;
}

bool B2Dimension::GetErrorNinja(B2View view, TVector3 &error) {
  switch (view) {
    case B2View::kSideView:
      error.SetX(0.5 * WGS_SCINTI_BAR_LENGTH);
      error.SetY(0.5 * WGS_SCINTI_LARGE);
      error.SetZ(0.5 * WGS_SCINTI_THICK);
      break;
    case B2View::kTopView:
      error.SetX(0.5 * WGS_SCINTI_LARGE);
      error.SetY(0.5 * WGS_SCINTI_BAR_LENGTH);
      error.SetZ(0.5 * WGS_SCINTI_THICK);
      break;
    default:
      return false;
  }
  return true;
}

bool
B2Dimension::GetError(B2Detector detector_id, B2View view, unsigned int plane, unsigned int slot, TVector3 &error) {
  switch (detector_id) {
    case B2Detector::kProtonModule: {
      return B2Dimension::GetErrorPm(view, plane, slot, error);
    }
    case B2Detector::kWagasciUpstream:
    case B2Detector::kWagasciDownstream: {
      return B2Dimension::GetErrorWgs(view, slot, error);
    }
    case B2Detector::kWallMrdNorth:
    case B2Detector::kWallMrdSouth: {
      return B2Dimension::GetErrorWallMrd(error);
    }
    case B2Detector::kBabyMind: {
      return B2Dimension::GetErrorBm(view, error);
    }
    case B2Detector::kYasuTracker: {
      return B2Dimension::GetErrorYasu(view, error);
    }
    case B2Detector::kNinja: {
      return B2Dimension::GetErrorNinja(view, error);
    }
    default:
      break;
  }
  return false;
}

bool B2Dimension::GetPosition(B2Detector detector_id, B2View view, unsigned int plane, unsigned int slot,
                              TVector3 &pos) const {
  switch (detector_id) {
    case B2Detector::kProtonModule: {
      return B2Dimension::GetPosPm(view, plane, slot, pos);
    }
    case B2Detector::kWagasciUpstream:
    case B2Detector::kWagasciDownstream: {
      return B2Dimension::GetPosWgs(view, plane, slot, pos);
    }
    case B2Detector::kWallMrdNorth:
    case B2Detector::kWallMrdSouth: {
      return B2Dimension::GetPosWallMrd(detector_id, plane, slot, pos);
    }
    case B2Detector::kBabyMind: {
      return B2Dimension::GetPosBm(view, plane, slot, pos);
    }
    case B2Detector::kYasuTracker: {
      return B2Dimension::GetPosYasu(plane, slot, pos);
    }
    case B2Detector::kNinja: {
      return B2Dimension::GetPosNinjaTracker(view, plane, slot, pos);
    }
    default:
      break;
  }
  return false;
}

bool B2Dimension::CheckDeadChannel(B2Detector detector, B2View view, unsigned int readout, unsigned int plane,
                                   unsigned int slot) {

  std::vector<std::vector<unsigned int> > deadchannel_side{{0, 0,  49},
                                                           {0, 0,  51},
                                                           {0, 1,  81},
                                                           {0, 2,  33},
                                                           {1, 0,  7},
                                                           {1, 0,  47},
                                                           {0, 8,  11},
                                                           {1, 6,  15},
                                                           {1, 7,  64},
                                                           {1, 7,  69},
                                                           {0, 11, 17},
                                                           {1, 11, 47},
                                                           {1, 16, 67},
                                                           {1, 16, 81},
                                                           {1, 17, 43},
                                                           {1, 17, 49}};
  std::vector<std::vector<unsigned int> > deadchannel_top{{0, 0, 6}};
  std::vector<std::vector<unsigned int> > deadchannel_ninja_side = {{2, 30}};
  std::vector<std::vector<unsigned int> > deadchannel_ninja_top  = {{1,  0},
								    {1,  1},
								    {1,  7},
								    {2, 20}}; // view, plane, slot
  std::vector<unsigned int> candidate{readout, plane, slot};

  if (detector == B2Detector::kBabyMind) {
    if (view == B2View::kSideView) {
      if (std::find(deadchannel_side.begin(), deadchannel_side.end(), candidate) != deadchannel_side.end()) {
        return true;
      }
    } else if (view == B2View::kTopView) {
      if (std::find(deadchannel_top.begin(), deadchannel_top.end(), candidate) != deadchannel_top.end()) {
        return true;
      }
    }
  } else if (detector == B2Detector::kNinja) {
    std::vector<unsigned int> candidate_ninja = {plane, slot};
    if (view == B2View::kSideView) {
      if (std::find(deadchannel_ninja_side.begin(), deadchannel_ninja_side.end(), candidate_ninja) != deadchannel_ninja_side.end()) {
	return true;
      }
    } else if (view == B2View::kTopView) {
      if (std::find(deadchannel_ninja_top.begin(), deadchannel_ninja_top.end(), candidate_ninja) != deadchannel_ninja_top.end()) {
	return true;
      }
    }
  }
  return false;
}

double B2Dimension::GetBMVerticalPE(double posx, double posy, B2Readout ireadout) const {
  double pe;
  double borderposy[8] = {0, 300, 750, 1200, 1500, 1750, 1900, 2300};
  int idx = 0;
  int idy = 0;

  for (int iy = 0; iy < 7; iy++) {
    if (borderposy[iy] < posy && posy < borderposy[iy + 1]) {
      idy = iy;
    }
  }

  for (int ix = 0; ix < 13; ix++) {
    if (ix == 0 && posx < posx_formap_[ix] * 10) {
      idx = 0;
    } else if (ix > 0 && posx_formap_[ix] * 10 <= posx && posx <= posx_formap_[ix + 1] * 10) {
      idx = ix;
    }
  }

  BOOST_LOG_TRIVIAL(debug) << "idx = " << idx << " idy = " << idy;

  switch (ireadout) {
    case kTopReadout:
    case kLeftReadout:
      pe = pe_vertical_bm_left_[idy][idx];
      break;
    case kBottomReadout:
    case kRightReadout:
      pe = pe_vertical_bm_right_[idy][idx];
      break;
    default:
      throw std::invalid_argument("Readout not recognized : " + READOUT_NAMES.at(ireadout));
  }

  return pe;
}

double B2Dimension::GetAverageTime(double posy, double posz, B2Readout readout) const{
  Int_t id_y = posy / 4.;
  Int_t id_z = posz / 4.;
  
  if(readout == B2Readout::kBottomReadout){
    return avt_bottom_val[id_y][id_z];
  }else if(readout == B2Readout::kTopReadout){
    return avt_top_val[id_y][id_z];
  }else{
    return -1.;
  }
}

double B2Dimension::GetAveragePe(double posy, double posz, B2Readout readout) const{
  Int_t id_y = posy / 4.;
  Int_t id_z = posz / 4.;

  if(readout == B2Readout::kBottomReadout){
    BOOST_LOG_TRIVIAL(debug) << id_y << " " << id_z << " " << pe_bottom_val[id_y][id_z];
    return pe_bottom_val[id_y][id_z];
  }else if(readout == B2Readout::kTopReadout){
    BOOST_LOG_TRIVIAL(debug) << id_y << " " << id_z << " " << pe_top_val[id_y][id_z];
    return pe_top_val[id_y][id_z];
  }else{
    return -1.;
  }
}

double B2Dimension::GetRondomTime(double posy, double posz, B2Readout readout) const{
  double randomtime = -1;
  Int_t id_y = posy / 4.;
  Int_t id_z = posz / 4.;

  TH1F hist_time("hist_time", "", 140, -1, 6);
  
  if(readout == B2Readout::kBottomReadout){
    for(int ibin=0; ibin<100; ibin++){
      Double_t value = time_bottom_val[id_y][id_z][ibin];
      hist_time.SetBinContent(ibin+1, value);
    }
  }else if(readout == B2Readout::kTopReadout){
    for(int ibin=0; ibin<100; ibin++){
      Double_t value = time_top_val[id_y][id_z][ibin];
      hist_time.SetBinContent(ibin+1, value);    
    }
  }
    
  randomtime = hist_time.GetRandom();

  return randomtime;
}

