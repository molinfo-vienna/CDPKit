/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeatureInteractionAnalyzerExport.cpp 
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

#include "CDPL/Chem/FeatureInteractionAnalyzer.hpp"
#include "CDPL/Chem/Pharmacophore.hpp"
#include "CDPL/Chem/Feature.hpp"

#include "Base/CallableObjectAdapter.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

    void setConstraintFunction(CDPL::Chem::FeatureInteractionAnalyzer& analyzer, unsigned int type1, unsigned int type2, 
			       const boost::python::object& callable)
    {
	analyzer.setConstraintFunction(type1, type2, CDPLPythonBase::BinaryFunctionAdapter<bool, 
				       CDPL::Chem::Feature, CDPL::Chem::Feature>(callable)); 
    }

    bool constrFuncCall(CDPL::Chem::FeatureInteractionAnalyzer::ConstraintFunction& func, 
			CDPL::Chem::Feature& ftr1, CDPL::Chem::Feature& ftr2)
    {
	return func(ftr1, ftr2);
    }

    void constrFuncNonZero(CDPL::Chem::FeatureInteractionAnalyzer::ConstraintFunction& func)
    {
	!func.empty();
    }
}


void CDPLPythonChem::exportFeatureInteractionAnalyzer()
{
    using namespace boost;
    using namespace CDPL;

    python::scope scope = python::class_<Chem::FeatureInteractionAnalyzer, boost::noncopyable>("FeatureInteractionAnalyzer", python::no_init)
	.def(python::init<>(python::arg("self")))
	.def(python::init<const Chem::FeatureInteractionAnalyzer&>(
		 (python::arg("self"), python::arg("analyzer"))))
	.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::FeatureInteractionAnalyzer>())	
	.def("setConstraintFunction", &setConstraintFunction, 
	     (python::arg("self"), python::arg("type1"), python::arg("type2"), python::arg("func")))
	.def("removeConstraintFunction", &Chem::FeatureInteractionAnalyzer::removeConstraintFunction, 
	     (python::arg("self"), python::arg("type1"), python::arg("type2")))
	.def("getConstraintFunction", &Chem::FeatureInteractionAnalyzer::getConstraintFunction, 
	     (python::arg("self"), python::arg("type1"), python::arg("type2")),
	     python::return_value_policy<python::copy_const_reference>())
	.def("assign", &Chem::FeatureInteractionAnalyzer::operator=, 
	     (python::arg("self"), python::arg("analyzer")), python::return_self<>())
	.def("analyze", &Chem::FeatureInteractionAnalyzer::analyze,
	     (python::arg("self"), python::arg("pharm1"), python::arg("pharm2"), python::arg("interactions")));

    python::class_<Chem::FeatureInteractionAnalyzer::ConstraintFunction>("ConstraintFunction", python::no_init)
	.def("__call__", &constrFuncCall, 
	     (python::arg("self"), python::arg("ftr1"), python::arg("ftr2")))
	.def("__nonzero__", &constrFuncNonZero, python::arg("self"));
}
