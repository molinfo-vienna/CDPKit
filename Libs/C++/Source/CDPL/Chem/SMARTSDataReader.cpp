/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SMARTSDataReader.cpp 
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

#include <istream>
#include <locale>
#include <algorithm>
#include <functional>
#include <cassert>

#include <boost/tokenizer.hpp>
#include <boost/bind.hpp>

#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Chem/BasicMolecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/ReactionMatchConstraint.hpp"
#include "CDPL/Chem/MolecularGraphMatchConstraint.hpp"
#include "CDPL/Chem/AtomMatchConstraint.hpp"
#include "CDPL/Chem/BondMatchConstraint.hpp"
#include "CDPL/Chem/ReactionFunctions.hpp"
#include "CDPL/Chem/AtomContainerFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/BondDirection.hpp"
#include "CDPL/Chem/ReactionRole.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/HybridizationState.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Base/DataIOBase.hpp"

#include "SMARTSDataReader.hpp"
#include "SMARTSData.hpp"


using namespace CDPL;


namespace
{

	const Chem::SMARTSDataReader::BondList NO_BONDS;
}


bool Chem::SMARTSDataReader::readReaction(std::istream& is, Reaction& rxn)
{
	if (!hasMoreData(is))
		return false;

	if (!(is >> rxnSMARTSString)) 
		throw Base::IOError("SMARTSDataReader: reading of reaction SMARTS string failed");

	strictErrorChecking = getStrictErrorCheckingParameter(ioBase);
	atomMappingIDOffset = getMaxAtomMappingID(rxn);

	bool have_aam_ids = false;
	bool have_comp_groups = false;

	typedef boost::tokenizer<boost::char_separator<char> > Tokenizer;

	const char role_sep[] = { SMARTS::REACTION_ROLE_SEPARATOR, 0 };
	const char comp_sep[] = { SMARTS::COMPONENT_SEPARATOR, 0 };

	unsigned int rxn_role = ReactionRole::REACTANT;

	Tokenizer rxn_tokenizer(rxnSMARTSString, boost::char_separator<char>(role_sep, "", boost::keep_empty_tokens));

	for (Tokenizer::iterator t_it1 = rxn_tokenizer.begin(); t_it1 != rxn_tokenizer.end(); ) {
		Tokenizer comp_tokenizer(*t_it1, boost::char_separator<char>(comp_sep, ""));

		std::size_t open_branch_cnt = 0;

		for (Tokenizer::iterator t_it2 = comp_tokenizer.begin(); t_it2 != comp_tokenizer.end(); ) {
			const std::string& comp_str = *t_it2;

			if (open_branch_cnt == 0)
				molSMARTSString.clear();

			std::string::const_iterator comp_str_end = comp_str.end();

			for (std::string::const_iterator c_it = comp_str.begin(); c_it != comp_str_end; ++c_it) {
				switch (*c_it) {
					
					case SMARTS::GROUPING_PREFIX:
						open_branch_cnt++;
						continue;

					case SMARTS::GROUPING_SUFFIX:
						if (open_branch_cnt > 0)
							open_branch_cnt--;

					default:
						continue;
				}
			}

			if (!molSMARTSString.empty())
				molSMARTSString.push_back(SMARTS::COMPONENT_SEPARATOR);

			molSMARTSString.append(comp_str);

			if (++t_it2 != comp_tokenizer.end() && open_branch_cnt > 0)  
				continue;

			Molecule& comp = rxn.addComponent(rxn_role);

			init(comp);
	
			parseSMARTS(comp, 0);
	
			setAtomStereoDescriptors(comp);
			addBondConfigurationConstraints(comp);
			setMoleculeMatchConstraints(comp);

			have_aam_ids |= haveRxnAtomMappingIDs;
			have_comp_groups |= haveComponentGroups;
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
					throw Base::IOError("SMARTSDataReader: invalid reaction SMARTS format");
				
				rxn_role = ReactionRole::PRODUCT;
				t_it1 = rxn_tokenizer.end();
				break;
		}
	}

	if (rxn_role != ReactionRole::PRODUCT)
		throw Base::IOError("SMARTSDataReader: unexpected end of input");

	if (have_aam_ids || have_comp_groups) {
		MatchConstraintList::SharedPointer new_list(new MatchConstraintList());

		if (have_comp_groups)
			new_list->addElement(ReactionMatchConstraint::COMPONENT_GROUPING, MatchConstraint::EQUAL);

		if (have_aam_ids)
			new_list->addElement(ReactionMatchConstraint::ATOM_MAPPING, MatchConstraint::EQUAL);

		if (hasMatchConstraints(rxn)) {
			MatchConstraintList::SharedPointer old_list = getMatchConstraints(rxn);

			if (old_list->getSize() > 0)
				new_list->addElement(ReactionMatchConstraint::CONSTRAINT_LIST, MatchConstraint::EQUAL, old_list);
		}

		setMatchConstraints(rxn, new_list);
	}

	return true;
}

bool Chem::SMARTSDataReader::skipReaction(std::istream& is)
{
	if (!hasMoreData(is))
		return false;

	if (!(is >> rxnSMARTSString)) 
		throw Base::IOError("SMARTSDataReader: reading of reaction SMARTS string failed");

	return true;
}

bool Chem::SMARTSDataReader::readMolecule(std::istream& is, Molecule& mol)
{
	if (!hasMoreData(is))
		return false;

	if (!(is >> molSMARTSString)) 
		throw Base::IOError("SMARTSDataReader: reading of molecule SMARTS string failed");

	strictErrorChecking = getStrictErrorCheckingParameter(ioBase);
	atomMappingIDOffset = getMaxAtomMappingID(mol);

	init(mol);
	
	parseSMARTS(mol, 0);

	setAtomStereoDescriptors(mol);
	addBondConfigurationConstraints(mol);
	setMoleculeMatchConstraints(mol);

	return true;
}

bool Chem::SMARTSDataReader::skipMolecule(std::istream& is)
{
	if (!hasMoreData(is))
		return false;

	if (!(is >> molSMARTSString)) 
		throw Base::IOError("SMARTSDataReader: reading of molecule SMARTS string failed");

	return true;
}

bool Chem::SMARTSDataReader::hasMoreData(std::istream& is) const
{
	is.imbue(std::locale::classic());

	return bool(std::istream::sentry(is, false));
}

void Chem::SMARTSDataReader::init(const Molecule& mol)
{
	nextCharIndex = 0;
	openBranchCount = 0;
	lexicalBondNumber = 0;
	startAtomIndex = mol.getNumAtoms();
	startBondIndex = mol.getNumBonds();

	bondTable.clear();
	closureBondMap.clear();
	nbrBondListTable.assign(nbrBondListTable.size(), BondList());

	haveRxnAtomMappingIDs = false;
	haveComponentGroups = false;

	componentGroupID = getMaxComponentGroupID(mol);
}

void Chem::SMARTSDataReader::setMoleculeMatchConstraints(Molecule& mol) const
{
	if (!haveComponentGroups)
		return;

	MatchConstraintList::SharedPointer new_list(new MatchConstraintList);

	new_list->addElement(MolecularGraphMatchConstraint::COMPONENT_GROUPING, MatchConstraint::EQUAL);

	if (hasMatchConstraints(mol)) {
		MatchConstraintList::SharedPointer old_list = getMatchConstraints(mol);

		if (old_list->getSize() > 0)
			new_list->addElement(MolecularGraphMatchConstraint::CONSTRAINT_LIST, MatchConstraint::EQUAL, old_list);
	}

	setMatchConstraints(mol, new_list);
}

void Chem::SMARTSDataReader::parseSMARTS(Molecule& mol, const Atom* prev_atom)
{
	char c;

	if (!getChar(c, true)) {
		ungetChar();

		if (strictErrorChecking) {
			if (!closureBondMap.empty())
				throw Base::IOError("SMARTSDataReader: pending ring closures");

			if (openBranchCount != 0)
				throw Base::IOError("SMARTSDataReader: branch parentheses not balanced");
		}

		return;
	}

	switch (c) {

		case SMARTS::COMPONENT_SEPARATOR:
			parseSMARTS(mol, 0);
			return;

		case SMARTS::GROUPING_PREFIX:
			if (!prev_atom && openBranchCount == 0)
				componentGroupID++;

			openBranchCount++;

			parseSMARTS(mol, prev_atom);
			parseSMARTS(mol, prev_atom);
			return;

		case SMARTS::GROUPING_SUFFIX:
			if (openBranchCount == 0)
				throw Base::IOError("SMARTSDataReader: branch parentheses not balanced");

			openBranchCount--;
			return;

		default:
			break;
	}

	ungetChar();

	const Atom* next_atom;

	if (prev_atom) {
		MatchConstraintList::SharedPointer constr_list = parseBondExpression();

		next_atom = parseAtom(mol);

		createBond(mol, prev_atom, next_atom, constr_list, lexicalBondNumber);

		addToBondList(mol.getAtomIndex(*prev_atom), lexicalBondNumber);
		addToBondList(mol.getAtomIndex(*next_atom), lexicalBondNumber++, false);

	} else
		next_atom = parseAtom(mol);

	parseSMARTS(mol, next_atom);
}

