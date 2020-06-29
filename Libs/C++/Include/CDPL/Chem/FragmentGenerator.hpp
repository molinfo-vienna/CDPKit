/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentGenerator.hpp 
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

/**
 * \file
 * \brief Definition of the class CDPL::Chem::FragmentGenerator.
 */

#ifndef CDPL_CHEM_FRAGMENTGENERATOR_HPP
#define CDPL_CHEM_FRAGMENTGENERATOR_HPP

#include <cstddef>
#include <vector>
#include <utility>

#include <boost/shared_ptr.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/FragmentList.hpp"
#include "CDPL/Chem/SubstructureSearch.hpp"
#include "CDPL/Util/BitSet.hpp"


namespace CDPL 
{

    namespace Chem
    {

		/**
		 * \addtogroup CDPL_CHEM_FRAGMENT_GENERATION
		 * @{
		 */

		/**
		 * \brief FragmentGenerator.
		 */
		class CDPL_CHEM_API FragmentGenerator 
		{

		  public:
			typedef boost::shared_ptr<FragmentGenerator> SharedPointer;

			class FragmentationRule
			{

			public:
				FragmentationRule(const MolecularGraph::SharedPointer& match_ptn, unsigned int id, unsigned int atom1_type, unsigned int atom2_type);

				const MolecularGraph::SharedPointer& getMatchPattern() const;

				void setMatchPattern(const MolecularGraph::SharedPointer& ptn);

				unsigned int getID() const;

				void setID(unsigned int id);

				unsigned int getAtom1Type() const;

				void setAtom1Type(unsigned int atom1_type);

				unsigned int getAtom2Type() const;

				void setAtom2Type(unsigned int atom2_type);
				
			private:
				MolecularGraph::SharedPointer matchPtn;
				unsigned int                  id;
				unsigned int                  atom1Type;
				unsigned int                  atom2Type;
			};
			
			class ExcludePattern
			{

			public:
				ExcludePattern(const MolecularGraph::SharedPointer& match_ptn, unsigned int rule_id);

				ExcludePattern(const MolecularGraph::SharedPointer& match_ptn);

				const MolecularGraph::SharedPointer& getMatchPattern() const;

				void setMatchPattern(const MolecularGraph::SharedPointer& ptn);

				unsigned int getRuleID() const;

				void setRuleID( unsigned int rule_id);

				bool isGeneric() const;

				void setGeneric(bool gen);
				
			private:
				MolecularGraph::SharedPointer matchPtn;
				unsigned int                  ruleID;
				bool                          generic;
			};

			class FragmentLink
			{

			public:
				FragmentLink(std::size_t frag1_idx, std::size_t frag2_idx, const Bond& bond,
							 unsigned int rule_id, unsigned int atom1_type, unsigned int atom2_type);

				std::size_t getFragment1Index() const;

				void setFragment1Index(std::size_t frag1_idx);

				std::size_t getFragment2Index() const;

				void setFragment2Index(std::size_t frag2_idx);
				
				const Bond& getBond() const;

				void setBond(const Bond& bond);
				
				unsigned int getRuleID() const;

				void setRuleID( unsigned int rule_id);

				unsigned int getAtom1Type() const;

				void setAtom1Type(unsigned int atom1_type);

				unsigned int getAtom2Type() const;

				void setAtom2Type(unsigned int atom2_type);
				
			private:
				std::size_t  frag1Idx;
				std::size_t  frag2Idx;
				const Bond*  bond;
				unsigned int ruleID;
				unsigned int atom1Type;
				unsigned int atom2Type;
			};

			/**
			 * \brief Constructs the \c %FragmentGenerator instance.
			 */
			FragmentGenerator();

			FragmentGenerator(const FragmentGenerator& gen);

			virtual ~FragmentGenerator() {}

			FragmentGenerator& operator=(const FragmentGenerator& gen);

			void addFragmentationRule(const MolecularGraph::SharedPointer& match_ptn, unsigned int rule_id,
									  unsigned int atom1_type, unsigned int atom2_type);

			void addFragmentationRule(const FragmentationRule& rule);

			const FragmentationRule& getFragmentationRule(std::size_t idx) const;

			FragmentationRule& getFragmentationRule(std::size_t idx);

			void removeFragmentationRule(std::size_t idx);

			std::size_t getNumFragmentationRules() const;

			void clearFragmentationRules();

			void addExcludePattern(const MolecularGraph::SharedPointer& match_ptn, unsigned int rule_id);

			void addExcludePattern(const MolecularGraph::SharedPointer& match_ptn);

			void addExcludePattern(const ExcludePattern& excl_ptn);

			const ExcludePattern& getExcludePattern(std::size_t idx) const;

			ExcludePattern& getExcludePattern(std::size_t idx);

			void removeExcludePattern(std::size_t idx);

			std::size_t getNumExcludePatterns() const;

			void clearExcludePatterns();

			bool includeSplitBonds() const;

			void includeSplitBonds(bool include);

			bool generateFragmentLinkInfo() const;

			void generateFragmentLinkInfo(bool generate);
				
			void generate(const MolecularGraph& molgraph, FragmentList& frags, bool append = false);

			std::size_t getNumFragmentLinks() const;

			const FragmentLink& getFragmentLink(std::size_t idx) const;
			
		  private:
			typedef std::pair<const Atom*, const Atom*> AtomPair;
			
			void init(const MolecularGraph& molgraph);

			void processFragRuleMatches(const MolecularGraph& molgraph, const FragmentationRule& rule);
			void processExcludePattern(const MolecularGraph& molgraph, const ExcludePattern& ptn);
			void splitIntoFragments(const MolecularGraph& molgraph, FragmentList& frags);

			AtomPair getMarkedAtoms(const MolecularGraph& ptn) const;

			struct SplitBondData
			{

				const Bond*  bond;
				unsigned int ruleID;
				unsigned int atom1Type;
				unsigned int atom2Type;
			};
			
			typedef std::vector<FragmentationRule> FragmentationRuleList;
			typedef std::vector<ExcludePattern> ExcludePatternList;
			typedef std::vector<FragmentLink> FragmentLinkList;
			typedef std::vector<SplitBondData> SplitBondDataArray;
			
			FragmentationRuleList fragRules;
			ExcludePatternList    exclPatterns;
			SubstructureSearch    subSearch;
			bool                  incSplitBonds;
			bool                  genFragLinkInfo;
			Util::BitSet          splitBondMask;
			SplitBondDataArray    splitBondData;
			FragmentLinkList      fragLinks;
		};

		/**
		 * @}
		 */
    }
}

#endif // CDPL_CHEM_FRAGMENTGENERATOR_HPP
