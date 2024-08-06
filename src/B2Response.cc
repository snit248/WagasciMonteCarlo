#include "B2Response.hh"
#include "B2HitSummary.hh"

// BOOST includes
#include <boost/make_unique.hpp>

// ROOT includes
#include <TRandom.h>
#include <CLHEP/Random/RandPoisson.h>

////////////////////////////////////////////////////////////////////////
//                            Interface                               //
////////////////////////////////////////////////////////////////////////

B2DetectorResponse::B2DetectorResponse(const B2Dimension &dimension) :
    b2_dimension_(dimension) {}

void B2DetectorResponse::ApplyScintiResponse(G4double &edep, const G4Track &track) {
  const auto kinetic_energy = track.GetKineticEnergy();
  const auto *particle = track.GetDefinition();
  const auto *material = track.GetMaterial();
  if (particle->GetPDGCharge() == 0) {
    BOOST_LOG_TRIVIAL(debug) << "No scintillator response for neutral particles";
    edep = 0;
  } else {
    const auto dedx = emcal_.GetDEDX(kinetic_energy, particle, material) / (MeV / cm);
    edep /= (1. + cbirks_ * dedx);
  }
}

void B2DetectorResponse::ApplyTDCResponse(G4int &tdc, G4double time) const {
  tdc = 0;
}

void B2DetectorResponse::ApplyOpticalSimulation(G4double &edep, const G4ThreeVector &pos, G4double &pe, G4double &time,
                                                G4int slot, B2Readout readout) const {
  pe = 0;
  time = 0;
}

////////////////////////////////////////////////////////////////////////
//                             B2Response                             //
////////////////////////////////////////////////////////////////////////

B2Response::B2Response(const B2Dimension &dimension) {
  this->detector_response_.emplace(B2Detector::kProtonModule,
                                   boost::make_unique<B2ProtonModuleResponse>(dimension));
  this->detector_response_.emplace(B2Detector::kWagasciUpstream,
                                   boost::make_unique<B2WagasciUpstreamResponse>(dimension));
  this->detector_response_.emplace(B2Detector::kWagasciDownstream,
                                   boost::make_unique<B2WagasciDownstreamResponse>(dimension));
  this->detector_response_.emplace(B2Detector::kWallMrdNorth,
                                   boost::make_unique<B2WallMrdNorthResponse>(dimension));
  this->detector_response_.emplace(B2Detector::kWallMrdSouth,
                                   boost::make_unique<B2WallMrdSouthResponse>(dimension));
  this->detector_response_.emplace(B2Detector::kBabyMind,
                                   boost::make_unique<B2BabyMindResponse>(dimension));
  this->detector_response_.emplace(B2Detector::kNinja,
                                   boost::make_unique<B2NinjaResponse>(dimension));
  this->detector_response_.emplace(B2Detector::kYasuTracker,
                                   boost::make_unique<B2YASUTrackerResponse>(dimension));

}

B2Response &B2Response::SwitchDetector(B2Detector detector) {
  BOOST_LOG_TRIVIAL(debug) << "Context: Transition to " << DETECTOR_NAMES.at(detector);
  this->current_detector_ = detector;
  return *this;
}

void B2Response::ApplyScintiResponse(G4double &edep, const G4Track &track) {
  this->detector_response_.at(current_detector_)->ApplyScintiResponse(edep, track);
}

void B2Response::ApplyLightCollection(G4double &edep, B2View view, G4int pln, G4int ch,
                                      const G4ThreeVector &pos) const {
  this->detector_response_.at(current_detector_)->ApplyLightCollection(edep, view, pln, ch, pos);
}

void B2Response::ApplyFiberResponse(G4double &edep, G4double &time, B2View view, G4int pln, G4int slot,
                                    B2Readout readout, const G4ThreeVector &pos) const {
  this->detector_response_.at(current_detector_)->ApplyFiberResponse(edep, time, view, pln, slot, readout, pos);
}

void B2Response::ApplyMPPCResponse(G4double &pe, G4double edep, B2View view, G4int pln, G4int slot, B2Readout readout,
                                   const G4ThreeVector &pos) const {
  this->detector_response_.at(current_detector_)->ApplyMPPCResponse(pe, edep, view, pln, slot, readout, pos);
}

void B2Response::ApplyADCResponse(G4double &pe, G4double &lope, G4int &adc, G4int &loadc) const {
  this->detector_response_.at(current_detector_)->ApplyADCResponse(pe, lope, adc, loadc);
}

void B2Response::ApplyTDCResponse(G4int &tdc, G4double time) const {
  this->detector_response_.at(current_detector_)->ApplyTDCResponse(tdc, time);
}

void B2Response::ApplyOpticalSimulation(G4double &edep, const G4ThreeVector &pos, G4double &pe, G4double &time,
                                        G4int slot, B2Readout readout) const {
  this->detector_response_.at(current_detector_)->ApplyOpticalSimulation(edep, pos, pe, time, slot, readout);
}

