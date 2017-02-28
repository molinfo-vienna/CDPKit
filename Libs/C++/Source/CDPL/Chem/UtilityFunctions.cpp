/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * UtilityFunctions.cpp 
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

#include <sstream>

#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/SMARTSMoleculeReader.hpp"
#include "CDPL/Chem/SMILESMoleculeReader.hpp"


using namespace CDPL; 


void Chem::foldBitSet(Util::BitSet& bs, std::size_t num_times)
{
	Util::BitSet tmp;

	for (std::size_t i = 0, new_num_bits = bs.size() >> 1; i < num_times; i++, new_num_bits >>= 1) {
		tmp = bs;
		tmp >>= new_num_bits;
		
		bs |= tmp;
		bs.resize(new_num_bits);
	}
}

Chem::Molecule::SharedPointer Chem::parseSMARTS(const std::string& smarts, bool init_qry)
{
	Molecule::SharedPointer mol_ptr(new BasicMolecule());

	parseSMARTS(smarts, *mol_ptr, init_qry);
	
	return mol_ptr;
}

bool Chem::parseSMARTS(const std::string& smarts, Molecule& mol, bool init_qry)
{
	std::istringstream iss(smarts);

	if (SMARTSMoleculeReader(iss).read(mol)) {
		if (init_qry)
			initSubstructureSearchQuery(mol, true);
		return true;
	}

	return false;
}

Chem::Molecule::SharedPointer Chem::parseSMILES(const std::string& smiles)
{
	Molecule::SharedPointer mol_ptr(new BasicMolecule());

	parseSMILES(smiles, *mol_ptr);

	return mol_ptr;
}

bool Chem::parseSMILES(const std::string& smiles, Molecule& mol)
{
	std::istringstream iss(smiles);

	if (SMILESMoleculeReader(iss).read(mol))
		return true;

	return false;
}

