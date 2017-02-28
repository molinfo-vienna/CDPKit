/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ScreeningProcessorImpl.cpp 
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

#include <algorithm>
#include <functional>
#include <limits>
#include <cmath>
#include <iterator>
#include <cassert>

#include <boost/bind.hpp>

#include "CDPL/Pharm/ScreeningDBAccessor.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/PharmacophoreFunctions.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/FeatureType.hpp"
#include "CDPL/Pharm/PharmacophoreFitScreeningScore.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/Entity3DContainerFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Math/VectorArrayFunctions.hpp"
#include "CDPL/Math/VectorAdapter.hpp"

#include "ScreeningProcessorImpl.hpp"


using namespace CDPL;


namespace
{

    const double NAN_SCORE         = std::numeric_limits<double>::quiet_NaN();
    const double VDW_RADIUS_FACTOR = 0.5;

	struct FeatureTolCmpFunc : public std::binary_function<const Pharm::Feature*, const Pharm::Feature*, bool> 
	{

		bool operator()(const Pharm::Feature* ftr1, const Pharm::Feature* ftr2) const {
			return (getTolerance(*ftr1) < getTolerance(*ftr2));
		}
	};
}


Pharm::ScreeningProcessorImpl::ScreeningProcessorImpl(ScreeningProcessor& parent, ScreeningDBAccessor& db_acc): 
	parent(&parent), dbAccessor(&db_acc), reportMode(ScreeningProcessor::FIRST_MATCHING_CONF), maxOmittedFeatures(0),
	checkXVolumes(true), bestAlignments(false), hitCallback(), progressCallback(), 
	scoringFunction(PharmacophoreFitScreeningScore()), featureGeomMatchFunction(false), pharmAlignment(true)
{
	pharmAlignment.setTopAlignmentConstraintFunction(
		boost::bind(&ScreeningProcessorImpl::checkTopologicalMapping, this, _1));
	pharmAlignment.setEntity3DCoordinatesFunction(
		boost::bind(&ScreeningProcessorImpl::getFeatureCoordinates, this, _1));
}

void Pharm::ScreeningProcessorImpl::setDBAccessor(ScreeningDBAccessor& db_acc)
{
	dbAccessor = &db_acc;
}

Pharm::ScreeningDBAccessor& Pharm::ScreeningProcessorImpl::getDBAccessor() const
{
	return *dbAccessor;
}

void Pharm::ScreeningProcessorImpl::setHitReportMode(ScreeningProcessor::HitReportMode mode)
{
	reportMode = mode;
}

Pharm::ScreeningProcessor::HitReportMode Pharm::ScreeningProcessorImpl::getHitReportMode() const
{
	return reportMode;
}

void Pharm::ScreeningProcessorImpl::setMaxNumOmittedFeatures(std::size_t max_num)
{
	maxOmittedFeatures = max_num;
}

std::size_t Pharm::ScreeningProcessorImpl::getMaxNumOmittedFeatures() const
{
	return maxOmittedFeatures;
}

void Pharm::ScreeningProcessorImpl::checkXVolumeClashes(bool check)
{
	checkXVolumes = check;
}

bool Pharm::ScreeningProcessorImpl::xVolumeClashesChecked() const
{
	return checkXVolumes;
}

void Pharm::ScreeningProcessorImpl::seekBestAlignments(bool seek_best)
{
	bestAlignments = seek_best;
}

bool Pharm::ScreeningProcessorImpl::bestAlignmentsSeeked() const
{
	return bestAlignments;
}

void Pharm::ScreeningProcessorImpl::setHitCallbackFunction(const HitCallbackFunction& func)
{
	hitCallback = func;
}

const Pharm::ScreeningProcessor::HitCallbackFunction& Pharm::ScreeningProcessorImpl::getHitCallbackFunction() const
{
	return hitCallback;
}

void Pharm::ScreeningProcessorImpl::setProgressCallbackFunction(const ProgressCallbackFunction& func)
{
	progressCallback = func;
}