////////////////////////////////////////////////////////////////////////
//                           Proton Module                            //
////////////////////////////////////////////////////////////////////////

void B2ProtonModuleResponse::ApplyLightCollection(G4double &edep, B2View view, G4int pln, G4int ch,
                                                  const G4ThreeVector &pos) const {

  G4double x;

  switch (view) {
    case B2View::kTopView :
      x = std::fabs(0.5 * PM_SCINTI_BAR_LENGTH + pos.x());
      break;
    case B2View::kSideView :
      x = std::fabs(0.5 * PM_SCINTI_BAR_LENGTH + pos.y());
      break;
    default :
      throw std::invalid_argument("Error : view number is not valid : " + std::to_string(view));
  }

  // Convert X from mm to cm
  x /= centimeter;

  if (pln == 0) {
    const int i = (int) x / 5;
    x = std::fabs(x - i * 5 - 2.5);
    edep *= std::exp(-1. * x / sciattleng_pm_);
  } else {
    if (x < 40 || x > 80) {
      const int i = (int) x / 5;
      x = std::fabs(x - i * 5 - 2.5);
      edep *= std::exp(-1. * x / sciattleng_pm_);
    } else {
      const int i = (int) (x / 2.5);
      x = std::fabs(x - i * 2.5 - 1.25);
      edep *= std::exp(-1. * x / sciattleng_pm_) * sci_bar_factor_;
    }
  }
}

void B2ProtonModuleResponse::ApplyFiberResponse(G4double &edep, G4double &time, B2View view, G4int pln, G4int slot,
                                                B2Readout readout,
                                                const G4ThreeVector &pos) const {

  G4double x;

  switch (view) {
    case B2View::kTopView :
      x = std::fabs(0.5 * PM_SCINTI_BAR_LENGTH - pos.y());
      break;
    case B2View::kSideView :
      x = std::fabs(0.5 * PM_SCINTI_BAR_LENGTH + pos.x());
      break;
    default :
      throw std::invalid_argument("Error : view number is not valid : " + std::to_string(view));
  }

  // attenuation in fiber
  edep *= std::exp(-1. * x / attenuation_length_);

  // delay in fiber
  time += x / TRANS_SPEED_IN_FIBER;
  time = gRandom->Gaus(time, 1.0);
}

void B2ProtonModuleResponse::ApplyMPPCResponse(G4double &pe, G4double edep, B2View view, G4int pln, G4int slot,
                                               B2Readout readout, const G4ThreeVector &pos) const {
  G4double npe = edep * mev2pe_pm_;
  npe = mppc_pixel_ * (1. - std::exp(eff_pde_pm_ * npe / mppc_pixel_));
  npe = npe / (1. - cross_after_rate_pm_);
  npe = (G4double) CLHEP::RandPoisson::shoot(npe);

  if ((pln == 0 || pln >= 18) || (slot < 8 || slot > 24))
    npe = gRandom->Gaus(npe, npe * pixel_gain_vari_pm_ing_);
  else
    npe = gRandom->Gaus(npe, npe * pixel_gain_vari_pm_sci_);

  pe = npe;
}

void B2ProtonModuleResponse::ApplyADCResponse(G4double &pe, G4double &lope, G4int &adc, G4int &loadc) const {
  //PE to ADC
  G4double adc_tmp = pedestal_ + pe * gain_;
  G4double loadc_tmp = pedestal_ + pe * low_gain_ * 14.29 / 13.55;

  //Electronics noise
  adc_tmp = gRandom->Gaus(adc_tmp, elec_noise_);
  loadc_tmp = gRandom->Gaus(loadc_tmp, low_elec_noise_);

  //ADC to Charge
  const G4double Q = (adc_tmp) / 135.5;
  const G4double loQ = (loadc_tmp) / 14.29;

  //Non linearlity of high gain ADC
  if (Q < 0.65)
    adc_tmp = (int) 135.5 * Q;
  else if (Q < 3.2)
    adc_tmp = (int) 217 * Q - 53;
  else if (Q < 4.2)
    adc_tmp = (int) 158.6 * Q + 133.9;
  else if (Q < 14)
    adc_tmp = (int) 5.1 * Q + 778.6;
  else
    adc_tmp = 850;

  //Non linearlity of low gain ADC
  if (loQ < 7)
    loadc_tmp = (int) 14.29 * loQ;
  else if (loQ < 27)
    loadc_tmp = (int) 26 * loQ - 82;
  else if (loQ < 35.5)
    loadc_tmp = (int) 21.12 * loQ + 48.24;
  else if (loQ < 178.4)
    loadc_tmp = (int) 0.7 * loQ + 775.1;
  else
    loadc_tmp = 900;

  //ADC to PE
  pe = (adc_tmp - pedestal_) / gain_;
  lope = (loadc_tmp - pedestal_) / low_gain_;
}

