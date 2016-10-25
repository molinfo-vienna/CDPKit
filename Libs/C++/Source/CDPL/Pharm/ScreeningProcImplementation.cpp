/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ScreeningProcImplementation.cpp 
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
#include "CDPL/Math/VectorAdapter.hpp"
#include "CDPL/Math/VectorArrayFunctions.hpp"

#include "ScreeningProcImplementation.hpp"


using namespace CDPL;


namespace
{

    const double NAN_SCORE = std::numeric_limits<double>::quiet_NaN();

	struct FeatureTolCmpFunc : public std::binary_function<const Pharm::Feature*, const Pharm::Feature*, bool> 
	{

		bool operator()(const Pharm::Feature* ftr1, const Pharm::Feature* ftr2) const {
			return (getTolerance(*ftr1) < getTolerance(*ftr2));
		}
	};
}


Pharm::ScreeningProcImplementation::ScreeningProcImplementation(ScreeningProcessor& parent, ScreeningDBAccessor& db_acc): 
	parent(&parent), dbAccessor(&db_acc), reportMode(ScreeningProcessor::FIRST_MATCHING_CONF), maxOmittedFeatures(0),
	checkXVolumes(true), bestAlignments(false), hitCallback(), progressCallback(), 
	scoringFunction(PharmacophoreFitScreeningScore()), ftrGeomMatchFunction(false), pharmAlignment(true)
{
	pharmAlignment.setTopAlignmentConstraintFunction(
		boost::bind(&ScreeningProcImplementation::checkTopologicalMapping, this, _1));
}

void Pharm::ScreeningProcImplementation::setDBAccessor(ScreeningDBAccessor& db_acc)
{
	dbAccessor = &db_acc;
}

Pharm::ScreeningDBAccessor& Pharm::ScreeningProcImplementation::getDBAccessor() const
{
	return *dbAccessor;
}

void Pharm::ScreeningProcImplementation::setHitReportMode(ScreeningProcessor::HitReportMode mode)
{
	reportMode = mode;
}

Pharm::ScreeningProcessor::HitReportMode Pharm::ScreeningProcImplementation::getHitReportMode() const
{
	return reportMode;
}

void Pharm::ScreeningProcImplementation::setMaxNumOmittedFeatures(std::size_t max_num)
{
	maxOmittedFeatures = max_num;
}

std::size_t Pharm::ScreeningProcImplementation::getMaxNumOmittedFeatures() const
{
	return maxOmittedFeatures;
}

void Pharm::ScreeningProcImplementation::checkXVolumeClashes(bool check)
{
	checkXVolumes = check;
}

bool Pharm::ScreeningProcImplementation::xVolumeClashesChecked() const
{
	return checkXVolumes;
}

void Pharm::ScreeningProcImplementation::seekBestAlignments(bool seek_best)
{
	bestAlignments = seek_best;
}

bool Pharm::ScreeningProcImplementation::bestAlignmentsSeeked() const
{
	return bestAlignments;
}

void Pharm::ScreeningProcImplementation::setHitCallbackFunction(const HitCallbackFunction& func)
{
	hitCallback = func;
}

const Pharm::ScreeningProcessor::HitCallbackFunction& Pharm::ScreeningProcImplementation::getHitCallbackFunction() const
{
	return hitCallback;
}

void Pharm::ScreeningProcImplementation::setProgressCallbackFunction(const ProgressCallbackFunction& func)
{
	progressCallback = func;
}

const Pharm::ScreeningProcessor::ProgressCallbackFunction& Pharm::ScreeningProcImplementation::getProgressCallbackFunction() const
{
	return progressCallback;
}

void Pharm::ScreeningProcImplementation::setScoringFunction(const ScoringFunction& func)
{
	scoringFunction = func;
}

const Pharm::ScreeningProcessor::ScoringFunction& Pharm::ScreeningProcImplementation::getScoringFunction() const
{
	return scoringFunction;
}

