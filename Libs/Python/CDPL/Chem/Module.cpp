/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Module.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; see the file COPYING. If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */


#include <boost/python.hpp>

#include "ClassExports.hpp"
#include "FunctionExports.hpp"
#include "NamespaceExports.hpp"
#include "ConverterRegistration.hpp"


BOOST_PYTHON_MODULE(_chem)
{
	using namespace CDPLPythonChem;

	exportEntity3D();
	exportEntity3DContainer();
	exportAtomContainer();
	exportBondContainer();
	exportAtom();
	exportBond();
	exportMolecularGraph();
	exportMolecule();
	exportReaction();
	exportBasicAtom();
	exportBasicBond();
	exportBasicMolecule();
	exportBasicReaction();
	exportFragment();
	exportEntity3DMapping();
	exportAtomMapping();
	exportBondMapping();
	exportAtomBondMapping();
	exportFragmentList();
	exportStringDataBlock();
	exportMassComposition();
	exportElementHistogram();
	exportStereoDescriptor();
	exportMultiConfMoleculeInputProcessor();
	exportDefaultMultiConfMoleculeInputProcessor();
	exportAtomDictionary();

	exportAtom3DCoordinatesFunctor();
	exportAtomConformer3DCoordinatesFunctor();
	exportAtomArray3DCoordinatesFunctor();

	exportMatchConstraintList();
	exportMatchExpressions();
	exportMatchExpressionLists();
	exportANDMatchExpressionLists();
	exportORMatchExpressionLists();
	exportNOTMatchExpressions();
	exportAtomTypeMatchExpression();
	exportAtomEnvironmentMatchExpression();
	exportAtomConfigurationMatchExpression();
	exportBondConfigurationMatchExpression();
	exportBondDirectionMatchExpression();
	exportBondSubstituentDirectionMatchExpression();
	exportBondReactionCenterStatusMatchExpression();
	exportMolecularGraphComponentGroupingMatchExpression();
	exportReactionAtomMappingMatchExpression();
	exportReactionComponentGroupingMatchExpression();

	exportSubstructureSearch();
	exportReactionSubstructureSearch();
	exportCommonConnectedSubstructureSearch();
	exportMaxCommonAtomSubstructureSearch();
	exportMaxCommonBondSubstructureSearch();

	exportReactor();

	exportTopologicalEntityAlignments();
	exportGeometricalEntityAlignments();

	exportCompleteRingSet();
	exportAromaticRingSet();
	exportAromaticSSSRSubset();
	exportSmallestSetOfSmallestRings();
	exportAromaticSubstructure();
	exportCyclicSubstructure();
	exportConnectedSubstructureSet();
	exportComponentSet();

	exportMorganNumberingGenerator();
	exportCanonicalNumberingGenerator();
	exportCIPPriorityCalculator();
	exportAtom2DCoordinatesGenerator();
	exportHydrogen3DCoordinatesGenerator();
	exportBondStereoFlagGenerator();
	exportBondDirectionGenerator();
	exportBondOrderGenerator();
	exportKekuleStructureGenerator();
	exportXLogPCalculator();
	exportTPSACalculator();
	exportHashCodeCalculator();
	exportSymmetryClassCalculator();
	exportLogSCalculator();
	exportMolecularComplexityCalculator();
	exportPEOEChargeCalculator();
	exportDaylightFingerprintGenerator();
	exportAutoCorrelationVectorCalculator();
	exportRDFCodeCalculator();
	exportBurdenMatrixGenerator();
	exportBCUTDescriptorCalculator();
	exportSurfaceAtomExtractor();

	exportMoleculeReader();
	exportMoleculeWriter();
	exportMolecularGraphReader();
	exportMolecularGraphWriter();
	exportReactionReader();
	exportReactionWriter();
	exportINCHIMoleculeReader();
	exportINCHIMolecularGraphWriter();
	exportJMEMoleculeReader();
	exportJMEMolecularGraphWriter();
	exportJMEReactionReader();
	exportJMEReactionWriter();
	exportSMILESMoleculeReader();
	exportSMILESReactionReader();
	exportSMILESMolecularGraphWriter();
	exportSMILESReactionWriter();
	exportSMARTSMoleculeReader();
	exportSMARTSReactionReader();
	exportSMARTSMolecularGraphWriter();
	exportSMARTSReactionWriter();
	exportMOLMoleculeReader();
	exportMOLMolecularGraphWriter();
	exportSDFMoleculeReader();
	exportSDFMolecularGraphWriter();
	exportRXNReactionReader();
	exportRXNReactionWriter();
	exportRDFReactionReader();
	exportRDFReactionWriter();
	exportCDFMoleculeReader();
	exportCDFMolecularGraphWriter();
	exportCDFReactionReader();
	exportCDFReactionWriter();
	exportMOL2MoleculeReader();
	exportMOL2MolecularGraphWriter();

	exportMoleculeIOManager();
	exportMolecularGraphIOManager();
	exportReactionIOManager();

	exportMoleculeInputHandler();
	exportMoleculeOutputHandler();
	exportMolecularGraphInputHandler();
	exportMolecularGraphOutputHandler();
	exportReactionInputHandler();
	exportReactionOutputHandler();
	exportINCHIMoleculeInputHandler();
	exportINCHIMolecularGraphOutputHandler();
	exportCDFMoleculeInputHandler();
	exportCDFMolecularGraphOutputHandler();
	exportCDFReactionInputHandler();
	exportCDFReactionOutputHandler();
	exportJMEMoleculeInputHandler();
	exportJMEReactionInputHandler();
	exportJMEMolecularGraphOutputHandler();
	exportJMEReactionOutputHandler();
	exportMOLMoleculeInputHandler();
	exportMOLMolecularGraphOutputHandler();
	exportSDFMoleculeInputHandler();
	exportSDFMolecularGraphOutputHandler();
	exportRXNReactionInputHandler();
	exportRXNReactionOutputHandler();
	exportRDFReactionInputHandler();
	exportRDFReactionOutputHandler();
	exportSMILESMoleculeInputHandler();
	exportSMILESReactionInputHandler();
	exportSMILESMolecularGraphOutputHandler();
	exportSMILESReactionOutputHandler();
	exportSMARTSMoleculeInputHandler();
	exportSMARTSReactionInputHandler();
	exportSMARTSMolecularGraphOutputHandler();
	exportSMARTSReactionOutputHandler();
	exportMOL2MoleculeInputHandler();
	exportMOL2MolecularGraphOutputHandler();

	exportMolecularGraphProperties();
	exportEntity3DProperties();
	exportAtomProperties();
	exportBondProperties();
	exportReactionProperties();

	exportControlParameters();
	exportControlParameterDefaults();

	exportDataFormats();

	exportAtomPropertyFlags();
	exportBondPropertyFlags();
	exportReactionRoles();
	exportAtomTypes();
	exportAtomConfigurations();
	exportBondConfigurations();
	exportBondStereoFlags();
	exportHybridizationStates();
	exportReactionCenterStates();
	exportBondDirections();
	exportRadicalTypes();
	exportAtomMatchConstraints();
	exportBondMatchConstraints();
	exportMolecularGraphMatchConstraints();
	exportReactionMatchConstraints();
	exportINCHIReturnCodes();
	exportMDLDataFormatVersions();
	exportMDLParities();

	exportControlParameterFunctions();
	exportUtilityFunctions();
	exportAtomContainerFunctions();
	exportBondContainerFunctions();
	exportEntity3DContainerFunctions();
	exportEntity3DFunctions();
	exportAtomFunctions();
	exportBondFunctions();
	exportMolecularGraphFunctions();
	exportMoleculeFunctions();
	exportFragmentFunctions();
	exportReactionFunctions();
	exportSimilarityFunctions();

	exportBoostFunctionWrappers();

	registerToPythonConverters();
	registerFromPythonConverters();
}
