/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentTreeNode.cpp 
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

#include <cmath>

#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/ForceField/MMFF94EnergyFunctions.hpp"

#include "FragmentTreeNode.hpp"
#include "FragmentTree.hpp"
#include "ForceFieldInteractionMask.hpp"


using namespace CDPL;


namespace
{

	template <typename InteractionData>
	void extractFragmentMMFF94InteractionParams2(const InteractionData& src_ia_data, InteractionData& tgt_ia_data,
												 Util::BitSet& free_ia_mask, const Util::BitSet& tgt_atom_mask)
	{
		for (Util::BitSet::size_type i = free_ia_mask.find_first(); i != Util::BitSet::npos; i = free_ia_mask.find_next(i)) {
			const typename InteractionData::ElementType& params = src_ia_data[i];

			if (tgt_atom_mask.test(params.getAtom1Index()) && 
				tgt_atom_mask.test(params.getAtom2Index())) {

				tgt_ia_data.addElement(params);
				free_ia_mask.reset(i);
			}
		}
	}

	template <typename InteractionData>
	void extractFragmentMMFF94InteractionParams3(const InteractionData& src_ia_data, InteractionData& tgt_ia_data,
												 Util::BitSet& free_ia_mask, const Util::BitSet& tgt_atom_mask)
	{
		for (Util::BitSet::size_type i = free_ia_mask.find_first(); i != Util::BitSet::npos; i = free_ia_mask.find_next(i)) {
			const typename InteractionData::ElementType& params = src_ia_data[i];

			if (tgt_atom_mask.test(params.getAtom1Index()) &&
				tgt_atom_mask.test(params.getAtom2Index()) && 
				tgt_atom_mask.test(params.getAtom3Index())) {

				tgt_ia_data.addElement(params);
				free_ia_mask.reset(i);
			}
		}
	}

	template <typename InteractionData>
	void extractFragmentMMFF94InteractionParams4(const InteractionData& src_ia_data, InteractionData& tgt_ia_data,
												 Util::BitSet& free_ia_mask, const Util::BitSet& tgt_atom_mask)
	{
		for (Util::BitSet::size_type i = free_ia_mask.find_first(); i != Util::BitSet::npos; i = free_ia_mask.find_next(i)) {
			const typename InteractionData::ElementType& params = src_ia_data[i];

			if (tgt_atom_mask.test(params.getAtom1Index()) &&
				tgt_atom_mask.test(params.getAtom2Index()) && 
				tgt_atom_mask.test(params.getAtom3Index()) &&
				tgt_atom_mask.test(params.getAtom4Index())) {

				tgt_ia_data.addElement(params);
				free_ia_mask.reset(i);
			}
		}
	}

	const double CONFORMER_LINEUP_SPACING        = 4.0;
	const double ATOM_CLASH_VDW_ENERGY_THRESHOLD = 5.0;
	const double MAX_TORSION_REF_BOND_ANGLE_COS  = std::cos(5.0 / 180.0 * M_PI);
}


ConfGen::FragmentTreeNode::FragmentTreeNode(ConfGen::FragmentTree& owner): 
	owner(owner), parent(0), splitBond(0), splitBondLength(0.0), rootMolGraph(), fragment(0)
{
	splitBondAtoms[0] = 0;
	splitBondAtoms[1] = 0;

	torsionRefAtoms[0] = 0;
	torsionRefAtoms[1] = 0;
}

ConfGen::FragmentTreeNode* ConfGen::FragmentTreeNode::getParent()
{
	return parent;
}

const ConfGen::FragmentTreeNode* ConfGen::FragmentTreeNode::getParent() const
{
	return parent;
}

const Chem::MolecularGraph* ConfGen::FragmentTreeNode::getFragment() const
{
	return fragment;
}

const Chem::MolecularGraph* ConfGen::FragmentTreeNode::getRootMolecularGraph() const
{
	return rootMolGraph;
}

const Chem::Bond* ConfGen::FragmentTreeNode::getSplitBond() const
{
	return splitBond;
}

void ConfGen::FragmentTreeNode:: setSplitBondLength(double length)
{
	splitBondLength = length;
}

double ConfGen::FragmentTreeNode::getSplitBondLength() const
{
	return splitBondLength;
}

const Chem::Atom* const* ConfGen::FragmentTreeNode::getSplitBondAtoms() const
{
	return splitBondAtoms;
}

