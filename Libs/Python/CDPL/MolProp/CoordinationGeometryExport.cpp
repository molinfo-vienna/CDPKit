/* 
 * CoordinationGeometryExport.cpp 
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

#include "CDPL/MolProp/CoordinationGeometry.hpp"

#include "NamespaceExports.hpp"


namespace 
{

    struct CoordinationGeometry {};
}


void CDPLPythonMolProp::exportCoordinationGeometries()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<CoordinationGeometry, boost::noncopyable>("CoordinationGeometry", python::no_init)
	.def_readonly("UNDEF", &MolProp::CoordinationGeometry::UNDEF)
	.def_readonly("NONE", &MolProp::CoordinationGeometry::NONE)
	.def_readonly("LINEAR", &MolProp::CoordinationGeometry::LINEAR)
	.def_readonly("TRIGONAL_PLANAR", &MolProp::CoordinationGeometry::TRIGONAL_PLANAR)
	.def_readonly("TETRAHEDRAL", &MolProp::CoordinationGeometry::TETRAHEDRAL)
	.def_readonly("TRIGONAL_BIPYRAMIDAL", &MolProp::CoordinationGeometry::TRIGONAL_BIPYRAMIDAL)
	.def_readonly("OCTAHEDRAL", &MolProp::CoordinationGeometry::OCTAHEDRAL)
	.def_readonly("PENTAGONAL_BIPYRAMIDAL", &MolProp::CoordinationGeometry::PENTAGONAL_BIPYRAMIDAL)
	.def_readonly("SQUARE_ANTIPRISMATIC", &MolProp::CoordinationGeometry::SQUARE_ANTIPRISMATIC)
	.def_readonly("BENT", &MolProp::CoordinationGeometry::BENT)
	.def_readonly("TRIGONAL_PYRAMIDAL", &MolProp::CoordinationGeometry::TRIGONAL_PYRAMIDAL)
	.def_readonly("SQUARE_PLANAR", &MolProp::CoordinationGeometry::SQUARE_PLANAR)
	.def_readonly("SQUARE_PYRAMIDAL", &MolProp::CoordinationGeometry::SQUARE_PYRAMIDAL)
	.def_readonly("T_SHAPED", &MolProp::CoordinationGeometry::T_SHAPED)
	.def_readonly("SEESAW", &MolProp::CoordinationGeometry::SEESAW)
	.def_readonly("PENTAGONAL_PYRAMIDAL", &MolProp::CoordinationGeometry::PENTAGONAL_PYRAMIDAL)
	.def_readonly("PENTAGONAL_PLANAR", &MolProp::CoordinationGeometry::PENTAGONAL_PLANAR);
}
