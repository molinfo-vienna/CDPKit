/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * Pharm.hpp 
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

/**
 * \file
 * \brief A convenience header including everything that is defined in namespace CDPL::Pharm.
 */

#ifndef CDPL_PHARM_HPP
#define CDPL_PHARM_HPP

#include "CDPL/Config.hpp"      

#include "CDPL/Pharm/Feature.hpp"  
#include "CDPL/Pharm/BasicFeature.hpp"  
#include "CDPL/Pharm/FeatureContainer.hpp"  
#include "CDPL/Pharm/FeatureSet.hpp"  
#include "CDPL/Pharm/Pharmacophore.hpp"      
#include "CDPL/Pharm/BasicPharmacophore.hpp"  

#include "CDPL/Pharm/FeatureMapping.hpp"  
#include "CDPL/Pharm/FeatureTypeHistogram.hpp"  
#include "CDPL/Pharm/Feature3DCoordinatesFunction.hpp"  

#include "CDPL/Pharm/FeatureContainerProperty.hpp"  
#include "CDPL/Pharm/FeatureProperty.hpp"  
#include "CDPL/Pharm/FeatureContainerPropertyDefault.hpp"  
#include "CDPL/Pharm/FeaturePropertyDefault.hpp"  
#include "CDPL/Pharm/ControlParameter.hpp"  
#include "CDPL/Pharm/ControlParameterDefault.hpp"  
#include "CDPL/Pharm/DataFormat.hpp"
#include "CDPL/Pharm/AttributedGridProperty.hpp"
#include "CDPL/Pharm/AttributedGridPropertyDefault.hpp"

#include "CDPL/Pharm/FeatureType.hpp"  
#include "CDPL/Pharm/FeatureGeometry.hpp"  

#include "CDPL/Pharm/FeatureGenerator.hpp"  
#include "CDPL/Pharm/PatternBasedFeatureGenerator.hpp"  
#include "CDPL/Pharm/AromaticFeatureGenerator.hpp"  
#include "CDPL/Pharm/HydrophobicFeatureGenerator.hpp"  
#include "CDPL/Pharm/HydrophobicAtomFeatureGenerator.hpp"  
#include "CDPL/Pharm/HBondAcceptorFeatureGenerator.hpp"  
#include "CDPL/Pharm/HBondDonorFeatureGenerator.hpp"  
#include "CDPL/Pharm/PosIonizableFeatureGenerator.hpp"  
#include "CDPL/Pharm/NegIonizableFeatureGenerator.hpp"  
#include "CDPL/Pharm/PharmacophoreGenerator.hpp"  
#include "CDPL/Pharm/DefaultPharmacophoreGenerator.hpp"  
#include "CDPL/Pharm/InteractionAnalyzer.hpp"  
#include "CDPL/Pharm/DefaultInteractionAnalyzer.hpp"  
#include "CDPL/Pharm/InteractionConstraintConnector.hpp"  
#include "CDPL/Pharm/FeatureDistanceConstraint.hpp"  
#include "CDPL/Pharm/HydrophobicInteractionConstraint.hpp"  
#include "CDPL/Pharm/IonicInteractionConstraint.hpp"  
#include "CDPL/Pharm/OrthogonalPiPiInteractionConstraint.hpp"  
#include "CDPL/Pharm/ParallelPiPiInteractionConstraint.hpp"  
#include "CDPL/Pharm/CationPiInteractionConstraint.hpp"  
#include "CDPL/Pharm/HBondingInteractionConstraint.hpp"  

#include "CDPL/Pharm/InteractionScoreCombiner.hpp"  
#include "CDPL/Pharm/FeatureDistanceScore.hpp"  
#include "CDPL/Pharm/HydrophobicInteractionScore.hpp"  
#include "CDPL/Pharm/IonicInteractionScore.hpp"  
#include "CDPL/Pharm/HBondingInteractionScore.hpp"  
#include "CDPL/Pharm/OrthogonalPiPiInteractionScore.hpp"  
#include "CDPL/Pharm/ParallelPiPiInteractionScore.hpp"  
#include "CDPL/Pharm/CationPiInteractionScore.hpp"  
#include "CDPL/Pharm/InteractionScoreGridCalculator.hpp"  
#include "CDPL/Pharm/InteractionScoreGridSetCalculator.hpp"  
#include "CDPL/Pharm/DefaultInteractionScoreGridSetCalculator.hpp"  

