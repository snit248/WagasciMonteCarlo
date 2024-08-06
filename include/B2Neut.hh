#ifndef Neut_h
#define Neut_h 1

// system includes
#include <string>
#include <unordered_map>
#include <array>

// ROOT includes
#include <TTree.h>
#include <TFile.h>
#include <TVector3.h>

// project includes
#include "B2Const.hh"
#include "B2Enum.hh"
#include "B2Pdg.hh"

static const std::size_t MAX_NUM_PRIMARY_PARTICLES = 100;
static const std::size_t MAX_NUM_SECONDARY_PARTICLES = 100;
static const std::size_t MAX_NUM_INTERMEDIATE_PARTICLES = 900;
static const std::size_t MAX_NUM_FSI_VERTICES = 300;

/**
 * Struct describing all the secondary particles coming out of the neutrino interaction
 * vertex after FSI.
 */
struct SecondaryParticles {

  enum TrackingFlag {
    kStopInsideNucleus = 0,
    kExitNucleus = 1
  };

  ///> number of particles coming out of the vertex (Npar)
  Int_t num_particles;
  ///> ID of the particle (Ipv) or (Ipvc)
  std::array<Int_t, MAX_NUM_SECONDARY_PARTICLES> particle_id;
  ///> ID of the parent particle (Iorgv) or (Iorgvc)
  std::array<Int_t, MAX_NUM_SECONDARY_PARTICLES> parent_id;
  ///> FLAG OF TO CHASE OR NOT (Icrnv) or (Ichvc)
  ///    0: stop in nucleus (do not chase)
  ///    1: go outside of nucleus (chase)
  std::array<Int_t, MAX_NUM_SECONDARY_PARTICLES> tracking_flag;
  ///> FLAG OF FINAL STATE (Iflgv) or (Iflvc)
  ///    0 : DETERMINED LATER PROCEDURE
  ///    1 : DECAY TO OTHER PARTICLE
  ///    2 : ESCAPE FROM DETECTOR
  ///    3 : ABSORPTION
  ///    4 : CHARGE EXCHANGE
  ///    5 : STOP AND NOT CONSIDER IN M.C.
  ///    6 : E.M. SHOWER
  ///    7 : HADRON PRODUCTION
  ///    8 : QUASI-ELASTIC SCATTER
  ///    9 : FORWARD (ELASTIC-LIKE) SCATTER
  std::array<Int_t, MAX_NUM_SECONDARY_PARTICLES> interaction_code;
  ///> modulus of the momentum 3D vector in MeV/c (Abspv) or (Abspvc)
  std::array<Float_t, MAX_NUM_SECONDARY_PARTICLES> abs_momentum;
  ///> momentum 3D vector in MeV/c (Pmomv) or (Pvc)
  Float_t momentum[MAX_NUM_SECONDARY_PARTICLES][3];
  ///> vertex position in nucleus (Pos)
  std::array<Float_t, 3> vertex;

  void SetBranches(TTree &tree);

  friend std::ostream &operator<<(std::ostream &os, const SecondaryParticles &obj);
};

/**
 * Struct describing the primary particle
 */
struct PrimaryParticle {
  UChar_t particle_id; ///> primary particle ID (gipart)
  std::array<Float_t, 3> starting_point; ///> primary particle starting point in cm (gpos0)
  std::array<Float_t, 3> direction; ///> primary particle direction at the starting point (gvec0)
  Float_t momentum; ///> momentum of the primary particle at the starting point in GeV (gamom0)

  void SetBranches(TTree &tree);

  friend std::ostream &operator<<(std::ostream &os, const PrimaryParticle &obj);
};

/**
 * Struct describing the cross-section information for coherent pion production.
 * Useful for t2kreweight.  For storing other intermediate calculations (currently only
 * used for coherent interaction M_A reweighting)
 */
struct CrsInfo {
  Float_t crsx; ///> X position of interaction vertex
  Float_t crsy; ///> Y position of interaction vertex
  Float_t crsz; ///> Z position of interaction vertex
  Float_t crsphi; ///> Angle between the neutrino and the lepton
  Float_t crsq2; ///> 4-momentum transfer Q^2 = (El - En)^2 - (pl - pn)^2
  /// where El = energy of lepton, En = energy of neutrino
  ///       pl = 3-momentum of lepton, pn = 3-momentum of neutrino

  void SetBranches(TTree &tree);
};

