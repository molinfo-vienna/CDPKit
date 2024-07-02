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

include_directories("${CMAKE_CURRENT_SOURCE_DIR}" "${CDPL_SOURCE_DIR}" "${CDPKIT_EXTERNAL_DIR}" "${CMAKE_CURRENT_BINARY_DIR}")

add_custom_command(OUTPUT ChEMBL-Solvents.smi.str
  COMMAND "${PYTHON_EXECUTABLE}" "${CDPKIT_PYTHON_SCRIPTS_DIR}/DataFileToCString.py" 
  "${CDPKIT_BUILTIN_DATA_DIR}/Chem/ChEMBL-Solvents.smi" 
  "ChEMBL-Solvents.smi.str"
  DEPENDS "${CDPKIT_BUILTIN_DATA_DIR}/Chem/ChEMBL-Solvents.smi" 
  COMMENT "-- Processing ChEMBL-Solvents.smi..."
  )
add_custom_command(OUTPUT ChEMBL-Salts.smi.str
  COMMAND "${PYTHON_EXECUTABLE}" "${CDPKIT_PYTHON_SCRIPTS_DIR}/DataFileToCString.py" 
  "${CDPKIT_BUILTIN_DATA_DIR}/Chem/ChEMBL-Salts.smi" 
  "ChEMBL-Salts.smi.str"
  DEPENDS "${CDPKIT_BUILTIN_DATA_DIR}/Chem/ChEMBL-Salts.smi" 
  COMMENT "-- Processing ChEMBL-Salts.smi..."
  )
add_custom_target(gen-chem-data-files DEPENDS ChEMBL-Solvents.smi.str ChEMBL-Salts.smi.str)
           
