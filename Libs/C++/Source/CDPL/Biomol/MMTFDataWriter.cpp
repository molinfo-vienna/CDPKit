/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MMTFDataWriter.cpp 
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

#include <algorithm>
#include <functional>
#include <iterator>

#include <boost/lexical_cast.hpp>

#include "CDPL/Biomol/MolecularGraphFunctions.hpp"
#include "CDPL/Biomol/AtomFunctions.hpp"
#include "CDPL/Biomol/PDBData.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Internal/AddressOf.hpp"

#include "MMTFDataWriter.hpp"


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

			long serial_no1 = getSerialNumber(*atom1);
			long serial_no2 = getSerialNumber(*atom2);

			return (serial_no1 < serial_no2);
		}
    };
}

	
bool Biomol::MMTFDataWriter::writeRecord(std::ostream& os, const Chem::MolecularGraph& molgraph)
{
	init(molgraph);

	return outputStructureData(os, molgraph);
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

	std::size_t max_chain_id_len = 0;
	long atom_serial = 1;
	
    for (std::size_t i = 0; i < num_atoms; i++, atom_serial++) {
		atom = atoms[i];

		std::size_t curr_model_no = getModelNumber(*atom);
		const std::string& curr_res_code = getResidueCode(*atom);
		long curr_res_seq_no = getResidueSequenceNumber(*atom);
		const std::string& curr_chain_id = getChainID(*atom);
		char curr_ins_code = getResidueInsertionCode(*atom);
		bool res_change = false;
		
		if (curr_model_no != model_no) {
			structData.numModels++;
			
			structData.chainsPerModel.push_back(num_chains_per_model + 1);
			num_chains_per_model = 0;

			structData.groupsPerChain.push_back(num_res_per_chain + 1);
			num_res_per_chain = 0;

			res_change = true;
		
		} else if (curr_chain_id != chain_id) {
			num_chains_per_model++;
			
			structData.groupsPerChain.push_back(num_res_per_chain + 1);
			num_res_per_chain = 0;

			res_change = true;
			
		} else if (curr_res_code != res_code || curr_res_seq_no != res_seq_no || curr_ins_code != ins_code) {
			num_res_per_chain++;
			res_change = true;
		}
		
		model_no = curr_model_no;
		res_code = curr_res_code;
		res_seq_no = curr_res_seq_no;
		chain_id = curr_chain_id;
		ins_code = curr_ins_code;
			
		max_chain_id_len = std::max(std::size_t(chain_id.size()), max_chain_id_len);
		atom_serial = std::max(getSerialNumber(*atom), atom_serial);
		
		if (res_change) {
			// TODO
			res_start_atom_idx = i;
		}
	}
	
	createGlobalBondData(molgraph);
	
	return max_chain_id_len;
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
	}	
}
		
void Biomol::MMTFDataWriter::init(const Chem::MolecularGraph& molgraph)
{
	atoms.clear();

	std::transform(molgraph.getAtomsBegin(), molgraph.getAtomsEnd(), std::back_inserter(atoms),
				   Internal::AddressOf<const Chem::Atom>());
	std::sort(atoms.begin(), atoms.end(), AtomLessCompareFunc());

	atomIndices.resize(molgraph.getNumAtoms());
	
	resBondMask.resize(molgraph.getNumBonds());
	resBondMask.reset();
}

void Biomol::MMTFDataWriter::clearStructureData()
{
	structData.numAtoms = 0;
	structData.numBonds = 0;
	structData.numModels = 0;

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
