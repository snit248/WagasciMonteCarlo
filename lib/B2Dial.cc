//
// Created by Giorgio Pintaudi on 2021/12/08.
//

#include <B2Dial.hh>

const std::unordered_map<B2DialField, std::string, EnumClassHash> DIAL_FIELD_NAMES = {
    {kEngineId,     "EngineId"},
    {kDialId,       "DialId"},
    {kEngineName,   "EngineName"},
    {kDialName,     "DialName"},
    {kType,         "Type"},
    {kFromValue,    "FromValue"},
    {kSigmaList,    "SigmaList"},
    {kSigmaUp,      "SigmaUp"},
    {kSigmaDown,    "SigmaDown"},
    {kBoundaryUp,   "BoundaryUp"},
    {kBoundaryDown, "BoundaryDown"},
    {kUnits,        "Units"},
    {kDescription,  "Description"}
};

const std::unordered_map<B2DialType, std::string, EnumClassHash> DIAL_TYPE_NAMES = {
    {kRealNumber, "real number"},
    {kInteger,    "integer"},
    {kBoolean,    "boolean"},
};

B2Dial::B2Dial() : TNamed("unknown_dial", "unknown_dial"), engine_id_(-1), dial_id_(-1) {
  EnableAllFields();
}

B2Dial::B2Dial(Int_t engine_id, Int_t dial_id) :
    TNamed(TString(engine_id) + "_" + TString(dial_id), TString(engine_id) + "_" + TString(dial_id)),
    engine_id_(engine_id), dial_id_(dial_id) {
  EnableAllFields();
}

Int_t B2Dial::GetEngineId() const {
  return engine_id_;
}

Int_t B2Dial::GetDialId() const {
  return dial_id_;
}

const TString &B2Dial::GetEngineName() const {
  return engine_name_;
}

const TString &B2Dial::GetDialName() const {
  return dial_name_;
}

B2DialType B2Dial::GetType() const {
  return static_cast<B2DialType>(type_);
}

Double_t B2Dial::GetFromValue() const {
  return from_value_;
}

Double_t B2Dial::GetSigmaUp() const {
  return sigma_up_;
}

Double_t B2Dial::GetSigmaDown() const {
  return sigma_down_;
}

Double_t B2Dial::GetBoundaryUp() const {
  return boundary_up_;
}

Double_t B2Dial::GetBoundaryDown() const {
  return boundary_down_;
}

const TString &B2Dial::GetUnits() const {
  return units_;
}

const TString &B2Dial::GetDescription() const {
  return description_;
}

void B2Dial::EnableField(B2DialField field) {
  const UInt_t mask = 1;
  enabled_fields_ |= (mask << field);
}

void B2Dial::EnableAllFields() {
  for (int i = 0; i < B2DialField::kNumDialFields; ++i) {
    EnableField((B2DialField) i);
  }
}

void B2Dial::DisableField(B2DialField field) {
  const UInt_t mask = 1;
  enabled_fields_ &= ~(mask << field);
}

void B2Dial::DisableAllFields() {
  for (int i = 0; i < B2DialField::kNumDialFields; ++i) {
    DisableField((B2DialField) i);
  }
}

bool B2Dial::IsFieldEnabled(B2DialField field) const {
  const UInt_t mask = 1;
  return enabled_fields_ & (mask << field);
}

bool B2Dial::IsFieldDisabled(B2DialField field) const {
  const UInt_t mask = 1;
  return !bool(enabled_fields_ & (mask << field));
}

void B2Dial::SetEngineName(const TString &engine_name) {
  engine_name_ = engine_name;
}

void B2Dial::SetDialName(const TString &dial_name) {
  dial_name_ = dial_name;
  SetNameTitle(dial_name_, dial_name_);
}

void B2Dial::SetType(B2DialType type) {
  type_ = type;
}

void B2Dial::SetFromValue(Double_t from_value) {
  from_value_ = from_value;
}

void B2Dial::SetSigmaUp(Double_t sigma_up) {
  sigma_up_ = sigma_up;
}

void B2Dial::SetSigmaDown(Double_t sigma_down) {
  sigma_down_ = sigma_down;
}

void B2Dial::SetBoundaryUp(Double_t boundary_up) {
  boundary_up_ = boundary_up;
}

void B2Dial::SetBoundaryDown(Double_t boundary_down) {
  boundary_down_ = boundary_down;
}

void B2Dial::SetUnits(const TString &units) {
  units_ = units;
}

void B2Dial::SetDescription(const TString &description) {
  description_ = description;
}

std::ostream &operator<<(std::ostream &os, const B2Dial &obj) {
  os << "Engine ID = " << obj.GetEngineId() << "\n"
     << "Dial ID = " << obj.GetDialId() << "\n"
     << "Engine name = " << obj.GetEngineName() << "\n"
     << "Dial name = " << obj.GetDialName() << "\n"
     << "Dial type = " << DIAL_TYPE_NAMES.at(obj.GetType()) << "\n"
     << "Nominal value = " << obj.GetFromValue() << " " << obj.GetUnits() << "\n"
     << "Sigma list = [";
  for (const auto &sigma: obj.GetSigmaList())
    os << sigma << ",";
  os << "]\n";
  if (obj.IsFieldEnabled(B2DialField::kSigmaUp))
    os << "Sigma up = " << obj.GetSigmaUp() << " " << obj.GetUnits() << "\n";
  if (obj.IsFieldEnabled(B2DialField::kSigmaDown))
    os << "Sigma down = " << obj.GetSigmaDown() << " " << obj.GetUnits() << "\n";
  if (obj.IsFieldEnabled(B2DialField::kBoundaryUp))
    os << "Boundary up = " << obj.GetBoundaryUp() << " " << obj.GetUnits() << "\n";
  if (obj.IsFieldEnabled(B2DialField::kBoundaryDown))
    os << "Boundary down = " << obj.GetBoundaryDown() << " " << obj.GetUnits() << "\n";
  if (obj.IsFieldEnabled(B2DialField::kDescription))
    os << "Description = " << obj.GetDescription() << "\n";
  return os;
}

bool B2Dial::operator==(const B2Dial &other) const {
  return GetEngineId() == other.GetEngineId() && GetDialId() == other.GetDialId();
}

void B2Dial::SetSigmaList(const B2SigmaList &sigma_list) {
  sigma_list_ = sigma_list;
}

const B2SigmaList &B2Dial::GetSigmaList() const {
  return sigma_list_;
}

std::size_t dial_hash_fn::operator()(const B2Dial &key) const {
  std::size_t h1 = std::hash<Int_t>()(key.GetEngineId());
  std::size_t h2 = std::hash<Int_t>()(key.GetDialId());
  return h1 ^ h2;
}

bool dial_key_equal_fn::operator()(const B2Dial &t1, const B2Dial &t2) const {
  return t1 == t2;
}

ClassImp(B2Dial)