void Chem::SMARTSDataReader::parseRingClosures(Molecule& mol, const Atom& atom)
{
	std::size_t saved_char_idx = nextCharIndex;
	MatchConstraintList::SharedPointer constr_list;

	while (hasNextChar()) {
		constr_list = parseBondExpression();
		
		std::size_t closure_no;
		char c;

		getChar(c, false);

		if (c != SMARTS::CLOSURE_NO_PREFIX) {
			if (!std::isdigit(c, std::locale::classic())) {
				nextCharIndex = saved_char_idx;
				return;
			}

			closure_no = c - '0';
			
		} else if (!parseNumber(closure_no, 2))
			throw Base::IOError("SMARTSDataReader: invalid ring closure bond number format");

		saved_char_idx = nextCharIndex;

		ClosureBondMap::iterator lb = closureBondMap.lower_bound(closure_no);

		if (lb != closureBondMap.end() && !(closureBondMap.key_comp()(closure_no, lb->first))) {
			const ClosureBond& closure_bond = lb->second;

			if (strictErrorChecking && closure_bond.startAtom == &atom)
				throw Base::IOError("SMARTSDataReader: trying to connect atom with itself");

			constr_list = combineBondMatchConstraints(constr_list, closure_bond.matchConstraints);

			createBond(mol, closure_bond.startAtom, &atom, constr_list, closure_bond.lexBondNumber);
			
			addToBondList(mol.getAtomIndex(atom), closure_bond.lexBondNumber);
		
			closureBondMap.erase(lb);

		} else {      // create a new map item for a future ring closure
			closureBondMap.insert(lb, 
								  ClosureBondMap::value_type(closure_no, ClosureBond(lexicalBondNumber, &atom, constr_list)));

			addToBondList(mol.getAtomIndex(atom), lexicalBondNumber++);
		}
	}
}

Chem::MatchConstraintList::SharedPointer 
Chem::SMARTSDataReader::combineBondMatchConstraints(const MatchConstraintList::SharedPointer& constr_list1, 
													const MatchConstraintList::SharedPointer& constr_list2) const
{
	if (!constr_list1 || constr_list1->getSize() == 0)
		return constr_list2;

	if (!constr_list2 || constr_list2->getSize() == 0)
		return constr_list1;

	if (constr_list1->getType() == MatchConstraintList::AND_LIST) {
		if (constr_list2->getType() == MatchConstraintList::AND_LIST) {
			std::for_each(constr_list2->getElementsBegin(), constr_list2->getElementsEnd(),
						  boost::bind(&Util::Array<MatchConstraint>::addElement, constr_list1, _1));

			return constr_list1;
		}

		constr_list1->addElement(BondMatchConstraint::CONSTRAINT_LIST,
								 MatchConstraint::EQUAL,
								 constr_list2);
		return constr_list1;

	} 

	if (constr_list2->getType() == MatchConstraintList::AND_LIST) {
		constr_list2->addElement(BondMatchConstraint::CONSTRAINT_LIST,
								 MatchConstraint::EQUAL,
								 constr_list1);
		return constr_list2;
	}

	MatchConstraintList::SharedPointer constr_list3(new MatchConstraintList());

	constr_list3->addElement(BondMatchConstraint::CONSTRAINT_LIST,
							 MatchConstraint::EQUAL,
							 constr_list1);

	constr_list3->addElement(BondMatchConstraint::CONSTRAINT_LIST,
							 MatchConstraint::EQUAL,
							 constr_list2);
	return constr_list3;
}

void Chem::SMARTSDataReader::createBond(Molecule& mol, const Atom* atom1, const Atom* atom2,
										MatchConstraintList::SharedPointer& constr_list, std::size_t lex_bond_no)
{
	assert(atom1 != 0 && atom2 != 0);

	if (!constr_list || constr_list->getSize() == 0) {
		constr_list.reset(new MatchConstraintList(MatchConstraintList::OR_LIST));

		constr_list->addElement(BondMatchConstraint::ORDER, 
								MatchConstraint::EQUAL,
								BondMatchConstraint::SINGLE | BondMatchConstraint::AROMATIC);
	}

	std::size_t atom1_idx = mol.getAtomIndex(*atom1);
	std::size_t atom2_idx = mol.getAtomIndex(*atom2);

	Bond& bond = mol.addBond(atom1_idx, atom2_idx);

	setMatchConstraints(bond, constr_list);

	setBondTableEntry(lex_bond_no, &bond);
}

Chem::MatchConstraintList::SharedPointer Chem::SMARTSDataReader::parseBondExpression()
{
	if (!hasNextChar())
		return MatchConstraintList::SharedPointer();

	return parseBondExpression(0);
}

Chem::MatchConstraintList::SharedPointer Chem::SMARTSDataReader::parseBondExpression(std::size_t state)
{
	MatchConstraintList::SharedPointer constr_list;
	MatchConstraintList::SharedPointer child_constr_list;

	char c;
	bool op_seen = false;

	switch (state) {

		case 0:
			while (true) {
				if (!(child_constr_list = parseBondExpression(1))) {
					if (op_seen && strictErrorChecking)
						throw Base::IOError("SMARTSDataReader: bond expression primitive missing");

					getChar(c, false);
					
					if (c == SMARTS::LOW_PRECED_AND_OPERATOR) {
						if (!constr_list && strictErrorChecking)
							throw Base::IOError("SMARTSDataReader: bond expression primitive missing");

						op_seen = true;
						continue;
					}

					ungetChar();

					if (constr_list && constr_list->getSize() == 1)
						return constr_list->getFirstElement().getValue<MatchConstraintList::SharedPointer>();

					return constr_list;
				}

				if (!constr_list)
					constr_list.reset(new MatchConstraintList());

				constr_list->addElement(AtomMatchConstraint::CONSTRAINT_LIST,
										MatchConstraint::EQUAL,
										child_constr_list);
				op_seen = false;
			}

		case 1:
			while (true) {
				if (!(child_constr_list = parseBondExpression(2))) {
					if (op_seen && strictErrorChecking)
						throw Base::IOError("SMARTSDataReader: bond expression primitive missing");

					getChar(c, false);
					
					if (c == SMARTS::OR_OPERATOR) {
						if (!constr_list && strictErrorChecking)
							throw Base::IOError("SMARTSDataReader: bond expression primitive missing");

						op_seen = true;
						continue;
					}

					ungetChar();

					if (constr_list && constr_list->getSize() == 1)
						return constr_list->getFirstElement().getValue<MatchConstraintList::SharedPointer>();

					return constr_list;
				}

				if (!constr_list)
					constr_list.reset(new MatchConstraintList(MatchConstraintList::OR_LIST));
	
				constr_list->addElement(AtomMatchConstraint::CONSTRAINT_LIST,
										MatchConstraint::EQUAL,
										child_constr_list);
				op_seen = false;
			}

		case 2:
			constr_list.reset(new MatchConstraintList());

			while (true) {
				if (!(parseBondExpressionPrimitive(*constr_list))) {
					if (op_seen && strictErrorChecking)
						throw Base::IOError("SMARTSDataReader: bond expression primitive missing");

					getChar(c, false);
					
					if (c == SMARTS::HI_PRECED_AND_OPERATOR) {
						if (constr_list->getSize() && strictErrorChecking)
							throw Base::IOError("SMARTSDataReader: bond expression primitive missing");

						op_seen = true;
						continue;
					}

					ungetChar();

					if (constr_list->getSize() == 0)
						return MatchConstraintList::SharedPointer();

					return constr_list;
				}

				op_seen = false;
			}

		default:
			assert(false);
	}

	return MatchConstraintList::SharedPointer();
}