B2ProtonModuleResponse::B2ProtonModuleResponse(const B2Dimension &dimension) : B2DetectorResponse(dimension) {}

////////////////////////////////////////////////////////////////////////
//                          WAGASCI UP                                //
////////////////////////////////////////////////////////////////////////

void B2WagasciUpstreamResponse::ApplyLightCollection(G4double &edep, B2View view, G4int pln, G4int slot,
                                                     const G4ThreeVector &pos) const {
  TVector3 sci_pos;
  B2GridPlane grid;
  unsigned grid_slot;
  b2_dimension_.get().GetPosWgs(view, pln, slot, sci_pos);
  B2Dimension::GetGridWgs(slot, grid_slot, grid);

  G4double x;

  switch (view) {

    case B2View::kTopView :
      if (grid == B2GridPlane::kPlaneScintillator) {
        x = std::fabs(pos.x() - (sci_pos.x() - glueshift_));

      } else {
        x = std::fabs(pos.z() - (sci_pos.z() + glueshift_));

      }
      break;

    case B2View::kSideView :
      if (grid == B2GridPlane::kPlaneScintillator) {
        x = std::fabs(pos.y() - (sci_pos.y() - glueshift_));
      } else {
        x = std::fabs(pos.z() - (sci_pos.z() - glueshift_));
      }
      break;

    default :
      throw std::invalid_argument("Error : view number is not valid : " + std::to_string(view));

  }

  edep *= std::exp(-1. * x / sciattleng_wgs_);
}

void B2WagasciUpstreamResponse::ApplyFiberResponse(G4double &edep, G4double &time, B2View view, G4int pln, G4int slot,
                                                   B2Readout readout,
                                                   const G4ThreeVector &pos) const {

  G4double x;

  switch (view) {
    case B2View::kTopView :
      x = std::fabs(0.5 * WGS_SCINTI_BAR_LENGTH - pos.y()) + WGS_FIBER_BUNDLE_LENGTH;
      break;
    case B2View::kSideView :
      x = std::fabs(0.5 * WGS_SCINTI_BAR_LENGTH + pos.x()) + WGS_FIBER_BUNDLE_LENGTH;
      break;
    default :
      throw std::invalid_argument("Error : view value is not valid : " + std::to_string(view));
  }

  // attenuation in fiber
  edep *= std::exp(-1. * x / attenuation_length_);

  // delay in fiber
  time += x / TRANS_SPEED_IN_FIBER;
  time = gRandom->Gaus(time, 1.0);

}

void B2WagasciUpstreamResponse::ApplyMPPCResponse(G4double &pe, G4double edep, B2View view, G4int pln, G4int slot,
                                                  B2Readout readout, const G4ThreeVector &pos) const {

  B2GridPlane grid;
  unsigned grid_slot;
  B2Dimension::GetGridWgs(slot, grid_slot, grid);

  G4double npe = 0;
  switch (grid) {
    case B2GridPlane::kPlaneScintillator:
    case B2GridPlane::kUnknownScintillator:
      npe = edep * mev2pe_uwg_plane_;
      break;
    case B2GridPlane::kGridLeftScintillator:
    case B2GridPlane::kGridRightScintillator:
      npe = edep * mev2pe_uwg_grid_;
      break;
  }

  npe = mppc_num_pixels_ * (1. - std::exp(eff_pde_wgs_ * npe / mppc_num_pixels_));
  npe = npe / (1. - cross_after_rate_uwg_);
  npe = (double) CLHEP::RandPoisson::shoot(npe);

  if (grid)
    npe = gRandom->Gaus(npe, npe * pixel_gain_variation_uwg_grid_);
  else
    npe = gRandom->Gaus(npe, npe * pixel_gain_variation_uwg_pln_);
  pe = npe;
}

void B2WagasciUpstreamResponse::ApplyADCResponse(G4double &pe, G4double &lope, G4int &adc, G4int &loadc) const {
  //Must be implemented based in the future
}

B2WagasciUpstreamResponse::B2WagasciUpstreamResponse(const B2Dimension &dimension) : B2DetectorResponse(dimension) {}

////////////////////////////////////////////////////////////////////////
//                        WAGASCI Down                                //
////////////////////////////////////////////////////////////////////////

