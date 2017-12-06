/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * JMEDataReader.cpp 
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

#include <boost/tokenizer.hpp>

#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/Entity3DFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/ReactionFunctions.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/BondStereoFlag.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/ReactionRole.hpp"
#include "CDPL/Chem/AtomMatchConstraint.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Base/DataIOBase.hpp"

#include "JMEDataReader.hpp"
#include "JMEFormatData.hpp"


using namespace CDPL;


bool Chem::JMEDataReader::readReaction(std::istream& is, Reaction& rxn)
{
	if (!hasMoreData(is))
		return false;

	init();
		
	atomMappingIDOffset = getMaxReactionAtomMappingID(rxn);

	unsigned int rxn_role = ReactionRole::REACTANT;
	bool read_comp = false;
	bool seen_delim = false;

	while (true) {
		char c;

		if (!is.get(c)) {
			if (is.eof())
				break;

			throw Base::IOError("JMEDataReader: unspecified input error while reading reaction");
		}

		if (std::isspace(c, is.getloc()))
			break;

		switch (c) {

			case JME::REACTION_ROLE_SEPARATOR:
	
				switch (rxn_role) {

					case ReactionRole::REACTANT:
						rxn_role = ReactionRole::AGENT;
						read_comp = false;
						continue;

					case ReactionRole::AGENT:
						rxn_role = ReactionRole::PRODUCT;
						read_comp = false;
						continue;

					default:
						break;
				}

				break;
		
			case JME::COMPONENT_SEPARATOR:
				seen_delim = true;
				continue;

			default:
				break;
		}

		is.putback(c);

		if (read_comp && !seen_delim) {
			if (strictErrorChecking)
				throw Base::IOError("JMEDataReader: garbage after end of reaction component");

			break;
		}

		readComponent(is, rxn.addComponent(rxn_role));

		read_comp = true;
		seen_delim = false;
	}
	
	if (rxn_role != ReactionRole::PRODUCT)
		throw Base::IOError("JMEDataReader: unexpected end of input while reading reaction");

	return true;
}

bool Chem::JMEDataReader::skipReaction(std::istream& is)
{
	if (!hasMoreData(is))
		return false;

	init();
		
	unsigned int rxn_role = ReactionRole::REACTANT;
	bool read_comp = false;
	bool seen_delim = false;

	while (true) {
		char c;

		if (!is.get(c)) {
			if (is.eof())
				break;

			throw Base::IOError("JMEDataReader: unspecified input error while skipping reaction data");
		}

		if (std::isspace(c, is.getloc()))
			break;

		switch (c) {

			case JME::REACTION_ROLE_SEPARATOR:
	
				switch (rxn_role) {

					case ReactionRole::REACTANT:
						rxn_role = ReactionRole::AGENT;
						read_comp = false;
						continue;

					case ReactionRole::AGENT:
						rxn_role = ReactionRole::PRODUCT;
						read_comp = false;
						continue;

					default:
						break;
				}

				break;
		
			case JME::COMPONENT_SEPARATOR:
				seen_delim = true;
				continue;

			default:
				break;
		}

		is.putback(c);

		if (read_comp && !seen_delim) {
			if (strictErrorChecking)
				throw Base::IOError("JMEDataReader: garbage after end of reaction component");

			break;
		}

		skipComponent(is);

		read_comp = true;
		seen_delim = false;
	}
	
	if (rxn_role != ReactionRole::PRODUCT)
		throw Base::IOError("JMEDataReader: unexpected end of input while skipping reaction data");

	return true;
}

bool Chem::JMEDataReader::readMolecule(std::istream& is, Molecule& mol)
{
	if (!hasMoreData(is))
		return false;

	init();

	atomMappingIDOffset = getMaxReactionAtomMappingID(mol);

	bool read_comp = false;
	bool seen_delim = false;

	while (true) {
		char c;

		if (!is.get(c)) {
			if (is.eof())
				break;

			throw Base::IOError("JMEDataReader: unspecified input error while reading molecule");
		}

		if (std::isspace(c, is.getloc()))
			break;

		if (c == JME::COMPONENT_SEPARATOR) {
			seen_delim = true;
			continue;
		}

		is.putback(c);

		if (read_comp && !seen_delim) {
			if (strictErrorChecking)
				throw Base::IOError("JMEDataReader: garbage after end of molecule");

			break;
		}

		readComponent(is, mol);

		read_comp = true;
		seen_delim = false;
	}

	return true;
}

