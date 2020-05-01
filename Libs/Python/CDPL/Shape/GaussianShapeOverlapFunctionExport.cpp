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

		GaussianShapeOverlapFunctionWrapper():
			GaussianShapeOverlapFunction() {}

		GaussianShapeOverlapFunctionWrapper(const CDPL::Shape::GaussianShapeOverlapFunction& func):
			GaussianShapeOverlapFunction(func) {}

		GaussianShapeOverlapFunctionWrapper(const CDPL::Shape::GaussianShapeFunction& ref_shape_func,
											const CDPL::Shape::GaussianShapeFunction& ovl_shape_func):
			GaussianShapeOverlapFunction(ref_shape_func, ovl_shape_func) {}

		double calcOverlapImpl(const CDPL::Shape::GaussianProductList* prod_list1, const CDPL::Shape::GaussianProductList* prod_list2,
							   const GaussianProductCenterArray& trans_prod_ctrs, bool orig_centers, bool rigid_xform) const {
			return 0.0;
		}

		double calcOverlapGradientImpl(const CDPL::Shape::GaussianProductList* prod_list1, const CDPL::Shape::GaussianProductList* prod_list2,
									   const GaussianProductCenterArray& trans_prod_ctrs, CDPL::Math::Vector3DArray::StorageType& grad,
									   bool rigid_xform) const {
			return 0.0;
		}
	};
}


void CDPLPythonShape::exportGaussianShapeOverlapFunction()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<GaussianShapeOverlapFunctionWrapper, GaussianShapeOverlapFunctionWrapper::SharedPointer, boost::noncopyable>("GaussianShapeOverlapFunction", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Shape::GaussianShapeFunction&, const Shape::GaussianShapeFunction&>
			 ((python::arg("self"), python::arg("ref_shape_func"), python::arg("ovl_shape_func")))
			 [python::with_custodian_and_ward<1, 2, python::with_custodian_and_ward<1, 3> >()])
		.def(python::init<const Shape::GaussianShapeOverlapFunction&>((python::arg("self"), python::arg("func")))[python::with_custodian_and_ward<1, 2>()])
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::GaussianShapeOverlapFunction>())
		.def("assign", python::pure_virtual(&Shape::GaussianShapeOverlapFunction::operator=), (python::arg("self"), python::arg("func")),
			 python::return_self<python::with_custodian_and_ward<1, 2> >())
		.def("setShapeFunction", python::pure_virtual(&Shape::GaussianShapeOverlapFunction::setShapeFunction),
			 (python::arg("self"), python::arg("func"), python::arg("is_ref")), python::with_custodian_and_ward<1, 2>())
		.def("getShapeFunction", python::pure_virtual(&Shape::GaussianShapeOverlapFunction::getShapeFunction),
			 (python::arg("self"), python::arg("ref")), python::return_internal_reference<>())
		.def("calcSelfOverlap", python::pure_virtual(&Shape::GaussianShapeOverlapFunction::calcSelfOverlap), (python::arg("self"), python::arg("ref")))
		.def("calcOverlap", python::pure_virtual(static_cast<double (Shape::GaussianShapeOverlapFunction::*)() const>(&Shape::GaussianShapeOverlapFunction::calcOverlap)),
			 python::arg("self"))
		.def("calcOverlap", python::pure_virtual(static_cast<double (Shape::GaussianShapeOverlapFunction::*)(const Math::Matrix4D&, bool)>(&Shape::GaussianShapeOverlapFunction::calcOverlap)),
			 (python::arg("self"), python::arg("xform"), python::arg("rigid_xform") = true))
		.def("calcOverlapGradient", python::pure_virtual(static_cast<double (Shape::GaussianShapeOverlapFunction::*)(const Math::Matrix4D&, Math::Vector3DArray&, bool)>(
															 &Shape::GaussianShapeOverlapFunction::calcOverlapGradient)),
			 (python::arg("self"), python::arg("xform"), python::arg("grad"), python::arg("rigid_xform") = true));
}
