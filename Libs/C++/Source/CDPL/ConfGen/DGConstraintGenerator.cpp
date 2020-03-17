/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * DGConstraintGenerator.cpp 
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
#include <numeric>

#include <boost/tuple/tuple_comparison.hpp>
#include <boost/bind.hpp>

#include "CDPL/ConfGen/DGConstraintGenerator.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Chem/HybridizationState.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/ForceField/MMFF94InteractionData.hpp"
#include "CDPL/ForceField/MMFF94BondStretchingInteractionData.hpp"
#include "CDPL/ForceField/MMFF94BondStretchingInteraction.hpp"
#include "CDPL/ForceField/MMFF94AngleBendingInteractionData.hpp"
#include "CDPL/ForceField/MMFF94AngleBendingInteraction.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


std::size_t ConfGen::DGConstraintGenerator::BondLengthKeyHash::operator()(const BondLengthKey& k) const 
{
	std::size_t hash = 0;

	boost::hash_combine(hash, k.first);
	boost::hash_combine(hash, k.second);

	return hash;
}

std::size_t ConfGen::DGConstraintGenerator::BondAngleKeyHash::operator()(const BondAngleKey& k) const 
{
	std::size_t hash = 0;

	boost::hash_combine(hash, k.get<0>());
	boost::hash_combine(hash, k.get<1>());
	boost::hash_combine(hash, k.get<2>());

	return hash;
}


ConfGen::DGConstraintGenerator::DGConstraintGenerator(): 
	molGraph(0), settings(DGConstraintGeneratorSettings::DEFAULT) 
{}

ConfGen::DGConstraintGeneratorSettings& ConfGen::DGConstraintGenerator::getSettings()
{
	return settings;
}

const ConfGen::DGConstraintGeneratorSettings& ConfGen::DGConstraintGenerator::getSettings() const
{
	return settings;
}

const Util::BitSet& ConfGen::DGConstraintGenerator::getExcludedHydrogenMask() const
{
	return hAtomMask;
}

std::size_t ConfGen::DGConstraintGenerator::getNumAtomStereoCenters() const
{
	return atomStereoData.size();
}

std::size_t ConfGen::DGConstraintGenerator::getNumBondStereoCenters() const
{
	return bondStereoData.size();
}

const ConfGen::DGConstraintGenerator::StereoCenterData& 
ConfGen::DGConstraintGenerator::getAtomStereoCenterData(std::size_t idx) const
{
	if (idx >= atomStereoData.size())
		throw Base::IndexError("DGConstraintGenerator: atom stereo center index out of bounds");

	return atomStereoData[idx];
}

const ConfGen::DGConstraintGenerator::StereoCenterData& 
ConfGen::DGConstraintGenerator::getBondStereoCenterData(std::size_t idx) const
{
	if (idx >= bondStereoData.size())
		throw Base::IndexError("DGConstraintGenerator: bond stereo center index out of bounds");

	return bondStereoData[idx];
}

ConfGen::DGConstraintGenerator::ConstStereoCenterDataIterator 
ConfGen::DGConstraintGenerator::getAtomStereoCenterDataBegin() const
{
	return atomStereoData.begin();
}

ConfGen::DGConstraintGenerator::ConstStereoCenterDataIterator 
ConfGen::DGConstraintGenerator::getAtomStereoCenterDataEnd() const
{
	return atomStereoData.end();
}

ConfGen::DGConstraintGenerator::ConstStereoCenterDataIterator 
ConfGen::DGConstraintGenerator::getBondStereoCenterDataBegin() const
{
	return bondStereoData.begin();
}

ConfGen::DGConstraintGenerator::ConstStereoCenterDataIterator 
ConfGen::DGConstraintGenerator::getBondStereoCenterDataEnd() const
{
	return bondStereoData.end();
}

void ConfGen::DGConstraintGenerator::addAtomStereoCenter(const Chem::Atom& atom, const Chem::StereoDescriptor& descr)
{
	using namespace Chem;

	if (descr.getConfiguration() != AtomConfiguration::R && descr.getConfiguration() != AtomConfiguration::S)
		return;

	if (!descr.isValid(atom))
		return;

	std::size_t num_ref_atoms = descr.getNumReferenceAtoms();
	bool excl_hs = settings.excludeHydrogens();

	for (std::size_t i = 0; i < num_ref_atoms; i++) {
		const Atom* ref_atom = descr.getReferenceAtoms()[i];

		if (!molGraph->containsAtom(*ref_atom)) 
			return;

		if (excl_hs)
			hAtomMask.reset(molGraph->getAtomIndex(*ref_atom));
	}

	atomStereoData.push_back(StereoCenterData(molGraph->getAtomIndex(atom), descr));
}

