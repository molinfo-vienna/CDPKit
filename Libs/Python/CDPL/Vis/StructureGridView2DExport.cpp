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

#include "CDPL/Config.hpp"
#include "CDPL/Vis/StructureGridView2D.hpp"
#include "CDPL/Vis/FontMetrics.hpp"
#include "CDPL/Base/DataFormat.hpp"

#include "ClassExports.hpp"


namespace
{

    CDPL::Vis::StructureGridView2D::Cell& getCellByTuple(CDPL::Vis::StructureGridView2D& grid_view,
                                                         const boost::python::tuple& indices)
    {
        using namespace boost;

        return grid_view(python::extract<std::size_t>(indices[0]),
                         python::extract<std::size_t>(indices[1]));
    }

    CDPL::Vis::StructureGridView2D::Cell& copyCell(CDPL::Vis::StructureGridView2D::Cell& cell,
                                                   CDPL::Vis::StructureGridView2D::Cell& rhs)
    {
        return (cell = rhs);
    }
}


void CDPLPythonVis::exportStructureGridView2D()
{
    using namespace boost;
    using namespace CDPL;

    python::scope scope = python::class_<Vis::StructureGridView2D, Vis::StructureGridView2D::SharedPointer, 
                                         python::bases<Vis::View2D>, boost::noncopyable>("StructureGridView2D", python::no_init)
        .def(python::init<>(python::arg("self")))
        .def(python::init<const Vis::StructureGridView2D&>((python::arg("self"), python::arg("grid_view"))))
#ifdef HAVE_CAIRO
        .def("write", static_cast<bool (Vis::StructureGridView2D::*)(const std::string&)>
             (&Vis::StructureGridView2D::write),
             (python::arg("self"), python::arg("file_name")))
        .def("write", static_cast<bool (Vis::StructureGridView2D::*)(const std::string&, const std::string&)>
             (&Vis::StructureGridView2D::write),
             (python::arg("self"), python::arg("file_name"), python::arg("fmt")))
        .def("write", static_cast<bool (Vis::StructureGridView2D::*)(const std::string&, const Base::DataFormat&)>
             (&Vis::StructureGridView2D::write),
             (python::arg("self"), python::arg("file_name"), python::arg("fmt")))
        .def("write", static_cast<bool (Vis::StructureGridView2D::*)(std::ostream&, const std::string&)>
             (&Vis::StructureGridView2D::write),
             (python::arg("self"), python::arg("os"), python::arg("fmt")))
        .def("write", static_cast<bool (Vis::StructureGridView2D::*)(std::ostream&, const Base::DataFormat&)>
             (&Vis::StructureGridView2D::write),
             (python::arg("self"), python::arg("os"), python::arg("fmt")))
#endif // HAVE_CAIRO
        .def("getFontMetrics", &Vis::StructureGridView2D::getFontMetrics, python::arg("self"),
             python::return_internal_reference<>())
        .def("__call__", static_cast<Vis::StructureGridView2D::Cell& (Vis::StructureGridView2D::*)(std::size_t, std::size_t)>
             (&Vis::StructureGridView2D::operator()),
             (python::arg("self"), python::arg("row"), python::arg("col")),
             python::return_internal_reference<>())
        .def("__getitem__", &getCellByTuple, (python::arg("self"), python::arg("row_and_col")),
             python::return_internal_reference<>())
        .def("setCellSize", &Vis::StructureGridView2D::setCellSize, 
             (python::arg("self"), python::arg("width"), python::arg("height")))
        .def("getCellWidth", &Vis::StructureGridView2D::getCellWidth, python::arg("self"))
        .def("getCellHeight", &Vis::StructureGridView2D::getCellHeight, python::arg("self"))
        .def("resize", &Vis::StructureGridView2D::resize, 
             (python::arg("self"), python::arg("num_rows"), python::arg("num_cols")))
        .def("getNumRows", &Vis::StructureGridView2D::getNumRows, python::arg("self"))
        .def("getNumColumns", &Vis::StructureGridView2D::getNumColumns, python::arg("self"))
        .def("clearStructures", &Vis::StructureGridView2D::clearStructures, python::arg("self"))
        .def("clearAllText", &Vis::StructureGridView2D::clearAllText, python::arg("self"))
        .def("assign", &Vis::StructureGridView2D::operator=, (python::arg("self"), python::arg("grid_view")),
             python::return_self<>())
        .def_readonly("DEF_CELL_WIDTH", Vis::StructureGridView2D::DEF_CELL_WIDTH)
        .def_readonly("DEF_CELL_HEIGHT", Vis::StructureGridView2D::DEF_CELL_HEIGHT)
        .add_property("cellWidth", &Vis::StructureGridView2D::getCellWidth)
        .add_property("cellHeight", &Vis::StructureGridView2D::getCellHeight)
        .add_property("numRows", &Vis::StructureGridView2D::getNumRows)
        .add_property("numColumns", &Vis::StructureGridView2D::getNumColumns)
        .add_property("fontMetrics", python::make_function(&Vis::StructureGridView2D::getFontMetrics,
                                                           python::return_internal_reference<>()),
                      python::make_function(&Vis::StructureGridView2D::setFontMetrics,     
                                            python::with_custodian_and_ward<1, 2>()));

    python::class_<Vis::StructureGridView2D::Cell, Vis::StructureGridView2D::Cell::SharedPointer,
                   boost::noncopyable>("Cell", python::no_init)
        .def("setStructure", &Vis::StructureGridView2D::Cell::setStructure, (python::arg("self"), python::arg("molgraph")))
        .def("getStructure", &Vis::StructureGridView2D::Cell::getStructure, python::arg("self"), 
             python::return_internal_reference<>())
        .def("clearStructure", &Vis::StructureGridView2D::Cell::clearStructure, python::arg("self"))
        .def("hashStructure", &Vis::StructureGridView2D::Cell::hasStructure, python::arg("self"))
        .def("setText", &Vis::StructureGridView2D::Cell::setText,
             (python::arg("self"), python::arg("pos") = Vis::StructureGridView2D::Cell::DEF_TEXT_POSITION,
             python::arg("line_almnt") = Vis::Alignment::NONE))
        .def("getText", &Vis::StructureGridView2D::Cell::getText,
             (python::arg("self"), python::arg("pos") = Vis::StructureGridView2D::Cell::DEF_TEXT_POSITION),
             python::return_internal_reference<>())
        .def("clearText", &Vis::StructureGridView2D::Cell::clearText,
             (python::arg("self"), python::arg("pos") = Vis::StructureGridView2D::Cell::DEF_TEXT_POSITION))
        .def("clearAllText", &Vis::StructureGridView2D::Cell::clearAllText,
             python::arg("self"))
        .def("hasAnyText", &Vis::StructureGridView2D::Cell::hasAnyText,
             python::arg("self"))
        .def("hasText", &Vis::StructureGridView2D::Cell::hasText,
             (python::arg("self"), python::arg("pos")))
        .def("assign", &copyCell, (python::arg("self"), python::arg("cell")), python::return_self<>())
        .def_readonly("DEF_TEXT_POSITION", Vis::StructureGridView2D::Cell::DEF_TEXT_POSITION)
        .add_property("structure", 
                      python::make_function(&Vis::StructureGridView2D::Cell::getStructure,
                                            python::return_internal_reference<>()),
                      &Vis::StructureGridView2D::Cell::setStructure);
}