const Pharm::ScreeningProcessor::ProgressCallbackFunction& Pharm::ScreeningProcessorImpl::getProgressCallbackFunction() const
{
	return progressCallback;
}

void Pharm::ScreeningProcessorImpl::setScoringFunction(const ScoringFunction& func)
{
	scoringFunction = func;
}

const Pharm::ScreeningProcessor::ScoringFunction& Pharm::ScreeningProcessorImpl::getScoringFunction() const
{
	return scoringFunction;
}

std::size_t Pharm::ScreeningProcessorImpl::searchDB(const FeatureContainer& query, std::size_t mol_start_idx, 
													std::size_t mol_end_idx)
{
	prepareDBSearch(query, mol_start_idx, mol_end_idx);

	std::size_t num_pharm_entries = pharmIndices.size();

	for (std::size_t i = 0; i <= num_pharm_entries; i++) {
		if (reportMode == ScreeningProcessor::BEST_MATCHING_CONF && !std::isnan(bestConfAlmntScore) &&
			(i == num_pharm_entries || pharmIndices[i].second != bestConfAlmntMolIdx)) {
			
			if (!reportHit(SearchHit(*parent, query, dbPharmacophore, dbMolecule, bestConfAlmntTransform,
									 bestConfAlmntPharmIdx, bestConfAlmntMolIdx, bestConfAlmntConfIdx),
						   bestConfAlmntScore))
				return numHits;
		}

		if (progressCallback && !progressCallback(i, num_pharm_entries))
			return numHits;

		if (i == num_pharm_entries)
			continue;

		std::size_t mol_idx = pharmIndices[i].second;

		if (reportMode == ScreeningProcessor::FIRST_MATCHING_CONF && molHitSet.test(mol_idx)) 
			continue;

		std::size_t pharm_idx = pharmIndices[i].first;

		if (!checkFeatureCounts(pharm_idx))
			continue;

		if (!check2PointPharmacophores(pharm_idx))
			continue;

		if (!performAlignment(pharm_idx, mol_idx))
			return numHits;
	}

	return numHits;
}

void Pharm::ScreeningProcessorImpl::prepareDBSearch(const FeatureContainer& query, std::size_t mol_start_idx, 
													std::size_t mol_end_idx)
{
	initQueryData(query);

	numHits = 0;
	loadedPharmIndex = dbAccessor->getNumPharmacophores();
	loadedMolIndex = dbAccessor->getNumMolecules();

	if (reportMode == ScreeningProcessor::FIRST_MATCHING_CONF) {
		molHitSet.resize(loadedMolIndex);
		molHitSet.reset();

	} else if (reportMode == ScreeningProcessor::BEST_MATCHING_CONF)
		bestConfAlmntScore = NAN_SCORE;

	initPharmIndexList(mol_start_idx, mol_end_idx);
}

