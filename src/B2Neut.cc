#include "B2Neut.hh"

// Geant4 includes
#include <G4ios.hh>
#include <TVector3.h>

// BOOST includes
#include <boost/log/trivial.hpp>

// user includes
#include "B2Enum.hh"
#include "B2SpillSummary.hh"

const std::unordered_map<int, std::string> NeutNeutrino::production_mode_{ // NOLINT(cert-err58-cpp)
    {B2ProductionMode::MODE_NUMU_ALL,    "muon neutrino all"},
    {B2ProductionMode::MODE_NUMU_PI,     "muon neutrino from pi+"},
    {B2ProductionMode::MODE_NUMU_K,      "muon neutrino from K+"},
    {B2ProductionMode::MODE_NUMU_MU,     "muon neutrino from mu-"},

    {B2ProductionMode::MODE_NUMUB_ALL,   "muon anti-neutrino all"},
    {B2ProductionMode::MODE_NUMUB_PI,    "muon anti-neutrino from pi-"},
    {B2ProductionMode::MODE_NUMUB_K,     "muon anti-neutrino from K-"},
    {B2ProductionMode::MODE_NUMUB_MU,    "muon anti-neutrino from mu+"},

    {B2ProductionMode::MODE_NUE_ALL,     "electron neutrino all"},
    {B2ProductionMode::MODE_NUE_KPLUS,   "electron neutrino from K+ (Ke3)"},
    {B2ProductionMode::MODE_NUE_K0,      "electron neutrino from K0L(Ke3)"},
    {B2ProductionMode::MODE_NUE_MU,      "electron neutrino from Mu+"},

    {B2ProductionMode::MODE_NUEB_ALL,    "electron anti-neutrino all"},
    {B2ProductionMode::MODE_NUEB_KMINUS, "electron anti-neutrino from K- (Ke3)"},
    {B2ProductionMode::MODE_NUEB_K0,     "electron anti-neutrino from K0L(Ke3)"},
    {B2ProductionMode::MODE_NUEB_MU,     "electron anti-neutrino from Mu-"},
};

std::ostream &operator<<(std::ostream &os, const SecondaryParticles &obj) {
  os << "    Number of secondary particles : " << obj.num_particles << "\n";
  os << "    Vertex : x = " << obj.vertex[B2Coordinate::kX] << " cm, y = " << obj.vertex[B2Coordinate::kY]
     << " cm, z = " << obj.vertex[B2Coordinate::kZ] << "cm\n";
  for (int j = 0; j < obj.num_particles; ++j) {
    os << "    Particle " << j << " :\n";
    os << "      Particle : " << B2Pdg::Stringify(obj.particle_id[j]) << " (PDGID " << obj.particle_id[j] << ")\n";
    os << "      Parent particle : " << B2Pdg::Stringify(obj.parent_id[j]) << " (PDGID " << obj.parent_id[j] << ")\n";
    os << "      Tracking Flag : ";
    if (obj.tracking_flag[j] == SecondaryParticles::kStopInsideNucleus)
      os << "stop inside the nucleus (" << SecondaryParticles::kStopInsideNucleus << ")\n";
    else if (obj.tracking_flag[j] == SecondaryParticles::kExitNucleus)
      os << "exit the nucleus (" << SecondaryParticles::kExitNucleus << ")\n";
    else
      os << "not recognized (" << obj.tracking_flag[j] << ")\n";
    os << "      Interaction Code : " << obj.interaction_code[j] << "\n";
    os << "      Absolute Momentum : " << obj.abs_momentum[j] << " MeV\n";
    os << "      Momentum : px = " << obj.momentum[j][B2Coordinate::kX]
       << " MeV, py = " << obj.momentum[j][B2Coordinate::kY]
       << " MeV, pz = " << obj.momentum[j][B2Coordinate::kZ] << "MeV\n";
  }
  return os;
}

