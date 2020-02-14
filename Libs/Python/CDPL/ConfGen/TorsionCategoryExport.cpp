/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TorsionCategoryExport.cpp 
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


#include <boost/python.hpp>

#include "CDPL/ConfGen/TorsionCategory.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

	class CategorySequence
	{

	public:
		CategorySequence(CDPL::ConfGen::TorsionCategory& cat): category(cat) {}

		std::size_t getNumCategories() const {
			return category.getNumCategories();
		}

		CDPL::ConfGen::TorsionCategory& getCategory(std::size_t idx) const {
			return category.getCategory(idx);
		}

		void removeCategory(std::size_t idx) const {
			return category.removeCategory(idx);
		}

	private:
		CDPL::ConfGen::TorsionCategory& category;
	};

	CategorySequence createCategorySequence(CDPL::ConfGen::TorsionCategory& cat)
	{
		return CategorySequence(cat);
	}

	class RuleSequence
	{

	public:
		RuleSequence(CDPL::ConfGen::TorsionCategory& cat): category(cat) {}

		std::size_t getNumRules() const {
			return category.getNumRules();
		}

		CDPL::ConfGen::TorsionRule& getRule(std::size_t idx) const {
			return category.getRule(idx);
		}

		void removeRule(std::size_t idx) const {
			return category.removeRule(idx);
		}

	private:
		CDPL::ConfGen::TorsionCategory& category;
	};

	RuleSequence createRuleSequence(CDPL::ConfGen::TorsionCategory& cat)
	{
		return RuleSequence(cat);
	}
}


