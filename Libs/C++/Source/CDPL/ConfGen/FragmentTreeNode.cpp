/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentTreeNode.cpp 
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

#include "CDPL/ConfGen/ReturnCode.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/ForceField/UtilityFunctions.hpp"
#include "CDPL/MolProp/AtomFunctions.hpp"

#include "FragmentTreeNode.hpp"
#include "FragmentTree.hpp"
#include "ForceFieldInteractionMask.hpp"
#include "UtilityFunctions.hpp"


using namespace CDPL;


namespace
{

	bool torsionAnglesEqual(double ang1, double ang2)
	{
		return (ConfGen::getAbsoluteAngleDistance(ang1, ang2) < 1.0);
	}

	bool compareConformerEnergy(const ConfGen::ConformerData::SharedPointer& conf_data1, 
								const ConfGen::ConformerData::SharedPointer& conf_data2)
	{
		return (conf_data1->getEnergy() < conf_data2->getEnergy());
	} 

	const double CONFORMER_LINEUP_SPACING       = 4.0;
	const double MAX_TORSION_REF_BOND_ANGLE_COS = std::cos(2.5 / 180.0 * M_PI);
	const double MAX_PLANAR_ATOM_GEOM_OOP_ANGLE = 10.0 / 180.0 * M_PI;
}


ConfGen::FragmentTreeNode::FragmentTreeNode(ConfGen::FragmentTree& owner): 
	owner(owner), parent(0), splitBond(0), changed(true)
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

