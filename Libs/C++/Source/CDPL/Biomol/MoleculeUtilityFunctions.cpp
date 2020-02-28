
/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MoleculeUtilityFunctions.cpp 
 *
 * This file is part of the Chemical Data Processing Toolkit
 *
 * Copyright (C) 2003-2020 Thomas A. Seidel <thomas.seidel@univie.ac.at>
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
#include <limits>

#include "CDPL/Biomol/MoleculeFunctions.hpp"
#include "CDPL/Biomol/AtomFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Math/VectorArray.hpp"
#include "CDPL/Internal/AddressOf.hpp"


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
 
	    const std::string& chain_id1 = getChainID(*atom1);
	    const std::string& chain_id2 = getChainID(*atom2);

	    if (chain_id1 < chain_id2)
		return true;

	    if (chain_id1 > chain_id2)
		return false;

	    long res_seq_no1 = getResidueSequenceNumber(*atom1);
	    long res_seq_no2 = getResidueSequenceNumber(*atom2);

	    if (res_seq_no1 < res_seq_no2)
		return true;

	    if (res_seq_no1 > res_seq_no2)
		return false;

	    char ins_code1 = getResidueInsertionCode(*atom1);
	    char ins_code2 = getResidueInsertionCode(*atom2);

	    if (ins_code1 < ins_code2)
		return true;

	    if (ins_code1 > ins_code2)
		return false;

	    const std::string& res_atom_name1 = getResidueAtomName(*atom1);
	    const std::string& res_atom_name2 = getResidueAtomName(*atom2);

	    return (res_atom_name1 < res_atom_name2);
	}
    };

    typedef std::vector<Math::Vector3DArray::SharedPointer> ConfArray;
    typedef std::vector<Chem::Atom*> AtomArray;
    typedef std::vector<std::size_t> SizeTArray;


    bool fetchCoordinates(AtomArray& atoms, std::size_t start_idx, std::size_t num_atoms, ConfArray& confs)
    {
	using namespace Chem;

	if (confs.size() < num_atoms + 1)
	    confs.resize(num_atoms + 1);

	for (std::size_t i = 0; i <= num_atoms; i++) {
	    if (!confs[i])
		confs[i].reset(new Math::Vector3DArray());

	    if (i == num_atoms) 
		return true;

	    Atom* atom = atoms[i + start_idx];

	    if (has3DCoordinatesArray(*atom) && get3DCoordinatesArray(*atom)->getSize() > 1)
		return false;

	    confs[i]->clear();	    
	    confs[i]->addElement(get3DCoordinates(*atom));
	}

	return true;
    }
 
    bool fetchCoordinates(AtomArray& atoms, std::size_t start_idx, std::size_t num_atoms, Math::Vector3DArray& coords)
    {
	using namespace Chem;

	if (coords.size() < num_atoms)
	    coords.resize(num_atoms);

	for (std::size_t i = 0; i < num_atoms; i++) {
	    Atom* atom = atoms[i + start_idx];

	    if (has3DCoordinatesArray(*atom) && get3DCoordinatesArray(*atom)->getSize() > 1)
		return false;

	    coords[i].assign(get3DCoordinates(*atom));
	}

	return true;
    }

    double calcMinCtrDist(ConfArray& confs, Math::Vector3DArray& coords, std::size_t num_atoms, std::size_t num_confs) 
    {
	Math::Vector3D ctr1;

	for (std::size_t j = 0; j < num_atoms; j++) 
	    ctr1.plusAssign(coords[j]);

	ctr1 /= num_atoms;

	Math::Vector3D ctr2;
	double min_dist = std::numeric_limits<double>::max();

	for (std::size_t i = 0; i < num_confs; i++) {
	    ctr2.clear();

	    for (std::size_t j = 0; j < num_atoms; j++) 
		ctr2.plusAssign((*confs[j])[i]);

	    ctr2 /= num_atoms;

	    double dist = length(ctr1 - ctr2);

	    if (dist < min_dist)
		min_dist = dist;
	}

	return min_dist;
    }

    bool processResidueSequence(Chem::Molecule& mol, AtomArray& atoms, SizeTArray& res_bounds, ConfArray& confs, double max_ctr_dist) 
    {
	using namespace Biomol;

	bool changes = false;

	for (std::size_t i = 0, end = res_bounds.size(); i < end; i += 2) {
	    std::size_t num_atoms = res_bounds[i + 1] - res_bounds[i];

	    if (num_atoms == 0)
		continue;

	    if (!fetchCoordinates(atoms, res_bounds[i], num_atoms, confs))
		continue;

	    std::size_t num_confs = 1;

	    for (std::size_t j = i + 2; j < end; j+= 2) {
		if ((res_bounds[j + 1] - res_bounds[j]) != num_atoms)
		    continue;

		if (!fetchCoordinates(atoms, res_bounds[j], num_atoms, *confs[num_atoms]))
		    continue;

		bool same_atom_seq = true;

		for (std::size_t k = 0; k < num_atoms; k++)
		    if (getResidueAtomName(*atoms[res_bounds[i] + k]) != getResidueAtomName(*atoms[res_bounds[j] + k])) {
			same_atom_seq = false;
			break;
		    }
		    
		if (!same_atom_seq) 
		    continue;
		    
		double min_ctr_dist = calcMinCtrDist(confs, *confs[num_atoms], num_atoms, num_confs);

		if (min_ctr_dist <= max_ctr_dist) {
		    for (std::size_t k = 0; k < num_atoms; k++) {
			confs[k]->addElement((*confs[num_atoms])[k]);

			mol.removeAtom(mol.getAtomIndex(*atoms[res_bounds[j] + k]));
		    }
		    
		    res_bounds[j + 1] = res_bounds[j];
		    num_confs++;

		    changes = true;
		} 
	    }

	    if (num_confs > 1) {
		for (std::size_t j = 0; j < num_atoms; j++)
		    set3DCoordinatesArray(*atoms[res_bounds[i] + j], Math::Vector3DArray::SharedPointer(new Math::Vector3DArray(*confs[j])));
	    }
	}

	return changes;
    }

    bool isWaterOxygen(const Chem::Atom& atom) 
    {
	using namespace Chem;

	if (getType(atom) != AtomType::O) 
	    return false;

	return (getHeavyAtomCount(atom) == 0);
    }
}

	
bool Biomol::combineInterferingResidueCoordinates(Chem::Molecule& mol, double max_ctr_dist)
{
    using namespace Chem;

    if (mol.getNumAtoms() == 0)
	return false;

    AtomArray atoms;
    SizeTArray res_bounds;
    ConfArray confs;

    for (Molecule::AtomIterator it = mol.getAtomsBegin(), end = mol.getAtomsEnd(); it != end; ++it) {
	Atom& atom = *it;

	if (atom.getNumBonds() == 0)
	    continue;

	if (isWaterOxygen(atom) || isWaterOxygen(atom.getAtom(0)))
	    continue;

	atoms.push_back(&atom);
    }

    std::sort(atoms.begin(), atoms.end(), AtomLessCompareFunc());

    std::size_t num_atoms = atoms.size();
    bool changes = false;

    Atom* atom = atoms.front();

    std::size_t model_no = getModelNumber(*atom);
    std::string res_code = getResidueCode(*atom);
    long res_seq_no = getResidueSequenceNumber(*atom);
    std::string chain_id = getChainID(*atom);
    char ins_code = getResidueInsertionCode(*atom);

    res_bounds.push_back(0);

    for (std::size_t i = 1; i < num_atoms; i++) {
	atom = atoms[i];

	std::size_t curr_model_no = getModelNumber(*atom);
	const std::string& curr_res_code = getResidueCode(*atom);
	long curr_res_seq_no = getResidueSequenceNumber(*atom);
	const std::string& curr_chain_id = getChainID(*atom);
	char curr_ins_code = getResidueInsertionCode(*atom);

	bool res_code_change = (curr_res_code != res_code);
	bool chain_id_change = (curr_chain_id != chain_id);

	if (res_code_change || chain_id_change || curr_model_no != model_no || curr_res_seq_no != res_seq_no || curr_ins_code != ins_code) {
	    res_bounds.push_back(i);

	    if (res_code_change || curr_model_no != model_no) {
		changes |= processResidueSequence(mol, atoms, res_bounds, confs, max_ctr_dist);

		model_no = curr_model_no;

		if (res_code_change)
		    res_code = curr_res_code;

		res_bounds.clear();
	    }

	    if (chain_id_change)
		chain_id = curr_chain_id;

	    res_seq_no = curr_res_seq_no;
	    ins_code = curr_ins_code;

	    res_bounds.push_back(i);
	} 
    }

    if (!res_bounds.empty()) {
	res_bounds.push_back(num_atoms);

	changes |= processResidueSequence(mol, atoms, res_bounds, confs, max_ctr_dist);
    }
    
    return changes;
}
