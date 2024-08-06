#include <boost/log/trivial.hpp>
#include <B2Boundary.hh>

B2Boundary::B2Boundary() = default;

Bool_t B2Boundary::CheckBoundaryCondition(Double_t value) {
  return true;
}

Bool_t B2Boundary::CheckBoundaryCondition(std::vector<Double_t> value) {
  return true;
}

ClassImp(B2Boundary)

////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
B2SingleBoundary<T>::B2SingleBoundary(T bound) : boundarycondition_(bound) {
  BOOST_LOG_TRIVIAL(info) << "bound = " << bound << " is set.";
}

template<typename T>
Bool_t B2SingleBoundary<T>::CheckBoundaryCondition(Double_t value) {
  return boundarycondition_ >= value;
}

template<typename T>
Bool_t B2SingleBoundary<T>::CheckBoundaryCondition(std::vector<Double_t> value) {
  Bool_t boundarycheck = true;
  for(auto& val : value){
    boundarycheck *= ( boundarycondition_ >= val );
  }
  return boundarycheck;
}

templateClassImp(B2SingleBoundary)

template
class B2SingleBoundary<Int_t>;

template
class B2SingleBoundary<Double_t>;

////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
B2DoubleBoundary<T>::B2DoubleBoundary(T &bound) {
  for (const auto &el: bound) {
    boundarycondition_.push_back(el);
  }
  BOOST_LOG_TRIVIAL(info) << "bound = (low, high) =  (" << boundarycondition_.at(0) << ", " << boundarycondition_.at(1)
                          << ") is set.";
}

template<typename T>
Bool_t B2DoubleBoundary<T>::CheckBoundaryCondition(Double_t value) {
  return boundarycondition_.at(0) <= value && value <= boundarycondition_.at(1);
}

template<typename T>
Bool_t B2DoubleBoundary<T>::CheckBoundaryCondition(std::vector<Double_t> value) {
  Int_t boundarycheck = 1;
  for(auto& val : value){
    boundarycheck *= static_cast<int>( boundarycondition_.at(0) <= val && val <= boundarycondition_.at(1) );
  }

  return static_cast<bool>(boundarycheck);
}

templateClassImp(B2DoubleBoundary)

template
class B2DoubleBoundary<std::vector<int>>;

template
class B2DoubleBoundary<std::vector<double>>;

////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
B2PointLikeBoundary<T>::B2PointLikeBoundary(T &bound) {
  for (const auto &el: bound) {
    boundarycondition_.push_back(el);
    BOOST_LOG_TRIVIAL(info) << "Point " << el << " is set.";
  }
}

template<typename T>
Bool_t B2PointLikeBoundary<T>::CheckBoundaryCondition(Double_t value) {
  if(boundarycondition_.size() == 1){
    if(boundarycondition_.at(0) == -64){ // 64 does mean "ignore this value".
      return true;
    }else {
      return std::find(boundarycondition_.begin(), boundarycondition_.end(), (Int_t) value) != boundarycondition_.end();
    }
  } else {
    return std::find(boundarycondition_.begin(), boundarycondition_.end(), (Int_t) value) != boundarycondition_.end();
  }
}

template<typename T>
Bool_t B2PointLikeBoundary<T>::CheckBoundaryCondition(std::vector<Double_t> value) {
  Bool_t boundarycheck = true;
  if(boundarycondition_.size() == 1){
    if(boundarycondition_.at(0) == -64){ // 64 does mean "ignore this value".
      return true;
    }else {
      for(auto& val : value){
	boundarycheck 
	  *= ( std::find(boundarycondition_.begin(), boundarycondition_.end(), (Int_t) val) != boundarycondition_.end() );
      }
    }
  } else {
    for(auto& val : value){
      boundarycheck 
	*= ( std::find(boundarycondition_.begin(), boundarycondition_.end(), (Int_t) val) != boundarycondition_.end() );
    }
  }

  return boundarycheck;
}


templateClassImp(B2PointLikeBoundary)

template
class B2PointLikeBoundary<std::vector<int>>;

template
class B2PointLikeBoundary<std::vector<double>>;

////////////////////////////////////////////////////////////////////////////////////////////////

B2DoubleBoundarySet::B2DoubleBoundarySet(std::vector<B2DoubleBoundary<std::vector<double>>> bounds, const std::string logic) {
  logic_ = logic;

  for (auto &el: bounds) {
    boundarycondition_.push_back(el);
  }

  BOOST_LOG_TRIVIAL(info) << "Logic = " << logic_;

}

Bool_t B2DoubleBoundarySet::CheckBoundaryCondition(std::vector<double> value) {
  Bool_t boundarycheck = true;
  
  if(value.size() != boundarycondition_.size()){
    BOOST_LOG_TRIVIAL(info) << value.size() << " " << boundarycondition_.size();
    throw std::invalid_argument("the value size is not consistent with boundary size");
    return 0;
  }

  if(logic_ == "Or"){
    boundarycheck = false;
    for(size_t i=0; i<value.size(); i++){
      //if boundarycheck >= 1, then it would be True 
      boundarycheck += boundarycondition_.at(i).CheckBoundaryCondition(value.at(i));
    }
  }if(logic_ == "Once"){
    Int_t npass=0;
    for(size_t i=0; i<value.size(); i++){
      //if boundarycheck == 1, then it would be True
      if(boundarycondition_.at(i).CheckBoundaryCondition(value.at(i)))
	npass ++;
    }
    
    if(npass == 1)
      boundarycheck = true;
    else
      boundarycheck = false;
    
  }else{
    for(size_t i=0; i<value.size(); i++){
      boundarycheck *= boundarycondition_.at(i).CheckBoundaryCondition(value.at(i));
    }
  }

  return boundarycheck;
}

ClassImp(B2DoubleBoundarySet)

////////////////////////////////////////////////////////////////////////////////////////////////