bool Chem::SMARTSDataReader::parseBondExpressionPrimitive(MatchConstraintList& constr_list)
{
	using namespace SMARTS;

	std::size_t saved_char_idx = nextCharIndex;
	bool has_not_pfx = hasNOTOperatorPrefix();
	char c;

	getChar(c, false);

	switch (c) {

		case BondExpression::SINGLE_BOND:
			constr_list.addElement(BondMatchConstraint::ORDER,
								   has_not_pfx ? MatchConstraint::NOT_EQUAL : MatchConstraint::EQUAL,
								   BondMatchConstraint::SINGLE);
			return true;

		case BondExpression::DOUBLE_BOND:
			constr_list.addElement(BondMatchConstraint::ORDER,
								   has_not_pfx ? MatchConstraint::NOT_EQUAL : MatchConstraint::EQUAL,
								   BondMatchConstraint::DOUBLE);
			return true;

		case BondExpression::TRIPLE_BOND:
			constr_list.addElement(BondMatchConstraint::ORDER,
								   has_not_pfx ? MatchConstraint::NOT_EQUAL : MatchConstraint::EQUAL,
								   BondMatchConstraint::TRIPLE);
			return true;

		case BondExpression::AROMATIC_BOND:
			constr_list.addElement(BondMatchConstraint::AROMATICITY,
								   MatchConstraint::EQUAL,
								   !has_not_pfx);
			return true;

		case BondExpression::RING_BOND:
			constr_list.addElement(BondMatchConstraint::RING_TOPOLOGY,
								   MatchConstraint::EQUAL,
								   !has_not_pfx);
			return true;

		case BondExpression::ANY_BOND:
			constr_list.addElement(BondMatchConstraint::ORDER,
								   MatchConstraint::EQUAL,
								   BondMatchConstraint::ANY_ORDER);
			return true;

		case BondExpression::UP_DIR_FLAG:
			constr_list.addElement(BondMatchConstraint::DIRECTION,
								   MatchConstraint::EQUAL,
								   (has_not_pfx ? BondDirection::DOWN : BondDirection::UP) | 
								   (hasUnspecStereoSuffix() ? BondDirection::UNSPECIFIED : static_cast<unsigned int>(0)));
			return true;

		case BondExpression::DOWN_DIR_FLAG:
			constr_list.addElement(BondMatchConstraint::DIRECTION,
								   MatchConstraint::EQUAL,
								   (has_not_pfx ? BondDirection::DOWN : BondDirection::UP) | 
								   (hasUnspecStereoSuffix() ? BondDirection::UNSPECIFIED : static_cast<unsigned int>(0)));
			return true;

		default:
			break;
	}

	nextCharIndex = saved_char_idx;

	return false;
}

const Chem::Atom* Chem::SMARTSDataReader::parseAtom(Molecule& mol)
{
	Atom& atom = mol.addAtom();

	MatchConstraintList::SharedPointer constr_list = parseAtomExpression(atom);

	setComponentGroupID(atom);

	setMatchConstraints(atom, constr_list);

	parseRingClosures(mol, atom);

	return &atom;
}

void Chem::SMARTSDataReader::setComponentGroupID(Atom& atom)
{
	if (componentGroupID == 0)
		return;

	Chem::setComponentGroupID(atom, componentGroupID);

	haveComponentGroups = true;
}

Chem::MatchConstraintList::SharedPointer Chem::SMARTSDataReader::parseAtomExpression(Atom& atom)
{
	MatchConstraintList::SharedPointer constr_list;
	char c;

	getChar(c, false);

	if (c == SMARTS::AtomExpression::COMPLEX_EXPR_PREFIX) {
		if (!(constr_list = parseAtomExpression(0, atom)))
			throw Base::IOError("SMARTSDataReader: invalid atom expression");

	} else if (!(constr_list = parseSimpleAtomExpression(c))) 
		throw Base::IOError("SMARTSDataReader: invalid atom expression");

	return constr_list;
}

Chem::MatchConstraintList::SharedPointer Chem::SMARTSDataReader::parseAtomExpression(std::size_t state, Atom& atom)
{
	MatchConstraintList::SharedPointer child_constr_list;
	MatchConstraintList::SharedPointer constr_list;

	char c;
	bool op_seen = false;

	switch (state) {

		case 0:
			if ((constr_list = parseExplicitHAtomExpression(atom)))
				return constr_list;

			while (true) {
				if (!(child_constr_list = parseAtomExpression(1, atom))) {
					if (op_seen && strictErrorChecking)
						throw Base::IOError("SMARTSDataReader: atom expression primitive missing");

					getChar(c, false);
					
					if (c == SMARTS::LOW_PRECED_AND_OPERATOR) {
						if (!constr_list && strictErrorChecking)
							throw Base::IOError("SMARTSDataReader: atom expression primitive missing");

						op_seen = true;
						continue;
					}

					using namespace SMARTS;

					if (c == AtomExpression::ATOM_MAPPING_ID_PREFIX) {
						if (!constr_list) {
							constr_list.reset(new MatchConstraintList());

							addAtomTypeConstraint(AtomType::A, false, *constr_list);
						}

						parseReactionAtomMappingID(atom);

						getChar(c, false);
					}

					if (c != AtomExpression::COMPLEX_EXPR_SUFFIX)
						throw Base::IOError("SMARTSDataReader: invalid atom expression - missing closing bracket");

					if (constr_list && constr_list->getSize() == 1)
						return constr_list->getFirstElement().getValue<MatchConstraintList::SharedPointer>();

					return constr_list;
				}

				if (!constr_list)
					constr_list.reset(new MatchConstraintList());

				constr_list->addElement(AtomMatchConstraint::CONSTRAINT_LIST,
										MatchConstraint::EQUAL,
										child_constr_list);

				op_seen = false;
			}

		case 1:
			while (true) {
				if (!(child_constr_list = parseAtomExpression(2, atom))) {
					if (op_seen && strictErrorChecking)
						throw Base::IOError("SMARTSDataReader: atom expression primitive missing");

					getChar(c, false);
					
					if (c == SMARTS::OR_OPERATOR) {
						if (!constr_list && strictErrorChecking)
							throw Base::IOError("SMARTSDataReader: atom expression primitive missing");

						op_seen = true;
						continue;
					}

					ungetChar();

					if (constr_list && constr_list->getSize() == 1)
						return constr_list->getFirstElement().getValue<MatchConstraintList::SharedPointer>();

					return constr_list;
				}

				if (!constr_list)
					constr_list.reset(new MatchConstraintList(MatchConstraintList::OR_LIST));

				constr_list->addElement(AtomMatchConstraint::CONSTRAINT_LIST,
										MatchConstraint::EQUAL,
										child_constr_list);
				op_seen = false;
			}

		case 2:
			constr_list.reset(new MatchConstraintList());

			while (true) {
				if (!(parseAtomExpressionPrimitive(*constr_list))) {
					if (op_seen && strictErrorChecking)
						throw Base::IOError("SMARTSDataReader: atom expression primitive missing");

					getChar(c, false);

					if (c == SMARTS::HI_PRECED_AND_OPERATOR) {
						if (constr_list->getSize() == 0 && strictErrorChecking)
							throw Base::IOError("SMARTSDataReader: atom expression primitive missing");

						op_seen = true;
						continue;
					}

					ungetChar();

					if (constr_list->getSize() == 0)
						return MatchConstraintList::SharedPointer();

					return constr_list;
				}

				op_seen = false;
			}

		default:
			assert(false);
	}

	return MatchConstraintList::SharedPointer();
}

Chem::MatchConstraintList::SharedPointer Chem::SMARTSDataReader::parseExplicitHAtomExpression(Atom& atom)
{
	using namespace SMARTS;

	std::size_t saved_char_idx = nextCharIndex;
	char c;

	getChar(c, false);

	MatchConstraintList::SharedPointer constr_list(new MatchConstraintList());

	if (std::isdigit(c, std::locale::classic())) {
		addIsotopeConstraint(c, false, *constr_list);

		getChar(c, false);

		if (c == HI_PRECED_AND_OPERATOR || c == LOW_PRECED_AND_OPERATOR)
			getChar(c, false);
	}

	if (c != 'H') {
		nextCharIndex = saved_char_idx;

		return MatchConstraintList::SharedPointer();
	}

	addAtomTypeConstraint(AtomType::H, false, false, *constr_list);

	getChar(c, false);

	if (c == HI_PRECED_AND_OPERATOR || c == LOW_PRECED_AND_OPERATOR)
		getChar(c, false);

	if (c == AtomExpression::POSITIVE_CHARGE_PREFIX || c == AtomExpression::NEGATIVE_CHARGE_PREFIX) {
		addChargeConstraint(c, false, *constr_list);

		getChar(c, false);
	}

	if (c == AtomExpression::ATOM_MAPPING_ID_PREFIX) {
		parseReactionAtomMappingID(atom);

		getChar(c, false);
	}

	if (c == AtomExpression::COMPLEX_EXPR_SUFFIX) 
		return constr_list;

	nextCharIndex = saved_char_idx;
	
	return MatchConstraintList::SharedPointer();
}

