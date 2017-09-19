find_package(Boost REQUIRED COMPONENTS program_options)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(uTOFwriter writer.cxx)
target_link_libraries(uTOFwriter ${Boost_PROGRAM_OPTIONS_LIBRARY} uTOFdataFormat)

add_executable(uTOFstripWriter stripWriter.cxx)
target_link_libraries(uTOFstripWriter ${Boost_PROGRAM_OPTIONS_LIBRARY} uTOFdataFormat)
		      
add_executable(uTOFcalib stripCalib.cxx)
target_link_libraries(uTOFcalib ${Boost_PROGRAM_OPTIONS_LIBRARY} uTOFdataFormat uTOFcalibration)
		      
install(TARGETS uTOFwriter RUNTIME DESTINATION bin)
install(TARGETS uTOFstripWriter RUNTIME DESTINATION bin)
install(TARGETS uTOFcalib RUNTIME DESTINATION bin)

