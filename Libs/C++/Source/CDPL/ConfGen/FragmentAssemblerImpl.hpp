/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentAssemblerImpl.hpp 
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
 * \brief Definition of the class CDPL::ConfGen::FragmentAssemblerImpl.
 */

#ifndef CDPL_CONFGEN_FRAGMENTASSEMBLERIMPL_HPP
#define CDPL_CONFGEN_FRAGMENTASSEMBLERIMPL_HPP

#include <memory>
#include <utility>

#include "CDPL/ConfGen/FragmentAssemblerSettings.hpp"
#include "CDPL/ConfGen/TorsionRuleMatcher.hpp"
#include "CDPL/ConfGen/FragmentLibraryEntry.hpp"
#include "CDPL/ConfGen/ConformerDataArray.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Chem/SmallestSetOfSmallestRings.hpp"
#include "CDPL/Util/ObjectStack.hpp"

#include "FragmentTree.hpp"
#include "FragmentConformerGeneratorImpl.hpp"


namespace CDPL 
{

	namespace Chem
	{

		class SmallestSetOfSmallestRings;
	}

	namespace ForceField
	{

		class MMFF94InteractionData;
		class MMFF94InteractionParameterizer;
	}

    namespace ConfGen 
    {
	
		class FragmentAssemblerImpl 
		{

			typedef ForceField::MMFF94InteractionData MMFF94InteractionData;

		public:
			typedef ConformerDataArray::const_iterator ConstConformerIterator;

			FragmentAssemblerImpl();

			~FragmentAssemblerImpl();

			FragmentAssemblerSettings& getSettings();

			void setAbortCallback(const CallbackFunction& func);

			const CallbackFunction& getAbortCallback() const;

			void setTimeoutCallback(const CallbackFunction& func);

			const CallbackFunction& getTimeoutCallback() const;

			unsigned int assemble(const Chem::MolecularGraph& molgraph, const Chem::MolecularGraph& parent_molgraph, 
								  const MMFF94InteractionData& ia_data);

			unsigned int assemble(const Chem::MolecularGraph& molgraph);
	
			std::size_t getNumConformers() const;

			ConformerData& getConformer(std::size_t idx);

			ConstConformerIterator getConformersBegin() const;
			ConstConformerIterator getConformersEnd() const;

			bool initialized();

		private:
			FragmentAssemblerImpl(const FragmentAssemblerImpl&);

			FragmentAssemblerImpl& operator=(const FragmentAssemblerImpl&);
	
			void init();

			unsigned int doAssemble(const Chem::MolecularGraph& molgraph);

			void buildFragmentTree(const Chem::MolecularGraph& molgraph);

			unsigned int setupFragmentConformers();

			bool transferInputCoordinates(const Chem::Fragment& frag, FragmentTreeNode* node);
			bool fetchConformersFromFragmentLibrary(unsigned int frag_type, FragmentTreeNode* node);
			unsigned int generateFragmentConformers(unsigned int frag_type, FragmentTreeNode* node);

			void fixBondLengths(const Chem::Fragment& frag, FragmentTreeNode* node);

			void buildFragmentLibraryEntryAtomIndexMap(const Chem::Fragment& frag, const FragmentTreeNode* frag_node);

			void assignLinkBondTorsions(FragmentTreeNode* node);

			const MMFF94InteractionData* getMMFF94Parameters();

			double getMMFF94BondLength(std::size_t atom1_idx, std::size_t atom2_idx);

			ConformerData::SharedPointer allocConformerData();

			typedef Util::ObjectStack<ConformerData> ConformerDataCache;
			typedef std::auto_ptr<ForceField::MMFF94InteractionParameterizer> MMFF94ParameterizerPtr;
			typedef std::auto_ptr<MMFF94InteractionData> MMFF94InteractionDataPtr;
			typedef std::vector<const Chem::Bond*> BondList;
			typedef std::pair<std::size_t, std::size_t> IndexPair;
			typedef std::vector<IndexPair> IndexPairList;
			typedef Chem::SmallestSetOfSmallestRings::SharedPointer SmallestSetOfSmallestRingsPtr;

			ConformerDataCache             confDataCache;
			FragmentAssemblerSettings      settings;
			CallbackFunction               abortCallback;
			CallbackFunction               timeoutCallback;
			const Chem::MolecularGraph*    parentMolGraph; 
			BondList                       fragLinkBonds;
			Chem::FragmentList             fragments;
			FragmentTree                   fragTree;
			TorsionRuleMatcher             torRuleMatcher;
			MMFF94ParameterizerPtr         mmff94Parameterizer;
			MMFF94InteractionDataPtr       mmff94Data;
			const MMFF94InteractionData*   usedMMFF94Data;
			FragmentConformerGeneratorImpl fragConfGen;
			FragmentLibraryEntry           fragLibEntry;
			Util::BitSet                   fragLinkBondMask;
			IndexPairList                  fragLibEntryAtomIdxMap;
			SmallestSetOfSmallestRingsPtr  fragSSSR;	
		};
    }
}

#endif // CDPL_CONFGEN_FRAGMENTASSEMBLERIMPL_HPP
