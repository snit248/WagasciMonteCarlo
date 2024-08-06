#ifndef B2_RESPONSE_HH
#define B2_RESPONSE_HH

#include <iostream>
#include <fstream>

#include <boost/log/trivial.hpp>

#include <G4ThreeVector.hh>
#include <G4EmCalculator.hh>
#include <G4Track.hh>

#include "B2Settings.hh"
#include "B2Dimension.hh"

class B2Response;

////////////////////////////////////////////////////////////////////////
//                            Interface                               //
////////////////////////////////////////////////////////////////////////

/**
 * Base class from which every detector response is derived. It only implements the ApplyScintiResponse method. All
 * the other methods are just an interface.
 */
class B2DetectorResponse {

protected:

  std::reference_wrapper<const B2Dimension> b2_dimension_;

  G4EmCalculator emcal_;

  // Birks' constant used in SciBooNE MC (cm / MeV). Error is +- 0.0023 cm / MeV.
  const G4double cbirks_ = 0.0208;
  // WLS fiber attenulation length (cm). Taken from Koga-san thesis. Assuming monochromatic source of 500 nm (green).
  const G4double attenuation_length_ = 241.7 * centimeter;

public:

  explicit B2DetectorResponse(const B2Dimension &dimension);

  virtual ~B2DetectorResponse() = default;

  virtual void ApplyScintiResponse(G4double &edep, const G4Track &track);

  virtual void ApplyLightCollection(G4double &edep, B2View view, G4int pln, G4int ch,
                                    const G4ThreeVector &pos) const = 0;

  virtual void ApplyFiberResponse(G4double &edep, G4double &time, B2View view, G4int pln, G4int slot,
                                  B2Readout readout, const G4ThreeVector &pos) const = 0;

  virtual void ApplyMPPCResponse(G4double &pe, G4double edep, B2View view, G4int pln, G4int slot,
                                 B2Readout readout, const G4ThreeVector &pos) const = 0;

  virtual void ApplyADCResponse(G4double &pe, G4double &lope, G4int &adc, G4int &loadc) const = 0;

  virtual void ApplyTDCResponse(G4int &tdc, G4double time) const;

  virtual void ApplyOpticalSimulation(G4double &edep, const G4ThreeVector &pos, G4double &pe, G4double &time,
                                      G4int slot, B2Readout readout) const;

};

////////////////////////////////////////////////////////////////////////
//                             B2Response                             //
////////////////////////////////////////////////////////////////////////

/**
 * This class handles all the detectors. It contains a smart pointer for every detector pointing to the relative
 * response object. The current detector can be selected using the SwitchDetector method. The default detector is
 * Proton Module. All the other methods follow the same interface as the underlying B2DetectorResponse.
 */
class B2Response {

protected:

  B2Detector current_detector_ = B2Detector::kProtonModule;

private:

  std::unordered_map<B2Detector, std::unique_ptr<B2DetectorResponse>, EnumClassHash> detector_response_;

public:

  explicit B2Response(const B2Dimension &dimension);

  B2Response &SwitchDetector(B2Detector detector);

  void ApplyScintiResponse(G4double &edep, const G4Track &track);

  void ApplyLightCollection(G4double &edep, B2View view, G4int pln, G4int ch,
                            const G4ThreeVector &pos) const;

  void ApplyFiberResponse(G4double &edep, G4double &time, B2View view, G4int pln, G4int slot, B2Readout readout,
                          const G4ThreeVector &pos) const;

  void ApplyMPPCResponse(G4double &pe, G4double edep, B2View view, G4int pln, G4int slot,
                         B2Readout readout, const G4ThreeVector &pos) const;

  void ApplyADCResponse(G4double &pe, G4double &lope, G4int &adc, G4int &loadc) const;

  void ApplyTDCResponse(G4int &tdc, G4double time) const;

  void ApplyOpticalSimulation(G4double &edep, const G4ThreeVector &pos, G4double &pe, G4double &time,
                              G4int slot, B2Readout readout) const;
};

////////////////////////////////////////////////////////////////////////
//                           Proton Module                            //
////////////////////////////////////////////////////////////////////////

class B2ProtonModuleResponse : public B2DetectorResponse {

private:

