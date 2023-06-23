/* 
 * FromPythonConverterRegistration.cpp 
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


#include <functional>

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
											   std::function<double(const Pharm::FeatureContainer&, const Pharm::FeatureContainer&, const Math::Matrix4D&)> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::PharmacophoreFitScreeningScore&,
											   std::function<double(const Pharm::ScreeningProcessor::SearchHit&)> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::FileScreeningHitCollector&,
											   std::function<bool(const Pharm::ScreeningProcessor::SearchHit&, double)> >();

	CDPLPythonBase::GenericFromPythonConverter<const Pharm::FeaturePairDistanceMatchFunctor&,
											   std::function<bool(const Pharm::Feature&, const Pharm::Feature&, const Pharm::Feature&, const Pharm::Feature&)> >();

	CDPLPythonBase::GenericFromPythonConverter<const Pharm::FeaturePositionMatchFunctor&, 
											   std::function<double(const Pharm::Feature&, const Pharm::Feature&, const Math::Matrix4D&)> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::FeatureGeometryMatchFunctor&, 
											   std::function<double(const Pharm::Feature&, const Pharm::Feature&, const Math::Matrix4D&)> >();

	CDPLPythonBase::GenericFromPythonConverter<const Pharm::XBondingInteractionConstraint&, 
											   std::function<bool(const Pharm::Feature&, const Pharm::Feature&)> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::HBondingInteractionConstraint&, 
											   std::function<bool(const Pharm::Feature&, const Pharm::Feature&)> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::OrthogonalPiPiInteractionConstraint&, 
											   std::function<bool(const Pharm::Feature&, const Pharm::Feature&)> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::CationPiInteractionConstraint&, 
											   std::function<bool(const Pharm::Feature&, const Pharm::Feature&)> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::FeatureTypeMatchFunctor&, 
											   std::function<bool(const Pharm::Feature&, const Pharm::Feature&)> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::ParallelPiPiInteractionConstraint&, 
											   std::function<bool(const Pharm::Feature&, const Pharm::Feature&)> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::FeatureDistanceConstraint&, 
											   std::function<bool(const Pharm::Feature&, const Pharm::Feature&)> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::InteractionConstraintConnector&, 
											   std::function<bool(const Pharm::Feature&, const Pharm::Feature&)> >();

	CDPLPythonBase::GenericFromPythonConverter<const Pharm::XBondingInteractionScore&, 
											   std::function<double(const Pharm::Feature&, const Pharm::Feature&)> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::XBondingInteractionScore&, 
											   std::function<double(const Math::Vector3D&, const Pharm::Feature&)> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::HBondingInteractionScore&, 
											   std::function<double(const Pharm::Feature&, const Pharm::Feature&)> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::HBondingInteractionScore&, 
											   std::function<double(const Math::Vector3D&, const Pharm::Feature&)> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::OrthogonalPiPiInteractionScore&, 
											   std::function<double(const Pharm::Feature&, const Pharm::Feature&)> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::OrthogonalPiPiInteractionScore&, 
											   std::function<double(const Math::Vector3D&, const Pharm::Feature&)> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::CationPiInteractionScore&, 
											   std::function<double(const Pharm::Feature&, const Pharm::Feature&)> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::CationPiInteractionScore&, 
											   std::function<double(const Math::Vector3D&, const Pharm::Feature&)> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::ParallelPiPiInteractionScore&, 
											   std::function<double(const Pharm::Feature&, const Pharm::Feature&)> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::ParallelPiPiInteractionScore&, 
											   std::function<double(const Math::Vector3D&, const Pharm::Feature&)> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::FeatureDistanceScore&, 
											   std::function<double(const Pharm::Feature&, const Pharm::Feature&)> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::FeatureDistanceScore&, 
											   std::function<double(const Math::Vector3D&, const Pharm::Feature&)> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::FeatureInteractionScoreCombiner&, 
											   std::function<double(const Pharm::Feature&, const Pharm::Feature&)> >();
	CDPLPythonBase::GenericFromPythonConverter<const Pharm::FeatureInteractionScoreCombiner&, 
											   std::function<double(const Math::Vector3D&, const Pharm::Feature&)> >();
}
