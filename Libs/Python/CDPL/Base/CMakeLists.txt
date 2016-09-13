INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

FILE(GLOB PYTHON_FILES "*.py")

FOREACH(PYTHON_FILE ${PYTHON_FILES})
  EXECUTE_PROCESS(COMMAND "${CMAKE_COMMAND}" -E copy "${PYTHON_FILE}" "${CMAKE_CURRENT_BINARY_DIR}"
                  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
ENDFOREACH(PYTHON_FILE)

SET(base_MOD_SRCS
    Module.cpp
    PropertyContainerExport.cpp
    LookupKeyExport.cpp
    ControlParameterContainerExport.cpp
    ControlParameterListExport.cpp
    DataFormatExport.cpp
    DataIOBaseExport.cpp
    IOStreamExport.cpp
    ToPythonConverterRegistration.cpp
    FromPythonConverterRegistration.cpp
    ExceptionTranslatorRegistration.cpp
   )

ADD_LIBRARY(_base MODULE ${base_MOD_SRCS})

TARGET_LINK_LIBRARIES(_base cdpl-base-shared ${Boost_PYTHON_LIBRARY} ${PYTHON_LIBRARIES})

SET_TARGET_PROPERTIES(_base PROPERTIES PREFIX "")

IF(WIN32)
  SET_TARGET_PROPERTIES(_base PROPERTIES SUFFIX ".pyd")
ELSE(WIN32)
  IF(NOT APPLE)
    SET_TARGET_PROPERTIES(_base PROPERTIES INSTALL_RPATH "${CDPKIT_PYTHON_MODULE_INSTALL_RPATH2}")

    SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/_base.so")
    CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
                   "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" 
                   @ONLY
                  )
    INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake")
  ELSE(NOT APPLE)
    SET_TARGET_PROPERTIES(_base PROPERTIES LINK_FLAGS "-Wl,-rpath,\"${CDPKIT_PYTHON_MODULE_INSTALL_RPATH2}\"")
  ENDIF(NOT APPLE)
ENDIF(WIN32)

INSTALL(FILES ${PYTHON_FILES} DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Base" COMPONENT CDPLPythonModules)
INSTALL(TARGETS _base DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Base" COMPONENT CDPLPythonModules)

IF(PYTHONINTERP_FOUND)
  ADD_SUBDIRECTORY(Tests)
ENDIF(PYTHONINTERP_FOUND)
