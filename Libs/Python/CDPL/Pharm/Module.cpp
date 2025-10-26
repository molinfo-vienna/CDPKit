/* 
 * Module.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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


#include "Module.hpp"
#include "ClassExports.hpp"
#include "FunctionExports.hpp"
#include "NamespaceExports.hpp"
#include "ConverterRegistration.hpp"


BOOST_PYTHON_MODULE(_pharm)
{
    using namespace CDPLPythonPharm;

    CDPLPython::declareGILNotUsed();

    exportFeature();
    exportBasicFeature();
    exportFeatureContainer();
    exportFeatureSet();
    exportPharmacophore();
    exportBasicPharmacophore();

    exportFeatureMapping();
    exportFeatureTypeHistogram();

    exportPharmacophoreReader();
    exportFeatureContainerWriter();
    exportPharmacophoreInputHandler();
    exportFeatureContainerOutputHandler();
    exportPharmacophoreIOManager();
    exportFeatureContainerIOManager();

    exportCDFPharmacophoreInputHandler();
    exportCDFFeatureContainerOutputHandler();
    exportCDFPharmacophoreReader();
    exportCDFFeatureContainerWriter();

    exportPMLPharmacophoreInputHandler();
    exportPMLFeatureContainerOutputHandler();
    exportPMLPharmacophoreReader();
    exportPMLFeatureContainerWriter();

    exportPharmacophoreFitScore();

    exportScreeningDBCreator();
    exportScreeningDBAccessor();
    exportScreeningProcessor();
    exportPharmacophoreFitScreeningScore();

    exportFileScreeningHitCollector();

    exportPSDPharmacophoreInputHandler();
    exportPSDMoleculeInputHandler();
    exportPSDMolecularGraphOutputHandler();
    exportPSDPharmacophoreReader();
    exportPSDMoleculeReader();
    exportPSDMolecularGraphWriter();
    exportPSDScreeningDBCreator();
    exportPSDScreeningDBAccessor();

    exportFeatureGenerator();
    exportPharmacophoreGenerator();
    exportDefaultPharmacophoreGenerator();
    exportPatternBasedFeatureGenerator();
    exportAromaticFeatureGenerator();
    exportHydrophobicFeatureGenerator();
    exportHydrophobicAtomFeatureGenerator();
    exportHBondAcceptorFeatureGenerator();
    exportHBondDonorFeatureGenerator();
    exportPosIonizableFeatureGenerator();
    exportNegIonizableFeatureGenerator();
    exportXBondAcceptorFeatureGenerator();
    exportXBondDonorFeatureGenerator();
    exportInteractionAnalyzer();
    exportDefaultInteractionAnalyzer();
    exportInteractionConstraintConnector();
    exportFeatureDistanceConstraint();
    exportHydrophobicInteractionConstraint();
    exportIonicInteractionConstraint();
    exportOrthogonalPiPiInteractionConstraint();
    exportParallelPiPiInteractionConstraint();
    exportCationPiInteractionConstraint();
    exportHBondingInteractionConstraint();
    exportXBondingInteractionConstraint();
    exportInteractionPharmacophoreGenerator();

    exportFeatureInteractionScore();
    exportFeatureInteractionScoreCombiner();
    exportFeatureDistanceScore();
    exportHydrophobicInteractionScore();
    exportIonicInteractionScore();
    exportOrthogonalPiPiInteractionScore();
    exportParallelPiPiInteractionScore();
    exportCationPiInteractionScore();
    exportHBondingInteractionScore();
    exportXBondingInteractionScore();

    exportTopologicalEntityAlignment();
    exportPharmacophoreAlignment();
    exportSpatialFeatureMapping();
    exportFeatureTypeMatchFunctor();
    exportFeaturePairDistanceMatchFunctor();
    exportFeaturePositionMatchFunctor();
    exportFeatureGeometryMatchFunctor();

    exportFeatureContainerProperties();
    exportFeatureProperties();
    exportFeatureContainerPropertyDefaults();
    exportFeaturePropertyDefaults();

    exportControlParameters();
    exportControlParameterDefaults();

    exportDataFormats();
    exportFeatureTypes();
    exportFeatureGeometries();

    exportPharmacophoreFunctions();
    exportFeatureFunctions();
    exportFeatureContainerFunctions();
    exportFeatureSetFunctions();
    exportControlParameterFunctions();
    exportMoleculeFunctions();
    exportUtilityFunctions();
    
    exportFunctionWrappers();

    registerToPythonConverters();
    registerFromPythonConverters();
}
