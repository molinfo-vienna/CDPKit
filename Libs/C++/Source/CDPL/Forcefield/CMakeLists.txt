INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

SET(cdpl-forcefield_LIB_SRCS
    MerckMolecularForcefield.cpp
   )

LINK_LIBRARIES(${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY})

IF(Boost_ATOMIC_FOUND)
  LINK_LIBRARIES(${Boost_ATOMIC_LIBRARY})
ENDIF(Boost_ATOMIC_FOUND)

ADD_LIBRARY(cdpl-forcefield-static STATIC ${cdpl-forcefield_LIB_SRCS})

SET_TARGET_PROPERTIES(cdpl-forcefield-static PROPERTIES 
                      OUTPUT_NAME cdpl-forcefield
                      CLEAN_DIRECT_OUTPUT 1
                      COMPILE_DEFINITIONS CDPL_FORCEFIELD_STATIC_LINK
                     )

INSTALL(TARGETS cdpl-forcefield-static
        DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLStaticLibraries
       )

ADD_LIBRARY(cdpl-forcefield-shared SHARED ${cdpl-forcefield_LIB_SRCS})

IF(APPLE)
  SET_TARGET_PROPERTIES(cdpl-forcefield-shared PROPERTIES VERSION "${CDPL_SO_VERSION}"
                        FRAMEWORK TRUE
                        OUTPUT_NAME CDPL-Forcefield
                        INSTALL_NAME_DIR "${CDPKIT_FRAMEWORK_INSTALL_NAME_DIR}"
                        LINK_FLAGS "-Wl,-rpath,\"${CDPKIT_FRAMEWORK_INSTALL_RPATH}\""
                       )
ELSE(APPLE)
  SET_TARGET_PROPERTIES(cdpl-forcefield-shared PROPERTIES VERSION "${CDPL_VERSION}" SOVERSION "${CDPL_SO_VERSION}"
                        OUTPUT_NAME cdpl-forcefield
                        CLEAN_DIRECT_OUTPUT 1
                        INSTALL_RPATH "${CDPKIT_LIBRARY_INSTALL_RPATH}"
                       )

  IF(UNIX)
    SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/libcdpl-forcefield.so")
    CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
                   "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" 
                   @ONLY
                  )
    INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake")
  ENDIF(UNIX)
ENDIF(APPLE)

INSTALL(TARGETS cdpl-forcefield-shared
        RUNTIME DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
        LIBRARY DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
        ARCHIVE DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLImportLibraries
        FRAMEWORK DESTINATION "${CDPKIT_FRAMEWORK_INSTALL_DIR}" COMPONENT CDPLFrameworks
       )

IF(Boost_UNIT_TEST_FRAMEWORK_FOUND)
  ADD_SUBDIRECTORY(Tests)
ENDIF(Boost_UNIT_TEST_FRAMEWORK_FOUND)
