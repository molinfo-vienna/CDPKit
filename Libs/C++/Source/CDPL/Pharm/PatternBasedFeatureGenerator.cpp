/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PatternBasedFeatureGenerator.cpp 
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

#include <algorithm>

#include <boost/bind.hpp>

#include "CDPL/Pharm/PatternBasedFeatureGenerator.hpp"
#include "CDPL/Pharm/Pharmacophore.hpp"
#include "CDPL/Pharm/Feature.hpp"
#include "CDPL/Pharm/FeatureFunctions.hpp"
#include "CDPL/Pharm/FeatureGeometry.hpp"
#include "CDPL/Chem/Fragment.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Math/SVDecomposition.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace
{

	const std::size_t MAX_BIT_SET_CACHE_SIZE = 500;
}


using namespace CDPL; 


Pharm::PatternBasedFeatureGenerator::PatternBasedFeatureGenerator():
	bitSetCache(MAX_BIT_SET_CACHE_SIZE)
{}

Pharm::PatternBasedFeatureGenerator::PatternBasedFeatureGenerator(const PatternBasedFeatureGenerator& gen): 
	FeatureGenerator(gen), bitSetCache(MAX_BIT_SET_CACHE_SIZE)
{
	for (IncludePatternList::const_iterator it = gen.includePatterns.begin(), end = gen.includePatterns.end(); it != end; ++it)
		includePatterns.push_back(IncludePattern(it->subQuery, it->featureType, it->featureTol, it->featureGeom, it->vectorLength));

	for (ExcludePatternList::const_iterator it = gen.excludePatterns.begin(), end = gen.excludePatterns.end(); it != end; ++it)
		excludePatterns.push_back(ExcludePattern(it->subQuery));
}

Pharm::PatternBasedFeatureGenerator::~PatternBasedFeatureGenerator() {}

void Pharm::PatternBasedFeatureGenerator::addIncludePattern(const Chem::MolecularGraph::SharedPointer& substruct, 
															unsigned int type, double tol, unsigned int geom,
															double length)
{
	includePatterns.push_back(IncludePattern(substruct, type, tol, geom, length));
}

void Pharm::PatternBasedFeatureGenerator::addExcludePattern(const Chem::MolecularGraph::SharedPointer& substruct)
{
	excludePatterns.push_back(ExcludePattern(substruct));
}
		
void Pharm::PatternBasedFeatureGenerator::clearIncludePatterns()
{
	includePatterns.clear();
}

void Pharm::PatternBasedFeatureGenerator::clearExcludePatterns()
{
	excludePatterns.clear();
}

