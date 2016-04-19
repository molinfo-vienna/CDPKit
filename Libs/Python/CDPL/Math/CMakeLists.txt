INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

FILE(GLOB PYTHON_FILES "*.py")

FOREACH(PYTHON_FILE ${PYTHON_FILES})
  EXECUTE_PROCESS(COMMAND "${CMAKE_COMMAND}" -E copy "${PYTHON_FILE}" "${CMAKE_CURRENT_BINARY_DIR}"
                  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
ENDFOREACH(PYTHON_FILE)

SET(math_MOD_SRCS
    Module.cpp
    VectorExpressionExport.cpp
    MatrixExpressionExport.cpp
    QuaternionExpressionExport.cpp
    VectorExport.cpp
    MatrixExport.cpp
    QuaternionExport.cpp
    RangeExport.cpp
    SliceExport.cpp
    VectorProxyExport.cpp
    MatrixProxyExport.cpp
    VectorAdapterExport.cpp
    MatrixAdapterExport.cpp
    QuaternionAdapterExport.cpp
    VectorFunctionExport.cpp
    MatrixFunctionExport.cpp
    SpecialFunctionExport.cpp
    QuaternionFunctionExport.cpp
    VectorArrayExport.cpp
    VectorArrayFunctionExport.cpp
    MLRModelExport.cpp
    BFGSMinimizerExport.cpp
    KabschAlgorithmExport.cpp
    ToPythonConverterRegistration.cpp
    FromPythonConverterRegistration.cpp
   )

ADD_LIBRARY(_math MODULE ${math_MOD_SRCS})

TARGET_LINK_LIBRARIES(_math cdpl-math-shared ${Boost_PYTHON_LIBRARY} ${PYTHON_LIBRARIES})

SET_TARGET_PROPERTIES(_math PROPERTIES PREFIX "")


IF(WIN32)
  SET_TARGET_PROPERTIES(_math PROPERTIES SUFFIX ".pyd")
ELSE(WIN32)
  IF(NOT APPLE)
    SET_TARGET_PROPERTIES(_math PROPERTIES INSTALL_RPATH "${CDPKIT_PYTHON_MODULE_INSTALL_RPATH2}")

    SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/_math.so")
    CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
                   "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" 
                   @ONLY
                  )
    INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake")
  ELSE(NOT APPLE)
    SET_TARGET_PROPERTIES(_math PROPERTIES LINK_FLAGS "-Wl,-rpath,\"${CDPKIT_PYTHON_MODULE_INSTALL_RPATH2}\"")
  ENDIF(NOT APPLE)
ENDIF(WIN32)

INSTALL(FILES ${PYTHON_FILES} DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Math" COMPONENT CDPLPythonModules)
INSTALL(TARGETS _math DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Math" COMPONENT CDPLPythonModules)

IF(PYTHONINTERP_FOUND)
  ADD_SUBDIRECTORY(Tests)
ENDIF(PYTHONINTERP_FOUND)