void ConfGen::DGConstraintGenerator::addBondStereoCenter(const Chem::Bond& bond, const Chem::StereoDescriptor& descr)
{
	using namespace Chem;
	
	if (descr.getConfiguration() != BondConfiguration::CIS && descr.getConfiguration() != BondConfiguration::TRANS)
		return;

	if (!molGraph->containsBond(bond))
		return;

	if (!molGraph->containsAtom(bond.getBegin()))
		return;

	if (!molGraph->containsAtom(bond.getEnd()))
		return;

	if (!descr.isValid(bond))
		return;

	if (!molGraph->containsAtom(*descr.getReferenceAtoms()[0]) || !molGraph->containsAtom(*descr.getReferenceAtoms()[3]))
		return;

	if (settings.excludeHydrogens()) {
		for (std::size_t i = 0; i < 2; i++) {
			const Atom& atom = bond.getAtom(i);
			Atom::ConstBondIterator b_it = atom.getBondsBegin();

			for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
				if (!molGraph->containsBond(*b_it))
					continue;

				if (!molGraph->containsAtom(*a_it))
					continue;

				hAtomMask.reset(molGraph->getAtomIndex(*a_it));
			}
		}
	}

	bondStereoData.push_back(StereoCenterData(molGraph->getBondIndex(bond), descr));
}

void CDPL::ConfGen::DGConstraintGenerator::setup(const Chem::MolecularGraph& molgraph, 
												 const ForceField::MMFF94InteractionData& ia_data)
{
	setup(molgraph, &ia_data);
}

void CDPL::ConfGen::DGConstraintGenerator::setup(const Chem::MolecularGraph& molgraph) 
{
	setup(molgraph, 0);
}

void CDPL::ConfGen::DGConstraintGenerator::setup(const Chem::MolecularGraph& molgraph, 
												 const ForceField::MMFF94InteractionData* ia_data)
{
    init(molgraph);
  
	if (settings.regardAtomConfiguration())
		extractAtomStereoCenterData();

	if (settings.regardBondConfiguration())
		extractBondStereoCenterData();

	assignBondLengths(ia_data);
    assignBondAngles(ia_data);
}

void ConfGen::DGConstraintGenerator::addBondLengthConstraints(Util::DG3DCoordinatesGenerator& coords_gen)
{
	for (BondLengthTable::const_iterator it = bondLengthTable.begin(), end = bondLengthTable.end(); it != end; ++it) {
		double bond_len = it->second;
		std::size_t atom1_idx = it->first.first;
		std::size_t atom2_idx = it->first.second;

		if (atomPairProcessed(atom1_idx, atom2_idx))
			continue;

		coords_gen.addDistanceConstraint(atom1_idx, atom2_idx, bond_len, bond_len);

		markAtomPairProcessed(atom1_idx, atom2_idx);
	}
}

void ConfGen::DGConstraintGenerator::addBondAngleConstraints(Util::DG3DCoordinatesGenerator& coords_gen)
{
	for (BondAngleTable::const_iterator it = bondAngleTable.begin(), end = bondAngleTable.end(); it != end; ++it) {
		std::size_t atom1_idx = it->first.get<0>();
		std::size_t atom2_idx = it->first.get<1>();
		std::size_t atom3_idx = it->first.get<2>();

		if (atomPairProcessed(atom1_idx, atom3_idx))
			continue;

		double angle = it->second;
		double bond1_len = getBondLength(atom2_idx, atom1_idx);
		double bond2_len = getBondLength(atom2_idx, atom3_idx);

		double dist = calc13AtomDistance(bond1_len, bond2_len, angle);

		coords_gen.addDistanceConstraint(atom1_idx, atom3_idx, dist, dist);
		coords_gen.addDistanceConstraint(atom1_idx, atom3_idx, dist, dist); // overemphasize for less distored structures
		coords_gen.addDistanceConstraint(atom1_idx, atom3_idx, dist, dist);
		coords_gen.addDistanceConstraint(atom1_idx, atom3_idx, dist, dist); 
		coords_gen.addDistanceConstraint(atom1_idx, atom3_idx, dist, dist);

		markAtomPairProcessed(atom1_idx, atom3_idx);
	}
}

