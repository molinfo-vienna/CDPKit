/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * InteractionTypeExport.cpp 
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

#include "CDPL/ForceField/InteractionType.hpp"

#include "NamespaceExports.hpp"


namespace 
{

	struct InteractionType {};
}


void CDPLPythonForceField::exportInteractionTypes()
{
	using namespace boost;
	using namespace CDPL;

	python::class_<InteractionType, boost::noncopyable>("InteractionType", python::no_init)
		.def_readonly("NONE", &ForceField::InteractionType::NONE)
		.def_readonly("BOND_STRETCHING", &ForceField::InteractionType::BOND_STRETCHING)
		.def_readonly("ANGLE_BENDING", &ForceField::InteractionType::ANGLE_BENDING)
		.def_readonly("STRETCH_BEND", &ForceField::InteractionType::STRETCH_BEND)
		.def_readonly("OUT_OF_PLANE_BENDING", &ForceField::InteractionType::OUT_OF_PLANE_BENDING)
		.def_readonly("TORSION", &ForceField::InteractionType::TORSION)
		.def_readonly("VAN_DER_WAALS", &ForceField::InteractionType::VAN_DER_WAALS)
		.def_readonly("ELECTROSTATIC", &ForceField::InteractionType::ELECTROSTATIC)
		.def_readonly("ALL", &ForceField::InteractionType::ALL);
}
