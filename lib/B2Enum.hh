//
// Created by Giorgio Pintaudi on 8/5/20.
//

#ifndef WAGASCIBABYMINDMONTECARLO_B2ENUM_HH
#define WAGASCIBABYMINDMONTECARLO_B2ENUM_HH

#include <unordered_map>
#include <string>
#include <cstddef>
#include <vector>

#include "B2Const.hh"

struct EnumClassHash {
  template<typename T>
  std::size_t operator()(T t) const {
    return static_cast<std::size_t>(t);
  }
};

/*
 * Sub-detectors ID. The numerical values are hard-coded into the geometry. Do not change them!
 */
enum B2Detector {
  kProtonModule = 0, ///> Proton module
  kWagasciUpstream = 1, ///> WAGASCI upstream
  kWagasciDownstream = 2, ///> WAGASCI downstream
  kWallMrdSouth = 3, ///> WallMRD south
  kWallMrdNorth = 4, ///> WallMRD north
  kBabyMind = 5, ///> BabyMIND
  kYasuTracker = 6, ///> YASU tracker
  kNinja = 7, ///> NINJA detector
  kNumDetectors = 8, ///> Number of detectors
  kWall = 9, ///> B2 floor concrete wall
  kPillarSouth = 10, ///> B2 floor south pillar
  kPillarNorth = 11, ///> B2 floor north pillar
  kUnknownDetector = B2_NON_INITIALIZED_VALUE
};

extern const std::unordered_map<B2Detector, std::string, EnumClassHash> DETECTOR_NAMES;

///> WallMRD direction (used for scintillator placement)
enum B2WallMrdDirection {
  kWallMrdSouthDirection = 1,
  kWallMrdNorthDirection = -1
};

enum B2CardinalDirection {
  kNorthDirection = 0,
  kSouthDirection,
  kDownstreamDirection,
  kUpstreamDirection,
  kUpDirection,
  kDownDirection,
  kNumCardianlDirections
};

///> Detector view
enum B2View {
  kSideView = 0, ///> view from side (when looking towards the south) (yz plane projection)
  kTopView = 1, ///> view from top (xz plane projection)
  kUnknownView = B2_NON_INITIALIZED_VALUE
};

extern const std::unordered_map<B2View, std::string, EnumClassHash> VIEW_NAMES;

///> Dimensionality
enum B2Dimensionality {
  kBidimensional = 0,
  kTridimensional,
  kOnePair,
  kUnknownDimension = B2_NON_INITIALIZED_VALUE
};

extern const std::unordered_map<B2Dimensionality, std::string, EnumClassHash> DIMENSIONALITY_NAMES;

///> type of readout of the scintillator bars
enum B2Readout {
  kTopReadout = 0, ///> Read from the top (WAGASCI, WallMRD, BabyMIND)
  kSideReadout = 1, ///> Read from the side (WAGASCI)
  kBottomReadout = 2, ///> Read from the left (WallMRD)
  kLeftReadout = 3, ///> Read from the left (BabyMIND)
  kRightReadout = 4, ///> Read from the left (BabyMIND)
  kUnknownReadout = 5, ///> Unknown readout
};

extern const std::unordered_map<B2Readout, std::size_t, EnumClassHash> READOUT_MAP;

extern const std::unordered_map<B2Readout, std::string, EnumClassHash> READOUT_NAMES;

///> Types of scintillator topology (horizontal bars, vertical bars or veto bars)
enum B2ScintillatorType {
  kVertical = 0,
  kHorizontal = 1,
  kVeto = 2,
  kLeft = 3,
  kRight = 4,
  kUnknownScintillatorType = B2_NON_INITIALIZED_VALUE
};

extern const std::unordered_map<B2ScintillatorType, std::string, EnumClassHash> SCINTILLATOR_TYPE_NAMES;