const Chem::Atom* const* ConfGen::FragmentTreeNode::getTorsionReferenceAtoms() const
{
	return torsionRefAtoms;
}

void ConfGen::FragmentTreeNode::setTorsionReferenceAtoms(const Chem::Atom* left, const Chem::Atom* right)
{
	torsionRefAtoms[0] = left;
	torsionRefAtoms[1] = right;
}

bool ConfGen::FragmentTreeNode::hasChildren() const
{
	return (leftChild && rightChild);
}

ConfGen::FragmentTreeNode* ConfGen::FragmentTreeNode::getLeftChild()
{
	return leftChild;
}

ConfGen::FragmentTreeNode* ConfGen::FragmentTreeNode::getRightChild()
{
	return rightChild;
}

const ConfGen::FragmentTreeNode* ConfGen::FragmentTreeNode::getLeftChild() const
{
	return leftChild;
}

const ConfGen::FragmentTreeNode* ConfGen::FragmentTreeNode::getRightChild() const
{
	return rightChild;
}

const ConfGen::FragmentTreeNode::ConformerDataArray& ConfGen::FragmentTreeNode::getConformers() const
{
	return conformers;
}

ConfGen::FragmentTreeNode::ConformerDataArray& ConfGen::FragmentTreeNode::getConformers()
{
	return conformers;
}

const ConfGen::FragmentTreeNode::IndexArray& ConfGen::FragmentTreeNode::getAtomIndices() const
{
	return atomIndices;
}

const Util::BitSet& ConfGen::FragmentTreeNode::getAtomMask() const
{
	return atomMask;
}

const Util::BitSet& ConfGen::FragmentTreeNode::getCoreAtomMask() const
{
	return coreAtomMask;
}

const ConfGen::FragmentTreeNode::TorsionAngleArray& ConfGen::FragmentTreeNode::getTorsionAngles() const
{
	return torsionAngles;
}

ConfGen::FragmentTreeNode::TorsionAngleArray& ConfGen::FragmentTreeNode::getTorsionAngles()
{
	return torsionAngles;
}

ForceField::MMFF94InteractionData& ConfGen::FragmentTreeNode::getMMFF94Parameters()
{
	return mmff94Data;
}

const ForceField::MMFF94InteractionData& ConfGen::FragmentTreeNode::getMMFF94Parameters() const
{
	return mmff94Data;
}

void ConfGen::FragmentTreeNode::distributeMMFF94Parameters(const ForceField::MMFF94InteractionData& ia_data,
														   ForceFieldInteractionMask& ia_mask)
{
	if (hasChildren()) {
		leftChild->distributeMMFF94Parameters(ia_data, ia_mask);
		rightChild->distributeMMFF94Parameters(ia_data, ia_mask);
	}

	extractFragmentMMFF94InteractionParams2(ia_data.getBondStretchingInteractions(), mmff94Data.getBondStretchingInteractions(), 
											ia_mask.bondStretching, coreAtomMask);
	extractFragmentMMFF94InteractionParams2(ia_data.getElectrostaticInteractions(), mmff94Data.getElectrostaticInteractions(), 
											ia_mask.electrostatic, coreAtomMask);
	extractFragmentMMFF94InteractionParams2(ia_data.getVanDerWaalsInteractions(), mmff94Data.getVanDerWaalsInteractions(), 
											ia_mask.vanDerWaals, coreAtomMask);
	extractFragmentMMFF94InteractionParams3(ia_data.getAngleBendingInteractions(), mmff94Data.getAngleBendingInteractions(), 
											ia_mask.angleBending, atomMask);
	extractFragmentMMFF94InteractionParams3(ia_data.getStretchBendInteractions(), mmff94Data.getStretchBendInteractions(), 
											ia_mask.stretchBend, atomMask);
	extractFragmentMMFF94InteractionParams4(ia_data.getOutOfPlaneBendingInteractions(), mmff94Data.getOutOfPlaneBendingInteractions(), 
											ia_mask.outOfPlaneBending, atomMask);
	extractFragmentMMFF94InteractionParams4(ia_data.getTorsionInteractions(), mmff94Data.getTorsionInteractions(), 
											ia_mask.torsion, atomMask);
}