std::ostream &operator<<(std::ostream &os, const PrimaryParticle &obj) {
  os << "      Particle : " << B2Pdg::Stringify((Int_t) obj.particle_id)
     << " (PDGID " << (Int_t) obj.particle_id << ")\n";
  os << "      Starting point : x = " << obj.starting_point[B2Coordinate::kX]
     << " cm, y = " << obj.starting_point[B2Coordinate::kY]
     << " cm, z = " << obj.starting_point[B2Coordinate::kZ] << "cm\n";
  os << "      Direction : x = " << obj.direction[B2Coordinate::kX]
     << ", y = " << obj.direction[B2Coordinate::kY]
     << ", z = " << obj.direction[B2Coordinate::kZ] << "\n";
  os << "      Absolute Momentum : " << obj.momentum << " GeV\n";
  return os;
}

std::ostream &operator<<(std::ostream &os, const NeutCrs &obj) {
  os << "    Cross-section energy : " << obj.cross_section_energy << " GeV\n";
  os << "    Total cross-section : " << obj.total_cross_section << " 10^(-38) cm^2\n";
  os << "    Differential cross-section : ";
  for (float i : obj.differential_cross_section) {
    os << i << " ";
  }
  os << "\n";
  return os;
}

std::ostream &operator<<(std::ostream &os, const PrimaryParticles &obj) {
  os << "    Event number : " << obj.event_number << "\n";
  os << "    Neutrino interaction : ";
  if (INTERACTION_MODE.count(static_cast<B2InteractionMode>(obj.mode)) > 0)
    os << INTERACTION_MODE.at(static_cast<B2InteractionMode>(obj.mode));
  else
    os << "not recognized";
  os << " (mode " << obj.mode << ")\n";
  os << "    Number of primary particles : " << obj.num_particles << "\n";
  for (int j = 0; j < obj.num_particles; ++j) {
    os << "     Particle " << j << " :\n";
    os << "       Particle : " << B2Pdg::Stringify(obj.particle_id[j])
       << " (PDGID " << obj.particle_id[j] << ")\n";
    os << "       Absolute Momentum : " << obj.abs_momentum[j] << " GeV\n";
    os << "       Momentum : px = " << obj.momentum[j][B2Coordinate::kX]
       << " GeV, py = " << obj.momentum[j][B2Coordinate::kY]
       << " GeV, pz = " << obj.momentum[j][B2Coordinate::kZ] << "GeV\n";
  }
  return os;
}

std::ostream &operator<<(std::ostream &os, const ParentParticle &obj) {
  os << "      Absolute Momentum : " << obj.abs_momentum << " GeV\n";
  os << "      Vertex : x = " << obj.vertex[B2Coordinate::kX]
     << " cm, y = " << obj.vertex[B2Coordinate::kY]
     << " cm, z = " << obj.vertex[B2Coordinate::kZ] << "cm\n";
  os << "      Direction : x = " << obj.direction[B2Coordinate::kX]
     << ", y = " << obj.direction[B2Coordinate::kY]
     << ", z = " << obj.direction[B2Coordinate::kZ] << "\n";
  os << "      Cosine of angle with beam : " << obj.cos_beam << "\n";
  return os;
}

std::ostream &operator<<(std::ostream &os, const TargetInfo &obj) {
  os << "    Number of bound neutrons : " << obj.number_bound_neutrons << "\n";
  os << "    Number of bound protons : " << obj.number_bound_protons << "\n";
  os << "    Number of free protons : " << obj.number_free_protons << "\n";
  os << "    Atomic mass number : " << obj.atomic_mass_number << "\n";
  return os;
}

std::ostream &operator<<(std::ostream &os, const NeutNeutrino &obj) {
  os << "    Energy : " << obj.energy << " GeV\n";
  os << "    Parent particle : " << B2Pdg::Stringify(obj.parent_id) << " (PDGID " << obj.parent_id << ")\n";
  os << "    Production Mode : ";
  if (NeutNeutrino::production_mode_.count(obj.production_mode) > 0)
    os << NeutNeutrino::production_mode_.at(obj.production_mode);
  else
    os << "not recognized";
  os << " (" << obj.production_mode << ")\n";
  os << "    Interaction vertex : R = " << obj.r << " cm, X = " << obj.x
     << " cm, Y = " << obj.y << " cm\n";
  os << "    Direction : x = " << obj.direction[B2Coordinate::kX]
     << ", y = " << obj.direction[B2Coordinate::kY]
     << ", z = " << obj.direction[B2Coordinate::kZ] << "\n";
  os << "    Detector ID number (FDID) : " << obj.fdid << "\n";
  os << "    Weighting Factor (Normalization) : " << obj.normalization << "\n";
  os << "    Primary particle information :\n";
  os << obj.primary_particle;
  os << "    Parent particle production :\n";
  os << obj.parent_production;
  os << "    Parent particle decay :\n";
  os << obj.parent_decay;
  return os;
}

