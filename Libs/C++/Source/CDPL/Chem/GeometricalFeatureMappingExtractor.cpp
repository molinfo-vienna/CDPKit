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

#include "CDPL/Chem/GeometricalFeatureMappingExtractor.hpp"
#include "CDPL/Chem/Pharmacophore.hpp"
#include "CDPL/Chem/Feature.hpp"
#include "CDPL/Chem/FeatureTypeMatchFunctor.hpp"
#include "CDPL/Chem/FeaturePositionMatchFunctor.hpp"
#include "CDPL/Chem/FeatureGeometryMatchFunctor.hpp"


using namespace CDPL; 


Chem::GeometricalFeatureMappingExtractor::GeometricalFeatureMappingExtractor(bool query_mode):
	typeMatchFunc(FeatureTypeMatchFunctor()), posMatchFunc(FeaturePositionMatchFunctor(query_mode)),
	geomMatchFunc(FeatureGeometryMatchFunctor(query_mode))
{}
	
void Chem::GeometricalFeatureMappingExtractor::setFeatureTypeMatchFunction(const FeatureTypeMatchFunction& func)
{
	typeMatchFunc = func;
}

const Chem::GeometricalFeatureMappingExtractor::FeatureTypeMatchFunction& 
Chem::GeometricalFeatureMappingExtractor::getFeatureTypeMatchFunction() const
{
	return typeMatchFunc;
}

void Chem::GeometricalFeatureMappingExtractor::setFeaturePositionMatchFunction(const FeaturePositionMatchFunction& func)
{
	posMatchFunc = func;
}

const Chem::GeometricalFeatureMappingExtractor::FeaturePositionMatchFunction& 
Chem::GeometricalFeatureMappingExtractor::getFeaturePositionMatchFunction() const
{
	return posMatchFunc;
}

void Chem::GeometricalFeatureMappingExtractor::setFeatureGeometryMatchFunction(const FeatureGeometryMatchFunction& func)
{
	geomMatchFunc = func;
}

const Chem::GeometricalFeatureMappingExtractor::FeatureGeometryMatchFunction& 
Chem::GeometricalFeatureMappingExtractor::getFeatureGeometryMatchFunction() const
{
	return geomMatchFunc;
}

void Chem::GeometricalFeatureMappingExtractor::getMapping(const Pharmacophore& ref_pharm, const Pharmacophore& pharm, Math::Matrix4D& xform, FeatureMapping& mapping) const
{
	mapping.clear();

    Pharmacophore::ConstFeatureIterator mpd_fts_beg = pharm.getFeaturesBegin(); 
    Pharmacophore::ConstFeatureIterator mpd_fts_end = pharm.getFeaturesEnd();

    for (Pharmacophore::ConstFeatureIterator ref_it = ref_pharm.getFeaturesBegin(), ref_end = ref_pharm.getFeaturesEnd(); ref_it != ref_end; ++ref_it) {
		const Feature& ref_ftr = *ref_it;

		for (Pharmacophore::ConstFeatureIterator mpd_it = mpd_fts_beg, mpd_end = mpd_fts_end; mpd_it != mpd_end; ++mpd_it) {
			const Feature& mpd_ftr = *mpd_it;

			if (typeMatchFunc && !typeMatchFunc(ref_ftr, mpd_ftr))
				continue;

			if (posMatchFunc && !posMatchFunc(ref_ftr, mpd_ftr, xform))
				continue;

			if (geomMatchFunc && !geomMatchFunc(ref_ftr, mpd_ftr, xform))
				continue;

			mapping.insertEntry(&ref_ftr, &mpd_ftr);
		}
	}
}
