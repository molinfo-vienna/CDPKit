/* 
 * ScoringFunctorExport.cpp 
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

#include "CDPL/Shape/ScoringFunctors.hpp"
#include "CDPL/Shape/AlignmentResult.hpp"

#include "Base/ObjectIdentityCheckVisitor.hpp"
#include "Base/CopyAssOp.hpp"

#include "ClassExports.hpp"


void CDPLPythonShape::exportScoringFunctors()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Shape::TotalOverlapTanimotoScore>("TotalOverlapTanimotoScore", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Shape::TotalOverlapTanimotoScore&>((python::arg("self"), python::arg("score"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::TotalOverlapTanimotoScore>())
        .def("assign", CDPLPythonBase::copyAssOp(&Shape::TotalOverlapTanimotoScore::operator=),
             (python::arg("self"), python::arg("score")), python::return_self<>())
        .def("__call__", &Shape::TotalOverlapTanimotoScore::operator(), (python::arg("self"), python::arg("res")));

    python::class_<Shape::ShapeTanimotoScore>("ShapeTanimotoScore", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Shape::ShapeTanimotoScore&>((python::arg("self"), python::arg("score"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::ShapeTanimotoScore>())
        .def("assign", CDPLPythonBase::copyAssOp(&Shape::ShapeTanimotoScore::operator=),
             (python::arg("self"), python::arg("score")), python::return_self<>())
        .def("__call__", &Shape::ShapeTanimotoScore::operator(), (python::arg("self"), python::arg("res")));

    python::class_<Shape::ColorTanimotoScore>("ColorTanimotoScore", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Shape::ColorTanimotoScore&>((python::arg("self"), python::arg("score"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::ColorTanimotoScore>())
        .def("assign", CDPLPythonBase::copyAssOp(&Shape::ColorTanimotoScore::operator=),
             (python::arg("self"), python::arg("score")), python::return_self<>())
        .def("__call__", &Shape::ColorTanimotoScore::operator(), (python::arg("self"), python::arg("res")));

    python::class_<Shape::TanimotoComboScore>("TanimotoComboScore", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Shape::TanimotoComboScore&>((python::arg("self"), python::arg("score"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::TanimotoComboScore>())
        .def("assign", CDPLPythonBase::copyAssOp(&Shape::TanimotoComboScore::operator=),
             (python::arg("self"), python::arg("score")), python::return_self<>())
        .def("__call__", &Shape::TanimotoComboScore::operator(), (python::arg("self"), python::arg("res")));


    python::class_<Shape::TotalOverlapTverskyScore>("TotalOverlapTverskyScore", python::no_init)
        .def(python::init<double, double>((python::arg("self"), python::arg("alpha") = 0.95, python::arg("beta") = 0.05)))
        .def(python::init<const Shape::TotalOverlapTverskyScore&>((python::arg("self"), python::arg("score"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::TotalOverlapTverskyScore>())
        .def("assign", CDPLPythonBase::copyAssOp(&Shape::TotalOverlapTverskyScore::operator=),
             (python::arg("self"), python::arg("score")), python::return_self<>())
        .def("__call__", &Shape::TotalOverlapTverskyScore::operator(), (python::arg("self"), python::arg("res")));

    python::class_<Shape::ShapeTverskyScore>("ShapeTverskyScore", python::no_init)
        .def(python::init<double, double>((python::arg("self"), python::arg("alpha") = 0.95, python::arg("beta") = 0.05)))
        .def(python::init<const Shape::ShapeTverskyScore&>((python::arg("self"), python::arg("score"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::ShapeTverskyScore>())
        .def("assign", CDPLPythonBase::copyAssOp(&Shape::ShapeTverskyScore::operator=),
             (python::arg("self"), python::arg("score")), python::return_self<>())
        .def("__call__", &Shape::ShapeTverskyScore::operator(), (python::arg("self"), python::arg("res")));

    python::class_<Shape::ColorTverskyScore>("ColorTverskyScore", python::no_init)
        .def(python::init<double, double>((python::arg("self"), python::arg("alpha") = 0.95, python::arg("beta") = 0.05)))
        .def(python::init<const Shape::ColorTverskyScore&>((python::arg("self"), python::arg("score"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::ColorTverskyScore>())
        .def("assign", CDPLPythonBase::copyAssOp(&Shape::ColorTverskyScore::operator=),
             (python::arg("self"), python::arg("score")), python::return_self<>())
        .def("__call__", &Shape::ColorTverskyScore::operator(), (python::arg("self"), python::arg("res")));

    python::class_<Shape::TverskyComboScore>("TverskyComboScore", python::no_init)
        .def(python::init<double, double>((python::arg("self"), python::arg("alpha") = 0.95, python::arg("beta") = 0.05)))
        .def(python::init<const Shape::TverskyComboScore&>((python::arg("self"), python::arg("score"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::TverskyComboScore>())
        .def("assign", CDPLPythonBase::copyAssOp(&Shape::TverskyComboScore::operator=),
             (python::arg("self"), python::arg("score")), python::return_self<>())
        .def("__call__", &Shape::TverskyComboScore::operator(), (python::arg("self"), python::arg("res")));


    python::class_<Shape::ReferenceTotalOverlapTverskyScore>("ReferenceTotalOverlapTverskyScore", python::no_init)
        .def(python::init<double>((python::arg("self"), python::arg("alpha") = 0.95)))
        .def(python::init<const Shape::ReferenceTotalOverlapTverskyScore&>((python::arg("self"), python::arg("score"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::ReferenceTotalOverlapTverskyScore>())
        .def("assign", CDPLPythonBase::copyAssOp(&Shape::ReferenceTotalOverlapTverskyScore::operator=),
             (python::arg("self"), python::arg("score")), python::return_self<>())
        .def("__call__", &Shape::ReferenceTotalOverlapTverskyScore::operator(), (python::arg("self"), python::arg("res")));

    python::class_<Shape::ReferenceShapeTverskyScore>("ReferenceShapeTverskyScore", python::no_init)
        .def(python::init<double>((python::arg("self"), python::arg("alpha") = 0.95)))
        .def(python::init<const Shape::ReferenceShapeTverskyScore&>((python::arg("self"), python::arg("score"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::ReferenceShapeTverskyScore>())
        .def("assign", CDPLPythonBase::copyAssOp(&Shape::ReferenceShapeTverskyScore::operator=),
             (python::arg("self"), python::arg("score")), python::return_self<>())
        .def("__call__", &Shape::ReferenceShapeTverskyScore::operator(), (python::arg("self"), python::arg("res")));

    python::class_<Shape::ReferenceColorTverskyScore>("ReferenceColorTverskyScore", python::no_init)
        .def(python::init<double>((python::arg("self"), python::arg("alpha") = 0.95)))
        .def(python::init<const Shape::ReferenceColorTverskyScore&>((python::arg("self"), python::arg("score"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::ReferenceColorTverskyScore>())
        .def("assign", CDPLPythonBase::copyAssOp(&Shape::ReferenceColorTverskyScore::operator=),
             (python::arg("self"), python::arg("score")), python::return_self<>())
        .def("__call__", &Shape::ReferenceColorTverskyScore::operator(), (python::arg("self"), python::arg("res")));

    python::class_<Shape::ReferenceTverskyComboScore>("ReferenceTverskyComboScore", python::no_init)
        .def(python::init<double>((python::arg("self"), python::arg("alpha") = 0.95)))
        .def(python::init<const Shape::ReferenceTverskyComboScore&>((python::arg("self"), python::arg("score"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::ReferenceTverskyComboScore>())
        .def("assign", CDPLPythonBase::copyAssOp(&Shape::ReferenceTverskyComboScore::operator=),
             (python::arg("self"), python::arg("score")), python::return_self<>())
        .def("__call__", &Shape::ReferenceTverskyComboScore::operator(), (python::arg("self"), python::arg("res")));


    python::class_<Shape::AlignedTotalOverlapTverskyScore>("AlignedTotalOverlapTverskyScore", python::no_init)
        .def(python::init<double>((python::arg("self"), python::arg("beta") = 0.95)))
        .def(python::init<const Shape::AlignedTotalOverlapTverskyScore&>((python::arg("self"), python::arg("score"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::AlignedTotalOverlapTverskyScore>())
        .def("assign", CDPLPythonBase::copyAssOp(&Shape::AlignedTotalOverlapTverskyScore::operator=),
             (python::arg("self"), python::arg("score")), python::return_self<>())
        .def("__call__", &Shape::AlignedTotalOverlapTverskyScore::operator(), (python::arg("self"), python::arg("res")));

    python::class_<Shape::AlignedShapeTverskyScore>("AlignedShapeTverskyScore", python::no_init)
        .def(python::init<double>((python::arg("self"), python::arg("beta") = 0.95)))
        .def(python::init<const Shape::AlignedShapeTverskyScore&>((python::arg("self"), python::arg("score"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::AlignedShapeTverskyScore>())
        .def("assign", CDPLPythonBase::copyAssOp(&Shape::AlignedShapeTverskyScore::operator=),
             (python::arg("self"), python::arg("score")), python::return_self<>())
        .def("__call__", &Shape::AlignedShapeTverskyScore::operator(), (python::arg("self"), python::arg("res")));

    python::class_<Shape::AlignedColorTverskyScore>("AlignedColorTverskyScore", python::no_init)
        .def(python::init<double>((python::arg("self"), python::arg("beta") = 0.95)))
        .def(python::init<const Shape::AlignedColorTverskyScore&>((python::arg("self"), python::arg("score"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::AlignedColorTverskyScore>())
        .def("assign", CDPLPythonBase::copyAssOp(&Shape::AlignedColorTverskyScore::operator=),
             (python::arg("self"), python::arg("score")), python::return_self<>())
        .def("__call__", &Shape::AlignedColorTverskyScore::operator(), (python::arg("self"), python::arg("res")));

    python::class_<Shape::AlignedTverskyComboScore>("AlignedTverskyComboScore", python::no_init)
        .def(python::init<double>((python::arg("self"), python::arg("beta") = 0.95)))
        .def(python::init<const Shape::AlignedTverskyComboScore&>((python::arg("self"), python::arg("score"))))
        .def(CDPLPythonBase::ObjectIdentityCheckVisitor<Shape::AlignedTverskyComboScore>())
        .def("assign", CDPLPythonBase::copyAssOp(&Shape::AlignedTverskyComboScore::operator=),
             (python::arg("self"), python::arg("score")), python::return_self<>())
        .def("__call__", &Shape::AlignedTverskyComboScore::operator(), (python::arg("self"), python::arg("res")));
}