void B2WagasciDownstreamResponse::ApplyLightCollection(G4double &edep, B2View view, G4int pln, G4int slot,
                                                       const G4ThreeVector &pos) const {
  TVector3 sci_pos;
  B2GridPlane grid;
  unsigned grid_slot;
  b2_dimension_.get().GetPosWgs(view, pln, slot, sci_pos);
  B2Dimension::GetGridWgs(slot, grid_slot, grid);

  G4double x;

  switch (view) {

    case B2View::kTopView :
      if (grid == B2GridPlane::kPlaneScintillator) {
        x = std::fabs(pos.x() - (sci_pos.x() - glueshift_));
      } else {
        x = std::fabs(pos.z() - (sci_pos.z() + glueshift_));
      }
      break;

    case B2View::kSideView :
      if (grid == B2GridPlane::kPlaneScintillator) {
        x = std::fabs(pos.y() - (sci_pos.y() - glueshift_));
      } else {
        x = std::fabs(pos.z() - (sci_pos.z() - glueshift_));
      }
      break;

    default :
      throw std::invalid_argument("Error : view number is not valid : " + std::to_string(view));

  }

  edep *= std::exp(-1. * x / sciattleng_wgs_);
}

void B2WagasciDownstreamResponse::ApplyFiberResponse(G4double &edep, G4double &time, B2View view, G4int pln, G4int slot,
                                                     B2Readout readout,
                                                     const G4ThreeVector &pos) const {

  G4double x;

  switch (view) {
    case B2View::kTopView :
      x = std::fabs(0.5 * WGS_SCINTI_BAR_LENGTH - pos.y()) + WGS_FIBER_BUNDLE_LENGTH;
      break;
    case B2View::kSideView :
      x = std::fabs(0.5 * WGS_SCINTI_BAR_LENGTH + pos.x()) + WGS_FIBER_BUNDLE_LENGTH;
      break;
    default :
      throw std::invalid_argument("Error : view value is not valid : " + std::to_string(view));
  }

  // attenuation in fiber
  edep *= std::exp(-1. * x / attenuation_length_);

  // delay in fiber
  time += x / TRANS_SPEED_IN_FIBER;
  time = gRandom->Gaus(time, 1.0);

}

void B2WagasciDownstreamResponse::ApplyMPPCResponse(G4double &pe, G4double edep, B2View view, G4int pln, G4int slot,
                                                    B2Readout readout, const G4ThreeVector &pos) const {

  B2GridPlane grid;
  unsigned grid_slot;
  B2Dimension::GetGridWgs(slot, grid_slot, grid);

  G4double npe = 0;
  switch (grid) {
    case B2GridPlane::kPlaneScintillator:
    case B2GridPlane::kUnknownScintillator:
      npe = edep * mev2pe_dwgs_plane_;
      break;
    case B2GridPlane::kGridLeftScintillator:
    case B2GridPlane::kGridRightScintillator:
      npe = edep * mev2pe_dwgs_grid_;
      break;
  }

  npe = mppc_num_pixels_ * (1. - std::exp(eff_pde_wgs_ * npe / mppc_num_pixels_));
  npe = npe / (1. - cross_after_rate_wgs_);
  npe = (double) CLHEP::RandPoisson::shoot(npe);

  if (grid)
    npe = gRandom->Gaus(npe, npe * pixel_gain_variation_wgs_grid_);
  else
    npe = gRandom->Gaus(npe, npe * pixel_gain_variation_wgs_pln_);
  pe = npe;
}

void B2WagasciDownstreamResponse::ApplyADCResponse(G4double &pe, G4double &lope, G4int &adc, G4int &loadc) const {
  //Must be implemented based in the future
}

B2WagasciDownstreamResponse::B2WagasciDownstreamResponse(const B2Dimension &dimension) : B2DetectorResponse(
    dimension) {}

////////////////////////////////////////////////////////////////////////
//                             WallMRD                                //
////////////////////////////////////////////////////////////////////////

void B2WallMrdResponse::ApplyMPPCResponse(G4double &pe, G4double edep, B2View view, G4int pln, G4int slot,
                                          B2Readout readout, const G4ThreeVector &pos) const {
  G4double npe = edep * (mev2pe_wmrd_);
  npe = mppc_pixel_ * (1. - std::exp(eff_pde_wmrd_ * npe / mppc_pixel_));
  npe = npe / (1. - cross_after_rate_wmrd_);
  npe = (G4double) CLHEP::RandPoisson::shoot(npe);
  npe = gRandom->Gaus(npe, npe * pixel_gain_vari_wmrd_);
  pe = npe;
}

void B2WallMrdResponse::ApplyADCResponse(G4double &pe, G4double &lope, G4int &adc, G4int &loadc) const {
  //PE to ADC
  G4double adc_tmp = pedestal_wmrd_ + pe * gain_wmrd_;
  //Electronics noise
  adc_tmp = gRandom->Gaus(adc_tmp, 30);
  //ADC to Charge
  adc = (G4int) adc_tmp;
  //ADC to PE
  pe = (adc - pedestal_wmrd_) / gain_wmrd_;
}

B2WallMrdResponse::B2WallMrdResponse(const B2Dimension &dimension) : B2DetectorResponse(dimension) {}

