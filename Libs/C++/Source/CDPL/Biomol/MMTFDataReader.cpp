/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMTFDataReader.cpp 
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

#include <istream>
#include <functional>
#include <algorithm>

#include <boost/lexical_cast.hpp>

#include "CDPL/Biomol/AtomFunctions.hpp"
#include "CDPL/Biomol/MolecularGraphFunctions.hpp"
#include "CDPL/Biomol/ControlParameterFunctions.hpp"
#include "CDPL/Biomol/ControlParameterDefault.hpp"
#include "CDPL/Biomol/PDBData.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Math/Vector.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Base/DataIOBase.hpp"

#include "MMTFDataReader.hpp"


using namespace CDPL;


namespace
{

	const std::size_t DATA_BLOCK_SIZE = 1024 * 4;

	struct ResidueAtomCmpFunc : public std::binary_function<const Chem::Atom*, const Chem::Atom*, bool>
	{

		bool operator()(const Chem::Atom* atom1, const Chem::Atom* atom2) const {
			using namespace Biomol;

			const std::string& res_atom_name1 = getResidueAtomName(*atom1);
			const std::string& res_atom_name2 = getResidueAtomName(*atom2);

			if (res_atom_name1 == res_atom_name2)
				return (getAltLocationID(*atom1) < getAltLocationID(*atom2));
	
			return (res_atom_name1 < res_atom_name2);
		}
	};
}


bool Biomol::MMTFDataReader::readRecord(std::istream& is, Chem::Molecule& mol)
{
	msgpack::object_handle handle;

	if (!readRecordData(is, handle))
		return false;

	mmtf::StructureData struct_data;
	
	handle.get().convert(struct_data);
	
	if (getStrictErrorCheckingParameter(ioBase) && !struct_data.hasConsistentData(false))
		throw Base::IOError("MMTFDataReader: got inconsistent MMTF data");

	buildMolecule(mol, struct_data);

	return true;
}

bool Biomol::MMTFDataReader::skipRecord(std::istream& is)
{
	msgpack::object_handle handle;

	return readRecordData(is, handle);
}
		
bool Biomol::MMTFDataReader::hasMoreData(std::istream& is) const
{
    return !std::istream::traits_type::eq_int_type(is.peek(), std::istream::traits_type::eof());
}

bool Biomol::MMTFDataReader::readRecordData(std::istream& is, msgpack::object_handle& handle) const
{
    if (!hasMoreData(is))
		return false;

	std::istream::pos_type curr_is_pos = is.tellg();

	if (curr_is_pos < 0)
		throw Base::IOError("MMTFDataReader: could not determine input stream read position");

	msgpack::unpacker unp;

	while (true) {
		unp.reserve_buffer(DATA_BLOCK_SIZE);
	
		if (!is.read(unp.buffer(), DATA_BLOCK_SIZE)) {
			if (is.bad() || !is.eof())
				throw Base::IOError("MMTFDataReader: reading raw input data failed");
		}

		unp.buffer_consumed(is.gcount());

		bool finished = unp.parser::next();

		if (finished) {
			handle.zone().reset(unp.release_zone());
			handle.set(unp.data());

			if (!is.eof()) 
				is.seekg(curr_is_pos + std::istream::pos_type(unp.parsed_size()));
		
			return true;
		}

		if (is.eof())
			throw Base::IOError("MMTFDataReader: unexpected end of input data");
	}

	return false;
}

