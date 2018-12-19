
/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MoleculeUtilityFunctions.cpp 
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

#include <vector>
#include <algorithm>
#include <functional>
#include <iterator>
#include <cstddef>

#include <boost/bind.hpp>

#include "CDPL/Biomol/UtilityFunctions.hpp"
#include "CDPL/Biomol/AtomFunctions.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Internal/AddressOf.hpp"

#include <iostream>
using namespace CDPL; 


namespace
{

    struct AtomLessCompareFunc : public std::binary_function<const Chem::Atom*, const Chem::Atom*, bool>
    {

	bool operator()(const Chem::Atom* atom1, const Chem::Atom* atom2) const {
	    using namespace Biomol;

	    std::size_t model_no1 = getModelNumber(*atom1);
	    std::size_t model_no2 = getModelNumber(*atom2);

	    if (model_no1 < model_no2)
		return true;

	    if (model_no1 > model_no2)
		return false;
	    
	    const std::string& res_code1 = getResidueCode(*atom1);
	    const std::string& res_code2 = getResidueCode(*atom2);

	    if (res_code1 < res_code2)
		return true;

	    if (res_code1 > res_code2)
		return false;
 
	    long res_seq_no1 = getResidueSequenceNumber(*atom1);
	    long res_seq_no2 = getResidueSequenceNumber(*atom2);

	    if (res_seq_no1 < res_seq_no2)
		return true;

	    if (res_seq_no1 > res_seq_no2)
		return false;

	    const std::string& res_atom_name1 = getResidueAtomName(*atom1);
	    const std::string& res_atom_name2 = getResidueAtomName(*atom2);

	    return (res_atom_name1 < res_atom_name2);
	}
    };
}

	
bool Biomol::combineInterferingResidueCoordinates(Chem::Molecule& mol, double max_rmsd)
{
    using namespace Chem;

    std::vector<Atom*> atoms;

    std::transform(mol.getAtomsBegin(), mol.getAtomsEnd(), std::back_inserter(atoms),
		   boost::bind(Internal::AddressOf<Atom>(), _1));

    if (atoms.empty())
	return false;
    
    std::sort(atoms.begin(), atoms.end(), AtomLessCompareFunc());

    std::vector<std::size_t> res_atom_ranges;
    
    for (std::size_t i = 0, num_atoms = atoms.size(); i < num_atoms; ) {
	std::size_t model_no = getModelNumber(*atoms[i]);

	for ( ; i < num_atoms && getModelNumber(*atoms[i]) == model_no; ) {
	    const std::string& res_code = getResidueCode(*atoms[i]);
	
	    res_atom_ranges.clear();

	    //std::cerr << "------------------------" << std::endl;
	    
	    for ( ; i < num_atoms && getResidueCode(*atoms[i]) == res_code && getModelNumber(*atoms[i]) == model_no; ) {
		long res_seq_no = getResidueSequenceNumber(*atoms[i]);
	    
		res_atom_ranges.push_back(i);

		//std::cerr << i << ": model_no = " << model_no << ", res_code = " << res_code << ", res_seq_no = " << res_seq_no << std::endl;
		
		for (i++; i < num_atoms && getResidueCode(*atoms[i]) == res_code && getModelNumber(*atoms[i]) == model_no &&
			 getResidueSequenceNumber(*atoms[i]) == res_seq_no; i++);

		res_atom_ranges.push_back(i);
	    }
	}
    }
    
    return false;
}