void CDPLPythonConfGen::exportTorsionCategory()
{
    using namespace boost;
    using namespace CDPL;

	python::scope scope = python::class_<ConfGen::TorsionCategory>("TorsionCategory", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ConfGen::TorsionCategory&>((python::arg("self"), python::arg("cat"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::TorsionCategory>())	
		.def("assign", CDPLPythonBase::copyAssOp(&ConfGen::TorsionCategory::operator=), 
			 (python::arg("self"), python::arg("cat")), python::return_self<>())
		.def("getMatchPatternString", &ConfGen::TorsionCategory::getMatchPatternString, python::arg("self"), 
			 python::return_value_policy<python::copy_const_reference>())
		.def("setMatchPatternString", &ConfGen::TorsionCategory::setMatchPatternString, (python::arg("self"), python::arg("ptn_str")))
		.def("getMatchPattern", &ConfGen::TorsionCategory::getMatchPattern, python::arg("self"), 
			 python::return_value_policy<python::copy_const_reference>())
		.def("setMatchPattern", &ConfGen::TorsionCategory::setMatchPattern, (python::arg("self"), python::arg("ptn")))
		.def("getBondAtom1Type", &ConfGen::TorsionCategory::getBondAtom1Type, python::arg("self"))
		.def("setBondAtom1Type", &ConfGen::TorsionCategory::setBondAtom1Type, (python::arg("self"), python::arg("type")))
		.def("getBondAtom2Type", &ConfGen::TorsionCategory::getBondAtom2Type, python::arg("self"))
		.def("setBondAtom2Type", &ConfGen::TorsionCategory::setBondAtom2Type, (python::arg("self"), python::arg("type")))
		.def("getName", &ConfGen::TorsionCategory::getName, python::arg("self"), 
			 python::return_value_policy<python::copy_const_reference>())
		.def("setName", &ConfGen::TorsionCategory::setName, (python::arg("self"), python::arg("name")))
		.def("getNumRules", &ConfGen::TorsionCategory::getNumRules, (python::arg("self"), python::arg("recursive") = false))
		.def("getRule",static_cast<ConfGen::TorsionRule& (ConfGen::TorsionCategory::*)(std::size_t)>(
				 &ConfGen::TorsionCategory::getRule), (python::arg("self"), python::arg("idx")),
			 python::return_internal_reference<>())
		.def("removeRule", static_cast<void (ConfGen::TorsionCategory::*)(std::size_t)>(
				 &ConfGen::TorsionCategory::removeRule), (python::arg("self"), python::arg("idx")))
		.def("addRule", static_cast<ConfGen::TorsionRule& (ConfGen::TorsionCategory::*)(const ConfGen::TorsionRule&)>(
				 &ConfGen::TorsionCategory::addRule), (python::arg("self"), python::arg("rule")), 
			 python::return_internal_reference<>())
		.def("addRule", static_cast<ConfGen::TorsionRule& (ConfGen::TorsionCategory::*)()>(&ConfGen::TorsionCategory::addRule), 
			 python::arg("self"), python::return_internal_reference<>())
		.def("getRules", &createRuleSequence, python::arg("self"), python::with_custodian_and_ward_postcall<0, 1>())
		.def("getNumCategories", &ConfGen::TorsionCategory::getNumCategories, (python::arg("self"), python::arg("recursive") = false))
		.def("getCategory",static_cast<ConfGen::TorsionCategory& (ConfGen::TorsionCategory::*)(std::size_t)>(
				 &ConfGen::TorsionCategory::getCategory), (python::arg("self"), python::arg("idx")),
			 python::return_internal_reference<>())
		.def("removeCategory", static_cast<void (ConfGen::TorsionCategory::*)(std::size_t)>(
				 &ConfGen::TorsionCategory::removeCategory), (python::arg("self"), python::arg("idx")))
		.def("addCategory", static_cast<ConfGen::TorsionCategory& (ConfGen::TorsionCategory::*)(const ConfGen::TorsionCategory&)>(
				 &ConfGen::TorsionCategory::addCategory), (python::arg("self"), python::arg("cat")), 
			 python::return_internal_reference<>())
		.def("addCategory", static_cast<ConfGen::TorsionCategory& (ConfGen::TorsionCategory::*)()>(&ConfGen::TorsionCategory::addCategory), 
			 python::arg("self"), python::return_internal_reference<>())
		.def("getCategories", &createCategorySequence, python::arg("self"), python::with_custodian_and_ward_postcall<0, 1>())
		.def("clear", &ConfGen::TorsionCategory::clear, python::arg("self"))
		.def("swap", &ConfGen::TorsionCategory::swap, (python::arg("self"), python::arg("cat")))
		.add_property("rules", python::make_function(&createRuleSequence, python::with_custodian_and_ward_postcall<0, 1>()))
		.add_property("categories", python::make_function(&createCategorySequence, python::with_custodian_and_ward_postcall<0, 1>()))
		.add_property("numRules", &ConfGen::TorsionCategory::getNumRules)
		.add_property("numCategories", &ConfGen::TorsionCategory::getNumCategories)
		.add_property("bondAtom1Type", &ConfGen::TorsionCategory::getBondAtom1Type, &ConfGen::TorsionCategory::setBondAtom1Type)
		.add_property("bondAtom2Type", &ConfGen::TorsionCategory::getBondAtom2Type, &ConfGen::TorsionCategory::setBondAtom2Type)
		.add_property("matchPatternString", 
					  python::make_function(&ConfGen::TorsionCategory::getMatchPatternString, 
											python::return_value_policy<python::copy_const_reference>()),
					  &ConfGen::TorsionCategory::setMatchPatternString)
		.add_property("matchPattern", python::make_function(&ConfGen::TorsionCategory::getMatchPattern, 
															python::return_value_policy<python::copy_const_reference>()),
					  &ConfGen::TorsionCategory::setMatchPattern)
		.add_property("name", python::make_function(&ConfGen::TorsionCategory::getName, 
													python::return_value_policy<python::copy_const_reference>()),
					  &ConfGen::TorsionCategory::setName);

	python::class_<RuleSequence>("RuleSequence", python::no_init)
		.def(python::init<const RuleSequence&>((python::arg("self"), python::arg("rules"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<RuleSequence>())	
		.def("__getitem__", &RuleSequence::getRule, (python::arg("self"), python::arg("idx")),
			 python::return_internal_reference<>())
		.def("__delitem__", &RuleSequence::removeRule, (python::arg("self"), python::arg("idx")))
		.def("__len__", &RuleSequence::getNumRules, python::arg("self"));

	python::class_<CategorySequence>("CategorySequence", python::no_init)
		.def(python::init<const CategorySequence&>((python::arg("self"), python::arg("cat"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<CategorySequence>())	
		.def("__getitem__", &CategorySequence::getCategory, (python::arg("self"), python::arg("idx")),
			 python::return_internal_reference<>())
		.def("__delitem__", &CategorySequence::removeCategory, (python::arg("self"), python::arg("idx")))
		.def("__len__", &CategorySequence::getNumCategories, python::arg("self"));
}
