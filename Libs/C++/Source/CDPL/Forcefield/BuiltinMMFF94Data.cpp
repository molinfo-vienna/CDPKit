/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * BuiltinMMFF94Data.cpp 
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

 
#include "StaticInit.hpp"

#include "BuiltinMMFF94Data.hpp"


using namespace CDPL;
using namespace Forcefield;


const char* BuiltinMMFF94Data::ANGLE_BENDING_PARAMETERS =                 
	#include "Forcefield/MMFFANG.PAR"
const char* BuiltinMMFF94Data::BOND_STRETCHING_PARAMETERS =               
	#include "Forcefield/MMFFBOND.PAR"
const char* BuiltinMMFF94Data::BOND_STRETCHING_EMP_RULE_PARAMETERS =      
	#include "Forcefield/MMFFBNDK.PAR"
const char* BuiltinMMFF94Data::STRETCH_BEND_PARAMETERS =                  
	#include "Forcefield/MMFFSTBN.PAR"
const char* BuiltinMMFF94Data::DEFAULT_STRETCH_BEND_PARAMETERS =          
	#include "Forcefield/MMFFDFSB.PAR"
const char* BuiltinMMFF94Data::OUT_OF_PLANE_BENDING_PARAMETERS =    
	#include "Forcefield/MMFFOOP.PAR"
const char* BuiltinMMFF94Data::STATIC_OUT_OF_PLANE_BENDING_PARAMETERS =   
	#include "Forcefield/MMFFSOOP.PAR"
const char* BuiltinMMFF94Data::TORSION_PARAMETERS =  
	#include "Forcefield/MMFFTOR.PAR"
const char* BuiltinMMFF94Data::STATIC_TORSION_PARAMETERS =              
	#include "Forcefield/MMFFSTOR.PAR"
const char* BuiltinMMFF94Data::VAN_DER_WAALS_PARAMETERS = 
	#include "Forcefield/MMFFVDW.PAR"

const char* BuiltinMMFF94Data::SYMBOLIC_ATOM_TYPE_PATTERNS =  
	#include "Forcefield/MMFFSMTP.PAR"
const char* BuiltinMMFF94Data::AROMATIC_ATOM_TYPE_DEFINITIONS =        
	#include "Forcefield/MMFFAROM.PAR"
const char* BuiltinMMFF94Data::HYDROGEN_ATOM_TYPE_DEFINITIONS =       
	#include "Forcefield/MMFFHDEF.PAR"
const char* BuiltinMMFF94Data::SYMBOLIC_TO_NUMERIC_ATOM_TYPE_MAPPING =   
	#include "Forcefield/MMFFSYMB.PAR"
const char* BuiltinMMFF94Data::NUMERIC_TO_PARAMETER_ATOM_TYPE_MAPPING =   
	#include "Forcefield/MMFFDEF.PAR"

const char* BuiltinMMFF94Data::BOND_CHARGE_INCREMENT_PARAMETERS =        
	#include "Forcefield/MMFFCHG.PAR"
const char* BuiltinMMFF94Data::PARTIAL_BOND_CHARGE_INCREMENT_PARAMETERS = 
	#include "Forcefield/MMFFPBCI.PAR"
