/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SMILESDataReader.cpp 
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
#include <locale>
#include <algorithm>
#include <functional>
#include <limits>
#include <cassert>

#include <boost/tokenizer.hpp>
#include <boost/bind.hpp>

#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/ReactionFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"
#include "CDPL/Chem/ReactionRole.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Base/DataIOBase.hpp"
#include "CDPL/Internal/StringUtilities.hpp"

#include "SMILESDataReader.hpp"
#include "SMILESData.hpp"


using namespace CDPL;


namespace
{

	const Chem::SMILESDataReader::STArray NO_BONDS;
}


bool Chem::SMILESDataReader::readReaction(std::istream& is, Reaction& rxn)
{
	if (!hasMoreData(is))
		return false;

	getParameters();

	atomMappingIDOffset = getMaxAtomMappingID(rxn);

	if (!(is >> rxnSMILESString)) 
		throw Base::IOError("SMILESDataReader: reading of reaction SMILES string failed");

	typedef boost::tokenizer<boost::char_separator<char> > Tokenizer;

	const char role_sep[] = { SMILES::REACTION_ROLE_SEPARATOR, 0 };
	const char comp_sep[] = { SMILES::COMPONENT_SEPARATOR, 0 };

	unsigned int rxn_role = ReactionRole::REACTANT;
	Tokenizer rxn_tokenizer(rxnSMILESString, boost::char_separator<char>(role_sep, "", boost::keep_empty_tokens));

	for (Tokenizer::iterator t_it1 = rxn_tokenizer.begin(); t_it1 != rxn_tokenizer.end(); ) {
		Tokenizer comp_tokenizer(*t_it1, boost::char_separator<char>(comp_sep, ""));
		std::size_t open_branch_cnt = 0;

		for (Tokenizer::iterator t_it2 = comp_tokenizer.begin(); t_it2 != comp_tokenizer.end(); ) {
			const std::string& comp_str = *t_it2;

			if (open_branch_cnt == 0)
				molSMILESString.clear();

			std::string::const_iterator comp_str_end = comp_str.end();

			for (std::string::const_iterator c_it = comp_str.begin(); c_it != comp_str_end; ++c_it) {
				switch (*c_it) {
					
					case SMILES::BRANCH_PREFIX:
						open_branch_cnt++;
						continue;

					case SMILES::BRANCH_SUFFIX:
						if (open_branch_cnt > 0)
							open_branch_cnt--;

					default:
						continue;
				}
			}

			if (!molSMILESString.empty())
				molSMILESString.push_back(SMILES::COMPONENT_SEPARATOR);

			molSMILESString.append(comp_str);

			if (++t_it2 != comp_tokenizer.end() && open_branch_cnt > 0)  
				continue;

			Molecule& comp = rxn.addComponent(rxn_role);

			init(comp);
	
			parseSMILES(comp, 0);
	
			kekulizeBonds(comp);
			setAtomStereoDescriptors(comp);
			setBondStereoDescriptors(comp);
		}

		if (++t_it1 == rxn_tokenizer.end())
			break;

		switch (rxn_role) {

			case ReactionRole::REACTANT:
				rxn_role = ReactionRole::AGENT;
				break;

			case ReactionRole::AGENT:
				rxn_role = ReactionRole::PRODUCT;
				break;

			case ReactionRole::PRODUCT:
				if (strictErrorChecking)
					throw Base::IOError("SMILESDataReader: invalid reaction SMILES format");

				return true;
		}
	}

	if (rxn_role != ReactionRole::PRODUCT)
		throw Base::IOError("SMILESDataReader: unexpected end of input");

	readName(is, rxn, rxnSMILESString, "SMILESDataReader: reading of reaction name failed");

	return true;
}

bool Chem::SMILESDataReader::skipReaction(std::istream& is)
{
	if (!hasMoreData(is))
		return false;
	
	if (!(is >> rxnSMILESString)) 
		throw Base::IOError("SMILESDataReader: reading of reaction SMILES string failed");

	getParameters();
	skipName(is, rxnSMILESString, "SMILESDataReader: skipping to next reaction data record failed");

	return true;
}

