set(DICTIONARY_HEADERS
        B2HitSummary.hh
        B2ClusterSummary.hh
        B2TrackSummary.hh
        B2VertexSummary.hh
        B2BeamSummary.hh
        B2Measurement.hh
        B2EventSummary.hh
        B2SpillSummary.hh
        B2EmulsionSummary.hh
        B2HitsSet.hh
        B2Pdg.hh
		B2RefArray.hh
		B2Boundary.hh
		B2Sigma.hh
		B2Dial.hh
		B2DialList.hh
		B2SigmaList.hh
        )

set(B2MC_LIBRARY_HEADERS
        B2Enum.hh
        B2Const.hh
        B2HitSummary.hh
        B2ClusterSummary.hh
        B2TrackSummary.hh
        B2VertexSummary.hh
        B2EventSummary.hh
        B2BeamSummary.hh
        B2Measurement.hh
        B2SpillSummary.hh
        B2EmulsionSummary.hh
        B2HitsSet.hh
		IB2Reader.hh
        B2Reader.hh
        B2Writer.hh
        B2Pdg.hh
        B2Dimension.hh
        B2Volume.hh
        B2MagneticField.hh
		B2RefArray.hh
		B2Boundary.hh
		B2Sigma.hh
		B2Dial.hh
		B2DialSigmaKey.hh
		B2DialList.hh
		B2SigmaList.hh
		B2ReaderDecorator.hh
		B2McWeightCalculator.hh
        )

set(B2MC_LIBRARY_SOURCES
        B2Enum.cc
        B2HitSummary.cc
        B2ClusterSummary.cc
        B2TrackSummary.cc
        B2VertexSummary.cc
        B2EventSummary.cc
        B2BeamSummary.cc
        B2Measurement.cc
        B2SpillSummary.cc
        B2EmulsionSummary.cc
        B2HitsSet.cc
        B2Reader.cc
        B2Writer.cc
        B2Pdg.cc
        B2Dimension.cc
        B2Volume.cc
        B2MagneticField.cc
		B2RefArray.cc
		B2Boundary.cc
		B2Sigma.cc
		B2Dial.cc
		B2DialSigmaKey.cc
		B2DialList.cc
		B2SigmaList.cc
		B2ReaderDecorator.cc
		B2McWeightCalculator.cc
        )

# Generate ROOT dictionary
root_generate_dictionary(G__B2MCDict ${DICTIONARY_HEADERS} LINKDEF B2MCLinkDef.h)

# libB2MC.so shared library
add_library(libB2MC SHARED ${B2MC_LIBRARY_HEADERS} ${B2MC_LIBRARY_SOURCES} G__B2MCDict.cxx)

# rename liblibB2MC into libB2MC
set_target_properties(libB2MC PROPERTIES OUTPUT_NAME B2MC)

# include the current directory
target_include_directories(libB2MC PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# Link with ...
target_link_libraries(libB2MC PUBLIC
        ${ROOT_LIBRARIES}
        ${Boost_LIBRARIES})

# list all target headers
set_target_properties(libB2MC PROPERTIES PUBLIC_HEADER "${B2MC_LIBRARY_HEADERS}")

# install the library in the lib folder
set_target_properties(libB2MC PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION ${PROJECT_VERSION_MAJOR})
install(TARGETS libB2MC
        LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
        PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCDIR}")

# install the ROOT dictionary in the lib folder
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libB2MCDict_rdict.pcm DESTINATION "${CMAKE_INSTALL_LIBDIR}")
