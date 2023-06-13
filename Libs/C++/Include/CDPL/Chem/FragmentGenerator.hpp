/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FragmentGenerator.hpp 
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
 * \brief Definition of the class CDPL::Chem::FragmentGenerator.
 */

#ifndef CDPL_CHEM_FRAGMENTGENERATOR_HPP
#define CDPL_CHEM_FRAGMENTGENERATOR_HPP

#include <cstddef>
#include <vector>
#include <memory>

#include <boost/function.hpp>

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
		 * \brief FragmentGenerator.
		 */
		class CDPL_CHEM_API FragmentGenerator 
		{

		  public:
			typedef std::shared_ptr<FragmentGenerator> SharedPointer;

			typedef boost::function1<bool, const MolecularGraph&> FragmentFilterFunction;
			
			class CDPL_CHEM_API FragmentationRule
			{

			public:
				FragmentationRule(const MolecularGraph::SharedPointer& match_ptn, unsigned int id);

				const MolecularGraph::SharedPointer& getMatchPattern() const;

				void setMatchPattern(const MolecularGraph::SharedPointer& ptn);

				unsigned int getID() const;

				void setID(unsigned int id);
				
			private:
				MolecularGraph::SharedPointer matchPtn;
				unsigned int                  id;
			};
			
			class CDPL_CHEM_API ExcludePattern
			{

			public:
				ExcludePattern(const MolecularGraph::SharedPointer& match_ptn, unsigned int rule_id);

				ExcludePattern(const MolecularGraph::SharedPointer& match_ptn);

				const MolecularGraph::SharedPointer& getMatchPattern() const;

				void setMatchPattern(const MolecularGraph::SharedPointer& ptn);

				unsigned int getRuleID() const;

				void setRuleID(unsigned int id);

				bool isGeneric() const;

				void setGeneric(bool generic);
				
			private:
				MolecularGraph::SharedPointer matchPtn;
				unsigned int                  ruleID;
				bool                          generic;
			};

			class CDPL_CHEM_API FragmentLink
			{

			public:
				FragmentLink(std::size_t frag1_idx, std::size_t frag2_idx, const Bond& bond,
							 unsigned int rule_id, unsigned int atom1_label, unsigned int atom2_label);

				std::size_t getFragment1Index() const;

				std::size_t getFragment2Index() const;

				const Bond& getBond() const;

				unsigned int getRuleID() const;

				unsigned int getAtom1Label() const;

				unsigned int getAtom2Label() const;
			
			private:
				std::size_t  frag1Idx;
				std::size_t  frag2Idx;
				const Bond*  bond;
				unsigned int ruleID;
				unsigned int atom1Label;
				unsigned int atom2Label;
			};

		  private:
			typedef std::vector<FragmentationRule> FragmentationRuleList;
			typedef std::vector<ExcludePattern> ExcludePatternList;
			typedef std::vector<FragmentLink> FragmentLinkList;

		  public:
			typedef FragmentationRuleList::const_iterator ConstFragmentationRuleIterator;
			typedef FragmentationRuleList::iterator FragmentationRuleIterator;

			typedef ExcludePatternList::const_iterator ConstExcludePatternIterator;
			typedef ExcludePatternList::iterator ExcludePatternIterator;

			typedef FragmentLinkList::const_iterator ConstFragmentLinkIterator;
						
			/**
			 * \brief Constructs the \c %FragmentGenerator instance.
			 */
			FragmentGenerator();

			FragmentGenerator(const FragmentGenerator& gen);

			virtual ~FragmentGenerator() {}

			FragmentGenerator& operator=(const FragmentGenerator& gen);

			void addFragmentationRule(const MolecularGraph::SharedPointer& match_ptn, unsigned int rule_id);

			void addFragmentationRule(const FragmentationRule& rule);

			const FragmentationRule& getFragmentationRule(std::size_t idx) const;

			FragmentationRule& getFragmentationRule(std::size_t idx);

			ConstFragmentationRuleIterator getFragmentationRulesBegin() const;

			ConstFragmentationRuleIterator getFragmentationRulesEnd() const;

			FragmentationRuleIterator getFragmentationRulesBegin();

			FragmentationRuleIterator getFragmentationRulesEnd();
			
			void removeFragmentationRule(std::size_t idx);

			std::size_t getNumFragmentationRules() const;

			void clearFragmentationRules();

			void addExcludePattern(const MolecularGraph::SharedPointer& match_ptn, unsigned int rule_id);

			void addExcludePattern(const MolecularGraph::SharedPointer& match_ptn);

			void addExcludePattern(const ExcludePattern& excl_ptn);

			const ExcludePattern& getExcludePattern(std::size_t idx) const;

			ExcludePattern& getExcludePattern(std::size_t idx);

			ConstExcludePatternIterator getExcludePatternsBegin() const;

			ConstExcludePatternIterator getExcludePatternsEnd() const;

			ExcludePatternIterator getExcludePatternsBegin();

			ExcludePatternIterator getExcludePatternsEnd();

			void removeExcludePattern(std::size_t idx);

			std::size_t getNumExcludePatterns() const;

			void clearExcludePatterns();

			bool includeSplitBonds() const;

			void includeSplitBonds(bool include);

			const FragmentFilterFunction& getFragmentFilterFunction() const;

			void setFragmentFilterFunction(const FragmentFilterFunction& func);
		
			void generate(const MolecularGraph& molgraph, FragmentList& frag_list, bool append = false);

			std::size_t getNumFragmentLinks() const;

			const FragmentLink& getFragmentLink(std::size_t idx) const;

			ConstFragmentLinkIterator getFragmentLinksBegin() const;

			ConstFragmentLinkIterator getFragmentLinksEnd() const;

		  private:
			void init(const MolecularGraph& molgraph);

			void processFragRuleMatches(const MolecularGraph& molgraph, const FragmentationRule& rule);
			void processExcludePatternMatches(const MolecularGraph& molgraph, const ExcludePattern& ptn);
			void splitIntoFragments(const MolecularGraph& molgraph, FragmentList& frag_list, bool append);
			void growFragment(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph, Chem::Fragment& frag);

			std::size_t findContainingFragment(const Chem::Atom& atom, const FragmentList& frag_list,
											   std::size_t start_idx) const;
			
			struct SplitBondData
			{

				const Bond*  bond;
				unsigned int ruleID;
				unsigned int atom1Label;
				unsigned int atom2Label;
			};
			
			typedef std::vector<SplitBondData> SplitBondDataArray;
			
			FragmentationRuleList  fragRules;
			ExcludePatternList     exclPatterns;
			FragmentLinkList       fragLinks;
			bool                   incSplitBonds;
			FragmentFilterFunction fragFilterFunc;
			SubstructureSearch     subSearch;
			Util::BitSet           splitBondMask;
			Util::BitSet           visAtomMask;
			SplitBondDataArray     splitBondData;
		};
    }
}

#endif // CDPL_CHEM_FRAGMENTGENERATOR_HPP
