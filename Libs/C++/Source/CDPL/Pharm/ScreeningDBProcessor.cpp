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

#include <boost/iterator/indirect_iterator.hpp>
#include <boost/bind.hpp>

#include "CDPL/Pharm/ScreeningDBProcessor.hpp"
#include "CDPL/Pharm/ScreeningDBAccessor.hpp"
#include "CDPL/Pharm/PharmacophoreAlignment.hpp"
#include "CDPL/Pharm/BasicPharmacophore.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureTypeHistogram.hpp"
#include "CDPL/Pharm/PharmacophoreFunctions.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/FeatureType.hpp"

#include "QueryTwoPointPharmacophore.hpp"
#include "TwoPointPharmacophoreGenerator.hpp"
#include "TwoPointPharmacophoreSet.hpp"

#include <iostream>
using namespace CDPL;


class Pharm::ScreeningDBProcessor::Implementation
{

public:
    Implementation(ScreeningDBAccessor& db_acc);

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

	typedef TwoPointPharmacophoreGenerator<TwoPointPharmacophore> DB2PointPharmGenerator;
	typedef TwoPointPharmacophoreGenerator<QueryTwoPointPharmacophore> Query2PointPharmGenerator;

	typedef boost::indirect_iterator<FeatureList::const_iterator, const Feature> FeatureListIterator;

    void initQueryData(const Pharmacophore& query);

	bool checkFeatureCounts(std::size_t pharm_idx) const;
	bool check2PointPharmacophores();
	bool performAlignment();

	bool checkTopologicalMapping(const FeatureMapping& mapping) const;

	ScreeningDBAccessor*             dbAccessor;
	HitReportMode                    reportMode;
	std::size_t                      maxOmittedFeatures;
	bool                             checkXVolumes;
	bool                             bestAlignments;
	HitCallbackFunction              hitCallback;
	ProgressCallbackFunction         progressCallback;
	ScoringFunction                  scoringFunction;
	BasicPharmacophore               dbPharmacophore;
    PharmacophoreAlignment           pharmAlignment;
	Query2PointPharmGenerator        query2PointPharmGen;
	DB2PointPharmGenerator           db2PointPharmGen;
	FeatureTypeHistogram             queryFeatureCounts; 
	TwoPointPharmacophoreList        query2PointPharmList;
	TwoPointPharmacophoreSet         db2PointPharmSet;
	std::size_t                      minNum2PointPharmMatches;
	FeatureList                      mandFeatures;
	FeatureList                      mandAndOptFeatures;
	FeatureList                      xVolumes;
	std::size_t                      numHits;
};


// SearchHit

Pharm::ScreeningDBProcessor::SearchHit::SearchHit(const ScreeningDBProcessor& db_proc, const Pharmacophore& qry_pharm,
												  const Pharmacophore& hit_pharm, const Chem::Molecule& mol, 
												  const Math::Matrix4D& xform, std::size_t pharm_idx, 
												  std::size_t mol_idx, std::size_t conf_idx):
	dbProcessor(db_proc), qryPharm(qry_pharm), hitPharm(hit_pharm), molecule(mol),
	almntXForm(xform), pharmIndex(pharm_idx), molIndex(mol_idx), confIndex(conf_idx) {}

const Pharm::ScreeningDBProcessor& Pharm::ScreeningDBProcessor::SearchHit::getDBProcessor() const
{
	return dbProcessor;
}

const Pharm::Pharmacophore& Pharm::ScreeningDBProcessor::SearchHit::getQueryPharmacophore() const
{
	return qryPharm;
}

const Pharm::Pharmacophore& Pharm::ScreeningDBProcessor::SearchHit::getHitPharmacophore() const
{
	return hitPharm;
}
				
const Chem::Molecule& Pharm::ScreeningDBProcessor::SearchHit::getHitMolecule() const
{
	return molecule;
}
				
const Math::Matrix4D& Pharm::ScreeningDBProcessor::SearchHit::getHitAlignmentTransform() const
{
	return almntXForm;
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
    impl(new Implementation(db_acc))
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

Pharm::ScreeningDBProcessor::Implementation::Implementation(ScreeningDBAccessor& db_acc): 
	dbAccessor(&db_acc), reportMode(FIRST_MATCHING_CONF), maxOmittedFeatures(0),
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
	initQueryData(query);
	numHits = 0;

	if (mol_end_idx == 0)
		mol_end_idx = dbAccessor->getNumMolecules();

	std::size_t num_pharm_entries = dbAccessor->getNumPharmacophores();

	for (std::size_t i = 0; i < num_pharm_entries; i++) {
		if (progressCallback && !progressCallback(i, num_pharm_entries))
			return numHits;

		std::size_t mol_idx = dbAccessor->getMoleculeIndex(i);
		
		if (mol_idx < mol_start_idx || mol_idx >= mol_end_idx)
			continue;

		if (!checkFeatureCounts(i))
			continue;

		dbPharmacophore.clear();
		dbAccessor->getPharmacophore(i, dbPharmacophore);

		if (!check2PointPharmacophores())
			continue;

		if (!performAlignment())
			return numHits;
	}

	if (progressCallback)
		progressCallback(num_pharm_entries, num_pharm_entries);

	return numHits;
}

void Pharm::ScreeningDBProcessor::Implementation::initQueryData(const Pharmacophore& query)
{
	mandFeatures.clear();
	mandAndOptFeatures.clear();
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

		mandAndOptFeatures.push_back(&ftr);
		pharmAlignment.addEntity(ftr, true);

		if (getOptionalFlag(ftr))
			continue;

		mandFeatures.push_back(&ftr);
		queryFeatureCounts[type]++;
	}

	query2PointPharmList.clear();

	query2PointPharmGen.generate(FeatureListIterator(mandFeatures.begin()),
								 FeatureListIterator(mandFeatures.end()),
								 std::back_inserter(query2PointPharmList));

	std::size_t min_num_ftrs = (mandFeatures.size() > maxOmittedFeatures ? 
								std::size_t(mandFeatures.size() - maxOmittedFeatures) : std::size_t(0));

	minNum2PointPharmMatches = (min_num_ftrs < 2 ? std::size_t(0) : (min_num_ftrs * (min_num_ftrs - 1)) / 2);

	pharmAlignment.setMinTopologicalMappingSize(min_num_ftrs);
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

bool Pharm::ScreeningDBProcessor::Implementation::check2PointPharmacophores()
{
	if (minNum2PointPharmMatches == 0)
		return true;

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

bool Pharm::ScreeningDBProcessor::Implementation::performAlignment()
{
	pharmAlignment.clearEntities(false);
	pharmAlignment.addPharmacophore(dbPharmacophore, false);

	if (pharmAlignment.nextAlignment())
		numHits++;

	return true;
}

bool Pharm::ScreeningDBProcessor::Implementation::checkTopologicalMapping(const FeatureMapping& mapping) const
{
	if (mandFeatures.size() == mandAndOptFeatures.size())
		return true;

	std::size_t min_num_mand_mappings = (mandFeatures.size() > maxOmittedFeatures ? 
										 std::size_t(mandFeatures.size() - maxOmittedFeatures) : std::size_t(0));

	if (min_num_mand_mappings == 0)
		return true;

	std::size_t num_mand_mappings = 0;

	for (FeatureList::const_iterator it = mandFeatures.begin(), end = mandFeatures.end(); it != end; ++it)
		if (mapping[*it]) 
			num_mand_mappings++;
		
	return (num_mand_mappings >= min_num_mand_mappings);
}
