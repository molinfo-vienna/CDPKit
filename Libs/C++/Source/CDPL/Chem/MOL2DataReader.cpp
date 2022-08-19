/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * MOL2DataReader.cpp 
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

#include <istream>
#include <locale>

#include <boost/algorithm/string.hpp>
#include <boost/bind.hpp>

#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/MultiConfMoleculeInputProcessor.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Base/DataIOBase.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Internal/StringUtilities.hpp"
#include "CDPL/Internal/StringDataIOUtilities.hpp"

#include "MOL2DataReader.hpp"
#include "MOL2FormatData.hpp"


using namespace CDPL;


namespace
{

	typedef boost::unordered_map<std::string, unsigned int> StringToTypeMap;

	StringToTypeMap stringToMoleculeTypeMap;
	StringToTypeMap stringToChargeTypeMap;
	StringToTypeMap stringToAtomTypeMap;
	StringToTypeMap stringToBondTypeMap;

	struct Init {

		Init() {
			using namespace Chem;
			using namespace MOL2;

			std::string str;

			for (std::size_t i = 0; i < sizeof(MOLECULE_TYPE_STRINGS) / sizeof(TypeToString); i++) {
				str = MOLECULE_TYPE_STRINGS[i].string;
				boost::to_upper(str);

				stringToMoleculeTypeMap.insert(StringToTypeMap::value_type(str, MOLECULE_TYPE_STRINGS[i].type));
			}

			for (std::size_t i = 0; i < sizeof(CHARGE_TYPE_STRINGS) / sizeof(TypeToString); i++) {
				str = CHARGE_TYPE_STRINGS[i].string;
				boost::to_upper(str);

				stringToChargeTypeMap.insert(StringToTypeMap::value_type(str, CHARGE_TYPE_STRINGS[i].type));
			}

			for (std::size_t i = 0; i < sizeof(ATOM_TYPE_STRINGS) / sizeof(TypeToString); i++) {
				str = ATOM_TYPE_STRINGS[i].string;
				boost::to_lower(str);

				stringToAtomTypeMap.insert(StringToTypeMap::value_type(str, ATOM_TYPE_STRINGS[i].type));
			}

			for (std::size_t i = 0; i < sizeof(BOND_TYPE_STRINGS) / sizeof(TypeToString); i++) {
				str = BOND_TYPE_STRINGS[i].string;
				boost::to_lower(str);

				stringToBondTypeMap.insert(StringToTypeMap::value_type(str, BOND_TYPE_STRINGS[i].type));
			}
		}

	} init;
}


bool Chem::MOL2DataReader::readMolecule(std::istream& is, Molecule& mol)
{
	if (!skipInputToRTI(is, MOL2::MOLECULE_RTI, true))
		return false;

	init(is);

	std::size_t atom_idx_offs = mol.getNumAtoms();
	std::size_t bond_idx_offs = mol.getNumBonds();

	doReadMolecule(is, mol);

	if (multiConfImport) {
		MolecularGraph* tgt_molgraph;

		if (atom_idx_offs == 0) {
			tgt_molgraph = &mol;

		} else {
			if (!confTargetFragment)
				confTargetFragment.reset(new Fragment());
			else
				confTargetFragment->clear();

			tgt_molgraph = confTargetFragment.get();

			std::for_each(mol.getAtomsBegin() + atom_idx_offs, mol.getAtomsEnd(), boost::bind(&Fragment::addAtom, confTargetFragment.get(), _1));
			std::for_each(mol.getBondsBegin() + bond_idx_offs, mol.getBondsEnd(), boost::bind(&Fragment::addBond, confTargetFragment.get(), _1));
			
			confTargetFragment->copyProperties(mol);
		}

		MultiConfMoleculeInputProcessor::SharedPointer mc_input_proc = getMultiConfInputProcessorParameter(ioBase);

		if (!mc_input_proc) {
			for (MolecularGraph::AtomIterator it = tgt_molgraph->getAtomsBegin(), end = tgt_molgraph->getAtomsEnd(); it != end; ++it) {
				Atom& atom = *it;
				Math::Vector3DArray::SharedPointer coords_array(new Math::Vector3DArray());
		
				set3DCoordinatesArray(atom, coords_array);
		
				coords_array->addElement(get3DCoordinates(atom));
			}

			extractStereoAtoms(*tgt_molgraph);

			while (hasMoreData(is)) {
				std::istream::pos_type last_spos = is.tellg();

				if (!addConformer(is, *tgt_molgraph)) {
					is.seekg(last_spos);
					return true;
				}
			}

			return true;
		}

		if (!mc_input_proc->init(*tgt_molgraph))
			return true;

		if (!confTestMolecule)
			confTestMolecule.reset(new BasicMolecule());

		for (std::istream::pos_type last_spos = is.tellg(); skipInputToRTI(is, MOL2::MOLECULE_RTI, true); last_spos = is.tellg()) {
			confTestMolecule->clear();

			doReadMolecule(is, *confTestMolecule);

			if (!mc_input_proc->addConformation(*tgt_molgraph, *confTestMolecule)) {
				is.seekg(last_spos);
				return true;
			}
		}
	}

	return true;
}

