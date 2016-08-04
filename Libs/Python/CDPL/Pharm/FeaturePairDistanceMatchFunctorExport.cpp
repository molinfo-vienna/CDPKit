/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeaturePairDistanceMatchFunctorExport.cpp 
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

#include "CDPL/Pharm/FeaturePairDistanceMatchFunctor.hpp"
#include "CDPL/Pharm/Feature.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

    bool callOperator(CDPL::Pharm::FeaturePairDistanceMatchFunctor& func, 
					  CDPL::Pharm::Feature& p1_ftr1, CDPL::Pharm::Feature& p1_ftr2,
					  CDPL::Pharm::Feature& p2_ftr1, CDPL::Pharm::Feature& p2_ftr2)
    {
		return func(p1_ftr1, p1_ftr2, p2_ftr1, p2_ftr2);
    }
}


void CDPLPythonPharm::exportFeaturePairDistanceMatchFunctor()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Pharm::FeaturePairDistanceMatchFunctor, boost::noncopyable>("FeaturePairDistanceMatchFunctor", python::no_init)
		.def(python::init<const Pharm::FeaturePairDistanceMatchFunctor&>((python::arg("self"), python::arg("func"))))
		.def(python::init<bool>((python::arg("self"), python::arg("query_mode"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::FeaturePairDistanceMatchFunctor>())
		.def("queryMode", &Pharm::FeaturePairDistanceMatchFunctor::queryMode, python::arg("self"))
		.def("assign", &Pharm::FeaturePairDistanceMatchFunctor::operator=, 
			 (python::arg("self"), python::arg("func")), python::return_self<>())
		.def("__call__", &callOperator, 
			 (python::arg("self"), python::arg("p1_ftr1"), 
			  python::arg("p1_ftr2"), python::arg("p2_ftr1"), python::arg("p2_ftr2")))
		.add_property("qryMode", &Pharm::FeaturePairDistanceMatchFunctor::queryMode);
}
