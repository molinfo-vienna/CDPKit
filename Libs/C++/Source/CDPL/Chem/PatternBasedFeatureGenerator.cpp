/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PatternBasedFeatureGenerator.cpp 
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

#include <boost/bind.hpp>

#include "CDPL/Chem/PatternBasedFeatureGenerator.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/Pharmacophore.hpp"
#include "CDPL/Chem/Feature.hpp"
#include "CDPL/Chem/FeatureFunctions.hpp"
#include "CDPL/Chem/FeatureGeometry.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/SubstructureSearch.hpp"
#include "CDPL/Math/SVDecomposition.hpp"


using namespace CDPL; 


Chem::PatternBasedFeatureGenerator::PatternBasedFeatureGenerator() {}

Chem::PatternBasedFeatureGenerator::PatternBasedFeatureGenerator(const PatternBasedFeatureGenerator& gen):
	includePatterns(gen.includePatterns), excludePatterns(gen.excludePatterns) {}

Chem::PatternBasedFeatureGenerator::~PatternBasedFeatureGenerator() {}

void Chem::PatternBasedFeatureGenerator::addIncludePattern(const MolecularGraph::SharedPointer& substruct, 
														   unsigned int type, double tol, unsigned int geom,
														   double length)
{
	includePatterns.push_back(FeaturePattern(substruct, type, tol, geom, length));
}

void Chem::PatternBasedFeatureGenerator::addExcludePattern(const MolecularGraph::SharedPointer& substruct)
{
	excludePatterns.push_back(substruct);
}
		
void Chem::PatternBasedFeatureGenerator::clearIncludePatterns()
{
	includePatterns.clear();
}

void Chem::PatternBasedFeatureGenerator::clearExcludePatterns()
{
	excludePatterns.clear();
}

void Chem::PatternBasedFeatureGenerator::generate(const MolecularGraph& molgraph, Pharmacophore& pharm)
{
	init(molgraph);

	getExcludeMatches();

	Util::BitSet* atom_mask = 0;
	SubstructureSearch& subsearch = getSubstructureSearch();

	subsearch.uniqueMappingsOnly(false);

	for (FeaturePatternList::const_iterator p_it = includePatterns.begin(), p_end = includePatterns.end(); p_it != p_end; ++p_it) {
		const FeaturePattern& ptn = *p_it;

		subsearch.setQuery(*ptn.substructQry);		
		subsearch.findMappings(molgraph);

		for (SubstructureSearch::ConstMappingIterator m_it = subsearch.getMappingsBegin(),
				 m_end = subsearch.getMappingsEnd(); m_it != m_end; ++m_it) {

			const AtomBondMapping& mapping = *m_it;

			if (!atom_mask)
				atom_mask = allocBitSet();

			createMatchedAtomMask(mapping.getAtomMapping(), *atom_mask, true);

			if (isContainedInList(*atom_mask, excludeMatches))
				continue;

			if (isContainedInList(*atom_mask, includeMatches))
				continue;
	
			addFeature(mapping, ptn, pharm);

			includeMatches.push_back(atom_mask);
			atom_mask = 0;
		}
	}

	if (atom_mask)
		freeBitSet(atom_mask);

	addNonPatternFeatures(molgraph, pharm);
}

Chem::PatternBasedFeatureGenerator& Chem::PatternBasedFeatureGenerator::operator=(const PatternBasedFeatureGenerator& gen)
{
	if (this == &gen)
		return *this;

	includePatterns = gen.includePatterns;
	excludePatterns = gen.excludePatterns;

	return *this;
}

Chem::SubstructureSearch& Chem::PatternBasedFeatureGenerator::getSubstructureSearch()
{
	if (!substructSearch) 
		substructSearch.reset(new SubstructureSearch());
	
	return *substructSearch;
}

void Chem::PatternBasedFeatureGenerator::addFeature(const AtomBondMapping& mapping, const FeaturePattern& ftr_ptn, 
													Pharmacophore& pharm)
{
	Feature& feature = pharm.addFeature();

	setType(feature, ftr_ptn.featureType);
	setTolerance(feature, ftr_ptn.featureTol);

	Fragment::SharedPointer substruct_ptr(new Fragment());
	
	posRefAtomList.clear();
	geomRefAtom1List.clear();
	geomRefAtom2List.clear();

	for (AtomMapping::ConstEntryIterator it = mapping.getAtomMapping().getEntriesBegin(), 
			 end = mapping.getAtomMapping().getEntriesEnd(); it != end; ++it) {

		const Atom& ptn_atom = *it->first;
		const Atom& mpd_atom = *it->second;

		std::size_t label = getReactionAtomMappingID(ptn_atom);

		if (label & FEATURE_ATOM_FLAG)
			substruct_ptr->addAtom(mpd_atom);
		
		if (label & POS_REF_ATOM_FLAG)
			posRefAtomList.push_back(&mpd_atom);

		if (label & GEOM_REF_ATOM1_FLAG)
			geomRefAtom1List.push_back(&mpd_atom);

		if (label & GEOM_REF_ATOM2_FLAG)
			geomRefAtom2List.push_back(&mpd_atom);
	}

	for (BondMapping::ConstEntryIterator it = mapping.getBondMapping().getEntriesBegin(), 
			 end = mapping.getBondMapping().getEntriesEnd(); it != end; ++it) {

		const Bond& mpd_bond = *it->second;

		if (substruct_ptr->containsAtom(mpd_bond.getBegin()) && substruct_ptr->containsAtom(mpd_bond.getEnd()))
			substruct_ptr->addBond(mpd_bond);
	}

	setSubstructure(feature, substruct_ptr);

	Math::Vector3D pos;

	if (calcCentroid(posRefAtomList, pos))
		set3DCoordinates(feature, pos);

	switch (ftr_ptn.featureGeom) {

		case FeatureGeometry::VECTOR: {
			Math::Vector3D orient;
			double length = calcVecFeatureOrientation(geomRefAtom1List, geomRefAtom2List, orient);

			if (length >= 0.0) {
				setOrientation(feature, orient);
				setLength(feature, ftr_ptn.vectorLength < 0.0 ? length : ftr_ptn.vectorLength);
			}

			break;
		}

		case FeatureGeometry::PLANE: {
			Math::Vector3D orient, tmp;

			if (calcPlaneFeatureOrientation(geomRefAtom1List, orient, tmp))
				setOrientation(feature, orient);
		}

		default:
			break;
	}

	setGeometry(feature, ftr_ptn.featureGeom);
}