bool Chem::MOL2DataReader::skipMolecule(std::istream& is)
{
	if (!skipInputToRTI(is, MOL2::MOLECULE_RTI, true))
		return false;

	init(is);

	if (!multiConfImport)
		return true;
	
	if (!confTargetMolecule)
		confTargetMolecule.reset(new BasicMolecule());
	else
		confTargetMolecule->clear();

	doReadMolecule(is, *confTargetMolecule);

	MultiConfMoleculeInputProcessor::SharedPointer mc_input_proc = getMultiConfInputProcessorParameter(ioBase);

	if (!mc_input_proc) {
		extractStereoAtoms(*confTargetMolecule);

		while (hasMoreData(is)) {
			std::istream::pos_type last_spos = is.tellg();

			if (!readNextConformer(is, *confTargetMolecule, false)) {
				is.seekg(last_spos);
				return true;
			}
		}

		return true;
	}

	if (!mc_input_proc->init(*confTargetMolecule))
		return true;

	for (std::istream::pos_type last_spos = is.tellg(); skipInputToRTI(is, MOL2::MOLECULE_RTI, true); last_spos = is.tellg()) {
		confTestMolecule->clear();

		doReadMolecule(is, *confTestMolecule);

		if (!mc_input_proc->isConformation(*confTargetMolecule, *confTestMolecule)) {
			is.seekg(last_spos);
			return true;
		}
	}

	return true;
}

bool Chem::MOL2DataReader::hasMoreData(std::istream& is)
{
	return skipInputToRTI(is, MOL2::MOLECULE_RTI, false);
}

void Chem::MOL2DataReader::init(std::istream& is)
{
	strictErrorChecking = getStrictErrorCheckingParameter(ioBase); 
	multiConfImport     = getMultiConfImportParameter(ioBase);
	calcFormalCharges   = getMOL2CalcFormalChargesParameter(ioBase);

	is.imbue(std::locale::classic());
}

void Chem::MOL2DataReader::doReadMolecule(std::istream& is, Molecule& mol)
{
	readMoleculeRecord(is, mol);
	readAtomSection(is, mol);
	readBondSection(is, mol);
	readSubstructSection(is, mol);

	if (!calcFormalCharges)
		return;
		
	std::size_t num_atoms = mol.getNumAtoms();

	for (std::size_t i = num_atoms - molAtomCount, j = 0; j < molAtomCount; i++, j++) {
		Atom& atom = mol.getAtom(i);

		setImplicitHydrogenCount(atom, 0);
		setFormalCharge(atom, calcFormalCharge(atom, mol));
	}
}