bool Chem::JMEDataReader::skipMolecule(std::istream& is)
{
	if (!hasMoreData(is))
		return false;

	init();

	bool read_comp = false;
	bool seen_delim = false;

	while (true) {
		char c;

		if (!is.get(c)) {
			if (is.eof())
				break;

			throw Base::IOError("JMEDataReader: unspecified input error while skipping molecule data");
		}

		if (std::isspace(c, is.getloc()))
			break;

		if (c == JME::COMPONENT_SEPARATOR) {
			seen_delim = true;
			continue;
		}

		is.putback(c);

		if (read_comp && !seen_delim) {
			if (strictErrorChecking)
				throw Base::IOError("JMEDataReader: garbage after end of molecule");

			break;
		}

		skipComponent(is);

		read_comp = true;
		seen_delim = false;
	}

	return true;
}

bool Chem::JMEDataReader::hasMoreData(std::istream& is) const
{
	is.imbue(std::locale::classic());

	return bool(std::istream::sentry(is, false)); 
}

void Chem::JMEDataReader::init()
{
	strictErrorChecking = getStrictErrorCheckingParameter(ioBase);
	coordsDim = getCoordinatesDimensionParameter(ioBase);

	switch (coordsDim) {

		case 0:
		case 2:
		case 3:
			break;

		default:
			coordsDim = 2;
	}
}

void Chem::JMEDataReader::readComponent(std::istream& is, Molecule& mol) const
{
	std::size_t atom_idx_offs = mol.getNumAtoms();
	std::size_t num_atoms;
	std::size_t num_bonds;

	if (!(is >> num_atoms)) 
		throw Base::IOError("JMEDataReader: error while reading component atom count");

	if (!(is >> num_bonds)) 
		throw Base::IOError("JMEDataReader: error while reading component bond count");

	mol.reserveMemoryForAtoms(atom_idx_offs + num_atoms);
	mol.reserveMemoryForBonds(mol.getNumBonds() + num_bonds);

	for (std::size_t i = 0; i < num_atoms; i++)
		readAtom(is, mol);

	for (std::size_t i = 0; i < num_bonds; i++) 
		readBond(is, mol, atom_idx_offs, num_atoms);
}

void Chem::JMEDataReader::skipComponent(std::istream& is) const
{
	std::size_t num_atoms;
	std::size_t num_bonds;

	if (!(is >> num_atoms)) 
		throw Base::IOError("JMEDataReader: error while reading component atom count");

	if (!(is >> num_bonds)) 
		throw Base::IOError("JMEDataReader: error while reading component bond count");

	std::string atom_type;
	double coord;
	std::size_t atom_idx;
	int bond_type;

	for (std::size_t i = 0; i < num_atoms; i++) {
		switch (coordsDim) {

			case 2:
				is >> atom_type >> coord >> coord;
				break;

			case 3:
				is >> atom_type >> coord >> coord >> coord;

			default:
				break;
		}

		if (!is)
			throw Base::IOError("JMEDataReader: error while skipping atom");
	}

	for (std::size_t i = 0; i < num_bonds; i++) {
		is >> atom_idx >> atom_idx >> bond_type;
				
		if (!is)
			throw Base::IOError("JMEDataReader: error while skipping bond");
	}
}