std::ostream &operator<<(std::ostream &os, const NeutEvent &obj) {
  os << "  Number of events : " << obj.number_events << "\n";
  os << "  Event ID : " << obj.id << "\n";
  os << "  Primary particles :\n";
  os << obj.primary;
  os << "  Secondary particles :\n";
  os << obj.secondary;
  os << "  Neutrino information :\n";
  os << obj.neutrino;
  os << "  Cross section information :\n";
  os << obj.neut_crs;
  os << "  Target material information :\n";
  os << obj.target_info;
  return os;
}

void SecondaryParticles::SetBranches(TTree &tree) {
  tree.SetBranchAddress("Npar", &num_particles);
  tree.SetBranchAddress("Ipv", particle_id.data());
  tree.SetBranchAddress("Iorgv", parent_id.data());
  tree.SetBranchAddress("Icrnv", tracking_flag.data());
  tree.SetBranchAddress("Iflgv", interaction_code.data());
  tree.SetBranchAddress("Abspv", abs_momentum.data());
  tree.SetBranchAddress("Pmomv", momentum);
  tree.SetBranchAddress("Pos", vertex.data());
}

void PrimaryParticle::SetBranches(TTree &tree) {
  tree.SetBranchAddress("gipart", &particle_id);
  tree.SetBranchAddress("gpos0", starting_point.data());
  tree.SetBranchAddress("gvec0", direction.data());
  tree.SetBranchAddress("gamom0", &momentum);
}

void CrsInfo::SetBranches(TTree &tree) {
  tree.SetBranchAddress("Crsx", &crsx);
  tree.SetBranchAddress("Crsy", &crsy);
  tree.SetBranchAddress("Crsz", &crsz);
  tree.SetBranchAddress("Crsphi", &crsphi);
  tree.SetBranchAddress("Crsq2", &crsq2);
}

void FsiHist::SetBranches(TTree &tree) {
  tree.SetBranchAddress("Nvert", &number_vertices);
  tree.SetBranchAddress("Posvert", vertex_position_in_nucleus);
  tree.SetBranchAddress("Iflgvert", vertex_type.data());
  tree.SetBranchAddress("Nvcvert", &number_intermediate_particles);
  tree.SetBranchAddress("Dirvert", direction);
  tree.SetBranchAddress("Abspvert", abs_momentum_lab_frame.data());
  tree.SetBranchAddress("Abstpvert", abs_momentum_nucleon_frame.data());
  tree.SetBranchAddress("Ipvert", particle_id.data());
  tree.SetBranchAddress("Iverti", initial_vertex_index.data());
  tree.SetBranchAddress("Ivertf", final_vertex_index.data());
  tree.SetBranchAddress("Fsiprob", &fsi_event_weight);
  tree.SetBranchAddress("Ibound", &target_nucleus_type);
}

void TargetInfo::SetBranches(TTree &tree) {
  tree.SetBranchAddress("Numbndn", &number_bound_neutrons);
  tree.SetBranchAddress("Numbndp", &number_bound_protons);
  tree.SetBranchAddress("Numfrep", &number_free_protons);
  tree.SetBranchAddress("Numatom", &atomic_mass_number);
}

B2Material TargetInfo::GetMaterial() const {
  switch (number_bound_protons) {
    case 8:
      return B2Material::kWater;
    case 6:
      return B2Material::kCarbon;
    case 26:
      return B2Material::kIron;
    default:
      return B2Material::kConcrete;
  }
}