void Chem::MOL2DataReader::readMoleculeRecord(std::istream& is, Molecule& mol)
{
	using namespace Internal;

// Name

	if (!readDataLine(is))
		throw Base::IOError("MOL2DataReader: error while reading molecule name: unexpected end of molecule record");

	setName(mol, dataLine);

// Atom count

	if (!readDataLine(is))
		throw Base::IOError("MOL2DataReader: error while reading counts line: unexpected end of molecule record");

	lineTokenizer.assign(dataLine);

	Tokenizer::iterator t_it = lineTokenizer.begin();
	Tokenizer::iterator t_end = lineTokenizer.end();

	if (t_it == t_end)
		throw Base::IOError("MOL2DataReader: missing number of atoms in molecule record");

	molAtomCount = parseNumber<std::size_t>(*t_it, "MOL2DataReader: error while parsing number of molecule atoms");
	molSubstructCount = 0;
	molBondCount = 0;

// Bond count

	if (++t_it != t_end) {
		molBondCount = parseNumber<std::size_t>(*t_it, "MOL2DataReader: error while parsing number of molecule bonds");

		if (strictErrorChecking && molAtomCount < 2 && molBondCount > 0)
			throw Base::IOError("MOL2DataReader: number of bonds > 0 while number of atoms < 2");

		if (++t_it != t_end)
			molSubstructCount = parseNumber<std::size_t>(*t_it, "MOL2DataReader: error while parsing number of substructures");
	}

// Molecule type

	if (!readDataLine(is))
		throw Base::IOError("MOL2DataReader: error while reading molecule type: unexpected end of molecule record");

	boost::to_upper(dataLine);

	StringToTypeMap::const_iterator it = stringToMoleculeTypeMap.find(dataLine);

	if (it == stringToMoleculeTypeMap.end()) {
		if (strictErrorChecking)
			throw Base::IOError("MOL2DataReader: unknown molecule type");

		setMOL2MoleculeType(mol, MOL2MoleculeType::UNKNOWN);

	} else
		setMOL2MoleculeType(mol, it->second);

// Charge type

	if (!readDataLine(is))
		throw Base::IOError("MOL2DataReader: error while reading atom charge type: unexpected end of molecule record");

	boost::to_upper(dataLine);

	it = stringToChargeTypeMap.find(dataLine);

	if (it == stringToChargeTypeMap.end()) {
		if (strictErrorChecking)
			throw Base::IOError("MOL2DataReader: unknown atom charge type");

		setMOL2ChargeType(mol, MOL2ChargeType::UNKNOWN);

	} else
		setMOL2ChargeType(mol, it->second);
}