void ConfGen::FragmentTreeNode::clearConformersDownwards()
{
	conformers.clear();

	if (hasChildren()) {
		leftChild->clearConformersDownwards();
		rightChild->clearConformersDownwards();
	}
}

void ConfGen::FragmentTreeNode::clearConformersUpwards()
{
	conformers.clear();

	if (parent)
		parent->clearConformersUpwards();
}

void ConfGen::FragmentTreeNode::addConformer(const Math::Vector3DArray& src_coords, bool calc_energy)
{
	ConformerData::SharedPointer new_conf = owner.allocConformerData();

	copyCoordinates(src_coords, atomIndices, *new_conf);

	new_conf->setEnergy(calc_energy ? calcMMFF94Energy(src_coords) : 0.0);

	conformers.push_back(new_conf);
}

void ConfGen::FragmentTreeNode::generateConformers()
{
	if (!conformers.empty() || !hasChildren())
		return;

	leftChild->generateConformers();
	rightChild->generateConformers();

	if (!splitBondAtoms[0] || !splitBondAtoms[1])
		lineupChildConformers();
	else
		alignAndRotateChildConformers();
}

void ConfGen::FragmentTreeNode::lineupChildConformers()
{
	std::size_t num_right_chld_confs = rightChild->conformers.size();

	childConfBounds.resize(2 * num_right_chld_confs);

	for (std::size_t i = 0; i < num_right_chld_confs; i++)
		calcConformerBounds(childConfBounds[i], childConfBounds[num_right_chld_confs + i], rightChild->atomIndices, *rightChild->conformers[i]);

	Math::Vector3D left_conf_bbox_min;
	Math::Vector3D::ConstPointer left_conf_bbox_min_data = left_conf_bbox_min.getData();
	Math::Vector3D left_conf_bbox_max;
	Math::Vector3D::ConstPointer left_conf_bbox_max_data = left_conf_bbox_max.getData();

	for (std::size_t i = 0, num_left_chld_confs = leftChild->conformers.size(); i < num_left_chld_confs; i++) {
		const ConformerData& left_conf = *leftChild->conformers[i];

		calcConformerBounds(left_conf_bbox_min, left_conf_bbox_max, leftChild->atomIndices, left_conf);

		for (std::size_t j = 0; j < num_right_chld_confs; j++) {
			Math::Vector3D::ConstPointer right_conf_bbox_min_data = childConfBounds[j].getData();
			Math::Vector3D::ConstPointer right_conf_bbox_max_data = childConfBounds[num_right_chld_confs + j].getData();

			double conf_trans[3] = {
			    left_conf_bbox_max_data[0] + CONFORMER_LINEUP_SPACING - right_conf_bbox_min_data[0],
				(left_conf_bbox_max_data[1] + left_conf_bbox_min_data[1]) * 0.5 - (right_conf_bbox_max_data[1] + left_conf_bbox_min_data[1]) * 0.5,
				(left_conf_bbox_max_data[2] + left_conf_bbox_min_data[2]) * 0.5 - (right_conf_bbox_max_data[2] + left_conf_bbox_min_data[2]) * 0.5
			};

			ConformerData::SharedPointer new_conf = owner.allocConformerData();

			copyCoordinates(left_conf, leftChild->atomIndices, *new_conf);

			const ConformerData& right_conf = *rightChild->conformers[j];
			const Math::Vector3DArray::StorageType& right_conf_data = right_conf.getData();
			Math::Vector3DArray::StorageType& new_conf_data = new_conf->getData();

			for (IndexArray::const_iterator it = rightChild->atomIndices.begin(), end = rightChild->atomIndices.end(); it != end; ++it) {
				std::size_t idx = *it;
				Math::Vector3D::ConstPointer atom_pos_data = right_conf_data[idx].getData();
				Math::Vector3D::Pointer new_atom_pos_data = new_conf_data[idx].getData();

				new_atom_pos_data[0] = atom_pos_data[0] + conf_trans[0];
				new_atom_pos_data[1] = atom_pos_data[1] + conf_trans[1];
				new_atom_pos_data[2] = atom_pos_data[2] + conf_trans[2];
			}

			new_conf->setEnergy(left_conf.getEnergy() + right_conf.getEnergy());

			conformers.push_back(new_conf);
		}
	}
}