void Pharm::ScreeningProcessorImpl::initQueryData(const FeatureContainer& query)
{
	queryPharmacophore = &query;

	queryMandFeatures.clear();
	queryMandFeatureTypes.clear();
	queryOptFeatures.clear();
	alignedQueryMandFeatures.clear();
	queryFeatureCounts.clear();
	queryFeatureTolerances.clear();
	queryFeaturePositions.clear();
	pharmAlignment.clearEntities(true);
	xVolumeIndices.clear();

	for (FeatureContainer::ConstFeatureIterator it = query.getFeaturesBegin(), end = query.getFeaturesEnd(); it != end; ++it) {
		const Feature& ftr = *it;

		queryFeatureTolerances.push_back(getTolerance(ftr));
		queryFeaturePositions.addElement(get3DCoordinates(ftr));

		if (getDisabledFlag(ftr))
			continue;

		if (getType(ftr) == FeatureType::X_VOLUME) {
			if (getOptionalFlag(ftr))
				continue;

			xVolumeIndices.push_back(ftr.getIndex());
			continue;
		}

		if (getOptionalFlag(ftr))
			insertFeature(ftr, queryOptFeatures);
		else
			insertFeature(ftr, queryMandFeatures);
	}

	for (FeatureMatrix::iterator it = queryMandFeatures.begin(), end = queryMandFeatures.end(); it != end; ++it) {
		FeatureList& ftr_list = *it; assert(!ftr_list.empty());		
		const Feature& max_tol_ftr = **std::max_element(ftr_list.begin(), ftr_list.end(), FeatureTolCmpFunc());
		unsigned int type = getType(max_tol_ftr);

		pharmAlignment.addEntity(max_tol_ftr, true);
		alignedQueryMandFeatures.push_back(&max_tol_ftr);
		queryMandFeatureTypes.push_back(type);
		queryFeatureCounts[type]++;
	}

	for (FeatureMatrix::iterator it = queryOptFeatures.begin(), end = queryOptFeatures.end(); it != end; ++it) {
		FeatureList& ftr_list = *it; assert(!ftr_list.empty());		
		const Feature& max_tol_ftr = **std::max_element(ftr_list.begin(), ftr_list.end(), FeatureTolCmpFunc());
		
		pharmAlignment.addEntity(max_tol_ftr, true);
		alignedQueryOptFeatures.push_back(&max_tol_ftr);
	}

	query2PointPharmList.clear();

	query2PointPharmGen.generate(FeatureListIterator(alignedQueryMandFeatures.begin()),
								 FeatureListIterator(alignedQueryMandFeatures.end()),
								 std::back_inserter(query2PointPharmList));

	std::size_t min_num_ftrs = (queryMandFeatures.size() > maxOmittedFeatures ? 
								std::size_t(queryMandFeatures.size() - maxOmittedFeatures) : std::size_t(0));

	minNum2PointPharmMatches = (min_num_ftrs < 2 ? std::size_t(0) : (min_num_ftrs * (min_num_ftrs - 1)) / 2);

	pharmAlignment.setMinTopologicalMappingSize(min_num_ftrs);
}

void Pharm::ScreeningProcessorImpl::insertFeature(const Feature& ftr, FeatureMatrix& ftr_mtx) const
{
	unsigned int ftr_type = getType(ftr);
	const Math::Vector3D& ftr_pos = get3DCoordinates(ftr);

	for (FeatureMatrix::iterator it = ftr_mtx.begin(), end = ftr_mtx.end(); it != end; ++it) {
		FeatureList& ftr_list = *it;
		const Feature& first_ftr = *ftr_list.front();

		if (getType(first_ftr) != ftr_type)
			continue;

		if (ftr_pos == get3DCoordinates(first_ftr)) {
			ftr_list.push_back(&ftr);
			return;
		}
	}

	ftr_mtx.resize(ftr_mtx.size() + 1);
	ftr_mtx.back().push_back(&ftr);
}

void Pharm::ScreeningProcessorImpl::initPharmIndexList(std::size_t mol_start_idx, std::size_t mol_end_idx)
{
	if (mol_end_idx == 0)
		mol_end_idx = dbAccessor->getNumMolecules();

	pharmIndices.clear();

	std::size_t num_pharm_entries = dbAccessor->getNumPharmacophores();

	for (std::size_t i = 0; i < num_pharm_entries; i++) {
		std::size_t mol_idx = dbAccessor->getMoleculeIndex(i);
		
		if (mol_idx < mol_start_idx || mol_idx >= mol_end_idx)
			continue;

		pharmIndices.push_back(IndexPair(i, mol_idx));
	}

	std::sort(pharmIndices.begin(), pharmIndices.end(), IndexPair2ndCmpFunc());
}

