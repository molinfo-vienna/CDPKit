/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeaturePositionMatchFunctorExport.cpp 
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


#include <boost/python.hpp>

#include "CDPL/Pharm/FeaturePositionMatchFunctor.hpp"
#include "CDPL/Pharm/Feature.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

	bool callOperator1(CDPL::Pharm::FeaturePositionMatchFunctor& func, CDPL::Pharm::Feature& ftr1, CDPL::Pharm::Feature& ftr2)
    {
		return func(ftr1, ftr2);
    }
	
    bool callOperator2(CDPL::Pharm::FeaturePositionMatchFunctor& func, CDPL::Pharm::Feature& ftr1, CDPL::Pharm::Feature& ftr2,
					   const CDPL::Math::Matrix4D& xform)
    {
		return func(ftr1, ftr2, xform);
    }
}


void CDPLPythonPharm::exportFeaturePositionMatchFunctor()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Pharm::FeaturePositionMatchFunctor, boost::noncopyable>("FeaturePositionMatchFunctor", python::no_init)
		.def(python::init<const Pharm::FeaturePositionMatchFunctor&>((python::arg("self"), python::arg("func"))))
		.def(python::init<bool>((python::arg("self"), python::arg("query_mode"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::FeaturePositionMatchFunctor>())
		.def("assign", CDPLPythonBase::copyAssOp(&Pharm::FeaturePositionMatchFunctor::operator=), 
			 (python::arg("self"), python::arg("func")), python::return_self<>())
		.def("__call__", &callOperator1, (python::arg("self"), python::arg("ftr1"), python::arg("ftr2")))
		.def("__call__", &callOperator2, (python::arg("self"), python::arg("ftr1"), python::arg("ftr2"), python::arg("xform")))
		.add_property("qryMode", &Pharm::FeaturePositionMatchFunctor::queryMode);
}
