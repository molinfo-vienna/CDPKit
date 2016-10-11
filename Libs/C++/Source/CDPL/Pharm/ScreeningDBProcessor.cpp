/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ScreeningDBProcessor.cpp 
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

#include <vector>
#include <iterator>
#include <utility>
#include <algorithm>
#include <limits>
#include <cmath>

#include <boost/bind.hpp>
#include <boost/iterator/indirect_iterator.hpp>

#include "CDPL/Pharm/ScreeningDBProcessor.hpp"
#include "CDPL/Pharm/ScreeningDBAccessor.hpp"
#include "CDPL/Pharm/PharmacophoreAlignment.hpp"
#include "CDPL/Pharm/BasicPharmacophore.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureTypeHistogram.hpp"
#include "CDPL/Pharm/PharmacophoreFunctions.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/FeatureType.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Math/VectorAdapter.hpp"
#include "CDPL/Math/VectorProxy.hpp"
#include "CDPL/Util/BitSet.hpp"

#include "QueryTwoPointPharmacophore.hpp"
#include "TwoPointPharmacophoreGenerator.hpp"
#include "TwoPointPharmacophoreSet.hpp"


using namespace CDPL;


namespace
{

    const double NAN_SCORE = std::numeric_limits<double>::quiet_NaN();
}


class Pharm::ScreeningDBProcessor::Implementation
{

public:
    Implementation(ScreeningDBProcessor& db_proc, ScreeningDBAccessor& db_acc);

	void setDBAccessor(ScreeningDBAccessor& db_acc);

	ScreeningDBAccessor& getDBAccessor() const;

	void setHitReportMode(HitReportMode mode);

	HitReportMode getHitReportMode() const;

	void setMaxNumOmittedFeatures(std::size_t max_num);

	std::size_t getMaxNumOmittedFeatures() const;

	void checkXVolumeClashes(bool check);

	bool checkXVolumeClashes() const;

	void seekBestAlignments(bool seek_best);

	bool seekBestAlignments() const;

	void setHitCallbackFunction(const HitCallbackFunction& func);

	const HitCallbackFunction& getHitCallbackFunction() const;

	void setProgressCallbackFunction(const ProgressCallbackFunction& func);

	const ProgressCallbackFunction& getProgressCallbackFunction() const;

	void setScoringFunction(const ScoringFunction& func);

	const ScoringFunction& getScoringFunction() const;

	std::size_t searchDB(const Pharmacophore& query, std::size_t mol_start_idx, std::size_t mol_end_idx);

private:
	typedef std::vector<QueryTwoPointPharmacophore> TwoPointPharmacophoreList;
	typedef std::vector<const Feature*> FeatureList;
	typedef std::vector<FeatureList> FeatureMatrix;
	typedef std::pair<std::size_t, std::size_t> IndexPair;
	typedef std::vector<IndexPair> IndexPairList;

	typedef TwoPointPharmacophoreGenerator<TwoPointPharmacophore> DB2PointPharmGenerator;
	typedef TwoPointPharmacophoreGenerator<QueryTwoPointPharmacophore> Query2PointPharmGenerator;

	typedef boost::indirect_iterator<FeatureList::const_iterator, const Feature> FeatureListIterator;

	struct IndexPair2ndCmpFunc
	{

		bool operator()(const IndexPair& p1, const IndexPair& p2) const {
			return (p1.second < p2.second);
		}
	};

	void prepareDBSearch(const Pharmacophore& query, std::size_t mol_start_idx, std::size_t mol_end_idx);

    void initQueryData(const Pharmacophore& query);
	void initPharmIndexList(std::size_t mol_start_idx, std::size_t mol_end_idx);

	bool insertFeature(const Feature& ftr, FeatureMatrix& ftr_mtx) const;

	bool checkFeatureCounts(std::size_t pharm_idx) const;
	bool check2PointPharmacophores(std::size_t pharm_idx);
	bool performAlignment(const Pharmacophore& query, std::size_t pharm_idx, std::size_t mol_idx);

