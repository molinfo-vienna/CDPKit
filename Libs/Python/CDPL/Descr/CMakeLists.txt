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

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB PYTHON_FILES "*.py")

foreach(PYTHON_FILE ${PYTHON_FILES})
  configure_file("${PYTHON_FILE}" "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)
endforeach(PYTHON_FILE)

set(descr_MOD_SRCS
    Module.cpp

    SimilarityFunctorExport.cpp 
    
    AtomRDFCodeCalculatorExport.cpp 
    MoleculeRDFDescriptorCalculatorExport.cpp 

    AutoCorrelation2DVectorCalculatorExport.cpp
    AtomAutoCorrelation3DVectorCalculatorExport.cpp 
    MoleculeAutoCorr3DDescriptorCalculatorExport.cpp 
    MoleculeAutoCorr2DDescriptorCalculatorExport.cpp 

    BurdenMatrixGeneratorExport.cpp 
    BCUTDescriptorCalculatorExport.cpp 
    MolecularComplexityCalculatorExport.cpp
    
    PathFingerprintGeneratorExport.cpp 
    CircularFingerprintGeneratorExport.cpp
    MACCSFingerprintGeneratorExport.cpp
    PubChemFingerprintGeneratorExport.cpp

    FeatureRDFCodeCalculatorExport.cpp 
    PharmacophoreRDFDescriptorCalculatorExport.cpp
    FeatureAutoCorrelation3DVectorCalculatorExport.cpp 
    PharmacophoreAutoCorr3DDescriptorCalculatorExport.cpp

    NPointPharmacophoreFingerprintGeneratorExport.cpp
    NPoint2DPharmacophoreFingerprintGeneratorExport.cpp
    NPoint3DPharmacophoreFingerprintGeneratorExport.cpp

    Entity3DContainerFunctionExport.cpp
    AtomContainerFunctionExport.cpp 
    MolecularGraphFunctionExport.cpp 
    SimilarityFunctionExport.cpp 

    FromPythonConverterRegistration.cpp
    FunctionWrapperExport.cpp
   )

add_library(_descr MODULE ${descr_MOD_SRCS})

target_link_libraries(_descr cdpl-descr-shared ${Boost_PYTHON_LIBRARY} ${PYTHON_LIBRARIES})

set_target_properties(_descr PROPERTIES PREFIX "")

if(WIN32)
  set_target_properties(_descr PROPERTIES SUFFIX ".pyd")
  set(BINARY_INPUT_FILE "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Descr/_descr.pyd")
else(WIN32)
  set_target_properties(_descr PROPERTIES INSTALL_RPATH "${CDPKIT_PYTHON_MODULE_INSTALL_RPATH2}")
  set(BINARY_INPUT_FILE "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Descr/_descr.so")
endif(WIN32)

configure_file("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
  "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" @ONLY)

install(FILES ${PYTHON_FILES} DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Descr" COMPONENT CDPLPythonModules)
install(TARGETS _descr DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Descr" COMPONENT CDPLPythonModules)
install(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" COMPONENT CDPLPythonModules)

if(PYTHON_TESTS_ENABLED)
  add_subdirectory(Tests)
endif(PYTHON_TESTS_ENABLED)