B2WallMrdNorthResponse::B2WallMrdNorthResponse(const B2Dimension &dimension) : B2WallMrdResponse(dimension) {}

void B2WallMrdNorthResponse::ApplyLightCollection(G4double &edep, B2View view, G4int pln, G4int slot,
                                                  const G4ThreeVector &pos) const {
  /*
  const auto x = B2HitSummary::WallMrdHitToFiber(slot, pos.y(), pos.z(), B2Detector::kWallMrdNorth);
  edep *= std::exp(-1. * x / sciattleng_wmrd_);
  */
}

void B2WallMrdNorthResponse::ApplyFiberResponse(G4double &edep, G4double &time, B2View view, G4int pln, G4int slot,
                                                B2Readout readout, const G4ThreeVector &pos) const {
  /*
  const auto x = B2HitSummary::WallMrdFiberTransmissionDistance(slot, pos.y(), pos.z(), readout,
                                                                B2Detector::kWallMrdNorth);
  edep *= std::exp(-1 * x / attleng_wmrd_);
  time += x / TRANS_SPEED_IN_FIBER_WMRD;
  */
}

void
B2WallMrdNorthResponse::ApplyOpticalSimulation(G4double &edep, const G4ThreeVector &pos, G4double &pe, G4double &time,
                                               G4int slot, B2Readout readout) const {
  G4double uncorrpe = edep * mev2pe_wmrd_;
  const auto localpos = B2HitSummary::GetLocalPositioninWallMrd(pos.z(), pos.y(), slot);
  auto averageTime = b2_dimension_.get().GetAverageTime(localpos.Px(), localpos.Py(), readout);
  auto averagePe = b2_dimension_.get().GetAveragePe(localpos.Px(), localpos.Py(), readout);

  BOOST_LOG_TRIVIAL(debug) << averageTime << " " << averagePe << " " << localpos.Px() << " " << localpos.Py();

  const auto n_of_outside_local_section_bottom = (Int_t) localpos.Pz();
  const auto n_of_outside_local_section_top = 14 - (Int_t) localpos.Pz();
  if (readout == B2Readout::kTopReadout) {
    Double_t remained_length_in_fiber = n_of_outside_local_section_top * WM_FIBER_LENGTH_IN_SECTION;
    averageTime += remained_length_in_fiber / TRANS_SPEED_IN_FIBER_WMRD;
    averagePe *= std::exp(-1 * remained_length_in_fiber / attleng_fiber_sci_wmrd_);
  } else if (readout == B2Readout::kBottomReadout) {
    Double_t remained_length_in_fiber = n_of_outside_local_section_bottom * WM_FIBER_LENGTH_IN_SECTION;
    averageTime += remained_length_in_fiber / TRANS_SPEED_IN_FIBER_WMRD;
    averagePe *= std::exp(-1 * remained_length_in_fiber / attleng_fiber_sci_wmrd_);
  }

  BOOST_LOG_TRIVIAL(debug) << "readout " << readout << " time : " << averageTime;

  pe = uncorrpe * averagePe;

  pe = mppc_pixel_ * (1. - std::exp(eff_pde_wmrd_ * pe / mppc_pixel_));
  pe = pe / (1. - cross_after_rate_wmrd_);
  pe = (double) CLHEP::RandPoisson::shoot(pe);
  pe = gRandom->Gaus(pe, pe * pixel_gain_vari_wmrd_);

  const auto npe = (Int_t) pe;

  std::map<double, int> photons;
  for (int iphoton = 0; iphoton < npe; iphoton++) {
    double eachtime = b2_dimension_.get().GetRondomTime(localpos.Px(), localpos.Py(), readout);
    photons[eachtime] = iphoton;
  }

  Double_t threshold_electronics = 2.5;
  Double_t accumulated_photons = 0;
  Double_t time_over_threshold = 0;

  for (auto &[time, photonid]: photons) {
    accumulated_photons++;
    time_over_threshold = time;
    if (accumulated_photons > threshold_electronics)
      break;
  }

  averageTime += time_over_threshold;
  time += averageTime;
}


B2WallMrdSouthResponse::B2WallMrdSouthResponse(const B2Dimension &dimension) : B2WallMrdResponse(dimension) {}

void B2WallMrdSouthResponse::ApplyLightCollection(G4double &edep, B2View view, G4int pln, G4int slot,
                                                  const G4ThreeVector &pos) const {
}

void B2WallMrdSouthResponse::ApplyFiberResponse(G4double &edep, G4double &time, B2View view, G4int pln, G4int slot,
                                                B2Readout readout, const G4ThreeVector &pos) const {
}

