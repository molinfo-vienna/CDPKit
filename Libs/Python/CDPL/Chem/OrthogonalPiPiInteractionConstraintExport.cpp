/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * OrthogonalPiPiInteractionConstraintExport.cpp 
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

#include "CDPL/Chem/OrthogonalPiPiInteractionConstraint.hpp"
#include "CDPL/Chem/Feature.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

    bool callOperator(CDPL::Chem::OrthogonalPiPiInteractionConstraint& constr, 
					  CDPL::Chem::Feature& ftr1, CDPL::Chem::Feature& ftr2)
    {
		return constr(ftr1, ftr2);
    }
}


void CDPLPythonChem::exportOrthogonalPiPiInteractionConstraint()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Chem::OrthogonalPiPiInteractionConstraint, boost::noncopyable>("OrthogonalPiPiInteractionConstraint", python::no_init)
		.def(python::init<const Chem::OrthogonalPiPiInteractionConstraint&>((python::arg("self"), python::arg("constr"))))
		.def(python::init<double, double, double, double>((python::arg("self"),
														 python::arg("min_v_dist") = Chem::OrthogonalPiPiInteractionConstraint::DEF_MIN_V_DISTANCE, 
														 python::arg("max_v_dist") = Chem::OrthogonalPiPiInteractionConstraint::DEF_MAX_V_DISTANCE,
														 python::arg("max_h_dist") = Chem::OrthogonalPiPiInteractionConstraint::DEF_MAX_H_DISTANCE,
														 python::arg("ang_tol") = Chem::OrthogonalPiPiInteractionConstraint::DEF_ANGLE_TOLERANCE)))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Chem::OrthogonalPiPiInteractionConstraint>())
		.def("getMinVDistance", &Chem::OrthogonalPiPiInteractionConstraint::getMinVDistance, python::arg("self"))
		.def("getMaxVDistance", &Chem::OrthogonalPiPiInteractionConstraint::getMaxVDistance, python::arg("self"))
		.def("getMaxHDistance", &Chem::OrthogonalPiPiInteractionConstraint::getMaxHDistance, python::arg("self"))
		.def("getAngleTolerance", &Chem::OrthogonalPiPiInteractionConstraint::getAngleTolerance, python::arg("self"))
		.def("assign", &Chem::OrthogonalPiPiInteractionConstraint::operator=, 
			 (python::arg("self"), python::arg("constr")), python::return_self<>())
		.def("__call__", &callOperator, (python::arg("self"), python::arg("ftr1"), python::arg("ftr2")))
		.add_property("minVDistance", &Chem::OrthogonalPiPiInteractionConstraint::getMinVDistance)
		.add_property("maxVDistance", &Chem::OrthogonalPiPiInteractionConstraint::getMaxVDistance)
		.add_property("maxHDistance", &Chem::OrthogonalPiPiInteractionConstraint::getMaxHDistance)
		.add_property("angleTolerance", &Chem::OrthogonalPiPiInteractionConstraint::getAngleTolerance)
		.def_readonly("DEF_MIN_V_DISTANCE", Chem::OrthogonalPiPiInteractionConstraint::DEF_MIN_V_DISTANCE)
		.def_readonly("DEF_MAX_V_DISTANCE", Chem::OrthogonalPiPiInteractionConstraint::DEF_MAX_V_DISTANCE)
		.def_readonly("DEF_MAX_H_DISTANCE", Chem::OrthogonalPiPiInteractionConstraint::DEF_MAX_H_DISTANCE)
		.def_readonly("DEF_ANGLE_TOLERANCE", Chem::OrthogonalPiPiInteractionConstraint::DEF_ANGLE_TOLERANCE);
}
