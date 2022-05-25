/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SpatialFeatureMapping.cpp 
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

#include "CDPL/Pharm/SpatialFeatureMapping.hpp"
#include "CDPL/Pharm/FeatureContainer.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureTypeMatchFunctor.hpp"
#include "CDPL/Pharm/FeaturePositionMatchFunctor.hpp"
#include "CDPL/Pharm/FeatureGeometryMatchFunctor.hpp"


using namespace CDPL; 


Pharm::SpatialFeatureMapping::SpatialFeatureMapping(bool query_mode):
	typeMatchFunc(FeatureTypeMatchFunctor()), posMatchFunc(FeaturePositionMatchFunctor(query_mode)),
	geomMatchFunc(FeatureGeometryMatchFunctor(query_mode))
{}
	
void Pharm::SpatialFeatureMapping::setTypeMatchFunction(const TypeMatchFunction& func)
{
	typeMatchFunc = func;
}

const Pharm::SpatialFeatureMapping::TypeMatchFunction& 
Pharm::SpatialFeatureMapping::getTypeMatchFunction() const
{
	return typeMatchFunc;
}

void Pharm::SpatialFeatureMapping::setPositionMatchFunction(const PositionMatchFunction& func)
{
	posMatchFunc = func;
}

const Pharm::SpatialFeatureMapping::PositionMatchFunction& 
Pharm::SpatialFeatureMapping::getPositionMatchFunction() const
{
	return posMatchFunc;
}

void Pharm::SpatialFeatureMapping::setGeometryMatchFunction(const GeometryMatchFunction& func)
{
	geomMatchFunc = func;
}

const Pharm::SpatialFeatureMapping::GeometryMatchFunction& 
Pharm::SpatialFeatureMapping::getGeometryMatchFunction() const
{
	return geomMatchFunc;
}

double Pharm::SpatialFeatureMapping::getPositionMatchScore(const Feature& ref_ftr, const Feature& aligned_ftr) const
{
	FeaturePairToScoreMap::const_iterator it = posMatchScores.find(FeaturePair(&ref_ftr, &aligned_ftr));

	if (it == posMatchScores.end())
		return 0.0;

	return it->second;
}

double Pharm::SpatialFeatureMapping::getGeometryMatchScore(const Feature& ref_ftr, const Feature& aligned_ftr) const
{
	FeaturePairToScoreMap::const_iterator it = geomMatchScores.find(FeaturePair(&ref_ftr, &aligned_ftr));

	if (it == geomMatchScores.end())
		return 0.0;

	return it->second;
}

void Pharm::SpatialFeatureMapping::perceive(const FeatureContainer& ref_ftrs, const FeatureContainer& aligned_ftrs, const Math::Matrix4D& xform)
{
	clear();

	posMatchScores.clear();
	geomMatchScores.clear();

    FeatureContainer::ConstFeatureIterator aligned_ftrs_beg = aligned_ftrs.getFeaturesBegin(); 
    FeatureContainer::ConstFeatureIterator aligned_ftrs_end = aligned_ftrs.getFeaturesEnd();

    for (FeatureContainer::ConstFeatureIterator it1 = ref_ftrs.getFeaturesBegin(), ref_end = ref_ftrs.getFeaturesEnd(); it1 != ref_end; ++it1) {
		const Feature& ref_ftr = *it1;

		for (FeatureContainer::ConstFeatureIterator it2 = aligned_ftrs_beg, mpd_end = aligned_ftrs_end; it2 != mpd_end; ++it2) {
			const Feature& aligned_ftr = *it2;

			if (typeMatchFunc && !typeMatchFunc(ref_ftr, aligned_ftr))
				continue;

			double pos_score = 0.0;

			if (posMatchFunc) {
				pos_score = posMatchFunc(ref_ftr, aligned_ftr, xform);

				if (pos_score <= 0.0) 
					continue;
			}

			double geom_score = 0.0;

			if (geomMatchFunc) {
				geom_score = geomMatchFunc(ref_ftr, aligned_ftr, xform);

				if (geom_score <= 0.0) 
					continue;
			}

			if (pos_score > 0.0)
				posMatchScores[FeaturePair(&ref_ftr, &aligned_ftr)] = pos_score;				

			if (geom_score > 0.0)
				geomMatchScores[FeaturePair(&ref_ftr, &aligned_ftr)] = geom_score;		

			insertEntry(&ref_ftr, &aligned_ftr);
		}
	}
}
