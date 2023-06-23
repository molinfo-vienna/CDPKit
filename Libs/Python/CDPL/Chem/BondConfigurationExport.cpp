/* 
 * BondConfigurationExport.cpp 
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

#include "CDPL/Chem/BondConfiguration.hpp"

#include "NamespaceExports.hpp"


namespace 
{

    struct BondConfiguration {};
}


void CDPLPythonChem::exportBondConfigurations()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<BondConfiguration, boost::noncopyable>("BondConfiguration", python::no_init)
        .def_readonly("UNDEF", &Chem::BondConfiguration::UNDEF)
        .def_readonly("NONE", &Chem::BondConfiguration::NONE)
        .def_readonly("E", &Chem::BondConfiguration::E)
        .def_readonly("TRANS", &Chem::BondConfiguration::TRANS)
        .def_readonly("Z", &Chem::BondConfiguration::Z)
        .def_readonly("CIS", &Chem::BondConfiguration::CIS)
        .def_readonly("EITHER", &Chem::BondConfiguration::EITHER);
}
