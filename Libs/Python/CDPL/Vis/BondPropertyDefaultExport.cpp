/* 
 * BondPropertyDefaultExport.cpp 
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

#include "CDPL/Vis/BondPropertyDefault.hpp"

#include "NamespaceExports.hpp"


namespace 
{

    struct BondPropertyDefault {};
}


void CDPLPythonVis::exportBondPropertyDefaults()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<BondPropertyDefault, boost::noncopyable>("BondPropertyDefault", python::no_init)
        .def_readonly("COLOR", &Vis::BondPropertyDefault::COLOR)
        .def_readonly("LINE_WIDTH", &Vis::BondPropertyDefault::LINE_WIDTH)
        .def_readonly("LINE_SPACING", &Vis::BondPropertyDefault::LINE_SPACING)
        .def_readonly("STEREO_BOND_WEDGE_WIDTH", &Vis::BondPropertyDefault::STEREO_BOND_WEDGE_WIDTH)
        .def_readonly("STEREO_BOND_HASH_SPACING", &Vis::BondPropertyDefault::STEREO_BOND_HASH_SPACING)
        .def_readonly("REACTION_CENTER_LINE_LENGTH", &Vis::BondPropertyDefault::REACTION_CENTER_LINE_LENGTH)
        .def_readonly("REACTION_CENTER_LINE_SPACING", &Vis::BondPropertyDefault::REACTION_CENTER_LINE_SPACING)
        .def_readonly("DOUBLE_BOND_TRIM_LENGTH", &Vis::BondPropertyDefault::DOUBLE_BOND_TRIM_LENGTH)
        .def_readonly("TRIPLE_BOND_TRIM_LENGTH", &Vis::BondPropertyDefault::TRIPLE_BOND_TRIM_LENGTH)
        .def_readonly("LABEL_FONT", &Vis::BondPropertyDefault::LABEL_FONT)
        .def_readonly("LABEL_SIZE", &Vis::BondPropertyDefault::LABEL_SIZE)
        .def_readonly("LABEL_MARGIN", &Vis::BondPropertyDefault::LABEL_MARGIN)
        .def_readonly("CONFIGURATION_LABEL_FONT", &Vis::BondPropertyDefault::CONFIGURATION_LABEL_FONT)
        .def_readonly("CONFIGURATION_LABEL_SIZE", &Vis::BondPropertyDefault::CONFIGURATION_LABEL_SIZE)
        .def_readonly("CONFIGURATION_LABEL_COLOR", &Vis::BondPropertyDefault::CONFIGURATION_LABEL_COLOR)
        .def_readonly("CUSTOM_LABEL_FONT", &Vis::BondPropertyDefault::CUSTOM_LABEL_FONT)
        .def_readonly("CUSTOM_LABEL_SIZE", &Vis::BondPropertyDefault::CUSTOM_LABEL_SIZE)
        .def_readonly("CUSTOM_LABEL_COLOR", &Vis::BondPropertyDefault::CUSTOM_LABEL_COLOR)
        .def_readonly("CUSTOM_LABEL", &Vis::BondPropertyDefault::CUSTOM_LABEL)
        .def_readonly("HIGHLIGHTED_FLAG", &Vis::BondPropertyDefault::HIGHLIGHTED_FLAG)
        .def_readonly("HIGHLIGHT_AREA_BRUSH", &Vis::BondPropertyDefault::HIGHLIGHT_AREA_BRUSH)
        .def_readonly("HIGHLIGHT_AREA_OUTLINE_PEN", &Vis::BondPropertyDefault::HIGHLIGHT_AREA_OUTLINE_PEN)
        ;
}