bool Pharm::ScreeningProcessorImpl::checkFeatureCounts(std::size_t pharm_idx) const
{
	const FeatureTypeHistogram& db_ftr_cnts = dbAccessor->getFeatureCounts(pharm_idx);
	std::size_t num_db_ftrs = 0;

	for (FeatureTypeHistogram::ConstEntryIterator it = db_ftr_cnts.getEntriesBegin(), 
			 end = db_ftr_cnts.getEntriesEnd(); it != end; ++it)
		num_db_ftrs += it->second;
	
	if ((num_db_ftrs + maxOmittedFeatures) < queryMandFeatures.size())
		return false;

	for (FeatureTypeHistogram::ConstEntryIterator it = queryFeatureCounts.getEntriesBegin(), 
			 end = queryFeatureCounts.getEntriesEnd(); it != end; ++it) {

		std::size_t db_ftr_cnt = db_ftr_cnts.getValue(it->first, 0);

		if ((db_ftr_cnt + maxOmittedFeatures) < it->second)
			return false;
	}

	return true;
}

bool Pharm::ScreeningProcessorImpl::check2PointPharmacophores(std::size_t pharm_idx)
{
	if (minNum2PointPharmMatches == 0)
		return true;

	loadPharmacophore(pharm_idx);

	db2PointPharmSet.clear();
	db2PointPharmGen.generate(dbPharmacophore.getFeaturesBegin(),
							  dbPharmacophore.getFeaturesEnd(),
							  std::inserter(db2PointPharmSet, db2PointPharmSet.begin()));

	typedef std::pair<TwoPointPharmacophoreSet::const_iterator, TwoPointPharmacophoreSet::const_iterator> IterPair;

	std::size_t num_query_2pt_pharms = query2PointPharmList.size();
	std::size_t max_num_mismatches = num_query_2pt_pharms - minNum2PointPharmMatches;

	for (std::size_t i = 0, num_matches = 0, num_mismatches = 0; i < num_query_2pt_pharms; i++) {
		const QueryTwoPointPharmacophore& query_2pt_pharm = query2PointPharmList[i];

		double min_dist = query_2pt_pharm.getFeatureDistance() - query_2pt_pharm.getFeature1Tolerance() 
			- query_2pt_pharm.getFeature2Tolerance();
		double max_dist = query_2pt_pharm.getFeatureDistance() + query_2pt_pharm.getFeature1Tolerance() 
			+ query_2pt_pharm.getFeature2Tolerance();

		IterPair eq_range = db2PointPharmSet.equal_range(query_2pt_pharm);
		bool match = false;

		for ( ; eq_range.first != eq_range.second; ++eq_range.first) {
			if (!TwoPointPharmEqCmpFunc()(query_2pt_pharm, *eq_range.first))
				continue;

			double dist = eq_range.first->getFeatureDistance();

			if (dist >= min_dist && dist <= max_dist) {
				num_matches++;

				if (num_matches >= minNum2PointPharmMatches)
					return true;

				match = true;
				break;
			}
		}

		if (!match) {
			num_mismatches++;

			if (num_mismatches > max_num_mismatches)
				return false;
		}
	}

	return false;
}

bool Pharm::ScreeningProcessorImpl::performAlignment(std::size_t pharm_idx, std::size_t mol_idx)
{
	loadPharmacophore(pharm_idx);

	pharmAlignment.clearEntities(false);
	pharmAlignment.addFeatures(dbPharmacophore, false);

	double best_score = NAN_SCORE;
	std::size_t conf_idx = dbAccessor->getConformationIndex(pharm_idx);

	while (pharmAlignment.nextAlignment()) {
		if (!checkGeomAlignment())
			continue;

		if (!checkXVolumeClashes(mol_idx, conf_idx))
			continue;

		SearchHit hit(*parent, *queryPharmacophore, dbPharmacophore, dbMolecule, 
					  pharmAlignment.getTransform(), pharm_idx, mol_idx, conf_idx);
		double score = calcScore(hit);

		if (!bestAlignments)
			return processHit(hit, score);

		if (std::isnan(best_score) || score > best_score) {
			best_score = score;
			bestAlmntTransform = pharmAlignment.getTransform();
		}
	}

	if (!std::isnan(best_score))
		return processHit(SearchHit(*parent, *queryPharmacophore, dbPharmacophore, dbMolecule, 
									bestAlmntTransform, pharm_idx, mol_idx, conf_idx), best_score);

	return true;
}

