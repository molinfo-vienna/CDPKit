/* 
 * GaussianShapeFunctionExport.cpp 
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

#include "CDPL/Shape/GaussianShapeFunction.hpp"
#include "CDPL/Shape/GaussianShape.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"

#include "ClassExports.hpp"


void CDPLPythonShape::exportGaussianShapeFunction()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Shape::GaussianShapeFunction, Shape::GaussianShapeFunction::SharedPointer>("GaussianShapeFunction", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Shape::GaussianShape&>((python::arg("self"), python::arg("shape")))[python::with_custodian_and_ward<1, 2>()])
        .def(python::init<const Shape::GaussianShapeFunction&>((python::arg("self"), python::arg("func")))[python::with_custodian_and_ward<1, 2>()])
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::GaussianShapeFunction>())
        .def("assign", &Shape::GaussianShapeFunction::operator=, (python::arg("self"), python::arg("func")), python::return_self<python::with_custodian_and_ward<1, 2> >())
        .def("setShape", &Shape::GaussianShapeFunction::setShape, (python::arg("self"), python::arg("shape")), python::with_custodian_and_ward<1, 2>())
        .def("getShape", &Shape::GaussianShapeFunction::getShape, python::arg("self"), python::return_internal_reference<>())
        .def("setMaxOrder", &Shape::GaussianShapeFunction::setMaxOrder, (python::arg("self"), python::arg("max_order")))
        .def("getMaxOrder", &Shape::GaussianShapeFunction::getMaxOrder, python::arg("self"))
        .def("setDistanceCutoff", &Shape::GaussianShapeFunction::setDistanceCutoff, (python::arg("self"), python::arg("cutoff")))
        .def("getDistanceCutoff", &Shape::GaussianShapeFunction::getDistanceCutoff, python::arg("self"))
        .def("reset", &Shape::GaussianShapeFunction::reset, python::arg("self"))
        .def("transform", &Shape::GaussianShapeFunction::transform, (python::arg("self"), python::arg("xform")))
        .def("getElementPositions", &Shape::GaussianShapeFunction::getElementPositions, (python::arg("self"), python::arg("coords")))
        .def("getElementPosition", &Shape::GaussianShapeFunction::getElementPosition, (python::arg("self"), python::arg("idx")),
            python::return_internal_reference<>())
        .def("calcDensity", &Shape::GaussianShapeFunction::calcDensity, (python::arg("self"), python::arg("pos")))
        .def("calcSurfaceArea", static_cast<double (Shape::GaussianShapeFunction::*)() const>(&Shape::GaussianShapeFunction::calcSurfaceArea),
             python::arg("self"))
        .def("calcSurfaceArea", static_cast<double (Shape::GaussianShapeFunction::*)(std::size_t) const>(&Shape::GaussianShapeFunction::calcSurfaceArea),
             (python::arg("self"), python::arg("elem_idx")))
        .def("calcCentroid", &Shape::GaussianShapeFunction::calcCentroid, (python::arg("self"), python::arg("ctr")))
        .def("calcQuadrupoleTensor", &Shape::GaussianShapeFunction::calcQuadrupoleTensor,
             (python::arg("self"), python::arg("ctr"), python::arg("quad_tensor")))
        .def_readonly("DEF_MAX_PRODUCT_ORDER", &Shape::GaussianShapeFunction::DEF_MAX_PRODUCT_ORDER)
        .def_readonly("DEF_DISTANCE_CUTOFF", &Shape::GaussianShapeFunction::DEF_DISTANCE_CUTOFF)
        .add_property("shape", python::make_function(&Shape::GaussianShapeFunction::getShape, python::return_internal_reference<>()),
                      python::make_function(&Shape::GaussianShapeFunction::setShape, python::with_custodian_and_ward<1, 2>()))
        .add_property("volume", &Shape::GaussianShapeFunction::calcVolume)
        .add_property("surfaceArea", static_cast<double (Shape::GaussianShapeFunction::*)() const>(&Shape::GaussianShapeFunction::calcSurfaceArea))
        .add_property("maxOrder", &Shape::GaussianShapeFunction::getMaxOrder, &Shape::GaussianShapeFunction::setMaxOrder)
        .add_property("distCutoff", &Shape::GaussianShapeFunction::getDistanceCutoff, &Shape::GaussianShapeFunction::setDistanceCutoff);
}
