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


namespace
{

	const double CARBON_RADIUS = 1.7;
}


Shape::ScreeningProcessor::ScreeningProcessor():
	colorFtrType(ScreeningSettings::DEFAULT.getColorFeatureType()), 
	multiConfQuery(ScreeningSettings::DEFAULT.multiConformerQuery()),
	allCarbon(ScreeningSettings::DEFAULT.allCarbonMode()),
    expChgPharmGen(false)
{
	init();
}

Shape::ScreeningProcessor::ScreeningProcessor(const Chem::MolecularGraph& query):
	colorFtrType(ScreeningSettings::DEFAULT.getColorFeatureType()), 
	multiConfQuery(ScreeningSettings::DEFAULT.multiConformerQuery()),
	allCarbon(ScreeningSettings::DEFAULT.allCarbonMode()),
    expChgPharmGen(false)
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
	applyShapeGenSettings(true);

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
	applyShapeGenSettings(false);
	applyAlignmentSettings();

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

void Shape::ScreeningProcessor::applyShapeGenSettings(bool query)
{
	using namespace Pharm;

	bool query_changed = false;

	if (allCarbon != settings.allCarbonMode()) {
		query_changed = true;
		allCarbon = settings.allCarbonMode();
	}

	shapeGen.setAtomRadius(allCarbon ? CARBON_RADIUS : -1.0);

	if (multiConfQuery != settings.multiConformerQuery()) {
		query_changed = true;
		multiConfQuery = settings.multiConformerQuery();
	}

	if (colorFtrType != settings.getColorFeatureType()) {
		query_changed = true;
		colorFtrType = settings.getColorFeatureType();
	}

	switch (colorFtrType) {

		case ScreeningSettings::PHARMACOPHORE_EXP_CHARGES:
			shapeGen.setPharmacophoreGenerator(expChgPharmGen);
			shapeGen.generatePharmacophoreShape(true);
			break;

		case ScreeningSettings::PHARMACOPHORE_IMP_CHARGES:
			shapeGen.setPharmacophoreGenerator(shapeGen.getDefaultPharmacophoreGenerator());
			shapeGen.generatePharmacophoreShape(true);
			break;
				
		default:
			shapeGen.generatePharmacophoreShape(false);
			break;
	}

	if (query_changed) {
		shapeGen.multiConformerMode(multiConfQuery);
		alignment.clearReferenceShapes();

		for (MolecularGraphList::const_iterator it = queryList.begin(), end = queryList.end(); it != end; ++it) {
			shapeGen.generate(**it, shapes, false);
			alignment.addReferenceShapes(shapes, true);
		}
	}

	shapeGen.multiConformerMode(query ? multiConfQuery : true);
}

void Shape::ScreeningProcessor::applyAlignmentSettings()
{
	alignment.setScoringFunction(settings.getScoringFunction());
	alignment.optimizeOverlap(settings.optimizeOverlap());
	alignment.greedyOptimization(settings.greedyOptimization());
	alignment.setMaxNumOptimizationIterations(settings.getMaxNumOptimizationIterations());
	alignment.setOptimizationStopGradient(settings.getOptimizationStopGradient());

	int almnt_mode = PrincipalAxesAlignmentStartGenerator::UNDEF;

	switch (int(settings.getAlignmentMode())) {

		case ScreeningSettings::SHAPE_CENTROID:
			almnt_mode = PrincipalAxesAlignmentStartGenerator::SHAPE_CENTROID;
			break;

		case ScreeningSettings::ATOM_CENTERS:
			almnt_mode = (PrincipalAxesAlignmentStartGenerator::NON_COLOR_ELEMENT_CENTERS |
						  PrincipalAxesAlignmentStartGenerator::LARGEST_SHAPE);
			break;

		case ScreeningSettings::COLOR_FEATURE_CENTERS:
			almnt_mode = (PrincipalAxesAlignmentStartGenerator::COLOR_ELEMENT_CENTERS |
						  PrincipalAxesAlignmentStartGenerator::LARGEST_SHAPE);
			break;

		case (ScreeningSettings::SHAPE_CENTROID | ScreeningSettings::ATOM_CENTERS):
			almnt_mode = (PrincipalAxesAlignmentStartGenerator::SHAPE_CENTROID |
						  PrincipalAxesAlignmentStartGenerator::NON_COLOR_ELEMENT_CENTERS |
						  PrincipalAxesAlignmentStartGenerator::LARGEST_SHAPE);
			break;

		case (ScreeningSettings::SHAPE_CENTROID | ScreeningSettings::COLOR_FEATURE_CENTERS):
			almnt_mode =(PrincipalAxesAlignmentStartGenerator::SHAPE_CENTROID |
						 PrincipalAxesAlignmentStartGenerator::COLOR_ELEMENT_CENTERS |
						 PrincipalAxesAlignmentStartGenerator::LARGEST_SHAPE);
			break;

		case (ScreeningSettings::ATOM_CENTERS | ScreeningSettings::COLOR_FEATURE_CENTERS):
			almnt_mode = (PrincipalAxesAlignmentStartGenerator::NON_COLOR_ELEMENT_CENTERS |
						  PrincipalAxesAlignmentStartGenerator::COLOR_ELEMENT_CENTERS |
						  PrincipalAxesAlignmentStartGenerator::LARGEST_SHAPE);
			break;

		case (ScreeningSettings::SHAPE_CENTROID | ScreeningSettings::ATOM_CENTERS | ScreeningSettings::COLOR_FEATURE_CENTERS):
			almnt_mode = (PrincipalAxesAlignmentStartGenerator::SHAPE_CENTROID |
						  PrincipalAxesAlignmentStartGenerator::NON_COLOR_ELEMENT_CENTERS |
						  PrincipalAxesAlignmentStartGenerator::COLOR_ELEMENT_CENTERS |
						  PrincipalAxesAlignmentStartGenerator::LARGEST_SHAPE);
		default:
			break;
	}

	if (almnt_mode != PrincipalAxesAlignmentStartGenerator::UNDEF) {
		alignment.performAlignment(true);
		alignment.getDefaultStartGenerator().setCenterAlignmentMode(PrincipalAxesAlignmentStartGenerator::CenterAlignmentMode(almnt_mode));

	} else
		alignment.performAlignment(false);

	switch (settings.getScreeningMode()) {

		case ScreeningSettings::BEST_OVERALL_MATCH:
			alignment.setResultSelectionMode(GaussianShapeAlignment::BEST_OVERALL);
			break;

		case ScreeningSettings::BEST_MATCH_PER_QUERY_CONF:
			alignment.setResultSelectionMode(GaussianShapeAlignment::BEST_PER_REFERENCE_SHAPE);
			break;

		default:
			alignment.setResultSelectionMode(GaussianShapeAlignment::BEST_PER_REFERENCE_SET);
			break;
	}
}
