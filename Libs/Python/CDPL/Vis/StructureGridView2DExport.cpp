/* 
 * StructureGridView2DExport.cpp 
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

#include "CDPL/Vis/StructureGridView2D.hpp"
#include "CDPL/Vis/FontMetrics.hpp"

#include "ClassExports.hpp"


namespace
{

    CDPL::Vis::StructureGridView2D::Cell& getCell(CDPL::Vis::StructureGridView2D& grid_view, std::size_t row, std::size_t col)
    {
        return grid_view(row, col);
    }

    CDPL::Vis::StructureGridView2D::Cell& getCellByTuple(CDPL::Vis::StructureGridView2D& grid_view, const boost::python::tuple& indices)
    {
        using namespace boost;

        auto row = python::extract<std::size_t>(indices[0]);
        auto col = python::extract<std::size_t>(indices[1]);

        return grid_view(row, col);
    }
}


void CDPLPythonVis::exportStructureGridView2D()
{
    using namespace boost;
    using namespace CDPL;

    python::scope scope = python::class_<Vis::StructureGridView2D, Vis::StructureGridView2D::SharedPointer, 
                                         python::bases<Vis::View2D>, boost::noncopyable>("StructureGridView2D", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def("getFontMetrics", &Vis::StructureGridView2D::getFontMetrics, python::arg("self"),
             python::return_internal_reference<1>())
        .def("__call__", &getCell, (python::arg("self"), python::arg("row"), python::arg("col")),
             python::return_internal_reference<>())
        .def("__getitem__", &getCellByTuple, (python::arg("self"), python::arg("row_and_col")),
             python::return_internal_reference<>())
        .add_property("fontMetrics", python::make_function(&Vis::StructureGridView2D::getFontMetrics,
                                                           python::return_internal_reference<1>()),
                      python::make_function(&Vis::StructureGridView2D::setFontMetrics,     
                                            python::with_custodian_and_ward<1, 2>()));

    python::class_<Vis::StructureGridView2D::Cell, Vis::StructureGridView2D::Cell::SharedPointer,
                   boost::noncopyable>("Cell", python::no_init)
        ;
}
