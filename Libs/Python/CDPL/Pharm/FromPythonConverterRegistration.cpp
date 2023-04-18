/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FromPythonConverterRegistration.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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


#include <boost/function.hpp>

#include "CDPL/Pharm/FeaturePairDistanceMatchFunctor.hpp"
#include "CDPL/Pharm/FeaturePositionMatchFunctor.hpp"
#include "CDPL/Pharm/FeatureGeometryMatchFunctor.hpp"
#include "CDPL/Pharm/HBondingInteractionConstraint.hpp"
#include "CDPL/Pharm/XBondingInteractionConstraint.hpp"
#include "CDPL/Pharm/OrthogonalPiPiInteractionConstraint.hpp"
#include "CDPL/Pharm/CationPiInteractionConstraint.hpp"
#include "CDPL/Pharm/FeatureTypeMatchFunctor.hpp"
#include "CDPL/Pharm/ParallelPiPiInteractionConstraint.hpp"
#include "CDPL/Pharm/FeatureDistanceConstraint.hpp"
#include "CDPL/Pharm/InteractionConstraintConnector.hpp"
#include "CDPL/Pharm/PharmacophoreFitScreeningScore.hpp"
#include "CDPL/Pharm/FileScreeningHitCollector.hpp"
#include "CDPL/Pharm/HBondingInteractionScore.hpp"
#include "CDPL/Pharm/XBondingInteractionScore.hpp"
#include "CDPL/Pharm/OrthogonalPiPiInteractionScore.hpp"
#include "CDPL/Pharm/CationPiInteractionScore.hpp"
#include "CDPL/Pharm/ParallelPiPiInteractionScore.hpp"
#include "CDPL/Pharm/FeatureDistanceScore.hpp"
#include "CDPL/Pharm/FeatureInteractionScoreCombiner.hpp"

#include "Base/GenericFromPythonConverter.hpp"

#include "ConverterRegistration.hpp"


void CDPLPythonPharm::registerFromPythonConverters()
{
	using namespace CDPL;

	CDPLPythonBase::GenericFromPythonConverter<const Pharm::PharmacophoreFitScore&,
											   boost::function3<double, const Pharm::FeatureContainer&, const Pharm::FeatureContainer&, 
																const Math::Matrix4D&> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::PharmacophoreFitScreeningScore&,
											   boost::function1<double, const Pharm::ScreeningProcessor::SearchHit&> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::FileScreeningHitCollector&,
											   boost::function2<bool, const Pharm::ScreeningProcessor::SearchHit&, double> >();

	CDPLPythonBase::GenericFromPythonConverter<const Pharm::FeaturePairDistanceMatchFunctor&,
											   boost::function4<bool, const Pharm::Feature&, const Pharm::Feature&, 
																const Pharm::Feature&, const Pharm::Feature&> >();

	CDPLPythonBase::GenericFromPythonConverter<const Pharm::FeaturePositionMatchFunctor&, 
											   boost::function3<double, const Pharm::Feature&, 
																const Pharm::Feature&, const Math::Matrix4D&> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::FeatureGeometryMatchFunctor&, 
											   boost::function3<double, const Pharm::Feature&, 
																const Pharm::Feature&, const Math::Matrix4D&> >();

	CDPLPythonBase::GenericFromPythonConverter<const Pharm::XBondingInteractionConstraint&, 
											   boost::function2<bool, const Pharm::Feature&, const Pharm::Feature&> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::HBondingInteractionConstraint&, 
											   boost::function2<bool, const Pharm::Feature&, const Pharm::Feature&> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::OrthogonalPiPiInteractionConstraint&, 
											   boost::function2<bool, const Pharm::Feature&, const Pharm::Feature&> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::CationPiInteractionConstraint&, 
											   boost::function2<bool, const Pharm::Feature&, const Pharm::Feature&> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::FeatureTypeMatchFunctor&, 
											   boost::function2<bool, const Pharm::Feature&, const Pharm::Feature&> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::ParallelPiPiInteractionConstraint&, 
											   boost::function2<bool, const Pharm::Feature&, const Pharm::Feature&> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::FeatureDistanceConstraint&, 
											   boost::function2<bool, const Pharm::Feature&, const Pharm::Feature&> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::InteractionConstraintConnector&, 
											   boost::function2<bool, const Pharm::Feature&, const Pharm::Feature&> >();

	CDPLPythonBase::GenericFromPythonConverter<const Pharm::XBondingInteractionScore&, 
											   boost::function2<double, const Pharm::Feature&, const Pharm::Feature&> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::XBondingInteractionScore&, 
											   boost::function2<double, const Math::Vector3D&, const Pharm::Feature&> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::HBondingInteractionScore&, 
											   boost::function2<double, const Pharm::Feature&, const Pharm::Feature&> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::HBondingInteractionScore&, 
											   boost::function2<double, const Math::Vector3D&, const Pharm::Feature&> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::OrthogonalPiPiInteractionScore&, 
											   boost::function2<double, const Pharm::Feature&, const Pharm::Feature&> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::OrthogonalPiPiInteractionScore&, 
											   boost::function2<double, const Math::Vector3D&, const Pharm::Feature&> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::CationPiInteractionScore&, 
											   boost::function2<double, const Pharm::Feature&, const Pharm::Feature&> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::CationPiInteractionScore&, 
											   boost::function2<double, const Math::Vector3D&, const Pharm::Feature&> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::ParallelPiPiInteractionScore&, 
											   boost::function2<double, const Pharm::Feature&, const Pharm::Feature&> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::ParallelPiPiInteractionScore&, 
											   boost::function2<double, const Math::Vector3D&, const Pharm::Feature&> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::FeatureDistanceScore&, 
											   boost::function2<double, const Pharm::Feature&, const Pharm::Feature&> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::FeatureDistanceScore&, 
											   boost::function2<double, const Math::Vector3D&, const Pharm::Feature&> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::FeatureInteractionScoreCombiner&, 
											   boost::function2<double, const Pharm::Feature&, const Pharm::Feature&> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::FeatureInteractionScoreCombiner&, 
											   boost::function2<double, const Math::Vector3D&, const Pharm::Feature&> >();
}