void Chem::MOL2DataReader::readAtomSection(std::istream& is, Molecule& mol)
{
	using namespace Internal;

	if (molAtomCount == 0)
		return;

	if (!skipInputToRTI(is, MOL2::ATOM_RTI, true))
		throw Base::IOError("MOL2DataReader: error while looking for molecule atom section: unexpected end of input");

	mol.reserveMemoryForAtoms(mol.getNumAtoms() + molAtomCount);

	atomIDsToIndex.clear();
	substructIDsToAtoms.clear();

	std::string tmp_string;
	unsigned int charge_type = getMOL2ChargeType(mol);

	for (std::size_t i = 0; i < molAtomCount; i++) {
		if (!readDataLine(is))
			throw Base::IOError("MOL2DataReader: error while reading atom data line: unexpected end of input");

		lineTokenizer.assign(dataLine);

		Tokenizer::iterator t_it = lineTokenizer.begin();
		Tokenizer::iterator t_end = lineTokenizer.end();

// Atom ID

		if (t_it == t_end)
			throw Base::IOError("MOL2DataReader: missing atom ID number");

		std::size_t id = parseNumber<std::size_t>(*t_it, "MOL2DataReader: error while parsing atom ID number");
		
		if (strictErrorChecking && atomIDsToIndex.find(id) != atomIDsToIndex.end())
			throw Base::IOError("MOL2DataReader: found multiple atoms with ID " + boost::lexical_cast<std::string>(id));

		atomIDsToIndex.insert(AtomIDToIndexMap::value_type(id, mol.getNumAtoms()));

// Atom name
		
		Atom& atom = mol.addAtom();

		if (++t_it == t_end)
			throw Base::IOError("MOL2DataReader: missing atom name");

		if (*t_it == MOL2::EMPTY_STRING_FIELD)
			setMOL2Name(atom, "");
		else
			setMOL2Name(atom, *t_it);

// Atom coordinates

		Math::Vector3D coords;

		if (++t_it == t_end)
			throw Base::IOError("MOL2DataReader: missing atom x-coordinate");

		coords[0] = parseNumber<double>(*t_it, "MOL2DataReader: error while parsing atom x-coordinate");

		if (++t_it == t_end)
			throw Base::IOError("MOL2DataReader: missing atom y-coordinate");

		coords[1] = parseNumber<double>(*t_it, "MOL2DataReader: error while parsing atom y-coordinate");

		if (++t_it == t_end)
			throw Base::IOError("MOL2DataReader: missing atom z-coordinate");

		coords[2] = parseNumber<double>(*t_it, "MOL2DataReader: error while parsing atom z-coordinate");

		set3DCoordinates(atom, coords);

// Atom type

		if (++t_it == t_end)
			throw Base::IOError("MOL2DataReader: missing Sybyl atom type");

		tmp_string = *t_it;
		boost::to_lower(tmp_string);

		StringToTypeMap::const_iterator it = stringToAtomTypeMap.find(tmp_string);

		if (it == stringToAtomTypeMap.end()) {
			if (!tmp_string.empty())
				tmp_string[0] = std::toupper(tmp_string[0], std::locale::classic());		

			unsigned int atom_type = AtomDictionary::getType(tmp_string);

			if (atom_type == AtomType::UNKNOWN && strictErrorChecking)
				throw Base::IOError("MOL2DataReader: cannot deduce atom type");

			setType(atom, atom_type);
			setSybylType(atom, SybylAtomType::UNKNOWN);

		} else {
			setType(atom, sybylToAtomType(it->second));
			setSybylType(atom, it->second);
		}

		setSymbol(atom, getSymbolForType(atom));
		
		bool have_charge = false;

// Substructure ID

		if (++t_it != t_end) {
			std::size_t substruct_id = parseNumber<double>(*t_it, "MOL2DataReader: error while parsing atom substructure ID");

// Substructure Name

			if (++t_it != t_end) {
				if (*t_it != MOL2::EMPTY_STRING_FIELD) {
					setMOL2SubstructureID(atom, substruct_id);
					setMOL2SubstructureName(atom, *t_it);

					substructIDsToAtoms.insert(SubstructIDToAtomMap::value_type(substruct_id, &atom));
				}

// Atom charge
				if (charge_type != MOL2ChargeType::NO_CHARGES && ++t_it != t_end) {
					setMOL2Charge(atom, parseNumber<double>(*t_it, "MOL2DataReader: error while parsing atom charge"));
					have_charge = true;
				}
			} 
		} 

		if (strictErrorChecking && !have_charge && charge_type != MOL2ChargeType::NO_CHARGES)
			throw Base::IOError("MOL2DataReader: missing atom charge");
	}
}

