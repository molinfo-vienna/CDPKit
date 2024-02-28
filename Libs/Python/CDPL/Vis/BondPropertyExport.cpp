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

#include "CDPL/Vis/BondProperty.hpp"
#include "CDPL/Base/LookupKey.hpp"

#include "NamespaceExports.hpp"


namespace 
{

    struct BondProperty {};
}


void CDPLPythonVis::exportBondProperties()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<BondProperty, boost::noncopyable>("BondProperty", python::no_init)
        .def_readonly("COLOR", &Vis::BondProperty::COLOR)
        .def_readonly("DOUBLE_BOND_TRIM_LENGTH", &Vis::BondProperty::DOUBLE_BOND_TRIM_LENGTH)
        .def_readonly("LABEL_FONT", &Vis::BondProperty::LABEL_FONT)
        .def_readonly("LABEL_MARGIN", &Vis::BondProperty::LABEL_MARGIN)
        .def_readonly("LABEL_SIZE", &Vis::BondProperty::LABEL_SIZE)
        .def_readonly("LINE_SPACING", &Vis::BondProperty::LINE_SPACING)
        .def_readonly("LINE_WIDTH", &Vis::BondProperty::LINE_WIDTH)
        .def_readonly("REACTION_CENTER_LINE_LENGTH", &Vis::BondProperty::REACTION_CENTER_LINE_LENGTH)
        .def_readonly("REACTION_CENTER_LINE_SPACING", &Vis::BondProperty::REACTION_CENTER_LINE_SPACING)
        .def_readonly("TRIPLE_BOND_TRIM_LENGTH", &Vis::BondProperty::TRIPLE_BOND_TRIM_LENGTH)
        .def_readonly("STEREO_BOND_HASH_SPACING", &Vis::BondProperty::STEREO_BOND_HASH_SPACING)
        .def_readonly("STEREO_BOND_WEDGE_WIDTH", &Vis::BondProperty::STEREO_BOND_WEDGE_WIDTH)
        .def_readonly("CONFIGURATION_LABEL_FONT", &Vis::BondProperty::CONFIGURATION_LABEL_FONT)
        .def_readonly("CONFIGURATION_LABEL_SIZE", &Vis::BondProperty::CONFIGURATION_LABEL_SIZE)
        .def_readonly("CONFIGURATION_LABEL_COLOR", &Vis::BondProperty::CONFIGURATION_LABEL_COLOR)
        .def_readonly("CUSTOM_LABEL_FONT", &Vis::BondProperty::CUSTOM_LABEL_FONT)
        .def_readonly("CUSTOM_LABEL_SIZE", &Vis::BondProperty::CUSTOM_LABEL_SIZE)
        .def_readonly("CUSTOM_LABEL_COLOR", &Vis::BondProperty::CUSTOM_LABEL_COLOR)
        .def_readonly("CUSTOM_LABEL", &Vis::BondProperty::CUSTOM_LABEL)
        ;
}