bool Chem::SMILESDataReader::readMolecule(std::istream& is, Molecule& mol)
{
	if (!hasMoreData(is))
		return false;

	getParameters();

	atomMappingIDOffset = getMaxAtomMappingID(mol);

	if (!(is >> molSMILESString)) 
		throw Base::IOError("SMILESDataReader: reading of molecule SMILES string failed");

	init(mol);

	parseSMILES(mol, 0);

	kekulizeBonds(mol);
	setAtomStereoDescriptors(mol);
	setBondStereoDescriptors(mol);

	readName(is, mol, molSMILESString, "SMILESDataReader: reading of molecule name failed");

	return true;
}

bool Chem::SMILESDataReader::skipMolecule(std::istream& is)
{
	if (!hasMoreData(is))
		return false;

	if (!(is >> molSMILESString)) 
		throw Base::IOError("SMILESDataReader: reading of molecule SMILES string failed");

	getParameters();
	skipName(is, rxnSMILESString, "SMILESDataReader: skipping to next molecule data record failed");

	return true;
}

void Chem::SMILESDataReader::getParameters()
{
	strictErrorChecking = getStrictErrorCheckingParameter(ioBase);
	recordFormat = getSMILESRecordFormatParameter(ioBase);
	recordSeparator = getRecordSeparatorParameter(ioBase);

	if (recordFormat != "S" && recordFormat != "SN")
		throw Base::IOError("SMILESDataReader: invalid smiles record format control-parameter");
}

template <typename T>
void Chem::SMILESDataReader::readName(std::istream& is, T& obj, std::string& str, 
									  const std::string& error_msg) const
{
	if (recordFormat == "SN") {
		if (is.eof()) {
			str.clear();
			return;
		}

		if (recordSeparator.size() == 1)
			std::getline(is, str, recordSeparator[0]);
		else
			std::getline(is, str);

		if (!is)
			throw Base::IOError(error_msg);

		Internal::trimString(str);

		setName(obj, str);
	}
}

void Chem::SMILESDataReader::skipName(std::istream& is, std::string& str, const std::string& error_msg) const
{
	if (recordFormat == "SN") {
		if (is.eof())
			return;

		if (recordSeparator.size() == 1)
			std::getline(is, str, recordSeparator[0]);
		else
			std::getline(is, str);

		if (!is)
			throw Base::IOError(error_msg);
	}
}

bool Chem::SMILESDataReader::hasMoreData(std::istream& is) const
{
	is.imbue(std::locale::classic());

	return bool(std::istream::sentry(is, false));
}

void Chem::SMILESDataReader::init(const Molecule& mol)
{
	nextCharIndex = 0;
	openBranchCount = 0;
	lexicalBondNumber = 0;
	startAtomIndex = mol.getNumAtoms();
	startBondIndex = mol.getNumBonds();

	aromaticAtomMask.reset();
	stereoAtomList.clear();
	bondDirectionTable.clear();
	bondTable.clear();
	closureBondMap.clear();
	nbrBondListTable.assign(nbrBondListTable.size(), STArray());
}

void Chem::SMILESDataReader::parseSMILES(Molecule& mol, const Atom* prev_atom)
{
	char c;

	if (!getChar(c, true)) {
		ungetChar();

		if (strictErrorChecking) {
			if (!closureBondMap.empty())
				throw Base::IOError("SMILESDataReader: pending ring closures");

			if (openBranchCount != 0)
				throw Base::IOError("SMILESDataReader: branch parentheses not balanced");
		}

		return;
	}

	switch (c) {

		case SMILES::COMPONENT_SEPARATOR:
			parseSMILES(mol, 0);
			return;

		case SMILES::BRANCH_PREFIX:
			openBranchCount++;

			parseSMILES(mol, prev_atom);
			parseSMILES(mol, prev_atom);
			return;

		case SMILES::BRANCH_SUFFIX:
			if (openBranchCount == 0)
				throw Base::IOError("SMILESDataReader: branch parentheses not balanced");

			openBranchCount--;
			return;

		default:
			break;
	}

	ungetChar();

	const Atom* next_atom;

	if (prev_atom) {
		BondParameters bond_params;

		parseBondParameters(bond_params);

		next_atom = parseAtom(mol);

		createBond(mol, prev_atom, next_atom, bond_params, lexicalBondNumber);

		addToBondList(mol.getAtomIndex(*prev_atom), lexicalBondNumber);
		addToBondList(mol.getAtomIndex(*next_atom), lexicalBondNumber++, false);

	} else
		next_atom = parseAtom(mol);

	parseSMILES(mol, next_atom);
}