Chem::MatchConstraintList::SharedPointer Chem::SMARTSDataReader::parseSimpleAtomExpression(char c)
{
	using namespace SMARTS;

	MatchConstraintList::SharedPointer constr_list(new MatchConstraintList());

	switch (c) {
		
		case AtomExpression::ANY_ATOM:
			addAtomTypeConstraint(AtomType::A, false, *constr_list);
			return constr_list;

		case AtomExpression::ANY_AROMATIC_ATOM:
			addAtomTypeConstraint(AtomType::A, true, false, *constr_list);
			return constr_list;

		case AtomExpression::ANY_NON_AROMATIC_ATOM:
			addAtomTypeConstraint(AtomType::A, false, false, *constr_list);
			return constr_list;

		case 'c':
			addAtomTypeConstraint(AtomType::C, true, false, *constr_list);
			return constr_list;

		case 'n':
			addAtomTypeConstraint(AtomType::N, true, false, *constr_list);
			return constr_list;

		case 'o':
			addAtomTypeConstraint(AtomType::O, true, false, *constr_list);
			return constr_list;

		case 's':
			addAtomTypeConstraint(AtomType::S, true, false, *constr_list);
			return constr_list;

		case 'p':
			addAtomTypeConstraint(AtomType::P, true, false, *constr_list);
			return constr_list;

		case 'C':
			if (getChar(c, true) && c == 'l') {
				addAtomTypeConstraint(AtomType::Cl, false, false, *constr_list);
				return constr_list;
			}

			ungetChar();
				
			addAtomTypeConstraint(AtomType::C, false, false, *constr_list);
			return constr_list;

		case 'N':
			addAtomTypeConstraint(AtomType::N, false, false, *constr_list);
			return constr_list;

		case 'O':
			addAtomTypeConstraint(AtomType::O, false, false, *constr_list);
			return constr_list;

		case 'S':
			addAtomTypeConstraint(AtomType::S, false, false, *constr_list);
			return constr_list;

		case 'P':	
			addAtomTypeConstraint(AtomType::P, false, false, *constr_list);
			return constr_list;

		case 'B':
			if (getChar(c, true) && c == 'r') {
				addAtomTypeConstraint(AtomType::Br, false, false, *constr_list);
				return constr_list;
			}

			ungetChar();

			addAtomTypeConstraint(AtomType::B, false, false, *constr_list);
			return constr_list;

		case 'F':
			addAtomTypeConstraint(AtomType::F, false, false, *constr_list);
			return constr_list;

		case 'I':
			addAtomTypeConstraint(AtomType::I, false, false, *constr_list);
			return constr_list;

		default:
			break;
	}

	return MatchConstraintList::SharedPointer();
}