	bool checkGeomAlignment() const;
	bool checkXVolumeClashes(std::size_t mol_idx, std::size_t conf_idx) const;

	bool checkTopologicalMapping(const FeatureMapping& mapping) const;

	void loadPharmacophore(std::size_t pharm_idx);
	void loadMolecule(std::size_t mol_idx);

	bool processHit(const SearchHit& hit, double score);
	bool reportHit(const SearchHit& hit, double score);

	ScreeningDBProcessor*            dbProcessor;
	ScreeningDBAccessor*             dbAccessor;
	HitReportMode                    reportMode;
	std::size_t                      maxOmittedFeatures;
	bool                             checkXVolumes;
	bool                             bestAlignments;
	HitCallbackFunction              hitCallback;
	ProgressCallbackFunction         progressCallback;
	ScoringFunction                  scoringFunction;
	BasicPharmacophore               dbPharmacophore;
	Chem::BasicMolecule              dbMolecule;
    PharmacophoreAlignment           pharmAlignment;
	Query2PointPharmGenerator        query2PointPharmGen;
	DB2PointPharmGenerator           db2PointPharmGen;
	FeatureTypeHistogram             queryFeatureCounts; 
	TwoPointPharmacophoreList        query2PointPharmList;
	TwoPointPharmacophoreSet         db2PointPharmSet;
	std::size_t                      minNum2PointPharmMatches;
	FeatureMatrix                    mandFeatures;
	FeatureMatrix                    optFeatures;
	FeatureList                      xVolumes;
	FeatureList                      alignedMandFeatures;
	FeatureList                      alignedOptFeatures;
	IndexPairList                    pharmIndices;  
	Util::BitSet                     molHitSet;
	std::size_t                      numHits;
	std::size_t                      loadedPharmIndex;
	std::size_t                      loadedMolIndex;
	Math::Matrix4D                   bestAlmntTransform;
	Math::Matrix4D                   bestConfAlmntTransform;
	std::size_t                      bestConfAlmntMolIdx;
	std::size_t                      bestConfAlmntConfIdx;
	std::size_t                      bestConfAlmntPharmIdx;
	double                           bestConfAlmntScore;
};


// SearchHit

Pharm::ScreeningDBProcessor::SearchHit::SearchHit(const ScreeningDBProcessor& db_proc, const Pharmacophore& qry_pharm,
												  const Pharmacophore& hit_pharm, const Chem::Molecule& mol, 
												  const Math::Matrix4D& xform, std::size_t pharm_idx, 
												  std::size_t mol_idx, std::size_t conf_idx):
	dbProcessor(&db_proc), qryPharm(&qry_pharm), hitPharm(&hit_pharm), molecule(&mol),
	almntTransform(&xform), pharmIndex(pharm_idx), molIndex(mol_idx), confIndex(conf_idx) {}

const Pharm::ScreeningDBProcessor& Pharm::ScreeningDBProcessor::SearchHit::getDBProcessor() const
{
	return *dbProcessor;
}

const Pharm::Pharmacophore& Pharm::ScreeningDBProcessor::SearchHit::getQueryPharmacophore() const
{
	return *qryPharm;
}

const Pharm::Pharmacophore& Pharm::ScreeningDBProcessor::SearchHit::getHitPharmacophore() const
{
	return *hitPharm;
}
				
const Chem::Molecule& Pharm::ScreeningDBProcessor::SearchHit::getHitMolecule() const
{
	return *molecule;
}
				
const Math::Matrix4D& Pharm::ScreeningDBProcessor::SearchHit::getHitAlignmentTransform() const
{
	return *almntTransform;
} 

std::size_t Pharm::ScreeningDBProcessor::SearchHit::getHitPharmacophoreIndex() const
{
	return pharmIndex;
}

