/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TorsionDriverImpl.hpp 
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

/**
 * \file
 * \brief Definition of the class CDPL::ConfGen::TorsionDriverImpl.
 */

#ifndef CDPL_CONFGEN_TORSIONDRIVERIMPL_HPP
#define CDPL_CONFGEN_TORSIONDRIVERIMPL_HPP

#include <memory>

#include "CDPL/ConfGen/TorsionDriverSettings.hpp"
#include "CDPL/ConfGen/TorsionRuleMatcher.hpp"
#include "CDPL/ConfGen/ConformerDataArray.hpp"
#include "CDPL/Chem/SubstructureSearch.hpp"

#include "FragmentTree.hpp"
#include "ForceFieldInteractionMask.hpp"


namespace CDPL 
{

	namespace ForceField
	{

		class MMFF94InteractionData;
		class MMFF94InteractionParameterizer;
	}

    namespace ConfGen 
    {
	
		class TorsionDriverImpl 
		{

		public:
			typedef ConformerDataArray::const_iterator ConstConformerIterator;

			TorsionDriverImpl();

			~TorsionDriverImpl();

			TorsionDriverSettings& getSettings();

			void setup(const Chem::MolecularGraph& molgraph, const Chem::MolecularGraph& root_molgraph);
			void setup(const Chem::MolecularGraph& molgraph, const Chem::MolecularGraph& root_molgraph, 
					   const Util::BitSet& bond_mask, bool is_excl_mask);

			void setMMFF94Parameters(const ForceField::MMFF94InteractionData& ia_data);
			bool setMMFF94Parameters(const Chem::MolecularGraph& root_molgraph);

			void clearInputCoordinates();
			void clearInputCoordinates(const Util::BitSet& atom_mask);

			void addInputCoordinates(const Math::Vector3DArray& coords);
			void addInputCoordinates(const Math::Vector3DArray& coords, const Util::BitSet& atom_mask);

			void setAbortCallback(const CallbackFunction& func);

			const CallbackFunction& getAbortCallback() const;

			void setTimeoutCallback(const CallbackFunction& func);

			const CallbackFunction& getTimeoutCallback() const;

			unsigned int drive();

			std::size_t getNumConformers() const;

			ConformerData& getConformer(std::size_t idx);

			ConstConformerIterator getConformersBegin() const;
			ConstConformerIterator getConformersEnd() const;

			FragmentTree& getFragmentTree();
	
			bool initialized() const;

		private:
			TorsionDriverImpl(const TorsionDriverImpl&);

			TorsionDriverImpl& operator=(const TorsionDriverImpl&);

			void addInputCoordinates(FragmentTreeNode* node, const Math::Vector3DArray& coords);
			void addInputCoordinates(FragmentTreeNode* node, const Math::Vector3DArray& coords, 
									 const Util::BitSet& atom_mask);

			void clearInputCoordinates(FragmentTreeNode* node, const Util::BitSet& atom_mask);

			void setupTorsionAngles(FragmentTreeNode* node);

			const ConfGen::TorsionRuleMatch* getMatchingTorsionRule(const Chem::Bond& bond);

			std::size_t getRotationalSymmetry(const Chem::Bond& bond);
			std::size_t getRotationalSymmetry(const Chem::Atom& atom, const Chem::Bond& bond) const;

			const Chem::Atom* getFirstNeighborAtom(const Chem::Atom* ctr_atom, const Chem::Atom* excl_atom,
												   const FragmentTreeNode* node) const;

			typedef std::auto_ptr<ForceField::MMFF94InteractionParameterizer> MMFF94ParameterizerPtr;
			typedef std::auto_ptr<ForceField::MMFF94InteractionData> MMFF94InteractionDataPtr;

			TorsionDriverSettings     settings;
			FragmentTree              fragTree;
			TorsionRuleMatcher        torRuleMatcher;
			Chem::SubstructureSearch  subSearch;
			MMFF94ParameterizerPtr    mmff94Parameterizer;
			MMFF94InteractionDataPtr  mmff94Data;
			Util::BitSet              tmpBitSet;
			ForceFieldInteractionMask mmff94InteractionMask;
		};
    }
}

#endif // CDPL_CONFGEN_TORSIONDRIVERIMPL_HPP
