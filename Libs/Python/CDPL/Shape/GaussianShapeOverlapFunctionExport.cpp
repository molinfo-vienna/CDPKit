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
			this->get_override("setShapeFunction")(boost::ref(func), is_ref);
		}

		const CDPL::Shape::GaussianShapeFunction* getShapeFunction(bool ref) const {
			return this->get_override("getShapeFunction")(ref);
		}

		void setColorMatchFunction(const ColorMatchFunction& func) {
			this->get_override("setColorMatchFunction")(boost::ref(func));
		}

		const ColorMatchFunction& getColorMatchFunction() const {
			return this->get_override("getColorMatchFunction")();
		}

		double calcSelfOverlap(bool ref) const {
			return this->get_override("calcSelfOverlap")(ref);
		}
			
		double calcOverlap() const {
			return this->get_override("calcOverlap")();
		}
		
		double calcOverlap(const CDPL::Math::Vector3DArray& coords) const {
			return this->get_override("calcOverlap")(boost::ref(coords));
		}

		double calcOverlapGradient(const CDPL::Math::Vector3DArray& coords, CDPL::Math::Vector3DArray& grad) const {
			return this->get_override("calcOverlapGradient")(boost::ref(coords), boost::ref(grad));
		}
	};
}


void CDPLPythonShape::exportGaussianShapeOverlapFunction()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<GaussianShapeOverlapFunctionWrapper, GaussianShapeOverlapFunctionWrapper::SharedPointer,
				   boost::noncopyable>("GaussianShapeOverlapFunction", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::GaussianShapeOverlapFunction>())
		.def("setShapeFunction", python::pure_virtual(&Shape::GaussianShapeOverlapFunction::setShapeFunction),
			 (python::arg("self"), python::arg("func"), python::arg("is_ref")), python::with_custodian_and_ward<1, 2>())
		.def("getShapeFunction", python::pure_virtual(&Shape::GaussianShapeOverlapFunction::getShapeFunction),
			 (python::arg("self"), python::arg("ref")), python::return_internal_reference<>())
		.def("setColorMatchFunction", python::pure_virtual(&Shape::GaussianShapeOverlapFunction::setColorMatchFunction),
			 (python::arg("self"), python::arg("func")), python::with_custodian_and_ward<1, 2>())
		.def("getColorMatchFunction", python::pure_virtual(&Shape::GaussianShapeOverlapFunction::getColorMatchFunction),
			 python::arg("self"), python::return_internal_reference<>())
		.def("calcSelfOverlap", python::pure_virtual(&Shape::GaussianShapeOverlapFunction::calcSelfOverlap),
			 (python::arg("self"), python::arg("ref")))
		.def("calcOverlap", python::pure_virtual(static_cast<double (Shape::GaussianShapeOverlapFunction::*)() const>
												 (&Shape::GaussianShapeOverlapFunction::calcOverlap)),
			 python::arg("self"))
		.def("calcOverlap", python::pure_virtual(static_cast<double (Shape::GaussianShapeOverlapFunction::*)(const Math::Vector3DArray&) const>
												 (&Shape::GaussianShapeOverlapFunction::calcOverlap)),
			 (python::arg("self"), python::arg("coords")))
		.def("calcOverlapGradient", python::pure_virtual(static_cast<double (Shape::GaussianShapeOverlapFunction::*)(const Math::Vector3DArray&, Math::Vector3DArray&) const>
														 (&Shape::GaussianShapeOverlapFunction::calcOverlapGradient)),
			 (python::arg("self"), python::arg("coords"), python::arg("grad")))
		.add_property("colorMatchFunction", python::make_function(&Shape::GaussianShapeOverlapFunction::getColorMatchFunction,
																  python::return_internal_reference<>()),
					  &Shape::GaussianShapeOverlapFunction::setColorMatchFunction);
}
