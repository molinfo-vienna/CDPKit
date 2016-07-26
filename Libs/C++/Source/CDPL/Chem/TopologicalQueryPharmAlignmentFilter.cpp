/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TopologicalQueryPharmAlignmentFilter.cpp 
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

#include "CDPL/Chem/TopologicalQueryPharmAlignmentFilter.hpp"
#include "CDPL/Chem/Pharmacophore.hpp"
#include "CDPL/Chem/Feature.hpp"
#include "CDPL/Chem/FeatureFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"


using namespace CDPL; 


Chem::TopologicalQueryPharmAlignmentFilter::TopologicalQueryPharmAlignmentFilter(const Pharmacophore& query, std::size_t max_omtd_ftrs):
    maxOmtdFeatures(max_omtd_ftrs)
{
	for (Pharmacophore::ConstFeatureIterator it = query.getFeaturesBegin(), end = query.getFeaturesEnd(); it != end; ++it) {
		const Feature& ftr = *it;

		if (getDisabledFlag(ftr) || getOptionalFlag(ftr))
			continue;

		unsigned int ftr_type = getType(ftr);
		const Math::Vector3D& ftr_pos = get3DCoordinates(ftr);
		FeatureArray::iterator ar_it = checkedFeatures.begin();

		for (FeatureArray::iterator ar_end = checkedFeatures.end(); 
			 ar_it != ar_end && (getType(**ar_it) != ftr_type || get3DCoordinates(**ar_it) != ftr_pos); ++ar_it);

		checkedFeatures.insert(ar_it, &ftr);
    }

	FeatureArray::const_iterator ftrs_beg = checkedFeatures.begin();

	for (FeatureArray::const_iterator it = ftrs_beg, end = checkedFeatures.end(); it != end; ) {
		const Feature& ftr = **it;
		unsigned int ftr_type = getType(ftr);
		const Math::Vector3D& ftr_pos = get3DCoordinates(ftr);

		for (++it; it != end && getType(**it) == ftr_type && get3DCoordinates(**it) == ftr_pos; ++it);

		ftrGroupLimits.push_back(it - ftrs_beg);
	}
}

bool Chem::TopologicalQueryPharmAlignmentFilter::operator()(const FeatureMapping& mapping) const
{
	std::size_t num_omitted = 0;
	std::size_t num_ftr_groups = ftrGroupLimits.size();

	for (std::size_t i = 0, j = 0; i < num_ftr_groups && num_omitted <= maxOmtdFeatures; j = ftrGroupLimits[i], i++) {
		for ( ; j < ftrGroupLimits[i]; j++)
			if (mapping.getValue(checkedFeatures[j], 0))
				break;

		if (j == ftrGroupLimits[i])
			num_omitted++;
	}

	return (num_omitted <= maxOmtdFeatures);
}
