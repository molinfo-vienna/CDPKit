/* 
 * ScreeningProcessor.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Pharm/ScreeningProcessor.hpp"

#include "ScreeningProcessorImpl.hpp"


using namespace CDPL;


// SearchHit

Pharm::ScreeningProcessor::SearchHit::SearchHit(const ScreeningProcessor& hit_prov, const FeatureContainer& qry_pharm,
												const FeatureContainer& hit_pharm, const Chem::Molecule& mol, 
												const Math::Matrix4D& xform, std::size_t pharm_idx, 
												std::size_t mol_idx, std::size_t conf_idx):
	provider(&hit_prov), qryPharm(&qry_pharm), hitPharm(&hit_pharm), molecule(&mol),
	almntTransform(&xform), pharmIndex(pharm_idx), molIndex(mol_idx), confIndex(conf_idx) {}

const Pharm::ScreeningProcessor& Pharm::ScreeningProcessor::SearchHit::getHitProvider() const
{
	return *provider;
}

const Pharm::FeatureContainer& Pharm::ScreeningProcessor::SearchHit::getQueryPharmacophore() const
{
	return *qryPharm;
}

const Pharm::FeatureContainer& Pharm::ScreeningProcessor::SearchHit::getHitPharmacophore() const
{
	return *hitPharm;
}
				
const Chem::Molecule& Pharm::ScreeningProcessor::SearchHit::getHitMolecule() const
{
	return *molecule;
}
				
const Math::Matrix4D& Pharm::ScreeningProcessor::SearchHit::getHitAlignmentTransform() const
{
	return *almntTransform;
} 

std::size_t Pharm::ScreeningProcessor::SearchHit::getHitPharmacophoreIndex() const
{
	return pharmIndex;
}

std::size_t Pharm::ScreeningProcessor::SearchHit::getHitMoleculeIndex() const
{
	return molIndex;
}

std::size_t Pharm::ScreeningProcessor::SearchHit::getHitConformationIndex() const
{
	return confIndex;
}


// ScreeningProcessor

Pharm::ScreeningProcessor::ScreeningProcessor(ScreeningDBAccessor& db_acc): 
    impl(new ScreeningProcessorImpl(*this, db_acc))
{}
	
Pharm::ScreeningProcessor::~ScreeningProcessor() {}

void Pharm::ScreeningProcessor::setDBAccessor(ScreeningDBAccessor& db_acc)
{
	impl->setDBAccessor(db_acc);
}

Pharm::ScreeningDBAccessor& Pharm::ScreeningProcessor::getDBAccessor() const
{
	return impl->getDBAccessor();
}

void Pharm::ScreeningProcessor::setHitReportMode(HitReportMode mode)
{
	impl->setHitReportMode(mode);
}

Pharm::ScreeningProcessor::HitReportMode Pharm::ScreeningProcessor::getHitReportMode() const
{
	return impl->getHitReportMode();
}

void Pharm::ScreeningProcessor::setMaxNumOmittedFeatures(std::size_t max_num)
{
	impl->setMaxNumOmittedFeatures(max_num);
}

std::size_t Pharm::ScreeningProcessor::getMaxNumOmittedFeatures() const
{
	return impl->getMaxNumOmittedFeatures();
}

void Pharm::ScreeningProcessor::checkXVolumeClashes(bool check)
{
	impl->checkXVolumeClashes(check);
}

bool Pharm::ScreeningProcessor::xVolumeClashesChecked() const
{
	return impl->xVolumeClashesChecked();
}

void Pharm::ScreeningProcessor::seekBestAlignments(bool seek_best)
{
	impl->seekBestAlignments(seek_best);
}

bool Pharm::ScreeningProcessor::bestAlignmentsSeeked() const
{
	return impl->bestAlignmentsSeeked();
}

void Pharm::ScreeningProcessor::setHitCallback(const HitCallbackFunction& func)
{
	impl->setHitCallback(func);
}

const Pharm::ScreeningProcessor::HitCallbackFunction& Pharm::ScreeningProcessor::getHitCallback() const
{
	return impl->getHitCallback();
}

void Pharm::ScreeningProcessor::setProgressCallback(const ProgressCallbackFunction& func)
{
	impl->setProgressCallback(func);
}

const Pharm::ScreeningProcessor::ProgressCallbackFunction& Pharm::ScreeningProcessor::getProgressCallback() const
{
	return impl->getProgressCallback();
}

void Pharm::ScreeningProcessor::setScoringFunction(const ScoringFunction& func)
{
	impl->setScoringFunction(func);
}

const Pharm::ScreeningProcessor::ScoringFunction& Pharm::ScreeningProcessor::getScoringFunction() const
{
	return impl->getScoringFunction();
}

std::size_t Pharm::ScreeningProcessor::searchDB(const FeatureContainer& query, std::size_t mol_start_idx, std::size_t mol_end_idx)
{
	return impl->searchDB(query, mol_start_idx, mol_end_idx);
}
