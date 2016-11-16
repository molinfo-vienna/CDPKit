/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * InteractionAnalyzerExport.cpp 
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

#include "CDPL/Pharm/InteractionAnalyzer.hpp"
#include "CDPL/Pharm/FeatureContainer.hpp"
#include "CDPL/Pharm/Feature.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonPharm::exportInteractionAnalyzer()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Pharm::InteractionAnalyzer, boost::noncopyable>("InteractionAnalyzer", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Pharm::InteractionAnalyzer&>(
				 (python::arg("self"), python::arg("analyzer"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::InteractionAnalyzer>())	
		.def("setConstraintFunction", &Pharm::InteractionAnalyzer::setConstraintFunction, 
			 (python::arg("self"), python::arg("type1"), python::arg("type2"), python::arg("func")))
		.def("removeConstraintFunction", &Pharm::InteractionAnalyzer::removeConstraintFunction, 
			 (python::arg("self"), python::arg("type1"), python::arg("type2")))
		.def("getConstraintFunction", &Pharm::InteractionAnalyzer::getConstraintFunction, 
			 (python::arg("self"), python::arg("type1"), python::arg("type2")),
			 python::return_value_policy<python::copy_const_reference>())
		.def("assign", &Pharm::InteractionAnalyzer::operator=, 
			 (python::arg("self"), python::arg("analyzer")), python::return_self<>())
		.def("analyze", &Pharm::InteractionAnalyzer::analyze,
			 (python::arg("self"), python::arg("cntnr1"), python::arg("cntnr2"), python::arg("iactions")));
}