  // Proton Module scintillator attenulation length (cm)
  const G4double sciattleng_pm_ = 10.46;
  // P.E. factor for SciBar scintillator
  //const G4double sci_bar_factor_ = 1.90;
  //const G4double sci_bar_factor_ = 2.28;
  //const G4double sci_bar_factor_ = 1.95;
  const G4double sci_bar_factor_ = 2.05;
  // MeV to PE conversion for Proton Module
  const G4double mev2pe_pm_ = 37.0;
  //const G4double mev2pe_pm_ = 39.0;
  // Number of MPPC pixels
  const G4double mppc_pixel_ = 667.;
  // Gain variation among pixels for Proton Module
  // const G4double pixel_gain_vari_pm_ = 0.031;
  // const G4double pixel_gain_vari_pm_ = 0.028;
  //const G4double pixel_gain_vari_pm_ = 0.025;
  const G4double pixel_gain_vari_pm_ing_ = 0.031;
  const G4double pixel_gain_vari_pm_sci_ = 0.0260;
  // PDE for Proton Module
  const G4double eff_pde_pm_ = -0.275;
  // Cross talk and after pulse rate for Proton Module
  const G4double cross_after_rate_pm_ = 0.09;
  // Pedestal of ADC counts
  const G4double pedestal_ = 0;
  // Gain ADC counts of high gain channel
  const G4double gain_ = 10;
  // Gain ADC counts of low gain channel
  const G4double low_gain_ = 1.0;
  // Sigma of high gain electronics noise
  const G4double elec_noise_ = 1.7;
  // Sigma of low gain electronics noise
  const G4double low_elec_noise_ = 1.2;

public:

  explicit B2ProtonModuleResponse(const B2Dimension &dimension);

  void ApplyLightCollection(G4double &edep, B2View view, G4int pln, G4int ch, const G4ThreeVector &pos) const override;

  void ApplyFiberResponse(G4double &edep, G4double &time, B2View view, G4int pln, G4int slot, B2Readout readout,
                          const G4ThreeVector &pos) const override;

  void ApplyMPPCResponse(G4double &pe, G4double edep, B2View view, G4int pln, G4int slot,
                         B2Readout readout, const G4ThreeVector &pos) const override;

  void ApplyADCResponse(G4double &pe, G4double &lope, G4int &adc, G4int &loadc) const override;

};

////////////////////////////////////////////////////////////////////////
//                          WAGASCI UP                                //
////////////////////////////////////////////////////////////////////////

class B2WagasciUpstreamResponse : public B2DetectorResponse {

private:

  // WAGASCI scintillator attenulation length (cm)
  const G4double sciattleng_wgs_ = 4.0 * centimeter;
  // Gain variation among pixels for WAGASCI
  const G4double pixel_gain_variation_uwg_pln_ = 0.25;
  const G4double pixel_gain_variation_uwg_grid_ = 0.30;
  // MeV to PE conversion for WAGASCI plane scintillators [Up]
  //const G4double mev2pe_uwgs_plane_ = 135;
  const G4double mev2pe_uwg_plane_ = 110;
  // MeV to PE conversion for WAGASCI grid scintillators
  const G4double mev2pe_uwg_grid_ = 108;

  // PDE for WAGASCI at wavelength of 500 nm (Chikuma-san thesis)
  const G4double eff_pde_wgs_ = -0.35;
  // Cross talk and after pulse rate for WAGASCI (Chikuma-san thesis)
  //const G4double cross_after_rate_wgs_ = 0.052;
  const G4double cross_after_rate_uwg_ = 0.052;
  // Glue shift in WAGASCI scintillators (cm)
  const G4double glueshift_ = 0.39 * centimeter;
  // Number of MPPC pixels
  const G4int mppc_num_pixels_ = 716;

public:

  explicit B2WagasciUpstreamResponse(const B2Dimension &dimension);

  void
  ApplyLightCollection(G4double &edep, B2View view, G4int pln, G4int slot, const G4ThreeVector &pos) const override;

  void ApplyFiberResponse(G4double &edep, G4double &time, B2View view, G4int pln, G4int slot, B2Readout readout,
                          const G4ThreeVector &pos) const override;