void ConfGen::FragmentTreeNode::alignAndRotateChildConformers()
{
	std::size_t num_tor_angles = torsionAngles.size();

	if (num_tor_angles > 0 && torsionAngleSines.empty()) {
		for (TorsionAngleArray::const_iterator it = torsionAngles.begin(), end = torsionAngles.end(); it != end; ++it) {
			double angle = M_PI * (*it) / 180.0;

			torsionAngleSines.push_back(std::sin(angle));
			torsionAngleCosines.push_back(std::cos(angle));
		}
	}

	std::size_t left_atom_idx = rootMolGraph->getAtomIndex(*splitBondAtoms[0]);
	std::size_t right_atom_idx = rootMolGraph->getAtomIndex(*splitBondAtoms[1]);

	std::size_t num_left_chld_confs = leftChild->conformers.size();
	std::size_t num_right_chld_confs = rightChild->conformers.size();

	double almnt_mtx[3][3];
	Math::Vector3D bond_vec;
	Math::Vector3D tor_ref_vec;

	for (std::size_t i = 0, tor_ref_atom_idx = torsionRefAtoms[0] ? rootMolGraph->getAtomIndex(*torsionRefAtoms[0]) : 0; i < num_left_chld_confs; i++) {
		ConformerData& conf = *leftChild->conformers[i];
		const Math::Vector3DArray::StorageType& conf_data = conf.getData();
		bool check_ref_vec_angle = true;

		bond_vec.assign(conf_data[right_atom_idx]);
		bond_vec.minusAssign(conf_data[left_atom_idx]);
		bond_vec /= length(bond_vec);

		if (torsionRefAtoms[0]) {
			tor_ref_vec.assign(conf_data[tor_ref_atom_idx]);
			tor_ref_vec.minusAssign(conf_data[left_atom_idx]);
			tor_ref_vec /= length(tor_ref_vec);
		
		} else if (torsionRefAtoms[1])
			calcVirtualTorsionReferenceAtomVector(conf, left_atom_idx, tor_ref_vec);

		else {
			calcOrthogonalVector(bond_vec, tor_ref_vec);
			check_ref_vec_angle = false;
		}

		calcAlignmentMatrix(bond_vec, tor_ref_vec, almnt_mtx, check_ref_vec_angle);
		alignCoordinates(almnt_mtx, conf, leftChild->atomIndices, left_atom_idx, right_atom_idx, 0.0);
	}

	for (std::size_t i = 0, tor_ref_atom_idx = torsionRefAtoms[1] ? rootMolGraph->getAtomIndex(*torsionRefAtoms[1]) : 0; i < num_right_chld_confs; i++) {
		ConformerData& conf = *rightChild->conformers[i];
		const Math::Vector3DArray::StorageType& conf_data = conf.getData();
		bool check_ref_vec_angle = true;

		bond_vec.assign(conf_data[right_atom_idx]);
		bond_vec.minusAssign(conf_data[left_atom_idx]);

		double bond_len = length(bond_vec);

		bond_vec /= bond_len;

		if (splitBondLength > 0.0)
			bond_len = splitBondLength;

		if (torsionRefAtoms[1]) {
			tor_ref_vec.assign(conf_data[tor_ref_atom_idx]);
			tor_ref_vec.minusAssign(conf_data[right_atom_idx]);
			tor_ref_vec /= length(tor_ref_vec);

		} else if (torsionRefAtoms[0])
			calcVirtualTorsionReferenceAtomVector(conf, right_atom_idx, tor_ref_vec);

		else {
			calcOrthogonalVector(bond_vec, tor_ref_vec);
			check_ref_vec_angle = false;
		}

		calcAlignmentMatrix(bond_vec, tor_ref_vec, almnt_mtx, check_ref_vec_angle);
		alignCoordinates(almnt_mtx, conf, rightChild->atomIndices, right_atom_idx, left_atom_idx, bond_len);
	}

	for (std::size_t i = 0, num_left_chld_confs = leftChild->conformers.size(); i < num_left_chld_confs; i++) {
		const ConformerData& left_conf = *leftChild->conformers[i];

		for (std::size_t j = 0; j < num_right_chld_confs; j++) {
			const ConformerData& right_conf = *rightChild->conformers[j];

			if (num_tor_angles == 0) {
				ConformerData::SharedPointer new_conf = owner.allocConformerData();

				copyCoordinates(left_conf, leftChild->atomIndices, *new_conf, right_atom_idx);
				copyCoordinates(right_conf, rightChild->atomIndices, *new_conf, left_atom_idx);

				new_conf->setEnergy(left_conf.getEnergy() + right_conf.getEnergy());

				conformers.push_back(new_conf);

			} else {
				for (std::size_t k = 0; k < num_tor_angles; k++) {
					ConformerData::SharedPointer new_conf = owner.allocConformerData();

					copyCoordinates(left_conf, leftChild->atomIndices, *new_conf, right_atom_idx);
					rotateCoordinates(right_conf, rightChild->atomIndices, *new_conf, 
									  torsionAngleSines[k], torsionAngleCosines[k], left_atom_idx);

					bool atom_clash = false;
					double node_ia_energy = calcMMFF94Energy(*new_conf, atom_clash);

					if (!atom_clash) {
						new_conf->setEnergy(left_conf.getEnergy() + right_conf.getEnergy() + node_ia_energy);

						conformers.push_back(new_conf);
					}
				}
			}
		}
	}
}