bool Chem::SMARTSDataReader::parseAtomExpressionPrimitive(MatchConstraintList& constr_list)
{
	using namespace SMARTS;

	std::size_t saved_char_idx = nextCharIndex;
	bool has_not_pfx = hasNOTOperatorPrefix();
	char c;

	getChar(c, false);

	if (std::isdigit(c, std::locale::classic())) {
		addIsotopeConstraint(c, has_not_pfx, constr_list);

		return true;
	}

	switch (c) {
		
		case AtomExpression::RECURSIVE_SMARTS_PREFIX:
			return addEnvironmentConstraint(has_not_pfx, constr_list);

		case AtomExpression::ATOMIC_NUMBER_PREFIX:
			return addAtomicNumberConstraint(has_not_pfx, constr_list);

		case AtomExpression::IMPLICIT_H_COUNT_PREFIX:
			return addImplicitHCountConstraint(has_not_pfx, constr_list);

		case AtomExpression::RING_SIZE_PREFIX:
			return addRingSizeConstraint(has_not_pfx, constr_list);

		case AtomExpression::VALENCE_PREFIX:
			return addValenceConstraint(has_not_pfx, constr_list);

		case AtomExpression::UNSATURATED_FLAG:
			return addUnsaturationConstraint(has_not_pfx, constr_list);

		case AtomExpression::RING_CONNECTIVITY_PREFIX:
			return addRingConnectivityConstraint(has_not_pfx, constr_list);

		case AtomExpression::HYBRIDIZATION_PREFIX:
			return addHybridizationStateConstraint(has_not_pfx, constr_list);

		case AtomExpression::POSITIVE_CHARGE_PREFIX:
		case AtomExpression::NEGATIVE_CHARGE_PREFIX:
			return addChargeConstraint(c, has_not_pfx, constr_list);

		case AtomExpression::CHIRAL_CLASS_PREFIX:
			return addChiralityConstraint(has_not_pfx, constr_list);

		case AtomExpression::ANY_ATOM:
			return addAtomTypeConstraint(AtomType::A, has_not_pfx, constr_list);

		case AtomExpression::ANY_AROMATIC_ATOM:
			if (getChar(c, false) && c == 's') 
				return addAtomTypeConstraint(AtomType::As, true, has_not_pfx, constr_list);

			ungetChar();

			return addAtomTypeConstraint(AtomType::A, true, has_not_pfx, constr_list);

		case AtomExpression::ANY_NON_AROMATIC_ATOM:
			getChar(c, false);

			switch (c) {

				case 'c':
					return addAtomTypeConstraint(AtomType::Ac, false, has_not_pfx, constr_list);

				case 'g':
					return addAtomTypeConstraint(AtomType::Ag, false, has_not_pfx, constr_list);

				case 'l':
					return addAtomTypeConstraint(AtomType::Al, false, has_not_pfx, constr_list);

				case 'm':
					return addAtomTypeConstraint(AtomType::Am, false, has_not_pfx, constr_list);

				case 'r':
					return addAtomTypeConstraint(AtomType::Ar, false, has_not_pfx, constr_list);

				case 's':
					return addAtomTypeConstraint(AtomType::As, false, has_not_pfx, constr_list);

				case 't':
					return addAtomTypeConstraint(AtomType::At, false, has_not_pfx, constr_list);

				case 'u':
					return addAtomTypeConstraint(AtomType::Au, false, has_not_pfx, constr_list);

				default:
					break;
			}

			ungetChar();

			return addAtomTypeConstraint(AtomType::A, false, has_not_pfx, constr_list);

		case AtomExpression::EXPLICIT_DEGREE_PREFIX:
			if (getChar(c, false) && c == 'y')
				return addAtomTypeConstraint(AtomType::Dy, false, has_not_pfx, constr_list);

			ungetChar();

			return addExplicitDegreeConstraint(has_not_pfx, constr_list);

		case AtomExpression::TOTAL_H_COUNT_PREFIX:
			getChar(c, false);

			switch (c) {

				case'e':
					return addAtomTypeConstraint(AtomType::He, false, has_not_pfx, constr_list);

				case 'f':
					return addAtomTypeConstraint(AtomType::Hf, false, has_not_pfx, constr_list);

				case 'g':
					return addAtomTypeConstraint(AtomType::Hg, false, has_not_pfx, constr_list);

				case 'o':
					return addAtomTypeConstraint(AtomType::Ho, false, has_not_pfx, constr_list);

				default:
					break;
			}

			ungetChar();

			return addTotalHCountConstraint(has_not_pfx, constr_list);

		case AtomExpression::RING_MEMBERSHIP_PREFIX:
			getChar(c, false);

			switch (c) {

				case 'a':
					return addAtomTypeConstraint(AtomType::Ra, false, has_not_pfx, constr_list);

				case 'b':
					return addAtomTypeConstraint(AtomType::Rb, false, has_not_pfx, constr_list);

				case 'e':
					return addAtomTypeConstraint(AtomType::Re, false, has_not_pfx, constr_list);

				case 'h':
					return addAtomTypeConstraint(AtomType::Rh, false, has_not_pfx, constr_list);

				case 'n':
					return addAtomTypeConstraint(AtomType::Rn, false, has_not_pfx, constr_list);

				case 'u':
					return addAtomTypeConstraint(AtomType::Ru, false, has_not_pfx, constr_list);

				default:
					break;
			}

			ungetChar();

			return addRingMembershipConstraint(has_not_pfx, constr_list);

		case AtomExpression::CONNECTIVITY_PREFIX:
			if (getChar(c, false) && c == 'e')
				return addAtomTypeConstraint(AtomType::Xe, false, has_not_pfx, constr_list);

			ungetChar();

			return addConnectivityConstraint(has_not_pfx, constr_list);

		case 'B':
			getChar(c, false);

			switch (c) {
			
				case 'a':
					return addAtomTypeConstraint(AtomType::Ba, false, has_not_pfx, constr_list);

				case 'e':
					return addAtomTypeConstraint(AtomType::Be, false, has_not_pfx, constr_list);

				case 'i':
					return addAtomTypeConstraint(AtomType::Bi, false, has_not_pfx, constr_list);

				case 'k':
					return addAtomTypeConstraint(AtomType::Bk, false, has_not_pfx, constr_list);

				case 'r':
					return addAtomTypeConstraint(AtomType::Br, false, has_not_pfx, constr_list);

				default:
					break;
			}

			ungetChar();

			return addAtomTypeConstraint(AtomType::B, false, has_not_pfx, constr_list);

		case 'C':
			getChar(c, false);

			switch (c) {
			
				case 'a':
					return addAtomTypeConstraint(AtomType::Ca, false, has_not_pfx, constr_list);

				case 'd':
					return addAtomTypeConstraint(AtomType::Cd, false, has_not_pfx, constr_list);

				case 'e':
					return addAtomTypeConstraint(AtomType::Ce, false, has_not_pfx, constr_list);

				case 'f':
					return addAtomTypeConstraint(AtomType::Cf, false, has_not_pfx, constr_list);

				case 'l':
					return addAtomTypeConstraint(AtomType::Cl, false, has_not_pfx, constr_list);

				case 'm':
					return addAtomTypeConstraint(AtomType::Cm, false, has_not_pfx, constr_list);

				case 'o':
					return addAtomTypeConstraint(AtomType::Co, false, has_not_pfx, constr_list);

				case 'r':
					return addAtomTypeConstraint(AtomType::Cr, false, has_not_pfx, constr_list);

				case 's':
					return addAtomTypeConstraint(AtomType::Cs, false, has_not_pfx, constr_list);

				case 'u':
					return addAtomTypeConstraint(AtomType::Cu, false, has_not_pfx, constr_list);
		
				default:
					break;
			}

			ungetChar();
				
			return addAtomTypeConstraint(AtomType::C, false, has_not_pfx, constr_list);

		case 'E':
			getChar(c, false);

			switch (c) {

				case 'r':
					return addAtomTypeConstraint(AtomType::Er, false, has_not_pfx, constr_list);

				case 's':
					return addAtomTypeConstraint(AtomType::Es, false, has_not_pfx, constr_list);

				case 'u':
					return addAtomTypeConstraint(AtomType::Eu, false, has_not_pfx, constr_list);
   	
				default:
					break;
			}

			break;

		case 'F':
			getChar(c, false);

			switch (c) {

				case 'e':
					return addAtomTypeConstraint(AtomType::Fe, false, has_not_pfx, constr_list);

				case 'm':
					return addAtomTypeConstraint(AtomType::Fm, false, has_not_pfx, constr_list);

				case 'r':
					return addAtomTypeConstraint(AtomType::Fr, false, has_not_pfx, constr_list);

				default:
					break;
			}

			ungetChar();

			return addAtomTypeConstraint(AtomType::F, false, has_not_pfx, constr_list);

		case 'G':
			getChar(c, false);
			
			switch (c) {

				case 'a':
					return addAtomTypeConstraint(AtomType::Ga, false, has_not_pfx, constr_list);

				case 'd':
					return addAtomTypeConstraint(AtomType::Gd, false, has_not_pfx, constr_list);

				case 'e':
					return addAtomTypeConstraint(AtomType::Ge, false, has_not_pfx, constr_list);
  
				default:
					break;
			}

			break;

		case 'I':
			getChar(c, false);

			switch (c) {
				
				case 'n':
					return addAtomTypeConstraint(AtomType::In, false, has_not_pfx, constr_list);

				case 'r':
					return addAtomTypeConstraint(AtomType::Ir, false, has_not_pfx, constr_list);
  
				default:
					break;
			}

			ungetChar();

			return addAtomTypeConstraint(AtomType::I, false, has_not_pfx, constr_list);

		case 'K':
			if (getChar(c, false) && c == 'r')
				return addAtomTypeConstraint(AtomType::Kr, false, has_not_pfx, constr_list);

			ungetChar();

			return addAtomTypeConstraint(AtomType::K, false, has_not_pfx, constr_list);

		case 'L':
			getChar(c, false);

			switch (c) {
				
				case 'a':
					return addAtomTypeConstraint(AtomType::La, false, has_not_pfx, constr_list);

				case 'i':
					return addAtomTypeConstraint(AtomType::Li, false, has_not_pfx, constr_list);

				case 'r':
					return addAtomTypeConstraint(AtomType::Lr, false, has_not_pfx, constr_list);

				case 'u':
					return addAtomTypeConstraint(AtomType::Lu, false, has_not_pfx, constr_list);
    
				default:
					break;
			}

			break;

		case 'M':
			getChar(c, false);

			switch (c) {

				case 'd':
					return addAtomTypeConstraint(AtomType::Md, false, has_not_pfx, constr_list);

				case 'g':
					return addAtomTypeConstraint(AtomType::Mg, false, has_not_pfx, constr_list);

				case 'n':
					return addAtomTypeConstraint(AtomType::Mn, false, has_not_pfx, constr_list);

				case 'o':
					return addAtomTypeConstraint(AtomType::Mo, false, has_not_pfx, constr_list);

				default:
					break;
			}

			break;

		case 'N':
			getChar(c, false);
			
			switch (c) {

				case 'a':
					return addAtomTypeConstraint(AtomType::Na, false, has_not_pfx, constr_list);

				case 'b':
					return addAtomTypeConstraint(AtomType::Nb, false, has_not_pfx, constr_list);

				case 'd':
					return addAtomTypeConstraint(AtomType::Nd, false, has_not_pfx, constr_list);

				case 'e':
					return addAtomTypeConstraint(AtomType::Ne, false, has_not_pfx, constr_list);

				case 'i':
					return addAtomTypeConstraint(AtomType::Ni, false, has_not_pfx, constr_list);

				case 'o':
					return addAtomTypeConstraint(AtomType::No, false, has_not_pfx, constr_list);

				case 'p':
					return addAtomTypeConstraint(AtomType::Np, false, has_not_pfx, constr_list);

				default:
					break;
			}

			ungetChar();

			return addAtomTypeConstraint(AtomType::N, false, has_not_pfx, constr_list);

		case 'O':
			if (getChar(c, false) && c == 's')
				return addAtomTypeConstraint(AtomType::Os, false, has_not_pfx, constr_list);

			ungetChar();

			return addAtomTypeConstraint(AtomType::O, false, has_not_pfx, constr_list);

		case 'P':
			getChar(c, false);

			switch (c) {
				
				case 'a':
					return addAtomTypeConstraint(AtomType::Pa, false, has_not_pfx, constr_list);

				case 'b':
					return addAtomTypeConstraint(AtomType::Pb, false, has_not_pfx, constr_list);

				case 'd':
					return addAtomTypeConstraint(AtomType::Pd, false, has_not_pfx, constr_list);

				case 'm':
					return addAtomTypeConstraint(AtomType::Pm, false, has_not_pfx, constr_list);

				case 'o':
					return addAtomTypeConstraint(AtomType::Po, false, has_not_pfx, constr_list);

				case 'r':
					return addAtomTypeConstraint(AtomType::Pr, false, has_not_pfx, constr_list);

				case 't':
					return addAtomTypeConstraint(AtomType::Pt, false, has_not_pfx, constr_list);

				case 'u':
					return addAtomTypeConstraint(AtomType::Pu, false, has_not_pfx, constr_list);
  
				default:
					break;
			}

			ungetChar();

			return addAtomTypeConstraint(AtomType::P, false, has_not_pfx, constr_list);

		case 'S':
			getChar(c, false);

			switch (c) {
				
				case 'b':
					return addAtomTypeConstraint(AtomType::Sb, false, has_not_pfx, constr_list);

				case 'c':
					return addAtomTypeConstraint(AtomType::Sc, false, has_not_pfx, constr_list);

				case 'e':
					return addAtomTypeConstraint(AtomType::Se, false, has_not_pfx, constr_list);

				case 'i':
					return addAtomTypeConstraint(AtomType::Si, false, has_not_pfx, constr_list);

				case 'm':
					return addAtomTypeConstraint(AtomType::Sm, false, has_not_pfx, constr_list);

				case 'n':
					return addAtomTypeConstraint(AtomType::Sn, false, has_not_pfx, constr_list);

				case 'r':
					return addAtomTypeConstraint(AtomType::Sr, false, has_not_pfx, constr_list);

				default:
					break;
			}

			ungetChar();

			return addAtomTypeConstraint(AtomType::S, false, has_not_pfx, constr_list);

		case 'T':
			getChar(c, false);

			switch (c) {
				
				case 'a':
					return addAtomTypeConstraint(AtomType::Ta, false, has_not_pfx, constr_list);

				case 'b':
					return addAtomTypeConstraint(AtomType::Tb, false, has_not_pfx, constr_list);

				case 'c':
					return addAtomTypeConstraint(AtomType::Tc, false, has_not_pfx, constr_list);

				case 'e':
					return addAtomTypeConstraint(AtomType::Te, false, has_not_pfx, constr_list);

				case 'h':
					return addAtomTypeConstraint(AtomType::Th, false, has_not_pfx, constr_list);

				case 'i':
					return addAtomTypeConstraint(AtomType::Ti, false, has_not_pfx, constr_list);

				case 'l':
					return addAtomTypeConstraint(AtomType::Tl, false, has_not_pfx, constr_list);

				case 'm':
					return addAtomTypeConstraint(AtomType::Tm, false, has_not_pfx, constr_list);

				default:
					break;
			}

			break;

		case 'U':
			return addAtomTypeConstraint(AtomType::U, false, has_not_pfx, constr_list);

		case 'V':
			return addAtomTypeConstraint(AtomType::V, false, has_not_pfx, constr_list);

		case 'W':
			return addAtomTypeConstraint(AtomType::W, false, has_not_pfx, constr_list);

		case 'Y':
			if (getChar(c, false) && c == 'b')
				return addAtomTypeConstraint(AtomType::Yb, false, has_not_pfx, constr_list);

			ungetChar();

			return addAtomTypeConstraint(AtomType::Y, false, has_not_pfx, constr_list);

		case 'Z':
			getChar(c, false);

			switch (c) {

				case 'n':
					return addAtomTypeConstraint(AtomType::Zn, false, has_not_pfx, constr_list);

				case 'r':
					return addAtomTypeConstraint(AtomType::Zr, false, has_not_pfx, constr_list);

				default:
					break;
			}

			break;

		case 'c':
			return addAtomTypeConstraint(AtomType::C, true, has_not_pfx, constr_list);

		case 'n':
			return addAtomTypeConstraint(AtomType::N, true, has_not_pfx, constr_list);

		case 'o':
			return addAtomTypeConstraint(AtomType::O, true, has_not_pfx, constr_list);

		case 's':
			if (getChar(c, false) && c == 'e') 
				return addAtomTypeConstraint(AtomType::Se, true, has_not_pfx, constr_list);

			ungetChar();

			return addAtomTypeConstraint(AtomType::S, true, has_not_pfx, constr_list);

		case 't':
			if (getChar(c, false) && c == 'e') 
				return addAtomTypeConstraint(AtomType::Te, true, has_not_pfx, constr_list);

			break;

		case 'p':
			return addAtomTypeConstraint(AtomType::P, true, has_not_pfx, constr_list);

		default:
			break;
	}

	nextCharIndex = saved_char_idx;

	return false;
}