std::size_t Pharm::ScreeningProcImplementation::searchDB(const Pharmacophore& query, std::size_t mol_start_idx, 
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

void Pharm::ScreeningProcImplementation::prepareDBSearch(const Pharmacophore& query, std::size_t mol_start_idx, 
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

void Pharm::ScreeningProcImplementation::initQueryData(const Pharmacophore& query)
{
	queryPharmacophore = &query;

	mandFeatures.clear();
	mandFtrPosAndRadii.clear();
	mandFeatureTypes.clear();
	optFeatures.clear();
	alignedMandFeatures.clear();
	xVolumePosAndRadii.clear();
	queryFeatureCounts.clear();
	pharmAlignment.clearEntities(true);

	for (Pharmacophore::ConstFeatureIterator it = query.getFeaturesBegin(), end = query.getFeaturesEnd(); it != end; ++it) {
		const Feature& ftr = *it;

		if (getDisabledFlag(ftr))
			continue;

		unsigned int type = getType(ftr);

		if (type == FeatureType::X_VOLUME) {
			if (getOptionalFlag(ftr))
				continue;

			xVolumePosAndRadii.push_back(PosAndRadiusPair(get3DCoordinates(ftr), getTolerance(ftr)));
			continue;
		}

		if (getOptionalFlag(ftr))
			insertFeature(ftr, optFeatures);
		else
			insertFeature(ftr, mandFeatures);
	}

	for (FeatureMatrix::iterator it = mandFeatures.begin(), end = mandFeatures.end(); it != end; ++it) {
		FeatureList& ftr_list = *it; assert(!ftr_list.empty());		
		const Feature& max_tol_ftr = **std::max_element(ftr_list.begin(), ftr_list.end(), FeatureTolCmpFunc());
		unsigned int type = getType(max_tol_ftr);

		pharmAlignment.addEntity(max_tol_ftr, true);
		alignedMandFeatures.push_back(&max_tol_ftr);
		mandFtrPosAndRadii.push_back(PosAndRadiusPair(get3DCoordinates(max_tol_ftr), getTolerance(max_tol_ftr)));
		mandFeatureTypes.push_back(type);
		queryFeatureCounts[type]++;
	}

	for (FeatureMatrix::iterator it = optFeatures.begin(), end = optFeatures.end(); it != end; ++it) {
		FeatureList& ftr_list = *it; assert(!ftr_list.empty());		
		const Feature& max_tol_ftr = **std::max_element(ftr_list.begin(), ftr_list.end(), FeatureTolCmpFunc());
		
		pharmAlignment.addEntity(max_tol_ftr, true);
		alignedOptFeatures.push_back(&max_tol_ftr);
	}

	query2PointPharmList.clear();

	query2PointPharmGen.generate(FeatureListIterator(alignedMandFeatures.begin()),
								 FeatureListIterator(alignedMandFeatures.end()),
								 std::back_inserter(query2PointPharmList));

	std::size_t min_num_ftrs = (mandFeatures.size() > maxOmittedFeatures ? 
								std::size_t(mandFeatures.size() - maxOmittedFeatures) : std::size_t(0));

	minNum2PointPharmMatches = (min_num_ftrs < 2 ? std::size_t(0) : (min_num_ftrs * (min_num_ftrs - 1)) / 2);

	pharmAlignment.setMinTopologicalMappingSize(min_num_ftrs);
}

void Pharm::ScreeningProcImplementation::insertFeature(const Feature& ftr, FeatureMatrix& ftr_mtx) const
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

void Pharm::ScreeningProcImplementation::initPharmIndexList(std::size_t mol_start_idx, std::size_t mol_end_idx)
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

bool Pharm::ScreeningProcImplementation::checkFeatureCounts(std::size_t pharm_idx) const
{
	const FeatureTypeHistogram& db_ftr_cnts = dbAccessor->getFeatureCounts(pharm_idx);
	std::size_t num_db_ftrs = 0;

	for (FeatureTypeHistogram::ConstEntryIterator it = db_ftr_cnts.getEntriesBegin(), 
			 end = db_ftr_cnts.getEntriesEnd(); it != end; ++it)
		num_db_ftrs += it->second;
	
	if ((num_db_ftrs + maxOmittedFeatures) < mandFeatures.size())
		return false;

	for (FeatureTypeHistogram::ConstEntryIterator it = queryFeatureCounts.getEntriesBegin(), 
			 end = queryFeatureCounts.getEntriesEnd(); it != end; ++it) {

		std::size_t db_ftr_cnt = db_ftr_cnts.getValue(it->first, 0);

		if ((db_ftr_cnt + maxOmittedFeatures) < it->second)
			return false;
	}

	return true;
}

bool Pharm::ScreeningProcImplementation::check2PointPharmacophores(std::size_t pharm_idx)
{
	if (minNum2PointPharmMatches == 0)
		return true;

	loadPharmacophore(pharm_idx);

	db2PointPharmSet.clear();
	db2PointPharmGen.generate(dbPharmacophore.getFeaturesBegin(),
							  dbPharmacophore.getFeaturesEnd(),
							  std::inserter(db2PointPharmSet, db2PointPharmSet.begin()));

	typedef std::pair<TwoPointPharmacophoreSet::const_iterator, TwoPointPharmacophoreSet::const_iterator> IterPair;

	std::size_t num_qry_2pt_pharms = query2PointPharmList.size();
	std::size_t max_num_mismatches = num_qry_2pt_pharms - minNum2PointPharmMatches;

	for (std::size_t i = 0, num_matches = 0, num_mismatches = 0; i < num_qry_2pt_pharms; i++) {
		const QueryTwoPointPharmacophore& qry_2pt_pharm = query2PointPharmList[i];

		double min_dist = qry_2pt_pharm.getFeatureDistance() - qry_2pt_pharm.getFeature1Tolerance() 
			- qry_2pt_pharm.getFeature2Tolerance();
		double max_dist = qry_2pt_pharm.getFeatureDistance() + qry_2pt_pharm.getFeature1Tolerance() 
			+ qry_2pt_pharm.getFeature2Tolerance();

		IterPair eq_range = db2PointPharmSet.equal_range(qry_2pt_pharm);
		bool match = false;

		for ( ; eq_range.first != eq_range.second; ++eq_range.first) {
			if (!TwoPointPharmEqCmpFunc()(qry_2pt_pharm, *eq_range.first))
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

bool Pharm::ScreeningProcImplementation::performAlignment(std::size_t pharm_idx, std::size_t mol_idx)
{
	loadPharmacophore(pharm_idx);

	pharmAlignment.clearEntities(false);
	pharmAlignment.addPharmacophore(dbPharmacophore, false);

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

bool Pharm::ScreeningProcImplementation::checkGeomAlignment()
{
	std::size_t num_missing = 0;
	std::size_t num_matches = 0;
	std::size_t min_num_matches = (alignedMandFeatures.size() > maxOmittedFeatures ? 
								   std::size_t(alignedMandFeatures.size() - maxOmittedFeatures) : std::size_t(0));

	const Math::Matrix4D& xform = pharmAlignment.getTransform();
	Math::Vector3D tmp;

	if (dbPharmFtrTypes.empty())
		for (BasicPharmacophore::ConstFeatureIterator it = dbPharmacophore.getFeaturesBegin(), 
				 end = dbPharmacophore.getFeaturesEnd(); it != end; ++it) 
			dbPharmFtrTypes.push_back(getType(*it));
	
	dbPharmFtrPositions.clear();

	get3DCoordinates(dbPharmacophore, dbPharmFtrPositions);
	transform(dbPharmFtrPositions, xform);

	std::size_t i = 0;
	std::size_t num_db_ftrs = dbPharmFtrTypes.size();

	for (FeatureMatrix::const_iterator qry_flst_it = mandFeatures.begin(), qry_flst_end = mandFeatures.end(); 
		 qry_flst_it != qry_flst_end; ++qry_flst_it, i++) {

		const FeatureList& qry_ftr_list = *qry_flst_it;

		unsigned int qry_type = mandFeatureTypes[i];
		const Math::Vector3D& qry_pos = mandFtrPosAndRadii[i].first;
		double qry_tol = mandFtrPosAndRadii[i].second;

		bool match = false;

		for (std::size_t j = 0; j < num_db_ftrs && !match; j++) {
			if (qry_type != dbPharmFtrTypes[j])
				continue;

			tmp.assign(dbPharmFtrPositions[j] - qry_pos);

			if (length(tmp) > qry_tol)
				continue;

			const Feature& al_ftr = dbPharmacophore.getFeature(j);

			for (FeatureList::const_iterator ftr_it = qry_ftr_list.begin(), ftr_end = qry_ftr_list.end(); 
				 ftr_it != ftr_end; ++ftr_it) {

				if (ftrGeomMatchFunction(**ftr_it, al_ftr, xform)) {
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

bool Pharm::ScreeningProcImplementation::checkXVolumeClashes(std::size_t mol_idx, std::size_t conf_idx)
{
	if (!checkXVolumes || xVolumePosAndRadii.empty())
		return true;

	loadMolecule(mol_idx);

	if (atomVdWRadii.empty())
		for (Chem::BasicMolecule::ConstAtomIterator it = dbMolecule.getAtomsBegin(), 
				 end = dbMolecule.getAtomsEnd(); it != end; ++it)
			atomVdWRadii.push_back(Chem::AtomDictionary::getVdWRadius(getType(*it)));

	if (atomCoordinates.isEmpty())
		getConformationData(dbMolecule, conf_idx, atomCoordinates);

	const Math::Matrix4D& xform = pharmAlignment.getTransform();
	Math::Vector3D al_pos;
	Math::Vector3D tmp;

	std::size_t num_atoms = atomCoordinates.getSize();
	std::size_t num_x_vols = xVolumePosAndRadii.size();

	for (std::size_t i = 0; i < num_atoms; i++) {
		al_pos.assign(range(prod(xform, homog(atomCoordinates[i])), 0, 3));

		for (std::size_t j = 0; j < num_x_vols; j++) {
			tmp.assign(al_pos - xVolumePosAndRadii[j].first);

			if (length(tmp) < (xVolumePosAndRadii[j].second + atomVdWRadii[i]))
				return false;
		}
	}

	return true;
}

double Pharm::ScreeningProcImplementation::calcScore(const SearchHit& hit)
{
	if (!scoringFunction)
		return 0.0;

	loadMolecule(hit.getHitMoleculeIndex());

	return scoringFunction(hit);
}

bool Pharm::ScreeningProcImplementation::checkTopologicalMapping(const FeatureMapping& mapping) const
{
	if (alignedOptFeatures.empty())
		return true;

	std::size_t num_missing = 0;

	for (FeatureList::const_iterator it = alignedMandFeatures.begin(), 
			 end = alignedMandFeatures.end(); it != end; ++it)
		if (!mapping[*it]) {
			num_missing++;

			if (num_missing > maxOmittedFeatures)
				return false;
		}

	return true;
}

void Pharm::ScreeningProcImplementation::loadMolecule(std::size_t mol_idx)
{
	if (mol_idx == loadedMolIndex)
		return;

	atomVdWRadii.clear();
	dbMolecule.clear();

	dbAccessor->getMolecule(mol_idx, dbMolecule);

	loadedMolIndex = mol_idx;
}

void Pharm::ScreeningProcImplementation::loadPharmacophore(std::size_t pharm_idx)
{
	if (pharm_idx == loadedPharmIndex)
		return;

	atomCoordinates.clear();
	dbPharmacophore.clear();
	dbPharmFtrTypes.clear();

	dbAccessor->getPharmacophore(pharm_idx, dbPharmacophore);

	loadedPharmIndex = pharm_idx;
}

bool Pharm::ScreeningProcImplementation::processHit(const SearchHit& hit, double score)
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

bool Pharm::ScreeningProcImplementation::reportHit(const SearchHit& hit, double score)
{
	numHits++;

	if (reportMode == ScreeningProcessor::FIRST_MATCHING_CONF) 
		molHitSet.set(hit.getHitMoleculeIndex());
	else if (reportMode == ScreeningProcessor::BEST_MATCHING_CONF) 
		bestConfAlmntScore = NAN_SCORE;

	if (!hitCallback)
		return true;

	loadMolecule(hit.getHitMoleculeIndex());
	loadPharmacophore(hit.getHitPharmacophoreIndex());

	return hitCallback(hit, score);
}
