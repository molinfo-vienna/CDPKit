INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

FILE(GLOB PYTHON_FILES "*.py")

FOREACH(PYTHON_FILE ${PYTHON_FILES})
  EXECUTE_PROCESS(COMMAND "${CMAKE_COMMAND}" -E copy "${PYTHON_FILE}" "${CMAKE_CURRENT_BINARY_DIR}"
                  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
ENDFOREACH(PYTHON_FILE)

SET(biomol_MOD_SRCS
    Module.cpp

    PDBDataExport.cpp
 
    PDBMoleculeReaderExport.cpp
    PDBMolecularGraphWriterExport.cpp
    PDBMoleculeInputHandlerExport.cpp
    PDBMolecularGraphOutputHandlerExport.cpp

    AtomPropertyExport.cpp
    MolecularGraphPropertyExport.cpp
    AtomPropertyFlagExport.cpp
    ResidueTypeExport.cpp
    DataFormatExport.cpp

    AtomFunctionExport.cpp
    MolecularGraphFunctionExport.cpp
    ResidueFunctionExport.cpp

    ToPythonConverterRegistration.cpp
    FromPythonConverterRegistration.cpp
   )

ADD_LIBRARY(_biomol MODULE ${biomol_MOD_SRCS})

TARGET_LINK_LIBRARIES(_biomol cdpl-biomol-shared ${Boost_PYTHON_LIBRARY} ${PYTHON_LIBRARIES})

SET_TARGET_PROPERTIES(_biomol PROPERTIES PREFIX "")

IF(WIN32)
  SET_TARGET_PROPERTIES(_biomol PROPERTIES SUFFIX ".pyd")
ELSE(WIN32)
  IF(NOT APPLE)
    SET_TARGET_PROPERTIES(_biomol PROPERTIES INSTALL_RPATH "${CDPKIT_PYTHON_MODULE_INSTALL_RPATH2}")

    SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/_biomol.so")
    CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
                   "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" 
                   @ONLY
                  )
    INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake")
  ELSE(NOT APPLE)
    SET_TARGET_PROPERTIES(_biomol PROPERTIES LINK_FLAGS "-Wl,-rpath,\"${CDPKIT_PYTHON_MODULE_INSTALL_RPATH2}\"")
  ENDIF(NOT APPLE)
ENDIF(WIN32)

INSTALL(FILES ${PYTHON_FILES} DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Biomol" COMPONENT CDPLPythonModules)
INSTALL(TARGETS _biomol DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Biomol" COMPONENT CDPLPythonModules)

IF(PYTHONINTERP_FOUND)
  ADD_SUBDIRECTORY(Tests)
ENDIF(PYTHONINTERP_FOUND)