bool Chem::SMARTSDataReader::addEnvironmentConstraint(bool has_not_pfx, MatchConstraintList& constr_list)
{
	using namespace SMARTS;

	char c;

	getChar(c, false);

	if (c != AtomExpression::RECURSIVE_SMARTS_BEGIN)
		throw Base::IOError("SMARTSDataReader: missing recursive smarts start delimiter");

	std::string smarts_str;
	std::size_t paren_count = 1;

	while (getChar(c, false)) {
		switch (c) {
	
			case SMARTS::GROUPING_SUFFIX:
				if (--paren_count == 0)
					break;
				
				smarts_str.push_back(c);
				continue;
			
			case SMARTS::GROUPING_PREFIX:
				paren_count++;

			default:
				smarts_str.push_back(c);
				continue;
		}

		break;
	}

	constr_list.addElement(AtomMatchConstraint::ENVIRONMENT,
						   has_not_pfx ? MatchConstraint::NOT_EQUAL : MatchConstraint::EQUAL,
						   parseSMARTS(smarts_str));

	return true;	
}

bool Chem::SMARTSDataReader::addAtomicNumberConstraint(bool has_not_pfx, MatchConstraintList& constr_list)
{
	unsigned int atomic_no;

	if (!parseNumber(atomic_no))
		throw Base::IOError("SMARTSDataReader: missing atomic number");

	constr_list.addElement(AtomMatchConstraint::TYPE,
						   has_not_pfx ? MatchConstraint::NOT_EQUAL : MatchConstraint::EQUAL,
						   atomic_no);
	return true;	
}

bool Chem::SMARTSDataReader::addImplicitHCountConstraint(bool has_not_pfx, MatchConstraintList& constr_list)
{
	std::size_t h_count = 1;

	parseNumber(h_count);

	constr_list.addElement(AtomMatchConstraint::IMPLICIT_H_COUNT,
						   has_not_pfx ? MatchConstraint::NOT_EQUAL : MatchConstraint::EQUAL,
						   h_count);
	return true;	
}

bool Chem::SMARTSDataReader::addTotalHCountConstraint(bool has_not_pfx, MatchConstraintList& constr_list)
{
	std::size_t h_count = 1;

	parseNumber(h_count);

	constr_list.addElement(AtomMatchConstraint::H_COUNT,
						   has_not_pfx ? MatchConstraint::NOT_EQUAL : MatchConstraint::EQUAL,
						   h_count);
	return true;
}

bool Chem::SMARTSDataReader::addRingSizeConstraint(bool has_not_pfx, MatchConstraintList& constr_list)
{
	std::size_t ring_size;

	if (parseNumber(ring_size)) 
		constr_list.addElement(AtomMatchConstraint::SSSR_RING_SIZE,
							   has_not_pfx ? MatchConstraint::NOT_EQUAL : MatchConstraint::EQUAL,
							   ring_size);
	else
		constr_list.addElement(AtomMatchConstraint::RING_TOPOLOGY,
							   has_not_pfx ? MatchConstraint::NOT_EQUAL : MatchConstraint::EQUAL,
							   true);
	return true;
}

bool Chem::SMARTSDataReader::addRingMembershipConstraint(bool has_not_pfx, MatchConstraintList& constr_list)
{
	std::size_t num_rings;

	if (parseNumber(num_rings)) 
		constr_list.addElement(AtomMatchConstraint::SSSR_RING_COUNT,
							   has_not_pfx ? MatchConstraint::NOT_EQUAL : MatchConstraint::EQUAL,
							   num_rings);
	else
		constr_list.addElement(AtomMatchConstraint::RING_TOPOLOGY,
							   has_not_pfx ? MatchConstraint::NOT_EQUAL : MatchConstraint::EQUAL,
							   true);
	return true;
}

bool Chem::SMARTSDataReader::addUnsaturationConstraint(bool has_not_pfx, MatchConstraintList& constr_list)
{
	constr_list.addElement(AtomMatchConstraint::UNSATURATION,
						   has_not_pfx ? MatchConstraint::NOT_EQUAL : MatchConstraint::EQUAL,
						   true);
	return true;
}

bool Chem::SMARTSDataReader::addHybridizationStateConstraint(bool has_not_pfx, MatchConstraintList& constr_list)
{
	std::size_t hyb_id;

	if (!parseNumber(hyb_id))
		throw Base::IOError("SMARTSDataReader: invalid hybridization state specification");

	unsigned int hyb_state;

	switch (hyb_id) {
		
		case 1:
			hyb_state = HybridizationState::SP;
			break;

		case 2:
			hyb_state = HybridizationState::SP2;
			break;

		case 3:
			hyb_state = HybridizationState::SP3;
			break;
		
		default:
			throw Base::IOError("SMARTSDataReader: invalid hybridization state specification");
	}

	constr_list.addElement(AtomMatchConstraint::HYBRIDIZATION_STATE,
						   has_not_pfx ? MatchConstraint::NOT_EQUAL : MatchConstraint::EQUAL,
						   hyb_state);
	return true;
}

bool Chem::SMARTSDataReader::addValenceConstraint(bool has_not_pfx, MatchConstraintList& constr_list)
{
	std::size_t valence = 1;

	parseNumber(valence);

	constr_list.addElement(AtomMatchConstraint::VALENCE,
						   has_not_pfx ? MatchConstraint::NOT_EQUAL : MatchConstraint::EQUAL,
						   valence);
	return true;
}

bool Chem::SMARTSDataReader::addExplicitDegreeConstraint(bool has_not_pfx, MatchConstraintList& constr_list)
{
	std::size_t num_expl_bonds = 1;

	parseNumber(num_expl_bonds);

	constr_list.addElement(AtomMatchConstraint::EXPLICIT_BOND_COUNT,
						   has_not_pfx ? MatchConstraint::NOT_EQUAL : MatchConstraint::EQUAL,
						   num_expl_bonds);
	return true;
}

