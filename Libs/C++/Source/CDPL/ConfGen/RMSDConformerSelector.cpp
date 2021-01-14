/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * RMSDConformerSelector.cpp 
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

#include <cmath>
#include <algorithm>
#include <cassert>
#include <cstddef>

#include <boost/bind.hpp>

#include "CDPL/ConfGen/RMSDConformerSelector.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/HybridizationState.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/ForceField/UtilityFunctions.hpp"
#include "CDPL/Math/VectorArrayFunctions.hpp"
#include "CDPL/Base/Exceptions.hpp"


namespace
{

	const std::size_t MAX_INDEX_ARRAY_CACHE_SIZE           = 1000;
	const std::size_t MAX_VECTOR_ARRAY_CACHE_SIZE          = 2000;
	const double      MIN_TETRAHEDRAL_ATOM_GEOM_OOP_ANGLE  = 10.0 / 180.0 * M_PI;
	const std::size_t ABORT_CALLBACK_ALIGNMENT_COUNT       = 10;
	const std::size_t ABORT_CALLBACK_SYM_MAPPING_COUNT     = 1;
}


using namespace CDPL;


const std::size_t ConfGen::RMSDConformerSelector::DEF_MAX_NUM_SYMMETRY_MAPPINGS;


ConfGen::RMSDConformerSelector::RMSDConformerSelector(): 
	idxArrayCache(MAX_INDEX_ARRAY_CACHE_SIZE), vecArrayCache(MAX_VECTOR_ARRAY_CACHE_SIZE), 
	molGraph(0), minRMSD(0.0), maxNumSymMappings(DEF_MAX_NUM_SYMMETRY_MAPPINGS)
{
	using namespace Chem;

	symMappingSearch.includeIdentityMapping(true);
	symMappingSearch.setAtomPropertyFlags(AtomPropertyFlag::TYPE | AtomPropertyFlag::FORMAL_CHARGE | AtomPropertyFlag::AROMATICITY |
										  AtomPropertyFlag::EXPLICIT_BOND_COUNT | AtomPropertyFlag::HYBRIDIZATION_STATE);
	symMappingSearch.setBondPropertyFlags(BondPropertyFlag::ORDER | BondPropertyFlag::TOPOLOGY |
										  BondPropertyFlag::AROMATICITY);
	symMappingSearch.setFoundMappingCallback(
		boost::bind(&ConfGen::RMSDConformerSelector::processSymMapping, this, _1, _2));
}

void ConfGen::RMSDConformerSelector::setMinRMSD(double min_rmsd)
{
    minRMSD = min_rmsd;
}

double ConfGen::RMSDConformerSelector::getMinRMSD() const
{
    return minRMSD;
}

void ConfGen::RMSDConformerSelector::setAbortCallback(const CallbackFunction& func)
{
	abortCallback = func;
}

const ConfGen::CallbackFunction& ConfGen::RMSDConformerSelector::getAbortCallback() const
{
	return abortCallback;
}

void ConfGen::RMSDConformerSelector::setup(const Chem::MolecularGraph& molgraph, const Util::BitSet& atom_mask)
{
	molGraph = &molgraph;

	buildSymMappingSearchMolGraph(atom_mask);

	atomStereoDescrs.clear();
	idxArrayCache.putAll();
	confAlignCoords.clear();
	selectedConfAlignCoords.clear();
	symMappings.clear();
}

void ConfGen::RMSDConformerSelector::setup(const Chem::MolecularGraph& molgraph, const Util::BitSet& atom_mask, 
										   const Util::BitSet& stable_config_atom_mask, const Math::Vector3DArray& coords)
{
	setup(molgraph, atom_mask);
	setupSymMappingValidationData(stable_config_atom_mask, coords);
}

std::size_t ConfGen::RMSDConformerSelector::getNumSymmetryMappings() const 
{
	return symMappings.size();
}

void ConfGen::RMSDConformerSelector::setMaxNumSymmetryMappings(std::size_t max_num)
{
	maxNumSymMappings = max_num;
}

std::size_t ConfGen::RMSDConformerSelector::getMaxNumSymmetryMappings() const
{
	return maxNumSymMappings;
}