void NeutCrs::SetBranches(TTree &tree) {
  tree.SetBranchAddress("Crsenergy", &cross_section_energy);
  tree.SetBranchAddress("Totcrsne", &total_cross_section);
  tree.SetBranchAddress("Difcrsne", differential_cross_section.data());
}

void PrimaryParticles::SetBranches(TTree &tree) {
  tree.SetBranchAddress("Nev", &event_number);
  tree.SetBranchAddress("Mode", &mode);
  tree.SetBranchAddress("Numnu", &num_particles);
  tree.SetBranchAddress("Ipnu", particle_id.data());
  tree.SetBranchAddress("Abspnu", abs_momentum.data());
  tree.SetBranchAddress("Pnu", momentum);
}

int PrimaryParticles::GetOutgoingParticleIndex(PDG_t pdg_id) {
  if (num_particles > 1) {
    for (auto it = std::next(particle_id.begin(), 2); it != particle_id.end(); ++it) {
      if (*it == pdg_id)
        return (int) std::distance(particle_id.begin(), it);
    }
  }
  return -1;
}

int PrimaryParticles::GetOutgoingNeutrinoIndex() {
  if (num_particles > 1) {
    for (auto it = std::next(particle_id.begin(), 2); it != particle_id.end(); ++it) {
      if (B2Pdg::IsNeutrinoOrAntiNeutrino(*it))
        return (int) std::distance(particle_id.begin(), it);
    }
  }
  return -1;
}

int PrimaryParticles::GetOutgoingLeptonIndex() {
  if (num_particles > 1) {
    for (auto it = std::next(particle_id.begin(), 2); it != particle_id.end(); ++it) {
      if (B2Pdg::IsLepton(*it))
        return (int) std::distance(particle_id.begin(), it);
    }
  }
  return -1;
}

int PrimaryParticles::GetTargetIndex() const {
  return num_particles > 1 ? 1 : -1;
}

int PrimaryParticles::GetIncomingNeutrinoIndex() const {
  return num_particles > 0 ? 0 : -1;
}

void ParentParticle::SetBranches(TTree &tree, ParentParticleType type) {
  switch (type) {
    case Production:
      tree.SetBranchAddress("ppi0", &abs_momentum);
      tree.SetBranchAddress("xpi0", vertex.data());
      tree.SetBranchAddress("npi0", direction.data());
      tree.SetBranchAddress("cospi0bm", &cos_beam);
      break;
    case Decay:
      tree.SetBranchAddress("ppi", &abs_momentum);
      tree.SetBranchAddress("xpi", vertex.data());
      tree.SetBranchAddress("npi", direction.data());
      tree.SetBranchAddress("cospibm", &cos_beam);
      break;
  }
}

void NeutNeutrino::SetBranches(TTree &tree) {
  tree.SetBranchAddress("Enu", &energy);
  tree.SetBranchAddress("ppid", &parent_id);
  tree.SetBranchAddress("modefd", &production_mode);
  parent_decay.SetBranches(tree, ParentParticle::ParentParticleType::Decay);
  tree.SetBranchAddress("norm", &normalization);
  tree.SetBranchAddress("nvtx0", &nvtx0);
  parent_production.SetBranches(tree, ParentParticle::ParentParticleType::Production);
  tree.SetBranchAddress("rnu", &r);
  tree.SetBranchAddress("xnu", &x);
  tree.SetBranchAddress("ynu", &y);
  tree.SetBranchAddress("nnu", direction.data());
  tree.SetBranchAddress("idfd", &fdid);
  primary_particle.SetBranches(tree);
}

void NeutEvent::SetBranches(TTree &tree) {
  primary.SetBranches(tree);
  fsi.SetBranches(tree);
  secondary.SetBranches(tree);
  neut_crs.SetBranches(tree);
  crs_info.SetBranches(tree);
  neutrino.SetBranches(tree);
  target_info.SetBranches(tree);
}

