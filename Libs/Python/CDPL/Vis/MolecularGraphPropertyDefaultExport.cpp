/* 
 * MolecularGraphPropertyDefaultExport.cpp 
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

#include "CDPL/Vis/MolecularGraphPropertyDefault.hpp"

#include "NamespaceExports.hpp"


namespace 
{

	struct MolecularGraphPropertyDefault {};
}


void CDPLPythonVis::exportMolecularGraphPropertyDefaults()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<MolecularGraphPropertyDefault, boost::noncopyable>("MolecularGraphPropertyDefault", python::no_init)
		.def_readonly("ATOM_COLOR_TABLE", &Vis::MolecularGraphPropertyDefault::ATOM_COLOR_TABLE)
		.def_readonly("ATOM_COLOR", &Vis::MolecularGraphPropertyDefault::ATOM_COLOR)
		.def_readonly("ATOM_LABEL_FONT", &Vis::MolecularGraphPropertyDefault::ATOM_LABEL_FONT)
		.def_readonly("ATOM_LABEL_SIZE", &Vis::MolecularGraphPropertyDefault::ATOM_LABEL_SIZE)
		.def_readonly("SECONDARY_ATOM_LABEL_FONT", &Vis::MolecularGraphPropertyDefault::SECONDARY_ATOM_LABEL_FONT)
		.def_readonly("SECONDARY_ATOM_LABEL_SIZE", &Vis::MolecularGraphPropertyDefault::SECONDARY_ATOM_LABEL_SIZE)
		.def_readonly("ATOM_LABEL_MARGIN", &Vis::MolecularGraphPropertyDefault::ATOM_LABEL_MARGIN)
		.def_readonly("RADICAL_ELECTRON_DOT_SIZE", &Vis::MolecularGraphPropertyDefault::RADICAL_ELECTRON_DOT_SIZE)
		.def_readonly("BOND_COLOR", &Vis::MolecularGraphPropertyDefault::BOND_COLOR)
		.def_readonly("BOND_LINE_WIDTH", &Vis::MolecularGraphPropertyDefault::BOND_LINE_WIDTH)
		.def_readonly("BOND_LINE_SPACING", &Vis::MolecularGraphPropertyDefault::BOND_LINE_SPACING)
		.def_readonly("STEREO_BOND_WEDGE_WIDTH", &Vis::MolecularGraphPropertyDefault::STEREO_BOND_WEDGE_WIDTH)
		.def_readonly("STEREO_BOND_HASH_SPACING", &Vis::MolecularGraphPropertyDefault::STEREO_BOND_HASH_SPACING)
		.def_readonly("REACTION_CENTER_LINE_LENGTH", &Vis::MolecularGraphPropertyDefault::REACTION_CENTER_LINE_LENGTH)
		.def_readonly("REACTION_CENTER_LINE_SPACING", &Vis::MolecularGraphPropertyDefault::REACTION_CENTER_LINE_SPACING)
		.def_readonly("DOUBLE_BOND_TRIM_LENGTH", &Vis::MolecularGraphPropertyDefault::DOUBLE_BOND_TRIM_LENGTH)
		.def_readonly("TRIPLE_BOND_TRIM_LENGTH", &Vis::MolecularGraphPropertyDefault::TRIPLE_BOND_TRIM_LENGTH)
		.def_readonly("BOND_LABEL_FONT", &Vis::MolecularGraphPropertyDefault::BOND_LABEL_FONT)
		.def_readonly("BOND_LABEL_SIZE", &Vis::MolecularGraphPropertyDefault::BOND_LABEL_SIZE)
		.def_readonly("BOND_LABEL_MARGIN", &Vis::MolecularGraphPropertyDefault::BOND_LABEL_MARGIN);
}