#include "CDPL/Pharm/GeometricalFeatureMappingExtractor.hpp"  
#include "CDPL/Pharm/PharmacophoreAlignment.hpp"  
#include "CDPL/Pharm/FeatureTypeMatchFunctor.hpp"  
#include "CDPL/Pharm/FeaturePairDistanceMatchFunctor.hpp"  
#include "CDPL/Pharm/FeaturePositionMatchFunctor.hpp"  
#include "CDPL/Pharm/FeatureGeometryMatchFunctor.hpp"  

#include "CDPL/Pharm/PharmacophoreFitScore.hpp"

#include "CDPL/Pharm/CDFPharmacophoreInputHandler.hpp"
#include "CDPL/Pharm/PMLPharmacophoreInputHandler.hpp"
#include "CDPL/Pharm/CDFFeatureContainerOutputHandler.hpp"
#include "CDPL/Pharm/PMLFeatureContainerOutputHandler.hpp"

#include "CDPL/Pharm/CDFPharmacophoreReader.hpp"
#include "CDPL/Pharm/PMLPharmacophoreReader.hpp"
#include "CDPL/Pharm/CDFFeatureContainerWriter.hpp"
#include "CDPL/Pharm/PMLFeatureContainerWriter.hpp"

#include "CDPL/Pharm/ScreeningDBCreator.hpp"
#include "CDPL/Pharm/ScreeningDBAccessor.hpp"
#include "CDPL/Pharm/ScreeningProcessor.hpp"
#include "CDPL/Pharm/PharmacophoreFitScreeningScore.hpp"

#include "CDPL/Pharm/FeatureRDFCodeCalculator.hpp"
#include "CDPL/Pharm/FeatureAutoCorrelation3DVectorCalculator.hpp"
#include "CDPL/Pharm/PharmacophoreRDFDescriptorCalculator.hpp"
#include "CDPL/Pharm/PharmacophoreAutoCorr3DDescriptorCalculator.hpp"

#include "CDPL/Pharm/PharmacophoreFunctions.hpp"  
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/FeatureContainerFunctions.hpp"
#include "CDPL/Pharm/FeatureSetFunctions.hpp"
#include "CDPL/Pharm/AttributedGridFunctions.hpp"
#include "CDPL/Pharm/ControlParameterFunctions.hpp"

#if defined(HAVE_BOOST_FILESYSTEM)

#include "CDPL/Pharm/FileScreeningHitCollector.hpp"

#  if defined(HAVE_BOOST_IOSTREAMS)

#include "CDPL/Pharm/CDFGZPharmacophoreInputHandler.hpp"
#include "CDPL/Pharm/CDFBZ2PharmacophoreInputHandler.hpp"

#include "CDPL/Pharm/CDFGZFeatureContainerOutputHandler.hpp"
#include "CDPL/Pharm/CDFBZ2FeatureContainerOutputHandler.hpp"

#include "CDPL/Pharm/CDFGZPharmacophoreReader.hpp"
#include "CDPL/Pharm/CDFBZ2PharmacophoreReader.hpp"

#include "CDPL/Pharm/CDFGZFeatureContainerWriter.hpp"
#include "CDPL/Pharm/CDFBZ2FeatureContainerWriter.hpp"

#  endif // defined(HAVE_BOOST_IOSTREAMS)
#endif // defined(HAVE_BOOST_FILESYSTEM)

#ifdef HAVE_SQLITE3
# if defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)

#include "CDPL/Pharm/PSDPharmacophoreInputHandler.hpp"
#include "CDPL/Pharm/PSDMoleculeInputHandler.hpp"
#include "CDPL/Pharm/PSDMolecularGraphOutputHandler.hpp"

#include "CDPL/Pharm/PSDPharmacophoreReader.hpp"
#include "CDPL/Pharm/PSDMoleculeReader.hpp"
#include "CDPL/Pharm/PSDMolecularGraphWriter.hpp"

# endif // defined(HAVE_BOOST_FILESYSTEM) && defined(HAVE_BOOST_IOSTREAMS)

#include "CDPL/Pharm/PSDScreeningDBCreator.hpp"
#include "CDPL/Pharm/PSDScreeningDBAccessor.hpp"

#endif // HAVE_SQLITE3
#endif // CDPL_PHARM_HPP
