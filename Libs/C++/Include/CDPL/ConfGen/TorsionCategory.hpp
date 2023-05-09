/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TorsionCategory.hpp 
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
 * \brief Definition of the class CDPL::ConfGen::TorsionCategory.
 */

#ifndef CDPL_CONFGEN_TORSIONCATEGORY_HPP
#define CDPL_CONFGEN_TORSIONCATEGORY_HPP

#include <vector>
#include <string>
#include <cstddef>

#include "CDPL/ConfGen/APIPrefix.hpp"
#include "CDPL/ConfGen/TorsionRule.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"


namespace CDPL 
{

	namespace ConfGen 
	{

		class CDPL_CONFGEN_API TorsionCategory
		{

			typedef std::vector<TorsionCategory> CategoryList;
			typedef std::vector<TorsionRule> RuleList;

		  public:
			typedef CategoryList::iterator CategoryIterator;
			typedef CategoryList::const_iterator ConstCategoryIterator;
			typedef RuleList::iterator RuleIterator;
			typedef RuleList::const_iterator ConstRuleIterator;

			TorsionCategory();

			virtual ~TorsionCategory() {}

			const std::string& getName() const;

			void setName(const std::string& name);
	
			const std::string& getMatchPatternString() const;

			void setMatchPatternString(const std::string& ptn_str);

			const Chem::MolecularGraph::SharedPointer& getMatchPattern() const;

			void setMatchPattern(const Chem::MolecularGraph::SharedPointer& ptn);
			
			unsigned int getBondAtom1Type() const;

			void setBondAtom1Type(unsigned int type);

			unsigned int getBondAtom2Type() const;

			void setBondAtom2Type(unsigned int type);

			TorsionCategory& addCategory();

			TorsionCategory& addCategory(const TorsionCategory& cat);

			TorsionRule& addRule();

			TorsionRule& addRule(const TorsionRule& rule);

			std::size_t getNumCategories(bool recursive = false) const;

			std::size_t getNumRules(bool recursive = false) const;

			TorsionCategory& getCategory(std::size_t idx);

			const TorsionCategory& getCategory(std::size_t idx) const;

			TorsionRule& getRule(std::size_t idx);

			const TorsionRule& getRule(std::size_t idx) const;

			void removeCategory(std::size_t idx);

			void removeRule(std::size_t idx);
	
			void removeCategory(const CategoryIterator& it);

			void removeRule(const RuleIterator& it);

			CategoryIterator getCategoriesBegin();

			CategoryIterator getCategoriesEnd();

			ConstCategoryIterator getCategoriesBegin() const;

			ConstCategoryIterator getCategoriesEnd() const;

			RuleIterator getRulesBegin();

			RuleIterator getRulesEnd();

			ConstRuleIterator getRulesBegin() const;

			ConstRuleIterator getRulesEnd() const;

			void swap(TorsionCategory& cat);

			void clear();

		  private:
			void checkCategoryIndex(std::size_t idx, bool it) const;

			void checkRuleIndex(std::size_t idx, bool it) const;

			std::string                         name;      
			std::string                         matchPatternStr;
			Chem::MolecularGraph::SharedPointer matchPattern;
			unsigned int                        bondAtom1Type;
			unsigned int                        bondAtom2Type;
			RuleList                            rules;
			CategoryList                        categories;
		};
	}
}

#endif // CDPL_CONFGEN_TORSIONCATEGORY_HPP