bool ConfGen::RMSDConformerSelector::selected(const Math::Vector3DArray& conf_coords)
{
	if (symMappings.empty()) {
		symMappingSearch.findMappings(symMappingSearchMolGraph);
		
		if (symMappings.empty())
			throw Base::OperationFailed("RMSDConformerSelector: could not perceive molecular graph automorphism group");
	}

	if (abortCallback && abortCallback())
		return false;

	if (!selectedConfAlignCoords.empty()) {
		std::size_t num_mappings = symMappings.size();
		bool first_pass = true;
		Math::Matrix4D conf_xform;
		std::size_t num_perf_almnts = 0;
		
		confAlignCoords.clear();
		
		for (VectorArrayList::const_reverse_iterator it = selectedConfAlignCoords.rbegin(), end = selectedConfAlignCoords.rend(); 
			 it != end; ++it, first_pass = false) {

			const Math::Vector3DArray& sel_conf_algn_coords = **it;

			for (std::size_t i = 0; i < num_mappings; i++) {
				if (first_pass) 
					confAlignCoords.push_back(buildCoordsArrayForMapping(*symMappings[i], conf_coords));
				
				if (!alignmentCalc.calculate(sel_conf_algn_coords, *confAlignCoords[i], false)) 
					return false;

				conf_xform.assign(alignmentCalc.getTransform());

				double rmsd = calcRMSD(sel_conf_algn_coords, *confAlignCoords[i], conf_xform);

				if (rmsd < minRMSD) 
					return false;

				if (abortCallback && ++num_perf_almnts == ABORT_CALLBACK_ALIGNMENT_COUNT) {
					if (abortCallback())
						return false;

					num_perf_almnts = 0;
				}
			}
		}

		selectedConfAlignCoords.push_back(confAlignCoords.front());

	} else
		selectedConfAlignCoords.push_back(buildCoordsArrayForMapping(*symMappings.front(), conf_coords));

	return true;
}

void ConfGen::RMSDConformerSelector::buildSymMappingSearchMolGraph(const Util::BitSet& atom_mask)
{
	using namespace Chem;

	symMappingSearchMolGraph.clear();

	for (Util::BitSet::size_type i = atom_mask.find_first(); i != Util::BitSet::npos; i = atom_mask.find_next(i)) 
		symMappingSearchMolGraph.addAtom(molGraph->getAtom(i));

	for (MolecularGraph::ConstBondIterator it = molGraph->getBondsBegin(), end = molGraph->getBondsEnd(); it != end; ++it) {
		const Bond& bond = *it;

		if (symMappingSearchMolGraph.containsAtom(bond.getBegin()) && symMappingSearchMolGraph.containsAtom(bond.getEnd()))
			symMappingSearchMolGraph.addBond(bond);
	}
}

void ConfGen::RMSDConformerSelector::setupSymMappingValidationData(const Util::BitSet& stable_config_atom_mask,
																   const Math::Vector3DArray& conf_coords)
{
	using namespace Chem;

	atomStereoDescrs.clear();

	for (Util::BitSet::size_type i = stable_config_atom_mask.find_first(); i != Util::BitSet::npos; i = stable_config_atom_mask.find_next(i)) {
		const Atom& atom = molGraph->getAtom(i);

		if (getHybridizationState(atom) != HybridizationState::SP3)
			continue;

		atomNeighbors.clear();

		std::size_t nbr_cnt = getConnectedAtoms(atom, symMappingSearchMolGraph, std::back_inserter(atomNeighbors));

		if (nbr_cnt < 3 || nbr_cnt > 4)
			continue;

		std::size_t nbr_atom1_idx = molGraph->getAtomIndex(*atomNeighbors[0]);
		std::size_t nbr_atom2_idx = molGraph->getAtomIndex(*atomNeighbors[1]);
		std::size_t nbr_atom3_idx = molGraph->getAtomIndex(*atomNeighbors[2]);
		std::size_t nbr_atom4_idx = (nbr_cnt == 4 ? molGraph->getAtomIndex(*atomNeighbors[3]) : i);

		const Math::Vector3D& nbr_atom1_coords = conf_coords[nbr_atom1_idx];
		const Math::Vector3D& nbr_atom2_coords = conf_coords[nbr_atom2_idx];
		const Math::Vector3D& nbr_atom3_coords = conf_coords[nbr_atom3_idx];
		const Math::Vector3D& nbr_atom4_coords = conf_coords[nbr_atom4_idx];

		if (nbr_cnt == 3) {
			double oop_angle = ForceField::calcOutOfPlaneAngle<double>(nbr_atom1_coords, nbr_atom4_coords, nbr_atom2_coords, nbr_atom3_coords);

			if (std::abs(oop_angle) < MIN_TETRAHEDRAL_ATOM_GEOM_OOP_ANGLE)
				continue;
		}

		double vol = innerProd(crossProd(nbr_atom4_coords - nbr_atom2_coords, nbr_atom4_coords - nbr_atom1_coords), 
							   nbr_atom4_coords - nbr_atom3_coords); 
		unsigned int config = (vol > 0.0 ? AtomConfiguration::S : vol < 0.0 ? AtomConfiguration::R : AtomConfiguration::NONE);

		if (config == AtomConfiguration::NONE)
			continue;
		
		if (nbr_cnt == 3) 
			atomStereoDescrs.insert(AtomStereoDescriptorMap::value_type(&atom, StereoDescriptor(config, *atomNeighbors[0], 
																								*atomNeighbors[1], *atomNeighbors[2])));
		else
			atomStereoDescrs.insert(AtomStereoDescriptorMap::value_type(&atom, StereoDescriptor(config, *atomNeighbors[0], 
																								*atomNeighbors[1], *atomNeighbors[2], 
																								*atomNeighbors[3])));
	}
}