  void ApplyMPPCResponse(G4double &pe, G4double edep, B2View view, G4int pln, G4int slot,
                         B2Readout readout, const G4ThreeVector &pos) const override;

  void ApplyADCResponse(G4double &pe, G4double &lope, G4int &adc, G4int &loadc) const override;

};

////////////////////////////////////////////////////////////////////////
//                        WAGASCI Down                                //
////////////////////////////////////////////////////////////////////////

class B2WagasciDownstreamResponse : public B2DetectorResponse {

private:

  // WAGASCI scintillator attenulation length (cm)
  const G4double sciattleng_wgs_ = 4.0 * centimeter;
  // Gain variation among pixels for WAGASCI
  const G4double pixel_gain_variation_wgs_pln_ = 0.25;
  const G4double pixel_gain_variation_wgs_grid_ = 0.30;

  // MeV to PE conversion for WAGASCI plane scintillators [Down]
  const G4double mev2pe_dwgs_plane_ = 110;
  // MeV to PE conversion for WAGASCI grid scintillators
  const G4double mev2pe_dwgs_grid_ = 108;

  // PDE for WAGASCI at wavelength of 500 nm (Chikuma-san thesis)
  const G4double eff_pde_wgs_ = -0.35;
  // Cross talk and after pulse rate for WAGASCI (Chikuma-san thesis)
  //const G4double cross_after_rate_wgs_ = 0.052;
  const G4double cross_after_rate_wgs_ = 0.032;
  // Glue shift in WAGASCI scintillators (cm)
  const G4double glueshift_ = 0.39 * centimeter;
  // Number of MPPC pixels
  const G4int mppc_num_pixels_ = 716;

public:

  explicit B2WagasciDownstreamResponse(const B2Dimension &dimension);

  void
  ApplyLightCollection(G4double &edep, B2View view, G4int pln, G4int slot, const G4ThreeVector &pos) const override;

  void ApplyFiberResponse(G4double &edep, G4double &time, B2View view, G4int pln, G4int slot, B2Readout readout,
                          const G4ThreeVector &pos) const override;

  void ApplyMPPCResponse(G4double &pe, G4double edep, B2View view, G4int pln, G4int slot,
                         B2Readout readout, const G4ThreeVector &pos) const override;

  void ApplyADCResponse(G4double &pe, G4double &lope, G4int &adc, G4int &loadc) const override;

};

////////////////////////////////////////////////////////////////////////
//                             WallMRD                                //
////////////////////////////////////////////////////////////////////////

class B2WallMrdResponse : public B2DetectorResponse {

protected:

  // Gain variation among pixels for WallMRD
  // const G4double pixel_gain_vari_wmrd_ = 0.031;
  // const G4double pixel_gain_vari_wmrd_ = 0.020;
  const G4double pixel_gain_vari_wmrd_ = 0.0001;
  // PDE for WallMRD
  const G4double eff_pde_wmrd_ = -0.35;
  // Cross talk and after pulse rate for WallMRD
  const G4double cross_after_rate_wmrd_ = 0.20;
  // MeV to PE conversion for WallMRD
  const G4double mev2pe_wmrd_ = 1.8;
  //const G4double mev2pe_wmrd_ = 65.0;
  //const G4double mev2pe_wmrd_ = 130.0;
  //WallMRD fiber+scinti attenuation length in fiber length (cm)
  //const G4double attleng_fiber_sci_wmrd_ = 602. * centimeter;
  const G4double attleng_fiber_sci_wmrd_ = 402. * centimeter;
  //const G4double attleng_fiber_sci_wmrd_ = 200. * centimeter;
  // WallMRD scintillator attenuation length (cm) (Not tested)
  const G4double sciattleng_wmrd_ = 10.46 * centimeter;
  // WallMRD fiber attenuation length (cm)
  const G4double attleng_wmrd_ = 250.6 * centimeter;
  // Average pedestal value for WallMRD (ADC)
  const G4double pedestal_wmrd_ = 500;
  // Average gain value for WallMRD (ADC)
  const G4double gain_wmrd_ = 83;
  // Number of MPPC pixels
  const G4double mppc_pixel_ = 667.;

public:

  explicit B2WallMrdResponse(const B2Dimension &dimension);