void Chem::MOL2DataReader::readBondSection(std::istream& is, Molecule& mol)
{
	using namespace Internal;

	if (molAtomCount < 2 || molBondCount == 0)
		return;

	if (!skipInputToRTI(is, MOL2::BOND_RTI, true))
		throw Base::IOError("MOL2DataReader: error while looking for molecule bond section: unexpected end of input");

	mol.reserveMemoryForBonds(mol.getNumBonds() + molBondCount);

	bool kekulize = false;
	std::string tmp_string;

	for (std::size_t i = 0; i < molBondCount; i++) {
		if (!readDataLine(is))
			throw Base::IOError("MOL2DataReader: error while reading bond data line: unexpected end of input");

		lineTokenizer.assign(dataLine);

		Tokenizer::iterator t_it = lineTokenizer.begin();
		Tokenizer::iterator t_end = lineTokenizer.end();

// Bond ID

		if (t_it == t_end)
			throw Base::IOError("MOL2DataReader: missing bond ID number");

		if (strictErrorChecking)
			parseNumber<std::size_t>(*t_it, "MOL2DataReader: error while parsing bond ID number");

// Bond atom IDs

		if (++t_it == t_end)
			throw Base::IOError("MOL2DataReader: missing atom ID of bond origin");

		std::size_t atom1_id = parseNumber<std::size_t>(*t_it, "MOL2DataReader: error while parsing bond origin atom ID");
		AtomIDToIndexMap::const_iterator idx_it = atomIDsToIndex.find(atom1_id);

		if (idx_it == atomIDsToIndex.end())
			throw Base::IOError("MOL2DataReader: bond origin atom with ID '" + *t_it + "' does not exist");

		std::size_t atom1_idx = idx_it->second;

		if (++t_it == t_end)
			throw Base::IOError("MOL2DataReader: missing atom ID of bond target");

		std::size_t atom2_id = parseNumber<std::size_t>(*t_it, "MOL2DataReader: error while parsing bond target atom ID");
		idx_it = atomIDsToIndex.find(atom2_id);

		if (idx_it == atomIDsToIndex.end())
			throw Base::IOError("MOL2DataReader: bond target atom with ID '" + *t_it + "' does not exist");

		std::size_t atom2_idx = idx_it->second;

// Bond type

		if (++t_it == t_end)
			throw Base::IOError("MOL2DataReader: missing Sybyl bond type");

		tmp_string = *t_it;
		boost::to_lower(tmp_string);

		unsigned int bond_type = SybylBondType::UNKNOWN;
		StringToTypeMap::const_iterator it = stringToBondTypeMap.find(tmp_string);

		if (it != stringToBondTypeMap.end())
			bond_type = it->second;

		else if (strictErrorChecking)
			throw Base::IOError("MOL2DataReader: unknown Sybyl bond type");

		if (bond_type == SybylBondType::NOT_CONNECTED)
			continue;

		Bond& bond = mol.addBond(atom1_idx, atom2_idx);

		setSybylType(bond, bond_type);

		switch (bond_type) {

			case SybylBondType::DOUBLE:
				setOrder(bond, 2);
				continue;

			case SybylBondType::TRIPLE:
				setOrder(bond, 3);
				continue;

			case SybylBondType::AROMATIC:
				kekulize = true;
				continue;

			default:
				setOrder(bond, 1);
		}
	}

	if (kekulize)
		kekulizeBonds(mol);	
}

void Chem::MOL2DataReader::readSubstructSection(std::istream& is, Molecule& mol)
{
	using namespace Internal;

	if (molSubstructCount == 0)
		return;

	if (!skipInputToRTI(is, MOL2::SUBSTRUCTURE_RTI, true))
		throw Base::IOError("MOL2DataReader: error while looking for substructure section: unexpected end of input");

	std::string name;
	std::string subtype;
	std::string chain;

	for (std::size_t i = 0; i < molSubstructCount; i++) {
		if (!readDataLine(is))
			throw Base::IOError("MOL2DataReader: error while reading substructure data line: unexpected end of input");

		lineTokenizer.assign(dataLine);

		Tokenizer::iterator t_it = lineTokenizer.begin();
		Tokenizer::iterator t_end = lineTokenizer.end();

// Substructure ID

		if (t_it == t_end)
			throw Base::IOError("MOL2DataReader: missing substructure ID number");

		std::size_t id = parseNumber<std::size_t>(*t_it, "MOL2DataReader: error while parsing substructure ID number");

// Substructure name

		if (++t_it == t_end)
			throw Base::IOError("MOL2DataReader: missing substructure name");

		name = *t_it;

// Substructure root atom

		if (++t_it == t_end)
			throw Base::IOError("MOL2DataReader: missing substructure root atom");

		chain.clear();
		subtype.clear();

// Substructure chain

		if (++t_it != t_end && ++t_it != t_end && ++t_it != t_end) {
			chain = *t_it;

// Substructure subtype

			if (++t_it != t_end)
				subtype= *t_it;
		}

		std::pair<SubstructIDToAtomMap::const_iterator, SubstructIDToAtomMap::const_iterator> atoms = substructIDsToAtoms.equal_range(id);

		for ( ; atoms.first != atoms.second; ++atoms.first) {
			if (strictErrorChecking && getMOL2SubstructureName(*atoms.first->second) != name)
				throw Base::IOError("MOL2DataReader: substructure name in atom section does not match name in substructure section");

			if (!chain.empty())
				setMOL2SubstructureChain(*atoms.first->second, chain);

			if (!subtype.empty())
				setMOL2SubstructureSubtype(*atoms.first->second, subtype);
		}
	}
}

