/* 
 * AlignmentExport.cpp 
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

#include "CDPL/Vis/Alignment.hpp"

#include "NamespaceExports.hpp"


namespace 
{

    struct Alignment {};
}


void CDPLPythonVis::exportAlignments()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<Alignment, boost::noncopyable>("Alignment", python::no_init)
        .def_readonly("BOTTOM", &Vis::Alignment::BOTTOM)
        .def_readonly("CENTER", &Vis::Alignment::CENTER)
        .def_readonly("H_ALIGNMENT_MASK", &Vis::Alignment::H_ALIGNMENT_MASK)
        .def_readonly("H_CENTER", &Vis::Alignment::H_CENTER)
        .def_readonly("LEFT", &Vis::Alignment::LEFT)
        .def_readonly("NONE", &Vis::Alignment::NONE)
        .def_readonly("RIGHT", &Vis::Alignment::RIGHT)
        .def_readonly("TOP", &Vis::Alignment::TOP)
        .def_readonly("V_ALIGNMENT_MASK", &Vis::Alignment::V_ALIGNMENT_MASK)
        .def_readonly("V_CENTER", &Vis::Alignment::V_CENTER);
}
