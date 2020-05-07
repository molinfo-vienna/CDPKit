/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * GaussianShapeOverlapFunctionExport.cpp 
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
#include <boost/shared_ptr.hpp>

#include "CDPL/Shape/GaussianShapeOverlapFunction.hpp"
#include "CDPL/Shape/GaussianShapeFunction.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

	struct GaussianShapeOverlapFunctionWrapper : CDPL::Shape::GaussianShapeOverlapFunction, boost::python::wrapper<CDPL::Shape::GaussianShapeOverlapFunction> 
	{

		typedef boost::shared_ptr<GaussianShapeOverlapFunctionWrapper> SharedPointer;

		void setShapeFunction(const CDPL::Shape::GaussianShapeFunction& func, bool is_ref) {
			if (boost::python::override f = this->get_override("setShapeFunction")) {
				f(boost::ref(func), is_ref);
				return;
			}

			CDPL::Shape::GaussianShapeOverlapFunction::setShapeFunction(func, is_ref);
		}

		void setShapeFunctionDef(const CDPL::Shape::GaussianShapeFunction& func, bool is_ref) {
			CDPL::Shape::GaussianShapeOverlapFunction::setShapeFunction(func, is_ref);
		}

		const CDPL::Shape::GaussianShapeFunction* getShapeFunction(bool ref) const {
			if (boost::python::override f = this->get_override("getShapeFunction")) {
				return f(ref);
			}

			return CDPL::Shape::GaussianShapeOverlapFunction::getShapeFunction(ref);
		}

		const CDPL::Shape::GaussianShapeFunction* getShapeFunctionDef(bool ref) const {
			return CDPL::Shape::GaussianShapeOverlapFunction::getShapeFunction(ref);
		}

		double calcSelfOverlap(bool ref) const {
			if (boost::python::override f = this->get_override("calcSelfOverlap")) {
				return f(ref);
			}

			return CDPL::Shape::GaussianShapeOverlapFunction::calcSelfOverlap(ref);
		}

		double calcSelfOverlapDef(bool ref) const {
			return CDPL::Shape::GaussianShapeOverlapFunction::calcSelfOverlap(ref);
		}
			
		double calcOverlap() const {
			if (boost::python::override f = this->get_override("calcOverlap")) {
				return f();
			}

			return CDPL::Shape::GaussianShapeOverlapFunction::calcOverlap();
		}
		
		double calcOverlapDef1() const {
			return CDPL::Shape::GaussianShapeOverlapFunction::calcOverlap();
		}
		
		double calcOverlap(const CDPL::Math::Matrix4D& xform, bool rigid_xform) {
			if (boost::python::override f = this->get_override("calcOverlap")) {
				return f(boost::ref(xform), rigid_xform);
			}

			return CDPL::Shape::GaussianShapeOverlapFunction::calcOverlap(xform, rigid_xform);
		}
		
		double calcOverlapDef2(const CDPL::Math::Matrix4D& xform, bool rigid_xform) {
			return CDPL::Shape::GaussianShapeOverlapFunction::calcOverlap(xform, rigid_xform);
		}

		double calcOverlapGradient(const CDPL::Math::Matrix4D& xform, CDPL::Math::Vector3DArray& grad, bool rigid_xform) {
			if (boost::python::override f = this->get_override("calcOverlapGradient")) {
				return f(boost::ref(xform), boost::ref(grad), rigid_xform);
			}

			return CDPL::Shape::GaussianShapeOverlapFunction::calcOverlapGradient(xform, grad, rigid_xform);
		}

		double calcOverlapGradientDef(const CDPL::Math::Matrix4D& xform, CDPL::Math::Vector3DArray& grad, bool rigid_xform) {
			return CDPL::Shape::GaussianShapeOverlapFunction::calcOverlapGradient(xform, grad, rigid_xform);
		}
	};
}


void CDPLPythonShape::exportGaussianShapeOverlapFunction()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<GaussianShapeOverlapFunctionWrapper, GaussianShapeOverlapFunctionWrapper::SharedPointer, boost::noncopyable>("GaussianShapeOverlapFunction", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::GaussianShapeOverlapFunction>())
		.def("setShapeFunction", &Shape::GaussianShapeOverlapFunction::setShapeFunction, &GaussianShapeOverlapFunctionWrapper::setShapeFunctionDef,
			 (python::arg("self"), python::arg("func"), python::arg("is_ref")), python::with_custodian_and_ward<1, 2>())
		.def("getShapeFunction", &Shape::GaussianShapeOverlapFunction::getShapeFunction, &GaussianShapeOverlapFunctionWrapper::getShapeFunctionDef,
			 (python::arg("self"), python::arg("ref")), python::return_internal_reference<>())
		.def("calcSelfOverlap", &Shape::GaussianShapeOverlapFunction::calcSelfOverlap,  &GaussianShapeOverlapFunctionWrapper::calcSelfOverlapDef,
			 (python::arg("self"), python::arg("ref")))
		.def("calcOverlap", static_cast<double (Shape::GaussianShapeOverlapFunction::*)() const>(&Shape::GaussianShapeOverlapFunction::calcOverlap),
			 &GaussianShapeOverlapFunctionWrapper::calcOverlapDef1,
			 python::arg("self"))
		.def("calcOverlap",static_cast<double (Shape::GaussianShapeOverlapFunction::*)(const Math::Matrix4D&, bool)>(&Shape::GaussianShapeOverlapFunction::calcOverlap),
			 &GaussianShapeOverlapFunctionWrapper::calcOverlapDef2,
			 (python::arg("self"), python::arg("xform"), python::arg("rigid_xform") = true))
		.def("calcOverlapGradient", static_cast<double (Shape::GaussianShapeOverlapFunction::*)(const Math::Matrix4D&, Math::Vector3DArray&, bool)>(
				 &Shape::GaussianShapeOverlapFunction::calcOverlapGradient), &GaussianShapeOverlapFunctionWrapper::calcOverlapGradientDef,
			 (python::arg("self"), python::arg("xform"), python::arg("grad"), python::arg("rigid_xform") = true));
}
