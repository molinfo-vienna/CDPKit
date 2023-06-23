/* 
 * BRICSAtomLabelExport.cpp 
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

#include "CDPL/Chem/BRICSAtomLabel.hpp"

#include "NamespaceExports.hpp"


namespace 
{

    struct BRICSAtomLabel {};
}


void CDPLPythonChem::exportBRICSAtomLabels()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<BRICSAtomLabel, boost::noncopyable>("BRICSAtomLabel", python::no_init)
        .def_readonly("NONE", &Chem::BRICSAtomLabel::NONE)
        .def_readonly("L1", &Chem::BRICSAtomLabel::L1)
        .def_readonly("L2", &Chem::BRICSAtomLabel::L2)
        .def_readonly("L3", &Chem::BRICSAtomLabel::L3)
        .def_readonly("L4", &Chem::BRICSAtomLabel::L4)
        .def_readonly("L5", &Chem::BRICSAtomLabel::L5)
        .def_readonly("L6", &Chem::BRICSAtomLabel::L6)
        .def_readonly("L7", &Chem::BRICSAtomLabel::L7)
        .def_readonly("L8", &Chem::BRICSAtomLabel::L8)
        .def_readonly("L9", &Chem::BRICSAtomLabel::L9)
        .def_readonly("L10", &Chem::BRICSAtomLabel::L10)
        .def_readonly("L11", &Chem::BRICSAtomLabel::L11)
        .def_readonly("L12", &Chem::BRICSAtomLabel::L12)
        .def_readonly("L13", &Chem::BRICSAtomLabel::L13)
        .def_readonly("L14", &Chem::BRICSAtomLabel::L14)
        .def_readonly("L15", &Chem::BRICSAtomLabel::L15)
        .def_readonly("L16", &Chem::BRICSAtomLabel::L16);
}
