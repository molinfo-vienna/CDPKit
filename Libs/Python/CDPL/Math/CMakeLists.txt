# -*- mode: CMake -*-

##
# CMakeLists.txt  
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2 of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program; see the file COPYING. If not, write to
# the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
##

IF(NUMPY_FOUND)
  INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}" "${NUMPY_INCLUDE_DIRS}")
ELSE(NUMPY_FOUND)
  INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}")
ENDIF(NUMPY_FOUND)

FILE(GLOB PYTHON_FILES "*.py")

FOREACH(PYTHON_FILE ${PYTHON_FILES})
  CONFIGURE_FILE("${PYTHON_FILE}" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)
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
    SparseVectorExport.cpp
    CVectorExport1.cpp
    CVectorExport2.cpp	
    CVectorExport3.cpp	
    ScalarVectorExport.cpp
    ZeroVectorExport.cpp
    UnitVectorExport.cpp

    MatrixExport.cpp
    SparseMatrixExport.cpp
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
    RegularSpatialGridFunctionExport.cpp

    VectorArrayExport.cpp
    VectorArrayFunctionExport.cpp
    MLRModelExport.cpp
    BFGSMinimizerExport.cpp
    KabschAlgorithmExport.cpp
    VectorArrayAlignmentCalculatorExport.cpp
    BoostFunctionWrapperExport.cpp
    
    ToPythonConverterRegistration.cpp
    
    FromPythonToExpressionPointerConverterRegistration.cpp
    FromPythonToVariantConverterRegistration.cpp
    FromPythonToVectorConverterRegistration.cpp
    FromPythonToCVectorConverterRegistration.cpp
    FromPythonToMatrixConverterRegistration.cpp	
    FromPythonToCMatrixConverterRegistration.cpp	
    FromPythonToQuaternionConverterRegistration.cpp	
    FromPythonToVectorArrayConverterRegistration.cpp	
    FromPythonToGridConverterRegistration.cpp
   )

SET(math_MOD_SRCS
    Module.cpp
   )

IF(NUMPY_FOUND)
  SET(math_impl_MOD_SRCS
      ${math_impl_MOD_SRCS}
      NumPy.cpp
     )
ENDIF(NUMPY_FOUND)

ADD_LIBRARY(_math-impl STATIC ${math_impl_MOD_SRCS})
ADD_LIBRARY(_math MODULE ${math_MOD_SRCS})

TARGET_LINK_LIBRARIES(_math _math-impl cdpl-math-shared ${Boost_PYTHON_LIBRARY} ${PYTHON_LIBRARIES})

SET_TARGET_PROPERTIES(_math PROPERTIES PREFIX "")
SET_TARGET_PROPERTIES(_math-impl PROPERTIES PREFIX "")


IF(WIN32)
  SET_TARGET_PROPERTIES(_math PROPERTIES SUFFIX ".pyd")
  SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/_math.pyd")
ELSE(WIN32)
  SET_TARGET_PROPERTIES(_math PROPERTIES COMPILE_DEFINITIONS "BOOST_PYTHON_USE_GCC_SYMBOL_VISIBILITY")

  IF(NOT APPLE)
    SET_TARGET_PROPERTIES(_math PROPERTIES INSTALL_RPATH "${CDPKIT_PYTHON_MODULE_INSTALL_RPATH2}")
    SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/_math.so")
  ELSE(NOT APPLE)
    SET_TARGET_PROPERTIES(_math PROPERTIES LINK_FLAGS "-Wl,-rpath,\"${CDPKIT_PYTHON_MODULE_INSTALL_RPATH2}\"")
  ENDIF(NOT APPLE)
ENDIF(WIN32)

IF(NOT APPLE)
  CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
    "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" 
    @ONLY
    )
  INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake")
ENDIF(NOT APPLE)

INSTALL(FILES ${PYTHON_FILES} DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Math" COMPONENT CDPLPythonModules)
INSTALL(TARGETS _math DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Math" COMPONENT CDPLPythonModules)

IF(PYTHONINTERP_FOUND)
  ADD_SUBDIRECTORY(Tests)
ENDIF(PYTHONINTERP_FOUND)