///> Every WAGASCI scintillator can be either of plane-type or grid-type. Grid scintillators can be
/// further subdivided into left of plane and right of plane scintillators.
enum B2GridPlane {
  kPlaneScintillator = 0,
  kGridLeftScintillator = 1,
  kGridRightScintillator = 2,
  kUnknownScintillator = B2_NON_INITIALIZED_VALUE
};

extern const std::unordered_map<B2GridPlane, std::string, EnumClassHash> GRID_PLANE_NAMES;

///> Selection of VETO planes
enum B2VetoPlane {
  kNotVeto = 0,
  kUpstreamVeto = 1,
  kUpVeto = 3,
  kBottomVeto = 4,
  kRightVeto = 5,
  kLeftVeto = 6
};

///> Neutrino beam line mode
enum B2NeutrinoBeamLineMode {
  kAntiNeutrinos = -1,
  kNeutrinos = 1
};

///> Type of event
enum B2EventType {
  kUnknownEventType = -2, ///> Unknown event type
  kCosmicSandMuonEvent = 0, ///> event due to a cosmic muon or sand muon
  kBeamNeutrinoEvent = 1, ///> event due to a neutrino interaction (from the neutrino beam line)
  kPencilBeamEvent = 2, ///> Pencil beam
  kEventIdStorage = 3, ///> Fake event used just to store the event ID of real data
};

enum B2TrackType {
  kPrimaryTrack = 0, ///> tracks going out of the primary vertex
  kSecondaryTrack = 1, ///> Secondary track that is not a Michel electron or a neutrino
  kUnknownTrackType = B2_NON_INITIALIZED_VALUE
};

///> Type of PrimaryTrack

enum B2PrimaryTrackType {
  kMatchingTrack = 0,
  kSingularTrack = 1,
  kSandMuonNonMatching = 2, ///> Muon produced from the interaction on wall, which go through only 1 subdetector except Baby MIND?
  kSandMuonMatching = 3, ///> Muon produced from the interaction on wall, which go through more than 2 subdetectors
  kBabyMind3DTrack = 4, ///> Track including only hits in Baby MIND (for NINJA)
  kSingleYASU = 5, //> Track reconstructed manually based on YASU trackers (a TargetModule to YASU)
  kPMtoDWGtoYASU = 6, //> Track reconstructed manually based on YASU trackers (PM to Downstream to YASU)
  kUWGtoPMtoDWGtoYASU = 7, //> Track reconstructed manually based on YASU trackers (PM to Downstream to YASU)
  kPMtoYASU = 8, //> Track reconstructed manually based on YASU trackers (PM to YASU)
  kUnknownPrimaryTrackType = B2_NON_INITIALIZED_VALUE
};

///> Type of SecondaryTrack

enum B2SecondaryTrackType {
  kMichelElectron = 0, ///> Michel electron or positron
  kMuonDecayNeutrino = 1, ///> Neutrinos accompaning Michel electron
  kGenericSecondaryTrack = 2,  ///> Secondary tracks other than Michel electrons and neutrinos
  kMichelElectronCandidateThatFailed = 3, ///> A Michel electron candidate that failed to pass the requirements
  kUnknownSecondaryTrackType = B2_NON_INITIALIZED_VALUE
};

extern const std::unordered_map<B2TrackType, std::string, EnumClassHash> TRACKED_PARTICLE_TYPE_NAMES;

extern const std::unordered_map<B2PrimaryTrackType, std::string, EnumClassHash> PRIMARY_TRACK_TYPE_NAMES;

extern const std::unordered_map<B2SecondaryTrackType, std::string, EnumClassHash> SECONDARY_TRACK_TYPE_NAMES;

/*
 * Interaction material
 */
enum B2Material {
  kWater = 0,
  kCarbon = 1,
  kIron = 2,
  kConcrete = 3,
  kSus304 = 4,
  kUnknownMaterial = B2_NON_INITIALIZED_VALUE,
};

extern const std::unordered_map<B2Material, std::string, EnumClassHash> MATERIAL_NAMES;

/*
 * Neutrino flavor
 */
