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

INCLUDE_DIRECTORIES("${CMAKE_CURRENT_SOURCE_DIR}" "${CDPL_SOURCE_DIR}" "${CDPKIT_EXTERNAL_DIR}")

SET(cdpl-chem_LIB_SRCS
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

    SubstructureSearch.cpp
    ReactionSubstructureSearch.cpp
    CommonConnectedSubstructureSearch.cpp
    MaxCommonAtomSubstructureSearch.cpp
    MaxCommonBondSubstructureSearch.cpp
    AutomorphismGroupSearch.cpp
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
    
    FragmentGenerator.cpp
    RECAPFragmentGenerator.cpp
    BRICSFragmentGenerator.cpp

    CompleteRingSet.cpp
    AromaticRingSet.cpp
    AromaticSSSRSubset.cpp
    SmallestSetOfSmallestRings.cpp
    AromaticSubstructure.cpp
    CyclicSubstructure.cpp
    ConnectedSubstructureSet.cpp
    ComponentSet.cpp

    MorganNumberingCalculator.cpp
    CIPPriorityCalculator.cpp
    CanonicalNumberingCalculator.cpp
    Atom2DCoordinatesCalculator.cpp
    Hydrogen3DCoordinatesCalculator.cpp
    BondStereoFlagCalculator.cpp
    BondDirectionCalculator.cpp
    BondOrderCalculator.cpp
    KekuleStructureCalculator.cpp
    HashCodeCalculator.cpp
    SymmetryClassCalculator.cpp
    SurfaceAtomExtractor.cpp
    PatternAtomTyper.cpp
    SubstructureHistogramCalculator.cpp
    GeneralizedBellAtomDensity.cpp
    AtomDensityGridCalculator.cpp
    BuriednessScore.cpp
    BuriednessGridCalculator.cpp

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
    
    AtomPropertyFunctions.cpp
    AtomTypeFunctions.cpp
    AtomFormalChargeFunction.cpp
    AtomHybridizationPerceptionFunction.cpp
    AtomFragmentMembershipFunctions.cpp
    AtomImplicitHydrogenCountFunction.cpp
    AtomConformerCoordinatesFunction.cpp
    AtomStereoDescriptorFunctions.cpp
    AtomCIPConfigurationFunction.cpp
    AtomMDLParityFunction.cpp
    AtomStereoCenterFlagFunction.cpp
    AtomMatchExpressionStringFunction.cpp
    AtomMatchExpressionFunction.cpp
    AtomSybylTypeFunctions.cpp
    AtomTopologicalDistanceFunction.cpp
    AtomMarkReachableAtomsFunction.cpp 

    BondPropertyFunctions.cpp
    BondFragmentMembershipFunctions.cpp
    BondStereoCenterFlagFunction.cpp
    BondStereoDescriptorFunction.cpp
    BondCIPConfigurationFunction.cpp
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
    MolecularGraphSubstructSearchInitializationFunctions.cpp
    MolecularGraphBond2DStereoFlagsFunction.cpp 
    MolecularGraphBondDirectionsFunction.cpp 
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
    MolecularGraphCopyStereoDescriptorsFunctions.cpp  
    MolecularGraphSplitIntoFragmentsFunction.cpp  
    MolecularGraphConformerFunctions.cpp

    ReactionPropertyFunctions.cpp
    ReactionMatchConstraintsFunctions.cpp
    ReactionMatchExpressionFunctions.cpp
    ReactionComponentGroupsFunctions.cpp
    ReactionAtomMappingFunctions.cpp
    ReactionHashCodeFunction.cpp
    ReactionSMILESFunction.cpp
    ReactionSubstructSearchInitializationFunctions.cpp
    ReactionMaxAtomMappingIDFunction.cpp
    ReactionMaxComponentGroupIDFunction.cpp

    MoleculeHydrogenManipulationFunctions.cpp
    MoleculeRemoveAtomsFunctions.cpp
    MoleculeNeutralizeFunction.cpp

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

IF(Boost_FILESYSTEM_FOUND AND Boost_IOSTREAMS_FOUND)
   LINK_LIBRARIES(${Boost_FILESYSTEM_LIBRARY} ${Boost_IOSTREAMS_LIBRARY})
ENDIF(Boost_FILESYSTEM_FOUND AND Boost_IOSTREAMS_FOUND)

LINK_LIBRARIES(${Boost_THREAD_LIBRARY} ${Boost_SYSTEM_LIBRARY} ${Boost_DATE_TIME_LIBRARY})

ADD_LIBRARY(cdpl-chem-static STATIC ${cdpl-chem_LIB_SRCS})

SET_TARGET_PROPERTIES(cdpl-chem-static PROPERTIES 
                      OUTPUT_NAME cdpl-chem
                      CLEAN_DIRECT_OUTPUT 1
                      COMPILE_DEFINITIONS "CDPL_CHEM_STATIC_LINK;CDPL_GRID_STATIC_LINK;CDPL_MATH_STATIC_LINK;CDPL_UTIL_STATIC_LINK;CDPL_BASE_STATIC_LINK"
                     )

TARGET_LINK_LIBRARIES(cdpl-chem-static cdpl-grid-static cdpl-math-static cdpl-util-static cdpl-base-static cdpl-internal-static inchi-static)

INSTALL(TARGETS cdpl-chem-static
        DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLStaticLibraries
       )

ADD_LIBRARY(cdpl-chem-shared SHARED ${cdpl-chem_LIB_SRCS})

TARGET_LINK_LIBRARIES(cdpl-chem-shared cdpl-grid-shared cdpl-base-shared cdpl-math-shared cdpl-util-shared cdpl-internal-static inchi-static)

IF(APPLE)
  SET_TARGET_PROPERTIES(cdpl-chem-shared PROPERTIES VERSION "${CDPL_SO_VERSION}"
                        FRAMEWORK TRUE
                        OUTPUT_NAME CDPL-Chem
                        INSTALL_NAME_DIR "${CDPKIT_FRAMEWORK_INSTALL_NAME_DIR}"
                        LINK_FLAGS "-Wl,-rpath,\"${CDPKIT_FRAMEWORK_INSTALL_RPATH}\""
                       )
ELSE(APPLE)
  SET_TARGET_PROPERTIES(cdpl-chem-shared PROPERTIES VERSION "${CDPL_VERSION}" SOVERSION "${CDPL_SO_VERSION}"
                        OUTPUT_NAME cdpl-chem
                        CLEAN_DIRECT_OUTPUT 1
                        INSTALL_RPATH "${CDPKIT_LIBRARY_INSTALL_RPATH}"
                       )

  IF(WIN32)
    SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/libcdpl-chem.dll")
  ELSE()			
    SET(BINARY_INPUT_FILE "${CMAKE_CURRENT_BINARY_DIR}/libcdpl-chem.so")
  ENDIF(WIN32)

  CONFIGURE_FILE("${CDPKIT_CMAKE_SCRIPTS_DIR}/InstallExternalRuntimeDependencies.cmake.in" 
    "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake"
    @ONLY
    )
  INSTALL(SCRIPT "${CMAKE_CURRENT_BINARY_DIR}/InstallExternalRuntimeDependencies.cmake" COMPONENT CDPLSharedLibraries)
ENDIF(APPLE)

INSTALL(TARGETS cdpl-chem-shared
        RUNTIME DESTINATION "${CDPKIT_EXECUTABLE_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
        LIBRARY DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLSharedLibraries
        ARCHIVE DESTINATION "${CDPKIT_LIBRARY_INSTALL_DIR}" COMPONENT CDPLImportLibraries
        FRAMEWORK DESTINATION "${CDPKIT_FRAMEWORK_INSTALL_DIR}" COMPONENT CDPLFrameworks
       )

IF(Boost_UNIT_TEST_FRAMEWORK_FOUND AND CDPKIT_TESTING_ENABLED)
  ADD_SUBDIRECTORY(Tests)
ENDIF(Boost_UNIT_TEST_FRAMEWORK_FOUND AND CDPKIT_TESTING_ENABLED)
