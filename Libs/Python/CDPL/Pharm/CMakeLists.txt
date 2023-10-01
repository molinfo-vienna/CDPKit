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

set(pharm_MOD_SRCS
    Module.cpp
    FeatureExport.cpp
    BasicFeatureExport.cpp
    FeatureContainerExport.cpp
    FeatureSetExport.cpp
    PharmacophoreExport.cpp
    BasicPharmacophoreExport.cpp

    FeatureMappingExport.cpp 
    FeatureTypeHistogramExport.cpp 
 
    FeatureContainerIOManagerExport.cpp 
    PharmacophoreIOManagerExport.cpp 
    PharmacophoreReaderExport.cpp 
    FeatureContainerWriterExport.cpp 
    PharmacophoreInputHandlerExport.cpp 
    FeatureContainerOutputHandlerExport.cpp 
 
    CDFPharmacophoreInputHandlerExport.cpp 
    CDFFeatureContainerOutputHandlerExport.cpp 
    CDFPharmacophoreReaderExport.cpp 
    CDFFeatureContainerWriterExport.cpp
   
    PMLPharmacophoreInputHandlerExport.cpp 
    PMLFeatureContainerOutputHandlerExport.cpp 
    PMLPharmacophoreReaderExport.cpp 
    PMLFeatureContainerWriterExport.cpp

    PharmacophoreFitScoreExport.cpp

    ScreeningDBCreatorExport.cpp
    ScreeningDBAccessorExport.cpp
    ScreeningProcessorExport.cpp
    PharmacophoreFitScreeningScoreExport.cpp
    FileScreeningHitCollectorExport.cpp

    PSDScreeningDBCreatorExport.cpp
    PSDScreeningDBAccessorExport.cpp
    PSDPharmacophoreInputHandlerExport.cpp 
    PSDMoleculeInputHandlerExport.cpp 
    PSDMolecularGraphOutputHandlerExport.cpp 
    PSDPharmacophoreReaderExport.cpp 
    PSDMoleculeReaderExport.cpp 
    PSDMolecularGraphWriterExport.cpp
      
    FunctionWrapperExport.cpp

    FeatureGeneratorExport.cpp
    PharmacophoreGeneratorExport.cpp
    DefaultPharmacophoreGeneratorExport.cpp
    PatternBasedFeatureGeneratorExport.cpp
    AromaticFeatureGeneratorExport.cpp
    HydrophobicFeatureGeneratorExport.cpp
    HydrophobicAtomFeatureGeneratorExport.cpp
    HBondAcceptorFeatureGeneratorExport.cpp
    HBondDonorFeatureGeneratorExport.cpp
    PosIonizableFeatureGeneratorExport.cpp
    NegIonizableFeatureGeneratorExport.cpp
    XBondAcceptorFeatureGeneratorExport.cpp
    XBondDonorFeatureGeneratorExport.cpp
    InteractionAnalyzerExport.cpp
    DefaultInteractionAnalyzerExport.cpp
    InteractionConstraintConnectorExport.cpp
    FeatureDistanceConstraintExport.cpp
    HydrophobicInteractionConstraintExport.cpp
    IonicInteractionConstraintExport.cpp
    OrthogonalPiPiInteractionConstraintExport.cpp
    ParallelPiPiInteractionConstraintExport.cpp
    CationPiInteractionConstraintExport.cpp
    HBondingInteractionConstraintExport.cpp
    XBondingInteractionConstraintExport.cpp
    InteractionPharmacophoreGeneratorExport.cpp

    FeatureInteractionScoreExport.cpp
    FeatureInteractionScoreCombinerExport.cpp
    FeatureDistanceScoreExport.cpp
    HydrophobicInteractionScoreExport.cpp
    IonicInteractionScoreExport.cpp
    OrthogonalPiPiInteractionScoreExport.cpp
    ParallelPiPiInteractionScoreExport.cpp
    CationPiInteractionScoreExport.cpp
    HBondingInteractionScoreExport.cpp
    XBondingInteractionScoreExport.cpp

    FeatureTypeMatchFunctorExport.cpp
    FeaturePairDistanceMatchFunctorExport.cpp
    TopologicalEntityAlignmentExport.cpp    
    PharmacophoreAlignmentExport.cpp
    SpatialFeatureMappingExport.cpp
    FeaturePositionMatchFunctorExport.cpp
    FeatureGeometryMatchFunctorExport.cpp
    
    FeatureContainerPropertyExport.cpp 
    FeaturePropertyExport.cpp 
    FeatureContainerPropertyDefaultExport.cpp 
    FeaturePropertyDefaultExport.cpp 
    DataFormatExport.cpp 
    FeatureTypeExport.cpp 
    FeatureGeometryExport.cpp 
    ControlParameterExport.cpp 
    ControlParameterDefaultExport.cpp 

    PharmacophoreFunctionExport.cpp 
    FeatureFunctionExport.cpp 
    FeatureContainerFunctionExport.cpp 
    FeatureSetFunctionExport.cpp 
    ControlParameterFunctionExport.cpp 
    MoleculeFunctionExport.cpp
    UtilityFunctionExport.cpp 

    ToPythonConverterRegistration.cpp
    FromPythonConverterRegistration.cpp
   )

add_library(_pharm MODULE ${pharm_MOD_SRCS})

target_link_libraries(_pharm cdpl-pharm-shared ${Boost_PYTHON_LIBRARY} ${PYTHON_LIBRARIES})

set_target_properties(_pharm PROPERTIES PREFIX "")

if(WIN32)
  set_target_properties(_pharm PROPERTIES SUFFIX ".pyd")
  set(BINARY_INPUT_FILE "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Pharm/_pharm.pyd")
else(WIN32)
  set_target_properties(_pharm PROPERTIES INSTALL_RPATH "${CDPKIT_PYTHON_MODULE_INSTALL_RPATH2}")
  set(BINARY_INPUT_FILE "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Pharm/_pharm.so")
endif(WIN32)

configure_file("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
  "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" @ONLY)

install(FILES ${PYTHON_FILES} DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Pharm" COMPONENT CDPLPythonModules)
install(TARGETS _pharm DESTINATION "${CDPKIT_PYTHON_INSTALL_DIR}/CDPL/Pharm" COMPONENT CDPLPythonModules)
install(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" COMPONENT CDPLPythonModules)

if(PYTHON_TESTS_ENABLED)
  add_subdirectory(Tests)
endif(PYTHON_TESTS_ENABLED)