const Chem::Bond* ConfGen::FragmentTreeNode::getSplitBond() const
{
	return splitBond;
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

bool ConfGen::FragmentTreeNode::containsAtom(const Chem::Atom& atom) const
{
	if (!owner.getMolecularGraph())
		return false;

	try {
		return atomMask.test(owner.getMolecularGraph()->getAtomIndex(atom));

	} catch (const Base::Exception& e) {}

	return false;
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

const ConfGen::FragmentTreeNode::DoubleArray& ConfGen::FragmentTreeNode::getTorsionAngles() const
{
	return torsionAngles;
}

void ConfGen::FragmentTreeNode::addTorsionAngle(double angle)
{
	torsionAngles.push_back(angle);
}

void ConfGen::FragmentTreeNode::removeDuplicateTorsionAngles()
{
	std::sort(torsionAngles.begin(), torsionAngles.end());
		
	torsionAngles.erase(std::unique(torsionAngles.begin(), torsionAngles.end(), &torsionAnglesEqual), torsionAngles.end());
}

std::size_t ConfGen::FragmentTreeNode::getNumTorsionAngles() const
{
	return torsionAngles.size();
}

ForceField::MMFF94InteractionData& ConfGen::FragmentTreeNode::getMMFF94Parameters()
{
	return mmff94Data;
}

const ForceField::MMFF94InteractionData& ConfGen::FragmentTreeNode::getMMFF94Parameters() const
{
	return mmff94Data;
}

void ConfGen::FragmentTreeNode::distMMFF94Parameters(const ForceField::MMFF94InteractionData& ia_data,
													 ForceFieldInteractionMask& ia_mask)
{
	if (hasChildren()) {
		leftChild->distMMFF94Parameters(ia_data, ia_mask);
		rightChild->distMMFF94Parameters(ia_data, ia_mask);
	}

	extractFragmentMMFF94InteractionParams2(ia_data.getBondStretchingInteractions(), mmff94Data.getBondStretchingInteractions(), 
											ia_mask.bondStretching, coreAtomMask);
	extractFragmentMMFF94InteractionParams2(ia_data.getElectrostaticInteractions(), mmff94Data.getElectrostaticInteractions(), 
											ia_mask.electrostatic, coreAtomMask);
	extractFragmentMMFF94InteractionParams2(ia_data.getVanDerWaalsInteractions(), mmff94Data.getVanDerWaalsInteractions(), 
											ia_mask.vanDerWaals, atomMask);
	extractFragmentMMFF94InteractionParams3(ia_data.getAngleBendingInteractions(), mmff94Data.getAngleBendingInteractions(), 
											ia_mask.angleBending, atomMask);
	extractFragmentMMFF94InteractionParams3(ia_data.getStretchBendInteractions(), mmff94Data.getStretchBendInteractions(), 
											ia_mask.stretchBend, atomMask);
	extractFragmentMMFF94InteractionParams4(ia_data.getOutOfPlaneBendingInteractions(), mmff94Data.getOutOfPlaneBendingInteractions(), 
											ia_mask.outOfPlaneBending, atomMask);
	extractFragmentMMFF94InteractionParams4(ia_data.getTorsionInteractions(), mmff94Data.getTorsionInteractions(), 
											ia_mask.torsion, atomMask);

	mmff94EnergyCalc.setup(mmff94Data);
}

const ConfGen::ConformerDataArray& ConfGen::FragmentTreeNode::getConformers() const
{
	return conformers;
}

std::size_t ConfGen::FragmentTreeNode::getNumConformers() const
{
	return conformers.size();
}

ConfGen::ConformerData& ConfGen::FragmentTreeNode::getConformer(std::size_t idx) const
{
	return *conformers[idx];
}

void ConfGen::FragmentTreeNode::orderConformersByEnergy()
{
	std::sort(conformers.begin(), conformers.end(), &compareConformerEnergy);
}

void ConfGen::FragmentTreeNode::clearConformers()
{
	conformers.clear();
	tmpConformers.clear();
	changed = true;
}

void ConfGen::FragmentTreeNode::clearConformersDownwards()
{
	conformers.clear();
	tmpConformers.clear();
	changed = true;

	if (hasChildren()) {
		leftChild->clearConformersDownwards();
		rightChild->clearConformersDownwards();
	}
}

void ConfGen::FragmentTreeNode::clearConformersUpwards()
{
	conformers.clear();
	tmpConformers.clear();
	changed = true;

	if (parent)
		parent->clearConformersUpwards();
}

void ConfGen::FragmentTreeNode::addConformer(const Math::Vector3DArray& src_coords)
{
	ConformerData::SharedPointer new_conf = owner.allocConformerData();

	copyCoordinates(src_coords, atomIndices, *new_conf);

	new_conf->setEnergy(calcMMFF94Energy(src_coords));

	conformers.push_back(new_conf);
	changed = true;
}

void ConfGen::FragmentTreeNode::addConformer(const ConformerData& conf_data)
{
	ConformerData::SharedPointer new_conf = owner.allocConformerData();

	copyCoordinates(conf_data, atomIndices, *new_conf);

	new_conf->setEnergy(conf_data.getEnergy());

	conformers.push_back(new_conf);
	changed = true;
}

void ConfGen::FragmentTreeNode::addConformer(const ConformerData::SharedPointer& conf_data)
{
	conformers.push_back(conf_data);
	changed = true;
}

unsigned int ConfGen::FragmentTreeNode::generateConformers(double e_window, std::size_t max_pool_size)
{
	if (!conformers.empty())
		return ReturnCode::SUCCESS;
 
	if (!hasChildren()) {
		if (atomIndices.empty())
			return ReturnCode::SUCCESS;

		return ReturnCode::TORSION_DRIVING_FAILED;
	}

	unsigned int ret_code = leftChild->generateConformers(e_window, max_pool_size);

	if (ret_code != ReturnCode::SUCCESS)
		return ret_code;

	ret_code = rightChild->generateConformers(e_window, max_pool_size);

	if (ret_code != ReturnCode::SUCCESS)
		return ret_code;

	tmpConformers.clear();

	if (!splitBondAtoms[0] || !splitBondAtoms[1])
		lineupChildConformers(e_window);
	else
		alignAndRotateChildConformers(e_window);

	changed = true;

	if (conformers.empty())
		return ReturnCode::TORSION_DRIVING_FAILED;

	if (max_pool_size > 0 && conformers.size() > max_pool_size) {
		orderConformersByEnergy();
		conformers.resize(max_pool_size);
	}

	return invokeCallbacks();
}

void ConfGen::FragmentTreeNode::lineupChildConformers(double e_window)
{
	std::size_t num_left_chld_confs = leftChild->conformers.size();
	std::size_t num_right_chld_confs = rightChild->conformers.size();
	std::size_t num_opt_confs = std::max(num_left_chld_confs, num_right_chld_confs);

	conformers.reserve(num_opt_confs);

	double left_bbox_min[3] = {};
	double left_bbox_max[3] = {};
	double right_bbox_min[3] = {};
	double right_bbox_max[3] = {};

	if (e_window > 0.0) {
		leftChild->orderConformersByEnergy();
		rightChild->orderConformersByEnergy();
	}

	double min_energy = 0.0;

	for (std::size_t i = 0; i < num_opt_confs; i++) {
		const ConformerData& left_conf = *leftChild->conformers[std::min(num_left_chld_confs - 1, i)];
		const ConformerData& right_conf = *rightChild->conformers[std::min(num_right_chld_confs - 1, i)];
		double energy = left_conf.getEnergy() + right_conf.getEnergy();

		if (e_window > 0.0) {
			if (conformers.empty())
				min_energy = energy;

			else if (energy > (min_energy + e_window))
				break;
		}

		calcConformerBounds(left_bbox_min, left_bbox_max, leftChild->atomIndices, left_conf);
		calcConformerBounds(right_bbox_min, right_bbox_max, rightChild->atomIndices, right_conf);

		double right_conf_trans[3] = {
		    left_bbox_max[0] + CONFORMER_LINEUP_SPACING - right_bbox_min[0],
			(left_bbox_max[1] + left_bbox_min[1]) * 0.5 - (right_bbox_max[1] + left_bbox_min[1]) * 0.5,
			(left_bbox_max[2] + left_bbox_min[2]) * 0.5 - (right_bbox_max[2] + left_bbox_min[2]) * 0.5
		};

		ConformerData::SharedPointer new_conf = owner.allocConformerData();
		Math::Vector3DArray::StorageType& new_conf_data = new_conf->getData();
		const Math::Vector3DArray::StorageType& right_conf_data = right_conf.getData();

		copyCoordinates(left_conf, leftChild->atomIndices, *new_conf);

		for (IndexArray::const_iterator it = rightChild->atomIndices.begin(), end = rightChild->atomIndices.end(); it != end; ++it) {
			std::size_t idx = *it;
			Math::Vector3D::ConstPointer atom_pos_data = right_conf_data[idx].getData();
			Math::Vector3D::Pointer new_atom_pos_data = new_conf_data[idx].getData();

			new_atom_pos_data[0] = atom_pos_data[0] + right_conf_trans[0];
			new_atom_pos_data[1] = atom_pos_data[1] + right_conf_trans[1];
			new_atom_pos_data[2] = atom_pos_data[2] + right_conf_trans[2];
		}

		new_conf->setEnergy(energy);
		conformers.push_back(new_conf);
	}
}

void ConfGen::FragmentTreeNode::alignAndRotateChildConformers(double e_window)
{
	initTorsionAngleData();

	const Chem::MolecularGraph& molgraph = *owner.getMolecularGraph();
	std::size_t left_atom_idx = molgraph.getAtomIndex(*splitBondAtoms[0]);
	std::size_t right_atom_idx = molgraph.getAtomIndex(*splitBondAtoms[1]);

	std::size_t num_left_chld_confs = leftChild->conformers.size();
	std::size_t num_right_chld_confs = rightChild->conformers.size();

	double almnt_mtx[3][3];
	Math::Vector3D bond_vec;
	Math::Vector3D tor_ref_vec;

	conformers.reserve(num_left_chld_confs * num_right_chld_confs);

	if (leftChild->changed) {
		for (std::size_t i = 0, tor_ref_atom_idx = torsionRefAtoms[0] ? molgraph.getAtomIndex(*torsionRefAtoms[0]) : 0; i < num_left_chld_confs; i++) {
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
			alignCoordinates(almnt_mtx, conf, leftChild->atomIndices, left_atom_idx, 0.0);
		}

		leftChild->changed = false;
	}

	if (rightChild->changed) {
		for (std::size_t i = 0, tor_ref_atom_idx = torsionRefAtoms[1] ? molgraph.getAtomIndex(*torsionRefAtoms[1]) : 0; i < num_right_chld_confs; i++) {
			ConformerData& conf = *rightChild->conformers[i];
			const Math::Vector3DArray::StorageType& conf_data = conf.getData();
			bool check_ref_vec_angle = true;

			bond_vec.assign(conf_data[right_atom_idx]);
			bond_vec.minusAssign(conf_data[left_atom_idx]);

			double bond_len = length(bond_vec);

			bond_vec /= bond_len;

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
			alignCoordinates(almnt_mtx, conf, rightChild->atomIndices, right_atom_idx, bond_len);
		}

		rightChild->changed = false;
	}

	ConformerData::SharedPointer new_conf;
	double min_energy = 0.0;
	std::size_t num_tor_angles = torsionAngles.size();

	for (std::size_t i = 0; i < num_left_chld_confs; i++) {
		const ConformerData& left_conf = *leftChild->conformers[i];
		double left_conf_energy = left_conf.getEnergy();

		if (num_tor_angles > 0 && new_conf) 
			copyCoordinates(left_conf, leftChild->atomIndices, *new_conf, right_atom_idx);

		for (std::size_t j = 0; j < num_right_chld_confs; j++) {
			const ConformerData& right_conf = *rightChild->conformers[j];
			double conf_energy_sum = left_conf_energy + right_conf.getEnergy();

			if (num_tor_angles == 0) {
				if (e_window > 0.0) {
					if (conformers.empty() || conf_energy_sum < min_energy) 
						min_energy = conf_energy_sum;

					else if (conf_energy_sum > (min_energy + e_window))
						continue;
				}

				ConformerData::SharedPointer new_conf = owner.allocConformerData();

				copyCoordinates(left_conf, leftChild->atomIndices, *new_conf, right_atom_idx);
				copyCoordinates(right_conf, rightChild->atomIndices, *new_conf, left_atom_idx);

				new_conf->setEnergy(conf_energy_sum);
				conformers.push_back(new_conf);

			} else {
				for (std::size_t k = 0; k < num_tor_angles; k++) {
					if (!new_conf) {
						new_conf = owner.allocConformerData();
						
						copyCoordinates(left_conf, leftChild->atomIndices, *new_conf, right_atom_idx);
					}

					rotateCoordinates(right_conf, rightChild->atomIndices, *new_conf, 
										  torsionAngleSines[k], torsionAngleCosines[k], left_atom_idx);

					double energy = conf_energy_sum + calcMMFF94Energy(*new_conf);

					if (e_window > 0.0) {
						if (conformers.empty() || energy < min_energy)
							min_energy = energy;

						else if (energy > (min_energy + e_window)) 
							continue;
					}

					new_conf->setEnergy(energy);
					conformers.push_back(new_conf);

					new_conf.reset();
				}
			}
		}
	}

	if (e_window > 0.0)
		removeOutOfWindowConformers(min_energy + e_window);
}

void ConfGen::FragmentTreeNode::initTorsionAngleData()
{
	if (!torsionAngleSines.empty())
		return;

	for (DoubleArray::const_iterator it = torsionAngles.begin(), end = torsionAngles.end(); it != end; ++it) {
		double angle = M_PI * (*it) / 180.0;

		torsionAngleSines.push_back(std::sin(angle));
		torsionAngleCosines.push_back(std::cos(angle));
	}
}

void ConfGen::FragmentTreeNode::removeOutOfWindowConformers(double max_energy)
{		
	for (ConformerDataArray::const_iterator conf_it = conformers.begin(), confs_end = conformers.end(); conf_it != confs_end; ++conf_it) {
		const ConformerData::SharedPointer& conf_data = *conf_it;

		if (conf_data->getEnergy() <= max_energy)
			tmpConformers.push_back(conf_data);
	}
				
	conformers.swap(tmpConformers);
	tmpConformers.clear();
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

void ConfGen::FragmentTreeNode::initFragmentData()
{
	atomMask = leftChild->atomMask;
	atomMask |= rightChild->atomMask;

	coreAtomMask = leftChild->coreAtomMask;
	coreAtomMask |= rightChild->coreAtomMask;

	atomIndices.clear();

	for (Util::BitSet::size_type i = atomMask.find_first(); i != Util::BitSet::npos; i = atomMask.find_next(i))
		atomIndices.push_back(i);
}

void ConfGen::FragmentTreeNode::initFragmentData(const Chem::MolecularGraph& frag, const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;

	std::size_t num_atoms = molgraph.getNumAtoms();

	atomMask.resize(num_atoms);
	atomMask.reset();

	coreAtomMask.resize(num_atoms);
	coreAtomMask.reset();

	atomIndices.clear();

	for (MolecularGraph::ConstAtomIterator it = frag.getAtomsBegin(), end = frag.getAtomsEnd(); it != end; ++it) {
		const Atom& atom = *it;
		std::size_t atom_idx = molgraph.getAtomIndex(atom);

		atomIndices.push_back(atom_idx);
		atomMask.set(atom_idx);

		if (MolProp::getExplicitBondCount(atom, frag) == 1 && MolProp::getExplicitBondCount(atom, molgraph) > 1) // is connected fragment atom?
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

void ConfGen::FragmentTreeNode::calcConformerBounds(double min[3], double max[3], const IndexArray& atom_inds, 
													const Math::Vector3DArray& coords) const
{
	const Math::Vector3DArray::StorageType& coords_data = coords.getData();

	bool init = true;

	for (IndexArray::const_iterator it = atom_inds.begin(), end = atom_inds.end(); it != end; ++it) {
		Math::Vector3D::ConstPointer atom_pos_data = coords_data[*it].getData();

		if (init) {
			min[0] = atom_pos_data[0];
			min[1] = atom_pos_data[1];
			min[2] = atom_pos_data[2];

			max[0] = atom_pos_data[0];
			max[1] = atom_pos_data[1];
			max[2] = atom_pos_data[2];
		
			init = false;
			continue;
		}

		if (atom_pos_data[0] > max[0])
			max[0] = atom_pos_data[0];

		else if (atom_pos_data[0] < min[0])
			min[0] = atom_pos_data[0];

		if (atom_pos_data[1] > max[1])
			max[1] = atom_pos_data[1];

		else if (atom_pos_data[1] < min[1])
			min[1] = atom_pos_data[1];

		if (atom_pos_data[2] > max[2])
			max[2] = atom_pos_data[2];
			
		else if (atom_pos_data[2] < min[2])
			min[2] = atom_pos_data[2];
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
												 std::size_t ctr_atom_idx, double x_disp) const
{
	// align split bond to x-axis 

	Math::Vector3DArray::StorageType& coords_data = coords.getData();
	Math::Vector3D::ConstPointer ctr_atom_pos_data = coords_data[ctr_atom_idx].getData();

	double ctr_atom_pos_x = ctr_atom_pos_data[0];
	double ctr_atom_pos_y = ctr_atom_pos_data[1];
	double ctr_atom_pos_z = ctr_atom_pos_data[2];

	for (IndexArray::const_iterator it = atom_inds.begin(), end = atom_inds.end(); it != end; ++it) {
		std::size_t idx = *it;
		Math::Vector3D::Pointer atom_pos_data = coords_data[idx].getData();

		double ctrd_x = atom_pos_data[0] - ctr_atom_pos_x;
		double ctrd_y = atom_pos_data[1] - ctr_atom_pos_y;
		double ctrd_z = atom_pos_data[2] - ctr_atom_pos_z;

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

	} else {
		y_axis.assign(crossProd(tor_ref_vec, bond_vec));
		y_axis /= length(y_axis);
	}

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
	const MolecularGraph& molgraph = *owner.getMolecularGraph();
	const Atom& atom = molgraph.getAtom(atom_idx);
	const Math::Vector3D& atom_pos = coords_data[atom_idx];

	Atom::ConstBondIterator b_it = atom.getBondsBegin();
	std::size_t bond_count = 0;
	std::size_t nbr_atom_inds[3];

	for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(), a_end = atom.getAtomsEnd(); a_it != a_end && bond_count < 3; ++a_it, ++b_it) {
		const Atom& nbr_atom = *a_it;

		if (!molgraph.containsAtom(nbr_atom) || !molgraph.containsBond(*b_it))
			continue;

		nbr_atom_inds[bond_count++] = molgraph.getAtomIndex(nbr_atom);
	}

	// check for planarity

	if (bond_count == 3 && 
		ForceField::calcOutOfPlaneAngle<double>(coords_data[nbr_atom_inds[0]], atom_pos, 
												coords_data[nbr_atom_inds[1]], coords_data[nbr_atom_inds[2]]) <= MAX_PLANAR_ATOM_GEOM_OOP_ANGLE) {

		ref_vec.assign(crossProd(coords_data[nbr_atom_inds[0]] - atom_pos, coords_data[nbr_atom_inds[1]] - atom_pos));

	} else { // non-planar case
		ref_vec.clear();

		for (std::size_t i = 0; i < bond_count; i++) {
			ref_vec.plusAssign(atom_pos);
			ref_vec.minusAssign(coords_data[nbr_atom_inds[i]]);
		}
	}

	double ref_vec_len = length(ref_vec);

	if (ref_vec_len > 0.0)
		ref_vec /= ref_vec_len;
}

double ConfGen::FragmentTreeNode::calcMMFF94Energy(const Math::Vector3DArray& coords)
{
	return mmff94EnergyCalc(coords.getData());
}

unsigned int ConfGen::FragmentTreeNode::invokeCallbacks() const
{
	if (owner.aborted())
		return ReturnCode::ABORTED;

	if (owner.timedout())
		return ReturnCode::TIMEOUT;

	return ReturnCode::SUCCESS;
}
