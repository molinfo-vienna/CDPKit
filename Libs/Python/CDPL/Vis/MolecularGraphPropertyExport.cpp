/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MolecularGraphPropertyExport.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Vis/MolecularGraphProperty.hpp"
#include "CDPL/Base/LookupKey.hpp"

#include "NamespaceExports.hpp"


namespace 
{

	struct MolecularGraphProperty {};
}


void CDPLPythonVis::exportMolecularGraphProperties()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<MolecularGraphProperty, boost::noncopyable>("MolecularGraphProperty", python::no_init)
		.def_readonly("ATOM_COLOR", &Vis::MolecularGraphProperty::ATOM_COLOR)
		.def_readonly("ATOM_COLOR_TABLE", &Vis::MolecularGraphProperty::ATOM_COLOR_TABLE)
		.def_readonly("RADICAL_ELECTRON_DOT_SIZE", &Vis::MolecularGraphProperty::RADICAL_ELECTRON_DOT_SIZE)
		.def_readonly("ATOM_LABEL_FONT", &Vis::MolecularGraphProperty::ATOM_LABEL_FONT)
		.def_readonly("ATOM_LABEL_MARGIN", &Vis::MolecularGraphProperty::ATOM_LABEL_MARGIN)
		.def_readonly("ATOM_LABEL_SIZE", &Vis::MolecularGraphProperty::ATOM_LABEL_SIZE)
		.def_readonly("SECONDARY_ATOM_LABEL_FONT", &Vis::MolecularGraphProperty::SECONDARY_ATOM_LABEL_FONT)
		.def_readonly("SECONDARY_ATOM_LABEL_SIZE", &Vis::MolecularGraphProperty::SECONDARY_ATOM_LABEL_SIZE)
		.def_readonly("BOND_COLOR", &Vis::MolecularGraphProperty::BOND_COLOR)
		.def_readonly("BOND_LABEL_FONT", &Vis::MolecularGraphProperty::BOND_LABEL_FONT)
		.def_readonly("BOND_LABEL_MARGIN", &Vis::MolecularGraphProperty::BOND_LABEL_MARGIN)
		.def_readonly("BOND_LABEL_SIZE", &Vis::MolecularGraphProperty::BOND_LABEL_SIZE)
		.def_readonly("BOND_LINE_SPACING", &Vis::MolecularGraphProperty::BOND_LINE_SPACING)
		.def_readonly("BOND_LINE_WIDTH", &Vis::MolecularGraphProperty::BOND_LINE_WIDTH)
		.def_readonly("REACTION_CENTER_LINE_LENGTH", &Vis::MolecularGraphProperty::REACTION_CENTER_LINE_LENGTH)
		.def_readonly("REACTION_CENTER_LINE_SPACING", &Vis::MolecularGraphProperty::REACTION_CENTER_LINE_SPACING)
		.def_readonly("STEREO_BOND_HASH_SPACING", &Vis::MolecularGraphProperty::STEREO_BOND_HASH_SPACING)
		.def_readonly("STEREO_BOND_WEDGE_WIDTH", &Vis::MolecularGraphProperty::STEREO_BOND_WEDGE_WIDTH)
		.def_readonly("DOUBLE_BOND_TRIM_LENGTH", &Vis::MolecularGraphProperty::DOUBLE_BOND_TRIM_LENGTH)
		.def_readonly("TRIPLE_BOND_TRIM_LENGTH", &Vis::MolecularGraphProperty::TRIPLE_BOND_TRIM_LENGTH);
}
