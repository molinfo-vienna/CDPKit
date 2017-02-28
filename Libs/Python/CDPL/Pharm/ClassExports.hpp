/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ClassExports.hpp 
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


#ifndef CDPL_PYTHON_PHARM_CLASSEXPORTS_HPP
#define CDPL_PYTHON_PHARM_CLASSEXPORTS_HPP

#include "CDPL/Config.hpp"


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

	void exportBoostFunctionWrappers();

	void exportPharmacophoreIOManager();
	void exportFeatureContainerIOManager();
	void exportPharmacophoreReader();
	void exportFeatureContainerWriter();
	void exportPharmacophoreInputHandler();
	void exportFeatureContainerOutputHandler();

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

#if defined(HAVE_BOOST_SYSTEM) && defined(HAVE_BOOST_FILESYSTEM)

	void exportFileScreeningHitCollector();

#endif // defined(HAVE_BOOST_SYSTEM) && defined(HAVE_BOOST_FILESYSTEM)

#ifdef HAVE_SQLITE3
# if defined(HAVE_BOOST_SYSTEM) && defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)

	void exportPSDPharmacophoreInputHandler();
	void exportPSDMoleculeInputHandler();
	void exportPSDMolecularGraphOutputHandler();
	void exportPSDPharmacophoreReader();
	void exportPSDMoleculeReader();
	void exportPSDMolecularGraphWriter();

#endif // defined(HAVE_BOOST_SYSTEM) && defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)

	void exportPSDScreeningDBCreator();
	void exportPSDScreeningDBAccessor();

#endif // HAVE_SQLITE3

	void exportFeatureGenerator();
	void exportPharmacophoreGenerator();
	void exportDefaultPharmacophoreGenerator();
	void exportPatternBasedFeatureGenerator();
	void exportAromaticFeatureGenerator();
	void exportHydrophobicFeatureGenerator();
	void exportHBondAcceptorFeatureGenerator();
	void exportHBondDonorFeatureGenerator();
	void exportPosIonizableFeatureGenerator();
	void exportNegIonizableFeatureGenerator();
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

	void exportFeatureTypeMatchFunctor();
	void exportFeaturePairDistanceMatchFunctor();
	void exportFeaturePositionMatchFunctor();
	void exportFeatureGeometryMatchFunctor();
	void exportTopologicalEntityAlignment();
	void exportGeometricalEntityAlignment();
	void exportPharmacophoreAlignment();
	void exportGeometricalFeatureMappingExtractor();
}

#endif // CDPL_PYTHON_PHARM_CLASSEXPORTS_HPP