void ConfGen::DGConstraintGenerator::addDefaultDistanceConstraints(Util::DG3DCoordinatesGenerator& coords_gen)
{
	using namespace Chem;

	if (!molGraph)
		return;

	double bond_length_sum = std::accumulate(bondLengthTable.begin(), bondLengthTable.end(), double(),
											 boost::bind(std::plus<double>(), _1,
														 boost::bind(&BondLengthTable::value_type::second, _2)));
	bool excl_hs = settings.excludeHydrogens();

	for (std::size_t i = 0; i < numAtoms; i++) {
		if (excl_hs && hAtomMask.test(i))
			continue;

		double cov_rad1 = AtomDictionary::getCovalentRadius(getType(molGraph->getAtom(i)));

		for (std::size_t j = i + 1; j < numAtoms; j++) {
			if (excl_hs && hAtomMask.test(j))
				continue;

			if (atomPairProcessed(i, j))
				continue;

			double cov_rad2 = AtomDictionary::getCovalentRadius(getType(molGraph->getAtom(j)));

			coords_gen.addDistanceConstraint(i, j, cov_rad1 + cov_rad2 + 1.5, bond_length_sum);

			markAtomPairProcessed(i, j);
		}
	}
}

void ConfGen::DGConstraintGenerator::add14DistanceConstraints(Util::DG3DCoordinatesGenerator& coords_gen)
{
	using namespace Chem;

	if (!molGraph)
		return;

	bool excl_hs = settings.excludeHydrogens();

	for (MolecularGraph::ConstBondIterator it = molGraph->getBondsBegin(), end = molGraph->getBondsEnd(); it != end; ++it) {
		const Bond& bond = *it;
		const Atom& atom1 = bond.getBegin();

		if (!molGraph->containsAtom(atom1))
			continue;

		std::size_t atom1_idx = molGraph->getAtomIndex(atom1);

		if (excl_hs && hAtomMask.test(atom1_idx))
			continue;

		const Atom& atom2 = bond.getEnd();

		if (!molGraph->containsAtom(atom2))
			continue;

		std::size_t atom2_idx = molGraph->getAtomIndex(atom2);

		if (excl_hs && hAtomMask.test(atom2_idx))
			continue;

		if (getNeighborAtoms(atom1, atomIndexList1, &atom2) == 0)
			continue;
	
		if (getNeighborAtoms(atom2, atomIndexList2, &atom1) == 0)
			continue;

		double bond_len = getBondLength(atom1_idx, atom2_idx);

		for (std::size_t i = 0, num_nbrs1 = atomIndexList1.size(); i < num_nbrs1; i++) {
			std::size_t nbr_atom1_idx = atomIndexList1[i];
			double nbr_bond1_angle = getBondAngle(nbr_atom1_idx, atom1_idx, atom2_idx);

			if (nbr_bond1_angle <= 0.0)
				continue;

			double nbr_bond1_len = getBondLength(nbr_atom1_idx, atom1_idx);

			for (std::size_t j = 0, num_nbrs2 = atomIndexList2.size(); j < num_nbrs2; j++) {
				std::size_t nbr_atom2_idx = atomIndexList2[j];

				if (atomPairProcessed(nbr_atom1_idx, nbr_atom2_idx))
					continue;

				double nbr_bond2_angle = getBondAngle(nbr_atom2_idx, atom2_idx, atom1_idx);
				
				if (nbr_bond2_angle <= 0.0)
					continue;

				double nbr_bond2_len = getBondLength(nbr_atom2_idx, atom2_idx);

				double cis_dist = calcCis14AtomDistance(nbr_bond1_len, bond_len, nbr_bond2_len, nbr_bond1_angle, nbr_bond2_angle);				
				double trans_dist = calcTrans14AtomDistance(nbr_bond1_len, bond_len, nbr_bond2_len, nbr_bond1_angle, nbr_bond2_angle);				

				coords_gen.addDistanceConstraint(nbr_atom1_idx, nbr_atom2_idx, cis_dist, trans_dist);

				markAtomPairProcessed(nbr_atom1_idx, nbr_atom2_idx);
			}
		}
	}
}

