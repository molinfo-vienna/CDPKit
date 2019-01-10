/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TorsionRuleMatcherExport.cpp 
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

#include "CDPL/ConfGen/TorsionRuleMatcher.hpp"
#include "CDPL/ConfGen/TorsionRuleMapping.hpp"
#include "CDPL/Chem/Bond.hpp"

#include "Base/CopyAssOp.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{
	
	bool findMatches(CDPL::ConfGen::TorsionRuleMatcher& matcher, CDPL::Chem::Bond& bond, 
					 const CDPL::Chem::MolecularGraph& molgraph, CDPL::ConfGen::TorsionRuleMapping& rule_map, bool append)
	{
		return matcher.findMatches(bond, molgraph, rule_map, append);
	}
}


void CDPLPythonConfGen::exportTorsionRuleMatcher()
{
    using namespace boost;
    using namespace CDPL;

   	python::scope scope = python::class_<ConfGen::TorsionRuleMatcher, boost::noncopyable>("TorsionRuleMatcher", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ConfGen::TorsionLibrary::SharedPointer&>((python::arg("self"), python::arg("lib"))))
		.def("reportUniqueMappingsOnly", &ConfGen::TorsionRuleMatcher::reportUniqueMappingsOnly, 
			 (python::arg("self"), python::arg("unique")))
		.def("onlyUniqueMappingsReported", &ConfGen::TorsionRuleMatcher::onlyUniqueMappingsReported, 
			 python::arg("self"))
		.def("reportAllRuleMappings", &ConfGen::TorsionRuleMatcher::reportAllRuleMappings, 
			 (python::arg("self"), python::arg("all")))
		.def("allRuleMappingsReported", &ConfGen::TorsionRuleMatcher::allRuleMappingsReported, 
			 python::arg("self"))
		.def("stopAtFirstMatchingRule", &ConfGen::TorsionRuleMatcher::stopAtFirstMatchingRule, 
			 (python::arg("self"), python::arg("stop")))
		.def("stoppedAtFirstMatchingRule", &ConfGen::TorsionRuleMatcher::stoppedAtFirstMatchingRule, 
			 python::arg("self"))
		.def("setTorsionLibrary", &ConfGen::TorsionRuleMatcher::setTorsionLibrary, 
			 (python::arg("self"), python::arg("lib")))
		.def("getTorsionLibrary", &ConfGen::TorsionRuleMatcher::getTorsionLibrary, 
			 python::arg("self"), python::return_value_policy<python::copy_const_reference>())
		.def("findMatches", &findMatches, 
			 (python::arg("self"), python::arg("bond"), python::arg("molgraph"), 
			  python::arg("rule_map"), python::arg("append") = false))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::TorsionRuleMatcher>())
		//.def("assign", CDPLPythonBase::copyAssOp(&ConfGen::TorsionRuleMatcher::operator=), 
		//	 (python::arg("self"), python::arg("gen")), python::return_self<>())
		.add_property("uniqueMappingsOnly", &ConfGen::TorsionRuleMatcher::onlyUniqueMappingsReported,
					  &ConfGen::TorsionRuleMatcher::reportUniqueMappingsOnly)
		.add_property("allRuleMappings", &ConfGen::TorsionRuleMatcher::allRuleMappingsReported,
					  &ConfGen::TorsionRuleMatcher::reportAllRuleMappings)
		.add_property("onlyFirstMatchingRule", &ConfGen::TorsionRuleMatcher::stoppedAtFirstMatchingRule, 
					  &ConfGen::TorsionRuleMatcher::stopAtFirstMatchingRule)
		.add_property("torsionLibrary", 
					  python::make_function(&ConfGen::TorsionRuleMatcher::getTorsionLibrary,
											python::return_value_policy<python::copy_const_reference>()),
					  &ConfGen::TorsionRuleMatcher::setTorsionLibrary);
}
