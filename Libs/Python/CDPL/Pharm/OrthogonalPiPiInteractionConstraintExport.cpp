/* 
 * OrthogonalPiPiInteractionConstraintExport.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003 Thomas Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Pharm/OrthogonalPiPiInteractionConstraint.hpp"
#include "CDPL/Pharm/Feature.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

    bool callOperator(CDPL::Pharm::OrthogonalPiPiInteractionConstraint& constr, 
					  CDPL::Pharm::Feature& ftr1, CDPL::Pharm::Feature& ftr2)
    {
		return constr(ftr1, ftr2);
    }
}


void CDPLPythonPharm::exportOrthogonalPiPiInteractionConstraint()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Pharm::OrthogonalPiPiInteractionConstraint, boost::noncopyable>("OrthogonalPiPiInteractionConstraint", python::no_init)
		.def(python::init<const Pharm::OrthogonalPiPiInteractionConstraint&>((python::arg("self"), python::arg("constr"))))
		.def(python::init<double, double, double, double>((python::arg("self"),
														 python::arg("min_h_dist") = Pharm::OrthogonalPiPiInteractionConstraint::DEF_MIN_H_DISTANCE, 
														 python::arg("max_h_dist") = Pharm::OrthogonalPiPiInteractionConstraint::DEF_MAX_H_DISTANCE,
														 python::arg("max_v_dist") = Pharm::OrthogonalPiPiInteractionConstraint::DEF_MAX_V_DISTANCE,
														 python::arg("max_ang") = Pharm::OrthogonalPiPiInteractionConstraint::DEF_MAX_ANGLE)))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::OrthogonalPiPiInteractionConstraint>())
		.def("getMinHDistance", &Pharm::OrthogonalPiPiInteractionConstraint::getMinHDistance, python::arg("self"))
		.def("getMaxHDistance", &Pharm::OrthogonalPiPiInteractionConstraint::getMaxHDistance, python::arg("self"))
		.def("getMaxVDistance", &Pharm::OrthogonalPiPiInteractionConstraint::getMaxVDistance, python::arg("self"))
		.def("getMaxAngle", &Pharm::OrthogonalPiPiInteractionConstraint::getMaxAngle, python::arg("self"))
		.def("assign", CDPLPythonBase::copyAssOp(&Pharm::OrthogonalPiPiInteractionConstraint::operator=), 
			 (python::arg("self"), python::arg("constr")), python::return_self<>())
		.def("__call__", &callOperator, (python::arg("self"), python::arg("ftr1"), python::arg("ftr2")))
		.add_property("minHDistance", &Pharm::OrthogonalPiPiInteractionConstraint::getMinHDistance)
		.add_property("maxHDistance", &Pharm::OrthogonalPiPiInteractionConstraint::getMaxHDistance)
		.add_property("maxVDistance", &Pharm::OrthogonalPiPiInteractionConstraint::getMaxVDistance)
		.add_property("maxAngle", &Pharm::OrthogonalPiPiInteractionConstraint::getMaxAngle)
		.def_readonly("DEF_MIN_H_DISTANCE", Pharm::OrthogonalPiPiInteractionConstraint::DEF_MIN_H_DISTANCE)
		.def_readonly("DEF_MAX_H_DISTANCE", Pharm::OrthogonalPiPiInteractionConstraint::DEF_MAX_H_DISTANCE)
		.def_readonly("DEF_MAX_V_DISTANCE", Pharm::OrthogonalPiPiInteractionConstraint::DEF_MAX_V_DISTANCE)
		.def_readonly("DEF_MAX_ANGLE", Pharm::OrthogonalPiPiInteractionConstraint::DEF_MAX_ANGLE);
}