std::size_t Pharm::ScreeningDBProcessor::SearchHit::getHitMoleculeIndex() const
{
	return molIndex;
}

std::size_t Pharm::ScreeningDBProcessor::SearchHit::getHitConformationIndex() const
{
	return confIndex;
}


// ScreeningDBProcessor

Pharm::ScreeningDBProcessor::ScreeningDBProcessor(ScreeningDBAccessor& db_acc): 
    impl(new Implementation(*this, db_acc))
{}
	
Pharm::ScreeningDBProcessor::~ScreeningDBProcessor() {}

void Pharm::ScreeningDBProcessor::setDBAccessor(ScreeningDBAccessor& db_acc)
{
	impl->setDBAccessor(db_acc);
}

Pharm::ScreeningDBAccessor& Pharm::ScreeningDBProcessor::getDBAccessor() const
{
	return impl->getDBAccessor();
}

void Pharm::ScreeningDBProcessor::setHitReportMode(HitReportMode mode)
{
	impl->setHitReportMode(mode);
}

Pharm::ScreeningDBProcessor::HitReportMode Pharm::ScreeningDBProcessor::getHitReportMode() const
{
	return impl->getHitReportMode();
}

void Pharm::ScreeningDBProcessor::setMaxNumOmittedFeatures(std::size_t max_num)
{
	impl->setMaxNumOmittedFeatures(max_num);
}

std::size_t Pharm::ScreeningDBProcessor::getMaxNumOmittedFeatures() const
{
	return impl->getMaxNumOmittedFeatures();
}

void Pharm::ScreeningDBProcessor::checkXVolumeClashes(bool check)
{
	impl->checkXVolumeClashes(check);
}

bool Pharm::ScreeningDBProcessor::checkXVolumeClashes() const
{
	return impl->checkXVolumeClashes();
}

void Pharm::ScreeningDBProcessor::seekBestAlignments(bool seek_best)
{
	impl->seekBestAlignments(seek_best);
}

bool Pharm::ScreeningDBProcessor::seekBestAlignments() const
{
	return impl->seekBestAlignments();
}

void Pharm::ScreeningDBProcessor::setHitCallbackFunction(const HitCallbackFunction& func)
{
	impl->setHitCallbackFunction(func);
}

const Pharm::ScreeningDBProcessor::HitCallbackFunction& Pharm::ScreeningDBProcessor::getHitCallbackFunction() const
{
	return impl->getHitCallbackFunction();
}

void Pharm::ScreeningDBProcessor::setProgressCallbackFunction(const ProgressCallbackFunction& func)
{
	impl->setProgressCallbackFunction(func);
}

const Pharm::ScreeningDBProcessor::ProgressCallbackFunction& Pharm::ScreeningDBProcessor::getProgressCallbackFunction() const
{
	return impl->getProgressCallbackFunction();
}

void Pharm::ScreeningDBProcessor::setScoringFunction(const ScoringFunction& func)
{
	impl->setScoringFunction(func);
}

const Pharm::ScreeningDBProcessor::ScoringFunction& Pharm::ScreeningDBProcessor::getScoringFunction() const
{
	return impl->getScoringFunction();
}

std::size_t Pharm::ScreeningDBProcessor::searchDB(const Pharmacophore& query, std::size_t mol_start_idx, std::size_t mol_end_idx)
{
	return impl->searchDB(query, mol_start_idx, mol_end_idx);
}


// Implementation

Pharm::ScreeningDBProcessor::Implementation::Implementation(ScreeningDBProcessor& db_proc, ScreeningDBAccessor& db_acc): 
	dbProcessor(&db_proc), dbAccessor(&db_acc), reportMode(FIRST_MATCHING_CONF), maxOmittedFeatures(0),
	checkXVolumes(true), bestAlignments(false), hitCallback(), progressCallback(), 
	scoringFunction(), pharmAlignment(true)
{
	pharmAlignment.setTopAlignmentConstraintFunction(boost::bind(&Implementation::checkTopologicalMapping, this, _1));
}