void Chem::JMEDataReader::readAtom(std::istream& is, Molecule& mol) const
{
	using namespace JME;

	std::string atom_str;

	if (!(is >> atom_str)) 
		throw Base::IOError("JMEDataReader: error while reading atom specification string");

	Atom& atom = mol.addAtom();

	std::string::const_iterator atom_str_beg = atom_str.begin();
	std::string::const_iterator atom_str_end = atom_str.end();
	std::string::const_iterator rxn_aam_id_pos = std::find(atom_str_beg, atom_str_end, AtomString::RXN_ATOM_ID_SEPARATOR);
	std::string::const_iterator query_flags_pos = std::find(atom_str_beg, rxn_aam_id_pos, AtomString::QUERY_FLAGS_SEPARATOR);

	MatchConstraintList::SharedPointer alist_constr_ptr;
	MatchConstraintList::SharedPointer query_constr_ptr;
	MatchConstraintList::SharedPointer atom_constr_ptr;

	if (std::find(atom_str_beg, query_flags_pos, AtomString::ATOM_LIST_SEPARATOR) != query_flags_pos) 
		alist_constr_ptr = readAtomList(atom_str_beg, query_flags_pos);
	else		   
		atom_constr_ptr = readAtomSymbol(&atom, atom_str_beg, query_flags_pos, query_flags_pos != rxn_aam_id_pos);

	if (query_flags_pos != rxn_aam_id_pos)
		query_constr_ptr = readQueryFlags(++query_flags_pos, rxn_aam_id_pos); 

	if (rxn_aam_id_pos != atom_str_end)
		readReactionAtomMappingID(atom, ++rxn_aam_id_pos, atom_str_end); 

	if (coordsDim == 2 || coordsDim == 3) {
		double x, y, z;

		if (!(is >> x)) 
			throw Base::IOError("JMEDataReader: error while reading atom x coordinate");

		if (!(is >> y)) 
			throw Base::IOError("JMEDataReader: error while reading atom y coordinate");

		if (coordsDim == 3) {
			if (!(is >> z)) 
				throw Base::IOError("JMEDataReader: error while reading atom z coordinate");

			set3DCoordinates(atom, Math::vec(x, y, z));

		} else
			set2DCoordinates(atom, Math::vec(x, y));
	}

	MatchConstraintList::SharedPointer combined_constr_ptr;

	if (alist_constr_ptr) {
		if (query_constr_ptr) {
			combined_constr_ptr.reset(new MatchConstraintList(MatchConstraintList::AND_LIST));

			combined_constr_ptr->addElement(AtomMatchConstraint::CONSTRAINT_LIST,
											MatchConstraint::EQUAL,
											alist_constr_ptr);
			combined_constr_ptr->addElement(AtomMatchConstraint::CONSTRAINT_LIST,
											MatchConstraint::EQUAL,
											query_constr_ptr);
		} else
			combined_constr_ptr = alist_constr_ptr;

	} else if (atom_constr_ptr) {
		if (query_constr_ptr) {
			combined_constr_ptr.reset(new MatchConstraintList(MatchConstraintList::AND_LIST));

			combined_constr_ptr->addElement(AtomMatchConstraint::CONSTRAINT_LIST,
											MatchConstraint::EQUAL,
											atom_constr_ptr);
			combined_constr_ptr->addElement(AtomMatchConstraint::CONSTRAINT_LIST,
											MatchConstraint::EQUAL,
											query_constr_ptr);
		} else
			combined_constr_ptr = atom_constr_ptr;
	} else
		combined_constr_ptr = query_constr_ptr;

	if (combined_constr_ptr) 
		setMatchConstraints(atom, combined_constr_ptr);

	bool has_symbol = hasSymbol(atom);

	if (!hasType(atom)) {
		if (has_symbol)
			setType(atom, getTypeForSymbol(atom));
		else
			setType(atom, AtomType::UNKNOWN);

	}

	if (!has_symbol)
		setSymbol(atom, getSymbolForType(atom));
}

