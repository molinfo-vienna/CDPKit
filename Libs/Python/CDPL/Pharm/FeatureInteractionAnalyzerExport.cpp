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

#include "CDPL/Pharm/FeatureInteractionAnalyzer.hpp"
#include "CDPL/Pharm/Pharmacophore.hpp"
#include "CDPL/Pharm/Feature.hpp"

#include "Base/CallableObjectAdapter.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

    void setConstraintFunction(CDPL::Pharm::FeatureInteractionAnalyzer& analyzer, unsigned int type1, unsigned int type2, 
							   const boost::python::object& callable)
    {
		analyzer.setConstraintFunction(type1, type2, CDPLPythonBase::BinaryFunctionAdapter<bool, 
									   CDPL::Pharm::Feature, CDPL::Pharm::Feature>(callable)); 
    }
}


void CDPLPythonPharm::exportFeatureInteractionAnalyzer()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Pharm::FeatureInteractionAnalyzer, boost::noncopyable>("FeatureInteractionAnalyzer", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Pharm::FeatureInteractionAnalyzer&>(
				 (python::arg("self"), python::arg("analyzer"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::FeatureInteractionAnalyzer>())	
		.def("setConstraintFunction", &setConstraintFunction, 
			 (python::arg("self"), python::arg("type1"), python::arg("type2"), python::arg("func")))
		.def("removeConstraintFunction", &Pharm::FeatureInteractionAnalyzer::removeConstraintFunction, 
			 (python::arg("self"), python::arg("type1"), python::arg("type2")))
		.def("getConstraintFunction", &Pharm::FeatureInteractionAnalyzer::getConstraintFunction, 
			 (python::arg("self"), python::arg("type1"), python::arg("type2")),
			 python::return_value_policy<python::copy_const_reference>())
		.def("assign", &Pharm::FeatureInteractionAnalyzer::operator=, 
			 (python::arg("self"), python::arg("analyzer")), python::return_self<>())
		.def("analyze", &Pharm::FeatureInteractionAnalyzer::analyze,
			 (python::arg("self"), python::arg("pharm1"), python::arg("pharm2"), python::arg("iactions")));
}