void ConfGen::FragmentTreeNode::setParent(FragmentTreeNode* node)
{
	parent = node;
}

void ConfGen::FragmentTreeNode::setSplitBond(const Chem::Bond* bond)
{
	splitBond = bond;
}

void ConfGen::FragmentTreeNode::setSplitBondAtoms(const Chem::Atom* left, const Chem::Atom* right)
{
	splitBondAtoms[0] = left;
	splitBondAtoms[1] = right;
}

void ConfGen::FragmentTreeNode::setChildren(FragmentTreeNode* left, FragmentTreeNode* right)
{
	leftChild = left;
	rightChild = right;
}

void ConfGen::FragmentTreeNode::setFragment(const Chem::MolecularGraph* frag)
{
	fragment = frag;
}

void ConfGen::FragmentTreeNode::setRootMolecularGraph(const Chem::MolecularGraph* root_molgraph)
{
	rootMolGraph = root_molgraph;
}

void ConfGen::FragmentTreeNode::initFragmentData()
{
	if (!hasChildren()) // sanity check
		return;
		
	atomMask = leftChild->atomMask;
	atomMask |= rightChild->atomMask;

	coreAtomMask = leftChild->coreAtomMask;
	coreAtomMask |= rightChild->coreAtomMask;

	atomIndices.clear();

	for (Util::BitSet::size_type i = atomMask.find_first(); i != Util::BitSet::npos; i = atomMask.find_next(i))
		atomIndices.push_back(i);
}

void ConfGen::FragmentTreeNode::initFragmentData(const Chem::MolecularGraph& frag, const Chem::MolecularGraph& root_molgraph)
{
	using namespace Chem;

	std::size_t num_atoms = root_molgraph.getNumAtoms();

	atomMask.resize(num_atoms);
	atomMask.reset();

	coreAtomMask.resize(num_atoms);
	coreAtomMask.reset();

	atomIndices.clear();

	for (MolecularGraph::ConstAtomIterator it = frag.getAtomsBegin(), end = frag.getAtomsEnd(); it != end; ++it) {
		const Atom& atom = *it;
		std::size_t atom_idx = root_molgraph.getAtomIndex(atom);

		atomIndices.push_back(atom_idx);
		atomMask.set(atom_idx);

		if (getExplicitBondCount(atom, frag) == 1 && getExplicitBondCount(atom, root_molgraph) > 1) // is connected fragment atom?
			continue;

		coreAtomMask.set(atom_idx);
	}
}

void ConfGen::FragmentTreeNode::clearTorsionDrivingData()
{
	torsionAngles.clear();
	torsionAngleSines.clear();
	torsionAngleCosines.clear();

	torsionRefAtoms[0] = 0;
	torsionRefAtoms[1] = 0;
}

