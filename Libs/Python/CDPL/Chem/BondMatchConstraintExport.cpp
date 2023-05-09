/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BondMatchConstraintExport.cpp 
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

#include "CDPL/Chem/BondMatchConstraint.hpp"

#include "NamespaceExports.hpp"


namespace 
{

	struct BondMatchConstraint {};
}


void CDPLPythonChem::exportBondMatchConstraints()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<BondMatchConstraint, boost::noncopyable>("BondMatchConstraint", python::no_init)
		.def_readonly("CONSTRAINT_LIST", &Chem::BondMatchConstraint::CONSTRAINT_LIST)  
		.def_readonly("ANY_ORDER", &Chem::BondMatchConstraint::ANY_ORDER)    
        .def_readonly("AROMATIC", &Chem::BondMatchConstraint::AROMATIC)    
        .def_readonly("AROMATICITY", &Chem::BondMatchConstraint::AROMATICITY)    
        .def_readonly("DIRECTION", &Chem::BondMatchConstraint::DIRECTION)    
        .def_readonly("DIRECTION_CONFIG", &Chem::BondMatchConstraint::DIRECTION_CONFIG)    
        .def_readonly("DOUBLE", &Chem::BondMatchConstraint::DOUBLE)    
        .def_readonly("CONFIGURATION", &Chem::BondMatchConstraint::CONFIGURATION)    
        .def_readonly("IGNORE_AROMATICITY", &Chem::BondMatchConstraint::IGNORE_AROMATICITY)    
        .def_readonly("ORDER", &Chem::BondMatchConstraint::ORDER)    
        .def_readonly("REACTION_CENTER_STATUS", &Chem::BondMatchConstraint::REACTION_CENTER_STATUS)    
        .def_readonly("RING_TOPOLOGY", &Chem::BondMatchConstraint::RING_TOPOLOGY)    
        .def_readonly("SINGLE", &Chem::BondMatchConstraint::SINGLE)    
        .def_readonly("TRIPLE", &Chem::BondMatchConstraint::TRIPLE);
}