void Chem::SMILESDataReader::parseRingClosures(Molecule& mol, const Atom& atom)
{
	BondParameters bond_params;

	std::size_t saved_char_idx = nextCharIndex;

	while (parseBondParameters(bond_params)) {
		char c;
		std::size_t closure_no;

		getChar(c, false);

		if (c != SMILES::CLOSURE_NO_PREFIX) {
			if (!std::isdigit(c, std::locale::classic())) {
				nextCharIndex = saved_char_idx;
				return;
			}

			closure_no = c - '0';
			
		} else if (!parseNumber(closure_no, 2))
			throw Base::IOError("SMILESDataReader: invalid ring closure bond number format");

		saved_char_idx = nextCharIndex;

		ClosureBondMap::iterator lb = closureBondMap.lower_bound(closure_no);

		if (lb != closureBondMap.end() && !(closureBondMap.key_comp()(closure_no, lb->first))) {
			const ClosureBond& closure_bond = lb->second;

			if (strictErrorChecking && closure_bond.startAtom == &atom)
				throw Base::IOError("SMILESDataReader: trying to connect atom with itself");

			bond_params.combineWith(closure_bond.bondParameters, strictErrorChecking);

			createBond(mol, closure_bond.startAtom, &atom, bond_params, closure_bond.lexBondNumber);
		
			closureBondMap.erase(lb);

			addToBondList(mol.getAtomIndex(atom), closure_bond.lexBondNumber);

		} else {      // create a new map item for a future ring closure
			closureBondMap.insert(lb, 
								  ClosureBondMap::value_type(closure_no, ClosureBond(lexicalBondNumber, &atom, bond_params)));

			addToBondList(mol.getAtomIndex(atom), lexicalBondNumber++);
		}
	}
}

bool Chem::SMILESDataReader::parseBondParameters(BondParameters& bond_params)
{
	using namespace SMILES;

	bond_params.direction = 0;
	bond_params.order = 0;
	bond_params.aromatic = false;
	bond_params.explicitBond = false;

	char c;

	if (!getChar(c, true)) {
		ungetChar();
		return false;
	}

	switch (c) {

		case BondSymbol::UP_DIR_FLAG:
		case BondSymbol::DOWN_DIR_FLAG:
			bond_params.direction = c;

		case BondSymbol::SINGLE_BOND:
			bond_params.order = 1;
			break;

		case BondSymbol::DOUBLE_BOND:
			bond_params.order = 2;
			break;

		case BondSymbol::TRIPLE_BOND:
			bond_params.order = 3;
			break;

		case BondSymbol::AROMATIC_BOND:
			bond_params.aromatic = true;
			break;
						
		default:
			ungetChar();
			return true;
	}

	bond_params.explicitBond = true;

	return true;
}

void Chem::SMILESDataReader::createBond(Molecule& mol, const Atom* atom1, const Atom* atom2,
										const BondParameters& bond_params, std::size_t lex_bond_no)
{
	assert(atom1 != 0 && atom2 != 0);

	std::size_t atom1_idx = mol.getAtomIndex(*atom1);
	std::size_t atom2_idx = mol.getAtomIndex(*atom2);

	Bond& bond = mol.addBond(atom1_idx, atom2_idx);

	std::size_t bond_idx = mol.getBondIndex(bond);

	if (bond_params.aromatic) {
		setAtomAromaticityFlag(atom1_idx);
		setAtomAromaticityFlag(atom2_idx);
		setAromaticityFlag(bond, true);

	} else {
		if (!(bond_params.order == 0 && getAtomAromaticityFlag(atom1_idx) && getAtomAromaticityFlag(atom2_idx)))
			setOrder(bond, std::max(bond_params.order, std::size_t(1)));
	}

	setBondDirection(bond_idx, bond_params.direction);
	setBondTableEntry(lex_bond_no, &bond);
}

const Chem::Atom* Chem::SMILESDataReader::parseAtom(Molecule& mol)
{
	char c;

	getChar(c, false);

	if (c == SMILES::AtomString::SPECIAL_ATOM_PREFIX)
		return parseSpecialAtom(mol);

	ungetChar();

	return parseOrgSubsetAtom(mol);
}

const Chem::Atom* Chem::SMILESDataReader::parseOrgSubsetAtom(Molecule& mol)
{
	char symbol[3];
	bool aromatic = parseElementSymbol(symbol, true);

	Atom& atom = mol.addAtom();
	std::string symbol_str(symbol);

	setSymbol(atom, symbol_str);
	setType(atom, AtomDictionary::getType(symbol_str));

	if (aromatic)
		setAtomAromaticityFlag(mol.getAtomIndex(atom));

	parseRingClosures(mol, atom);

	return &atom;
}

