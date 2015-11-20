/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MoleculeFunctionExport.cpp 
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

#include "CDPL/Chem/MoleculeFunctions.hpp"
#include "CDPL/Chem/Molecule.hpp"

#include "FunctionExports.hpp"
#include "FunctionWrapper.hpp"


namespace
{

	MAKE_FUNCTION_WRAPPER3(void, replaceAtomStereoReferenceAtoms, CDPL::Chem::Molecule&, CDPL::Chem::MolecularGraph&, std::size_t)
	MAKE_FUNCTION_WRAPPER4(void, replaceBondStereoReferenceAtoms, CDPL::Chem::Molecule&, CDPL::Chem::MolecularGraph&, std::size_t, std::size_t)
}

void CDPLPythonChem::exportMoleculeFunctions()
{
	using namespace boost;
	using namespace CDPL;

	python::def("replaceAtomStereoReferenceAtoms", &replaceAtomStereoReferenceAtomsWrapper3,
				(python::arg("mol_copy"), python::arg("molgraph"), python::arg("atom_idx_offs") = 0));
	python::def("replaceBondStereoReferenceAtoms", &replaceBondStereoReferenceAtomsWrapper4,
				(python::arg("mol_copy"), python::arg("molgraph"), python::arg("atom_idx_offs") = 0, 
				 python::arg("bond_start_idx") = 0));
	python::def("makeHydrogenDeplete", &Chem::makeHydrogenDeplete, python::arg("mol"));
	python::def("makeOrdinaryHydrogenDeplete", &Chem::makeOrdinaryHydrogenDeplete, 
				(python::arg("mol"), python::arg("flags")));
	python::def("makeHydrogenComplete", &Chem::makeHydrogenComplete, python::arg("mol"));
}
