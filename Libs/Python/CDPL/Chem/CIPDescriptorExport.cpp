/* 
 * CIPDescriptorExport.cpp 
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

#include "CDPL/Chem/CIPDescriptor.hpp"

#include "NamespaceExports.hpp"


namespace 
{

    struct CIPDescriptor {};
}


void CDPLPythonChem::exportCIPDescriptors()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<CIPDescriptor, boost::noncopyable>("CIPDescriptor", python::no_init)
        .def_readonly("UNDEF", &Chem::CIPDescriptor::UNDEF)
        .def_readonly("NONE", &Chem::CIPDescriptor::NONE)
        .def_readonly("NS", &Chem::CIPDescriptor::NS)
        .def_readonly("R", &Chem::CIPDescriptor::R)
        .def_readonly("S", &Chem::CIPDescriptor::S)
        .def_readonly("r", &Chem::CIPDescriptor::r)
        .def_readonly("s", &Chem::CIPDescriptor::s)
        .def_readonly("M", &Chem::CIPDescriptor::M)
        .def_readonly("P", &Chem::CIPDescriptor::P)
        .def_readonly("m", &Chem::CIPDescriptor::m)
        .def_readonly("p", &Chem::CIPDescriptor::p)
        .def_readonly("E", &Chem::CIPDescriptor::E)
        .def_readonly("Z", &Chem::CIPDescriptor::Z)
        .def_readonly("seqCis", &Chem::CIPDescriptor::seqCis)
        .def_readonly("seqTrans", &Chem::CIPDescriptor::seqTrans);
}