const Chem::Atom* Chem::SMILESDataReader::parseSpecialAtom(Molecule& mol)
{
	std::size_t isotope;
	bool iso_spec = parseNumber(isotope);

	char symbol[3];
	bool aromatic = parseElementSymbol(symbol, false);

	unsigned int perm_desig = parseStereoSpec();

	std::size_t impl_h_count = 0;
	bool h_count_spec = parseImplicitHCount(impl_h_count);

	long charge = parseCharge();

	std::size_t aam_id = parseReactionAtomMappingID();

	char c;

	getChar(c, false);

	if (c != SMILES::AtomString::SPECIAL_ATOM_SUFFIX)
		throw Base::IOError("SMILESDataReader: invalid atom specification - missing closing bracket");

	Atom& atom = mol.addAtom();
	std::size_t atom_idx = mol.getAtomIndex(atom);
	std::string symbol_str(symbol);

	setSymbol(atom, symbol_str);
	setType(atom, AtomDictionary::getType(symbol_str));

	if (iso_spec)
		setIsotope(atom, isotope);

	if (charge != 0)
		setFormalCharge(atom, charge);

	if (!h_count_spec || (h_count_spec && impl_h_count != 0))
		setImplicitHydrogenCount(atom, impl_h_count);

	if (aam_id > 0)
		setAtomMappingID(atom, aam_id + atomMappingIDOffset);

	if (aromatic)
		setAtomAromaticityFlag(atom_idx);

	if (perm_desig > 0)
		addStereoAtom(&atom, perm_desig);

	parseRingClosures(mol, atom);

	return &atom;		
}

bool Chem::SMILESDataReader::parseElementSymbol(char symbol[3], bool org_subset)
{
	symbol[1] = 0;
	symbol[2] = 0;

	getChar(symbol[0], false);

	if (symbol[0] == SMILES::AtomString::UNDEF_ELEMENT_SYMBOL)
		return false;

	if (!std::isalpha(symbol[0], std::locale::classic())) {
		if (strictErrorChecking)
			throw Base::IOError("SMILESDataReader: invalid element symbol");

		return false;
	}

	if (std::islower(symbol[0], std::locale::classic())) {
		switch (symbol[0]) {

			case 't':
				if (org_subset && strictErrorChecking)
					throw Base::IOError("SMILESDataReader: invalid element symbol");

			case 's':
				if (!org_subset) {
					getChar(symbol[1], false);
					
					if (symbol[1] != 'e') {
						ungetChar();
						symbol[1] = 0;
					} 
				}

			case 'c':
			case 'n':
			case 'o':
			case 'p':
				break;

			case 'a':
				if (!org_subset) {
					getChar(symbol[1], false);
					
					if (symbol[1] == 's')
						break;

					ungetChar();
					symbol[1] = 0;
				}

			default:
				if (strictErrorChecking)
					throw Base::IOError("SMILESDataReader: invalid element symbol");

				return false;
		}

		symbol[0] = std::toupper(symbol[0], std::locale::classic());				
		return true;
	}

	if (getChar(symbol[1], true) && std::islower(symbol[1], std::locale::classic())) {
		if (!org_subset) {
			if (strictErrorChecking && !AtomDictionary::isChemicalElement(AtomDictionary::getType(symbol)))
				throw Base::IOError("SMILESDataReader: invalid element symbol");

			return false;
		}

		switch (symbol[0]) {
	
			case 'B':
				if (symbol[1] != 'r')
					break;

				return false;

			case 'C':
				if (symbol[1] != 'l')
					break;

				return false;

			default:
				break;
		}
	}

	ungetChar();
	symbol[1] = 0;

	if (strictErrorChecking && !AtomDictionary::isChemicalElement(AtomDictionary::getType(symbol)))
		throw Base::IOError("SMILESDataReader: invalid element symbol");

	return false;
}

