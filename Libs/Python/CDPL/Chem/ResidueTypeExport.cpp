/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * ResidueTypeExport.cpp 
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

#include "CDPL/Chem/ResidueType.hpp"

#include "NamespaceExports.hpp"


namespace 
{

    struct ResidueType {};
}


void CDPLPythonChem::exportResidueTypes()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<ResidueType, boost::noncopyable>("ResidueType", python::no_init)
		.def_readonly("UNKNOWN", Chem::ResidueType::UNKNOWN)
	    .def_readonly("OTHER", Chem::ResidueType::OTHER)
	    .def_readonly("NON_POLYMER", Chem::ResidueType::NON_POLYMER)
	    .def_readonly("PEPTIDE_CARBOXY_TERMINUS", Chem::ResidueType::PEPTIDE_CARBOXY_TERMINUS)
	    .def_readonly("PEPTIDE_AMINO_TERMINUS", Chem::ResidueType::PEPTIDE_AMINO_TERMINUS)
	    .def_readonly("PEPTIDE_LINKING", Chem::ResidueType::PEPTIDE_LINKING)
	    .def_readonly("BETA_PEPTIDE_LINKING", Chem::ResidueType::BETA_PEPTIDE_LINKING)
	    .def_readonly("GAMMA_PEPTIDE_LINKING", Chem::ResidueType::GAMMA_PEPTIDE_LINKING)
	    .def_readonly("PEPTIDE_LIKE", Chem::ResidueType::PEPTIDE_LIKE)
		.def_readonly("RNA_HYDROXY_TERMINUS", Chem::ResidueType::RNA_HYDROXY_TERMINUS)
		.def_readonly("DNA_HYDROXY_TERMINUS", Chem::ResidueType::DNA_HYDROXY_TERMINUS)
		.def_readonly("RNA_LINKING", Chem::ResidueType::RNA_LINKING)
	    .def_readonly("DNA_LINKING", Chem::ResidueType::DNA_LINKING)
	    .def_readonly("SACCHARIDE_LINKING", Chem::ResidueType::SACCHARIDE_LINKING)
	    .def_readonly("SACCHARIDE", Chem::ResidueType::SACCHARIDE);
}
