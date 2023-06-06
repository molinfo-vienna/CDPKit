/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMTFDataWriter.cpp 
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


#include "StaticInit.hpp"

#include <algorithm>
#include <iterator>
#include <limits>

#include <boost/lexical_cast.hpp>

#include "CDPL/Biomol/MolecularGraphFunctions.hpp"
#include "CDPL/Biomol/AtomFunctions.hpp"
#include "CDPL/Biomol/PDBData.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Math/VectorArray.hpp"

#include "MMTFDataWriter.hpp"


using namespace CDPL;


namespace
{

    struct AtomOrderingFunc
    {

		bool operator()(const Chem::Atom* atom1, const Chem::Atom* atom2) const {
			using namespace Biomol;

			std::size_t model_no1 = getModelNumber(*atom1);
			std::size_t model_no2 = getModelNumber(*atom2);

			if (model_no1 < model_no2)
				return true;

			if (model_no1 > model_no2)
				return false;

			return (getSerialNumber(*atom1) < getSerialNumber(*atom2));
		}
    };
}

	
bool Biomol::MMTFDataWriter::writeRecord(std::ostream& os, const Chem::MolecularGraph& molgraph)
{
	init(molgraph);

	return outputStructureData(os, molgraph);
}

void Biomol::MMTFDataWriter::init(const Chem::MolecularGraph& molgraph)
{
	atoms.clear();

	std::transform(molgraph.getAtomsBegin(), molgraph.getAtomsEnd(), std::back_inserter(atoms),
				   [](const Chem::Atom& atom) { return &atom; });
	std::sort(atoms.begin(), atoms.end(), AtomOrderingFunc());

	atomIndices.assign(atoms.size(), std::numeric_limits<std::size_t>::max());
	
	resBondMask.resize(molgraph.getNumBonds());
	resBondMask.reset();
}

void Biomol::MMTFDataWriter::clearStructureData()
{
	structData.numAtoms = 0;
	structData.numBonds = 0;
	structData.numModels = 0;
	structData.numGroups = 0;

	structData.chainsPerModel.clear();
	structData.groupsPerChain.clear();
	structData.chainIdList.clear();
	structData.groupList.clear();
	structData.groupIdList.clear();
	structData.insCodeList.clear();
	structData.bondAtomList.clear();
	structData.bondOrderList.clear();
	structData.xCoordList.clear();
	structData.yCoordList.clear();
	structData.zCoordList.clear();
}

void Biomol::MMTFDataWriter::clearResidueData()
{
	residueData.singleLetterCode = 0;

	residueData.formalChargeList.clear();
    residueData.atomNameList.clear();
    residueData.elementList.clear();
    residueData.bondAtomList.clear();
    residueData.bondOrderList.clear();
    residueData.groupName.clear();
    residueData.chemCompType.clear();
}

bool Biomol::MMTFDataWriter::outputStructureData(std::ostream& os, const Chem::MolecularGraph& molgraph)
{
	encodeToStream(structData, os, 1000, 100, createStructureData(molgraph));
	
	return os.good();
}

