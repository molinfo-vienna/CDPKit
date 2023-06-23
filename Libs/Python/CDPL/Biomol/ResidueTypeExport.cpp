/* 
 * ResidueTypeExport.cpp 
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

#include "CDPL/Biomol/ResidueType.hpp"

#include "NamespaceExports.hpp"


namespace 
{

    struct ResidueType {};
}


void CDPLPythonBiomol::exportResidueTypes()
{
    using namespace boost;
    using namespace CDPL;

    python::class_<ResidueType, boost::noncopyable>("ResidueType", python::no_init)
		.def_readonly("UNKNOWN", Biomol::ResidueType::UNKNOWN)
	    .def_readonly("OTHER", Biomol::ResidueType::OTHER)
	    .def_readonly("NON_POLYMER", Biomol::ResidueType::NON_POLYMER)
	    .def_readonly("PEPTIDE_CARBOXY_TERMINUS", Biomol::ResidueType::PEPTIDE_CARBOXY_TERMINUS)
	    .def_readonly("PEPTIDE_AMINO_TERMINUS", Biomol::ResidueType::PEPTIDE_AMINO_TERMINUS)
	    .def_readonly("PEPTIDE_LINKING", Biomol::ResidueType::PEPTIDE_LINKING)
	    .def_readonly("BETA_PEPTIDE_LINKING", Biomol::ResidueType::BETA_PEPTIDE_LINKING)
	    .def_readonly("GAMMA_PEPTIDE_LINKING", Biomol::ResidueType::GAMMA_PEPTIDE_LINKING)
	    .def_readonly("PEPTIDE_LIKE", Biomol::ResidueType::PEPTIDE_LIKE)
		.def_readonly("RNA_HYDROXY_TERMINUS", Biomol::ResidueType::RNA_HYDROXY_TERMINUS)
		.def_readonly("DNA_HYDROXY_TERMINUS", Biomol::ResidueType::DNA_HYDROXY_TERMINUS)
		.def_readonly("RNA_LINKING", Biomol::ResidueType::RNA_LINKING)
	    .def_readonly("DNA_LINKING", Biomol::ResidueType::DNA_LINKING)
	    .def_readonly("SACCHARIDE_LINKING", Biomol::ResidueType::SACCHARIDE_LINKING)
	    .def_readonly("SACCHARIDE", Biomol::ResidueType::SACCHARIDE);
}
