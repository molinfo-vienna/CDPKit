/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * AtomContainerAtomTypeMaskFunction.cpp 
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

#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"


using namespace CDPL; 


std::size_t Chem::buildAtomTypeMask(const Chem::AtomContainer& cntnr, Util::BitSet& mask, unsigned int type, bool reset)
{
	std::size_t num_atoms = cntnr.getNumAtoms();

	if (reset)
		mask.reset();

	if (mask.size() < num_atoms)
		mask.resize(num_atoms);

	std::size_t num_bits = 0;

	for (std::size_t i = 0; i < num_atoms; i++) {
		const Atom& atom = cntnr.getAtom(i);
		
		if (getType(atom) == type) {
			mask.set(i);
			num_bits++;
		}
	}

	return num_bits;
}