bool Chem::MOL2DataReader::addConformer(std::istream& is, MolecularGraph& molgraph)
{
	if (!readNextConformer(is, molgraph, true))
		return false;

	addConformation(molgraph, confCoords);
	return true;
}

bool Chem::MOL2DataReader::readNextConformer(std::istream& is, const MolecularGraph& molgraph, bool save_coords)
{
	using namespace Internal;

	if (!skipInputToRTI(is, MOL2::MOLECULE_RTI, true))
		return false;

	if (!readDataLine(is))
		throw Base::IOError("MOL2DataReader: error while reading molecule name: unexpected end of molecule record");

	if (!readDataLine(is))
		throw Base::IOError("MOL2DataReader: error while reading counts line: unexpected end of molecule record");

	lineTokenizer.assign(dataLine);

	Tokenizer::iterator t_it = lineTokenizer.begin();
	Tokenizer::iterator t_end = lineTokenizer.end();

	if (t_it == t_end)
		throw Base::IOError("MOL2DataReader: missing number of atoms in molecule record");

	if (molAtomCount != parseNumber<std::size_t>(*t_it, "MOL2DataReader: error while parsing number of molecule atoms"))
		return false;

	if (++t_it != t_end) { 
		if (molBondCount != parseNumber<std::size_t>(*t_it, "MOL2DataReader: error while parsing number of molecule bonds"))
			return false;

	} else if (molBondCount != 0) 
		return false;

	if (molAtomCount == 0)
		return true;

	if (!skipInputToRTI(is, MOL2::ATOM_RTI, true))
		throw Base::IOError("MOL2DataReader: error while looking for molecule atom section: unexpected end of input");

	atomIDsToIndex.clear();

	if (!stereoAtoms.empty() || save_coords)
		confCoords.resize(molAtomCount);

	std::string tmp_string;

	for (std::size_t i = 0; i < molAtomCount; i++) {
		if (!readDataLine(is))
			throw Base::IOError("MOL2DataReader: error while reading atom data line: unexpected end of input");

		lineTokenizer.assign(dataLine);

		Tokenizer::iterator t_it = lineTokenizer.begin();
		Tokenizer::iterator t_end = lineTokenizer.end();

// Atom ID

		if (t_it == t_end)
			throw Base::IOError("MOL2DataReader: missing atom ID number");

		std::size_t id = parseNumber<std::size_t>(*t_it, "MOL2DataReader: error while parsing atom ID number");
		
		if (strictErrorChecking && atomIDsToIndex.find(id) != atomIDsToIndex.end())
			throw Base::IOError("MOL2DataReader: found multiple atoms with ID " + boost::lexical_cast<std::string>(id));

		atomIDsToIndex.insert(AtomIDToIndexMap::value_type(id, i));

// Atom name
	
		if (++t_it == t_end)
			throw Base::IOError("MOL2DataReader: missing atom name");

// Atom coordinates

		if (!stereoAtoms.empty() || save_coords) {
			Math::Vector3D::Pointer coords = confCoords[i].getData();

			if (++t_it == t_end)
				throw Base::IOError("MOL2DataReader: missing atom x-coordinate");

			coords[0] = parseNumber<double>(*t_it, "MOL2DataReader: error while parsing atom x-coordinate");

			if (++t_it == t_end)
				throw Base::IOError("MOL2DataReader: missing atom y-coordinate");

			coords[1] = parseNumber<double>(*t_it, "MOL2DataReader: error while parsing atom y-coordinate");

			if (++t_it == t_end)
				throw Base::IOError("MOL2DataReader: missing atom z-coordinate");

			coords[2] = parseNumber<double>(*t_it, "MOL2DataReader: error while parsing atom z-coordinate");

		} else {
			if (++t_it == t_end)
				throw Base::IOError("MOL2DataReader: missing atom x-coordinate");

			if (++t_it == t_end)
				throw Base::IOError("MOL2DataReader: missing atom y-coordinate");

			if (++t_it == t_end)
				throw Base::IOError("MOL2DataReader: missing atom z-coordinate");
		}

// Atom type

		if (++t_it == t_end)
			throw Base::IOError("MOL2DataReader: missing Sybyl atom type");

		const Atom& atom = molgraph.getAtom(i);

		tmp_string = *t_it;
		boost::to_lower(tmp_string);

		StringToTypeMap::const_iterator it = stringToAtomTypeMap.find(tmp_string);

		if (it == stringToAtomTypeMap.end()) {
			if (!tmp_string.empty())
				tmp_string[0] = std::toupper(tmp_string[0], std::locale::classic());		

			if (getType(atom) != AtomDictionary::getType(tmp_string))
				return false;

		} else {
			if (getSybylType(atom) != it->second)
				return false;
		}
	}

	if (molBondCount > 0) {
		if (!skipInputToRTI(is, MOL2::BOND_RTI, true))
			throw Base::IOError("MOL2DataReader: error while looking for molecule bond section: unexpected end of input");

		for (std::size_t i = 0; i < molBondCount; i++) {
			if (!readDataLine(is))
				throw Base::IOError("MOL2DataReader: error while reading bond data line: unexpected end of input");

			lineTokenizer.assign(dataLine);

			Tokenizer::iterator t_it = lineTokenizer.begin();
			Tokenizer::iterator t_end = lineTokenizer.end();

// Bond ID

			if (t_it == t_end)
				throw Base::IOError("MOL2DataReader: missing bond ID number");

// Bond atom IDs

			if (++t_it == t_end)
				throw Base::IOError("MOL2DataReader: missing atom ID of bond origin");

			std::size_t atom1_id = parseNumber<std::size_t>(*t_it, "MOL2DataReader: error while parsing bond origin atom ID");
			AtomIDToIndexMap::const_iterator idx_it = atomIDsToIndex.find(atom1_id);

			if (idx_it == atomIDsToIndex.end())
				throw Base::IOError("MOL2DataReader: bond origin atom with ID '" + *t_it + "' does not exist");

			const Bond& bond = molgraph.getBond(i);
			
			if (molgraph.getAtomIndex(bond.getBegin()) != idx_it->second)
				return false;

			if (++t_it == t_end)
				throw Base::IOError("MOL2DataReader: missing atom ID of bond target");

			std::size_t atom2_id = parseNumber<std::size_t>(*t_it, "MOL2DataReader: error while parsing bond target atom ID");
			idx_it = atomIDsToIndex.find(atom2_id);

			if (idx_it == atomIDsToIndex.end())
				throw Base::IOError("MOL2DataReader: bond target atom with ID '" + *t_it + "' does not exist");

			if (molgraph.getAtomIndex(bond.getEnd()) != idx_it->second)
				return false;

// Bond type

			if (++t_it == t_end)
				throw Base::IOError("MOL2DataReader: missing Sybyl bond type");

			tmp_string = *t_it;
			boost::to_lower(tmp_string);

			unsigned int bond_type = SybylBondType::UNKNOWN;
			StringToTypeMap::const_iterator it = stringToBondTypeMap.find(tmp_string);

			if (it != stringToBondTypeMap.end())
				bond_type = it->second;

			else if (strictErrorChecking)
				throw Base::IOError("MOL2DataReader: unknown Sybyl bond type");

			if (bond_type == SybylBondType::NOT_CONNECTED)
				continue;

			if (getSybylType(bond) != bond_type)
				return false;
		}
	}

	for (StereoAtomList::const_iterator it = stereoAtoms.begin(), end = stereoAtoms.end(); it != end; ++it) {
		const Atom& atom = **it;
		const StereoDescriptor& descr = getStereoDescriptor(atom);
		unsigned int calc_config = calcAtomConfiguration(atom, molgraph, descr, confCoords);

		if (calc_config != descr.getConfiguration()) 
			return false;
	}

	return true;
}