void Pharm::ScreeningDBProcessor::Implementation::setDBAccessor(ScreeningDBAccessor& db_acc)
{
	dbAccessor = &db_acc;
}

Pharm::ScreeningDBAccessor& Pharm::ScreeningDBProcessor::Implementation::getDBAccessor() const
{
	return *dbAccessor;
}

void Pharm::ScreeningDBProcessor::Implementation::setHitReportMode(HitReportMode mode)
{
	reportMode = mode;
}

Pharm::ScreeningDBProcessor::HitReportMode Pharm::ScreeningDBProcessor::Implementation::getHitReportMode() const
{
	return reportMode;
}

void Pharm::ScreeningDBProcessor::Implementation::setMaxNumOmittedFeatures(std::size_t max_num)
{
	maxOmittedFeatures = max_num;
}

std::size_t Pharm::ScreeningDBProcessor::Implementation::getMaxNumOmittedFeatures() const
{
	return maxOmittedFeatures;
}

void Pharm::ScreeningDBProcessor::Implementation::checkXVolumeClashes(bool check)
{
	checkXVolumes = check;
}

bool Pharm::ScreeningDBProcessor::Implementation::checkXVolumeClashes() const
{
	return checkXVolumes;
}

void Pharm::ScreeningDBProcessor::Implementation::seekBestAlignments(bool seek_best)
{
	bestAlignments = seek_best;
}

bool Pharm::ScreeningDBProcessor::Implementation::seekBestAlignments() const
{
	return bestAlignments;
}

void Pharm::ScreeningDBProcessor::Implementation::setHitCallbackFunction(const HitCallbackFunction& func)
{
	hitCallback = func;
}

const Pharm::ScreeningDBProcessor::HitCallbackFunction& Pharm::ScreeningDBProcessor::Implementation::getHitCallbackFunction() const
{
	return hitCallback;
}

void Pharm::ScreeningDBProcessor::Implementation::setProgressCallbackFunction(const ProgressCallbackFunction& func)
{
	progressCallback = func;
}

const Pharm::ScreeningDBProcessor::ProgressCallbackFunction& Pharm::ScreeningDBProcessor::Implementation::getProgressCallbackFunction() const
{
	return progressCallback;
}

void Pharm::ScreeningDBProcessor::Implementation::setScoringFunction(const ScoringFunction& func)
{
	scoringFunction = func;
}

const Pharm::ScreeningDBProcessor::ScoringFunction& Pharm::ScreeningDBProcessor::Implementation::getScoringFunction() const
{
	return scoringFunction;
}

std::size_t Pharm::ScreeningDBProcessor::Implementation::searchDB(const Pharmacophore& query, std::size_t mol_start_idx, std::size_t mol_end_idx)
{
	prepareDBSearch(query, mol_start_idx, mol_end_idx);

	std::size_t num_pharm_entries = pharmIndices.size();

	for (std::size_t i = 0; i <= num_pharm_entries; i++) {
		if (reportMode == BEST_MATCHING_CONF && !std::isnan(bestConfAlmntScore) &&
			(i == num_pharm_entries || pharmIndices[i].second != bestConfAlmntMolIdx)) {

				loadMolecule(bestConfAlmntMolIdx);
				loadPharmacophore(bestConfAlmntPharmIdx);

				reportHit(SearchHit(*dbProcessor, query, dbPharmacophore, dbMolecule, bestConfAlmntTransform,
									bestConfAlmntPharmIdx, bestConfAlmntMolIdx, bestConfAlmntConfIdx),
						  bestConfAlmntScore);
			}

		if (progressCallback && !progressCallback(i, num_pharm_entries))
			return numHits;

		if (i == num_pharm_entries)
			continue;

		std::size_t mol_idx = pharmIndices[i].second;

		if (reportMode == FIRST_MATCHING_CONF && molHitSet.test(mol_idx))
			continue;

		std::size_t pharm_idx = pharmIndices[i].first;

		if (!checkFeatureCounts(pharm_idx))
			continue;

		if (!check2PointPharmacophores(pharm_idx))
			continue;

		if (!performAlignment(query, pharm_idx, mol_idx))
			return numHits;
	}

	return numHits;
}