Chem::MatchConstraintList::SharedPointer 
Chem::JMEDataReader::readAtomList(std::string::const_iterator it, std::string::const_iterator end) const
{
	using namespace JME;

	MatchConstraintList::SharedPointer alist_constr_ptr(new MatchConstraintList(MatchConstraintList::OR_LIST));

	typedef boost::tokenizer<boost::char_separator<char> > Tokenizer;

	const char alist_sep[] = { AtomString::ATOM_LIST_SEPARATOR, 0 };

	boost::char_separator<char> tokenizer_func(alist_sep, "", boost::keep_empty_tokens);
	Tokenizer tokenizer(it, end, tokenizer_func);
		
	for (Tokenizer::iterator token_it = tokenizer.begin(); token_it != tokenizer.end(); ++token_it) {
		MatchConstraintList::SharedPointer atom_constr_ptr = readAtomSymbol(0, token_it->begin(), token_it->end(), true);

		if (atom_constr_ptr)
			alist_constr_ptr->addElement(AtomMatchConstraint::CONSTRAINT_LIST,
										 MatchConstraint::EQUAL,
										 atom_constr_ptr);
	}

	if (alist_constr_ptr->getSize() != 0)
		return alist_constr_ptr;

	return MatchConstraintList::SharedPointer();
}

Chem::MatchConstraintList::SharedPointer 
Chem::JMEDataReader::readAtomSymbol(Atom* atom, std::string::const_iterator it, 
									std::string::const_iterator end, bool has_query_flags) const
{
	using namespace JME;
	
	std::string symbol;

	for ( ; it != end; ++it) {
		char c = *it;

		if (c == '+' || c == '-')
			break;

		symbol.push_back(c);
	}

	MatchConstraintList::SharedPointer atom_constr_ptr(new MatchConstraintList(MatchConstraintList::AND_LIST));

	if (symbol == AtomString::ANY_NON_C_ATOM_SYMBOL) {
		if (atom)
			setType(*atom, AtomType::QH);

		atom_constr_ptr->addElement(AtomMatchConstraint::TYPE,
									MatchConstraint::EQUAL,
									AtomType::QH);

	} else if (symbol == AtomString::ANY_ATOM_SYMBOL) {
		if (atom)
			setType(*atom, AtomType::ANY);

		atom_constr_ptr->addElement(AtomMatchConstraint::TYPE, 
									MatchConstraint::EQUAL,
									AtomType::ANY);

	} else if (symbol == AtomString::ANY_AROM_ATOM_SYMBOL) {
		if (atom)
			setType(*atom, AtomType::ANY);

		atom_constr_ptr->addElement(AtomMatchConstraint::TYPE, 
									MatchConstraint::EQUAL,
									AtomType::ANY);
		atom_constr_ptr->addElement(AtomMatchConstraint::AROMATICITY, 
									MatchConstraint::EQUAL, 
									true);

	} else if (symbol == AtomString::ANY_NON_AROM_ATOM_SYMBOL) {
		if (atom)
			setType(*atom, AtomType::ANY);

		atom_constr_ptr->addElement(AtomMatchConstraint::TYPE, 
									MatchConstraint::EQUAL,
									AtomType::ANY);
		atom_constr_ptr->addElement(AtomMatchConstraint::AROMATICITY, 
									MatchConstraint::EQUAL, 
									false);
	} else {
		std::size_t sym_len = symbol.length();

		if (sym_len > 1 && symbol[0] == AtomString::ATOMIC_NUMBER_PREFIX) {
			unsigned int atom_type = 0;
			std::size_t i = 1;

			for ( ; i < sym_len && std::isdigit(symbol[i], std::locale::classic()); i++)
				atom_type = atom_type * 10 + symbol[i] - '0';

			if (i == sym_len) {
				if (atom)
					setType(*atom, atom_type);

				atom_constr_ptr->addElement(AtomMatchConstraint::TYPE, 
											MatchConstraint::EQUAL,
											atom_type);
			} else if (atom)
				setSymbol(*atom, symbol);

		} else {
			if (sym_len == 1 && 
				(symbol[0] == 'c' || symbol[0] == 'n' || symbol[0] == 'o' || symbol[0] == 's' || symbol[0] == 'p')) {
				symbol[0] = std::toupper(symbol[0], std::locale::classic());

				unsigned int atom_type = AtomDictionary::getType(symbol);

				if (atom)
					setType(*atom, atom_type);

				atom_constr_ptr->addElement(AtomMatchConstraint::TYPE, 
											MatchConstraint::EQUAL,
											atom_type);
				atom_constr_ptr->addElement(AtomMatchConstraint::AROMATICITY, 
											MatchConstraint::EQUAL, 
											true);
			} else if (has_query_flags) {
				unsigned int atom_type = AtomDictionary::getType(symbol);

				if (atom_type != AtomType::UNKNOWN && atom_type <= AtomType::MAX_ATOMIC_NO) {
					if (atom)
						setType(*atom, atom_type);

					atom_constr_ptr->addElement(AtomMatchConstraint::TYPE, 
												MatchConstraint::EQUAL,
												atom_type);
					atom_constr_ptr->addElement(AtomMatchConstraint::AROMATICITY, 
												MatchConstraint::EQUAL, 
												false);
				} else if (atom)
					setSymbol(*atom, symbol);

			} else if (atom)
				setSymbol(*atom, symbol);
		}
	}

	if (it != end) {
		long charge = readAtomCharge(it, end);

		if (atom)
			setFormalCharge(*atom, charge);

		if (has_query_flags || atom_constr_ptr->getSize() != 0)
			atom_constr_ptr->addElement(AtomMatchConstraint::CHARGE, 
										MatchConstraint::EQUAL,
										charge);
	}

	if (atom_constr_ptr->getSize() != 0)
		return atom_constr_ptr;

	return MatchConstraintList::SharedPointer();
}

