INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}" "${CDPL_SOURCE_DIR}")

SET(cdpl-confgen_LIB_SRCS
    DGConstraintGenerator.cpp
    Raw3DCoordinatesGenerator.cpp
    FragmentList.cpp
    FragmentLibraryEntry.cpp
    FragmentLibrary.cpp
    CDFFragmentLibraryDataReader.cpp
    CDFFragmentLibraryDataWriter.cpp
    CDFMoleculeDataFunctions.cpp
    UtilityFunctions.cpp
   )

IF(Boost_TIMER_FOUND AND Boost_CHRONO_FOUND)
   SET(cdpl-confgen_LIB_SRCS
       ${cdpl-confgen_LIB_SRCS}
       RandomConformerGenerator.cpp
       FragmentConformerGenerator.cpp
       FragmentLibraryGenerator.cpp
      )	  

   LINK_LIBRARIES(${Boost_TIMER_LIBRARY} ${Boost_CHRONO_LIBRARY})	
ENDIF(Boost_TIMER_FOUND AND Boost_CHRONO_FOUND)

ADD_LIBRARY(cdpl-confgen-static STATIC ${cdpl-confgen_LIB_SRCS})

SET_TARGET_PROPERTIES(cdpl-confgen-static PROPERTIES 
                      OUTPUT_NAME cdpl-confgen
                      CLEAN_DIRECT_OUTPUT 1
                      COMPILE_DEFINITIONS "CDPL_CONFGEN_STATIC_LINK;CDPL_BASE_STATIC_LINK;CDPL_CHEM_STATIC_LINK;CDPL_MATH_STATIC_LINK;CDPL_UTIL_STATIC_LINK;CDPL_FORCEFIELD_STATIC_LINK"
                     )

TARGET_LINK_LIBRARIES(cdpl-confgen-static cdpl-base-static cdpl-chem-static cdpl-math-static cdpl-util-static cdpl-forcefield-static cdpl-internal-static)

INSTALL(TARGETS cdpl-confgen-static
        DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLStaticLibraries
       )

ADD_LIBRARY(cdpl-confgen-shared SHARED ${cdpl-confgen_LIB_SRCS})

TARGET_LINK_LIBRARIES(cdpl-confgen-shared cdpl-base-shared cdpl-chem-shared cdpl-math-shared cdpl-util-shared cdpl-forcefield-shared cdpl-internal-static)

IF(APPLE)
  SET_TARGET_PROPERTIES(cdpl-confgen-shared PROPERTIES VERSION "${CDPL_SO_VERSION}"
                        FRAMEWORK TRUE
                        OUTPUT_NAME CDPL-ConfGen
                        INSTALL_NAME_DIR "${CDPKIT_FRAMEWORK_INSTALL_NAME_DIR}"
                        LINK_FLAGS "-Wl,-rpath,\"${CDPKIT_FRAMEWORK_INSTALL_RPATH}\""
                       )
ELSE(APPLE)
  SET_TARGET_PROPERTIES(cdpl-confgen-shared PROPERTIES VERSION "${CDPL_VERSION}" SOVERSION "${CDPL_SO_VERSION}"
                        OUTPUT_NAME cdpl-confgen
                        CLEAN_DIRECT_OUTPUT 1
                        INSTALL_RPATH "${CDPKIT_LIBRARY_INSTALL_RPATH}"
                       )

  IF(UNIX)
    SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/libcdpl-confgen.so")
    CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
                   "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" 
                   @ONLY
                  )
    INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake")
  ENDIF(UNIX)
ENDIF(APPLE)

INSTALL(TARGETS cdpl-confgen-shared
        RUNTIME DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
        LIBRARY DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
        ARCHIVE DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLImportLibraries
        FRAMEWORK DESTINATION "${CDPKIT_FRAMEWORK_INSTALL_DIR}" COMPONENT CDPLFrameworks
       )

IF(Boost_UNIT_TEST_FRAMEWORK_FOUND AND CMAKE_BUILD_TYPE EQUAL "DEBUG")
  ADD_SUBDIRECTORY(Tests)
ENDIF(Boost_UNIT_TEST_FRAMEWORK_FOUND AND CMAKE_BUILD_TYPE EQUAL "DEBUG")
