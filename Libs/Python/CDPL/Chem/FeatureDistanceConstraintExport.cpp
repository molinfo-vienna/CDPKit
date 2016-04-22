/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeatureDistanceConstraintExport.cpp 
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

#include "CDPL/Chem/FeatureDistanceConstraint.hpp"
#include "CDPL/Chem/Feature.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

    bool callOperator(CDPL::Chem::FeatureDistanceConstraint& constr, 
					  CDPL::Chem::Feature& ftr1, CDPL::Chem::Feature& ftr2)
    {
		return constr(ftr1, ftr2);
    }
}


void CDPLPythonChem::exportFeatureDistanceConstraint()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Chem::FeatureDistanceConstraint, boost::noncopyable>("FeatureDistanceConstraint", python::no_init)
		.def(python::init<const Chem::FeatureDistanceConstraint&>((python::arg("self"), python::arg("constr"))))
		.def(python::init<double, double>((python::arg("self"), python::arg("min_dist"), python::arg("max_dist"))))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::FeatureDistanceConstraint>())
		.def("getMinDistance", &Chem::FeatureDistanceConstraint::getMinDistance, python::arg("self"))
		.def("getMaxDistance", &Chem::FeatureDistanceConstraint::getMaxDistance, python::arg("self"))
		.def("assign", &Chem::FeatureDistanceConstraint::operator=, 
			 (python::arg("self"), python::arg("con")), python::return_self<>())
		.def("__call__", &callOperator, (python::arg("self"), python::arg("ftr1"), python::arg("ftr2")))
		.add_property("minDistance", &Chem::FeatureDistanceConstraint::getMinDistance)
		.add_property("maxDistance", &Chem::FeatureDistanceConstraint::getMaxDistance);
}
