/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * PatternBasedTautomerizationRule.hpp 
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
 * \brief Definition of the class CDPL::Chem::PatternBasedTautomerizationRule.
 */

#ifndef CDPL_CHEM_PATTERNBASEDTAUTOMERIZATIONRULE_HPP
#define CDPL_CHEM_PATTERNBASEDTAUTOMERIZATIONRULE_HPP

#include <cstddef>
#include <vector>
#include <algorithm>
#include <iterator>

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include "CDPL/Chem/APIPrefix.hpp"
#include "CDPL/Chem/TautomerizationRule.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/SubstructureSearch.hpp"
#include "CDPL/Util/BitSet.hpp"
#include "CDPL/Util/ObjectStack.hpp"


namespace CDPL 
{

    namespace Chem
    {
	
		/**
		 * \brief PatternBasedTautomerizationRule.
		 */
		class CDPL_CHEM_API PatternBasedTautomerizationRule : public TautomerizationRule
		{

		  public:
			typedef boost::shared_ptr<PatternBasedTautomerizationRule> SharedPointer;

			struct BondOrderChange
			{

				std::size_t atom1ID;
				std::size_t atom2ID;
				long        orderChange;
			};

			PatternBasedTautomerizationRule(unsigned int rule_id);

			PatternBasedTautomerizationRule(const PatternBasedTautomerizationRule& rule);

			PatternBasedTautomerizationRule& operator=(const PatternBasedTautomerizationRule& rule);

			template <typename Iter>
			void addTransformationPattern(const MolecularGraph::SharedPointer& pattern, Iter bond_chgs_beg, Iter bond_chgs_end) {
				structPatterns.push_back(pattern);
				patternSubSearchList.push_back(SubstructureSearch::SharedPointer(new SubstructureSearch(*pattern)));
				patternBondChangeLists.resize(patternBondChangeLists.size() + 1);

				std::copy(bond_chgs_beg, bond_chgs_end, std::back_inserter(patternBondChangeLists.back()));
			}

			void addExcludePattern(const MolecularGraph::SharedPointer& pattern);

			void addExcludePatterns(const PatternBasedTautomerizationRule& rule);

			void clearExcludePatterns();

			bool setup(MolecularGraph& parent_molgraph);
		
			unsigned int getID() const;

			bool generate(Molecule& tautomer);

			TautomerizationRule::SharedPointer clone() const;

		  private:
			bool applyTransformation(Molecule& tautomer);

			Atom* getTautomerAtom(Molecule& tautomer, std::size_t ptn_atom_id, const AtomMapping& mapping) const;

			void freeBitSet(Util::BitSet* bset);

			void createMatchedBondMask(const BondMapping& mapping, Util::BitSet& bond_mask) const;

			typedef std::vector<BondOrderChange> BondOrderChangeList;
			typedef std::vector<BondOrderChangeList> BondOrderChangeListArray;
			typedef std::vector<MolecularGraph::SharedPointer> StructPatternList;
			typedef std::vector<SubstructureSearch::SharedPointer> SubstructureSearchList;
			typedef std::vector<Util::BitSet*> BitSetList;
			typedef Util::ObjectStack<Util::BitSet> BitSetCache;

			unsigned int                ruleID;
			StructPatternList           structPatterns;
			StructPatternList           excludePatterns;
			BondOrderChangeListArray    patternBondChangeLists;
			SubstructureSearchList      patternSubSearchList;
			SubstructureSearchList      excludeSubSearchList;
			const MolecularGraph*       parentMolGraph;
			std::size_t                 currPatternIdx;
			std::size_t                 currMappingIdx;
			Util::BitSet                bondMask;
			BitSetList                  excludeMatches;
			BitSetCache                 bitSetCache;
		};
    }
}

#endif // CDPL_CHEM_PATTERNBASEDTAUTOMERIZATIONRULE_HPP