void Pharm::ScreeningDBProcessor::Implementation::prepareDBSearch(const Pharmacophore& query, std::size_t mol_start_idx, std::size_t mol_end_idx)
{
	initQueryData(query);

	numHits = 0;
	loadedPharmIndex = dbAccessor->getNumPharmacophores();
	loadedMolIndex = dbAccessor->getNumMolecules();

	if (reportMode == FIRST_MATCHING_CONF) {
		molHitSet.resize(loadedMolIndex);
		molHitSet.reset();

	} else if (reportMode == BEST_MATCHING_CONF)
		bestConfAlmntScore = NAN_SCORE;

	initPharmIndexList(mol_start_idx, mol_end_idx);
}

void Pharm::ScreeningDBProcessor::Implementation::initQueryData(const Pharmacophore& query)
{
	mandFeatures.clear();
	optFeatures.clear();
	alignedMandFeatures.clear();
	xVolumes.clear();
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

			xVolumes.push_back(&ftr);
			continue;
		}

		if (getOptionalFlag(ftr)) {
			if (insertFeature(ftr, optFeatures)) {
				pharmAlignment.addEntity(ftr, true);
				alignedOptFeatures.push_back(&ftr);
			}
			continue;
		}

		if (insertFeature(ftr, mandFeatures)) {
			pharmAlignment.addEntity(ftr, true);
			alignedMandFeatures.push_back(&ftr);
			queryFeatureCounts[type]++;
		}
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

bool Pharm::ScreeningDBProcessor::Implementation::insertFeature(const Feature& ftr, FeatureMatrix& ftr_mtx) const
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
			return false;
		}
	}

	ftr_mtx.resize(ftr_mtx.size() + 1);
	ftr_mtx.back().push_back(&ftr);

	return true;
}

void Pharm::ScreeningDBProcessor::Implementation::initPharmIndexList(std::size_t mol_start_idx, std::size_t mol_end_idx)
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

bool Pharm::ScreeningDBProcessor::Implementation::checkFeatureCounts(std::size_t pharm_idx) const
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

bool Pharm::ScreeningDBProcessor::Implementation::check2PointPharmacophores(std::size_t pharm_idx)
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

		double min_dist = qry_2pt_pharm.getFeatureDistance() - qry_2pt_pharm.getFeature1Tolerance() - qry_2pt_pharm.getFeature2Tolerance();
		double max_dist = qry_2pt_pharm.getFeatureDistance() + qry_2pt_pharm.getFeature1Tolerance() + qry_2pt_pharm.getFeature2Tolerance();

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

bool Pharm::ScreeningDBProcessor::Implementation::performAlignment(const Pharmacophore& query, std::size_t pharm_idx, std::size_t mol_idx)
{
	loadPharmacophore(pharm_idx);

	pharmAlignment.clearEntities(false);
	pharmAlignment.addPharmacophore(dbPharmacophore, false);

	double best_score = NAN_SCORE;
	std::size_t conf_idx = dbAccessor->getConformationIndex(pharm_idx);

	while (pharmAlignment.nextAlignment()) {
		if (!checkGeomAlignment())
			continue;

		loadMolecule(mol_idx);

		if (!checkXVolumeClashes(mol_idx, conf_idx))
			continue;

		SearchHit hit(*dbProcessor, query, dbPharmacophore, dbMolecule, 
					  pharmAlignment.getTransform(), pharm_idx, mol_idx, conf_idx);
		double score = (scoringFunction ? scoringFunction(hit) : 1.0);

		if (!bestAlignments)
			return processHit(hit, score);

		if (std::isnan(best_score) || score > best_score) {
			best_score = score;
			bestAlmntTransform = pharmAlignment.getTransform();
		}
	}

	if (!std::isnan(best_score))
		return processHit(SearchHit(*dbProcessor, query, dbPharmacophore, dbMolecule, 
									bestAlmntTransform, pharm_idx, mol_idx, conf_idx), best_score);

	return true;
}