long Chem::JMEDataReader::readAtomCharge(std::string::const_iterator it, std::string::const_iterator end) const
{
	using namespace JME;

	long charge = 0;
	bool exit = false;

	for ( ; it != end && !exit; ) {
		char c = *it;
		int sign;

		switch (c) {

			case AtomString::NEGATIVE_CHARGE_PREFIX:
				sign = -1;
				break;

			case AtomString::POSITIVE_CHARGE_PREFIX:
				sign = 1;
				break;

			default:
				exit = true;
				continue;
		}

		if  (++it != end) {
			long mult = 0;

			for ( ; it != end && std::isdigit(*it, std::locale::classic()); ++it)
				mult = mult * 10 + *it - '0';

			charge += mult * sign;

		} else 
			charge = sign;
	}

	return charge;
}

Chem::MatchConstraintList::SharedPointer 
Chem::JMEDataReader::readQueryFlags(std::string::const_iterator it, std::string::const_iterator end) const
{
	using namespace JME;

	typedef boost::tokenizer<boost::char_separator<char> > Tokenizer;

	const char query_flags_sep[] = { AtomString::QUERY_FLAGS_SEPARATOR, 0 };

	boost::char_separator<char> tokenizer_func(query_flags_sep);
	Tokenizer tokenizer(it, end, tokenizer_func);

	MatchConstraintList::SharedPointer query_constr_ptr(new MatchConstraintList(MatchConstraintList::AND_LIST));

	for (Tokenizer::iterator token_it = tokenizer.begin(); token_it != tokenizer.end(); ++token_it) {
		const std::string& query_flag = *token_it;

		if (query_flag == AtomString::RING_ATOM_FLAG) 
			query_constr_ptr->addElement(AtomMatchConstraint::RING_TOPOLOGY, 
										 MatchConstraint::EQUAL,
										 true);

		else if (query_flag == AtomString::CHAIN_ATOM_FLAG) 
			query_constr_ptr->addElement(AtomMatchConstraint::RING_TOPOLOGY, 
										 MatchConstraint::EQUAL,
										 false);

		else if (query_flag == AtomString::ANY_AROM_ATOM_SYMBOL) 
			query_constr_ptr->addElement(AtomMatchConstraint::AROMATICITY, 
										 MatchConstraint::EQUAL,
										 true);

		else if (query_flag == AtomString::ANY_NON_AROM_ATOM_SYMBOL) 
			query_constr_ptr->addElement(AtomMatchConstraint::AROMATICITY, 
										 MatchConstraint::EQUAL,
										 false);

		else if (query_flag[0] == AtomString::HEAVY_BOND_COUNT_PREFIX) {
			std::size_t heavy_bnd_cnt = 0;
			std::size_t str_len = query_flag.length();

			for (std::size_t i = 1; i < str_len && std::isdigit(query_flag[i], std::locale::classic()); i++)
				heavy_bnd_cnt = heavy_bnd_cnt * 10 + query_flag[i] - '0';

			query_constr_ptr->addElement(AtomMatchConstraint::HEAVY_BOND_COUNT, 
										 MatchConstraint::EQUAL,
										 heavy_bnd_cnt);

		} else if (query_flag[0] == AtomString::H_COUNT_PREFIX) {
			std::size_t h_count = 0;
			std::size_t str_len = query_flag.length();

			for (std::size_t i = 1; i < str_len && std::isdigit(query_flag[i], std::locale::classic()); i++)
				h_count = h_count * 10 + query_flag[i] - '0';

			query_constr_ptr->addElement(AtomMatchConstraint::H_COUNT, 
										 MatchConstraint::EQUAL,
										 h_count);

		} else if (strictErrorChecking)
			throw Base::IOError("JMEDataReader: invalid query specification for atom");

		else
			continue;
	}

	if (query_constr_ptr->getSize() != 0)
		return query_constr_ptr;

	return MatchConstraintList::SharedPointer();
}

