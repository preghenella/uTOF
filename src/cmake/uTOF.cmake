################################################################################
# uTOF_GENERATE_LIBRARY
################################################################################

macro(uTOF_GENERATE_LIBRARY)

  ROOT_GENERATE_DICTIONARY(G__${CMAKE_PROJECT_NAME}${MODULE} ${HEADERS} LINKDEF ${MODULE}_LinkDef.h)
  add_library(${CMAKE_PROJECT_NAME}${MODULE} SHARED ${SOURCES} G__${CMAKE_PROJECT_NAME}${MODULE}.cxx)
  target_link_libraries(${CMAKE_PROJECT_NAME}${MODULE} ${ROOT_LIBRARIES} ${MODULE_DEPENDENCIES} Core)
  install(TARGETS ${CMAKE_PROJECT_NAME}${MODULE} LIBRARY DESTINATION lib)

  if (${ROOT_VERSION} VERSION_GREATER "6.0")
     install(FILES ${CMAKE_CURRENT_BINARY_DIR}/lib${CMAKE_PROJECT_NAME}${MODULE}_rdict.pcm ${CMAKE_CURRENT_BINARY_DIR}/lib${CMAKE_PROJECT_NAME}${MODULE}.rootmap DESTINATION lib)
  endif (${ROOT_VERSION} VERSION_GREATER "6.0")

  if(${CMAKE_SYSTEM} MATCHES Darwin)
     set_target_properties(${CMAKE_PROJECT_NAME}${MODULE} PROPERTIES LINK_FLAGS "-undefined dynamic_lookup")
  endif(${CMAKE_SYSTEM} MATCHES Darwin)

endmacro(uTOF_GENERATE_LIBRARY)