void Chem::MOL2DataReader::extractStereoAtoms(MolecularGraph& molgraph)
{
	stereoAtoms.clear();

	perceiveSSSR(molgraph, true);
	setRingFlags(molgraph, false);
	calcImplicitHydrogenCounts(molgraph, false);
	perceiveHybridizationStates(molgraph, false);
	setAromaticityFlags(molgraph, false);
	calcCIPPriorities(molgraph, false);

	perceiveAtomStereoCenters(molgraph, false, true, false);

	for (MolecularGraph::AtomIterator it = molgraph.getAtomsBegin(), end = molgraph.getAtomsEnd(); it != end; ++it) {
		Atom& atom = *it;

		if (!getStereoCenterFlag(atom)) {
			setStereoDescriptor(atom, StereoDescriptor(AtomConfiguration::NONE));
			continue;
		} 
		
		if ((!hasStereoDescriptor(atom) || getStereoDescriptor(atom).getConfiguration() == AtomConfiguration::UNDEF) &&
			!isInvertibleNitrogen(atom, molgraph) && !isAmideNitrogen(atom, molgraph, false, false) && !isPlanarNitrogen(atom, molgraph)) { 

			StereoDescriptor descr = calcStereoDescriptor(atom, molgraph, 3);

			setStereoDescriptor(atom, descr);

			if (descr.getConfiguration() == AtomConfiguration::R || descr.getConfiguration() == AtomConfiguration::R)
				stereoAtoms.push_back(&atom);
		}
	}
}