double Chem::PatternBasedFeatureGenerator::calcVecFeatureOrientation(const AtomList& alist1, const AtomList& alist2, Math::Vector3D& orient) const
{
	Math::Vector3D org;

	if (!calcCentroid(alist1, org))
		return -1.0;
 
	if (!calcCentroid(alist2, orient))
		return -1.0;
 
	orient.minusAssign(org);

	double len = length(orient);

	orient /= len;

	return len;
}

bool Chem::PatternBasedFeatureGenerator::calcPlaneFeatureOrientation(const AtomList& alist, Math::Vector3D& orient, Math::Vector3D& centroid)
{
	if (!calcCentroid(alist, centroid))
		return false;

	std::size_t num_points = alist.size();

	svdU.resize(num_points, 3, false);
	
	for (std::size_t i = 0; i < num_points; i++)
		row(svdU, i) = get3DCoordinates(*alist[i]) - centroid;

	if (!svDecompose(svdU, svdW, svdV))
		return false;

	orient = column(svdV, 2);
	orient /= length(orient);

	return true;
}

bool Chem::PatternBasedFeatureGenerator::calcCentroid(const AtomList& alist, Math::Vector3D& centroid) const
{
	for (AtomList::const_iterator it = alist.begin(), end = alist.end(); it != end; ++it) {
		const Atom& atom = **it;

		if (!has3DCoordinates(atom))
			return false;

		centroid.plusAssign(get3DCoordinates(atom));
	}

	if (alist.size() == 0)
		return false;

	centroid /= double(alist.size());
	return true;
}

void Chem::PatternBasedFeatureGenerator::getExcludeMatches()
{
	SubstructureSearch& subsearch = getSubstructureSearch();

	subsearch.uniqueMappingsOnly(true);

	for (SubstructPatternList::const_iterator p_it = excludePatterns.begin(), p_end = excludePatterns.end(); p_it != p_end; ++p_it) {
		subsearch.setQuery(*p_it->get());		
		subsearch.findMappings(*molGraph);

		for (SubstructureSearch::ConstMappingIterator m_it = subsearch.getMappingsBegin(), 
				 m_end = subsearch.getMappingsEnd(); m_it != m_end; ++m_it) {

			Util::BitSet* atom_mask = allocBitSet();
			const AtomMapping& atom_mapping = m_it->getAtomMapping();

			createMatchedAtomMask(atom_mapping, *atom_mask, true);

			if (!atom_mask->any())
				createMatchedAtomMask(atom_mapping, *atom_mask, false);

			excludeMatches.push_back(atom_mask);
		}
	}
}

bool Chem::PatternBasedFeatureGenerator::isContainedInList(const Util::BitSet& atom_mask, const BitSetList& bset_list) const
{
	for (BitSetList::const_iterator it = bset_list.begin(), end = bset_list.end(); it != end; ++it)
		if (atom_mask.is_subset_of(**it))
			return true;

	return false;
}

bool Chem::PatternBasedFeatureGenerator::isContainedInIncMatchList(const Util::BitSet& atom_mask) const 
{
	return isContainedInList(atom_mask, includeMatches);
}

bool Chem::PatternBasedFeatureGenerator::isContainedInExMatchList(const Util::BitSet& atom_mask) const
{
	return isContainedInList(atom_mask, excludeMatches);
}

void Chem::PatternBasedFeatureGenerator::createMatchedAtomMask(const AtomMapping& mapping, Util::BitSet& atom_mask, bool check_label) const
{
	atom_mask.resize(molGraph->getNumAtoms());
	atom_mask.reset();

	for (AtomMapping::ConstEntryIterator it = mapping.getEntriesBegin(), end = mapping.getEntriesEnd(); it != end; ++it) {
		if (check_label) {
			std::size_t label = getReactionAtomMappingID(*it->first);

			if (!(label & FEATURE_ATOM_FLAG))
				continue;
		}

		atom_mask.set(molGraph->getAtomIndex(*it->second));
	}
}

void Chem::PatternBasedFeatureGenerator::init(const MolecularGraph& molgraph)
{
    molGraph = &molgraph;

	std::for_each(includeMatches.begin(), includeMatches.end(), 
				  boost::bind(&PatternBasedFeatureGenerator::freeBitSet, this, _1));

	std::for_each(excludeMatches.begin(), excludeMatches.end(), 
				  boost::bind(&PatternBasedFeatureGenerator::freeBitSet, this, _1));

	includeMatches.clear();
	excludeMatches.clear();
}

void Chem::PatternBasedFeatureGenerator::freeBitSet(Util::BitSet* bset)
{
	freeBitSets.push_back(bset);
}

Util::BitSet* Chem::PatternBasedFeatureGenerator::allocBitSet()
{
	if (freeBitSets.empty()) {
		BitSetPtr bset_ptr(new Util::BitSet());
	
		allocBitSets.push_back(bset_ptr);

		return bset_ptr.get();
	}

	Util::BitSet* bset = freeBitSets.back();

	freeBitSets.pop_back();

	return bset;	
}