/**
 * Struct describing the final state interactions. Useful for t2kreweight.
 */
struct FsiHist {
  ///> number of vertices (Nvert)
  Int_t number_vertices;
  ///> position of vertex in nucleus (Posvert)
  Float_t vertex_position_in_nucleus[MAX_NUM_FSI_VERTICES][3];
  ///> Type of the vertex (Iflgvert)
  //     (*10 FOR HI-NRG)
  //     (*100 for SKDETSIM non-NEFFECT interactions
  //           +0 Free Hydrogen, +1 Oxygen)
  //
  // -1 : ESCAPE
  //  0 : INITIAL (or unmatched parent vertex if I>1)
  //  1 :
  //  2 :
  //  3 : ABSORPTION
  //  4 : CHARGE EXCHANGE
  //  5 :
  //  6 :
  //  7 : HADRON PRODUCTION (hi-nrg only, i.e. 70)
  //  8 : QUASI-ELASTIC SCATTER
  //  9 : FORWARD (ELASTIC-LIKE) SCATTER
  std::array<Int_t, MAX_NUM_FSI_VERTICES> vertex_type;
  ///> number of intermediate particles (Nvcvert)
  Int_t number_intermediate_particles;
  ///> direction of the intermediate particle (Dirvert)
  Float_t direction[MAX_NUM_INTERMEDIATE_PARTICLES][3];
  ///> Absolute momentum of the intermedABSOLUTE MOM. OF J-TH PART. in lab frame (MeV/c) (Abspvert)
  std::array<Float_t, MAX_NUM_INTERMEDIATE_PARTICLES> abs_momentum_lab_frame;
  ///>  ABSOLUTE MOM. OF J-TH PART. in nucleon rest frame (Abstpvert)
  std::array<Float_t, MAX_NUM_INTERMEDIATE_PARTICLES> abs_momentum_nucleon_frame;
  ///> PARTICLE CODE OF J-TH PARTICLE (Ipvert)
  std::array<Int_t, MAX_NUM_INTERMEDIATE_PARTICLES> particle_id;
  ///> INDEX OF INITIAL VERTEX OF J-TH PARTICLE (Iverti)
  std::array<Int_t, MAX_NUM_INTERMEDIATE_PARTICLES> initial_vertex_index;
  ///> INDEX OF FINAL VERTEX OF J-TH PARTICLE (Ivertf)
  std::array<Int_t, MAX_NUM_INTERMEDIATE_PARTICLES> final_vertex_index;
  ///> weight of event (Fsiprob)
  Float_t fsi_event_weight;
  ///> kind of target nucleus (Oxygen, Carbon, etc...) (Ibound)
  Int_t target_nucleus_type;

  void SetBranches(TTree &tree);
};

/**
 * Information about the target material.
 */
struct TargetInfo {
  ///> The number of bound neutrons in the material. For a nucleus,
  /// simply the number of neutrons in the nucleus. (Numbndn)
  /// (e.g. CH => 6, H2O => 8, Ar => 22, Fe => 30)
  Int_t number_bound_neutrons;
  ///> The number of bound protons in the material. (Numbndp)
  ///  (e.g. CH => 6, H2O => 8, Ar => 18, Fe => 26)
  Int_t number_bound_protons;
  ///> The number of free protons. As NEUT is designed for
  /// water, it allows for molecules with hydrogen atoms.
  /// These are treated as free protons. (Numfrep)
  Int_t number_free_protons;
  ///> The atomic mass number of the nucleus (not including any
  /// hydrogen) i.e. NUMATOM = NUMBNDN + NUMBNDP. NEUT should
  /// complain if this condition is not met. (Numatom)
  Int_t atomic_mass_number;

  void SetBranches(TTree &tree);

  friend std::ostream &operator<<(std::ostream &os, const TargetInfo &obj);

  /**
   * @return material of the target (isotopes are treated as the same)
   */
  B2Material GetMaterial() const;
};

/**
 * Information about the cross-section.
 */
struct NeutCrs {
  ///> energy of neutrino in GeV (same as 34.Enu) (Crsnergy)
  Float_t cross_section_energy;
  ///> total cross-section in 10^(-38) cm^2 (Totcrsne)
  Float_t total_cross_section;
  ///> differential cross-section. The parameter of the
  /// cross-section depends on the mode (Difcrsne)
  std::array<Float_t, 8> differential_cross_section;

  void SetBranches(TTree &tree);

