add_executable(B2MC
        B2MC.cc
        B2DetectorConstruction.cc
        B2EventAction.cc
        B2ScintillatorHit.cc
        B2HorizontalSensitiveDetector.cc
        B2PrimaryGeneratorAction.cc
        B2Response.cc
        B2RunAction.cc
        B2TrackingAction.cc
        B2VerticalSensitiveDetector.cc
        B2Neut.cc
        B2Converters.cc
        B2RandomVertexZ.cc
        B2CosmicMuon.cc
        B2SensitiveDetector.cc
        B2VetoSensitiveDetector.cc
        B2Configuration.cc
        B2Settings.cc
        B2Logging.cc
        B2EmulsionHit.cc
        B2EmulsionSensitiveDetector.cc
        B2MichelElectron.cc
        B2MagneticFieldWrapper.cc)

target_link_libraries(B2MC
        ${ROOT_LIBRARIES}
        ${Geant4_LIBRARIES}
        ${Boost_LIBRARIES}
        libB2MC)

# install the library in the lib folder
install(TARGETS B2MC DESTINATION "${CMAKE_INSTALL_BINDIR}")