void ConfGen::DGConstraintGenerator::addAtomConfigurationConstraints(Util::DG3DCoordinatesGenerator& coords_gen)
{
	using namespace Chem;

	for (ConstStereoCenterDataIterator it = atomStereoData.begin(), end = atomStereoData.end(); it != end; ++it) {
		const Chem::StereoDescriptor& descr = it->second;
		double lb = 0.5;
		double ub = 1000.0;

		if (descr.getConfiguration() == AtomConfiguration::R) {
			ub = -0.5;
			lb = -1000.0;
		}

		std::size_t atom_idx = it->first;

		stereoAtomMask.set(atom_idx);

		coords_gen.addVolumeConstraint(molGraph->getAtomIndex(*descr.getReferenceAtoms()[0]),
									   molGraph->getAtomIndex(*descr.getReferenceAtoms()[1]),
									   molGraph->getAtomIndex(*descr.getReferenceAtoms()[2]),
									   descr.getNumReferenceAtoms() == 3 ? 
									   atom_idx : molGraph->getAtomIndex(*descr.getReferenceAtoms()[3]),
									   lb, ub);
	}
}

void ConfGen::DGConstraintGenerator::addBondConfigurationConstraints(Util::DG3DCoordinatesGenerator& coords_gen)
{
	using namespace Chem;

	for (ConstStereoCenterDataIterator it = bondStereoData.begin(), end = bondStereoData.end(); it != end; ++it) {
		const Bond& bond = molGraph->getBond(it->first);
		const Atom& atom1 = bond.getBegin();
		const Atom& atom2 = bond.getEnd();

		const Chem::StereoDescriptor& descr = it->second;
		unsigned int ref_config = descr.getConfiguration();

		std::size_t ref_atom1_idx = molGraph->getAtomIndex(*descr.getReferenceAtoms()[0]);
		std::size_t ref_atom2_idx = molGraph->getAtomIndex(*descr.getReferenceAtoms()[3]);
		std::size_t atom1_idx = molGraph->getAtomIndex(atom1);
		std::size_t atom2_idx = molGraph->getAtomIndex(atom2);

		if (getNeighborAtoms(atom1, atomIndexList1, &atom2) == 0)
			continue;
	
		if (getNeighborAtoms(atom2, atomIndexList2, &atom1) == 0)
			continue;

		double bond_len = getBondLength(atom1_idx, atom2_idx);

		for (std::size_t i = 0, num_nbrs1 = atomIndexList1.size(); i < num_nbrs1; i++) {
			std::size_t nbr_atom1_idx = atomIndexList1[i];
			double nbr_bond1_angle = getBondAngle(nbr_atom1_idx, atom1_idx, atom2_idx);

			if (nbr_bond1_angle <= 0.0)
				continue;

			double nbr_bond1_len = getBondLength(nbr_atom1_idx, atom1_idx);

			for (std::size_t j = 0, num_nbrs2 = atomIndexList2.size(); j < num_nbrs2; j++) {
				std::size_t nbr_atom2_idx = atomIndexList2[j];
				double nbr_bond2_angle = getBondAngle(nbr_atom2_idx, atom2_idx, atom1_idx);
				
				if (nbr_bond2_angle <= 0.0)
					continue;

				double nbr_bond2_len = getBondLength(nbr_atom2_idx, atom2_idx);
				double nbr_atom_dist = 0.0;
				unsigned int config = (nbr_atom1_idx == ref_atom1_idx) ^ (nbr_atom2_idx == ref_atom2_idx) ? 
					(ref_config == BondConfiguration::TRANS ? BondConfiguration::CIS : BondConfiguration::TRANS) :
					(ref_config == BondConfiguration::CIS ? BondConfiguration::CIS : BondConfiguration::TRANS);

				if (config == BondConfiguration::CIS)
					nbr_atom_dist = calcCis14AtomDistance(nbr_bond1_len, bond_len, nbr_bond2_len, nbr_bond1_angle, nbr_bond2_angle);	
				else
					nbr_atom_dist = calcTrans14AtomDistance(nbr_bond1_len, bond_len, nbr_bond2_len, nbr_bond1_angle, nbr_bond2_angle);

				coords_gen.addDistanceConstraint(nbr_atom1_idx, nbr_atom2_idx, nbr_atom_dist, nbr_atom_dist);

				markAtomPairProcessed(nbr_atom1_idx, nbr_atom2_idx);
			}
		}
	}
}