B2Neut::B2Neut(const std::string &neut_file) :
    event_index_(0),
    tfile_(neut_file.c_str(), "READ"),
    ttree_(nullptr) {
  if (Initialize(neut_file) <= 0) {
    throw std::runtime_error("No events found in NEUT file : " + std::string(neut_file));
  }
}

B2Neut::B2Neut() : event_index_(0), ttree_(nullptr) {}

Long64_t B2Neut::Initialize(const std::string &neut_file) {

  BOOST_LOG_TRIVIAL(info) << "Reading NEUT file " << neut_file << " ......\n";

  ttree_ = (TTree *) tfile_.Get(NEUT_TREE_NAME.c_str());
  if (ttree_ == nullptr) {
    std::stringstream ss;
    ss << "Failed to read TTree named " << NEUT_TREE_NAME << " from NEUT file " << neut_file;
    throw std::runtime_error(ss.str());
  }

  neut_event_.SetBranches(*ttree_);
  neut_event_.number_events = ttree_->GetEntries();

  return neut_event_.number_events;
}

int B2Neut::ReadNextEvent() {

  if (event_index_ > neut_event_.number_events) {
    neut_event_.primary.mode = B2InteractionMode::MODE_ERROR;
    return neut_event_.primary.mode;
  }

  if (event_index_ % 10000 == 0) {
    BOOST_LOG_TRIVIAL(info) << "Read " << event_index_ << " NEUT events\n";
  }

  ttree_->GetEntry(event_index_);
  neut_event_.id = event_index_++;

  return neut_event_.primary.mode;
}

const NeutEvent &B2Neut::GetEvent() {
  return neut_event_;
}

void B2Neut::DumpEvent() {
  BOOST_LOG_TRIVIAL(info) << "**************************************************\n";
  BOOST_LOG_TRIVIAL(info) << "************ Input NEUT file infomation **********\n";
  BOOST_LOG_TRIVIAL(info) << "**************************************************\n";
  BOOST_LOG_TRIVIAL(info) << neut_event_ << G4endl;
}

PDG_t B2Neut::ProductionMode2PdgId(int mode) {
  return B2Neut::ProductionMode2PdgId((B2ProductionMode) mode);
}

PDG_t B2Neut::ProductionMode2PdgId(B2ProductionMode mode) {
  if (mode >= 10 && mode <= 19)
    return PDG_t::kNuMu;
  else if (mode >= 20 && mode <= 29)
    return PDG_t::kNuMuBar;
  else if (mode >= 30 && mode <= 39)
    return PDG_t::kNuE;
  else if (mode >= 40 && mode <= 49)
    return PDG_t::kNuEBar;
  else
    throw std::invalid_argument("Particle production mode not recognized : " + std::to_string(mode));
}

B2NeutrinoFlavor B2Neut::ProductionMode2NeutrinoFlavor(B2ProductionMode mode) {
  if (mode >= 10 && mode <= 19)
    return B2NeutrinoFlavor::kPrimaryMuonNeutrino;
  else if (mode >= 20 && mode <= 29)
    return B2NeutrinoFlavor::kPrimaryAntiMuonNeutrino;
  else if (mode >= 30 && mode <= 39)
    return B2NeutrinoFlavor::kPrimaryElectronNeutrino;
  else if (mode >= 40 && mode <= 49)
    return B2NeutrinoFlavor::kPrimaryAntiElectronNeutrino;
  else
    throw std::invalid_argument("Particle production mode not recognized : " + std::to_string(mode));
}

B2NeutrinoFlavor B2Neut::ProductionMode2NeutrinoFlavor(int mode) {
  return B2Neut::ProductionMode2NeutrinoFlavor((B2ProductionMode) mode);
}