bool Chem::SMARTSDataReader::addConnectivityConstraint(bool has_not_pfx, MatchConstraintList& constr_list)
{
	std::size_t num_bonds = 1;

	parseNumber(num_bonds);

	constr_list.addElement(AtomMatchConstraint::BOND_COUNT,
						   has_not_pfx ? MatchConstraint::NOT_EQUAL : MatchConstraint::EQUAL,
						   num_bonds);
	return true;
}

bool Chem::SMARTSDataReader::addRingConnectivityConstraint(bool has_not_pfx, MatchConstraintList& constr_list)
{
	std::size_t num_ring_bonds;

	if (parseNumber(num_ring_bonds)) 
		constr_list.addElement(AtomMatchConstraint::RING_BOND_COUNT,
							   has_not_pfx ? MatchConstraint::NOT_EQUAL : MatchConstraint::EQUAL,
							   num_ring_bonds);
	else 
		constr_list.addElement(AtomMatchConstraint::RING_TOPOLOGY,
							   has_not_pfx ? MatchConstraint::NOT_EQUAL : MatchConstraint::EQUAL,
							   true);
	return true;
}

bool Chem::SMARTSDataReader::addChargeConstraint(char c, bool has_not_pfx, MatchConstraintList& constr_list)
{
	using namespace SMARTS;

	long charge = 0;

	for (bool exit = false; !exit; getChar(c, false)) {
		long sign;

		switch (c) {

			case AtomExpression::POSITIVE_CHARGE_PREFIX:
				sign = 1;
				break;

			case AtomExpression::NEGATIVE_CHARGE_PREFIX:
				sign = -1;
				break;

			default:
				exit = true;
				break;
		}

		if (exit)
			break;

		std::size_t count = 1;

		parseNumber(count);

		charge += sign * count;
	}

	ungetChar();

	constr_list.addElement(AtomMatchConstraint::CHARGE,
						   has_not_pfx ? MatchConstraint::NOT_EQUAL : MatchConstraint::EQUAL,
						   charge);
	return true;
}

bool Chem::SMARTSDataReader::addChiralityConstraint(bool has_not_pfx, MatchConstraintList& constr_list)
{
	using namespace SMARTS;

	unsigned int perm_desig = 1;
	char c;

	for ( ; getChar(c, false) && c == AtomExpression::CHIRAL_CLASS_PREFIX; perm_desig++);

	ungetChar();

	if (perm_desig == 1 && !parseNumber(perm_desig)) {
		std::string class_type(' ', 2);

		getChar(class_type[0], false);

		if (c == AtomExpression::TETRAHEDRAL_CHIRALITY[0] 
			|| c == AtomExpression::ALLENE_TYPE_CHIRALITY[0]
			|| c == AtomExpression::SQUARE_PLANAR_CHIRALITY[0]
			|| c == AtomExpression::TRIG_BIPYR_CHIRALITY[0]
			|| c == AtomExpression::OCTAHEDRAL_CHIRALITY[0]) {
	
			getChar(class_type[1], false);

			bool supported_class = false;

			if (class_type == AtomExpression::TETRAHEDRAL_CHIRALITY)
				supported_class = true;

			else if (strictErrorChecking 
					 && class_type != AtomExpression::ALLENE_TYPE_CHIRALITY
					 && class_type != AtomExpression::SQUARE_PLANAR_CHIRALITY
					 && class_type != AtomExpression::TRIG_BIPYR_CHIRALITY
					 && class_type != AtomExpression::OCTAHEDRAL_CHIRALITY)

				throw Base::IOError("SMARTSDataReader: specification for unknown chiral class");

			parseNumber(perm_desig);

			if (!supported_class)
				perm_desig = 0;

		} else
			ungetChar();
	}

	if (perm_desig == 0) {
		constr_list.addElement(AtomMatchConstraint::CONFIGURATION, 
							   MatchConstraint::EQUAL,
							   static_cast<unsigned int>(0));
		return true;
	}

	if ((perm_desig % 2) != 0)
		perm_desig = (has_not_pfx ? AtomConfiguration::S : AtomConfiguration::R);
	else
		perm_desig = (has_not_pfx ? AtomConfiguration::R : AtomConfiguration::S);

	if (hasUnspecStereoSuffix())
		perm_desig |= AtomConfiguration::EITHER;

	constr_list.addElement(AtomMatchConstraint::CONFIGURATION, 
						   MatchConstraint::EQUAL,
						   perm_desig);
	return true;
}

bool Chem::SMARTSDataReader::addIsotopeConstraint(char c, bool has_not_pfx, MatchConstraintList& constr_list) 
{
	std::size_t isotope = c - '0';

	while (getChar(c, false) && std::isdigit(c, std::locale::classic())) 
		isotope = isotope * 10 + (c - '0');

	ungetChar();

	constr_list.addElement(AtomMatchConstraint::ISOTOPE,
						   has_not_pfx ? MatchConstraint::NOT_EQUAL : MatchConstraint::EQUAL,
						   isotope);
	return true;
}

bool Chem::SMARTSDataReader::addAtomTypeConstraint(unsigned int atom_type, bool has_not_pfx, MatchConstraintList& constr_list)
{
	constr_list.addElement(AtomMatchConstraint::TYPE, 
						   has_not_pfx ? MatchConstraint::NOT_EQUAL : MatchConstraint::EQUAL,
						   atom_type);
	return true;
}

bool Chem::SMARTSDataReader::addAtomTypeConstraint(unsigned int atom_type, bool aromatic, bool has_not_pfx, 
												   MatchConstraintList& constr_list)
{
	if (atom_type == AtomType::A) {
		constr_list.addElement(AtomMatchConstraint::AROMATICITY, 
							   has_not_pfx ? MatchConstraint::NOT_EQUAL : MatchConstraint::EQUAL,
							   aromatic);
		return true;
	}
	
	if (has_not_pfx) {
		MatchConstraintList::SharedPointer or_list_constr(new MatchConstraintList(MatchConstraintList::OR_LIST));

		or_list_constr->addElement(AtomMatchConstraint::TYPE, 
								   MatchConstraint::NOT_EQUAL,
								   atom_type);
		or_list_constr->addElement(AtomMatchConstraint::AROMATICITY, 
								   MatchConstraint::NOT_EQUAL,
								   aromatic);

		constr_list.addElement(AtomMatchConstraint::CONSTRAINT_LIST,
							   MatchConstraint::EQUAL,
							   or_list_constr);
		return true;
	}

	constr_list.addElement(AtomMatchConstraint::TYPE, 
						   MatchConstraint::EQUAL,
						   atom_type);
	constr_list.addElement(AtomMatchConstraint::AROMATICITY, 
						   MatchConstraint::EQUAL,
						   aromatic);
	return true;
}

void Chem::SMARTSDataReader::parseReactionAtomMappingID(Atom& atom)
{
	std::size_t aam_id;

	if (!parseNumber(aam_id)) 
		throw Base::IOError("SMARTSDataReader: invalid or missing reaction atom atom mapping class number");

	if (aam_id > 0)
		setAtomMappingID(atom, aam_id + atomMappingIDOffset);

	hasUnspecStereoSuffix();

	haveRxnAtomMappingIDs = true;
}

Chem::Molecule::SharedPointer Chem::SMARTSDataReader::parseSMARTS(const std::string& rec_smarts_str)
{
	if (!smartsParser) 
		smartsParser.reset(new SMARTSDataReader(ioBase), boost::bind(&SMARTSDataReader::destroySMARTSParser, this, _1));

	Molecule::SharedPointer mol_ptr(new BasicMolecule());

	Molecule& mol = *mol_ptr;

	smartsParser->strictErrorChecking = strictErrorChecking;
	smartsParser->molSMARTSString = rec_smarts_str;

	smartsParser->init(mol);

	smartsParser->parseSMARTS(mol, 0);
	smartsParser->setAtomStereoDescriptors(mol);
	smartsParser->addBondConfigurationConstraints(mol);
	smartsParser->setMoleculeMatchConstraints(mol);

	initSubstructureSearchQuery(mol, true);

	return mol_ptr;
}

bool Chem::SMARTSDataReader::hasNOTOperatorPrefix()
{
	bool has_not_op = false;

	for (char c; getChar(c, false) && c == SMARTS::NOT_OPERATOR; has_not_op = !has_not_op); 

	ungetChar();

	return has_not_op;
}