void ConfGen::FragmentTreeNode::calcConformerBounds(Math::Vector3D& min, Math::Vector3D& max, const IndexArray& atom_inds, 
													const Math::Vector3DArray& coords) const
{
	Math::Vector3D::Pointer min_data = min.getData();
	Math::Vector3D::Pointer max_data = max.getData();
	const Math::Vector3DArray::StorageType& coords_data = coords.getData();

	bool init = true;

	for (IndexArray::const_iterator it = atom_inds.begin(), end = atom_inds.end(); it != end; ++it) {
		Math::Vector3D::ConstPointer atom_pos_data = coords_data[*it].getData();

		if (init) {
			min_data[0] = atom_pos_data[0];
			min_data[1] = atom_pos_data[1];
			min_data[2] = atom_pos_data[2];

			max_data[0] = atom_pos_data[0];
			max_data[1] = atom_pos_data[1];
			max_data[2] = atom_pos_data[2];
		
			init = false;
			continue;
		}

		if (atom_pos_data[0] > max_data[0])
			max_data[0] = atom_pos_data[0];

		else if (atom_pos_data[0] < min_data[0])
			min_data[0] = atom_pos_data[0];

		if (atom_pos_data[1] > max_data[1])
			max_data[1] = atom_pos_data[1];

		else if (atom_pos_data[1] < min_data[1])
			min_data[1] = atom_pos_data[1];

		if (atom_pos_data[2] > max_data[2])
			max_data[2] = atom_pos_data[2];
			
		else if (atom_pos_data[2] < min_data[2])
			min_data[2] = atom_pos_data[2];
	}
} 

void ConfGen::FragmentTreeNode::copyCoordinates(const Math::Vector3DArray& src_coords, const IndexArray& atom_inds, 
												Math::Vector3DArray& tgt_coords) const
{
	const Math::Vector3DArray::StorageType& src_coords_data = src_coords.getData();
	Math::Vector3DArray::StorageType& tgt_coords_data = tgt_coords.getData();

	for (IndexArray::const_iterator it = atom_inds.begin(), end = atom_inds.end(); it != end; ++it) {
		std::size_t idx = *it;
		Math::Vector3D::ConstPointer src_atom_pos_data = src_coords_data[idx].getData();
		Math::Vector3D::Pointer tgt_atom_pos_data = tgt_coords_data[idx].getData();

		tgt_atom_pos_data[0] = src_atom_pos_data[0];
		tgt_atom_pos_data[1] = src_atom_pos_data[1];
		tgt_atom_pos_data[2] = src_atom_pos_data[2];
	}
}

void ConfGen::FragmentTreeNode::copyCoordinates(const Math::Vector3DArray& src_coords, const IndexArray& atom_inds, 
												Math::Vector3DArray& tgt_coords, std::size_t excl_atom_idx) const
{
	const Math::Vector3DArray::StorageType& src_coords_data = src_coords.getData();
	Math::Vector3DArray::StorageType& tgt_coords_data = tgt_coords.getData();

	for (IndexArray::const_iterator it = atom_inds.begin(), end = atom_inds.end(); it != end; ++it) {
		std::size_t idx = *it;

		if (idx == excl_atom_idx)
			continue;

		Math::Vector3D::ConstPointer src_atom_pos_data = src_coords_data[idx].getData();
		Math::Vector3D::Pointer tgt_atom_pos_data = tgt_coords_data[idx].getData();

		tgt_atom_pos_data[0] = src_atom_pos_data[0];
		tgt_atom_pos_data[1] = src_atom_pos_data[1];
		tgt_atom_pos_data[2] = src_atom_pos_data[2];
	}
}

void ConfGen::FragmentTreeNode::rotateCoordinates(const Math::Vector3DArray& src_coords, const IndexArray& atom_inds, 
												  Math::Vector3DArray& tgt_coords, double ang_sin, double ang_cos, 
												  std::size_t excl_atom_idx) const
{
	// rotate coordinates around x-axis...

	const Math::Vector3DArray::StorageType& src_coords_data = src_coords.getData();
	Math::Vector3DArray::StorageType& tgt_coords_data = tgt_coords.getData();

	for (IndexArray::const_iterator it = atom_inds.begin(), end = atom_inds.end(); it != end; ++it) {
		std::size_t idx = *it;

		if (idx == excl_atom_idx)
			continue;

		Math::Vector3D::ConstPointer src_atom_pos_data = src_coords_data[idx].getData();
		Math::Vector3D::Pointer tgt_atom_pos_data = tgt_coords_data[idx].getData();

		tgt_atom_pos_data[0] = src_atom_pos_data[0];
		tgt_atom_pos_data[1] = src_atom_pos_data[1] * ang_cos - src_atom_pos_data[2] * ang_sin;
		tgt_atom_pos_data[2] = src_atom_pos_data[1] * ang_sin + src_atom_pos_data[2] * ang_cos;
	}
}

