# draw BabyMIND magnetic field using ROOT
add_executable(draw_field draw_field.cc)
target_link_libraries(draw_field ${ROOT_LIBRARIES})

# check the amount of hits in each sub-detector
add_executable(detector_id detector_id.cc)
target_link_libraries(detector_id ${ROOT_LIBRARIES} ${Boost_LIBRARIES} libB2MC)

install(TARGETS detector_id draw_field DESTINATION "${CMAKE_INSTALL_BINDIR}")
