//
// Created by Giorgio Pintaudi on 2021/12/08.
//

#ifndef WAGASCIREWEIGHT_B2DIAL_HPP
#define WAGASCIREWEIGHT_B2DIAL_HPP

// ROOT includes
#include <TNamed.h>
#include <TString.h>
#include <Rtypes.h>

// B2 includes
#include <B2Enum.hh>
#include <B2Dial.hh>
#include "B2SigmaList.hh"


struct WeightEventTestFixture;

namespace wgrw {
  class FileDialReader;
}

// Columns of the dial configuration file
enum B2DialField {
  kEngineId = 0,
  kDialId,
  kEngineName,
  kDialName,
  kType,
  kFromValue,
  kSigmaList,
  kSigmaUp,
  kSigmaDown,
  kBoundaryUp,
  kBoundaryDown,
  kUnits,
  kDescription,
  kNumDialFields,
};

// Types of dials
enum B2DialType {
  kRealNumber, // The dial is a continuos variable
  kInteger,    // The dial is an integer variable
  kBoolean,    // The dial is a boolean variable
};

// Human-readable names of the B2DialField enum
extern const std::unordered_map<B2DialField, std::string, EnumClassHash> DIAL_FIELD_NAMES;

// Human-readable names of the B2DialType enum
extern const std::unordered_map<B2DialType, std::string, EnumClassHash> DIAL_TYPE_NAMES;

///////////////////////////////////////////////////////////////////////////////////////

/**
 * Class containing the info about a single dial. The dial engine can be NEUT or NIWGReWeight.
 * Inside T2KReWeight a dial is identified by just the EngineID and DialID. The following info
 * is automatically read from the configuration file or from the input ROOT file.
 *   - Engine ID
 *   - Dial ID
 *   - Engine name
 *   - Dial name
 *   - Dial type
 *   - Dial nominal value
 *   - Sigma list
 *   - Dial sigma (right)
 *   - Dial sigma (left)
 *   - Dial upper limit
 *   - Dial lower limit
 *   - Dial units
 *   - Dial description
 */
class B2Dial : public TNamed {

  friend wgrw::FileDialReader;
  friend WeightEventTestFixture;

private:

  // Engine ID number
  Int_t engine_id_{};

  // B2Dial ID number
  Int_t dial_id_{};

  // Engine name
  TString engine_name_;

  // B2Dial name
  TString dial_name_;

  // Type of dial (real number, integer number, boolean, ...)
  Int_t type_{};

  // Nominal value
  Double_t from_value_{};

  // List of sigmas that are to be stored in splines
  B2SigmaList sigma_list_;

  // B2Dial value at 1 sigma up
  Double_t sigma_up_{};

  // B2Dial value at 1 sigma down
  Double_t sigma_down_{};

  // Upper boundary of dial value
  Double_t boundary_up_{};

  // Lower boundary of dial value
  Double_t boundary_down_{};

  // Units
  TString units_;

  // Description
  TString description_;

  // Enabled fields of dial
  UInt_t enabled_fields_{};

  // Enable a dial field
  void EnableField(B2DialField field);

  // Diable a dial field
  void DisableField(B2DialField field);

  // Enable all dial fields
  void EnableAllFields();

  // Disable all dial fields
  void DisableAllFields();

  void SetEngineName(const TString &engine_name);

  void SetDialName(const TString &dial_name);

  void SetType(B2DialType type);

  void SetFromValue(Double_t from_value);

  void SetSigmaUp(Double_t sigma_up);

  void SetSigmaDown(Double_t sigma_down);

  void SetBoundaryUp(Double_t boundary_up);

  void SetBoundaryDown(Double_t boundary_down);

  void SetUnits(const TString &units);

  void SetDescription(const TString &description);

  void SetSigmaList(const B2SigmaList &sigma_list);

public:

  // Default constructor (engine ID = -1 and dial ID = -1)
  B2Dial();

  /**
   * @param engine_id EngineID number (same as T2KReWeight)
   * @param dial_id DialID number (same as T2KReWeight)
   */
  B2Dial(Int_t engine_id, Int_t dial_id);

  // Engine ID number (same as T2KReWeight)
  Int_t GetEngineId() const;

  // B2Dial ID number (same as T2KReWeight)
  Int_t GetDialId() const;

  // Engine name
  const TString &GetEngineName() const;

  // B2Dial name
  const TString &GetDialName() const;

  // B2Dial type (real number, integer number, boolean)
  B2DialType GetType() const;

  // Nominal value
  Double_t GetFromValue() const;

  // B2Sigma up
  Double_t GetSigmaUp() const;

  // B2Sigma down
  Double_t GetSigmaDown() const;

  // Upper boundary
  Double_t GetBoundaryUp() const;

  // Lower boundary
  Double_t GetBoundaryDown() const;

  // B2Dial units
  const TString &GetUnits() const;

  // B2Dial description
  const TString &GetDescription() const;

  // List of sigmas that are to be stored in splines
  const B2SigmaList &GetSigmaList() const;

  // True if a field (a member) is enabled
  bool IsFieldEnabled(B2DialField field) const;

  // True if a field (a member) is disabled
  bool IsFieldDisabled(B2DialField field) const;

  // Compare only the EngineID and DialID
  bool operator==(const B2Dial &other) const;

  // Print the dial info to the stream
  friend std::ostream &operator<<(std::ostream &os, const B2Dial &obj);

ClassDef(B2Dial, 3)
};

std::ostream &operator<<(std::ostream &os, const B2Dial &obj);

// hash function using a B2Dial object as key
struct dial_hash_fn {
  std::size_t operator()(const B2Dial &key) const;
};

// function comparing two B2Dial objects
struct dial_key_equal_fn {
  bool operator()(const B2Dial &t1, const B2Dial &t2) const;
};


#endif //WAGASCIREWEIGHT_B2DIAL_HPP