void
B2WallMrdSouthResponse::ApplyOpticalSimulation(G4double &edep, const G4ThreeVector &pos, G4double &pe, G4double &time,
                                               G4int slot, B2Readout readout) const {

  G4double uncorrpe = edep * mev2pe_wmrd_;
  const auto localpos = B2HitSummary::GetLocalPositioninWallMrd(pos.z(), pos.y(), slot);
  auto averageTime = b2_dimension_.get().GetAverageTime(localpos.Px(), localpos.Py(), readout);
  auto averagePe = b2_dimension_.get().GetAveragePe(localpos.Px(), localpos.Py(), readout);

  BOOST_LOG_TRIVIAL(debug) << averageTime << " " << averagePe << " " << localpos.Px() << " " << localpos.Py();

  const auto n_of_outside_local_section_bottom = (Int_t) localpos.Pz();
  const auto n_of_outside_local_section_top = 14 - (Int_t) n_of_outside_local_section_bottom;
  if (readout == B2Readout::kTopReadout) {
    Double_t remained_length_in_fiber = n_of_outside_local_section_top * WM_FIBER_LENGTH_IN_SECTION;
    averageTime += remained_length_in_fiber / TRANS_SPEED_IN_FIBER_WMRD;
    averagePe *= std::exp(-1 * remained_length_in_fiber / attleng_fiber_sci_wmrd_);
  } else if (readout == B2Readout::kBottomReadout) {
    Double_t remained_length_in_fiber = n_of_outside_local_section_bottom * WM_FIBER_LENGTH_IN_SECTION;
    averageTime += remained_length_in_fiber / TRANS_SPEED_IN_FIBER_WMRD;
    averagePe *= std::exp(-1 * remained_length_in_fiber / attleng_fiber_sci_wmrd_);
  }

  BOOST_LOG_TRIVIAL(debug) << "readout " << readout << " time : " << averageTime;

  pe = uncorrpe * averagePe;

  pe = mppc_pixel_ * (1. - std::exp(eff_pde_wmrd_ * pe / mppc_pixel_));
  pe = pe / (1. - cross_after_rate_wmrd_);
  pe = (double) CLHEP::RandPoisson::shoot(pe);
  pe = gRandom->Gaus(pe, pe * pixel_gain_vari_wmrd_);

  const auto npe = (Int_t) pe;

  std::map<double, int> photons;
  for (int iphoton = 0; iphoton < npe; iphoton++) {
    double eachtime = b2_dimension_.get().GetRondomTime(localpos.Px(), localpos.Py(), readout);
    photons[eachtime] = iphoton;
  }

  Double_t threshold_electronics = 2.5;
  Double_t accumulated_photons = 0;
  Double_t time_over_threshold = 0;

  for (auto &[t, photonid]: photons) {
    accumulated_photons++;
    time_over_threshold = t;
    if (accumulated_photons > threshold_electronics)
      break;
  }

  averageTime += time_over_threshold;

  if (readout == kTopReadout)
    BOOST_LOG_TRIVIAL(debug) << "readout " << readout << " time : avt = " << time << " "
                             << averageTime << " ypos = " << pos.y();

  time += averageTime;

}


////////////////////////////////////////////////////////////////////////
//                           Baby MIND                                //
////////////////////////////////////////////////////////////////////////

void B2BabyMindResponse::ApplyLightCollection(G4double &edep, B2View view, G4int pln, G4int slot,
                                              const G4ThreeVector &pos) const {
  //Must be implemented based in the future
}

void B2BabyMindResponse::ApplyFiberResponse(G4double &edep, G4double &time, B2View view, G4int pln, G4int slot,
                                            B2Readout readout,
                                            const G4ThreeVector &pos) const {
  G4double x;
  switch (view) {
    case B2View::kTopView : {
      x = std::fabs(0.5 * BM_VERTICAL_SCINTI_LENGTH - pos.y());
      break;
    }
    case B2View::kSideView : {
      const int dir = 2 * (readout - B2Readout::kLeftReadout) - 1;
      x = std::fabs(0.5 * BM_HORIZONTAL_SCINTI_LENGTH + pos.x() * dir);
      //std::cout << "posx = " << pos.x()  << " readout = " << readout  << " x = " << x << '\n';

      //const int dir = std::abs(2 * (readout - B2Readout::kLeftReadout) - 1);
      //x = std::fabs(0.5 * BM_HORIZONTAL_SCINTI_LENGTH + pos.x() * dir);
      //std::cout << "posx = " << pos.x()  << " readout = " << readout  << " x = " << x << '\n';
      break;
    }
    default :
      throw std::invalid_argument("Error : view number is not valid : " + std::to_string(view));
  }

  // attenuation in fiber
  edep *= std::exp(-1. * x / attleng_bm_);

  // delay in fiber
  time += x / TRANS_SPEED_IN_FIBER;
  time = gRandom->Gaus(time, 1.0);
}