unsigned int Chem::SMILESDataReader::parseStereoSpec()
{
	using namespace SMILES;

	char c;
	std::size_t prefix_cnt = 0;

	for ( ; getChar(c, false) && c == AtomString::CHIRAL_CLASS_PREFIX; prefix_cnt++);

	ungetChar();

	if (prefix_cnt != 1)
		return prefix_cnt;

	if (parseNumber(prefix_cnt))
		return prefix_cnt;

	std::string class_type(' ', 2);

	getChar(class_type[0], false);

	if (c == AtomString::TETRAHEDRAL_CHIRALITY[0] 
		|| c == AtomString::ALLENE_TYPE_CHIRALITY[0]
		|| c == AtomString::SQUARE_PLANAR_CHIRALITY[0]
		|| c == AtomString::TRIG_BIPYR_CHIRALITY[0]
		|| c == AtomString::OCTAHEDRAL_CHIRALITY[0]) {
	
		getChar(class_type[1], false);

		bool supported_class = false;

		if (class_type == AtomString::TETRAHEDRAL_CHIRALITY)
			supported_class = true;

		else if (strictErrorChecking 
				 && class_type != AtomString::ALLENE_TYPE_CHIRALITY
				 && class_type != AtomString::SQUARE_PLANAR_CHIRALITY
				 && class_type != AtomString::TRIG_BIPYR_CHIRALITY
				 && class_type != AtomString::OCTAHEDRAL_CHIRALITY)

			throw Base::IOError("SMILESDataReader: specification for unknown chiral class");

		unsigned int perm_desig = 1;

		parseNumber(perm_desig);

		return (supported_class ? perm_desig : 0);
	}

	ungetChar();

	return 1;
}

bool Chem::SMILESDataReader::parseImplicitHCount(std::size_t& value)
{
	char c;

	getChar(c, false);

	if (c != SMILES::AtomString::H_COUNT_PREFIX) {
		ungetChar();
		return false;
	}

	value = 1;

	parseNumber(value);

	return true;
}

long Chem::SMILESDataReader::parseCharge()
{
	using namespace SMILES;

	long charge = 0;
	char c;

	while (true) {
		long sign;

		getChar(c, false);

		switch (c) {

			case AtomString::POSITIVE_CHARGE_PREFIX:
				sign = 1;
				break;

			case AtomString::NEGATIVE_CHARGE_PREFIX:
				sign = -1;
				break;

			default:
				ungetChar();
				return charge;
		}

		std::size_t count = 1;

		parseNumber(count);

		charge += sign * count;
	}

	return 0;
}

std::size_t Chem::SMILESDataReader::parseReactionAtomMappingID()
{
	char c;
	std::size_t aam_id = 0;

	getChar(c, false);

	if (c != SMILES::AtomString::ATOM_MAPPING_ID_PREFIX) {
		ungetChar();
		return 0;
	}

	if (!parseNumber(aam_id) && strictErrorChecking)
		throw Base::IOError("SMILESDataReader: invalid reaction atom atom mapping class number");

	return aam_id;
}

template <typename T>
bool Chem::SMILESDataReader::parseNumber(T& value, std::size_t max_digits)
{
	char c;

	getChar(c, false);

	if (std::isdigit(c, std::locale::classic())) {
		value = T(c - '0');

		if (max_digits == 1)
			return true;

		for (std::size_t num_digits = 1; getChar(c, true) && std::isdigit(c, std::locale::classic()); ) {
			value = value * T(10) + T(c - '0');

			if (max_digits > 0 && ++num_digits == max_digits)
				return true;
		}

		ungetChar();

		return true;
	}

	ungetChar();

	return false;
}

bool Chem::SMILESDataReader::getChar(char& c, bool eos_allowed)
{
	if (nextCharIndex >= molSMILESString.length()) {
		if (!eos_allowed)
			throw Base::IOError("SMILESDataReader: unexpected end of input");

		nextCharIndex++;
		
		c = 0;
		return false;
	}

	c = molSMILESString[nextCharIndex++];

	return true;
}

void Chem::SMILESDataReader::ungetChar()
{
	assert(nextCharIndex > 0);

	nextCharIndex--;
}

void Chem::SMILESDataReader::setAtomAromaticityFlag(std::size_t atom_idx)
{
	assert(atom_idx >= startAtomIndex);

	std::size_t bit_index = atom_idx - startAtomIndex;

	if (aromaticAtomMask.size() < bit_index + 1)
		aromaticAtomMask.resize(bit_index + 1);

	aromaticAtomMask.set(bit_index);
}

bool Chem::SMILESDataReader::getAtomAromaticityFlag(std::size_t atom_idx) const
{
	assert(atom_idx >= startAtomIndex);

	std::size_t bit_index = atom_idx - startAtomIndex;

	return (aromaticAtomMask.size() <= bit_index ? false : aromaticAtomMask.test(bit_index));
}

