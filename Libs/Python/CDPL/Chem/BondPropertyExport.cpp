/* 
 * BondPropertyExport.cpp 
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

#include "CDPL/Chem/BondProperty.hpp"
#include "CDPL/Base/LookupKey.hpp"

#include "NamespaceExports.hpp"


namespace 
{

    struct BondProperty {};
}


void CDPLPythonChem::exportBondProperties()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<BondProperty, boost::noncopyable>("BondProperty", python::no_init)
        .def_readonly("ORDER", &Chem::BondProperty::ORDER)
        .def_readonly("SYBYL_TYPE", &Chem::BondProperty::SYBYL_TYPE)
        .def_readonly("RING_FLAG", &Chem::BondProperty::RING_FLAG)
        .def_readonly("AROMATICITY_FLAG", &Chem::BondProperty::AROMATICITY_FLAG)
        .def_readonly("STEREO_DESCRIPTOR", &Chem::BondProperty::STEREO_DESCRIPTOR)
        .def_readonly("STEREO_CENTER_FLAG", &Chem::BondProperty::STEREO_CENTER_FLAG)
        .def_readonly("CIP_CONFIGURATION", &Chem::BondProperty::CIP_CONFIGURATION)
        .def_readonly("DIRECTION", &Chem::BondProperty::DIRECTION)
        .def_readonly("STEREO_2D_FLAG", &Chem::BondProperty::STEREO_2D_FLAG)
        .def_readonly("REACTION_CENTER_STATUS", &Chem::BondProperty::REACTION_CENTER_STATUS)
        .def_readonly("MATCH_CONSTRAINTS", &Chem::BondProperty::MATCH_CONSTRAINTS)
        .def_readonly("MATCH_EXPRESSION", &Chem::BondProperty::MATCH_EXPRESSION)
        .def_readonly("MATCH_EXPRESSION_STRING", &Chem::BondProperty::MATCH_EXPRESSION_STRING);
}
