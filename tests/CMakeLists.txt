if (BUILD_TESTS)

    include(CTest)

    foreach (SOURCE
            B2DetectorConstruction.cc
            B2EmulsionSensitiveDetector.cc
            B2EmulsionHit.cc
#            B2EventAction.cc
            B2MichelElectron.cc
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
            B2Logging.cc)
        list(APPEND SOURCES ../src/${SOURCE})
    endforeach ()

    add_library(libTMP STATIC ${SOURCES})
    target_link_libraries(libTMP ${ROOT_LIBRARIES}
            ${Geant4_LIBRARIES}
            ${Boost_LIBRARIES}
            libB2MC)
    set_target_properties(libTMP PROPERTIES OUTPUT_NAME TMP)

    foreach (TEST
            B2Neut
            B2PrimaryParticles
            B2Dimension
            B2RandomVertexZ
            B2CosmicMuon
            B2Measurement
            B2ClusterSummary
            B2TrackSummary
            B2VertexSummary
            B2SpillSummary
#            B2EventAction
            B2HitSummary
            B2HitsSet
            B2Logging
            B2Settings
            B2Configuration
            B2Volume
            B2Writer
            B2Clone
            B2Response
            )
        include_directories("${gtest_SOURCE_DIR}/include")
        add_executable(${TEST}_test ${TEST}.test.cc)

        target_link_libraries(${TEST}_test
                gtest
                gmock
                gtest_main
                libTMP)
        install(TARGETS ${TEST}_test DESTINATION "${CMAKE_INSTALL_BINDIR}")
    endforeach ()

    add_test(TestB2Neut B2Neut_test "${CMAKE_SOURCE_DIR}/data/sample_neutfile/13a_nd7_posi250_numu_h2o_1.root")

    message(STATUS "Building unit tests -- done")

endif ()