void B2Neut::SetTestValues() {
  neut_event_.neutrino.energy = 0.8801277; // GeV
  neut_event_.neutrino.production_mode = 11;
  neut_event_.neutrino.normalization = 2.692e+14;
  neut_event_.neutrino.x = -30.22892; // cm
  neut_event_.neutrino.y = 49.738487; // cm
  neut_event_.neut_crs.total_cross_section = 1.2541106; // 10^(-38) cm^2
  neut_event_.primary.event_number = 4;
  neut_event_.primary.mode = 1;
  neut_event_.primary.num_particles = 4;
  neut_event_.primary.particle_id.at(0) = 14;
  neut_event_.primary.particle_id.at(1) = 2112;
  neut_event_.primary.particle_id.at(2) = 13;
  neut_event_.primary.particle_id.at(3) = 2212;
  neut_event_.target_info.number_bound_neutrons = 8;
  neut_event_.target_info.number_bound_protons = 8;
  neut_event_.target_info.atomic_mass_number = 16;
  neut_event_.primary.abs_momentum.at(0) = 0.8801278; // GeV/c
  neut_event_.primary.abs_momentum.at(1) = 0.1744690; // GeV/c
  neut_event_.primary.abs_momentum.at(2) = 0.4867432; // GeV/c
  neut_event_.primary.abs_momentum.at(3) = 0.9157828; // GeV/c
  neut_event_.primary.momentum[0][B2Coordinate::kX] = -0.024457; // GeV/c
  neut_event_.primary.momentum[0][B2Coordinate::kY] = -0.071376; // GeV/c
  neut_event_.primary.momentum[0][B2Coordinate::kZ] = 0.8768877; // GeV/c
  neut_event_.secondary.num_particles = 5;
  neut_event_.secondary.particle_id.at(0) = 14;
  neut_event_.secondary.particle_id.at(1) = 2112;
  neut_event_.secondary.particle_id.at(2) = 13;
  neut_event_.secondary.particle_id.at(3) = 2212;
  neut_event_.secondary.particle_id.at(4) = 22;
  neut_event_.secondary.tracking_flag.at(0) = 0;
  neut_event_.secondary.tracking_flag.at(1) = 0;
  neut_event_.secondary.tracking_flag.at(2) = 1;
  neut_event_.secondary.tracking_flag.at(3) = 1;
  neut_event_.secondary.tracking_flag.at(4) = 1;
  neut_event_.secondary.momentum[0][B2Coordinate::kX] = -24.45773; // MeV/c
  neut_event_.secondary.momentum[0][B2Coordinate::kY] = -71.37625; // MeV/c
  neut_event_.secondary.momentum[0][B2Coordinate::kZ] = 876.88781; // MeV/c
  neut_event_.secondary.momentum[1][B2Coordinate::kX] = -83.20854; // MeV/c
  neut_event_.secondary.momentum[1][B2Coordinate::kY] = 147.97674; // MeV/c
  neut_event_.secondary.momentum[1][B2Coordinate::kZ] = 40.232555; // MeV/c
  neut_event_.secondary.momentum[2][B2Coordinate::kX] = -460.1699; // MeV/c
  neut_event_.secondary.momentum[2][B2Coordinate::kY] = 140.15473; // MeV/c
  neut_event_.secondary.momentum[2][B2Coordinate::kZ] = 74.291549; // MeV/c
  neut_event_.secondary.momentum[3][B2Coordinate::kX] = 352.50347; // MeV/c
  neut_event_.secondary.momentum[3][B2Coordinate::kY] = -63.55488; // MeV/c
  neut_event_.secondary.momentum[3][B2Coordinate::kZ] = 842.82873; // MeV/c
  neut_event_.secondary.momentum[4][B2Coordinate::kX] = -1.364530; // MeV/c
  neut_event_.secondary.momentum[4][B2Coordinate::kY] = -5.790673; // MeV/c
  neut_event_.secondary.momentum[4][B2Coordinate::kZ] = 1.6728867; // MeV/c
  neut_event_.secondary.abs_momentum.at(0) = 880.12780; // MeV/c
  neut_event_.secondary.abs_momentum.at(1) = 174.46900; // MeV/c
  neut_event_.secondary.abs_momentum.at(2) = 486.74325; // MeV/c
  neut_event_.secondary.abs_momentum.at(3) = 915.78283; // MeV/c
  neut_event_.secondary.abs_momentum.at(4) = 6.1799993; // MeV/c
}

TTree *B2Neut::GetNEUTTree() const {
  return ttree_;
}