bool Pharm::ScreeningProcessorImpl::checkGeomAlignment()
{
	std::size_t num_al_mand_ftrs = alignedQueryMandFeatures.size();
	std::size_t min_num_matches = (num_al_mand_ftrs > maxOmittedFeatures ? 
								   std::size_t(num_al_mand_ftrs - maxOmittedFeatures) : std::size_t(0));

	if (initDBFeaturesByType) {
		for (TypeToFeatureListMap::iterator it = dbFeaturesByType.begin(), end = dbFeaturesByType.end(); it != end; ++it)
			it->second.clear();

		for (BasicPharmacophore::ConstFeatureIterator it = dbPharmacophore.getFeaturesBegin(), end = dbPharmacophore.getFeaturesEnd(); it != end; ++it) {
			const Feature& ftr = *it;
			dbFeaturesByType[getType(ftr)].push_back(&ftr);
		}

		initDBFeaturesByType = false;
	}

	const Math::Matrix4D& xform = pharmAlignment.getTransform();
	Math::Vector3D tmp;
	
	alignedDBFeaturePositions = dbFeaturePositions;
	transform(alignedDBFeaturePositions, xform);

	std::size_t num_missing = 0;
	std::size_t num_matches = 0;

	for (std::size_t i = 0; i < num_al_mand_ftrs; i++) {
		std::size_t query_ftr_idx = alignedQueryMandFeatures[i]->getIndex();

		const Math::Vector3D& query_pos = queryFeaturePositions[query_ftr_idx];
		double query_tol = queryFeatureTolerances[query_ftr_idx];

		const FeatureList& db_ftr_list = dbFeaturesByType[queryMandFeatureTypes[i]];
		bool match = false;

		for (FeatureList::const_iterator db_ftr_it = db_ftr_list.begin(), db_ftr_end = db_ftr_list.end(); db_ftr_it != db_ftr_end && !match; ++db_ftr_it) {
			const Feature& db_ftr = **db_ftr_it;
			std::size_t db_ftr_idx = db_ftr.getIndex();

			tmp.assign(alignedDBFeaturePositions[db_ftr_idx]);
			tmp.minusAssign(query_pos);

			if (length(tmp) > query_tol)
				continue;

			const FeatureList& query_ftr_list = queryMandFeatures[i];

			for (FeatureList::const_iterator ftr_it = query_ftr_list.begin(), ftr_end = query_ftr_list.end(); ftr_it != ftr_end; ++ftr_it) {
				if (featureGeomMatchFunction(**ftr_it, db_ftr, xform)) {
					match = true;
					break;
				}
			}
		}

		if (!match) {
			num_missing++;

			if (num_missing > maxOmittedFeatures)
				return false;

		} else {
			num_matches++;

			if (num_matches >= min_num_matches)
				return true;
		}
	}

	return true;
}

bool Pharm::ScreeningProcessorImpl::checkXVolumeClashes(std::size_t mol_idx, std::size_t conf_idx)
{
	if (!checkXVolumes || xVolumeIndices.empty())
		return true;

	loadMolecule(mol_idx);

	if (atomVdWRadii.empty())
		for (Chem::BasicMolecule::ConstAtomIterator it = dbMolecule.getAtomsBegin(), 
				 end = dbMolecule.getAtomsEnd(); it != end; ++it)
			atomVdWRadii.push_back(Chem::AtomDictionary::getVdWRadius(getType(*it)) * VDW_RADIUS_FACTOR);

	if (atomCoordinates.isEmpty())
		getConformationData(dbMolecule, conf_idx, atomCoordinates);

	const Math::Matrix4D& xform = pharmAlignment.getTransform();
	Math::Vector3D al_pos;
	Math::Vector3D tmp;

	std::size_t num_atoms = atomCoordinates.getSize();
	std::size_t num_x_vols = xVolumeIndices.size();

	for (std::size_t i = 0; i < num_atoms; i++) {
		al_pos.assign(range(prod(xform, homog(atomCoordinates[i])), 0, 3));

		for (std::size_t j = 0; j < num_x_vols; j++) {
			tmp.assign(al_pos - queryFeaturePositions[xVolumeIndices[j]]);

			if (length(tmp) < (queryFeatureTolerances[xVolumeIndices[j]] + atomVdWRadii[i]))
				return false;
		}
	}

	return true;
}