void Chem::SMILESDataReader::addStereoAtom(Atom* atom, unsigned int perm_desig)
{
	stereoAtomList.push_back(StereoAtomDescr(atom, perm_desig));
}

void Chem::SMILESDataReader::setBondDirection(std::size_t bond_idx, char dir_flag)
{
	assert(bond_idx >= startBondIndex);

	std::size_t tab_index = bond_idx - startBondIndex;

	if (bondDirectionTable.size() <= tab_index)
		bondDirectionTable.resize(tab_index + 1);

	bondDirectionTable[tab_index] = dir_flag;
}

char Chem::SMILESDataReader::getBondDirection(std::size_t bond_idx) const
{
	assert(bond_idx >= startBondIndex);

	std::size_t tab_index = bond_idx - startBondIndex;

	return (bondDirectionTable.size() <= tab_index ? 0 : bondDirectionTable[tab_index]);
}

void Chem::SMILESDataReader::setBondTableEntry(std::size_t bond_no, const Bond* bond)
{
	if (bondTable.size() < bond_no + 1)
		bondTable.resize(bond_no + 1);

	bondTable[bond_no] = bond;
}

void Chem::SMILESDataReader::addToBondList(std::size_t atom_idx, std::size_t bond_no, bool at_tail)
{
	assert(atom_idx >= startAtomIndex);

	std::size_t tab_index = atom_idx - startAtomIndex;

	if (nbrBondListTable.size() < tab_index + 1)
		nbrBondListTable.resize(tab_index + 1);

	if (at_tail)
		nbrBondListTable[tab_index].push_back(bond_no);
	else
		nbrBondListTable[tab_index].insert(nbrBondListTable[tab_index].begin(), bond_no);
}

const Chem::SMILESDataReader::STArray& Chem::SMILESDataReader::getBondList(std::size_t atom_idx) const
{
	assert(atom_idx >= startAtomIndex);

	std::size_t tab_index = atom_idx - startAtomIndex;

	if (tab_index >= nbrBondListTable.size())
		return NO_BONDS;
	
	return nbrBondListTable[tab_index];
}

void Chem::SMILESDataReader::setAtomStereoDescriptors(const Molecule& mol) const
{
	StereoAtomList::const_iterator sad_list_end = stereoAtomList.end();

	for (StereoAtomList::const_iterator sad_it = stereoAtomList.begin(); sad_it != sad_list_end; ++sad_it) {
		const StereoAtomDescr& descr = *sad_it;
		unsigned int perm_desig = descr.second;

		if (perm_desig < 1 || perm_desig > 2)
			continue;

		Atom* atom = descr.first;

		assert(atom != 0);

		std::size_t atom_idx = mol.getAtomIndex(*atom);
		std::size_t num_bonds = atom->getNumBonds();
		const STArray& lex_bond_list = getBondList(atom_idx);

		assert(num_bonds == lex_bond_list.size());

		if (num_bonds < 3 || num_bonds > 4)
			continue;

		const Atom* ref_atoms[4];

		if (num_bonds == 4) {
			for (std::size_t i = 1; i <= 4; i++) {
				std::size_t lex_bond_no = lex_bond_list[i % 4];
			
				assert(lex_bond_no < bondTable.size());

				ref_atoms[i - 1] = &bondTable[lex_bond_no]->getNeighbor(*atom);
			}

			std::size_t lex_bond_no = lex_bond_list[0];
			
			assert(lex_bond_no < bondTable.size());

			ref_atoms[3] = &bondTable[lex_bond_no]->getNeighbor(*atom);

		} else {
			if (std::find_if(atom->getAtomsBegin(), atom->getAtomsEnd(), 
							 boost::bind(std::less<std::size_t>(), 
										 boost::bind(&Molecule::getAtomIndex, boost::ref(mol), _1),
										 atom_idx)) != atom->getAtomsEnd()) { // the chiral atom is not the very first one

				perm_desig = (perm_desig == 1 ? 2 : 1);
			} 

			for (std::size_t i = 0; i < 3; i++) {
				std::size_t lex_bond_no = lex_bond_list[i];
			
				assert(lex_bond_no < bondTable.size());

				ref_atoms[i] = &bondTable[lex_bond_no]->getNeighbor(*atom);
			}
		}
	
		unsigned int config = (perm_desig == 1 ? AtomConfiguration::R : AtomConfiguration::S);
	
		if (num_bonds == 3)
			setStereoDescriptor(*atom, StereoDescriptor(config, *ref_atoms[0], *ref_atoms[1], *ref_atoms[2]));
		else
			setStereoDescriptor(*atom, StereoDescriptor(config, *ref_atoms[0], *ref_atoms[1], *ref_atoms[2], *ref_atoms[3]));
	} 
}