bool Chem::SMARTSDataReader::hasUnspecStereoSuffix()
{
	char c;
	
	getChar(c, false);

	if (c == SMARTS::UNSPEC_STEREO_SUFFIX)
		return true;

	ungetChar();

	return false;
}

template <typename T>
bool Chem::SMARTSDataReader::parseNumber(T& value, std::size_t max_digits)
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

bool Chem::SMARTSDataReader::hasNextChar() const
{
	return (nextCharIndex < molSMARTSString.length());
}

bool Chem::SMARTSDataReader::getChar(char& c, bool eos_allowed)
{
	if (!hasNextChar()) {
		if (!eos_allowed)
			throw Base::IOError("SMARTSDataReader: unexpected end of input");

		nextCharIndex++;

		c = 0;
		return false;
	}

	c = molSMARTSString[nextCharIndex++];

	return true;
}

void Chem::SMARTSDataReader::ungetChar()
{
	assert(nextCharIndex > 0);

	nextCharIndex--;
}

void Chem::SMARTSDataReader::setBondTableEntry(std::size_t bond_no, const Bond* bond)
{
	if (bondTable.size() < bond_no + 1)
		bondTable.resize(bond_no + 1);

	bondTable[bond_no] = bond;
}

void Chem::SMARTSDataReader::addToBondList(std::size_t atom_idx, std::size_t bond_no, bool at_tail)
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

const Chem::SMARTSDataReader::BondList& Chem::SMARTSDataReader::getBondList(std::size_t atom_idx) const
{
	assert(atom_idx >= startAtomIndex);

	std::size_t tab_index = atom_idx - startAtomIndex;

	if (tab_index >= nbrBondListTable.size())
		return NO_BONDS;
   
	return nbrBondListTable[tab_index];
}

void Chem::SMARTSDataReader::setAtomStereoDescriptors(const Molecule& mol) const
{
	Molecule::ConstAtomIterator atoms_end = mol.getAtomsEnd();

	for (Molecule::ConstAtomIterator it = mol.getAtomsBegin() + startAtomIndex; it != atoms_end; ++it)
		setAtomStereoDescriptors(mol, *it, *getMatchConstraints(*it));
}

void Chem::SMARTSDataReader::setAtomStereoDescriptors(const Molecule& mol, const Atom& atom, MatchConstraintList& constr_list) const
{
	MatchConstraintList::ElementIterator constr_end = constr_list.getElementsEnd();

	for (MatchConstraintList::ElementIterator it = constr_list.getElementsBegin(); it != constr_end; ++it) {
		MatchConstraint& constraint = *it;

		if (constraint.getID() == AtomMatchConstraint::CONFIGURATION)
			setAtomStereoDescriptor(mol, atom, constraint);

		else if (constraint.getID() == AtomMatchConstraint::CONSTRAINT_LIST)
			setAtomStereoDescriptors(mol, atom, *constraint.getValue<MatchConstraintList::SharedPointer>());
	}
}

void Chem::SMARTSDataReader::setAtomStereoDescriptor(const Molecule& mol, const Atom& atom, MatchConstraint& constraint) const
{
	unsigned int perm_desig = constraint.getValue<unsigned int>();
				
	if (perm_desig == 0) {
		constraint.setValue(StereoDescriptor(0));
		return;
	}

	bool has_either_config = ((perm_desig & AtomConfiguration::EITHER) != 0);
	unsigned int config = perm_desig & (AtomConfiguration::S | AtomConfiguration::R);

	assert(config == AtomConfiguration::S || config == AtomConfiguration::R);

	std::size_t atom_idx = mol.getAtomIndex(atom);
	std::size_t num_bonds = atom.getNumBonds();
	const BondList& lex_bond_list = getBondList(atom_idx);

	assert(num_bonds == lex_bond_list.size());

	if (num_bonds < 3 || num_bonds > 4) {
		constraint.setValue(StereoDescriptor(0));
		return;
	}

	const Atom* ref_atoms[4];

	if (num_bonds == 4) {
		for (std::size_t i = 1; i <= 4; i++) {
			std::size_t lex_bond_no = lex_bond_list[i % 4];
			
			assert(lex_bond_no < bondTable.size());

			ref_atoms[i - 1] = &bondTable[lex_bond_no]->getNeighbor(atom);
		}

		std::size_t lex_bond_no = lex_bond_list[0];
		
		assert(lex_bond_no < bondTable.size());

		ref_atoms[3] = &bondTable[lex_bond_no]->getNeighbor(atom);

	} else {
		if (std::find_if(atom.getAtomsBegin(), atom.getAtomsEnd(), 
						 boost::bind(std::less<std::size_t>(), 
									 boost::bind(&Molecule::getAtomIndex, boost::ref(mol), _1),
									 atom_idx)) != atom.getAtomsEnd()) { // the chiral atom is not the very first one

			config = (config == AtomConfiguration::S ? config == AtomConfiguration::R : AtomConfiguration::S);
		} 

		for (std::size_t i = 0; i < 3; i++) {
			std::size_t lex_bond_no = lex_bond_list[i];
			
			assert(lex_bond_no < bondTable.size());

			ref_atoms[i] = &bondTable[lex_bond_no]->getNeighbor(atom);
		}
	}

	if (has_either_config)
		config |= AtomConfiguration::EITHER;

	if (num_bonds == 3)
		constraint.setValue(StereoDescriptor(config, *ref_atoms[0], *ref_atoms[1], *ref_atoms[2]));
	else
		constraint.setValue(StereoDescriptor(config, *ref_atoms[0], *ref_atoms[1], *ref_atoms[2], *ref_atoms[3]));
}

void Chem::SMARTSDataReader::addBondConfigurationConstraints(Molecule& mol) const
{
	Molecule::BondIterator bonds_end = mol.getBondsEnd();

	for (Molecule::BondIterator b_it1 = mol.getBondsBegin() + startBondIndex; b_it1 != bonds_end; ++b_it1) {
		Bond& bond = *b_it1;
		const Atom* atoms[2] = { &bond.getBegin(), &bond.getEnd() };

		std::size_t num_nbrs = atoms[0]->getNumBonds();

		if (num_nbrs < 2 || num_nbrs > 3)
			continue;

		num_nbrs = atoms[1]->getNumBonds();

		if (num_nbrs < 2 || num_nbrs > 3)
			continue;

		bool add_dir_geom_constr = true;

		for (std::size_t i = 0; i < 2; i++) {
			Atom::ConstBondIterator nbr_bonds_end = atoms[i]->getBondsEnd();			
			bool found_dir_constr = false;

			for (Atom::ConstBondIterator b_it2 = atoms[i]->getBondsBegin(); b_it2 != nbr_bonds_end; ++b_it2) {
				const Bond& nbr_bond = *b_it2;

				if (&nbr_bond == &bond)
					continue;

				if (hasBondDirectionConstraint(*getMatchConstraints(nbr_bond))) {
					found_dir_constr = true;
					break;
				}
			} 

			if (!found_dir_constr) {
				add_dir_geom_constr = false;				
				break;
			}
		}

		if (!add_dir_geom_constr)
			continue;

		const MatchConstraintList::SharedPointer& constr_list = getMatchConstraints(bond);

		if (constr_list->getType() == MatchConstraintList::AND_LIST) {
			constr_list->addElement(BondMatchConstraint::DIRECTION_CONFIG,
									MatchConstraint::EQUAL);
			continue;
		}

		MatchConstraintList::SharedPointer new_constr_list(new MatchConstraintList());

		new_constr_list->addElement(BondMatchConstraint::CONSTRAINT_LIST,
									MatchConstraint::EQUAL,
									constr_list);

		new_constr_list->addElement(BondMatchConstraint::DIRECTION_CONFIG,
									MatchConstraint::EQUAL);

		setMatchConstraints(bond, new_constr_list);
	}
}

bool Chem::SMARTSDataReader::hasBondDirectionConstraint(const MatchConstraintList& constr_list) const
{
	MatchConstraintList::ConstElementIterator constr_end = constr_list.getElementsEnd();

	for (MatchConstraintList::ConstElementIterator it = constr_list.getElementsBegin(); it != constr_end; ++it) {
		const MatchConstraint& constraint = *it;

		if (constraint.getID() == BondMatchConstraint::DIRECTION)
			return true;

		if (constraint.getID() == BondMatchConstraint::CONSTRAINT_LIST &&
			hasBondDirectionConstraint(*constraint.getValue<MatchConstraintList::SharedPointer>()))
			return true;
	}

	return false;
}

void Chem::SMARTSDataReader::destroySMARTSParser(SMARTSDataReader* parser) const
{
	delete parser;
}