void ConfGen::DGConstraintGenerator::addAtomPlanarityConstraints(Util::DG3DCoordinatesGenerator& coords_gen)
{
	using namespace Chem;

	if (!molGraph)
		return;

	bool excl_hs = settings.excludeHydrogens();

	for (std::size_t i = 0; i < numAtoms; i++) {
		if (excl_hs && hAtomMask.test(i))
			continue;

		if (settings.regardAtomConfiguration() && stereoAtomMask.test(i))
			continue;

		const Atom& atom = molGraph->getAtom(i);

		if (!isPlanar(atom))
			continue;

		if (getNeighborAtoms(atom, atomIndexList1) != 3)
			continue;

		coords_gen.addVolumeConstraint(i, atomIndexList1[0], atomIndexList1[1], atomIndexList1[2], 0.0, 0.0);
	}
}

void ConfGen::DGConstraintGenerator::addBondPlanarityConstraints(Util::DG3DCoordinatesGenerator& coords_gen)
{
	using namespace Chem;

	if (!molGraph)
		return;

	bool excl_hs = settings.excludeHydrogens();

	for (MolecularGraph::ConstBondIterator it = molGraph->getBondsBegin(), end = molGraph->getBondsEnd(); it != end; ++it) {
		const Bond& bond = *it;
		const Atom& atom1 = bond.getBegin();

		if (!molGraph->containsAtom(atom1))
			continue;

		std::size_t atom1_idx = molGraph->getAtomIndex(atom1);

		if (excl_hs && hAtomMask.test(atom1_idx))
			continue;

		if (settings.regardAtomConfiguration() && stereoAtomMask.test(atom1_idx))
			continue;

		const Atom& atom2 = bond.getEnd();

		if (!molGraph->containsAtom(atom2))
			continue;

		std::size_t atom2_idx = molGraph->getAtomIndex(atom2);

		if (excl_hs && hAtomMask.test(atom2_idx))
			continue;

		if (settings.regardAtomConfiguration() && stereoAtomMask.test(atom1_idx))
			continue;

		if (!isPlanar(bond))
			continue;

		std::size_t num_nbrs1 = getNeighborAtoms(atom1, atomIndexList1, &atom2);

		if (num_nbrs1 < 1 && num_nbrs1 > 2)
			continue;
	
		std::size_t num_nbrs2 = getNeighborAtoms(atom2, atomIndexList2, &atom1);

		if (num_nbrs2 < 1 && num_nbrs2 > 2)
			continue;
	
		for (std::size_t i = 0; i < num_nbrs1; i++) {
			std::size_t nbr_atom1_idx = atomIndexList1[i];

			for (std::size_t j = 0; j < num_nbrs2; j++) {
				std::size_t nbr_atom2_idx = atomIndexList2[j];

				coords_gen.addVolumeConstraint(atom1_idx, nbr_atom1_idx, nbr_atom2_idx, atom2_idx, 0.0, 0.0);
			}
		}
	}
}

void ConfGen::DGConstraintGenerator::init(const Chem::MolecularGraph& molgraph)
{
	molGraph = &molgraph;

	bondLengthTable.clear();
	bondAngleTable.clear();
	atomStereoData.clear();
	bondStereoData.clear();

    numAtoms = molgraph.getNumAtoms();
	
	procAtomPairMask.resize(numAtoms * numAtoms);
	procAtomPairMask.reset();

	hAtomMask.resize(numAtoms);

    if (settings.excludeHydrogens())
		buildAtomTypeMask(molgraph, hAtomMask, Chem::AtomType::H);

	if (settings.regardAtomConfiguration()) {
		stereoAtomMask.resize(numAtoms);
		stereoAtomMask.reset();
	}
}

void ConfGen::DGConstraintGenerator::assignBondLengths(const ForceField::MMFF94InteractionData* ia_data)
{
	using namespace ForceField;
	using namespace Chem;

	bool excl_hs = settings.excludeHydrogens();

	if (ia_data) {
		const MMFF94BondStretchingInteractionData& bs_data = ia_data->getBondStretchingInteractions();
	
		for (MMFF94BondStretchingInteractionData::ConstElementIterator it = bs_data.getElementsBegin(), end = bs_data.getElementsEnd(); it != end; ++it) {
			const MMFF94BondStretchingInteraction& iactn = *it;

			std::size_t atom1_idx = iactn.getAtom1Index();

			if (atom1_idx >= numAtoms)
				continue;

			std::size_t atom2_idx = iactn.getAtom2Index();

			if (atom2_idx >= numAtoms)
				continue;

			if (excl_hs && (hAtomMask.test(atom1_idx) || hAtomMask.test(atom2_idx)))
				continue;

			setBondLength(atom1_idx, atom2_idx, iactn.getReferenceLength());
		} 
	}

	// Fallback

	for (MolecularGraph::ConstBondIterator it = molGraph->getBondsBegin(), end = molGraph->getBondsEnd(); it != end; ++it) {
		const Bond& bond = *it;
		const Atom& atom1 = bond.getBegin();

		if (!molGraph->containsAtom(atom1))
			continue;

		const Atom& atom2 = bond.getEnd();

		if (!molGraph->containsAtom(atom2))
			continue;

		std::size_t atom1_idx = molGraph->getAtomIndex(atom1);
		std::size_t atom2_idx = molGraph->getAtomIndex(atom2);

		if (excl_hs && (hAtomMask.test(atom1_idx) || hAtomMask.test(atom2_idx)))
			continue;
	
		if (getBondLength(atom1_idx, atom2_idx) >= 0.0)
			continue;

		std::size_t order = getOrder(bond);
		double cov_rad1 = AtomDictionary::getCovalentRadius(getType(atom1), order);
		double cov_rad2 = AtomDictionary::getCovalentRadius(getType(atom2), order);

		setBondLength(atom1_idx, atom2_idx, cov_rad1 + cov_rad2);
	}
}

