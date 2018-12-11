/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * TorsionRuleExport.cpp 
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

#include "CDPL/ConfGen/TorsionRule.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonConfGen::exportTorsionRule()
{
    using namespace boost;
    using namespace CDPL;

    python::scope scope = python::class_<ConfGen::TorsionRule>("TorsionRule", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const ConfGen::TorsionRule&>((python::arg("self"), python::arg("rule"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::TorsionRule>())	
		.def("assign", CDPLPythonBase::copyAssOp(&ConfGen::TorsionRule::operator=), 
			 (python::arg("self"), python::arg("rule")), python::return_self<>())
		.def("getMatchPattern", &ConfGen::TorsionRule::getMatchPattern, python::arg("self"), 
			 python::return_value_policy<python::copy_const_reference>())
		.def("setMatchPattern", &ConfGen::TorsionRule::setMatchPattern, (python::arg("self"), python::arg("ptn")))
		.def("getNumAngles", &ConfGen::TorsionRule::getNumAngles, python::arg("self"))
		.def("__len__", &ConfGen::TorsionRule::getNumAngles, python::arg("self"))
		.def("getAngle", &ConfGen::TorsionRule::getAngle, (python::arg("self"), python::arg("idx")),
			 python::return_internal_reference<>())
		.def("__getitem__", &ConfGen::TorsionRule::getAngle, (python::arg("self"), python::arg("idx")),
			 python::return_internal_reference<>())
		.def("removeAngle", static_cast<void (ConfGen::TorsionRule::*)(std::size_t)>(&ConfGen::TorsionRule::removeAngle), 
			 (python::arg("self"), python::arg("idx")))
		.def("__delitem__", static_cast<void (ConfGen::TorsionRule::*)(std::size_t)>(&ConfGen::TorsionRule::removeAngle), 
			 (python::arg("self"), python::arg("idx")))
		.def("addAngle", static_cast<void (ConfGen::TorsionRule::*)(const ConfGen::TorsionRule::AngleEntry&)>(&ConfGen::TorsionRule::addAngle), 
			 (python::arg("self"), python::arg("ang_entry")))
		.def("__iadd__", static_cast<void (ConfGen::TorsionRule::*)(const ConfGen::TorsionRule::AngleEntry&)>(&ConfGen::TorsionRule::addAngle), 
			 (python::arg("self"), python::arg("ang_entry")))
		.def("addAngle", static_cast<void (ConfGen::TorsionRule::*)(double, double, double, double)>(&ConfGen::TorsionRule::addAngle), 
			 (python::arg("self"), python::arg("ang"), python::arg("tol1"), python::arg("tol2"), python::arg("score")))
		.def("clear", &ConfGen::TorsionRule::clear, python::arg("self"))
		.def("swap", &ConfGen::TorsionRule::swap, (python::arg("self"), python::arg("rule")))
		.add_property("numAngles", &ConfGen::TorsionRule::getNumAngles)
		.add_property("matchPattern", 
					  python::make_function(&ConfGen::TorsionRule::getMatchPattern, 
											python::return_value_policy<python::copy_const_reference>()),
					  &ConfGen::TorsionRule::setMatchPattern);

	python::class_<ConfGen::TorsionRule::AngleEntry>("AngleEntry", python::no_init)
		.def(python::init<double, double, double, double>(
				 (python::arg("self"), python::arg("ang"), python::arg("tol1"), python::arg("tol2"), python::arg("score"))))
		.def(python::init<const ConfGen::TorsionRule::AngleEntry&>((python::arg("self"), python::arg("entry"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<ConfGen::TorsionRule::AngleEntry>())	
		.def("assign", CDPLPythonBase::copyAssOp(&ConfGen::TorsionRule::AngleEntry::operator=), 
			 (python::arg("self"), python::arg("entry")), python::return_self<>())
		.def("getAngle", &ConfGen::TorsionRule::AngleEntry::getAngle, python::arg("self"))
		.def("getScore", &ConfGen::TorsionRule::AngleEntry::getScore, python::arg("self"))
		.def("getTolerance1", &ConfGen::TorsionRule::AngleEntry::getTolerance1, python::arg("self"))
		.def("getTolerance2", &ConfGen::TorsionRule::AngleEntry::getTolerance2, python::arg("self"))
		.add_property("angle", &ConfGen::TorsionRule::AngleEntry::getAngle)
		.add_property("score", &ConfGen::TorsionRule::AngleEntry::getScore)
		.add_property("tolerance1", &ConfGen::TorsionRule::AngleEntry::getTolerance1)
		.add_property("tolerance2", &ConfGen::TorsionRule::AngleEntry::getTolerance2);
}
