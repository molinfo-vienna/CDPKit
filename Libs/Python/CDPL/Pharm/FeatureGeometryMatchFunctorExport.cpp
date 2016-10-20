/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeatureGeometryMatchFunctorExport.cpp 
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

#include "CDPL/Pharm/FeatureGeometryMatchFunctor.hpp"
#include "CDPL/Pharm/Feature.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

    bool callOperator(CDPL::Pharm::FeatureGeometryMatchFunctor& func, 
					  CDPL::Pharm::Feature& ftr1, CDPL::Pharm::Feature& ftr2, const CDPL::Math::Matrix4D& xform)
    {
		return func(ftr1, ftr2, xform);
    }
}


void CDPLPythonPharm::exportFeatureGeometryMatchFunctor()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Pharm::FeatureGeometryMatchFunctor, boost::noncopyable>("FeatureGeometryMatchFunctor", python::no_init)
		.def(python::init<const Pharm::FeatureGeometryMatchFunctor&>((python::arg("self"), python::arg("func"))))
		.def(python::init<bool, double, double, double>((python::arg("self"), python::arg("query_mode"),
														 python::arg("hba_ang_tol") = Pharm::FeatureGeometryMatchFunctor::DEF_HBA_ANGLE_TOLERANCE, 
														 python::arg("hbd_ang_tol") = Pharm::FeatureGeometryMatchFunctor::DEF_HBD_ANGLE_TOLERANCE,
														 python::arg("ar_ang_tol") = Pharm::FeatureGeometryMatchFunctor::DEF_AR_PLANE_ANGLE_TOLERANCE)))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::FeatureGeometryMatchFunctor>())
		.def("assign", &Pharm::FeatureGeometryMatchFunctor::operator=, 
			 (python::arg("self"), python::arg("func")), python::return_self<>())
		.def("getHBondAcceptorAngleTolerance", &Pharm::FeatureGeometryMatchFunctor::getHBondAcceptorAngleTolerance,
			 python::arg("self"))
		.def("getHBondDonorAngleTolerance", &Pharm::FeatureGeometryMatchFunctor::getHBondDonorAngleTolerance,
			 python::arg("self"))
		.def("getAromPlaneAngleTolerance", &Pharm::FeatureGeometryMatchFunctor::getAromPlaneAngleTolerance,
			 python::arg("self"))
		.def("strictGeometryMatching", &Pharm::FeatureGeometryMatchFunctor::strictGeometryMatching,
			 python::arg("self"))
		.def("__call__", &callOperator, (python::arg("self"), python::arg("ftr1"), python::arg("ftr2"), python::arg("xform")))
		.add_property("hBondAcceptorAngleTolerance", &Pharm::FeatureGeometryMatchFunctor::getHBondAcceptorAngleTolerance)
		.add_property("hBondDonorAngleTolerance", &Pharm::FeatureGeometryMatchFunctor::getHBondDonorAngleTolerance)
		.add_property("aromPlaneAngleTolerance", &Pharm::FeatureGeometryMatchFunctor::getAromPlaneAngleTolerance)
		.add_property("strictGeomMatching", &Pharm::FeatureGeometryMatchFunctor::strictGeometryMatching)
		.def_readonly("DEF_HBA_ANGLE_TOLERANCE", &Pharm::FeatureGeometryMatchFunctor::DEF_HBA_ANGLE_TOLERANCE)
		.def_readonly("DEF_HBD_ANGLE_TOLERANCE", &Pharm::FeatureGeometryMatchFunctor::DEF_HBD_ANGLE_TOLERANCE)
		.def_readonly("DEF_AR_PLANE_ANGLE_TOLERANCE", &Pharm::FeatureGeometryMatchFunctor::DEF_AR_PLANE_ANGLE_TOLERANCE);
}