void ConfGen::DGConstraintGenerator::assignBondAngles(const ForceField::MMFF94InteractionData* ia_data)
{
	using namespace ForceField;
	using namespace Chem;

	const FragmentList& sssr = *getSSSR(*molGraph);
	bool excl_hs = settings.excludeHydrogens();

	if (ia_data) {
		const MMFF94AngleBendingInteractionData& bs_data = ia_data->getAngleBendingInteractions();
	
		for (MMFF94AngleBendingInteractionData::ConstElementIterator it = bs_data.getElementsBegin(), end = bs_data.getElementsEnd(); it != end; ++it) {
			const MMFF94AngleBendingInteraction& iactn = *it;

			std::size_t term_atom1_idx = iactn.getTerminalAtom1Index();

			if (term_atom1_idx >= numAtoms)
				continue;

			std::size_t ctr_atom_idx = iactn.getCenterAtomIndex();

			if (ctr_atom_idx >= numAtoms)
				continue;
	
			std::size_t term_atom2_idx = iactn.getTerminalAtom2Index();

			if (term_atom2_idx >= numAtoms)
				continue;
	
			if (excl_hs && (hAtomMask.test(term_atom1_idx) || hAtomMask.test(ctr_atom_idx) || hAtomMask.test(term_atom2_idx)))
				continue;

			if (iactn.isLinearAngle())
				setBondAngle(term_atom1_idx, ctr_atom_idx, term_atom2_idx, M_PI);
			else
				setBondAngle(term_atom1_idx, ctr_atom_idx, term_atom2_idx, std::abs(iactn.getReferenceAngle()) * M_PI / 180.0);
		} 
	}

	// Fallback

	for (std::size_t i = 0; i < numAtoms; i++) {
		if (excl_hs && hAtomMask.test(i))
			continue;

		const Atom& ctr_atom = molGraph->getAtom(i);
		double angle = 0.0;

		switch (getHybridizationState(ctr_atom)) {

			case HybridizationState::SP1:
				angle = M_PI;
				break;

			case HybridizationState::SP2:
				angle = M_PI * 120.0 / 180.0;
				break;

			case HybridizationState::SP3:
				angle = M_PI * 109.5 / 180.0;
				break;
				
			default:
				continue;
		}

		bool ring_check = getRingFlag(ctr_atom);
		Atom::ConstBondIterator nb_it1 = ctr_atom.getBondsBegin();

		for (Atom::ConstAtomIterator na_it1 = ctr_atom.getAtomsBegin(), na_end = ctr_atom.getAtomsEnd(); na_it1 != na_end; ++na_it1) {
			const Atom& term_atom1 = *na_it1;
			const Bond& term_bond1 = *nb_it1;

			if (!molGraph->containsAtom(term_atom1) || !molGraph->containsBond(term_bond1))
				continue;

			std::size_t term_atom1_idx = molGraph->getAtomIndex(term_atom1);

			if (excl_hs && hAtomMask.test(term_atom1_idx))
				continue;

			bool term_bond1_in_ring = (ring_check ? getRingFlag(term_bond1) : false);
			Atom::ConstBondIterator nb_it2 = ++nb_it1;

			for (Atom::ConstAtomIterator na_it2 = na_it1 + 1; na_it2 != na_end; ++na_it2) {
				const Atom& term_atom2 = *na_it2;
				const Bond& term_bond2 = *nb_it2;

				if (!molGraph->containsAtom(term_atom2) || !molGraph->containsBond(term_bond2))
					continue;

				std::size_t term_atom2_idx = molGraph->getAtomIndex(term_atom2);

				if (excl_hs && hAtomMask.test(term_atom2_idx))
					continue;

				if (getBondAngle(term_atom1_idx, i, term_atom2_idx) >= 0.0)
					continue;

				if (term_bond1_in_ring && getRingFlag(term_bond2)) {
					switch (getSmallestRingSize(sssr, term_bond1, term_bond2)) {

						case 3:
							setBondAngle(term_atom1_idx, i, term_atom2_idx,  M_PI * 60.0 / 180.0);
							continue;

						case 4:
							if (angle == M_PI * 109.5 / 180.0) 
								setBondAngle(term_atom1_idx, i, term_atom2_idx,  M_PI * 88.5 / 180.0);
							else
								setBondAngle(term_atom1_idx, i, term_atom2_idx,  M_PI * 90.0 / 180.0);
							continue;

						default:
							break;
					}
				}

				setBondAngle(term_atom1_idx, i, term_atom2_idx, angle);
			}
		}
	}
}

