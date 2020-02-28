/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SybylAtomTypeExport.cpp 
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

#include "CDPL/Chem/SybylAtomType.hpp"

#include "NamespaceExports.hpp"


namespace 
{

	struct SybylAtomType {};
}


void CDPLPythonChem::exportSybylAtomTypes()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<SybylAtomType, boost::noncopyable>("SybylAtomType", python::no_init)
		.def_readonly("UNKNOWN", &Chem::SybylAtomType::UNKNOWN)
		.def_readonly("C_3", &Chem::SybylAtomType::C_3)
	    .def_readonly("C_2", &Chem::SybylAtomType::C_2)
	    .def_readonly("C_1", &Chem::SybylAtomType::C_1)
	    .def_readonly("C_ar", &Chem::SybylAtomType::C_ar)
	    .def_readonly("C_cat", &Chem::SybylAtomType::C_cat)
	    .def_readonly("N_3", &Chem::SybylAtomType::N_3)
	    .def_readonly("N_2", &Chem::SybylAtomType::N_2)
		.def_readonly("N_1", &Chem::SybylAtomType::N_1)
	    .def_readonly("N_ar", &Chem::SybylAtomType::N_ar)
	    .def_readonly("N_am", &Chem::SybylAtomType::N_am)
	    .def_readonly("N_pl3", &Chem::SybylAtomType::N_pl3)
	    .def_readonly("N_4", &Chem::SybylAtomType::N_4)
	    .def_readonly("O_3", &Chem::SybylAtomType::O_3)
	    .def_readonly("O_2", &Chem::SybylAtomType::O_2)
	    .def_readonly("O_co2", &Chem::SybylAtomType::O_co2)
	    .def_readonly("O_spc", &Chem::SybylAtomType::O_spc)
	    .def_readonly("O_t3p", &Chem::SybylAtomType::O_t3p)
	    .def_readonly("S_3", &Chem::SybylAtomType::S_3)
	    .def_readonly("S_2", &Chem::SybylAtomType::S_2)
	    .def_readonly("S_O", &Chem::SybylAtomType::S_O)
	    .def_readonly("S_O2", &Chem::SybylAtomType::S_O2)
	    .def_readonly("P_3", &Chem::SybylAtomType::P_3)
	    .def_readonly("F", &Chem::SybylAtomType::F)
	    .def_readonly("H", &Chem::SybylAtomType::H)
	    .def_readonly("H_spc", &Chem::SybylAtomType::H_spc)
	    .def_readonly("H_t3p", &Chem::SybylAtomType::H_t3p)
	    .def_readonly("LP", &Chem::SybylAtomType::LP)
	    .def_readonly("Du", &Chem::SybylAtomType::Du)
	    .def_readonly("Du_C", &Chem::SybylAtomType::Du_C)
	    .def_readonly("Any", &Chem::SybylAtomType::Any)
	    .def_readonly("Hal", &Chem::SybylAtomType::Hal)
	    .def_readonly("Het", &Chem::SybylAtomType::Het)
	    .def_readonly("Hev", &Chem::SybylAtomType::Hev)
	    .def_readonly("Li", &Chem::SybylAtomType::Li)
	    .def_readonly("Na", &Chem::SybylAtomType::Na)
	    .def_readonly("Mg", &Chem::SybylAtomType::Mg)
	    .def_readonly("Al", &Chem::SybylAtomType::Al)
	    .def_readonly("Si", &Chem::SybylAtomType::Si)
	    .def_readonly("K", &Chem::SybylAtomType::K)
	    .def_readonly("Ca", &Chem::SybylAtomType::Ca)
	    .def_readonly("Cr_th", &Chem::SybylAtomType::Cr_th)
	    .def_readonly("Cr_oh", &Chem::SybylAtomType::Cr_oh)
	    .def_readonly("Mn", &Chem::SybylAtomType::Mn)
	    .def_readonly("e", &Chem::SybylAtomType::Fe)
	    .def_readonly("Co_oh", &Chem::SybylAtomType::Co_oh)
	    .def_readonly("Cu", &Chem::SybylAtomType::Cu)
	    .def_readonly("Cl", &Chem::SybylAtomType::Cl)
	    .def_readonly("Br", &Chem::SybylAtomType::Br)
	    .def_readonly("I", &Chem::SybylAtomType::I)
	    .def_readonly("Zn", &Chem::SybylAtomType::Zn)
	    .def_readonly("Se", &Chem::SybylAtomType::Se)
	    .def_readonly("Mo", &Chem::SybylAtomType::Mo)
	    .def_readonly("Sn", &Chem::SybylAtomType::Sn)
	    .def_readonly("MAX_TYPE", &Chem::SybylAtomType::MAX_TYPE);
}
