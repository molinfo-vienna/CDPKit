/* 
 * ClassExports.hpp 
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


#ifndef CDPL_PYTHON_PHARM_CLASSEXPORTS_HPP
#define CDPL_PYTHON_PHARM_CLASSEXPORTS_HPP


namespace CDPLPythonPharm
{

    void exportFeature();
    void exportBasicFeature();
    void exportFeatureContainer();
    void exportFeatureSet();
    void exportPharmacophore();
    void exportBasicPharmacophore();

    void exportFeatureMapping();
    void exportFeatureTypeHistogram();

    void exportFunctionWrappers();

    void exportPharmacophoreReader();
    void exportFeatureContainerWriter();
    void exportPharmacophoreInputHandler();
    void exportFeatureContainerOutputHandler();
    void exportPharmacophoreIOManager();
    void exportFeatureContainerIOManager();

    void exportCDFPharmacophoreInputHandler();
    void exportCDFFeatureContainerOutputHandler();
    void exportCDFPharmacophoreReader();
    void exportCDFFeatureContainerWriter();

    void exportPMLPharmacophoreInputHandler();
    void exportPMLFeatureContainerOutputHandler();
    void exportPMLPharmacophoreReader();
    void exportPMLFeatureContainerWriter();

    void exportPharmacophoreFitScore();

    void exportScreeningDBCreator();
    void exportScreeningDBAccessor();
    void exportScreeningProcessor();
    void exportPharmacophoreFitScreeningScore();

    void exportFileScreeningHitCollector();

    void exportPSDPharmacophoreInputHandler();
    void exportPSDMoleculeInputHandler();
    void exportPSDMolecularGraphOutputHandler();
    void exportPSDPharmacophoreReader();
    void exportPSDMoleculeReader();
    void exportPSDMolecularGraphWriter();
    void exportPSDScreeningDBCreator();
    void exportPSDScreeningDBAccessor();

    void exportFeatureGenerator();
    void exportPharmacophoreGenerator();
    void exportDefaultPharmacophoreGenerator();
    void exportPatternBasedFeatureGenerator();
    void exportAromaticFeatureGenerator();
    void exportHydrophobicFeatureGenerator();
    void exportHydrophobicAtomFeatureGenerator();
    void exportHBondAcceptorFeatureGenerator();
    void exportHBondDonorFeatureGenerator();
    void exportPosIonizableFeatureGenerator();
    void exportNegIonizableFeatureGenerator();
    void exportXBondAcceptorFeatureGenerator();
    void exportXBondDonorFeatureGenerator();
    void exportInteractionAnalyzer();
    void exportDefaultInteractionAnalyzer();
    void exportInteractionConstraintConnector();
    void exportFeatureDistanceConstraint();
    void exportHydrophobicInteractionConstraint();
    void exportIonicInteractionConstraint();
    void exportOrthogonalPiPiInteractionConstraint();
    void exportParallelPiPiInteractionConstraint();
    void exportCationPiInteractionConstraint();
    void exportHBondingInteractionConstraint();
    void exportXBondingInteractionConstraint();
    void exportInteractionPharmacophoreGenerator();

    void exportFeatureInteractionScore();
    void exportFeatureInteractionScoreCombiner();
    void exportFeatureDistanceScore();
    void exportHydrophobicInteractionScore();
    void exportIonicInteractionScore();
    void exportOrthogonalPiPiInteractionScore();
    void exportParallelPiPiInteractionScore();
    void exportCationPiInteractionScore();
    void exportHBondingInteractionScore();
    void exportXBondingInteractionScore();

    void exportFeatureTypeMatchFunctor();
    void exportFeaturePairDistanceMatchFunctor();
    void exportFeaturePositionMatchFunctor();
    void exportFeatureGeometryMatchFunctor();
    void exportTopologicalEntityAlignment();
    void exportPharmacophoreAlignment();
    void exportSpatialFeatureMapping();
} // namespace CDPLPythonPharm

#endif // CDPL_PYTHON_PHARM_CLASSEXPORTS_HPP