set(cdpl-chem_LIB_SRCS
    ChEMBL-Solvents.smi.str
    ChEMBL-Salts.smi.str

    Entity3D.cpp
    Entity3DContainer.cpp
    AtomContainer.cpp
    BondContainer.cpp
    MolecularGraph.cpp
    Molecule.cpp
    Atom.cpp
    Bond.cpp
    Reaction.cpp
    BasicReaction.cpp
    BasicMolecule.cpp
    BasicAtom.cpp
    BasicBond.cpp
    Fragment.cpp
    ElectronSystem.cpp
    Entity3DMapping.cpp    
    AtomBondMapping.cpp

    Entity3DProperty.cpp
    AtomProperty.cpp
    BondProperty.cpp
    MolecularGraphProperty.cpp
    ReactionProperty.cpp
    AtomPropertyDefault.cpp
    BondPropertyDefault.cpp
    MolecularGraphPropertyDefault.cpp
    ReactionPropertyDefault.cpp

    ControlParameter.cpp
    ControlParameterDefault.cpp
    DataFormat.cpp
    INCHIReturnCode.cpp

    StringDataBlock.cpp
    StereoDescriptor.cpp
    AtomDictionary.cpp

    DefaultMultiConfMoleculeInputProcessor.cpp

    INCHIMoleculeReader.cpp
    INCHIMolecularGraphWriter.cpp
    JMEDataReader.cpp
    JMEDataWriter.cpp
    JMEMoleculeReader.cpp
    JMEMolecularGraphWriter.cpp
    JMEReactionReader.cpp
    JMEReactionWriter.cpp
    SMILESDataReader.cpp
    SMILESDataWriter.cpp
    SMILESMoleculeReader.cpp
    SMILESReactionReader.cpp
    SMILESMolecularGraphWriter.cpp
    SMILESReactionWriter.cpp
    SMARTSDataReader.cpp
    SMARTSDataWriter.cpp
    SMARTSMoleculeReader.cpp
    SMARTSReactionReader.cpp
    SMARTSMolecularGraphWriter.cpp
    SMARTSReactionWriter.cpp
    MDLDataReader.cpp
    MDLDataWriter.cpp
    MOLMoleculeReader.cpp
    MOLMolecularGraphWriter.cpp
    SDFMoleculeReader.cpp
    SDFMolecularGraphWriter.cpp
    RXNReactionReader.cpp
    RXNReactionWriter.cpp
    RDFReactionReader.cpp
    RDFReactionWriter.cpp
    CDFDataReader.cpp
    CDFDataWriter.cpp
    CDFMoleculeReader.cpp
    CDFMolecularGraphWriter.cpp
    CDFReactionReader.cpp
    CDFReactionWriter.cpp
    MOL2DataReader.cpp
    MOL2DataWriter.cpp
    MOL2MoleculeReader.cpp
    MOL2MolecularGraphWriter.cpp
    XYZDataReader.cpp
    XYZDataWriter.cpp
    XYZMoleculeReader.cpp
    XYZMolecularGraphWriter.cpp
  
    SubstructureSearch.cpp
    ReactionSubstructureSearch.cpp
    CommonConnectedSubstructureSearch.cpp
    MaxCommonAtomSubstructureSearch.cpp
    MaxCommonBondSubstructureSearch.cpp
    AutomorphismGroupSearch.cpp
    MultiSubstructureSearch.cpp
    Reactor.cpp

    TautomerScore.cpp
    TautomerGenerator.cpp
    DefaultTautomerGenerator.cpp
    PatternBasedTautomerizationRule.cpp 
    KetoEnolTautomerization.cpp 
    ImineEnamineTautomerization.cpp  
    NitrosoOximeTautomerization.cpp  
    AmideImidicAcidTautomerization.cpp  
    LactamLactimTautomerization.cpp  
    KeteneYnolTautomerization.cpp  
    NitroAciTautomerization.cpp  
    PhosphinicAcidTautomerization.cpp  
    SulfenicAcidTautomerization.cpp  
    GenericHydrogen13ShiftTautomerization.cpp  
    GenericHydrogen15ShiftTautomerization.cpp  
    ResonanceStructureGenerator.cpp
    StereoisomerGenerator.cpp
    ChEMBLStandardizer.cpp
    ProtonationStateStandardizer.cpp
    
    FragmentGenerator.cpp
    RECAPFragmentGenerator.cpp
    BRICSFragmentGenerator.cpp
    BemisMurckoAnalyzer.cpp

    CompleteRingSet.cpp
    AromaticRingSet.cpp
    AromaticSSSRSubset.cpp
    SmallestSetOfSmallestRings.cpp
    ExtendedSSSR.cpp
    AromaticSubstructure.cpp
    CyclicSubstructure.cpp
    ConnectedSubstructureSet.cpp
    ComponentSet.cpp
    PiElectronSystemList.cpp

    CIPConfigurationLabeler.cpp
    CIPConfigurationLabelerImpl.cpp
    CIPDigraph.cpp
    CIPMancude.cpp
    CIPStereoCenter.cpp
    CIPSp2BondCenter.cpp
    CIPTetrahedralCenter.cpp
    CIPSorter.cpp
    CIPSequenceRule.cpp
    CIPRule1a.cpp
    CIPRule1b.cpp
    CIPRule2.cpp
    CIPRule3.cpp
    CIPRule4a.cpp
    CIPRule4b.cpp
    CIPRule4c.cpp
    CIPRule5.cpp
    CIPRule6.cpp
    CIPPairList.cpp
    CIPRuleStack.cpp
    
    CIPPriorityCalculator.cpp
    MorganNumberingCalculator.cpp
    CanonicalNumberingCalculator.cpp
    Atom2DCoordinatesCalculator.cpp
    Hydrogen3DCoordinatesCalculator.cpp
    BondStereoFlagCalculator.cpp
    BondOrderCalculator.cpp
    KekuleStructureCalculator.cpp
    HashCodeCalculator.cpp
    SymmetryClassCalculator.cpp
    SurfaceAtomExtractor.cpp
    PatternAtomTyper.cpp
    SubstructureHistogramCalculator.cpp

    Entity3DPropertyFunctions.cpp

    Entity3DContainerCoordinatesFunctions.cpp
    Entity3DContainerGeometricalDistanceMatrixFunction.cpp
    Entity3DContainerCentroidFunction.cpp
    Entity3DContainerBoundingBoxFunctions.cpp

    AtomContainerCoordinatesFunctions.cpp
    AtomContainerMaxAtomMappingIDFunction.cpp
    AtomContainerMaxComponentGroupIDFunction.cpp
    AtomContainerConformerFunctions.cpp
    AtomContainerAtomTypeMaskFunction.cpp
    AtomContainerCopyAtomsFunctions.cpp
    AtomContainerBoundingBoxFunctions.cpp
    AtomContainerCentroidFunction.cpp
    AtomContainerCenterOfMassFunction.cpp
    
    AtomPropertyFunctions.cpp
    AtomTypeFunctions.cpp
    AtomFormalChargeFunction.cpp
    AtomHybridizationPerceptionFunction.cpp
    AtomFragmentMembershipFunctions.cpp
    AtomImplicitHydrogenCountFunction.cpp
    AtomConformerCoordinatesFunction.cpp
    AtomStereoDescriptorFunctions.cpp
    AtomMDLParityFunction.cpp
    AtomStereoCenterFlagFunction.cpp
    AtomMatchExpressionStringFunction.cpp
    AtomMatchExpressionFunction.cpp
    AtomSybylTypeFunctions.cpp
    AtomTopologicalDistanceFunction.cpp
    AtomMarkReachableAtomsFunction.cpp 
    AtomEnvironmentFunction.cpp
    
    BondPropertyFunctions.cpp
    BondFragmentMembershipFunctions.cpp
    BondStereoCenterFlagFunction.cpp
    BondStereoDescriptorFunction.cpp
    BondMatchExpressionStringFunction.cpp
    BondMatchExpressionFunction.cpp
    BondSybylTypePerception.cpp

    MolecularGraphPropertyFunctions.cpp
    MolecularGraphMatchConstraintsFunctions.cpp
    MolecularGraphComponentFunctions.cpp
    MolecularGraphRingSetFunctions.cpp
    MolecularGraphSSSRFunctions.cpp
    MolecularGraphCyclicSubstructureFunctions.cpp
    MolecularGraphGeometricalDistanceMatrixFunction.cpp
    MolecularGraphTopologicalDistanceFunctions.cpp
    MolecularGraphAdjacencyMatrixFunction.cpp
    MolecularGraphIncidenceMatrixFunction.cpp
    MolecularGraphBondMatrixFunction.cpp
    MolecularGraphBondElectronMatrixFunction.cpp
    MolecularGraphBondAtomTypeMatrixFunction.cpp
    MolecularGraphComponentGroupsFunctions.cpp
    MolecularGraphExtractReactionCenterFunction.cpp
    MolecularGraphCompleteBondCountFunction.cpp
    MolecularGraphAromaticRingSetFunctions.cpp
    MolecularGraphAromaticSubstructureFunctions.cpp
    MolecularGraphKekulizeBondsFunction.cpp
    MolecularGraphBondOrdersFunction.cpp
    MolecularGraphMatchExpressionFunctions.cpp
    MolecularGraphMatchExpressionStringsFunction.cpp
    MolecularGraphSMILESFunction.cpp
    MolecularGraphINCHIFunctions.cpp
    MolecularGraphHashCodeFunction.cpp
    MolecularGraphBond2DStereoFlagsFunction.cpp 
    MolecularGraphCIPPrioritiesFunction.cpp 
    MolecularGraphSymmetryClassesFunction.cpp 
    MolecularGraphCanonicalNumberingFunction.cpp 
    MolecularGraphMorganNumberingFunction.cpp 
    MolecularGraphAtomStereoFunctions.cpp 
    MolecularGraphBondStereoFunctions.cpp 
    MolecularGraphImplicitHydrogenCountsFunction.cpp 
    MolecularGraphFormalChargesFunction.cpp 
    MolecularGraphHybridizationStatesFunction.cpp 
    MolecularGraphAromaticityFlagsFunction.cpp 
    MolecularGraphRingFlagsFunction.cpp 
    MolecularGraphAtomTypesFromSymbolFunction.cpp
    MolecularGraphAtomSymbolsFromTypeFunction.cpp
    MolecularGraph2DCoordinatesFunction.cpp
    MolecularGraph3DCoordinatesFunctions.cpp
    MolecularGraphSybylAtomTypesFunction.cpp
    MolecularGraphCanonicalizationFunctions.cpp 
    MolecularGraphFragmentMembershipFunctions.cpp 
    MolecularGraphFragmentTranslationFunctions.cpp
    MolecularGraphSplitIntoFragmentsFunction.cpp  
    MolecularGraphConformerFunctions.cpp
    MolecularGraphPiElectronSystemsFunctions.cpp
    MolecularGraphInitializationFunctions.cpp
    
    ReactionPropertyFunctions.cpp
    ReactionMatchConstraintsFunctions.cpp
    ReactionMatchExpressionFunctions.cpp
    ReactionComponentGroupsFunctions.cpp
    ReactionAtomMappingFunctions.cpp
    ReactionHashCodeFunction.cpp
    ReactionSMILESFunction.cpp
    ReactionMaxAtomMappingIDFunction.cpp
    ReactionMaxComponentGroupIDFunction.cpp
    ReactionInitializationFunctions.cpp
    
    MoleculeHydrogenManipulationFunctions.cpp
    MoleculeRemoveAtomsFunctions.cpp
    MoleculeConnectAtomsFunctions.cpp

    FragmentHydrogenManipulationFunctions.cpp
    FragmentRemoveAtomsFunctions.cpp

    Atom3DCoordinatesFunctor.cpp
    AtomConformer3DCoordinatesFunctor.cpp
    AtomArray3DCoordinatesFunctor.cpp

    ControlParameterFunctions.cpp
    UtilityFunctions.cpp

    MatchConstraintList.cpp
    AtomTypeMatchExpression.cpp
    AtomEnvironmentMatchExpression.cpp
    AtomConfigurationMatchExpression.cpp
    BondConfigurationMatchExpression.cpp
    BondDirectionMatchExpression.cpp
    BondSubstituentDirectionMatchExpression.cpp
    BondReactionCenterStatusMatchExpression.cpp
    MolecularGraphComponentGroupingMatchExpression.cpp
    ReactionAtomMappingMatchExpression.cpp
    ReactionComponentGroupingMatchExpression.cpp
   )