void Pharm::PatternBasedFeatureGenerator::generate(const Chem:: MolecularGraph& molgraph, Pharmacophore& pharm)
{
	using namespace Chem;

	init(molgraph);

	getExcludeMatches();

	Util::BitSet* atom_mask = 0;

	for (IncludePatternList::const_iterator p_it = includePatterns.begin(), p_end = includePatterns.end(); p_it != p_end; ++p_it) {
		const IncludePattern& ptn = *p_it;

		ptn.subSearch->findMappings(molgraph);

		for (SubstructureSearch::ConstMappingIterator m_it = ptn.subSearch->getMappingsBegin(),
				 m_end = ptn.subSearch->getMappingsEnd(); m_it != m_end; ++m_it) {

			const AtomBondMapping& mapping = *m_it;

			if (!atom_mask)
				atom_mask = bitSetCache.getRaw();

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

	addNonPatternFeatures(molgraph, pharm);
}

Pharm::FeatureGenerator::SharedPointer Pharm::PatternBasedFeatureGenerator::clone() const
{
	return FeatureGenerator::SharedPointer(new PatternBasedFeatureGenerator(*this));
}

Pharm::PatternBasedFeatureGenerator& Pharm::PatternBasedFeatureGenerator::operator=(const PatternBasedFeatureGenerator& gen)
{
	if (this == &gen)
		return *this;

	FeatureGenerator::operator=(gen);

	includePatterns.clear();

	for (IncludePatternList::const_iterator it = gen.includePatterns.begin(), end = gen.includePatterns.end(); it != end; ++it)
		includePatterns.push_back(IncludePattern(it->subQuery, it->featureType, it->featureTol, it->featureGeom, it->vectorLength));

	excludePatterns.clear();

	for (ExcludePatternList::const_iterator it = gen.excludePatterns.begin(), end = gen.excludePatterns.end(); it != end; ++it)
		excludePatterns.push_back(ExcludePattern(it->subQuery));

	return *this;
}

void Pharm::PatternBasedFeatureGenerator::addFeature(const Chem::AtomBondMapping& mapping, const IncludePattern& ftr_ptn, 
													 Pharmacophore& pharm)
{
	using namespace Chem;

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

		std::size_t label = getAtomMappingID(ptn_atom);

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

		case FeatureGeometry::SPHERE:
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

double Pharm::PatternBasedFeatureGenerator::calcVecFeatureOrientation(const AtomList& alist1, const AtomList& alist2, Math::Vector3D& orient) const
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

bool Pharm::PatternBasedFeatureGenerator::calcPlaneFeatureOrientation(const AtomList& alist, Math::Vector3D& orient, Math::Vector3D& centroid)
{
	if (!calcCentroid(alist, centroid))
		return false;

	std::size_t num_points = alist.size();
	const Chem::Atom3DCoordinatesFunction& coords_func = getAtom3DCoordinatesFunction();

	svdU.resize(num_points, 3, false);
	
	for (std::size_t i = 0; i < num_points; i++)
		row(svdU, i) = coords_func(*alist[i]) - centroid;

	if (!svDecompose(svdU, svdW, svdV))
		return false;

	orient = column(svdV, 2);
	orient /= length(orient);

	return true;
}

bool Pharm::PatternBasedFeatureGenerator::calcCentroid(const AtomList& alist, Math::Vector3D& centroid) const
{
	using namespace Chem;

	const Atom3DCoordinatesFunction& coords_func = getAtom3DCoordinatesFunction();

	if (coords_func.empty())
		return false;

	for (AtomList::const_iterator it = alist.begin(), end = alist.end(); it != end; ++it) {
		const Atom& atom = **it;

		try {
			centroid.plusAssign(coords_func(atom));
		} catch (const Base::ItemNotFound& e) {
			return false;
		} catch (...) {
			throw;
		}
	}

	if (alist.size() == 0)
		return false;

	centroid /= double(alist.size());
	return true;
}

void Pharm::PatternBasedFeatureGenerator::getExcludeMatches()
{
	using namespace Chem;

	for (ExcludePatternList::const_iterator p_it = excludePatterns.begin(), p_end = excludePatterns.end(); p_it != p_end; ++p_it) {
		const ExcludePattern& x_ptn = *p_it;

		x_ptn.subSearch->findMappings(*molGraph);

		for (SubstructureSearch::ConstMappingIterator m_it = x_ptn.subSearch->getMappingsBegin(), 
				 m_end = x_ptn.subSearch->getMappingsEnd(); m_it != m_end; ++m_it) {

			Util::BitSet* atom_mask = bitSetCache.getRaw();
			const AtomMapping& atom_mapping = m_it->getAtomMapping();

			createMatchedAtomMask(atom_mapping, *atom_mask, true);

			if (!atom_mask->any())
				createMatchedAtomMask(atom_mapping, *atom_mask, false);

			excludeMatches.push_back(atom_mask);
		}
	}
}

bool Pharm::PatternBasedFeatureGenerator::isContainedInList(const Util::BitSet& atom_mask, const BitSetList& bset_list) const
{
	for (BitSetList::const_iterator it = bset_list.begin(), end = bset_list.end(); it != end; ++it)
		if (atom_mask.is_subset_of(**it))
			return true;

	return false;
}

bool Pharm::PatternBasedFeatureGenerator::isContainedInIncMatchList(const Util::BitSet& atom_mask) const 
{
	return isContainedInList(atom_mask, includeMatches);
}

bool Pharm::PatternBasedFeatureGenerator::isContainedInExMatchList(const Util::BitSet& atom_mask) const
{
	return isContainedInList(atom_mask, excludeMatches);
}

void Pharm::PatternBasedFeatureGenerator::createMatchedAtomMask(const Chem::AtomMapping& mapping, Util::BitSet& atom_mask, bool check_label) const
{
	using namespace Chem;

	atom_mask.resize(molGraph->getNumAtoms());
	atom_mask.reset();

	for (AtomMapping::ConstEntryIterator it = mapping.getEntriesBegin(), end = mapping.getEntriesEnd(); it != end; ++it) {
		if (check_label) {
			std::size_t label = getAtomMappingID(*it->first);

			if (!(label & FEATURE_ATOM_FLAG))
				continue;
		}

		atom_mask.set(molGraph->getAtomIndex(*it->second));
	}
}

void Pharm::PatternBasedFeatureGenerator::init(const Chem::MolecularGraph& molgraph)
{
    molGraph = &molgraph;

	includeMatches.clear();
	excludeMatches.clear();

	bitSetCache.putAll();
}