bool ConfGen::RMSDConformerSelector::processSymMapping(const Chem::MolecularGraph& molgraph, const Chem::AtomBondMapping& mapping)
{
	using namespace Chem;
	
	if (abortCallback && (symMappings.size() % ABORT_CALLBACK_SYM_MAPPING_COUNT) == 0 && abortCallback()) {
		symMappingSearch.stopSearch();
		return false;
	}

	if (maxNumSymMappings > 0 && symMappings.size() >= maxNumSymMappings) {
		symMappingSearch.stopSearch();
		return false;
	}
	
	if (!isValidSymMapping(mapping))
		return false;

	IndexArray* idx_mapping = idxArrayCache.getRaw();
	const AtomMapping& atom_mapping = mapping.getAtomMapping();

	idx_mapping->clear();

	for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(), end = molgraph.getAtomsEnd(); it != end; ++it) {
		const Atom* mpd_atom = atom_mapping[&*it];

		assert(mpd_atom);

		idx_mapping->push_back(molGraph->getAtomIndex(*mpd_atom));
	}

	symMappings.push_back(idx_mapping);
	
	return false;
}

bool ConfGen::RMSDConformerSelector::isValidSymMapping(const Chem::AtomBondMapping& mapping) const
{
	using namespace Chem;

	if (atomStereoDescrs.empty())
		return true;

	const AtomMapping& atom_mapping = mapping.getAtomMapping();

	for (AtomStereoDescriptorMap::const_iterator it = atomStereoDescrs.begin(), end = atomStereoDescrs.end(); it != end; ++it) {
		const Atom* atom = it->first;
		const Atom* mpd_atom = atom_mapping[atom];
		
		if (!mpd_atom)
			continue;

		AtomStereoDescriptorMap::const_iterator mpd_atom_stereo_it = atomStereoDescrs.find(mpd_atom);
		
		if (mpd_atom_stereo_it == end)
			continue;

		const StereoDescriptor& atom_stereo = it->second;
		const Atom* const* ref_atoms = atom_stereo.getReferenceAtoms();
		std::size_t num_ref_atoms = atom_stereo.getNumReferenceAtoms();
		const Atom* mpd_ref_atoms[4] = { 0 };
		bool valid = true;

		for (std::size_t i = 0; i < num_ref_atoms; i++) {
			if ((mpd_ref_atoms[i] = atom_mapping[ref_atoms[i]]))
				continue;

			valid = false;
			break;
		}

		if (!valid)
			continue;

		const StereoDescriptor& mpd_atom_stereo = mpd_atom_stereo_it->second;
		unsigned int perm_parity = (num_ref_atoms == 4 ? 
									mpd_atom_stereo.getPermutationParity(*mpd_ref_atoms[0], *mpd_ref_atoms[1], *mpd_ref_atoms[2], *mpd_ref_atoms[3]) :
									mpd_atom_stereo.getPermutationParity(*mpd_ref_atoms[0], *mpd_ref_atoms[1], *mpd_ref_atoms[2]));

		switch (perm_parity) {

			case 1:
				if (atom_stereo.getConfiguration() == mpd_atom_stereo.getConfiguration()) 
					return false;
				break;

			case 2:
				if (atom_stereo.getConfiguration() != mpd_atom_stereo.getConfiguration())
					return false;

			default:
				break;
		}
	}

	return true;
}

ConfGen::RMSDConformerSelector::VectorArrayPtr 
ConfGen::RMSDConformerSelector::buildCoordsArrayForMapping(const IndexArray& mapping, const Math::Vector3DArray& conf_coords)
{
	VectorArrayPtr coords_ptr = vecArrayCache.get();
	Math::Vector3DArray& coords = *coords_ptr;
	Math::Vector3DArray::StorageType& coords_data = coords.getData();
	std::size_t arr_size = mapping.size();
	Math::Vector3D ctr;

	coords.resize(arr_size);

	for (std::size_t i = 0; i < arr_size; i++) {
		const Math::Vector3D& pos = conf_coords[mapping[i]];

		ctr.plusAssign(pos);
		coords_data[i].assign(pos);
	}

	ctr /= arr_size;

	for (Math::Vector3DArray::ElementIterator it = coords.getElementsBegin(), end = coords.getElementsEnd(); it != end; ++it)
		it->minusAssign(ctr);

	return coords_ptr;
}