void B2BabyMindResponse::ApplyMPPCResponse(G4double &pe, G4double edep, B2View view, G4int pln, G4int slot,
                                           B2Readout readout, const G4ThreeVector &pos) const {

  G4double npe;

  switch (view) {
    case B2View::kSideView : {
      npe = edep * mev2pe_bm_;
      npe = mppc_pixel_bm_ * (1. - std::exp(eff_pde_bm_ * npe / mppc_pixel_bm_));
      npe = npe / (1. - cross_after_rate_side_bm_);
      npe = (double) CLHEP::RandPoisson::shoot(npe);
      npe = gRandom->Gaus(npe, npe * pixel_gain_vari_side_bm_);
      //std::cout << view << " " << edep << " " << npe  << " " << pos.x() << " " << pos.y()  << " " << pos.z() << '\n';
      //std::cout << "pos.x = " << pos.x() << '\n';

      break;
    }
    case B2View::kTopView : {
      TVector3 refpos;
      b2_dimension_.get().GetPosBm(view, pln, slot, refpos);
      const double mapx = pos.x() - (refpos.Px() - 0.5 * BM_VERTICAL_SCINTI_LARGE);
      const double mapy = -pos.y() + 0.5 * BM_VERTICAL_SCINTI_LENGTH;
      const double vpe = b2_dimension_.get().GetBMVerticalPE(mapx, mapy, readout) * bm_top_factor;
      npe = vpe;
      //std::cout << view << " " << mapx << " " << mapy << " " << vpe << " " << pos.x() << " " << pos.y()  << '\n';
      npe = mppc_pixel_bm_ * (1. - std::exp(eff_pde_bm_ * npe / mppc_pixel_bm_));
      npe = npe / (1. - cross_after_rate_top_bm_);
      npe = (double) CLHEP::RandPoisson::shoot(npe);
      npe = gRandom->Gaus(npe, npe * pixel_gain_vari_top_bm_);
      break;
    }
    default :
      throw std::invalid_argument("Error : view number is not valid : " + std::to_string(view));
  }

  pe = npe;
}

void B2BabyMindResponse::ApplyADCResponse(G4double &pe, G4double &lope, G4int &adc, G4int &loadc) const {
  //Must be implemented based in the future
}

B2BabyMindResponse::B2BabyMindResponse(const B2Dimension &dimension) : B2DetectorResponse(dimension) {}

////////////////////////////////////////////////////////////////////////
//                             YASU Tracker                           //
////////////////////////////////////////////////////////////////////////

void B2YASUTrackerResponse::ApplyMPPCResponse(G4double &pe, G4double edep, B2View view, G4int pln, G4int slot,
                                              B2Readout readout, const G4ThreeVector &pos) const {
}

void B2YASUTrackerResponse::ApplyADCResponse(G4double &pe, G4double &lope, G4int &adc, G4int &loadc) const {
}

void B2YASUTrackerResponse::ApplyLightCollection(G4double &edep, B2View view, G4int pln, G4int slot,
                                                 const G4ThreeVector &pos) const {
}

void B2YASUTrackerResponse::ApplyFiberResponse(G4double &edep, G4double &time, B2View view, G4int pln, G4int slot,
                                               B2Readout readout, const G4ThreeVector &pos) const {
}

void
B2YASUTrackerResponse::ApplyOpticalSimulation(G4double &edep, const G4ThreeVector &pos, G4double &pe, G4double &time,
                                              G4int slot, B2Readout readout) const {

  G4double uncorrpe = edep * mev2pe_yasu_;
  const auto localpos = B2HitSummary::GetLocalPositioninYASUTracker(pos.y(), pos.x(), slot);
  auto averageTime = b2_dimension_.get().GetAverageTime(localpos.Px(), localpos.Py(), kTopReadout);
  auto averagePe = b2_dimension_.get().GetAveragePe(localpos.Px(), localpos.Py(), kTopReadout);

  BOOST_LOG_TRIVIAL(debug) << "posy = " << pos.y() << " posx = " << pos.x() << " " << slot << " slot % 7 = " << slot % 7
                           << " slot / 7 = " << slot / 7;
  BOOST_LOG_TRIVIAL(debug) << averageTime << " " << averagePe << " " << localpos.Px() << " " << localpos.Py() << " "
                           << localpos.Pz();

  const auto n_of_outside_local_section = (Int_t) localpos.Pz();
  const auto remained_length_in_fiber = n_of_outside_local_section * WM_FIBER_LENGTH_IN_SECTION;
  BOOST_LOG_TRIVIAL(debug) << "remained_length_in_fiber = " << remained_length_in_fiber;
  averageTime += remained_length_in_fiber / TRANS_SPEED_IN_FIBER_WMRD;
  averagePe *= std::exp(-1 * remained_length_in_fiber / attleng_fiber_sci_wmrd_);

  pe = uncorrpe * averagePe;

  pe = mppc_pixel_ * (1. - std::exp(eff_pde_yasu_ * pe / mppc_pixel_));
  pe = pe / (1. - cross_after_rate_yasu_);
  pe = (double) CLHEP::RandPoisson::shoot(pe);
  pe = gRandom->Gaus(pe, pe * pixel_gain_vari_yasu_);

  BOOST_LOG_TRIVIAL(debug) << "readout " << readout << " time : " << averageTime;

  const auto npe = (Int_t) pe;

  std::map<double, int> photons;
  for (int iphoton = 0; iphoton < npe; iphoton++) {
    double eachtime = b2_dimension_.get().GetRondomTime(localpos.Px(), localpos.Py(), kTopReadout);
    photons[eachtime] = iphoton;
  }

  Double_t threshold_electronics = 2.5;
  Double_t accumulated_photons = 0;
  Double_t time_over_threshold = 0;

  for (auto &[t, photonid]: photons) {
    accumulated_photons++;
    time_over_threshold = t;
    if (accumulated_photons > threshold_electronics)
      break;
  }

  averageTime += time_over_threshold;

  BOOST_LOG_TRIVIAL(debug) << "PE = " << pe;
  BOOST_LOG_TRIVIAL(debug) << "readout " << readout << " time : avt = " << time << " " << averageTime << " ypos = "
                           << pos.x();
  time += averageTime;

}