std::size_t Biomol::MMTFDataWriter::createStructureData(const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;
	
	clearStructureData();
	setStructureMetaData(molgraph);
	
	std::size_t num_atoms = atoms.size();

	if (num_atoms == 0)
		return 0;
	
	clearResidueData();

	std::size_t num_chains_per_model = 0;
	std::size_t num_res_per_chain = 0;
	std::size_t res_start_atom_idx = 0;

	const Atom* atom = atoms.front();
	
	std::size_t model_no = getModelNumber(*atom);
    std::string res_code = getResidueCode(*atom);
    long res_seq_no = getResidueSequenceNumber(*atom);
    std::string chain_id = getChainID(*atom);
    char ins_code = getResidueInsertionCode(*atom);

	if (ins_code == ' ')
		ins_code = 0;

	std::size_t max_chain_id_len = 0;
	long atom_serial = 1;
	
    for (std::size_t i = 0; i < num_atoms; i++) {
		atom = atoms[i];

		std::size_t curr_model_no = getModelNumber(*atom);
		const std::string& curr_res_code = getResidueCode(*atom);
		long curr_res_seq_no = getResidueSequenceNumber(*atom);
		const std::string& curr_chain_id = getChainID(*atom);
		char curr_ins_code = getResidueInsertionCode(*atom);
		bool res_change = false;
		
		if (curr_ins_code == ' ')
			curr_ins_code = 0;

		if (curr_model_no != model_no) {
			structData.numModels++;
			structData.numChains++; //

			structData.chainsPerModel.push_back(num_chains_per_model + 1);
			num_chains_per_model = 0; //

			structData.groupsPerChain.push_back(num_res_per_chain + 1); //
			structData.chainIdList.push_back(chain_id); // 

			num_res_per_chain = 0; //
			res_change = true; //
		
		} else if (curr_chain_id != chain_id) {
			structData.numChains++;
			num_chains_per_model++;
			
			structData.groupsPerChain.push_back(num_res_per_chain + 1);
			structData.chainIdList.push_back(chain_id);

			num_res_per_chain = 0;
			res_change = true;
			
		} else if (curr_res_code != res_code || curr_res_seq_no != res_seq_no || curr_ins_code != ins_code) {
			num_res_per_chain++;
			res_change = true;
		}
			
		if (res_change) {
			residueData.groupName = res_code;

			structData.groupIdList.push_back(res_seq_no);
			structData.insCodeList.push_back(ins_code);

			createResidueBondData(res_start_atom_idx, i, molgraph);
			addResidueTypeIndex();
			clearResidueData();

			res_start_atom_idx = i;
		}

		atom_serial = std::max(getSerialNumber(*atom), atom_serial);

		atomIndices[molgraph.getAtomIndex(*atom)] = structData.numAtoms;

		model_no = curr_model_no;
		res_code = curr_res_code;
		res_seq_no = curr_res_seq_no;
		chain_id = curr_chain_id;
		ins_code = curr_ins_code;
			
		max_chain_id_len = std::max(std::size_t(chain_id.size()), max_chain_id_len);

		if (has3DCoordinatesArray(*atom)) {
			const Math::Vector3DArray& coords = *get3DCoordinatesArray(*atom);

			if (coords.getSize() > 1) {
				for (std::size_t j = 0; j < 26 && j < coords.getSize(); j++) {
					addAtomData(*atom, coords[j], atom_serial);

					structData.altLocList.push_back('A' + char(j));
				}

				continue;
			}
		}
		
		const Math::Vector3D& coords = get3DCoordinates(*atom);

		addAtomData(*atom, coords, atom_serial);
	
		structData.altLocList.push_back(' ');
	}

	structData.numModels++;
	structData.numChains++;

	structData.chainsPerModel.push_back(num_chains_per_model + 1);
	structData.groupsPerChain.push_back(num_res_per_chain + 1);
	structData.chainIdList.push_back(chain_id);

	residueData.groupName = res_code;

	structData.groupIdList.push_back(res_seq_no);
	structData.insCodeList.push_back(ins_code);

	createResidueBondData(res_start_atom_idx, num_atoms, molgraph);
	addResidueTypeIndex();

	createGlobalBondData(molgraph);
	
	return max_chain_id_len;
}

void Biomol::MMTFDataWriter::addAtomData(const Chem::Atom& atom, const Math::Vector3D& coords, long& atom_serial)
{
	structData.xCoordList.push_back(coords(0));
	structData.yCoordList.push_back(coords(1));
	structData.zCoordList.push_back(coords(2));

	structData.bFactorList.push_back(getBFactor(atom));
	structData.occupancyList.push_back(getOccupancy(atom));
	structData.atomIdList.push_back(atom_serial++);

	residueData.formalChargeList.push_back(getFormalCharge(atom));
	residueData.atomNameList.push_back(getResidueAtomName(atom));
	residueData.elementList.push_back(getSymbol(atom));

	structData.numAtoms++;
}

