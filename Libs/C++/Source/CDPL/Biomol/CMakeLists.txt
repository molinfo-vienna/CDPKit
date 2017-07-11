INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}" "${CDPL_SOURCE_DIR}")

SET(cdpl-biomol_LIB_SRCS
    PDBData.cpp
    ResidueDictionary.cpp
    ResidueList.cpp

    AtomProperty.cpp
    MolecularGraphProperty.cpp
    AtomPropertyDefault.cpp
    MolecularGraphPropertyDefault.cpp
    DataFormat.cpp
    ControlParameter.cpp
    ControlParameterDefault.cpp

    PDBDataReader.cpp
    PDBDataWriter.cpp
    PDBMoleculeReader.cpp
    PDBMolecularGraphWriter.cpp
    CDFDataReader.cpp
    CDFDataWriter.cpp

    HierarchyViewNode.cpp
    HierarchyViewModel.cpp
    HierarchyViewChain.cpp
    HierarchyView.cpp

    AtomPropertyFunctions.cpp
    MolecularGraphPropertyFunctions.cpp
    ControlParameterFunctions.cpp

    AtomUtilityFunctions.cpp
    AtomContainerUtilityFunctions.cpp
    MolecularGraphUtilityFunctions.cpp
   )

LINK_LIBRARIES(${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY})

ADD_LIBRARY(cdpl-biomol-static STATIC ${cdpl-biomol_LIB_SRCS})

SET_TARGET_PROPERTIES(cdpl-biomol-static PROPERTIES 
                      OUTPUT_NAME cdpl-biomol
                      CLEAN_DIRECT_OUTPUT 1
                      COMPILE_DEFINITIONS "CDPL_BIOMOL_STATIC_LINK;CDPL_CHEM_STATIC_LINK;CDPL_MATH_STATIC_LINK;CDPL_UTIL_STATIC_LINK;CDPL_BASE_STATIC_LINK"
                     )

TARGET_LINK_LIBRARIES(cdpl-biomol-static cdpl-chem-static cdpl-math-static cdpl-util-static cdpl-base-static cdpl-internal-static)

INSTALL(TARGETS cdpl-biomol-static
        DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLStaticLibraries
       )

ADD_LIBRARY(cdpl-biomol-shared SHARED ${cdpl-biomol_LIB_SRCS})

TARGET_LINK_LIBRARIES(cdpl-biomol-shared cdpl-chem-shared cdpl-base-shared cdpl-math-shared cdpl-util-shared cdpl-internal-static)

IF(APPLE)
  SET_TARGET_PROPERTIES(cdpl-biomol-shared PROPERTIES VERSION "${CDPL_SO_VERSION}"
                        FRAMEWORK TRUE
                        OUTPUT_NAME CDPL-Biomol
                        INSTALL_NAME_DIR "${CDPKIT_FRAMEWORK_INSTALL_NAME_DIR}"
                        LINK_FLAGS "-Wl,-rpath,\"${CDPKIT_FRAMEWORK_INSTALL_RPATH}\""
                       )
ELSE(APPLE)
  SET_TARGET_PROPERTIES(cdpl-biomol-shared PROPERTIES VERSION "${CDPL_VERSION}" SOVERSION "${CDPL_SO_VERSION}"
                        OUTPUT_NAME cdpl-biomol
                        CLEAN_DIRECT_OUTPUT 1
                        INSTALL_RPATH "${CDPKIT_LIBRARY_INSTALL_RPATH}"
                       )

  IF(UNIX)
    SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/libcdpl-biomol.so")
    CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
                   "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake"
                    @ONLY
                  )
    INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake")
  ENDIF(UNIX)
ENDIF(APPLE)

INSTALL(TARGETS cdpl-biomol-shared
        RUNTIME DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
        LIBRARY DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
        ARCHIVE DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLImportLibraries
        FRAMEWORK DESTINATION "${CDPKIT_FRAMEWORK_INSTALL_DIR}" COMPONENT CDPLFrameworks
       )

IF(Boost_UNIT_TEST_FRAMEWORK_FOUND)
  ADD_SUBDIRECTORY(Tests)
ENDIF(Boost_UNIT_TEST_FRAMEWORK_FOUND)