  void ApplyMPPCResponse(G4double &pe, G4double edep, B2View view, G4int pln, G4int slot,
                         B2Readout readout, const G4ThreeVector &pos) const override;

  void ApplyADCResponse(G4double &pe, G4double &lope, G4int &adc, G4int &loadc) const override;

// Using for Wall-MRD

};

class B2WallMrdNorthResponse : public B2WallMrdResponse {

public:

  explicit B2WallMrdNorthResponse(const B2Dimension &dimension);

  void ApplyLightCollection(G4double &edep, B2View view, G4int pln, G4int slot,
                            const G4ThreeVector &pos) const override;

  void ApplyFiberResponse(G4double &edep, G4double &time, B2View view, G4int pln, G4int slot, B2Readout readout,
                          const G4ThreeVector &pos) const override;

  void ApplyOpticalSimulation(G4double &edep, const G4ThreeVector &pos, G4double &pe, G4double &time,
                              G4int slot, B2Readout readout) const override;

// Using for Wall-MRD north

};

class B2WallMrdSouthResponse : public B2WallMrdResponse {

public:

  explicit B2WallMrdSouthResponse(const B2Dimension &dimension);

  void ApplyLightCollection(G4double &edep, B2View view, G4int pln, G4int slot,
                            const G4ThreeVector &pos) const override;

  void ApplyFiberResponse(G4double &edep, G4double &time, B2View view, G4int pln, G4int slot, B2Readout readout,
                          const G4ThreeVector &pos) const override;

  void ApplyOpticalSimulation(G4double &edep, const G4ThreeVector &pos, G4double &pe, G4double &time,
                              G4int slot, B2Readout readout) const override;

// Using for Wall-MRD north

};


////////////////////////////////////////////////////////////////////////
//                           Baby MIND                                //
////////////////////////////////////////////////////////////////////////

class B2BabyMindResponse : public B2DetectorResponse {

private:

  // BMTracker fiber attenulation length (cm)
  //const G4double attleng_bm_ = 301.6 * centimeter;
  const G4double attleng_bm_ = 400.6 * centimeter;
  // BMTracker scintillator attenulation length (cm) to be corrected
  const G4double sciattleng_bm_ = 3.0 * centimeter;
  // Gain variation among pixels for BMTracker
  const G4double pixel_gain_vari_side_bm_ = 0.27;
  // Gain variation among pixels for BMTracker
  const G4double pixel_gain_vari_top_bm_ = 0.5;
  // MeV to PE conversion for BMTracker
  //const G4double mev2pe_bm_ = 50.0;
  //const G4double mev2pe_bm_ = 55.0;
  //const G4double mev2pe_bm_ = 58.0;
  const G4double mev2pe_bm_ = 95.0;
  // Number of MPPC pixels for BMTracker
  const G4double mppc_pixel_bm_ = 1600.;
  // PDE for BMTracker
  const G4double eff_pde_bm_ = -0.35;
  // Cross talk and after pulse rate for BMTracker
  const G4double cross_after_rate_side_bm_ = 0.01;
  // Cross talk and after pulse rate for BMTracker
  const G4double cross_after_rate_top_bm_ = 0.28;
  // manually implement the tuning parameter of vertical modules in Baby MIND
  const G4double bm_top_factor = 1.40;

public:

  explicit B2BabyMindResponse(const B2Dimension &dimension);

  void
  ApplyLightCollection(G4double &edep, B2View view, G4int pln, G4int slot, const G4ThreeVector &pos) const override;

  void ApplyFiberResponse(G4double &edep, G4double &time, B2View view, G4int pln, G4int slot, B2Readout readout,
                          const G4ThreeVector &pos) const override;

  void ApplyMPPCResponse(G4double &pe, G4double edep, B2View view, G4int pln, G4int slot,
                         B2Readout readout, const G4ThreeVector &pos) const override;

  void ApplyADCResponse(G4double &pe, G4double &lope, G4int &adc, G4int &loadc) const override;

};

////////////////////////////////////////////////////////////////////////
//                           YASU Tracker                             //
////////////////////////////////////////////////////////////////////////

class B2YASUTrackerResponse : public B2DetectorResponse {

private:

  // YASUTracker fiber attenulation length (cm)
  const G4double attleng_yasu_ = 250.6 * centimeter;
  // YASUTracker scintillator attenulation length (cm) to be corrected
  const G4double sciattleng_yasu_ = 10.46 * centimeter;
  // Gain variation among pixels for YASUTracker
  const G4double pixel_gain_vari_yasu_ = 0.031;
  //WallMRD fiber+scinti attenuation length in fiber length (cm)
  const G4double attleng_fiber_sci_wmrd_ = 402. * centimeter;
  // MeV to PE conversion for YASUTracker
  const G4double mev2pe_yasu_ = 1.5;
  //const G4double mev2pe_yasu_ = 65.0;
  // Number of MPPC pixels for YASUTracker
  const G4double mppc_pixel_ = 667.;
  // PDE for YASUTracker
  const G4double eff_pde_yasu_ = -0.35;
  // Cross talk and after pulse rate for YASUTracker
  const G4double cross_after_rate_yasu_ = 0.30;
  // Pedestal of ADC counts
  const G4double pedestal_ = 0;
  // Gain ADC counts of high gain channel
  const G4double gain_ = 10;

public:

  explicit B2YASUTrackerResponse(const B2Dimension &dimension);

  void
  ApplyLightCollection(G4double &edep, B2View view, G4int pln, G4int slot, const G4ThreeVector &pos) const override;

  void ApplyFiberResponse(G4double &edep, G4double &time, B2View view, G4int pln, G4int slot, B2Readout readout,
                          const G4ThreeVector &pos) const override;

  void ApplyMPPCResponse(G4double &pe, G4double edep, B2View view, G4int pln, G4int slot,
                         B2Readout readout, const G4ThreeVector &pos) const override;

  void ApplyADCResponse(G4double &pe, G4double &lope, G4int &adc, G4int &loadc) const override;

  void ApplyOpticalSimulation(G4double &edep, const G4ThreeVector &pos, G4double &pe, G4double &time,
                              G4int slot, B2Readout readout) const override;

};

////////////////////////////////////////////////////////////////////////
//                               NINJA                                //
////////////////////////////////////////////////////////////////////////

class B2NinjaResponse : public B2DetectorResponse {

private:

  // NINJA scintillator attenulation length
  const G4double sciattleng_ninja_ = 4.0 * centimeter;
  // Gain variation among pixels for NINJA tracker
  // const G4double pixel_gain_vari_ninja_ = 0.031;
  const G4double pixel_gain_vari_ninja_[4] = {0.035,
					      0.035,
					      0.15,
					      0.30};
  // MeV to PE conversion for NINJA tracker
  // const G4double mev2pe_ninja_ = 31.5;
  const G4double mev2pe_ninja_ = 80.;
  // PDE for NINJA tracker linearity correction
  const G4double eff_pde_ninja_[4] = {-0.28,
				      -0.28,
				      -0.43,
				      -0.52};
  // Cross talk rate for NINJA tracker
  // const G4double cross_after_rate_ninja_ = 0.18;
  const G4double cross_after_rate_ninja_[4] = {0.18,
					       0.18,
					       0.18,
					       0.18};
  // Fiber length between scinti and MPPC for NINJA tracker
  const G4double fiberbundle_ninja_ = 14.5 * centimeter;
  // Number of MPPC pixels
  const G4double mppc_pixel_ = 667.;
  // Glue shift in WAGASCI scintillators (cm)
  const G4double glueshift_ = 0.39 * centimeter;

public:

  explicit B2NinjaResponse(const B2Dimension &dimension);

  void
  ApplyLightCollection(G4double &edep, B2View view, G4int pln, G4int slot, const G4ThreeVector &pos) const override;

  void ApplyFiberResponse(G4double &edep, G4double &time, B2View view, G4int pln, G4int slot, B2Readout readout,
                          const G4ThreeVector &pos) const override;

  static G4int GetModuleId(B2View view, G4int slot) ;

  void ApplyMPPCResponse(G4double &pe, G4double edep, B2View view, G4int pln, G4int slot,
                         B2Readout readout, const G4ThreeVector &pos) const override;

  void ApplyADCResponse(G4double &pe, G4double &lope, G4int &adc, G4int &loadc) const override;

};

#endif