enum B2NeutrinoFlavor {
  kCosmicMuon = -1,
  kPrimaryMuonNeutrino = 1,
  kPrimaryAntiMuonNeutrino = 2,
  kPrimaryElectronNeutrino = 3,
  kPrimaryAntiElectronNeutrino = 4,
};

/**
 * Global coordinates
 */
enum B2Coordinate {
  kX = 0,
  kY = 1,
  kZ = 2
};
/**
 * This enum controls if the WAGASCI detectors contain water or not.
 */
enum B2WaterSettings {
  kWgupOutWgdownOut = 1, ///> both WAGASCI upstream and WAGASCI downstream are empty
  kWgupInWgdownOut = 2, ///> WAGASCI upstream is full and WAGASCI downstream is empty
  kWgupOutWgdownIn = 3, ///> WAGASCI upstream is empty and WAGASCI downstream is full
  kWgupInWgdownIn = 4, ///> both WAGASCI upstream and WAGASCI downstream are full
};
/*
 * How the primary particle (neutrino) was produced in the beam line.
 */
enum B2ProductionMode {
  MODE_NUMU_ALL = 10,  // numu all
  MODE_NUMU_PI = 11,  // numu from pi+
  MODE_NUMU_K = 12,  // numu from K+
  MODE_NUMU_MU = 13,  // numu from mu-

  MODE_NUMUB_ALL = 20,  // numu_bar all
  MODE_NUMUB_PI = 21,  // numu_bar from pi-
  MODE_NUMUB_K = 22,  // numu_bar from K-
  MODE_NUMUB_MU = 23,  // numu_bar from mu+

  MODE_NUE_ALL = 30,  // nue all
  MODE_NUE_KPLUS = 31,  // nue from K+ (Ke3)
  MODE_NUE_K0 = 32,  // nue from K0L(Ke3)
  MODE_NUE_MU = 33,  // nue from Mu+

  MODE_NUEB_ALL = 40,  // nue_bar all
  MODE_NUEB_KMINUS = 41,  // nue_bar from K- (Ke3)
  MODE_NUEB_K0 = 42,  // nue_bar from K0L(Ke3)
  MODE_NUEB_MU = 43,  // nue_bar from Mu-
};
/*
 * NEUT interaction modes. See the PrimaryParticles::interaction_mode_ map for further details.
 */
enum B2InteractionMode {
  MODE_ERROR = -1111,
  MODE_UNKNOWN = 0,
  MODE_CCQE = 1,
  MODE_2P2H = 2,
  MODE_CC_1PROTON_1PI_PLUS = 11,
  MODE_CC_1PROTON_1PI_ZERO = 12,
  MODE_CC_1NEUTRON_1PI_PLUS = 13,
  MODE_CC_COHERENT_PI_PLUS = 16,
  MODE_CC_1PROTON_1GAMMA = 17,
  MODE_CC_MULTI_PI = 21,
  MODE_CC_ETA = 22,
  MODE_CC_LAMBDA = 23,
  MODE_CC_DIS = 26,
  MODE_CC_DIFFRACTIVE_PI = 27,
  MODE_NC_1NEUTRON_1PI_ZERO = 31,
  MODE_NC_1PROTON_1PI_ZERO = 32,
  MODE_NC_1PROTON_1PI_MINUS = 33,
  MODE_NC_1NEUTRON_1PI_PLUS = 34,
  MODE_NC_COHERENT_PI_ZERO = 36,
  MODE_NC_1NEUTRON_1GAMMA = 38,
  MODE_NC_1PROTON_1GAMMA = 39,
  MODE_NC_MULTI_PI = 41,
  MODE_NC_1NEUTRON_ETA = 42,
  MODE_NC_1PROTON_ETA = 43,
  MODE_NC_LAMBDA_KAON_ZERO = 44,
  MODE_NC_LAMBDA_KAON_PLUS = 45,
  MODE_NC_MESONS = 46,
  MODE_NC_DIFFRACTIVE_PI = 47,
  MODE_NC_ELASTIC_1PROTON = 51,
  MODE_NC_ELASTIC_1NEUTRON = 52,
  MODE_MICHEL_ELECTRON = 666,
  MODE_COSMIC_MUON = 667,
  MODE_PENCIL_BEAM = 668,
  MODE_NINJA_KINK_BEAM = 669,
};