B2YASUTrackerResponse::B2YASUTrackerResponse(const B2Dimension &dimension) : B2DetectorResponse(dimension) {}

////////////////////////////////////////////////////////////////////////
//                               NINJA                                //
////////////////////////////////////////////////////////////////////////

void B2NinjaResponse::ApplyLightCollection(G4double &edep, B2View view, G4int pln, G4int slot,
                                           const G4ThreeVector &pos) const {

  TVector3 sci_pos;
  B2Dimension::GetPosNinjaTracker(view, pln, slot, sci_pos);

  G4double x;
  switch (view) {
    case B2View::kSideView :
      if (pln % 2 == 0)
        x = std::fabs(pos.y() - (sci_pos.y() - glueshift_));
      else
        x = std::fabs(pos.y() - (sci_pos.y() + glueshift_));
      break;
    case B2View::kTopView :
      if (pln % 2 == 0)
        x = std::fabs(pos.x() - (sci_pos.x() - glueshift_));
      else
        x = std::fabs(pos.x() - (sci_pos.x() + glueshift_));
      break;
    default :
      throw std::invalid_argument("Error : view number is not valid" + std::to_string(view));
  }
  edep *= std::exp(-1. * x / sciattleng_ninja_);
}

void B2NinjaResponse::ApplyFiberResponse(G4double &edep, G4double &time, B2View view, G4int pln, G4int slot,
                                         B2Readout readout,
                                         const G4ThreeVector &pos) const {

  G4double x;

  switch (view) {
    case B2View::kSideView :
      x = std::fabs(0.5 * NINJA_HORIZ_SCI_LENGTH - pos.x()) + fiberbundle_ninja_;
      break;
    case B2View::kTopView :
      x = std::fabs(0.5 * NINJA_VERTI_SCI_LENGTH + pos.y()) + fiberbundle_ninja_;
      break;
    default :
      throw std::invalid_argument("Error : view number is not valid" + std::to_string(view));
  }

  // attenuation in fiber
  edep *= std::exp(-1. * x / attenuation_length_);

  // delay in fiber
  time += x / TRANS_SPEED_IN_FIBER;
  time = gRandom->Gaus(time, 1.0);
}

G4int B2NinjaResponse::GetModuleId(B2View view, G4int slot) {

  switch (view) {
    case B2View::kSideView :
      if (slot <= 15) return 0;
      else return 1;
    case B2View::kTopView :
      if (slot <= 15) return 2;
      else return 3;
    default :
      throw std::invalid_argument("Error : view number is not valid" + std::to_string(view));
  }
}

void
B2NinjaResponse::ApplyMPPCResponse(G4double &pe, G4double edep, B2View view, G4int pln, G4int slot, B2Readout readout,
                                   const G4ThreeVector &pos) const {

  G4int module = GetModuleId(view, slot);

  G4double npe = edep * mev2pe_ninja_;
  npe = mppc_pixel_ * (1. - std::exp(eff_pde_ninja_[module] * npe / mppc_pixel_));
  npe = npe / (1. - cross_after_rate_ninja_[module]);
  npe = (G4double) CLHEP::RandPoisson::shoot(npe);
  npe = gRandom->Gaus(npe, npe * pixel_gain_vari_ninja_[module]);
  pe = npe;
}

void B2NinjaResponse::ApplyADCResponse(G4double &pe, G4double &lope, G4int &adc, G4int &loadc) const {
  // We only use EASIROC high gain ADC
  // and the linearity is OK in the NINJA PE region
}

B2NinjaResponse::B2NinjaResponse(const B2Dimension &dimension) : B2DetectorResponse(dimension) {}
