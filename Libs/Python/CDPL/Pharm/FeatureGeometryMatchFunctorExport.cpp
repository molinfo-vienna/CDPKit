/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * FeatureGeometryMatchFunctorExport.cpp 
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

#include "CDPL/Pharm/FeatureGeometryMatchFunctor.hpp"
#include "CDPL/Pharm/Feature.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


namespace
{

	bool callOperator1(CDPL::Pharm::FeatureGeometryMatchFunctor& func, CDPL::Pharm::Feature& ftr1,
					   CDPL::Pharm::Feature& ftr2)
    {
		return func(ftr1, ftr2);
    }
	
    bool callOperator2(CDPL::Pharm::FeatureGeometryMatchFunctor& func, CDPL::Pharm::Feature& ftr1,
					   CDPL::Pharm::Feature& ftr2, const CDPL::Math::Matrix4D& xform)
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
		.def(python::init<double, double, double, double, double, double>((python::arg("self"), 
														 python::arg("max_hba_int_dir_angle") = Pharm::FeatureGeometryMatchFunctor::DEF_MAX_HBA_INTERACTION_DIR_ANGLE, 
														 python::arg("max_hba_orient_dev") = Pharm::FeatureGeometryMatchFunctor::DEF_MAX_HBA_ORIENTATION_DEVIATION,
														 python::arg("max_hbd_int_dir_dev") = Pharm::FeatureGeometryMatchFunctor::DEF_MAX_HBD_INTERACTION_DIR_DEVIATION,
														 python::arg("max_xba_int_dir_dev") = Pharm::FeatureGeometryMatchFunctor::DEF_MAX_XBA_INTERACTION_DIR_DEVIATION,
														 python::arg("max_xbd_int_dir_dev") = Pharm::FeatureGeometryMatchFunctor::DEF_MAX_XBD_INTERACTION_DIR_DEVIATION,
														 python::arg("max_ar_orient_dev") = Pharm::FeatureGeometryMatchFunctor::DEF_MAX_AR_ORIENTATION_DEVIATION)))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Pharm::FeatureGeometryMatchFunctor>())
		.def("assign", CDPLPythonBase::copyAssOp(&Pharm::FeatureGeometryMatchFunctor::operator=), 
			 (python::arg("self"), python::arg("func")), python::return_self<>())
		.def("getMaxHBAInteractionDirAngle", &Pharm::FeatureGeometryMatchFunctor::getMaxHBAInteractionDirAngle,
			 python::arg("self"))
		.def("setMaxHBAInteractionDirAngle", &Pharm::FeatureGeometryMatchFunctor::setMaxHBAInteractionDirAngle,
			 (python::arg("self"), python::arg("angle")))
		.def("getMaxHBAOrientationDeviation",  &Pharm::FeatureGeometryMatchFunctor::getMaxHBAOrientationDeviation, python::arg("self"))
		.def("setMaxHBAOrientationDeviation", &Pharm::FeatureGeometryMatchFunctor::setMaxHBAOrientationDeviation,
			 (python::arg("self"), python::arg("angle")))
		.def("getMaxHBDInteractionDirDeviation", &Pharm::FeatureGeometryMatchFunctor::getMaxHBDInteractionDirDeviation,
			 python::arg("self"))
		.def("setMaxHBDInteractionDirDeviation", &Pharm::FeatureGeometryMatchFunctor::setMaxHBDInteractionDirDeviation,
			 (python::arg("self"), python::arg("angle")))
		.def("getMaxXBAInteractionDirDeviation", &Pharm::FeatureGeometryMatchFunctor::getMaxXBAInteractionDirDeviation,
			 python::arg("self"))
		.def("setMaxXBAInteractionDirDeviation", &Pharm::FeatureGeometryMatchFunctor::setMaxXBAInteractionDirDeviation,
			 (python::arg("self"), python::arg("angle")))
		.def("getMaxXBDInteractionDirDeviation", &Pharm::FeatureGeometryMatchFunctor::getMaxXBDInteractionDirDeviation,
			 python::arg("self"))
		.def("setMaxXBDInteractionDirDeviation", &Pharm::FeatureGeometryMatchFunctor::setMaxXBDInteractionDirDeviation,
			 (python::arg("self"), python::arg("angle")))
		.def("getMaxAROrientationDeviation", &Pharm::FeatureGeometryMatchFunctor::getMaxAROrientationDeviation,
			 python::arg("self"))
		.def("setMaxAROrientationDeviation", &Pharm::FeatureGeometryMatchFunctor::setMaxAROrientationDeviation,
			 (python::arg("self"), python::arg("angle")))
		.def("__call__", &callOperator1, (python::arg("self"), python::arg("ftr1"), python::arg("ftr2")))
		.def("__call__", &callOperator2, (python::arg("self"), python::arg("ftr1"), python::arg("ftr2"), python::arg("xform")))
		.add_property("maxHBAInteractionDirAngle", &Pharm::FeatureGeometryMatchFunctor::getMaxHBAInteractionDirAngle,
					  &Pharm::FeatureGeometryMatchFunctor::setMaxHBAInteractionDirAngle)
		.add_property("maxHBAOrientationDeviation",  &Pharm::FeatureGeometryMatchFunctor::getMaxHBAOrientationDeviation,
					  &Pharm::FeatureGeometryMatchFunctor::setMaxHBAOrientationDeviation)
		.add_property("maxHBDInteractionDirDeviation", &Pharm::FeatureGeometryMatchFunctor::getMaxHBDInteractionDirDeviation,
					  &Pharm::FeatureGeometryMatchFunctor::setMaxHBDInteractionDirDeviation)
		.add_property("maxXBDInteractionDirDeviation", &Pharm::FeatureGeometryMatchFunctor::getMaxXBDInteractionDirDeviation,
					  &Pharm::FeatureGeometryMatchFunctor::setMaxXBDInteractionDirDeviation)
		.add_property("maxXBAInteractionDirDeviation", &Pharm::FeatureGeometryMatchFunctor::getMaxXBAInteractionDirDeviation,
					  &Pharm::FeatureGeometryMatchFunctor::setMaxXBAInteractionDirDeviation)
		.add_property("maxAROrientationDeviation", &Pharm::FeatureGeometryMatchFunctor::getMaxAROrientationDeviation,
					  &Pharm::FeatureGeometryMatchFunctor::setMaxAROrientationDeviation)
		.def_readonly("DEF_MAX_HBA_INTERACTION_DIR_ANGLE", &Pharm::FeatureGeometryMatchFunctor::DEF_MAX_HBA_INTERACTION_DIR_ANGLE)
		.def_readonly("DEF_MAX_HBA_ORIENTATION_DEVIATION", &Pharm::FeatureGeometryMatchFunctor::DEF_MAX_HBA_ORIENTATION_DEVIATION)
		.def_readonly("DEF_MAX_HBD_INTERACTION_DIR_DEVIATION", &Pharm::FeatureGeometryMatchFunctor::DEF_MAX_HBD_INTERACTION_DIR_DEVIATION)
		.def_readonly("DEF_MAX_XBA_INTERACTION_DIR_DEVIATION", &Pharm::FeatureGeometryMatchFunctor::DEF_MAX_XBA_INTERACTION_DIR_DEVIATION)
		.def_readonly("DEF_MAX_XBD_INTERACTION_DIR_DEVIATION", &Pharm::FeatureGeometryMatchFunctor::DEF_MAX_XBD_INTERACTION_DIR_DEVIATION)
		.def_readonly("DEF_MAX_AR_ORIENTATION_DEVIATION", &Pharm::FeatureGeometryMatchFunctor::DEF_MAX_AR_ORIENTATION_DEVIATION);
}
