/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TorsionCategory.cpp 
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

#include <algorithm>

#include "CDPL/ConfGen/TorsionCategory.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Base/Exceptions.hpp"


using namespace CDPL;


ConfGen::TorsionCategory::TorsionCategory():
	bondAtom1Type(Chem::AtomType::UNKNOWN), bondAtom2Type(Chem::AtomType::UNKNOWN)
{}

const std::string& ConfGen::TorsionCategory::getName() const
{
	return name;
}

void ConfGen::TorsionCategory::setName(const std::string& name)
{
	this->name = name;
}

const std::string& ConfGen::TorsionCategory::getMatchPatternString() const
{
	return matchPatternStr;
}

void ConfGen::TorsionCategory::setMatchPatternString(const std::string& ptn_str)
{
	matchPatternStr = ptn_str;
}

const Chem::MolecularGraph::SharedPointer& ConfGen::TorsionCategory::getMatchPattern() const
{
	return matchPattern;
}

void ConfGen::TorsionCategory::setMatchPattern(const Chem::MolecularGraph::SharedPointer& ptn)
{
	matchPattern = ptn;
}
			
unsigned int ConfGen::TorsionCategory::getBondAtom1Type() const
{
	return bondAtom1Type;
}

void ConfGen::TorsionCategory::setBondAtom1Type(unsigned int type)
{
	bondAtom1Type = type;
}

unsigned int ConfGen::TorsionCategory::getBondAtom2Type() const
{
	return bondAtom2Type;
}

void ConfGen::TorsionCategory::setBondAtom2Type(unsigned int type)
{
	bondAtom2Type = type;
}

ConfGen::TorsionCategory& ConfGen::TorsionCategory::addCategory()
{
	categories.push_back(TorsionCategory());

	return categories.back();
}

ConfGen::TorsionCategory& ConfGen::TorsionCategory::addCategory(const TorsionCategory& cat)
{
	categories.push_back(cat);

	return categories.back();
}

ConfGen::TorsionRule& ConfGen::TorsionCategory::addRule()
{
	rules.push_back(TorsionRule());

	return rules.back();
}

ConfGen::TorsionRule& ConfGen::TorsionCategory::addRule(const TorsionRule& rule)
{
	rules.push_back(rule);

	return rules.back();
}

std::size_t ConfGen::TorsionCategory::getNumCategories(bool recursive) const
{
	if (!recursive)
		return categories.size();

	std::size_t num_cats = categories.size();

	for (ConstCategoryIterator it = categories.begin(), end = categories.end(); it != end; ++it)
		num_cats += it->getNumCategories(true);

	return num_cats;
}

std::size_t ConfGen::TorsionCategory::getNumRules(bool recursive) const
{
	if (!recursive)
		return rules.size();

	std::size_t num_rules = rules.size();

	for (ConstCategoryIterator it = categories.begin(), end = categories.end(); it != end; ++it)
		num_rules += it->getNumRules(true);

	return num_rules;
}

ConfGen::TorsionCategory& ConfGen::TorsionCategory::getCategory(std::size_t idx)
{
	checkCategoryIndex(idx, false);

	return categories[idx];
}

const ConfGen::TorsionCategory& ConfGen::TorsionCategory::getCategory(std::size_t idx) const
{
	checkCategoryIndex(idx, false);

	return categories[idx];
}

ConfGen::TorsionRule& ConfGen::TorsionCategory::getRule(std::size_t idx)
{
	checkRuleIndex(idx, false);

	return rules[idx];
}

const ConfGen::TorsionRule& ConfGen::TorsionCategory::getRule(std::size_t idx) const
{
	checkRuleIndex(idx, false);

	return rules[idx];
}

void ConfGen::TorsionCategory::removeCategory(std::size_t idx)
{
	checkCategoryIndex(idx, false);

	categories.erase(categories.begin() + idx);
}

void ConfGen::TorsionCategory::removeRule(std::size_t idx)
{
	checkRuleIndex(idx, false);

	rules.erase(rules.begin() + idx);
}
	
void ConfGen::TorsionCategory::removeCategory(const CategoryIterator& it)
{
	checkCategoryIndex(it - categories.begin(), true);

	categories.erase(it);
}

void ConfGen::TorsionCategory::removeRule(const RuleIterator& it)
{
	checkRuleIndex(it - rules.begin(), true);

	rules.erase(it);
}

ConfGen::TorsionCategory::CategoryIterator ConfGen::TorsionCategory::getCategoriesBegin()
{
	return categories.begin();
}

ConfGen::TorsionCategory::CategoryIterator ConfGen::TorsionCategory::getCategoriesEnd()
{
	return categories.end();
}

ConfGen::TorsionCategory::ConstCategoryIterator ConfGen::TorsionCategory::getCategoriesBegin() const
{
	return categories.begin();
}

ConfGen::TorsionCategory::ConstCategoryIterator ConfGen::TorsionCategory::getCategoriesEnd() const
{
	return categories.end();
}

ConfGen::TorsionCategory::RuleIterator ConfGen::TorsionCategory::getRulesBegin()
{
	return rules.begin();
}

ConfGen::TorsionCategory::RuleIterator ConfGen::TorsionCategory::getRulesEnd()
{
	return rules.end();
}

ConfGen::TorsionCategory::ConstRuleIterator ConfGen::TorsionCategory::getRulesBegin() const
{
	return rules.begin();
}

ConfGen::TorsionCategory::ConstRuleIterator ConfGen::TorsionCategory::getRulesEnd() const
{
	return rules.end();
}

void ConfGen::TorsionCategory::swap(TorsionCategory& cat)
{
	std::swap(bondAtom1Type, cat.bondAtom1Type);
	std::swap(bondAtom2Type, cat.bondAtom2Type);
	
	matchPattern.swap(cat.matchPattern);
	name.swap(cat.name);
	categories.swap(cat.categories);
	rules.swap(cat.rules);
}

void ConfGen::TorsionCategory::clear()
{
	name.clear();
	rules.clear();
	categories.clear();
	matchPattern.reset();

	bondAtom1Type = Chem::AtomType::UNKNOWN;
	bondAtom2Type = Chem::AtomType::UNKNOWN;
}

void ConfGen::TorsionCategory::checkCategoryIndex(std::size_t idx, bool it) const
{
	if (idx >= categories.size())
		throw Base::IndexError(it ? "TorsionCategory: category iterator out of bounds" : 
							   "TorsionCategory: category index out of bounds");
}

void ConfGen::TorsionCategory::checkRuleIndex(std::size_t idx, bool it) const
{
	if (idx >= rules.size())
		throw Base::IndexError(it ? "TorsionCategory: rule iterator out of bounds" : 
							   "TorsionCategory: rule index out of bounds");
}
