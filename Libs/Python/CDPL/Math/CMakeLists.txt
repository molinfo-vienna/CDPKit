##
# CMakeLists.txt  
#
# This file is part of the Chemical Data Processing Toolkit
#
# Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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

if(NUMPY_FOUND)
  include_directories("${CMAKE_CURRENT_SOURCE_DIR}" "${NUMPY_INCLUDE_DIRS}")
else(NUMPY_FOUND)
  include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
endif(NUMPY_FOUND)

file(GLOB PYTHON_FILES "*.py")

foreach(PYTHON_FILE ${PYTHON_FILES})
  configure_file("${PYTHON_FILE}" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)
endforeach(PYTHON_FILE)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-overloaded-virtual -Wno-maybe-uninitialized")
endif(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")

if(NOT WIN32)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif(NOT WIN32)

set(math_impl_MOD_SRCS
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
    FunctionWrapperExport.cpp
    
    ToPythonConverterRegistration.cpp
    
    FromPythonToExpressionPointerConverterRegistration.cpp
    FromPythonToAnyConverterRegistration.cpp
    FromPythonToVectorConverterRegistration.cpp
    FromPythonToCVectorConverterRegistration.cpp
    FromPythonToMatrixConverterRegistration.cpp    
    FromPythonToCMatrixConverterRegistration.cpp    
    FromPythonToQuaternionConverterRegistration.cpp    
    FromPythonToVectorArrayConverterRegistration.cpp    
    FromPythonToGridConverterRegistration.cpp
   )

set(math_MOD_SRCS
    Module.cpp
   )

if(NUMPY_FOUND)
  set(math_impl_MOD_SRCS
      ${math_impl_MOD_SRCS}
      NumPy.cpp
     )
endif(NUMPY_FOUND)

add_library(_math-impl STATIC ${math_impl_MOD_SRCS})
add_library(_math MODULE ${math_MOD_SRCS})

target_link_libraries(_math _math-impl cdpl-math-shared ${Boost_PYTHON_LIBRARY} ${PYTHON_LIBRARIES})

set_target_properties(_math PROPERTIES PREFIX "")
set_target_properties(_math-impl PROPERTIES PREFIX "")

if(WIN32)
  set_target_properties(_math PROPERTIES SUFFIX ".pyd")
  set(BINARY_INPUT_FILE "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Math/_math.pyd")
else(WIN32)
  set_target_properties(_math PROPERTIES INSTALL_RPATH "${CDPKIT_PYTHON_MODULE_INSTALL_RPATH2}")
  set(BINARY_INPUT_FILE "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Math/_math.so")
endif(WIN32)

configure_file("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
  "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" @ONLY)

install(FILES ${PYTHON_FILES} DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Math" COMPONENT CDPLPythonModules)
install(TARGETS _math DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Math" COMPONENT CDPLPythonModules)
install(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" COMPONENT CDPLPythonModules)

if(PYTHON_TESTS_ENABLED)
  add_subdirectory(Tests)
endif(PYTHON_TESTS_ENABLED)