bool Chem::MOL2DataReader::readInputLine(std::istream& is)
{
	while (!std::istream::traits_type::eq_int_type(is.peek(), std::istream::traits_type::eof())) {
		Internal::readLine(is, inputLine, "MOL2DataReader: error while reading input line", false, false, 0, Chem::MOL2::END_OF_LINE);

		if (inputLine.empty()) 
			return true;

		if (inputLine[0] == MOL2::COMMENT_PREFIX)
			continue;

		return true;
	}

	return false;
}

bool Chem::MOL2DataReader::readDataLine(std::istream& is)
{
	using namespace Internal;

	dataLine.clear();

	while (readInputLine(is)) {
		trimString(inputLine, false, true);

		if (inputLine.empty()) {
			trimString(dataLine);
			return true;
		}

		if (inputLine[inputLine.size() - 1] == MOL2::LINE_CONT_MARKER) {
			dataLine.insert(dataLine.size(), inputLine, 0, inputLine.size() - 1);
			continue;
		}

		if (dataLine.empty()) 
			dataLine.swap(inputLine);
		else
			dataLine.append(inputLine);

		trimString(dataLine);
		return true;
	}

	return false;
}

bool Chem::MOL2DataReader::skipInputToRTI(std::istream& is, const std::string& rti, bool skip_rti)
{
	for (std::istream::pos_type last_spos = is.tellg(); readInputLine(is); last_spos = is.tellg()) {
		Internal::trimString(inputLine, false, true);

		if (inputLine != rti)
			continue;

		if (!skip_rti)
			is.seekg(last_spos);

		return true;
	}

	return false;
}
