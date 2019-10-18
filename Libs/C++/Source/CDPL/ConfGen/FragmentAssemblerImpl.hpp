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

#include "CDPL/ConfGen/FragmentAssemblerSettings.hpp"
#include "CDPL/ConfGen/TorsionRuleMatcher.hpp"
#include "CDPL/ConfGen/ConformerDataArray.hpp"
#include "CDPL/ConfGen/FragmentLibraryEntry.hpp"
#include "CDPL/ConfGen/ForceFieldInteractionMask.hpp"
#include "CDPL/Util/ObjectStack.hpp"

#include "FragmentTree.hpp"
#include "FragmentConformerGeneratorImpl.hpp"
#include "TorsionDriverImpl.hpp"
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
	
		class FragmentAssemblerImpl 
		{

		public:
			typedef ConformerDataArray::const_iterator ConstStructureIterator;

			FragmentAssemblerImpl();

			~FragmentAssemblerImpl();

			FragmentAssemblerSettings& getSettings();

			void setAbortCallback(const CallbackFunction& func);

			const CallbackFunction& getAbortCallback() const;

			void setTimeoutCallback(const CallbackFunction& func);

			const CallbackFunction& getTimeoutCallback() const;

			unsigned int assemble(const Chem::MolecularGraph& molgraph);
			unsigned int assemble(const Chem::MolecularGraph& molgraph, 
								  const ForceField::MMFF94InteractionData& ia_data);

			std::size_t getNumStructures() const;

			ConformerData& getStructure(std::size_t idx);

			ConstStructureIterator getStructuresBegin() const;
			ConstStructureIterator getStructuresEnd() const;

			FragmentTree& getFragmentTree();

		private:
			FragmentAssemblerImpl(const FragmentAssemblerImpl&);

			FragmentAssemblerImpl& operator=(const FragmentAssemblerImpl&);
	
			void clear();

			void buildFragmentTree(const Chem::MolecularGraph& molgraph);
			void extractBuildFragments(FragmentTreeNode* node);
			void setBuildFragmentMMFF94Parameters(const ForceField::MMFF94InteractionData& ia_data);
			void setFragmentLinkBondLengths(FragmentTreeNode* node, 
											const ForceField::MMFF94InteractionData& ia_data);

			struct BuildFragmentData
			{

				FragmentTreeNode*  treeNode;
				ConformerDataArray conformers;
			};

			typedef std::auto_ptr<ForceField::MMFF94InteractionParameterizer> MMFF94ParameterizerPtr;
			typedef std::auto_ptr<ForceField::MMFF94InteractionData> MMFF94InteractionDataPtr;

			typedef Util::ObjectStack<ConformerData> ConformerDataCache;
			typedef Util::ObjectStack<BuildFragmentData> BuildFragmentDataCache;
			typedef std::vector<BuildFragmentData*> BuildFragmentList;

			ConformerDataCache             confDataCache;
			BuildFragmentDataCache         buildFragDataCache;
			FragmentAssemblerSettings      settings;
			CallbackFunction               abortCallback;
			CallbackFunction               timeoutCallback;
			FragmentTree                   fragTree;
			BuildFragmentList              buildFrags;
			TorsionRuleMatcher             torRuleMatcher;
			FragmentConformerGeneratorImpl fragConfGen;
			TorsionDriverImpl              torDriver;
			FragmentLibraryEntry           fragLibEntry;
			ConformerDataArray             structures;
			MMFF94ParameterizerPtr         mmff94Parameterizer;
			MMFF94InteractionDataPtr       mmff94Data;
			ForceFieldInteractionMask      mmff94InteractionMask;
			Util::BitSet                   fragLinkBondMask;
		};
    }
}

#endif // CDPL_CONFGEN_FRAGMENTASSEMBLERIMPL_HPP