void Biomol::MMTFDataWriter::addResidueTypeIndex()
{
	structData.numGroups++;

	for (std::size_t i = 0; i < structData.groupList.size(); i++)
		if (structData.groupList[i].groupName == residueData.groupName &&
			structData.groupList[i] == residueData) {

			structData.groupTypeList.push_back(i);
			return;
		}

	structData.groupTypeList.push_back(structData.groupList.size());
	structData.groupList.push_back(residueData);
}

void Biomol::MMTFDataWriter::setStructureMetaData(const Chem::MolecularGraph& molgraph)
{
	if (!hasPDBData(molgraph))
		return;
	
	const PDBData::SharedPointer& pdb_data = getPDBData(molgraph);

	if (pdb_data->containsRecord(PDBData::TITLE))
		structData.title = pdb_data->getData(PDBData::TITLE);

	if (pdb_data->containsRecord(PDBData::RESOLUTION))
		structData.resolution = boost::lexical_cast<float>(pdb_data->getData(PDBData::RESOLUTION));

	if (pdb_data->containsRecord(PDBData::DEPOSITION_DATE))
		structData.depositionDate = pdb_data->getData(PDBData::DEPOSITION_DATE);

	if (pdb_data->containsRecord(PDBData::STRUCTURE_ID))
		structData.structureId = pdb_data->getData(PDBData::STRUCTURE_ID);
}

void Biomol::MMTFDataWriter::createGlobalBondData(const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;

	for (std::size_t i = 0, num_bonds = molgraph.getNumBonds(); i < num_bonds; i++) {
		if (resBondMask.test(i))
			continue;

		const Bond& bond = molgraph.getBond(i);
		const Atom& atom1 = bond.getBegin();
	
		if (!molgraph.containsAtom(atom1))
			continue;

		const Atom& atom2 = bond.getEnd();

		if (!molgraph.containsAtom(atom2))
			continue;

		std::size_t atom1_idx = atomIndices[molgraph.getAtomIndex(atom1)];
		std::size_t atom2_idx = atomIndices[molgraph.getAtomIndex(atom2)];

		structData.bondAtomList.push_back(atom1_idx);
		structData.bondAtomList.push_back(atom2_idx);
		structData.bondOrderList.push_back(getOrder(bond));
		structData.numBonds++;
	}	
}

void Biomol::MMTFDataWriter::createResidueBondData(std::size_t start_atom_idx, std::size_t end_atom_idx, const Chem::MolecularGraph& molgraph)
{
	using namespace Chem;

	std::size_t atom_idx_offs = atomIndices[molgraph.getAtomIndex(*atoms[start_atom_idx])];

	for (std::size_t i = start_atom_idx; i < end_atom_idx; i++) {
		const Atom* atom = atoms[i];

		Atom::ConstAtomIterator a_it = atom->getAtomsBegin();
		std::size_t res_ctr_atom_idx = atomIndices[molgraph.getAtomIndex(*atom)] - atom_idx_offs;

		for (Atom::ConstBondIterator b_it = atom->getBondsBegin(), b_end = atom->getBondsEnd(); b_it != b_end; ++b_it, ++a_it) {
			const Bond& bond = *b_it;

			if (!molgraph.containsBond(bond))
				continue;

			std::size_t bond_idx = molgraph.getBondIndex(bond);

			if (resBondMask.test(bond_idx))
				continue;

			const Atom& nbr_atom = *a_it;

			if (!molgraph.containsAtom(nbr_atom))
				continue;

			std::size_t seq_nbr_atom_idx = atomIndices[molgraph.getAtomIndex(nbr_atom)];

			if (seq_nbr_atom_idx == std::numeric_limits<std::size_t>::max() || seq_nbr_atom_idx < atom_idx_offs)
				continue;

			residueData.bondAtomList.push_back(res_ctr_atom_idx);
			residueData.bondAtomList.push_back(seq_nbr_atom_idx - atom_idx_offs);
			residueData.bondOrderList.push_back(getOrder(bond));

			structData.numBonds++;

			resBondMask.set(bond_idx);
		}
	}
}