link_libraries(${Boost_IOSTREAMS_LIBRARY})

if(NOT PYPI_PACKAGE_BUILD)
  add_library(cdpl-chem-static STATIC ${cdpl-chem_LIB_SRCS} $<TARGET_OBJECTS:inchi> $<TARGET_OBJECTS:cdpl-internal>)
  add_dependencies(cdpl-chem-static gen-chem-data-files)
  
  set_target_properties(cdpl-chem-static PROPERTIES 
    OUTPUT_NAME cdpl-chem
    CLEAN_DIRECT_OUTPUT 1
    COMPILE_DEFINITIONS "CDPL_CHEM_STATIC_LINK")

  target_link_libraries(cdpl-chem-static cdpl-math-static cdpl-util-static cdpl-base-static)

  install(TARGETS cdpl-chem-static
    DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLStaticLibraries)
endif(NOT PYPI_PACKAGE_BUILD)

add_library(cdpl-chem-shared SHARED ${cdpl-chem_LIB_SRCS} $<TARGET_OBJECTS:inchi> $<TARGET_OBJECTS:cdpl-internal>)
add_dependencies(cdpl-chem-shared gen-chem-data-files)

target_link_libraries(cdpl-chem-shared cdpl-base-shared cdpl-math-shared cdpl-util-shared)