void Chem::JMEDataReader::readReactionAtomMappingID(Atom& atom, std::string::const_iterator it, 
													std::string::const_iterator end) const
{
	std::size_t rxn_aam_id = 0;
	bool has_id = false;

	for ( ; it != end && std::isdigit(*it, std::locale::classic()); ++it) {
		rxn_aam_id = rxn_aam_id * 10 + *it - '0';
		has_id = true;
	}

	if (!has_id && strictErrorChecking)
		throw Base::IOError("JMEDataReader: invalid reaction atom atom mapping class number");

	if (strictErrorChecking && it != end)
		throw Base::IOError("JMEDataReader: junk after reaction atom atom mapping class number");

	if (rxn_aam_id > 0)
		setReactionAtomMappingID(atom, rxn_aam_id + atomMappingIDOffset);
}

void Chem::JMEDataReader::readBond(std::istream& is, Molecule& mol, std::size_t atom_idx_offs, 
								   std::size_t num_atoms) const
{
	std::size_t atom1_idx;

	if (!(is >> atom1_idx)) 
		throw Base::IOError("JMEDataReader: error while reading bond start atom number");

	if (atom1_idx == 0 || atom1_idx > num_atoms)
		throw Base::IOError("JMEDataReader: bond start atom number range error");

	std::size_t atom2_idx;

	if (!(is >> atom2_idx)) 
		throw Base::IOError("JMEDataReader: error while reading bond end atom number");

	if (atom2_idx == 0 || atom2_idx > num_atoms)
		throw Base::IOError("JMEDataReader: bond end atom number range error");

	Bond& bond = mol.addBond(atom_idx_offs + atom1_idx - 1, atom_idx_offs + atom2_idx - 1);

	int bond_type;

	if (!(is >> bond_type)) 
		throw Base::IOError("JMEDataReader: error while reading bond type");

	using namespace JME;

	unsigned int bond_stereo = BondStereoFlag::PLAIN;
	std::size_t order = 1;

	switch (bond_type) {

		case BondType::SINGLE:
			break;

		case BondType::DOUBLE:
			order = 2;
			break;

		case BondType::TRIPLE:
			order = 3;
			break;

		case BondType::UP:
			bond_stereo = BondStereoFlag::UP;
			break;

		case BondType::DOWN:
			bond_stereo = BondStereoFlag::DOWN;
			break;

		default:
			if (strictErrorChecking)
				throw Base::IOError("JMEDataReader: invalid bond type");

			return;
	}

	set2DStereoFlag(bond, bond_stereo);
	setOrder(bond, order);
}
