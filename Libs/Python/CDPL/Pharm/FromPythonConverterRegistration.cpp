/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FromPythonConverterRegistration.cpp 
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


#include <boost/function.hpp>

#include "CDPL/Pharm/FeaturePairDistanceMatchFunctor.hpp"
#include "CDPL/Pharm/FeaturePositionMatchFunctor.hpp"
#include "CDPL/Pharm/FeatureGeometryMatchFunctor.hpp"
#include "CDPL/Pharm/HBondingInteractionConstraint.hpp"
#include "CDPL/Pharm/OrthogonalPiPiInteractionConstraint.hpp"
#include "CDPL/Pharm/CationPiInteractionConstraint.hpp"
#include "CDPL/Pharm/FeatureTypeMatchFunctor.hpp"
#include "CDPL/Pharm/ParallelPiPiInteractionConstraint.hpp"
#include "CDPL/Pharm/FeatureDistanceConstraint.hpp"
#include "CDPL/Pharm/InteractionConstraintConnector.hpp"
#include "CDPL/Pharm/PharmacophoreFitScreeningScore.hpp"
#include "CDPL/Pharm/FileScreeningHitCollector.hpp"

#include "Base/GenericFromPythonConverter.hpp"

#include "ConverterRegistration.hpp"


void CDPLPythonPharm::registerFromPythonConverters()
{
	using namespace CDPL;

	CDPLPythonBase::GenericFromPythonConverter<Pharm::PharmacophoreFitScore,
											   boost::function3<double, const Pharm::FeatureContainer&, const Pharm::FeatureContainer&, 
																const Math::Matrix4D&> >();
	CDPLPythonBase::GenericFromPythonConverter<Pharm::PharmacophoreFitScreeningScore,
											   boost::function1<double, const Pharm::ScreeningProcessor::SearchHit&> >();
	CDPLPythonBase::GenericFromPythonConverter<Pharm::FileScreeningHitCollector,
											   boost::function2<bool, const Pharm::ScreeningProcessor::SearchHit&, double> >();

	CDPLPythonBase::GenericFromPythonConverter<Pharm::FeaturePairDistanceMatchFunctor,
											   boost::function4<bool, const Pharm::Feature&, const Pharm::Feature&, 
																const Pharm::Feature&, const Pharm::Feature&> >();

	CDPLPythonBase::GenericFromPythonConverter<Pharm::FeaturePositionMatchFunctor, 
											   boost::function3<double, const Pharm::Feature&, 
																const Pharm::Feature&, const Math::Matrix4D&> >();
	CDPLPythonBase::GenericFromPythonConverter<Pharm::FeatureGeometryMatchFunctor, 
											   boost::function3<double, const Pharm::Feature&, 
																const Pharm::Feature&, const Math::Matrix4D&> >();

	CDPLPythonBase::GenericFromPythonConverter<Pharm::HBondingInteractionConstraint, 
											   boost::function2<bool, const Pharm::Feature&, const Pharm::Feature&> >();
	CDPLPythonBase::GenericFromPythonConverter<Pharm::OrthogonalPiPiInteractionConstraint, 
											   boost::function2<bool, const Pharm::Feature&, const Pharm::Feature&> >();
	CDPLPythonBase::GenericFromPythonConverter<Pharm::CationPiInteractionConstraint, 
											   boost::function2<bool, const Pharm::Feature&, const Pharm::Feature&> >();
	CDPLPythonBase::GenericFromPythonConverter<Pharm::FeatureTypeMatchFunctor, 
											   boost::function2<bool, const Pharm::Feature&, const Pharm::Feature&> >();
	CDPLPythonBase::GenericFromPythonConverter<Pharm::ParallelPiPiInteractionConstraint, 
											   boost::function2<bool, const Pharm::Feature&, const Pharm::Feature&> >();
	CDPLPythonBase::GenericFromPythonConverter<Pharm::FeatureDistanceConstraint, 
											   boost::function2<bool, const Pharm::Feature&, const Pharm::Feature&> >();

	CDPLPythonBase::GenericFromPythonConverter<Pharm::InteractionConstraintConnector, 
											   Pharm::InteractionConstraintConnector::ConstraintFunction>();
}
