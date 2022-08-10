/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PharmacophoreRDFDescriptorCalculator.cpp 
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


#include "StaticInit.hpp"

#include <boost/bind.hpp>

#include "CDPL/Descr/PharmacophoreRDFDescriptorCalculator.hpp"
#include "CDPL/Pharm/FeatureContainer.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureType.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"


using namespace CDPL;


namespace
{

	struct FeaturePairWeightFunc
	{

		double operator()(const Pharm::Feature& ftr1, const Pharm::Feature& ftr2, unsigned int slot_ftr_type) const {
			unsigned int ftr_type1 = getType(ftr1);
			unsigned int ftr_type2 = getType(ftr2);

			if (ftr_type1 == slot_ftr_type && ftr_type2 == slot_ftr_type)
				return 2;

			if (ftr_type1 == slot_ftr_type || ftr_type2 == slot_ftr_type)
				return 1;

			return 0;
		}
	};

	unsigned int FEATURE_TYPES[] = {
	    Pharm::FeatureType::HYDROPHOBIC,
		Pharm::FeatureType::AROMATIC,
		Pharm::FeatureType::NEGATIVE_IONIZABLE,
		Pharm::FeatureType::POSITIVE_IONIZABLE,
		Pharm::FeatureType::H_BOND_DONOR,
		Pharm::FeatureType::H_BOND_ACCEPTOR
	};
}


CDPL::Descr::PharmacophoreRDFDescriptorCalculator::PharmacophoreRDFDescriptorCalculator(): weightFunc()
{
    setFeature3DCoordinatesFunction(&Chem::get3DCoordinates);
} 

CDPL::Descr::PharmacophoreRDFDescriptorCalculator::PharmacophoreRDFDescriptorCalculator(const Pharm::FeatureContainer& cntnr, Math::DVector& descr): weightFunc()
{
    setFeature3DCoordinatesFunction(&Chem::get3DCoordinates);
    calculate(cntnr, descr);
}

void CDPL::Descr::PharmacophoreRDFDescriptorCalculator::setSmoothingFactor(double factor)
{
    rdfCalculator.setSmoothingFactor(factor);
}
		
double CDPL::Descr::PharmacophoreRDFDescriptorCalculator::getSmoothingFactor() const
{
    return rdfCalculator.getSmoothingFactor();
}

void CDPL::Descr::PharmacophoreRDFDescriptorCalculator::setScalingFactor(double factor)
{
    rdfCalculator.setScalingFactor(factor);
}

double CDPL::Descr::PharmacophoreRDFDescriptorCalculator::getScalingFactor() const
{
    return rdfCalculator.getScalingFactor();
}

void CDPL::Descr::PharmacophoreRDFDescriptorCalculator::setStartRadius(double start_radius)
{
    rdfCalculator.setStartRadius(start_radius);
}

double CDPL::Descr::PharmacophoreRDFDescriptorCalculator::getStartRadius() const
{
    return rdfCalculator.getStartRadius();
}

void CDPL::Descr::PharmacophoreRDFDescriptorCalculator::setRadiusIncrement(double radius_inc)
{
    rdfCalculator.setRadiusIncrement(radius_inc);
}

double CDPL::Descr::PharmacophoreRDFDescriptorCalculator::getRadiusIncrement() const
{
    return rdfCalculator.getRadiusIncrement();
}

void CDPL::Descr::PharmacophoreRDFDescriptorCalculator::setNumSteps(std::size_t num_steps)
{
    rdfCalculator.setNumSteps(num_steps);
}

std::size_t CDPL::Descr::PharmacophoreRDFDescriptorCalculator::getNumSteps() const
{
    return rdfCalculator.getNumSteps();
}

void CDPL::Descr::PharmacophoreRDFDescriptorCalculator::setFeature3DCoordinatesFunction(const Feature3DCoordinatesFunction& func)
{
    rdfCalculator.setEntity3DCoordinatesFunction(func);
}

void CDPL::Descr::PharmacophoreRDFDescriptorCalculator::setFeaturePairWeightFunction(const FeaturePairWeightFunction& func)
{
    weightFunc = func;
}

void CDPL::Descr::PharmacophoreRDFDescriptorCalculator::enableDistanceToIntervalCenterRounding(bool enable)
{
	rdfCalculator.enableDistanceToIntervalCenterRounding(enable);
}

bool CDPL::Descr::PharmacophoreRDFDescriptorCalculator::distanceToIntervalsCenterRoundingEnabled() const
{
	return rdfCalculator.distanceToIntervalsCenterRoundingEnabled();
}

void CDPL::Descr::PharmacophoreRDFDescriptorCalculator::calculate(const Pharm::FeatureContainer& cntnr, Math::DVector& descr)
{
	std::size_t sub_descr_size = rdfCalculator.getNumSteps() + 1;
	std::size_t num_ftr_types = sizeof(FEATURE_TYPES) / sizeof(unsigned int);

	descr.resize(sub_descr_size * num_ftr_types, false);

	for (std::size_t i = 0; i < num_ftr_types; i++) {
		if (weightFunc)
			rdfCalculator.setEntityPairWeightFunction(boost::bind<double>(weightFunc, _1, _2, FEATURE_TYPES[i]));
		else
			rdfCalculator.setEntityPairWeightFunction(boost::bind<double>(FeaturePairWeightFunc(), _1, _2, FEATURE_TYPES[i]));

		Math::VectorRange<Math::DVector> sub_descr(descr, Math::range(i * sub_descr_size, (i + 1) * sub_descr_size));

		rdfCalculator.calculate(cntnr.getFeaturesBegin(), cntnr.getFeaturesEnd(), sub_descr);
	}
}
