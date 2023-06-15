/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PharmacophoreAutoCorr3DDescriptorCalculator.cpp 
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


#include "StaticInit.hpp"

#include <functional>

#include "CDPL/Descr/PharmacophoreAutoCorr3DDescriptorCalculator.hpp"
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


CDPL::Descr::PharmacophoreAutoCorr3DDescriptorCalculator::PharmacophoreAutoCorr3DDescriptorCalculator(): weightFunc()
{
    setFeature3DCoordinatesFunction(&Chem::get3DCoordinates);
} 

CDPL::Descr::PharmacophoreAutoCorr3DDescriptorCalculator::PharmacophoreAutoCorr3DDescriptorCalculator(const Pharm::FeatureContainer& cntnr, Math::DVector& descr): weightFunc()
{
    setFeature3DCoordinatesFunction(&Chem::get3DCoordinates);
    calculate(cntnr, descr);
}

void CDPL::Descr::PharmacophoreAutoCorr3DDescriptorCalculator::setStartRadius(double start_radius)
{
    autoCorrCalculator.setStartRadius(start_radius);
}

double CDPL::Descr::PharmacophoreAutoCorr3DDescriptorCalculator::getStartRadius() const
{
    return autoCorrCalculator.getStartRadius();
}

void CDPL::Descr::PharmacophoreAutoCorr3DDescriptorCalculator::setRadiusIncrement(double radius_inc)
{
    autoCorrCalculator.setRadiusIncrement(radius_inc);
}

double CDPL::Descr::PharmacophoreAutoCorr3DDescriptorCalculator::getRadiusIncrement() const
{
    return autoCorrCalculator.getRadiusIncrement();
}

void CDPL::Descr::PharmacophoreAutoCorr3DDescriptorCalculator::setNumSteps(std::size_t num_steps)
{
    autoCorrCalculator.setNumSteps(num_steps);
}

std::size_t CDPL::Descr::PharmacophoreAutoCorr3DDescriptorCalculator::getNumSteps() const
{
    return autoCorrCalculator.getNumSteps();
}

void CDPL::Descr::PharmacophoreAutoCorr3DDescriptorCalculator::setFeature3DCoordinatesFunction(const Feature3DCoordinatesFunction& func)
{
    autoCorrCalculator.setEntity3DCoordinatesFunction(func);
}

void CDPL::Descr::PharmacophoreAutoCorr3DDescriptorCalculator::setFeaturePairWeightFunction(const FeaturePairWeightFunction& func)
{
    weightFunc = func;
}

void CDPL::Descr::PharmacophoreAutoCorr3DDescriptorCalculator::calculate(const Pharm::FeatureContainer& cntnr, Math::DVector& descr)
{
	using namespace std::placeholders;
	
	std::size_t sub_descr_size = autoCorrCalculator.getNumSteps() + 1;
	std::size_t num_ftr_types = sizeof(FEATURE_TYPES) / sizeof(unsigned int);

	descr.resize(sub_descr_size * num_ftr_types, false);

	for (std::size_t i = 0; i < num_ftr_types; i++) {
		if (weightFunc)
			autoCorrCalculator.setEntityPairWeightFunction(std::bind<double>(weightFunc, _1, _2, FEATURE_TYPES[i]));
		else
			autoCorrCalculator.setEntityPairWeightFunction(std::bind<double>(FeaturePairWeightFunc(), _1, _2, FEATURE_TYPES[i]));

		Math::VectorRange<Math::DVector> sub_descr(descr, Math::range(i * sub_descr_size, (i + 1) * sub_descr_size));

		autoCorrCalculator.calculate(cntnr.getFeaturesBegin(), cntnr.getFeaturesEnd(), sub_descr);
	}
}
