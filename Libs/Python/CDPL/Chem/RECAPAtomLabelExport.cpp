/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * RECAPAtomLabelExport.cpp 
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

#include "CDPL/Chem/RECAPAtomLabel.hpp"

#include "NamespaceExports.hpp"


namespace 
{

	struct RECAPAtomLabel {};
}


void CDPLPythonChem::exportRECAPAtomLabels()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<RECAPAtomLabel, boost::noncopyable>("RECAPAtomLabel", python::no_init)
		.def_readonly("NONE", &Chem::RECAPAtomLabel::NONE)
		.def_readonly("AMIDE_N", &Chem::RECAPAtomLabel::AMIDE_N)
		.def_readonly("AMIDE_C", &Chem::RECAPAtomLabel::AMIDE_C)
		.def_readonly("ESTER_O", &Chem::RECAPAtomLabel::ESTER_O)
		.def_readonly("ESTER_C", &Chem::RECAPAtomLabel::ESTER_C)
		.def_readonly("AMINE_N", &Chem::RECAPAtomLabel::AMINE_N)
		.def_readonly("AMINE_C", &Chem::RECAPAtomLabel::AMINE_C)
		.def_readonly("UREA_N", &Chem::RECAPAtomLabel::UREA_N)
		.def_readonly("UREA_C", &Chem::RECAPAtomLabel::UREA_C)
		.def_readonly("ETHER_O", &Chem::RECAPAtomLabel::ETHER_O)
		.def_readonly("ETHER_C", &Chem::RECAPAtomLabel::ETHER_C)
		.def_readonly("OLEFIN_C", &Chem::RECAPAtomLabel::OLEFIN_C)
		.def_readonly("QUARTERNARY_N_N", &Chem::RECAPAtomLabel::QUARTERNARY_N_N)
		.def_readonly("QUARTERNARY_N_C", &Chem::RECAPAtomLabel::QUARTERNARY_N_C)
		.def_readonly("AROMATIC_N_ALIPHATIC_C_N", &Chem::RECAPAtomLabel::AROMATIC_N_ALIPHATIC_C_N)
		.def_readonly("AROMATIC_N_ALIPHATIC_C_C", &Chem::RECAPAtomLabel::AROMATIC_N_ALIPHATIC_C_C)
		.def_readonly("LACTAM_N_ALIPHATIC_C_N", &Chem::RECAPAtomLabel::LACTAM_N_ALIPHATIC_C_N)
		.def_readonly("LACTAM_N_ALIPHATIC_C_C", &Chem::RECAPAtomLabel::LACTAM_N_ALIPHATIC_C_C)
		.def_readonly("AROMATIC_C_AROMATIC_C_C", &Chem::RECAPAtomLabel::AROMATIC_C_AROMATIC_C_C)
		.def_readonly("SULFONAMIDE_N", &Chem::RECAPAtomLabel::SULFONAMIDE_N)
		.def_readonly("SULFONAMIDE_S", &Chem::RECAPAtomLabel::SULFONAMIDE_S);
}