bool Pharm::ScreeningDBProcessor::Implementation::checkGeomAlignment() const
{
	std::size_t num_missing = 0;

	Math::Vector3D trans_pos2;
	const Math::Matrix4D& xform = pharmAlignment.getTransform();

	for (FeatureList::const_iterator qry_it = alignedMandFeatures.begin(), qry_end = alignedMandFeatures.end(); qry_it != qry_end; ++qry_it) {
		const Feature& qry_ftr = **qry_it;
		unsigned int qry_type = getType(qry_ftr);
		const Math::Vector3D& qry_pos = get3DCoordinates(qry_ftr);
		double qry_tol = getTolerance(qry_ftr);

		bool match = false;

		for (BasicPharmacophore::ConstFeatureIterator al_it = dbPharmacophore.getFeaturesBegin(), al_end = dbPharmacophore.getFeaturesEnd(); al_it != al_end; ++al_it) {
			const Feature& al_ftr = *al_it;

			if (qry_type != getType(al_ftr))
				continue;

			trans_pos2.assign(range(prod(xform, homog(get3DCoordinates(al_ftr))), 0, 3));
			trans_pos2.minusAssign(qry_pos);

			if (length(trans_pos2) > qry_tol)
				continue;
/*

			if (geomMatchFunc && !geomMatchFunc(ref_ftr, mpd_ftr, xform))
				continue;
*/
			match = true;
			break;
		}

		if (!match) {
			num_missing++;

			if (num_missing > maxOmittedFeatures)
				return false;
		}
	}

	return true;
}

bool Pharm::ScreeningDBProcessor::Implementation::checkXVolumeClashes(std::size_t mol_idx, std::size_t conf_idx) const
{
	if (!checkXVolumes)
		return true;

	return true;
}

bool Pharm::ScreeningDBProcessor::Implementation::checkTopologicalMapping(const FeatureMapping& mapping) const
{
	if (alignedOptFeatures.size())
		return true;

	std::size_t num_missing = 0;

	for (FeatureList::const_iterator it = alignedMandFeatures.begin(), end = alignedMandFeatures.end(); it != end; ++it)
		if (!mapping[*it]) {
			num_missing++;

			if (num_missing > maxOmittedFeatures)
				return false;
		}

	return true;
}

void Pharm::ScreeningDBProcessor::Implementation::loadMolecule(std::size_t mol_idx)
{
	if (mol_idx == loadedMolIndex)
		return;

	dbMolecule.clear();
	dbAccessor->getMolecule(mol_idx, dbMolecule);

	loadedMolIndex = mol_idx;
}

void Pharm::ScreeningDBProcessor::Implementation::loadPharmacophore(std::size_t pharm_idx)
{
	if (pharm_idx == loadedPharmIndex)
		return;

	dbPharmacophore.clear();
	dbAccessor->getPharmacophore(pharm_idx, dbPharmacophore);

	loadedPharmIndex = pharm_idx;
}

bool Pharm::ScreeningDBProcessor::Implementation::processHit(const SearchHit& hit, double score)
{
	if (reportMode == BEST_MATCHING_CONF) {
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

bool Pharm::ScreeningDBProcessor::Implementation::reportHit(const SearchHit& hit, double score)
{
	numHits++;

	if (reportMode == FIRST_MATCHING_CONF) 
		molHitSet.set(hit.getHitMoleculeIndex());
	else if (reportMode == BEST_MATCHING_CONF) 
		bestConfAlmntScore = NAN_SCORE;

	if (!hitCallback)
		return true;

	return hitCallback(hit, score);
}