void ConfGen::FragmentTreeNode::alignCoordinates(const double almnt_mtx[3][3], Math::Vector3DArray& coords, const IndexArray& atom_inds, 
												 std::size_t ctr_atom_idx, std::size_t excl_atom_idx, double x_disp) const
{
	// align split bond to x-axis 

	Math::Vector3DArray::StorageType& coords_data = coords.getData();
	Math::Vector3D::ConstPointer ctr_atom_pos_data = coords_data[ctr_atom_idx].getData();

	for (IndexArray::const_iterator it = atom_inds.begin(), end = atom_inds.end(); it != end; ++it) {
		std::size_t idx = *it;

		if (idx == excl_atom_idx)
			continue;

		Math::Vector3D::Pointer atom_pos_data = coords_data[idx].getData();

		double ctrd_x = atom_pos_data[0] - ctr_atom_pos_data[0];
		double ctrd_y = atom_pos_data[1] - ctr_atom_pos_data[1];
		double ctrd_z = atom_pos_data[2] - ctr_atom_pos_data[2];

		atom_pos_data[0] = almnt_mtx[0][0] * ctrd_x + almnt_mtx[0][1] * ctrd_y + almnt_mtx[0][2] * ctrd_z + x_disp;
		atom_pos_data[1] = almnt_mtx[1][0] * ctrd_x + almnt_mtx[1][1] * ctrd_y + almnt_mtx[1][2] * ctrd_z;
		atom_pos_data[2] = almnt_mtx[2][0] * ctrd_x + almnt_mtx[2][1] * ctrd_y + almnt_mtx[2][2] * ctrd_z;
	}
}

void ConfGen::FragmentTreeNode::calcAlignmentMatrix(const Math::Vector3D& bond_vec, const Math::Vector3D& tor_ref_vec, 
													double almnt_mtx[3][3], bool check_ref_vec_angle) const
{
	Math::Vector3D y_axis;

	if (check_ref_vec_angle && std::abs(angleCos(bond_vec, tor_ref_vec, 1.0, true)) > MAX_TORSION_REF_BOND_ANGLE_COS) { // (near) linear?
		Math::Vector3D orth_bond_vec;

		calcOrthogonalVector(bond_vec, orth_bond_vec);

		y_axis.assign(crossProd(orth_bond_vec, bond_vec));

	} else
		y_axis.assign(crossProd(tor_ref_vec, bond_vec));

	Math::Vector3D z_axis(crossProd(bond_vec, y_axis));

	Math::Vector3D::ConstPointer x_axis_data = bond_vec.getData();
	Math::Vector3D::ConstPointer y_axis_data = y_axis.getData();
	Math::Vector3D::ConstPointer z_axis_data = z_axis.getData();

	almnt_mtx[0][0] = x_axis_data[0];
	almnt_mtx[0][1] = x_axis_data[1];
	almnt_mtx[0][2] = x_axis_data[2];
	almnt_mtx[1][0] = y_axis_data[0];
	almnt_mtx[1][1] = y_axis_data[1];
	almnt_mtx[1][2] = y_axis_data[2];
	almnt_mtx[2][0] = z_axis_data[0];
	almnt_mtx[2][1] = z_axis_data[1];
	almnt_mtx[2][2] = z_axis_data[2];
}

void ConfGen::FragmentTreeNode::calcOrthogonalVector(const Math::Vector3D& vec, Math::Vector3D& ortho_vec) const
{
	Math::Vector3D::ConstPointer vec_data = vec.getData();
	Math::Vector3D::Pointer ortho_vec_data = ortho_vec.getData();
	
	if (vec_data[0] != 0.0) {
		ortho_vec_data[0] = (vec_data[1] + vec_data[2]) / vec_data[0];
		ortho_vec_data[1] = -1.0;
		ortho_vec_data[2] = -1.0;

	} else if (vec_data[1] != 0.0) {
		ortho_vec_data[0] = -1.0;
		ortho_vec_data[1] = (vec_data[0] + vec_data[2]) / vec_data[1];
		ortho_vec_data[2] = -1.0;

	} else if (vec_data[1] != 0.0) {
		ortho_vec_data[0] = -1.0;
		ortho_vec_data[1] = -1.0;
		ortho_vec_data[2] = (vec_data[0] + vec_data[1]) / vec_data[2];

	} else {
		ortho_vec_data[0] = 1.0;
		ortho_vec_data[1] = 0.0;
		ortho_vec_data[2] = 0.0;

		return;
	}

	ortho_vec /= length(ortho_vec);
}