void Biomol::MMTFDataReader::buildMolecule(Chem::Molecule& mol, const mmtf::StructureData& struct_data)
{
	using namespace Chem;
		
	mol.reserveMemoryForAtoms(mol.getNumAtoms() + struct_data.numAtoms);
	mol.reserveMemoryForBonds(mol.getNumBonds() + struct_data.numBonds);

	PDBData::SharedPointer pdb_data;

	if (hasPDBData(mol))
		pdb_data = getPDBData(mol);

	else {
		pdb_data.reset(new PDBData());

		setPDBData(mol, pdb_data);
	}

	pdb_data->setRecord(PDBData::TITLE, struct_data.title);
	pdb_data->setRecord(PDBData::RESOLUTION, boost::lexical_cast<std::string>(struct_data.resolution));
	pdb_data->setRecord(PDBData::DEPOSITION_DATE, struct_data.depositionDate);
	pdb_data->setRecord(PDBData::STRUCTURE_ID, struct_data.structureId);

	atoms.clear();
	
	// traverse models
	for (std::size_t model_idx = 0, num_models = struct_data.numModels, chain_idx = 0, res_idx = 0, atom_idx = 0; model_idx < num_models; model_idx++) {

		// traverse model chains
		for (std::size_t model_chain_idx = 0, num_chains = struct_data.chainsPerModel[chain_idx]; model_chain_idx < num_chains; model_chain_idx++, chain_idx++) {

			// traverse chain residues
			for (std::size_t chain_res_idx = 0, num_res = struct_data.groupsPerChain[chain_idx]; chain_res_idx < num_res; chain_res_idx++, res_idx++) {
				const mmtf::GroupType& group = struct_data.groupList[struct_data.groupTypeList[res_idx]];
				std::size_t atom_idx_offs = atom_idx;

				// traverse residue atoms
				for (std::size_t res_atom_idx = 0; res_atom_idx < group.atomNameList.size(); res_atom_idx++, atom_idx++) {
					Math::Vector3D coords;

					coords(0) = struct_data.xCoordList[atom_idx];
					coords(1) = struct_data.yCoordList[atom_idx];
					coords(2) = struct_data.zCoordList[atom_idx];

					if (struct_data.altLocList[atom_idx] != ' ') {
						bool alt_loc_atom = false;
					
						for (AtomArray::reverse_iterator it = atoms.rbegin(), end = atoms.rend(); it != end; ++it) {
							Atom& atom = **it;

							if (getResidueSequenceNumber(atom) != struct_data.groupIdList[res_idx])
								break;

							if (getResidueInsertionCode(atom) != struct_data.insCodeList[res_idx])
								break;

							if (getResidueCode(atom) != group.groupName)
								break;

							if (getModelNumber(atom) != (model_idx + 1))
								break;

							if (getChainID(atom) != struct_data.chainIdList[chain_idx])
								break;

							if (getResidueAtomName(atom) != group.atomNameList[res_atom_idx])
								continue;

							Math::Vector3DArray::SharedPointer coords_array_ptr;

							if (has3DCoordinatesArray(atom))
								coords_array_ptr = get3DCoordinatesArray(atom);

							else {
								coords_array_ptr.reset(new Math::Vector3DArray());
								coords_array_ptr->addElement(get3DCoordinates(atom));

								set3DCoordinatesArray(atom, coords_array_ptr);
							}

							coords_array_ptr->addElement(coords);

							atoms.push_back(&atom);
							alt_loc_atom = true;
							break;
						}

						if (alt_loc_atom)
							continue;
					}
					
					Atom& atom = mol.addAtom();

					atoms.push_back(&atom);

					setModelNumber(atom, model_idx + 1);
					set3DCoordinates(atom, coords);
					setResidueCode(atom, group.groupName);
					setResidueSequenceNumber(atom, struct_data.groupIdList[res_idx]);
					setResidueInsertionCode(atom, struct_data.insCodeList[res_idx]);
					setChainID(atom, struct_data.chainIdList[chain_idx]);
					setBFactor(atom, struct_data.bFactorList[atom_idx]);
					setOccupancy(atom, struct_data.occupancyList[atom_idx]);
					setSerialNumber(atom, struct_data.atomIdList[atom_idx]);
					setFormalCharge(atom, group.formalChargeList[res_atom_idx]);
					setResidueAtomName(atom, group.atomNameList[res_atom_idx]);
					setSymbol(atom, group.elementList[res_atom_idx]);
					setType(atom, AtomDictionary::getType(group.elementList[res_atom_idx]));
					setAltLocationID(atom, struct_data.altLocList[atom_idx]);
				}

				// traverse residue bonds
				for (std::size_t res_bond_idx = 0, num_bonds = group.bondAtomList.size() / 2; res_bond_idx < num_bonds; res_bond_idx++) {
					std::size_t atom1_idx = mol.getAtomIndex(*atoms[atom_idx_offs + group.bondAtomList[res_bond_idx * 2]]);
					std::size_t atom2_idx = mol.getAtomIndex(*atoms[atom_idx_offs + group.bondAtomList[res_bond_idx * 2 + 1]]);

					addBond(mol, atom1_idx, atom2_idx, group.bondOrderList[res_bond_idx]);
				}
			}
		}
	}

	// traverse inter-residue bonds
	for (std::size_t i = 0, num_bonds = struct_data.bondAtomList.size() / 2; i < num_bonds; i++) {
		std::size_t atom1_idx = mol.getAtomIndex(*atoms[struct_data.bondAtomList[i * 2]]);
		std::size_t atom2_idx = mol.getAtomIndex(*atoms[struct_data.bondAtomList[i * 2 + 1]]);

		addBond(mol, atom1_idx, atom2_idx, struct_data.bondOrderList[i]);
	}
}

void Biomol::MMTFDataReader::addBond(Chem::Molecule& mol, std::size_t atom1_idx, std::size_t atom2_idx, std::size_t order) const
{
	using namespace Chem;

	if (atom1_idx == atom2_idx)
		return;
	
	setOrder(mol.addBond(atom1_idx, atom2_idx), order);
}
