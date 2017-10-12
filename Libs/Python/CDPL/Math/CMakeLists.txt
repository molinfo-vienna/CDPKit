INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")

FILE(GLOB PYTHON_FILES "*.py")

FOREACH(PYTHON_FILE ${PYTHON_FILES})
  EXECUTE_PROCESS(COMMAND "${CMAKE_COMMAND}" -E copy "${PYTHON_FILE}" "${CMAKE_CURRENT_BINARY_DIR}"
                  WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
ENDFOREACH(PYTHON_FILE)

IF(CMAKE_COMPILER_IS_GNUCC AND UNIX)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
ENDIF(CMAKE_COMPILER_IS_GNUCC AND UNIX)

SET(math_impl_MOD_SRCS
    VectorExpressionExport.cpp
    MatrixExpressionExport.cpp
    QuaternionExpressionExport.cpp
    GridExpressionExport.cpp

    VectorExport.cpp
    CVectorExport1.cpp
    CVectorExport2.cpp	
    CVectorExport3.cpp	
    ScalarVectorExport.cpp
    ZeroVectorExport.cpp
    UnitVectorExport.cpp

    MatrixExport.cpp
    CMatrixExport1.cpp
    CMatrixExport2.cpp
    CMatrixExport3.cpp    
    TranslationMatrixExport.cpp
    ScalingMatrixExport.cpp
    RotationMatrixExport.cpp
    IdentityMatrixExport.cpp
    ScalarMatrixExport.cpp
    ZeroMatrixExport.cpp    
    QuaternionExport.cpp
    RealQuaternionExport.cpp
    GridExport.cpp
    ZeroGridExport.cpp
    ScalarGridExport.cpp
    RegularSpatialGridExport.cpp

    RangeExport.cpp
    SliceExport.cpp
    VectorSliceExport.cpp
    ConstVectorSliceExport.cpp
    VectorRangeExport.cpp
    ConstVectorRangeExport.cpp
    
    MatrixRangeExport.cpp
    ConstMatrixRangeExport.cpp
    MatrixSliceExport.cpp
    ConstMatrixSliceExport.cpp	
    MatrixRowExport.cpp
    ConstMatrixRowExport.cpp
    MatrixColumnExport.cpp
    ConstMatrixColumnExport.cpp    
 
    VectorQuaternionAdapterExport.cpp
    ConstVectorQuaternionAdapterExport.cpp
    HomogenousCoordsAdapterExport.cpp
    ConstHomogenousCoordsAdapterExport.cpp

    TriangularMatrixTypeExport.cpp
    TriangularMatrixAdapterExport1.cpp
    TriangularMatrixAdapterExport2.cpp
    TriangularMatrixAdapterExport3.cpp
    TriangularMatrixAdapterExport4.cpp 
    MatrixTransposeExport.cpp
    ConstMatrixTransposeExport.cpp	

    QuaternionAdapterExport.cpp
    
    VectorFunctionExport.cpp
    MatrixFunctionExport.cpp
    SpecialFunctionExport.cpp
    QuaternionFunctionExport.cpp
    GridFunctionExport.cpp

    VectorArrayExport.cpp
    VectorArrayFunctionExport.cpp
    MLRModelExport.cpp
    BFGSMinimizerExport.cpp
    KabschAlgorithmExport.cpp
    BoostFunctionWrapperExport.cpp
    
    ToPythonConverterRegistration.cpp
    
    FromPythonToExpressionPointerConverterRegistration.cpp
    FromPythonToVariantConverterRegistration.cpp
    FromPythonToVectorConverterRegistration.cpp
    FromPythonToCVectorConverterRegistration.cpp
    FromPythonToMatrixConverterRegistration.cpp	
    FromPythonToCMatrixConverterRegistration.cpp	
    FromPythonToGridConverterRegistration.cpp	
   )

SET(math_MOD_SRCS
    Module.cpp
   )

ADD_LIBRARY(_math-impl STATIC ${math_impl_MOD_SRCS})
ADD_LIBRARY(_math MODULE ${math_MOD_SRCS})

TARGET_LINK_LIBRARIES(_math _math-impl cdpl-math-shared ${Boost_PYTHON_LIBRARY} ${PYTHON_LIBRARIES})

SET_TARGET_PROPERTIES(_math PROPERTIES PREFIX "")
SET_TARGET_PROPERTIES(_math-impl PROPERTIES PREFIX "")


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
