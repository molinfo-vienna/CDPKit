/* 
 * GaussianShapeExport.cpp 
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


#include <memory>

#include <boost/python.hpp>

#include "CDPL/Shape/GaussianShape.hpp"

#include "Base/PropertyContainerVisitor.hpp"
#include "Base/CopyAssOp.hpp"
#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


namespace
{

	struct GaussianShapeWrapper : CDPL::Shape::GaussianShape, boost::python::wrapper<CDPL::Shape::GaussianShape> 
	{
	
		typedef std::shared_ptr<GaussianShapeWrapper> SharedPointer;

		GaussianShapeWrapper(): 
			CDPL::Shape::GaussianShape() {}

		GaussianShapeWrapper(const CDPL::Shape::GaussianShape& shape): 
			CDPL::Shape::GaussianShape(shape) {}
	};
}


void CDPLPythonShape::exportGaussianShape()
{
    using namespace boost;
    using namespace CDPL;

	python::scope scope = python::class_<GaussianShapeWrapper, GaussianShapeWrapper::SharedPointer, 
										 python::bases<Base::PropertyContainer> >("GaussianShape", python::no_init)
		.def(python::init<>(python::arg("self")))
		.def(python::init<const Shape::GaussianShape&>((python::arg("self"), python::arg("shape"))))
		.def("assign", CDPLPythonBase::copyAssOp(&Shape::GaussianShape::operator=), (python::arg("self"), python::arg("shape")),
			 python::return_self<>())
		.def(CDPLPythonBase::PropertyContainerSpecialFunctionsVisitor(true))	
		.def("clear", &Shape::GaussianShape::clear, python::arg("self"))
		.def("getNumElements", &Shape::GaussianShape::getNumElements, python::arg("self"))
		.def("__len__", &Shape::GaussianShape::getNumElements, python::arg("self"))
		.def("addElement", static_cast<void (Shape::GaussianShape::*)(const Math::Vector3D&, double, std::size_t, double)>(&Shape::GaussianShape::addElement),
			 (python::arg("self"), python::arg("pos"), python::arg("radius"),
			  python::arg("color") = 0, python::arg("hardness") = 2.7))
		.def("addElement", static_cast<void (Shape::GaussianShape::*)(const Shape::GaussianShape::Element&)>(&Shape::GaussianShape::addElement),
			 (python::arg("self"), python::arg("elem")))
		.def("removeElement", &Shape::GaussianShape::removeElement, (python::arg("self"), python::arg("idx")))
		.def("__delitem__", &Shape::GaussianShape::removeElement, (python::arg("self"), python::arg("idx")))
		.def("getElement", static_cast<Shape::GaussianShape::Element& (Shape::GaussianShape::*)(std::size_t)>(&Shape::GaussianShape::getElement),
			 (python::arg("self"), python::arg("idx")), python::return_internal_reference<>())
		.def("__getitem__", static_cast<Shape::GaussianShape::Element& (Shape::GaussianShape::*)(std::size_t)>(&Shape::GaussianShape::getElement),
			 (python::arg("self"), python::arg("idx")), python::return_internal_reference<>());	

	python::class_<Shape::GaussianShape::Element>("Element", python::no_init)
		.def(python::init<const Shape::GaussianShape::Element&>((python::arg("self"), python::arg("elem"))))
		.def(python::init<const Math::Vector3D&, double, std::size_t, double>((python::arg("pos"), python::arg("radius"),
																			   python::arg("color") = 0, python::arg("hardness") = 2.7)))
		.def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::GaussianShape::Element>())
		.def("assign", CDPLPythonBase::copyAssOp(&Shape::GaussianShape::Element::operator=),
			 (python::arg("self"), python::arg("elem")), python::return_self<>())
		.def("setPosition", &Shape::GaussianShape::Element::setPosition, (python::arg("self"), python::arg("pos")))
		.def("getPosition", &Shape::GaussianShape::Element::getPosition, python::arg("self"), python::return_internal_reference<>())
		.def("setRadius", &Shape::GaussianShape::Element::setRadius, (python::arg("self"), python::arg("radius")))
		.def("getRadius", &Shape::GaussianShape::Element::getRadius, python::arg("self"))
		.def("setColor", &Shape::GaussianShape::Element::setColor, (python::arg("self"), python::arg("color")))
		.def("getColor", &Shape::GaussianShape::Element::getColor, python::arg("self"))
		.def("setHardness", &Shape::GaussianShape::Element::setHardness, (python::arg("self"), python::arg("hardness")))
		.def("getHardness", &Shape::GaussianShape::Element::getHardness, python::arg("self"))
		.add_property("radius", &Shape::GaussianShape::Element::getRadius,
					  &Shape::GaussianShape::Element::setRadius)
		.add_property("color", &Shape::GaussianShape::Element::getColor,
					  &Shape::GaussianShape::Element::setColor)
		.add_property("hardness", &Shape::GaussianShape::Element::getHardness,
					  &Shape::GaussianShape::Element::setHardness)
		.add_property("position", python::make_function(&Shape::GaussianShape::Element::getPosition,
														python::return_internal_reference<>()),
					  &Shape::GaussianShape::Element::setPosition);

	python::register_ptr_to_python<Shape::GaussianShape::SharedPointer>();
}
