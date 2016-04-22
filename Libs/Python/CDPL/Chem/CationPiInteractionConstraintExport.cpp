/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * CationPiInteractionConstraintExport.cpp 
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

#include "CDPL/Chem/CationPiInteractionConstraint.hpp"
#include "CDPL/Chem/Feature.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

    bool callOperator(CDPL::Chem::CationPiInteractionConstraint& constr, 
					  CDPL::Chem::Feature& ftr1, CDPL::Chem::Feature& ftr2)
    {
		return constr(ftr1, ftr2);
    }
}


void CDPLPythonChem::exportCationPiInteractionConstraint()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Chem::CationPiInteractionConstraint, boost::noncopyable>("CationPiInteractionConstraint", python::no_init)
		.def(python::init<const Chem::CationPiInteractionConstraint&>((python::arg("self"), python::arg("constr"))))
		.def(python::init<bool, double, double, double>((python::arg("self"), python::arg("aro_cat"), 
														 python::arg("min_dist") = Chem::CationPiInteractionConstraint::DEF_MIN_DISTANCE, 
														 python::arg("max_dist") = Chem::CationPiInteractionConstraint::DEF_MAX_DISTANCE,
														 python::arg("max_ang") = Chem::CationPiInteractionConstraint::DEF_MAX_ANGLE)))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::CationPiInteractionConstraint>())
		.def("getMinDistance", &Chem::CationPiInteractionConstraint::getMinDistance, python::arg("self"))
		.def("getMaxDistance", &Chem::CationPiInteractionConstraint::getMaxDistance, python::arg("self"))
		.def("getMaxAngle", &Chem::CationPiInteractionConstraint::getMaxAngle, python::arg("self"))
		.def("assign", &Chem::CationPiInteractionConstraint::operator=, 
			 (python::arg("self"), python::arg("constr")), python::return_self<>())
		.def("__call__", &callOperator, (python::arg("self"), python::arg("ftr1"), python::arg("ftr2")))
		.add_property("minDistance", &Chem::CationPiInteractionConstraint::getMinDistance)
		.add_property("maxDistance", &Chem::CationPiInteractionConstraint::getMaxDistance)
		.add_property("maxAngle", &Chem::CationPiInteractionConstraint::getMaxAngle)
		.def_readonly("DEF_MIN_DISTANCE", Chem::CationPiInteractionConstraint::DEF_MIN_DISTANCE)
		.def_readonly("DEF_MAX_DISTANCE", Chem::CationPiInteractionConstraint::DEF_MAX_DISTANCE)
		.def_readonly("DEF_MAX_ANGLE", Chem::CationPiInteractionConstraint::DEF_MAX_ANGLE);
}
