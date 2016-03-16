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
	exportPharmacophore();
	exportFeature();
	exportBasicPharmacophore();
	exportBasicFeature();
	exportFragment();
	exportAtomMapping();
	exportBondMapping();
	exportAtomBondMapping();
	exportFragmentList();
	exportMDLDataBlock();
	exportMassComposition();
	exportElementHistogram();
	exportStereoDescriptor();
	exportMultiConfMoleculeInputProcessor();
	exportDefaultMultiConfMoleculeInputProcessor();

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

	exportCompleteRingSet();
	exportAromaticRingSet();
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
	exportPDBMoleculeReader();
	exportPDBMolecularGraphWriter();
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
	exportJMEMoleculeInputHandler();
	exportJMEReactionInputHandler();
	exportJMEMolecularGraphOutputHandler();
	exportJMEReactionOutputHandler();
	exportPDBMoleculeInputHandler();
	exportPDBMolecularGraphOutputHandler();
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

	exportMolecularGraphProperties();
	exportEntity3DProperties();
	exportAtomProperties();
	exportBondProperties();
	exportReactionProperties();
	exportPharmacophoreProperties();
	exportFeatureProperties();

	exportControlParameters();
	exportControlParameterDefaults();

	exportDataFormats();

	exportAtomPropertyFlags();
	exportBondPropertyFlags();
	exportReactionRoles();
	exportAtomTypes();
	exportResidueTypes();
	exportAtomConfigurations();
	exportBondConfigurations();
	exportBondStereoFlags();
	exportHybridizationStates();
	exportReactionCenterStates();
	exportBondDirections();
	exportRadicalTypes();
	exportFeatureTypes();
	exportFeatureGeometries();
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
	exportPharmacophoreFunctions();
	exportFeatureFunctions();
	exportSimilarityFunctions();
	exportAtomTypeFunctions();
	exportResidueFunctions();

	registerToPythonConverters();
	registerFromPythonConverters();
}
