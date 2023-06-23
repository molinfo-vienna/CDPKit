/* 
 * TorsionRuleMatcherExport.cpp 
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


#include <boost/python.hpp>

#include "CDPL/ConfGen/TorsionRuleMatcher.hpp"
#include "CDPL/Chem/Bond.hpp"

#include "Base/CopyAssOp.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{
	
	bool findMatches(CDPL::ConfGen::TorsionRuleMatcher& matcher, CDPL::Chem::Bond& bond, 
					 const CDPL::Chem::MolecularGraph& molgraph, bool append)
	{
		return matcher.findMatches(bond, molgraph, append);
	}
}


void CDPLPythonConfGen::exportTorsionRuleMatcher()
{
    using namespace boost;
    using namespace CDPL;

	typedef void (ConfGen::TorsionRuleMatcher::*SetBoolFunc)(bool);
	typedef bool (ConfGen::TorsionRuleMatcher::*GetBoolFunc)() const;

   	python::class_<ConfGen::TorsionRuleMatcher, boost::noncopyable>("TorsionRuleMatcher", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ConfGen::TorsionLibrary::SharedPointer&>((python::arg("self"), python::arg("lib"))))
		.def("findUniqueMappingsOnly", SetBoolFunc(&ConfGen::TorsionRuleMatcher::findUniqueMappingsOnly), 
			 (python::arg("self"), python::arg("unique")))
		.def("findUniqueMappingsOnly", GetBoolFunc(&ConfGen::TorsionRuleMatcher::findUniqueMappingsOnly), 
			 python::arg("self"))
		.def("findAllRuleMappings", SetBoolFunc(&ConfGen::TorsionRuleMatcher::findAllRuleMappings), 
			 (python::arg("self"), python::arg("all")))
		.def("findAllRuleMappings", GetBoolFunc(&ConfGen::TorsionRuleMatcher::findAllRuleMappings), 
			 python::arg("self"))
		.def("stopAtFirstMatchingRule", SetBoolFunc(&ConfGen::TorsionRuleMatcher::stopAtFirstMatchingRule), 
			 (python::arg("self"), python::arg("stop")))
		.def("stopAtFirstMatchingRule", GetBoolFunc(&ConfGen::TorsionRuleMatcher::stopAtFirstMatchingRule), 
			 python::arg("self"))
		.def("setTorsionLibrary", &ConfGen::TorsionRuleMatcher::setTorsionLibrary, 
			 (python::arg("self"), python::arg("lib")))
		.def("getTorsionLibrary", &ConfGen::TorsionRuleMatcher::getTorsionLibrary, 
			 python::arg("self"), python::return_value_policy<python::copy_const_reference>())
		.def("getNumMatches", &ConfGen::TorsionRuleMatcher::getNumMatches, python::arg("self"))
		.def("getMatch", &ConfGen::TorsionRuleMatcher::getMatch, (python::arg("self"), python::arg("idx")),
			 python::return_internal_reference<1>())
		.def("findMatches", &findMatches, 
			 (python::arg("self"), python::arg("bond"), python::arg("molgraph"), python::arg("append") = false))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::TorsionRuleMatcher>())
		//.def("assign", CDPLPythonBase::copyAssOp(&ConfGen::TorsionRuleMatcher::operator=), 
		//	 (python::arg("self"), python::arg("gen")), python::return_self<>())
		.def("__getitem__", &ConfGen::TorsionRuleMatcher::getMatch, (python::arg("self"), python::arg("idx")), 
			 python::return_internal_reference<1>())
		.def("__len__", &ConfGen::TorsionRuleMatcher::getNumMatches, python::arg("self"))
		.add_property("numMatches", &ConfGen::TorsionRuleMatcher::getNumMatches)
		.add_property("uniqueMappingsOnly", GetBoolFunc(&ConfGen::TorsionRuleMatcher::findUniqueMappingsOnly),
					  SetBoolFunc(&ConfGen::TorsionRuleMatcher::findUniqueMappingsOnly))
		.add_property("allRuleMappings", GetBoolFunc(&ConfGen::TorsionRuleMatcher::findAllRuleMappings),
					  SetBoolFunc(&ConfGen::TorsionRuleMatcher::findAllRuleMappings))
		.add_property("onlyFirstMatchingRule", GetBoolFunc(&ConfGen::TorsionRuleMatcher::stopAtFirstMatchingRule), 
					  SetBoolFunc(&ConfGen::TorsionRuleMatcher::stopAtFirstMatchingRule))
		.add_property("torsionLibrary", 
					  python::make_function(&ConfGen::TorsionRuleMatcher::getTorsionLibrary,
											python::return_value_policy<python::copy_const_reference>()),
					  &ConfGen::TorsionRuleMatcher::setTorsionLibrary);
}
