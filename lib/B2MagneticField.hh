// system includes
#include <string>
#include <TVector3.h>
#include <B2Const.hh>
class B2MagneticField {

public:

  explicit B2MagneticField(const std::string& magfield_table_file_path);

  TVector3 GetFieldValue(const TVector3 &point) const;

private:

  const static std::size_t xbins_ = 251;
  const static std::size_t ybins_ = 201;

  double bx_[xbins_][ybins_]{}, by_[xbins_][ybins_]{}, bz_[xbins_][ybins_]{};
  double xmin_, xmax_, ymin_, ymax_, zmin_, zmax_;
};
