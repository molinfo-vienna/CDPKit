/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomMatchConstraintExport.cpp 
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

#include "CDPL/Chem/AtomMatchConstraint.hpp"

#include "NamespaceExports.hpp"


namespace 
{

	struct AtomMatchConstraint {};
}


void CDPLPythonChem::exportAtomMatchConstraints()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<AtomMatchConstraint, boost::noncopyable>("AtomMatchConstraint", python::no_init)
		.def_readonly("CONSTRAINT_LIST", &Chem::AtomMatchConstraint::CONSTRAINT_LIST)    
		.def_readonly("AROMATICITY", &Chem::AtomMatchConstraint::AROMATICITY)    
        .def_readonly("BOND_COUNT", &Chem::AtomMatchConstraint::BOND_COUNT)    
        .def_readonly("CHARGE", &Chem::AtomMatchConstraint::CHARGE)    
        .def_readonly("ENVIRONMENT", &Chem::AtomMatchConstraint::ENVIRONMENT)    
        .def_readonly("EXPLICIT_BOND_COUNT", &Chem::AtomMatchConstraint::EXPLICIT_BOND_COUNT)    
        .def_readonly("EXPLICIT_H_COUNT", &Chem::AtomMatchConstraint::EXPLICIT_H_COUNT)    
        .def_readonly("EXPLICIT_VALENCE", &Chem::AtomMatchConstraint::EXPLICIT_VALENCE)    
        .def_readonly("HEAVY_BOND_COUNT", &Chem::AtomMatchConstraint::HEAVY_BOND_COUNT)    
        .def_readonly("H_COUNT", &Chem::AtomMatchConstraint::H_COUNT)    
        .def_readonly("IMPLICIT_H_COUNT", &Chem::AtomMatchConstraint::IMPLICIT_H_COUNT)    
        .def_readonly("ISOTOPE", &Chem::AtomMatchConstraint::ISOTOPE)    
        .def_readonly("CONFIGURATION", &Chem::AtomMatchConstraint::CONFIGURATION)    
        .def_readonly("RING_BOND_COUNT", &Chem::AtomMatchConstraint::RING_BOND_COUNT)    
        .def_readonly("RING_TOPOLOGY", &Chem::AtomMatchConstraint::RING_TOPOLOGY)    
        .def_readonly("SSSR_RING_SIZE", &Chem::AtomMatchConstraint::SSSR_RING_SIZE)    
        .def_readonly("SSSR_RING_COUNT", &Chem::AtomMatchConstraint::SSSR_RING_COUNT)    
        .def_readonly("TYPE", &Chem::AtomMatchConstraint::TYPE)    
        .def_readonly("HYBRIDIZATION_STATE", &Chem::AtomMatchConstraint::HYBRIDIZATION_STATE)    
        .def_readonly("UNSATURATION", &Chem::AtomMatchConstraint::UNSATURATION)    
        .def_readonly("VALENCE", &Chem::AtomMatchConstraint::VALENCE);
}
