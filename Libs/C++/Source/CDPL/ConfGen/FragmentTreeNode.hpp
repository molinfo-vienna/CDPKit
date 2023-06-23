/* 
 * FragmentTreeNode.hpp 
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

/**
 * \file
 * \brief Definition of the class CDPL::ConfGen::FragmentTreeNode.
 */

#ifndef CDPL_CONFGEN_FRAGMENTTREENODE_HPP
#define CDPL_CONFGEN_FRAGMENTTREENODE_HPP

#include <cstddef>
#include <vector>

#include "CDPL/ConfGen/ConformerDataArray.hpp"
#include "CDPL/ForceField/MMFF94InteractionData.hpp"
#include "CDPL/ForceField/MMFF94EnergyCalculator.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class MolecularGraph;
		class Atom;
		class Bond;
	}

    namespace ConfGen 
    {

		class FragmentTree;
		struct ForceFieldInteractionMask;

		class FragmentTreeNode
		{

			friend class FragmentTree;

		public:
			typedef std::vector<std::size_t> IndexArray;
			typedef std::vector<double> DoubleArray;	

			const FragmentTreeNode* getParent() const;
			FragmentTreeNode* getParent();

			const Chem::Bond* getSplitBond() const;
			const Chem::Atom* const* getSplitBondAtoms() const;
		
			const Chem::Atom* const* getTorsionReferenceAtoms() const;

			void setTorsionReferenceAtoms(const Chem::Atom* left, const Chem::Atom* right);

			bool hasChildren() const;

			bool containsAtom(const Chem::Atom& atom) const;

			const FragmentTreeNode* getLeftChild() const;
			const FragmentTreeNode* getRightChild() const;

			FragmentTreeNode* getLeftChild();
			FragmentTreeNode* getRightChild();
		
			const IndexArray& getAtomIndices() const;

			const Util::BitSet& getAtomMask() const;
			const Util::BitSet& getCoreAtomMask() const;

			const DoubleArray& getTorsionAngles() const;

			void addTorsionAngle(double angle);

			void removeDuplicateTorsionAngles();

			std::size_t getNumTorsionAngles() const;

			ForceField::MMFF94InteractionData& getMMFF94Parameters();

			const ForceField::MMFF94InteractionData& getMMFF94Parameters() const;

			void distMMFF94Parameters(const ForceField::MMFF94InteractionData& ia_data,
									  ForceFieldInteractionMask& ia_mask);

			const ConformerDataArray& getConformers() const;

			std::size_t getNumConformers() const;

			ConformerData& getConformer(std::size_t idx) const;
			
			void orderConformersByEnergy();

			void clearConformers();
			void clearConformersDownwards();
			void clearConformersUpwards();
			
			void addConformer(const Math::Vector3DArray& src_coords);
			void addConformer(const ConformerData& conf_data);
			void addConformer(const ConformerData::SharedPointer& conf_data);

			unsigned int generateConformers(double e_window = 0.0, std::size_t max_pool_size = 0);

			double calcMMFF94Energy(const Math::Vector3DArray& coords);
		
		private:
			FragmentTreeNode(FragmentTree& owner);
			FragmentTreeNode(const FragmentTreeNode&);

			FragmentTreeNode& operator=(const FragmentTreeNode&);

			void lineupChildConformers(double e_window);
			void alignAndRotateChildConformers(double e_window);

			void initTorsionAngleData();
			void removeOutOfWindowConformers(double max_energy);

			void setParent(FragmentTreeNode* node);
			void setChildren(FragmentTreeNode* left, FragmentTreeNode* right);

			void setSplitBond(const Chem::Bond* bond);
			void setSplitBondAtoms(const Chem::Atom* left, const Chem::Atom* right);
		
			void initFragmentData();
			void initFragmentData(const Chem::MolecularGraph& frag, const Chem::MolecularGraph& molgraph);

			void clearTorsionDrivingData();

			void calcConformerBounds(double min[3], double max[3], const IndexArray& atom_inds,
									 const Math::Vector3DArray& coords) const;

			void copyCoordinates(const Math::Vector3DArray& src_coords, const IndexArray& atom_inds, 
								 Math::Vector3DArray& tgt_coords) const;

			void copyCoordinates(const Math::Vector3DArray& src_coords, const IndexArray& atom_inds, 
								 Math::Vector3DArray& tgt_coords, std::size_t excl_atom_idx) const;

			void rotateCoordinates(const Math::Vector3DArray& src_coords, const IndexArray& atom_inds, 
								   Math::Vector3DArray& tgt_coords, double ang_sin, double ang_cos, 
								   std::size_t excl_atom_idx) const;

			void alignCoordinates(const double almnt_mtx[3][3], Math::Vector3DArray& coords, const IndexArray& atom_inds, 
								  std::size_t ctr_atom_idx, double x_disp) const;

			void calcAlignmentMatrix(const Math::Vector3D& bond_vec, const Math::Vector3D& tor_ref_vec, 
									 double almnt_mtx[3][3], bool check_ref_vec_angle) const;

			void calcOrthogonalVector(const Math::Vector3D& vec, Math::Vector3D& ortho_vec) const;

			void calcVirtualTorsionReferenceAtomVector(const Math::Vector3DArray& coords, std::size_t atom_idx, 
													   Math::Vector3D& ref_vec) const;

			unsigned int invokeCallbacks() const;

			typedef ForceField::MMFF94InteractionData MMFF94InteractionData;
			typedef ForceField::MMFF94EnergyCalculator<double> MMFF94EnergyCalculator;

			FragmentTree&           owner;
			FragmentTreeNode*       parent;
			const Chem::Bond*       splitBond;
			const Chem::Atom*       splitBondAtoms[2];
			const Chem::Atom*       torsionRefAtoms[2];
			FragmentTreeNode*       leftChild;
			FragmentTreeNode*       rightChild;
			IndexArray              atomIndices;
			Util::BitSet            atomMask;
			Util::BitSet            coreAtomMask;
			ConformerDataArray      conformers;
			ConformerDataArray      tmpConformers;
			DoubleArray             torsionAngles;
			DoubleArray             torsionAngleCosines;
			DoubleArray             torsionAngleSines;
			MMFF94InteractionData   mmff94Data;
			MMFF94EnergyCalculator  mmff94EnergyCalc;
			bool                    changed;
		};
    }
}

#endif // CDPL_CONFGEN_FRAGMENTTREENODE_HPP
