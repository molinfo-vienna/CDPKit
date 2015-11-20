/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomTypeFunctionExport.cpp 
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

#include "CDPL/Chem/AtomTypeFunctions.hpp"

#include "FunctionExports.hpp"


namespace
{

    boost::python::object getValenceStates(unsigned int type)
    {
	using namespace boost;

	const int* val_states = CDPL::Chem::getValenceStates(type);
	python::list val_state_list;

	while (*val_states >= 0)
	    val_state_list.append(*val_states++);

	return val_state_list;
    }
}


void CDPLPythonChem::exportAtomTypeFunctions()
{
    using namespace boost;
    using namespace CDPL;

    python::def("getAtomTypeSymbol", &Chem::getAtomTypeSymbol, (python::arg("type"), python::arg("isotope") = 0),
				python::return_value_policy<python::copy_const_reference>());
    python::def("getElementName", &Chem::getElementName, (python::arg("type"), python::arg("isotope") = 0),
				python::return_value_policy<python::copy_const_reference>());
    python::def("getAtomType", &Chem::getAtomType, python::arg("symbol"));
    python::def("getMostAbundantIsotope", &Chem::getMostAbundantIsotope, python::arg("type"));
    python::def("getIUPACGroup", &Chem::getIUPACGroup, python::arg("type"));
    python::def("getNumValenceElectrons", &Chem::getNumValenceElectrons, python::arg("type"));
    python::def("getAtomicWeight", &Chem::getAtomicWeight, (python::arg("type"), python::arg("isotope") = 0));
    python::def("getVdWRadius", &Chem::getVdWRadius, python::arg("type"));
    python::def("getCovalentRadius", &Chem::getCovalentRadius, (python::arg("type"), python::arg("order") = 1));
    python::def("getAllredRochowElectronegativity", &Chem::getAllredRochowElectronegativity, python::arg("type"));
    python::def("getValenceStates", &getValenceStates, python::arg("type"));
    python::def("isChemicalElement", &Chem::isChemicalElement, python::arg("type"));
    python::def("isMainGroupElement", &Chem::isMainGroupElement, python::arg("type"));
    python::def("isTransitionMetal", &Chem::isTransitionMetal, python::arg("type"));
    python::def("isMetal", &Chem::isMetal, python::arg("type"));
    python::def("isSemiMetal", &Chem::isSemiMetal, python::arg("type"));
    python::def("isNonMetal", &Chem::isNonMetal, python::arg("type"));
    python::def("isHalogen", &Chem::isHalogen, python::arg("type"));
    python::def("isNobleGas", &Chem::isNobleGas, python::arg("type"));
}
