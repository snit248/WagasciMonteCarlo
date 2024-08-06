if (BUILD_EXAMPLES)
    add_executable(sample_reader sample_reader.cc)
    target_link_libraries(sample_reader ${ROOT_LIBRARIES} ${Boost_LIBRARIES} libB2MC)
    install(TARGETS sample_reader DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")

    add_executable(sample_muon sample_muon.cc)
    target_link_libraries(sample_muon ${ROOT_LIBRARIES} ${Boost_LIBRARIES} libB2MC)
    install(TARGETS sample_muon DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")

    add_executable(sample_clone sample_clone.cc)
    target_link_libraries(sample_clone ${ROOT_LIBRARIES} ${Boost_LIBRARIES} libB2MC)
    install(TARGETS sample_clone DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")

    add_executable(sample_print sample_print.cc)
    target_link_libraries(sample_print ${ROOT_LIBRARIES} ${Boost_LIBRARIES} libB2MC)
    install(TARGETS sample_print DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")

    add_executable(sample_true sample_true.cc)
    target_link_libraries(sample_true ${ROOT_LIBRARIES} ${Boost_LIBRARIES} libB2MC)
    install(TARGETS sample_true DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")

    add_executable(sample_recon sample_recon.cc)
    target_link_libraries(sample_recon ${ROOT_LIBRARIES} ${Boost_LIBRARIES} libB2MC)
    install(TARGETS sample_recon DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")

    add_executable(sample_writer sample_writer.cc)
    target_link_libraries(sample_writer ${ROOT_LIBRARIES} ${Boost_LIBRARIES} libB2MC)
    install(TARGETS sample_writer DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")

    message(STATUS "Building examples -- done")

endif ()

    add_executable(fitter_tree fitter_tree.cc)
    target_link_libraries(fitter_tree ${ROOT_LIBRARIES} ${Boost_LIBRARIES} libB2MC)
    install(TARGETS fitter_tree DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")

    add_executable(sample_CC0pi sample_CC0pi.cc)
    target_link_libraries(sample_CC0pi ${ROOT_LIBRARIES} ${Boost_LIBRARIES} libB2MC)
    install(TARGETS sample_CC0pi DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")