void ConfGen::DGConstraintGenerator::extractAtomStereoCenterData()
{
	using namespace Chem;

	for (MolecularGraph::ConstAtomIterator it = molGraph->getAtomsBegin(), end = molGraph->getAtomsEnd(); it != end; ++it) {
		const Atom& atom = *it;
		const StereoDescriptor& descr = getStereoDescriptor(atom);

		addAtomStereoCenter(atom, descr);
	}
}

void ConfGen::DGConstraintGenerator::extractBondStereoCenterData()
{
	using namespace Chem;

	for (MolecularGraph::ConstBondIterator it = molGraph->getBondsBegin(), end = molGraph->getBondsEnd(); it != end; ++it) {
		const Bond& bond = *it;
		const StereoDescriptor& descr = getStereoDescriptor(bond);

		addBondStereoCenter(bond, descr);
	}
}

void ConfGen::DGConstraintGenerator::setBondLength(std::size_t atom1_idx, std::size_t atom2_idx, double length)
{
	if (atom1_idx > atom2_idx)
		std::swap(atom1_idx, atom2_idx);

	bondLengthTable[BondLengthKey(atom1_idx, atom2_idx)] = length;
}

double ConfGen::DGConstraintGenerator::getBondLength(std::size_t atom1_idx, std::size_t atom2_idx) const
{
	if (atom1_idx > atom2_idx)
		std::swap(atom1_idx, atom2_idx);

	BondLengthTable::const_iterator it = bondLengthTable.find(BondLengthKey(atom1_idx, atom2_idx));

	if (it == bondLengthTable.end())
		return -1.0;

	return it->second;
}

void ConfGen::DGConstraintGenerator::setBondAngle(std::size_t atom1_idx, std::size_t atom2_idx, std::size_t atom3_idx, double angle)
{
	if (atom1_idx > atom3_idx)
		std::swap(atom1_idx, atom3_idx);

	bondAngleTable[BondAngleKey(atom1_idx, atom2_idx, atom3_idx)] = angle;
}

double ConfGen::DGConstraintGenerator::getBondAngle(std::size_t atom1_idx, std::size_t atom2_idx, std::size_t atom3_idx) const
{
	if (atom1_idx > atom3_idx)
		std::swap(atom1_idx, atom3_idx);

	BondAngleTable::const_iterator it = bondAngleTable.find(BondAngleKey(atom1_idx, atom2_idx, atom3_idx));

	if (it == bondAngleTable.end())
		return -1.0;

	return it->second;
}

std::size_t ConfGen::DGConstraintGenerator::getSmallestRingSize(const Chem::FragmentList& sssr, const Chem::Bond& bond1, 
																const Chem::Bond& bond2) const
{
	using namespace Chem;

	std::size_t sm_size = 0;

	for (FragmentList::ConstElementIterator it = sssr.getElementsBegin(), end = sssr.getElementsEnd(); it != end; ++it) {
		const Fragment& ring = *it;

		if (!ring.containsBond(bond1) || !ring.containsBond(bond2))
			continue;

		if (sm_size == 0)
			sm_size = ring.getNumAtoms();
		else
			sm_size = std::min(sm_size, ring.getNumAtoms());
	}

	return sm_size;
} 

