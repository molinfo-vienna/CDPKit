/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ScreeningProcessor.cpp 
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

#include <boost/math/special_functions/fpclassify.hpp>

#include "CDPL/Shape/ScreeningProcessor.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


Shape::ScreeningProcessor::ScreeningProcessor()
{
	init();
}

Shape::ScreeningProcessor::ScreeningProcessor(const Chem::MolecularGraph& query)
{
	init();
	addQuery(query);
}

Shape::ScreeningProcessor::~ScreeningProcessor()
{}

void Shape::ScreeningProcessor::setHitCallback(const HitCallbackFunction& func)
{
	hitCallback = func;
}

const Shape::ScreeningProcessor::HitCallbackFunction& Shape::ScreeningProcessor::getHitCallback() const
{
	return hitCallback;
}

const Shape::ScreeningSettings& Shape::ScreeningProcessor::getSettings() const
{
	return settings;
}

Shape::ScreeningSettings& Shape::ScreeningProcessor::getSettings()
{
	return settings;
}

void Shape::ScreeningProcessor::clearQuerySet()
{
	alignment.clearReferenceShapes();
	queryList.clear();
}

void Shape::ScreeningProcessor::addQuery(const Chem::MolecularGraph& molgraph)
{
	// TODO: apply settings

	shapeGen.generate(molgraph, shapes, false);
	alignment.addReferenceShapes(shapes, true);
	queryList.push_back(&molgraph);
}

std::size_t Shape::ScreeningProcessor::getQuerySetSize() const
{
	return queryList.size();
}

const Chem::MolecularGraph& Shape::ScreeningProcessor::getQuery(std::size_t idx) const
{
    if (idx >= queryList.size())
		throw Base::IndexError("ScreeningProcessor: query index out of bounds");

	return *queryList[idx];
}

Shape::ScreeningProcessor::ConstMolecularGraphIterator Shape::ScreeningProcessor::getQuerySetBegin() const
{
	return queryList.begin();
}

Shape::ScreeningProcessor::ConstMolecularGraphIterator Shape::ScreeningProcessor::getQuerySetEnd() const
{
	return queryList.end();
}

bool Shape::ScreeningProcessor::process(const Chem::MolecularGraph& molgraph)
{
	// TODO: apply settings

	shapeGen.generate(molgraph, shapes, false);
	
	if (!alignment.align(shapes))
		return false;

	if (hitCallback) {
		bool have_thresh = boost::math::isfinite(settings.getScoreThreshold());

		for (GaussianShapeAlignment::ConstResultIterator it = alignment.getResultsBegin(), end = alignment.getResultsEnd(); it != end; ++it) {
			const AlignmentResult& res = *it;

			if (have_thresh && res.getScore() < settings.getScoreThreshold())
				continue;

			hitCallback(*queryList[res.getReferenceShapeSetIndex()], molgraph, res);
		}
	}

	return true;
}

void Shape::ScreeningProcessor::init()
{
	alignment.calcSelfOverlaps(true);
	alignment.calcColorSelfOverlaps(true);
	alignment.setMaxOrder(1);
	alignment.getDefaultOverlapFunction().proximityOptimization(true);
	alignment.getDefaultOverlapFunction().fastExpFunction(true);

	shapeGen.includeHydrogens(false);
}