  friend std::ostream &operator<<(std::ostream &os, const NeutCrs &obj);
};

/**
 * Information about the primary particle
 *
 * Interaction modes:
 * There are several different interaction modes that NEUT
 * can use. Set to 0 to select the mode for each event based on cross-section,
 * or set to an individual mode to generate  a single interaction
 * type. This can also be set to -1, which I believe selects from all modes
 * according to their weights set in NEUT-CRS (this may not be correct
 * though). A description of what interaction each mode corresponds to
 * is given in neutcore/nemodsel.F
 */
struct PrimaryParticles {
  ///> event number (Nev)
  Int_t event_number;
  ///> interaction mode (Mode)
  /// There are several different interaction modes that NEUT
  /// can use. A description of what interaction each mode corresponds to
  /// is given in neutcore/nemodsel.F. A partial list of modes is also
  /// contained in the B2InteractionMode enum
  Int_t mode;
  ///> number of particle at neutrino interaction (Numnu)
  ///   0 : incoming neutrino
  ///   1 : target (mostly neutron or proton)
  ///   2+ : outgoing particles
  Int_t num_particles;
  ///> particle code at neutrino interaction (P.D.G. code) Ipnu(numnu)
  std::array<Int_t, MAX_NUM_PRIMARY_PARTICLES> particle_id;
  ///> absolute momentum in GeV/c (Abspnu)
  std::array<Float_t, MAX_NUM_PRIMARY_PARTICLES> abs_momentum;
  ///> 3-momentum in GeV/c (Pnu)
  Float_t momentum[MAX_NUM_PRIMARY_PARTICLES][3];

  void SetBranches(TTree &tree);

  friend std::ostream &operator<<(std::ostream &os, const PrimaryParticles &obj);

  /**
   * @return index of the incoming neutrino to be used in the
   * particle_id, abs_momentum and momentum arrays
   */
  int GetIncomingNeutrinoIndex() const;

  /**
   * @return index of target nucleon to be used in the
   * particle_id, abs_momentum and momentum arrays
   */
  int GetTargetIndex() const;

  /**
   * @return index of the outgoing lepton to be used in the
   * particle_id, abs_momentum and momentum arrays
   */
  int GetOutgoingLeptonIndex();

  /**
   * @return index of the outgoing neutrino to be used in the
   * particle_id, abs_momentum and momentum arrays
   */
  int GetOutgoingNeutrinoIndex();

  /**
   * @param PDG ID of the desired outgoing particle
   * @return index of the outgoing particle to be used in the
   * particle_id, abs_momentum and momentum arrays
   */
  int GetOutgoingParticleIndex(PDG_t pdg_id);

};

/**
 * Information about the particle that produced the neutrino (in the beam line)
 */
struct ParentParticle {

  enum ParentParticleType {
    Production,
    Decay
  };

  ///> momentum of the parent particle in GeV (ppi)
  Float_t abs_momentum;
  ///> decay position of the parent particle in the global coordinate in cm (npi)
  std::array<Float_t, 3> vertex;
  ///> directional vector of the parent particle in the global coordinate (npi)
  std::array<Float_t, 3> direction;
  ///> cosine of the angle between the parent particle direction and the beam direction (cospibm)
  Float_t cos_beam;

  void SetBranches(TTree &tree, ParentParticleType type);

  friend std::ostream &operator<<(std::ostream &os, const ParentParticle &obj);
};

/*
 * Information about the primary neutrino and its parents.
 * The global coordinate position can be obtained by adding XFD(idFD), YFD(idFD)
 *
 * NFD[0,10]:I  : Number of near detectors defined in the simulation
 * BXFD(NFD):R, BYFD(NFD):R  : Beam center position at each ZFD in the global coordinate
 * XFD(NFD):R, YFD(NFD):R,ZFD(NFD):R   : detector center position in the global coordinate
 * HFD(NFD):R, VFD(NFD):R   : horizontal and vertical half size of the detector
 */