void Chem::SMILESDataReader::kekulizeBonds(Molecule& mol)
{
	if (startBondIndex == 0) {
		Chem::kekulizeBonds(mol);
		return;
	}

	readMolGraph.clear();

	std::for_each(mol.getBondsBegin() + startBondIndex, mol.getBondsEnd(), 
				  boost::bind(&Fragment::addBond, readMolGraph, _1));

	Chem::kekulizeBonds(readMolGraph);
}

void Chem::SMILESDataReader::setBondStereoDescriptors(Molecule& mol) const
{
	using namespace SMILES;
 
	Molecule::BondIterator bonds_end = mol.getBondsEnd();

	for (Molecule::BondIterator b_it = mol.getBondsBegin() + startBondIndex; b_it != bonds_end; ++b_it) {
		Bond& bond = *b_it;

		if (getOrder(bond) != 2)
			continue;

		char nbr_bond_dirs[2][2] = { { 0, 0 }, { 0, 0 } };
		const Atom* geom_ref_atoms[2] = { 0, 0 };
		bool skip = false;

		for (std::size_t i = 0; i < 2 && !skip; i++) {
			const Atom& atom = (i == 0 ? bond.getBegin() : bond.getEnd());
			std::size_t num_bonds = atom.getNumBonds();

			if (num_bonds < 2 || num_bonds > 3) {
				skip = true;
				break;
			}

			Atom::ConstAtomIterator atoms_end = atom.getAtomsEnd();
			Atom::ConstBondIterator nbr_b_it = atom.getBondsBegin();

			for (Atom::ConstAtomIterator a_it = atom.getAtomsBegin(); a_it != atoms_end; ++a_it, ++nbr_b_it) {
				const Bond& nbr_bond = *nbr_b_it;	

				if (&nbr_bond == &bond)
					continue;

				const Atom& nbr_atom = *a_it;

				if (!geom_ref_atoms[i]) {
					geom_ref_atoms[i] = &nbr_atom;
					nbr_bond_dirs[i][0] = getBondDirection(mol.getBondIndex(nbr_bond));

				} else
					nbr_bond_dirs[i][1] = getBondDirection(mol.getBondIndex(nbr_bond));		
			}

			if (!geom_ref_atoms[i]) {
				skip = true;
				break;
			}

			if (nbr_bond_dirs[i][0] == 0)
				switch (nbr_bond_dirs[i][1]) {

					case BondSymbol::UP_DIR_FLAG:
						nbr_bond_dirs[i][0] = BondSymbol::DOWN_DIR_FLAG;
						break;

					case BondSymbol::DOWN_DIR_FLAG:
						nbr_bond_dirs[i][0] = BondSymbol::UP_DIR_FLAG;
						break;

					default:
						skip = true;
						break;
				}
		}

		if (skip)
			continue;
	
		setStereoDescriptor(bond, StereoDescriptor((nbr_bond_dirs[0][0] == nbr_bond_dirs[1][0] ? BondConfiguration::TRANS : BondConfiguration::CIS),
												   *geom_ref_atoms[0], bond.getBegin(), bond.getEnd(), *geom_ref_atoms[1]));
	}
}


void Chem::SMILESDataReader::BondParameters::combineWith(const BondParameters& params, bool strict_error_checks)
{
	if (!explicitBond) {
		if (params.explicitBond)
			*this = params;

		return;
	}

	if (!params.explicitBond)
		return;

	if (direction == 0)
		direction = params.direction;

	else if (params.direction != 0 && direction != params.direction) {
		if (strict_error_checks)
			throw Base::IOError("SMILESDataReader: conflicting multiple bond direction specifications");

		direction = 0;
	}

	if (order == 0)
		order = params.order;

	else if (strict_error_checks && params.order != 0 && order != params.order)
		throw Base::IOError("SMILESDataReader: conflicting multiple bond order specifications");

	aromatic |= params.aromatic;
}
