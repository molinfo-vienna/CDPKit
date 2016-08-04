/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeatureInteractionConstraintConnectorExport.cpp 
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

#include "CDPL/Pharm/FeatureInteractionConstraintConnector.hpp"
#include "CDPL/Pharm/Feature.hpp"

#include "Base/CallableObjectAdapter.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

	CDPL::Pharm::FeatureInteractionConstraintConnector*
	construct(bool and_expr, const boost::python::object& func1, const boost::python::object& func2)
    {
		return new CDPL::Pharm::FeatureInteractionConstraintConnector(
			and_expr, 
			CDPLPythonBase::BinaryFunctionAdapter<bool, CDPL::Pharm::Feature, CDPL::Pharm::Feature>(func1),
			CDPLPythonBase::BinaryFunctionAdapter<bool, CDPL::Pharm::Feature, CDPL::Pharm::Feature>(func2)); 
    }

    bool callOperator(CDPL::Pharm::FeatureInteractionConstraintConnector& con, 
					  CDPL::Pharm::Feature& ftr1, CDPL::Pharm::Feature& ftr2)
    {
		return con(ftr1, ftr2);
    }
}


void CDPLPythonPharm::exportFeatureInteractionConstraintConnector()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Pharm::FeatureInteractionConstraintConnector, 
				   boost::noncopyable>("FeatureInteractionConstraintConnector", python::no_init)
		.def(python::init<const Pharm::FeatureInteractionConstraintConnector&>(
				 (python::arg("self"), python::arg("con"))))
		.def("__init__", python::make_constructor(&construct, python::default_call_policies(),
												  (python::arg("and_expr"), python::arg("func2"), python::arg("func1"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::FeatureInteractionConstraintConnector>())
		.def("assign", &Pharm::FeatureInteractionConstraintConnector::operator=, 
			 (python::arg("self"), python::arg("con")), python::return_self<>())
		.def("__call__", &callOperator, 
			 (python::arg("self"), python::arg("ftr1"), python::arg("ftr2")));
}