set_target_properties(cdpl-chem-shared PROPERTIES VERSION "${CDPL_VERSION}" SOVERSION "${CDPL_SO_VERSION}"
  OUTPUT_NAME cdpl-chem
  CLEAN_DIRECT_OUTPUT 1
  INSTALL_RPATH "${CDPKIT_LIBRARY_INSTALL_RPATH}")

if(WIN32)
  set(BINARY_INPUT_FILE "${CDPKIT_EXECUTABLE_INSTALL_DIR}/libcdpl-chem.dll")
elseif(APPLE)
  set(BINARY_INPUT_FILE "${CDPKIT_LIBRARY_INSTALL_DIR}/libcdpl-chem.dylib")
else()            
  set(BINARY_INPUT_FILE "${CDPKIT_LIBRARY_INSTALL_DIR}/libcdpl-chem.so")
endif(WIN32)

configure_file("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
  "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" @ONLY)

if(WIN32 AND PYPI_PACKAGE_BUILD)
   install(TARGETS cdpl-chem-shared
     RUNTIME DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries)
else()
  install(TARGETS cdpl-chem-shared
    RUNTIME DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
    LIBRARY DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
    ARCHIVE DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLImportLibraries)
endif(WIN32 AND PYPI_PACKAGE_BUILD)

install(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" COMPONENT CDPLSharedLibraries)

if(CDPL_CXX_UNIT_TESTS_ENABLED)
  add_subdirectory(Tests)
endif(CDPL_CXX_UNIT_TESTS_ENABLED)