void ConfGen::FragmentTreeNode::calcVirtualTorsionReferenceAtomVector(const Math::Vector3DArray& coords, std::size_t atom_idx, 
																	  Math::Vector3D& ref_vec) const
{
	using namespace Chem;

	const Math::Vector3DArray::StorageType& coords_data = coords.getData();
	const Atom& atom = rootMolGraph->getAtom(atom_idx);
	const Math::Vector3D& atom_pos = coords_data[atom_idx];

	Atom::ConstBondIterator b_it = atom.getBondsBegin();
	std::size_t bond_count = 0;

	ref_vec.clear();

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
		const Atom& nbr_atom = *a_it;

		if (!rootMolGraph->containsAtom(nbr_atom) || !rootMolGraph->containsBond(*b_it))
			continue;

		ref_vec.plusAssign(atom_pos - coords_data[rootMolGraph->getAtomIndex(nbr_atom)]);
		bond_count++;
	}

	double ref_vec_len = length(ref_vec);

	if (ref_vec_len > 0.0)
		ref_vec /= ref_vec_len;
}

double ConfGen::FragmentTreeNode::calcMMFF94Energy(const Math::Vector3DArray& coords) const
{
	return (ForceField::calcMMFF94VanDerWaalsEnergy<double>(mmff94Data.getVanDerWaalsInteractions().getElementsBegin(),
															mmff94Data.getVanDerWaalsInteractions().getElementsEnd(), 
															coords.getData()) +
			calcNonVdWMMFF94Energies(coords));
}

double ConfGen::FragmentTreeNode::calcMMFF94Energy(const Math::Vector3DArray& coords, bool& atom_clash) const
{
	using namespace ForceField;

	atom_clash = false;

	const Math::Vector3DArray::StorageType& coords_data = coords.getData();
	double vdw_e = 0.0;

	for (MMFF94VanDerWaalsInteractionData::ConstElementIterator it = mmff94Data.getVanDerWaalsInteractions().getElementsBegin(),
			 end = mmff94Data.getVanDerWaalsInteractions().getElementsEnd(); it != end; ++it) {

		double energy = calcMMFF94VanDerWaalsEnergy<double>(*it, coords_data);

		if (energy >= ATOM_CLASH_VDW_ENERGY_THRESHOLD) {
			atom_clash = true;
			return 0.0;
		}

		vdw_e += energy;
	}

	return (vdw_e +	calcNonVdWMMFF94Energies(coords));
}

double ConfGen::FragmentTreeNode::calcNonVdWMMFF94Energies(const Math::Vector3DArray& coords) const
{
	using namespace ForceField;

	const Math::Vector3DArray::StorageType& coords_data = coords.getData();

	return (calcMMFF94BondStretchingEnergy<double>(mmff94Data.getBondStretchingInteractions().getElementsBegin(),
												   mmff94Data.getBondStretchingInteractions().getElementsEnd(), 
												   coords_data) +
			calcMMFF94AngleBendingEnergy<double>(mmff94Data.getAngleBendingInteractions().getElementsBegin(),
												 mmff94Data.getAngleBendingInteractions().getElementsEnd(), 
												 coords_data) + 
			calcMMFF94StretchBendEnergy<double>(mmff94Data.getStretchBendInteractions().getElementsBegin(),
												mmff94Data.getStretchBendInteractions().getElementsEnd(), 
												coords_data) +
			calcMMFF94OutOfPlaneBendingEnergy<double>(mmff94Data.getOutOfPlaneBendingInteractions().getElementsBegin(),
													  mmff94Data.getOutOfPlaneBendingInteractions().getElementsEnd(), 
													  coords_data) +
			calcMMFF94TorsionEnergy<double>(mmff94Data.getTorsionInteractions().getElementsBegin(),
											mmff94Data.getTorsionInteractions().getElementsEnd(), 
											coords_data) +
			calcMMFF94ElectrostaticEnergy<double>(mmff94Data.getElectrostaticInteractions().getElementsBegin(),
												  mmff94Data.getElectrostaticInteractions().getElementsEnd(), 
												  coords_data));
}
