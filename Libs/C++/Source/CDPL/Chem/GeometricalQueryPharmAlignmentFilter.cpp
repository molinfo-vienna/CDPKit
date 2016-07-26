/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GeometricalQueryPharmAlignmentFilter.cpp 
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


#include "StaticInit.hpp"

#include "CDPL/Chem/GeometricalQueryPharmAlignmentFilter.hpp"
#include "CDPL/Chem/Pharmacophore.hpp"
#include "CDPL/Chem/Feature.hpp"
#include "CDPL/Chem/FeatureFunctions.hpp"


using namespace CDPL; 


Chem::GeometricalQueryPharmAlignmentFilter::GeometricalQueryPharmAlignmentFilter(const Pharmacophore& query, std::size_t max_omtd_ftrs):
    maxOmtdFeatures(max_omtd_ftrs)
{
	for (Pharmacophore::ConstFeatureIterator it = query.getFeaturesBegin(), end = query.getFeaturesEnd(); it != end; ++it) {
		const Feature& ftr = *it;

		if (getDisabledFlag(ftr) || getOptionalFlag(ftr))
			continue;

		checkedFeatures.push_back(&ftr);
    }
}

bool Chem::GeometricalQueryPharmAlignmentFilter::operator()(const FeatureMapping& mapping) const
{
	std::size_t num_omitted = 0;

	for (FeatureArray::const_iterator it = checkedFeatures.begin(), end = checkedFeatures.end();
		 it != end && num_omitted <= maxOmtdFeatures; ++it) {

		if (!mapping.getValue(*it, 0))
			num_omitted++;
	}

	return (num_omitted <= maxOmtdFeatures);
}