double Pharm::ScreeningProcessorImpl::calcScore(const SearchHit& hit)
{
	if (!scoringFunction)
		return 0.0;

	loadMolecule(hit.getHitMoleculeIndex());

	return scoringFunction(hit);
}

bool Pharm::ScreeningProcessorImpl::checkTopologicalMapping(const FeatureMapping& mapping) const
{
	if (alignedQueryOptFeatures.empty())
		return true;

	std::size_t num_missing = 0;

	for (FeatureList::const_iterator it = alignedQueryMandFeatures.begin(), end = alignedQueryMandFeatures.end(); it != end; ++it)
		if (!mapping.getValue(*it)) {
			num_missing++;

			if (num_missing > maxOmittedFeatures)
				return false;
		}

	return true;
}

void Pharm::ScreeningProcessorImpl::loadMolecule(std::size_t mol_idx)
{
	if (mol_idx == loadedMolIndex)
		return;

	atomVdWRadii.clear();
	dbMolecule.clear();

	dbAccessor->getMolecule(mol_idx, dbMolecule);

	loadedMolIndex = mol_idx;
}

void Pharm::ScreeningProcessorImpl::loadPharmacophore(std::size_t pharm_idx)
{
	if (pharm_idx == loadedPharmIndex)
		return;

	atomCoordinates.clear();
	dbPharmacophore.clear();
	dbFeaturePositions.clear();
	initDBFeaturesByType = true;

	dbAccessor->getPharmacophore(pharm_idx, dbPharmacophore);

	loadedPharmIndex = pharm_idx;
}

bool Pharm::ScreeningProcessorImpl::processHit(const SearchHit& hit, double score)
{
	if (reportMode == ScreeningProcessor::BEST_MATCHING_CONF) {
		if (!std::isnan(bestConfAlmntScore) && score <= bestConfAlmntScore)
			return true;

		bestConfAlmntScore = score;
		bestConfAlmntTransform = hit.getHitAlignmentTransform();
		bestConfAlmntMolIdx = hit.getHitMoleculeIndex();
		bestConfAlmntConfIdx = hit.getHitConformationIndex();
		bestConfAlmntPharmIdx = hit.getHitPharmacophoreIndex();
		
		return true;
	} 

	return reportHit(hit, score);
}

bool Pharm::ScreeningProcessorImpl::reportHit(const SearchHit& hit, double score)
{
	numHits++;

	if (reportMode == ScreeningProcessor::FIRST_MATCHING_CONF) {
		molHitSet.set(hit.getHitMoleculeIndex());

	} else if (reportMode == ScreeningProcessor::BEST_MATCHING_CONF) 
		bestConfAlmntScore = NAN_SCORE;

	if (!hitCallback)
		return true;

	loadMolecule(hit.getHitMoleculeIndex());
	loadPharmacophore(hit.getHitPharmacophoreIndex());

	return hitCallback(hit, score);
}

const Math::Vector3D& Pharm::ScreeningProcessorImpl::getFeatureCoordinates(const Feature& ftr)
{
	if (&ftr.getPharmacophore() == queryPharmacophore)
		return queryFeaturePositions[ftr.getIndex()];

	if (dbFeaturePositions.isEmpty())
		get3DCoordinates(dbPharmacophore, dbFeaturePositions);

	return dbFeaturePositions[ftr.getIndex()];
}