/*
 * There are two types of scintillator bars inside the Proton Module.
 * - INGRID-type scintillator bars of 1cm x 5cm x 120cm
 * - SciBar-type scintillator bars of 1.3cm x 2.5cm x 120cm
 */
enum B2ProtonModuleScintillatorType {
  kIngridType = 0,
  kSciBarType = 1
};

/**
 * Emulsion film consists of two gel layers on a polystyrene base.
 * Track in a film is made by coincidence of the both layers
 */
enum B2EmulsionLayer {
  ///> downstream (north) gel layer in one emulsion film
  kDownstreamGel = 0,
  ///> upstream (south) gel layer in one emulsion film
  kUpstreamGel = 1
};

/**
 * We have roughly three types of emulsion films.
 * Each type of films are analysed separately.
 */
enum B2EmulsionType {
  ///> Water/Iron ECC, ISS
  kECC = 0,
  ///> OSS, Shifter, TSS
  kShifter = 1,
  ///> SSS, SDS
  kSSS = 2,
  ///> Unknown emulsion film type
  kUnknownEmulsionType = B2_NON_INITIALIZED_VALUE
};

/**
 * Enum to distinguish true and recon information
 */
enum B2DataType {
  kMonteCarlo,
  kRealData
};

extern const std::unordered_map<B2EmulsionType, std::string, EnumClassHash> FILMTYPE_NAMES;

/**
 * X coordinate offset for each subdetector
 */
extern const std::unordered_map<B2Detector, double, EnumClassHash> POSITION_OFFSET_X;

/**
 * Y coordinate offset for each subdetector
 */
extern const std::unordered_map<B2Detector, double, EnumClassHash> POSITION_OFFSET_Y;

/**
 * Z coordinate offset for each subdetector
 */
extern const std::unordered_map<B2Detector, double, EnumClassHash> POSITION_OFFSET_Z;

/**
 * Convert from readout to view
 * @param readout readout
 * @return view
 */
B2View readout_to_view(B2Readout readout);

/**
 * Calculate number of readouts for each detector
 * @param detector detector ID
 * @return number of readouts
 */
unsigned detector_to_number_readouts(B2Detector detector);

/**
 * Calculate readout 1 (arbitrary) for double readout detectors
 * @param detector detector ID
 * @param scintillator_type scintillator type (verticle, horizontal, etc...)
 * @return readout
 */
B2Readout detector_to_readout1(B2Detector detector, B2ScintillatorType scintillator_type);

/**
 * Calculate readout 1 (arbitrary) for double readout detectors
 * @param detector detector ID
 * @param scintillator_type scintillator type (verticle, horizontal, etc...)
 * @return readout
 */
B2Readout detector_to_readout2(B2Detector detector, B2ScintillatorType scintillator_type);

/**
 * Calculate single readout for single readout detectors
 * @param detector detector ID
 * @param scintillator_type scintillator type (verticle, horizontal, etc...)
 * @param plane plane number
 * @return readout
 */
B2Readout detector_to_single_readout(B2Detector detector, B2ScintillatorType scintillator_type, int plane = 0);

/**
 * List all the readouts of a specific detector
 * @param detector detector ID
 * @param scintillator_type scintillator type (verticle, horizontal, etc...)
 * @param plane plane number
 * @return readouts
 */
std::vector<B2Readout> detector_to_readouts(B2Detector detector, B2ScintillatorType scintillator_type, int plane = 0);

/**
 * Interaction Feynman diagram description
 */
extern const std::unordered_map<B2InteractionMode, std::string, EnumClassHash> INTERACTION_MODE;

#endif //WAGASCIBABYMINDMONTECARLO_B2ENUM_HH
