/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GeometricalFeatureMappingExtractor.cpp 
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

#include "CDPL/Pharm/GeometricalFeatureMappingExtractor.hpp"
#include "CDPL/Pharm/Pharmacophore.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureTypeMatchFunctor.hpp"
#include "CDPL/Pharm/FeaturePositionMatchFunctor.hpp"
#include "CDPL/Pharm/FeatureGeometryMatchFunctor.hpp"


using namespace CDPL; 


Pharm::GeometricalFeatureMappingExtractor::GeometricalFeatureMappingExtractor(bool query_mode):
	typeMatchFunc(FeatureTypeMatchFunctor()), posMatchFunc(FeaturePositionMatchFunctor(query_mode)),
	geomMatchFunc(FeatureGeometryMatchFunctor(query_mode))
{}
	
void Pharm::GeometricalFeatureMappingExtractor::setTypeMatchFunction(const TypeMatchFunction& func)
{
	typeMatchFunc = func;
}

const Pharm::GeometricalFeatureMappingExtractor::TypeMatchFunction& 
Pharm::GeometricalFeatureMappingExtractor::getTypeMatchFunction() const
{
	return typeMatchFunc;
}

void Pharm::GeometricalFeatureMappingExtractor::setPositionMatchFunction(const PositionMatchFunction& func)
{
	posMatchFunc = func;
}

const Pharm::GeometricalFeatureMappingExtractor::PositionMatchFunction& 
Pharm::GeometricalFeatureMappingExtractor::getPositionMatchFunction() const
{
	return posMatchFunc;
}

void Pharm::GeometricalFeatureMappingExtractor::setGeometryMatchFunction(const GeometryMatchFunction& func)
{
	geomMatchFunc = func;
}

const Pharm::GeometricalFeatureMappingExtractor::GeometryMatchFunction& 
Pharm::GeometricalFeatureMappingExtractor::getGeometryMatchFunction() const
{
	return geomMatchFunc;
}

double Pharm::GeometricalFeatureMappingExtractor::getPositionMatchScore(const Feature& ftr1, const Feature& ftr2) const
{
	FeaturePairToScoreMap::const_iterator it = posMatchScores.find(FeaturePair(&ftr1, &ftr2));

	if (it == posMatchScores.end())
		return 0.0;

	return it->second;
}

double Pharm::GeometricalFeatureMappingExtractor::getGeometryMatchScore(const Feature& ftr1, const Feature& ftr2) const
{
	FeaturePairToScoreMap::const_iterator it = geomMatchScores.find(FeaturePair(&ftr1, &ftr2));

	if (it == geomMatchScores.end())
		return 0.0;

	return it->second;
}

void Pharm::GeometricalFeatureMappingExtractor::getMapping(const Pharmacophore& ref_pharm, const Pharmacophore& pharm, const Math::Matrix4D& xform, FeatureMapping& mapping)
{
	mapping.clear();

	posMatchScores.clear();
	geomMatchScores.clear();

    Pharmacophore::ConstFeatureIterator mpd_fts_beg = pharm.getFeaturesBegin(); 
    Pharmacophore::ConstFeatureIterator mpd_fts_end = pharm.getFeaturesEnd();

    for (Pharmacophore::ConstFeatureIterator ref_it = ref_pharm.getFeaturesBegin(), ref_end = ref_pharm.getFeaturesEnd(); ref_it != ref_end; ++ref_it) {
		const Feature& ref_ftr = *ref_it;

		for (Pharmacophore::ConstFeatureIterator mpd_it = mpd_fts_beg, mpd_end = mpd_fts_end; mpd_it != mpd_end; ++mpd_it) {
			const Feature& mpd_ftr = *mpd_it;

			if (typeMatchFunc && !typeMatchFunc(ref_ftr, mpd_ftr))
				continue;

			double pos_score = 0.0;

			if (posMatchFunc) {
				pos_score = posMatchFunc(ref_ftr, mpd_ftr, xform);

				if (pos_score <= 0.0) 
					continue;
			}

			double geom_score = 0.0;

			if (geomMatchFunc) {
				geom_score = geomMatchFunc(ref_ftr, mpd_ftr, xform);

				if (geom_score <= 0.0) 
					continue;
			}

			if (pos_score > 0.0)
				posMatchScores[FeaturePair(&ref_ftr, &mpd_ftr)] = pos_score;				

			if (geom_score > 0.0)
				geomMatchScores[FeaturePair(&ref_ftr, &mpd_ftr)] = geom_score;		

			mapping.insertEntry(&ref_ftr, &mpd_ftr);
		}
	}
}
