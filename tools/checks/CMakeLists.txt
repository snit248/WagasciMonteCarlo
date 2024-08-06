# check hits
add_executable(check_hits check_hits.cc)
target_link_libraries(check_hits ${ROOT_LIBRARIES} ${Boost_LIBRARIES} libB2MC)

# check clusters
add_executable(check_clusters check_clusters.cc)
target_link_libraries(check_clusters ${ROOT_LIBRARIES} ${Boost_LIBRARIES} libB2MC)

install(TARGETS check_clusters DESTINATION "${CMAKE_INSTALL_BINDIR}")