std::size_t ConfGen::DGConstraintGenerator::getSmallestRingSize(const Chem::FragmentList& sssr, std::size_t atom1_idx, std::size_t atom2_idx) const
{
	using namespace Chem;

	std::size_t sm_size = 0;
	const Atom& atom1 = molGraph->getAtom(atom1_idx);
	const Atom& atom2 = molGraph->getAtom(atom2_idx);

	for (FragmentList::ConstElementIterator it = sssr.getElementsBegin(), end = sssr.getElementsEnd(); it != end; ++it) {
		const Fragment& ring = *it;

		if (!ring.containsAtom(atom1) || !ring.containsAtom(atom2))
			continue;

		if (sm_size == 0)
			sm_size = ring.getNumAtoms();
		else
			sm_size = std::min(sm_size, ring.getNumAtoms());
	}

	return sm_size;
} 

void ConfGen::DGConstraintGenerator::markAtomPairProcessed(std::size_t atom1_idx, std::size_t atom2_idx)
{
	if (atom1_idx > atom2_idx)
		std::swap(atom1_idx, atom2_idx);

	procAtomPairMask.set(atom1_idx * numAtoms + atom2_idx);
}

bool ConfGen::DGConstraintGenerator::atomPairProcessed(std::size_t atom1_idx, std::size_t atom2_idx) const
{
	if (atom1_idx > atom2_idx)
		std::swap(atom1_idx, atom2_idx);

	return procAtomPairMask.test(atom1_idx * numAtoms + atom2_idx);
}

double ConfGen::DGConstraintGenerator::calc13AtomDistance(double bond1_len, double bond2_len, double angle) const
{
	double r1_2 = bond1_len * bond1_len;
	double r2_2 = bond2_len * bond2_len;
	double x = 2 * bond1_len * bond2_len * std::cos(angle);

	return std::sqrt(r1_2 + r2_2 - x);
}

double ConfGen::DGConstraintGenerator::calcCis14AtomDistance(double bond1_len, double bond2_len, double bond3_len, 
															 double angle_12, double angle_23) const
{
	return (bond2_len - bond1_len * std::cos(angle_12) - bond3_len * std::cos(angle_23));
}

double ConfGen::DGConstraintGenerator::calcTrans14AtomDistance(double bond1_len, double bond2_len, double bond3_len, 
															   double angle_12, double angle_23) const
{
	double x1 = bond1_len * std::cos(angle_12);
	double y1 = bond1_len * std::sin(angle_12);
	double x4 = bond2_len - bond3_len * std::cos(angle_23);
	double y4 = -bond3_len * std::sin(angle_23);

	double dx = x4 - x1;
	double dy = y4 - y1;

	return std::sqrt(dx * dx + dy * dy);
}

bool ConfGen::DGConstraintGenerator::isPlanar(const Chem::Atom& atom) const
{
	using namespace Chem;

	if (getHybridizationState(atom) == HybridizationState::SP2)
		return true;

	if (getAromaticityFlag(atom))
		return true;

	return isPlanarNitrogen(atom, *molGraph);
}

bool ConfGen::DGConstraintGenerator::isPlanar(const Chem::Bond& bond) const
{
	using namespace Chem;

	if (getAromaticityFlag(bond))
		return true;

	std::size_t order = getOrder(bond);

	if (order == 3)
		return true;

	const Atom& atom1 = bond.getBegin();
	const Atom& atom2 = bond.getEnd();

	if (order == 2)
		return ((getHybridizationState(atom1) == HybridizationState::SP2 || getAromaticityFlag(atom1)) &&
				(getHybridizationState(atom2) == HybridizationState::SP2 || getAromaticityFlag(atom2)));

	return isAmideBond(bond, *molGraph, true, false);
}

std::size_t ConfGen::DGConstraintGenerator::getNeighborAtoms(const Chem::Atom& atom, AtomIndexList& idx_list, const Chem::Atom* x_atom) const
{
	using namespace Chem;

	idx_list.clear();

	Atom::ConstBondIterator b_it = atom.getBondsBegin();
	bool excl_hs = settings.excludeHydrogens();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
		const Atom& nbr_atom = *a_it;

		if (&nbr_atom == x_atom)
			continue;

		if (!molGraph->containsAtom(nbr_atom))
			continue;

		if (!molGraph->containsBond(*b_it))
			continue;

		std::size_t atom_idx = molGraph->getAtomIndex(nbr_atom);

		if (excl_hs && hAtomMask.test(atom_idx))
			continue;

		idx_list.push_back(atom_idx);
	}

	return idx_list.size();
}
