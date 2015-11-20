/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ResidueComponentTypeExport.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2010 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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

#include "CDPL/Chem/ResidueComponentType.hpp"

#include "NamespaceExports.hpp"


namespace 
{

    struct ResidueComponentType {};
}


void CDPLPythonChem::exportResidueComponentTypes()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<ResidueComponentType, boost::noncopyable>("ResidueComponentType", python::no_init)
		.def_readonly("UNKNOWN", Chem::ResidueComponentType::UNKNOWN)
	    .def_readonly("OTHER", Chem::ResidueComponentType::OTHER)
	    .def_readonly("NON_POLYMER", Chem::ResidueComponentType::NON_POLYMER)
	    .def_readonly("PEPTIDE_CARBOXY_TERMINUS", Chem::ResidueComponentType::PEPTIDE_CARBOXY_TERMINUS)
	    .def_readonly("PEPTIDE_AMINO_TERMINUS", Chem::ResidueComponentType::PEPTIDE_AMINO_TERMINUS)
	    .def_readonly("PEPTIDE_LINKING", Chem::ResidueComponentType::PEPTIDE_LINKING)
	    .def_readonly("BETA_PEPTIDE_LINKING", Chem::ResidueComponentType::BETA_PEPTIDE_LINKING)
	    .def_readonly("GAMMA_PEPTIDE_LINKING", Chem::ResidueComponentType::GAMMA_PEPTIDE_LINKING)
	    .def_readonly("PEPTIDE_LIKE", Chem::ResidueComponentType::PEPTIDE_LIKE)
		.def_readonly("RNA_HYDROXY_TERMINUS", Chem::ResidueComponentType::RNA_HYDROXY_TERMINUS)
		.def_readonly("DNA_HYDROXY_TERMINUS", Chem::ResidueComponentType::DNA_HYDROXY_TERMINUS)
		.def_readonly("RNA_LINKING", Chem::ResidueComponentType::RNA_LINKING)
	    .def_readonly("DNA_LINKING", Chem::ResidueComponentType::DNA_LINKING)
	    .def_readonly("SACCHARIDE_LINKING", Chem::ResidueComponentType::SACCHARIDE_LINKING)
	    .def_readonly("SACCHARIDE", Chem::ResidueComponentType::SACCHARIDE);
}