struct NeutNeutrino {
  ///> energy of the neutrino in GeV (Enu)
  Float_t energy;
  ///> ID of the particle that produced the neutrino (ppid)
  Int_t parent_id;
  ///> production mode (modefd)
  Int_t production_mode;
  ///> information about the parent particle (ppi, xpi, npi, cospibm)
  ParentParticle parent_decay;
  ///> weight factor to give flux/cm2 with 1E21 pot for each file (normalization)
  Float_t normalization;
  ///> obsolete: use number of parents "ng" instead.
  Int_t nvtx0;
  ///> same quantity as parent_decay except at the production of the parent particle.
  /// (ppi0, xpi0, npi0, cospi0bm)
  ParentParticle parent_production;
  ///> R position of neutrino at the detector in the detector coordinate in cm.
  /// The detector center is the origin. (rnu)
  Float_t r;
  ///> X position of neutrino at the detector in the detector coordinate in cm.
  /// The detector center is the origin. (xnu)
  Float_t x;
  ///> Y position of neutrino at the detector in the detector coordinate in cm.
  /// The detector center is the origin. (ynu)
  Float_t y;
  ///> neutrino direction in the global coordinate (nnu)
  std::array<Float_t, 3> direction;
  ///> detector ID number. (e.g. 3000.XFD(idFD) is the x position of the idFD detector.) (idfd)
  Int_t fdid;
  ///> information about the primary particle (gipart, gpos0, gvec0, gamom0)
  PrimaryParticle primary_particle;

  void SetBranches(TTree &tree);

  friend std::ostream &operator<<(std::ostream &os, const NeutNeutrino &obj);

private:
  static const std::unordered_map<int, std::string> production_mode_;
};

/*
 * Container struct filled with the information about a single neutrino event read from the NEUT file
 */
struct NeutEvent {
  Long64_t number_events; ///> total number of events
  Int_t id; ///>  event number

  PrimaryParticles primary; // list of primary particles
  FsiHist fsi; // information about final state interactions
  SecondaryParticles secondary; // list of secondary particles
  NeutCrs neut_crs; // information about NEUT cross-section
  CrsInfo crs_info; // information about coherent pion production
  NeutNeutrino neutrino; // information about the incoming neutrino and its parents
  TargetInfo target_info; // information about target material

  void SetBranches(TTree &tree);

  friend std::ostream &operator<<(std::ostream &os, const NeutEvent &obj);
};

///////////////////////////////////////////////////////////////////////////////////////////
//                                        B2Neut                                         //
///////////////////////////////////////////////////////////////////////////////////////////

/**
 * This class reads a NEUT neutrino event from a NEUT file and stores the information into
 * a NeutEvent container.
 */
class B2Neut {

private:

  int event_index_; ///> current index of the NEUT event
  TFile tfile_; ///> NEUT tfile handle
  TTree *ttree_; ///> NEUT ttree handle
  NeutEvent neut_event_{}; ///> current NEUT event container

private:

  /**
   * Open the NEUT file and set branches addresses
   * @param neut_file NEUT file to open
   * @return number of events in the NEUT file
   */
  Long64_t Initialize(const std::string &neut_file);

protected:

  /**
   * Empty constructor for unit testing
   */
  B2Neut();

  /**
   * Set test values for unit testing
   */
   virtual void SetTestValues();

public:

  /**
   * Initialize NEUT file reader. Just calls the Initialize method.
   * @param neut_file path to NEUT file
   */
  explicit B2Neut(const std::string &neut_file);

  B2Neut(const B2Neut &) = delete;

  // This class should not be copiable
  // move constructor and move assignment are not implicitly declared (Cf. C++11 12.8/9)
  B2Neut &operator()(const B2Neut &) = delete;

  /**
   * Read the next event into the NeutEvent container.
   *
   * @return interaction mode (in case of error the interaction mode is set to -1111)
   */
  int ReadNextEvent();

  /**
   * @return NeutEvent object getter
   */
  const NeutEvent &GetEvent();

  /**
   * Print current event info to the console
   */
  void DumpEvent();

  /**
   * @return NEUT TTree
   */
  TTree *GetNEUTTree() const;

public:

  /**
   * Convert NEUT particle production mode (modefd) into neutrino PDG ID
   * @param mode neutrino production mode from NEUT output
   * @return PDG ID of the neutrino
   */
  static PDG_t ProductionMode2PdgId(B2ProductionMode mode);
  static PDG_t ProductionMode2PdgId(int mode);

  /**
   * Convert NEUT particle production mode (modefd) into neutrino flavor (same same B2Settings)
   * @param mode neutrino production mode from NEUT output
   * @return neutrino flavor
   */
  static B2NeutrinoFlavor ProductionMode2NeutrinoFlavor(B2ProductionMode mode);
  static B2NeutrinoFlavor ProductionMode2NeutrinoFlavor(int mode);

};


#endif
