/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomTypeMatchExpression.cpp
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

#include "CDPL/Chem/AtomTypeMatchExpression.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomTypeFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"


using namespace CDPL;


Chem::AtomTypeMatchExpression::AtomTypeMatchExpression(unsigned int atom_type, bool not_match): 
	atomType(atom_type), notMatch(not_match) {}

bool Chem::AtomTypeMatchExpression::operator()(const Atom&, const MolecularGraph&, 
											   const Atom& target_atom, const MolecularGraph&, 
											   const Base::Variant&) const
{
	unsigned int target_atom_type = getType(target_atom);

	if (atomType != AtomType::UNKNOWN && atomType <= AtomType::MAX_ATOMIC_NO)   
		return (notMatch ? atomType != target_atom_type : atomType == target_atom_type);

	switch (atomType) {

		case AtomType::ANY:
		case AtomType::AH:
			return !notMatch;

		case AtomType::A:
			return (notMatch ? target_atom_type == AtomType::H : target_atom_type != AtomType::H);
			
		case AtomType::Q:
			return (notMatch ? target_atom_type == AtomType::H || target_atom_type == AtomType::C
					: target_atom_type != AtomType::H && target_atom_type != AtomType::C);

		case AtomType::QH:
			return (notMatch ? target_atom_type == AtomType::C : target_atom_type != AtomType::C);

		case AtomType::M:
			return (notMatch ? !isMetal(target_atom_type) : isMetal(target_atom_type));

		case AtomType::MH:
			return (notMatch ? target_atom_type != AtomType::H && !isMetal(target_atom_type) 
					: target_atom_type == AtomType::H || isMetal(target_atom_type));

		case AtomType::X:
			return (notMatch ? !isHalogen(target_atom_type) : isHalogen(target_atom_type));

		case AtomType::XH:
			return (notMatch ? target_atom_type != AtomType::H && !isHalogen(target_atom_type)
					: target_atom_type == AtomType::H || isHalogen(target_atom_type));
		default:
			return true;
	}
}
