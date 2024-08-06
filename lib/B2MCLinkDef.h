#ifdef __ROOTCLING__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;
#pragma link off all typedef;

#pragma link C++ class B2Measurement1D+;
#pragma link C++ class B2Measurement2D+;
#pragma link C++ class B2Measurement3D+;
#pragma link C++ class B2Energy+;
#pragma link C++ class B2Momentum+;
#pragma link C++ class B2Time+;
#pragma link C++ class B2Distance+;
#pragma link C++ class B2Position+;
#pragma link C++ class B2Direction+;
#pragma link C++ class B2Angle+;
#pragma link C++ class B2ViewAngle+;
#pragma link C++ class B2Vector3+;
#pragma link C++ class B2VectorDoubleReadout<Int_t>+;
#pragma link C++ class B2VectorDoubleReadout<Double_t>+;
#pragma link C++ class B2VectorDoubleReadout<B2Vector3>+;
#pragma link C++ typedef B2DoubleReadoutD+;
#pragma link C++ typedef B2DoubleReadoutI+;
#pragma link C++ typedef B2DoubleReadout3+;

#pragma link C++ class B2EventSummary+;
#pragma link C++ class B2HitSummary+;
#pragma link C++ class B2BeamSummary+;
#pragma link C++ class B2HitsSet+;
#pragma link C++ class B2ClusterSummary+;
#pragma link C++ class B2TrackSummary+;
#pragma link C++ class B2VertexSummary+;
#pragma link C++ class B2EmulsionSummary+;
#pragma link C++ class B2SpillSummary+;
#pragma link C++ class B2RefArray+;

#pragma link C++ class B2Boundary+;
#pragma link C++ class B2SingleBoundary<int>+;
#pragma link C++ class B2SingleBoundary<double>+;
#pragma link C++ class B2DoubleBoundary<std::vector<int>>+;
#pragma link C++ class B2DoubleBoundary<std::vector<double>>+;
#pragma link C++ class B2PointLikeBoundary<std::vector<int>>+;
#pragma link C++ class B2PointLikeBoundary<std::vector<double>>+;
#pragma link C++ class B2DoubleBoundarySet+;

#pragma link C++ enum B2Sigma+;
#pragma link C++ class std::set<B2Sigma>+;
#pragma link C++ class std::set<B2Sigma>::iterator+;
#pragma link C++ class std::set<B2Sigma>::const_iterator+;
#pragma link C++ function operator != ( std::set<B2Sigma>::const_iterator, std::set<B2Sigma>::const_iterator);
#pragma link C++ function operator != ( std::set<B2Sigma>::iterator, std::set<B2Sigma>::iterator);
#pragma link C++ class B2SigmaList+;

#pragma link C++ class B2Dial+;
#pragma link C++ class std::vector<B2Dial>+;
#pragma link C++ class std::vector<B2Dial>::iterator+;
#pragma link C++ class std::vector<B2Dial>::const_iterator+;
#pragma link C++ function operator != ( std::vector<B2Dial>::const_iterator, std::vector<B2Dial>::const_iterator);
#pragma link C++ function operator != ( std::vector<B2Dial>::iterator, std::vector<B2Dial>::iterator);
#pragma link C++ class B2DialList+;

#endif
