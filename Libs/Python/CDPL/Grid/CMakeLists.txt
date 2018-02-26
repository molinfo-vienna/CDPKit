INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

FILE(GLOB PYTHON_FILES "*.py")

FOREACH(PYTHON_FILE ${PYTHON_FILES})
  EXECUTE_PROCESS(COMMAND "${CMAKE_COMMAND}" -E copy "${PYTHON_FILE}" "${CMAKE_CURRENT_BINARY_DIR}"
                  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
ENDFOREACH(PYTHON_FILE)

SET(grid_MOD_SRCS
    Module.cpp
    AttributedGridExport.cpp
    SpatialGridExport.cpp
    RegularGridExport.cpp
    RegularGridSetExport.cpp

    AttributedGridPropertyExport.cpp 
    AttributedGridPropertyDefaultExport.cpp 
    ControlParameterExport.cpp 
    ControlParameterDefaultExport.cpp 
    DataFormatExport.cpp 

    RegularGridInputHandlerExport.cpp
    RegularGridOutputHandlerExport.cpp
    RegularGridSetInputHandlerExport.cpp
    RegularGridSetOutputHandlerExport.cpp

    RegularGridIOManagerExport.cpp
    RegularGridSetIOManagerExport.cpp

    RegularGridReaderExport.cpp
    RegularGridWriterExport.cpp
    RegularGridSetReaderExport.cpp
    RegularGridSetWriterExport.cpp

    CDFRegularGridInputHandlerExport.cpp
    CDFRegularGridOutputHandlerExport.cpp
    CDFRegularGridSetInputHandlerExport.cpp
    CDFRegularGridSetOutputHandlerExport.cpp

    CDFRegularGridReaderExport.cpp
    CDFRegularGridWriterExport.cpp
    CDFRegularGridSetReaderExport.cpp
    CDFRegularGridSetWriterExport.cpp

    AttributedGridFunctionExport.cpp 
    ControlParameterFunctionExport.cpp 

    ToPythonConverterRegistration.cpp
    FromPythonConverterRegistration.cpp
   )

ADD_LIBRARY(_grid MODULE ${grid_MOD_SRCS})

TARGET_LINK_LIBRARIES(_grid cdpl-grid-shared ${Boost_PYTHON_LIBRARY} ${PYTHON_LIBRARIES})

SET_TARGET_PROPERTIES(_grid PROPERTIES PREFIX "")

IF(WIN32)
  SET_TARGET_PROPERTIES(_grid PROPERTIES SUFFIX ".pyd")
ELSE(WIN32)
  SET_TARGET_PROPERTIES(_grid PROPERTIES COMPILE_DEFINITIONS "BOOST_PYTHON_USE_GCC_SYMBOL_VISIBILITY")

  IF(NOT APPLE)
    SET_TARGET_PROPERTIES(_grid PROPERTIES INSTALL_RPATH "${CDPKIT_PYTHON_MODULE_INSTALL_RPATH2}")

    SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/_grid.so")
    CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
                   "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" 
                   @ONLY
                  )
    INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake")
  ELSE(NOT APPLE)
    SET_TARGET_PROPERTIES(_grid PROPERTIES LINK_FLAGS "-Wl,-rpath,\"${CDPKIT_PYTHON_MODULE_INSTALL_RPATH2}\"")
  ENDIF(NOT APPLE)
ENDIF(WIN32)

INSTALL(FILES ${PYTHON_FILES} DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Grid" COMPONENT CDPLPythonModules)
INSTALL(TARGETS _grid DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Grid" COMPONENT CDPLPythonModules)

IF(PYTHONINTERP_FOUND)
  ADD_SUBDIRECTORY(Tests)
ENDIF(PYTHONINTERP_FOUND)
