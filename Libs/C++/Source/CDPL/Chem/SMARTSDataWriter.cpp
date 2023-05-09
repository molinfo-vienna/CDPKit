/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SMARTSDataWriter.cpp 
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

#include <ostream>
#include <locale>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <cassert>

#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/AtomMatchConstraint.hpp"
#include "CDPL/Chem/BondMatchConstraint.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/HybridizationState.hpp"
#include "CDPL/Chem/ReactionRole.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/BondDirection.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Base/DataIOBase.hpp"
#include "CDPL/Internal/AtomFunctions.hpp"

#include "SMARTSDataWriter.hpp"
#include "SMARTSData.hpp"


using namespace CDPL;


namespace 
{
	
	const Chem::MatchConstraint* findMatchConstraint(const Chem::MatchConstraintList& constr_list,
													 unsigned int constr_id, 
													 Chem::MatchConstraint::Relation relation)
	{
		using namespace Chem;

		MatchConstraintList::ConstElementIterator constr_end = constr_list.getElementsEnd();
				
		for (MatchConstraintList::ConstElementIterator it = constr_list.getElementsBegin(); it != constr_end; ++it) {
			const MatchConstraint& constraint = *it;

			if (constraint.getID() == constr_id && constraint.getRelation() == relation)
				return &constraint;
		}

		return 0;
	}

	bool isANDMatchConstraintList(const Chem::MatchConstraintList& constr_list)
	{
		return (constr_list.getType() == Chem::MatchConstraintList::AND_LIST ||
				(constr_list.getType() == Chem::MatchConstraintList::OR_LIST && constr_list.getSize() <= 1));
	}

	bool isORMatchConstraintList(const Chem::MatchConstraintList& constr_list)
	{
		return (constr_list.getType() == Chem::MatchConstraintList::OR_LIST ||
				(constr_list.getType() == Chem::MatchConstraintList::AND_LIST && constr_list.getSize() <= 1));
	}

	template <typename ValueType, typename ObjectType>
	ValueType getConstraintValue(const Chem::MatchConstraint& constraint, 
								 const ObjectType& obj,
								 ValueType (*propFunc)(const ObjectType&))
	{
		if (constraint.hasValue())
			return constraint.template getValue<ValueType>();

		return propFunc(obj);
	}

	template <typename ValueType, typename ObjectType>
	ValueType getConstraintValue(const Chem::MatchConstraint& constraint, 
								 const ObjectType& obj,
								 const Chem::MolecularGraph& molgraph,
								 ValueType (*propFunc)(const ObjectType&, const Chem::MolecularGraph&))
	{
		if (constraint.hasValue())
			return constraint.template getValue<ValueType>();

		return propFunc(obj, molgraph);
	}

	std::size_t calcTotalHydrogenCount(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph) 
	{
		return Internal::getAtomCount(atom, molgraph, Chem::AtomType::H);
	}

	Chem::StereoDescriptor calcStereoDescriptor(const Chem::Atom& atom, const Chem::MolecularGraph& molgraph) 
	{
		return calcStereoDescriptor(atom, molgraph, 0);
	}

	const std::size_t MAX_NODE_CACHE_SIZE = 1000;
	const std::size_t MAX_EDGE_CACHE_SIZE = 1000;
}


Chem::SMARTSDataWriter::SMARTSDataWriter(const Base::DataIOBase& io_base): 
	ioBase(io_base), nodeCache(boost::bind(&SMARTSDataWriter::createNode, this), NodeCache::DefaultDestructor(), MAX_NODE_CACHE_SIZE),
	edgeCache(boost::bind(&SMARTSDataWriter::createEdge, this), EdgeCache::DefaultDestructor(), MAX_EDGE_CACHE_SIZE)
{}

bool Chem::SMARTSDataWriter::writeReaction(std::ostream& os, const Reaction& rxn)
{
	strictErrorChecking = getStrictErrorCheckingParameter(ioBase);

	os.imbue(std::locale::classic());

	os << std::dec;
	
	if (os.tellp() > 0)
		os << getRecordSeparatorParameter(ioBase);

	bool first_comp = true;
	Reaction::ConstComponentIterator comps_end = rxn.getComponentsEnd(ReactionRole::REACTANT);

	for (Reaction::ConstComponentIterator it = rxn.getComponentsBegin(ReactionRole::REACTANT); it != comps_end; ++it) {
		const Molecule& comp = *it;

		if (comp.getNumAtoms() == 0)
			continue;

		if (!first_comp)
			os << SMARTS::COMPONENT_SEPARATOR;

		writeMolGraph(os, comp, true);

		first_comp = false;
	}

	os << SMARTS::REACTION_ROLE_SEPARATOR;

	first_comp = true;
	comps_end = rxn.getComponentsEnd(ReactionRole::AGENT);

	for (Reaction::ConstComponentIterator it = rxn.getComponentsBegin(ReactionRole::AGENT); it != comps_end; ++it) {
		const Molecule& comp = *it;

		if (comp.getNumAtoms() == 0)
			continue;

		if (!first_comp)
			os << SMARTS::COMPONENT_SEPARATOR;

		writeMolGraph(os, comp, true);

		first_comp = false;
	}

	os << SMARTS::REACTION_ROLE_SEPARATOR;

	first_comp = true;
	comps_end = rxn.getComponentsEnd(ReactionRole::PRODUCT);

	for (Reaction::ConstComponentIterator it = rxn.getComponentsBegin(ReactionRole::PRODUCT); it != comps_end; ++it) {
		const Molecule& comp = *it;

		if (comp.getNumAtoms() == 0)
			continue;

		if (!first_comp)
			os << SMARTS::COMPONENT_SEPARATOR;

		writeMolGraph(os, comp, true);

		first_comp = false;
	}

	return os.good();
}

bool Chem::SMARTSDataWriter::writeMolGraph(std::ostream& os, const MolecularGraph& molgraph, bool rxn_context)
{
	if (!rxn_context) {
		strictErrorChecking = getStrictErrorCheckingParameter(ioBase);

		os.imbue(std::locale::classic());

		os << std::dec;

		if (os.tellp() > 0)
			os << getRecordSeparatorParameter(ioBase);
	}

	bool first_comp = true;

	if (hasComponentGroups(molgraph)) {
		const FragmentList& comp_groups = *getComponentGroups(molgraph);
		FragmentList::ConstElementIterator comp_groups_end = comp_groups.getElementsEnd();

		for (FragmentList::ConstElementIterator cg_it = comp_groups.getElementsBegin(); cg_it != comp_groups_end; ++cg_it) {
			const Fragment& comp_grp = *cg_it;
			bool write_grp_prefix = true;

			FragmentList::SharedPointer grp_comps_ptr = perceiveComponents(comp_grp);
			FragmentList::ConstElementIterator comps_end = grp_comps_ptr->getElementsEnd();

			for (FragmentList::ConstElementIterator it = grp_comps_ptr->getElementsBegin(); it != comps_end; ++it) {
				const Fragment& comp = *it;
	
				if (comp.getNumAtoms() == 0)
					continue;

				if (!first_comp)
					os << SMARTS::COMPONENT_SEPARATOR;

				if (write_grp_prefix) {
					os << SMARTS::GROUPING_PREFIX;
					write_grp_prefix = false;
				}

				writeComponent(os, comp);
				first_comp = false;
			}

			if (!write_grp_prefix)
				os << SMARTS::GROUPING_SUFFIX;
		}

		const FragmentList& components = *getComponents(molgraph);
		FragmentList::ConstElementIterator comps_end = components.getElementsEnd();

		for (FragmentList::ConstElementIterator it = components.getElementsBegin(); it != comps_end; ++it) {
			const Fragment& comp = *it;
	
			if (comp.getNumAtoms() == 0)
				continue;
			
			if (std::find_if(comp.getAtomsBegin(), comp.getAtomsEnd(),
							 boost::bind(std::not_equal_to<std::size_t>(), 0, 
										 boost::bind(&getComponentGroupID, _1))) != comp.getAtomsEnd())
				continue;

			if (!first_comp)
				os << SMARTS::COMPONENT_SEPARATOR;

			writeComponent(os, comp);
			first_comp = false;
		}

		return os.good();
	}

	const FragmentList& components = *getComponents(molgraph);
	FragmentList::ConstElementIterator comps_end = components.getElementsEnd();

	for (FragmentList::ConstElementIterator it = components.getElementsBegin(); it != comps_end; ++it) {
		const Fragment& comp = *it;
	
		if (comp.getNumAtoms() == 0)
			continue;

		if (!first_comp)
			os << SMARTS::COMPONENT_SEPARATOR;

		writeComponent(os, comp);
		first_comp = false;
	}

	return os.good();
}

void Chem::SMARTSDataWriter::writeComponent(std::ostream& os, const MolecularGraph& molgraph)
{
	init();

	buildDFSTree(molgraph);
	distRingClosureNumbers();
	generateSMARTS(os);
}

void Chem::SMARTSDataWriter::init()
{
	ringClosureNumberStack.clear();
	componentNodes.clear();
	nodeCache.putAll();
	edgeCache.putAll();

	highestRingClosureNumber = 0;
}

void Chem::SMARTSDataWriter::buildDFSTree(const MolecularGraph& molgraph, DFSTreeNode* node)
{
	if (!node) {
		node = createRootNode(molgraph);
		atomNodeMapping.assign(molgraph.getNumAtoms(), 0);
	}

	std::size_t lex_order = componentNodes.size();

	node->setLexicalOrder(lex_order);

	const Atom* atom = node->getAtom();

	assert(atom != 0);

	atomNodeMapping[molgraph.getAtomIndex(*atom)] = node;

	Atom::ConstAtomIterator nbrs_end = atom->getAtomsEnd();
	Atom::ConstBondIterator b_it = atom->getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom->getAtomsBegin(); a_it != nbrs_end; ++a_it, ++b_it) {
		const Atom& nbr_atom = *a_it;
		const Bond& bond = *b_it;
	
		if (!molgraph.containsAtom(nbr_atom) || !molgraph.containsBond(bond))
			continue;

		DFSTreeNode* nbr_node = atomNodeMapping[molgraph.getAtomIndex(nbr_atom)];

		if (nbr_node) {           
			if (lex_order > nbr_node->getLexicalOrder() && nbr_node != node->getParentEdge()->getBegin()) { // ring closure
				DFSTreeEdge* edge = allocEdge();

				node->addRingClosureOutEdge(edge);
				nbr_node->addRingClosureInEdge(edge);

				edge->setBond(&bond);
				edge->setNodes(node, nbr_node);
				edge->setMolGraph(&molgraph);
			}

			continue;
		}

		nbr_node = allocNode();

		DFSTreeEdge* edge = allocEdge();

		edge->setBond(&bond);
		edge->setMolGraph(&molgraph);
		edge->setNodes(node, nbr_node);

		nbr_node->setAtom(&nbr_atom);
		nbr_node->setMolGraph(&molgraph);
		nbr_node->setParentEdge(edge);

		node->addChildEdge(edge);

		buildDFSTree(molgraph, nbr_node);
	}
}

Chem::SMARTSDataWriter::DFSTreeNode* Chem::SMARTSDataWriter::createRootNode(const MolecularGraph& molgraph)
{
	DFSTreeNode* root_node = allocNode();

	root_node->setAtom(&molgraph.getAtom(0));
	root_node->setMolGraph(&molgraph);
	root_node->setParentEdge(0);

	return root_node;
}

void Chem::SMARTSDataWriter::distRingClosureNumbers()
{
	NodeList::iterator nodes_end = componentNodes.end();

	for (NodeList::iterator it = componentNodes.begin(); it != nodes_end; ++it) {
		DFSTreeNode* node = *it;

		std::for_each(node->getRingClosureInEdgesBegin(), node->getRingClosureInEdgesEnd(),
					  boost::bind(&DFSTreeEdge::setRingClosureNumber, _1,
								  boost::bind(&SMARTSDataWriter::getRingClosureNumber, this)));

		std::for_each(node->getRingClosureOutEdgesBegin(), node->getRingClosureOutEdgesEnd(),
					  boost::bind(&SMARTSDataWriter::putRingClosureNumber, this,
								  boost::bind(&DFSTreeEdge::getRingClosureNumber, _1)));
	}
}

void Chem::SMARTSDataWriter::generateSMARTS(std::ostream& os) const
{
	componentNodes.front()->generateSMARTS(os);
}

std::size_t Chem::SMARTSDataWriter::getRingClosureNumber()
{
	if (ringClosureNumberStack.empty()) {
		if (highestRingClosureNumber == 99)
			throw Base::IOError("SMARTSDataWriter: ran out of ring closure numbers");

		return ++highestRingClosureNumber;
	}

	std::size_t top_no = ringClosureNumberStack.back();

	ringClosureNumberStack.pop_back();

	return top_no;
}

void Chem::SMARTSDataWriter::putRingClosureNumber(std::size_t no)
{
	ringClosureNumberStack.push_back(no);
}

Chem::SMARTSDataWriter::DFSTreeNode* Chem::SMARTSDataWriter::createNode()
{
	return new DFSTreeNode(*this);
}

Chem::SMARTSDataWriter::DFSTreeEdge* Chem::SMARTSDataWriter::createEdge()
{
	return new DFSTreeEdge(*this);
}

Chem::SMARTSDataWriter::DFSTreeNode* Chem::SMARTSDataWriter::allocNode()
{
	DFSTreeNode* node = nodeCache.getRaw();

	node->clear();
	componentNodes.push_back(node);

	return node;
}

Chem::SMARTSDataWriter::DFSTreeEdge* Chem::SMARTSDataWriter::allocEdge()
{
	return edgeCache.getRaw();
}

void Chem::SMARTSDataWriter::writeSMARTS(std::ostream& os, const MolecularGraph& molgraph)
{
	if (!smartsWriter) 
		smartsWriter.reset(new SMARTSDataWriter(ioBase), boost::bind(&SMARTSDataWriter::destroySMARTSWriter, this, _1));

	smartsWriter->writeMolGraph(os, molgraph);
}

void Chem::SMARTSDataWriter::destroySMARTSWriter(SMARTSDataWriter* writer) const
{
	delete writer;
}


// -------------------------

Chem::SMARTSDataWriter::DFSTreeNode::DFSTreeNode(SMARTSDataWriter& writer): 
	writer(writer), molGraph(0), atom(0), parentEdge(0)  {}

void Chem::SMARTSDataWriter::DFSTreeNode::clear()
{
	childEdges.clear();
	ringClosureInEdges.clear();
	ringClosureOutEdges.clear();
}
				
void Chem::SMARTSDataWriter::DFSTreeNode::setAtom(const Atom* atm)
{
	atom = atm;
}

const Chem::Atom* Chem::SMARTSDataWriter::DFSTreeNode::getAtom() const
{
	return atom;
}

void Chem::SMARTSDataWriter::DFSTreeNode::setMolGraph(const MolecularGraph* molgraph)
{
	molGraph = molgraph;
}

void Chem::SMARTSDataWriter::DFSTreeNode::setLexicalOrder(std::size_t order)
{
	lexicalOrder = order;
}

std::size_t Chem::SMARTSDataWriter::DFSTreeNode::getLexicalOrder() const
{
	return lexicalOrder;
}

void Chem::SMARTSDataWriter::DFSTreeNode::setParentEdge(DFSTreeEdge* edge)
{
	parentEdge = edge;
}

const Chem::SMARTSDataWriter::DFSTreeEdge* Chem::SMARTSDataWriter::DFSTreeNode::getParentEdge() const
{
	return parentEdge;
}

void Chem::SMARTSDataWriter::DFSTreeNode::addChildEdge(DFSTreeEdge* edge)
{
	childEdges.push_back(edge);
}

void Chem::SMARTSDataWriter::DFSTreeNode::addRingClosureInEdge(DFSTreeEdge* edge)
{
	ringClosureInEdges.push_back(edge);
}

void Chem::SMARTSDataWriter::DFSTreeNode::addRingClosureOutEdge(DFSTreeEdge* edge)
{
	ringClosureOutEdges.push_back(edge);
}

Chem::SMARTSDataWriter::EdgeIterator Chem::SMARTSDataWriter::DFSTreeNode::getRingClosureInEdgesBegin()
{
	return ringClosureInEdges.begin();
}

Chem::SMARTSDataWriter::EdgeIterator Chem::SMARTSDataWriter::DFSTreeNode::getRingClosureInEdgesEnd()
{
	return ringClosureInEdges.end();
}

Chem::SMARTSDataWriter::EdgeIterator Chem::SMARTSDataWriter::DFSTreeNode::getRingClosureOutEdgesBegin()
{
	return ringClosureOutEdges.begin();
}

Chem::SMARTSDataWriter::EdgeIterator Chem::SMARTSDataWriter::DFSTreeNode::getRingClosureOutEdgesEnd()
{
	return ringClosureOutEdges.end();
}

void Chem::SMARTSDataWriter::DFSTreeNode::generateSMARTS(std::ostream& os) const
{
	writeAtomExpression(os);
	writeRingClosures(os);
	writeChildNodeExpressions(os);
}

void Chem::SMARTSDataWriter::DFSTreeNode::writeAtomExpression(std::ostream& os) const
{
	using namespace SMARTS;

	const MatchConstraintList& constr_list = *getMatchConstraints(*atom);
	std::size_t aam_id = getAtomMappingID(*atom);

	if (aam_id == 0) {
		if (constr_list.getSize() == 0) {
			os << AtomExpression::ANY_ATOM;
			return;
		}

		if (writeSimpleAtomExpression(os, constr_list))
			return;

		std::string expr_string;

		writeComplexAtomExpression(constr_list, expr_string, 0);

		if (!expr_string.empty()) {
			os << AtomExpression::COMPLEX_EXPR_PREFIX
			   << expr_string
			   << AtomExpression::COMPLEX_EXPR_SUFFIX;
			
			return;
		}

		os << AtomExpression::ANY_ATOM;

	} else {
		os << AtomExpression::COMPLEX_EXPR_PREFIX;

		if (constr_list.getSize() > 0) {
			std::string expr_string;

			writeComplexAtomExpression(constr_list, expr_string, 0);

			if (!expr_string.empty())
				os << expr_string;
			else
				os << AtomExpression::ANY_ATOM;
		}

		writeReactionAtomMappingID(os, aam_id);

		os << AtomExpression::COMPLEX_EXPR_SUFFIX;
	}
}

bool Chem::SMARTSDataWriter::DFSTreeNode::writeSimpleAtomExpression(std::ostream& os,
																	const MatchConstraintList& constr_list) const
{
	using namespace SMARTS;

	if (constr_list.getSize() > 2)
		return false;

	if (!isANDMatchConstraintList(constr_list))
		return false;

	if (constr_list.getSize() == 1) {
		const MatchConstraint& constraint = constr_list.getFirstElement();
		
		if (constraint.getID() == AtomMatchConstraint::AROMATICITY) {
			bool write_arom_sym = getConstraintValue<bool>(constraint, *atom, &getAromaticityFlag);
			
			switch (constraint.getRelation()) {

				case MatchConstraint::EQUAL:
					break;

				case MatchConstraint::NOT_EQUAL:
					write_arom_sym = !write_arom_sym;
					break;
					
				default:
					return false;
			}

			os << (write_arom_sym ? AtomExpression::ANY_AROMATIC_ATOM : AtomExpression::ANY_NON_AROMATIC_ATOM);
			return true;
		}
		
		if (constraint.getID() == AtomMatchConstraint::TYPE && 
			constraint.getRelation() == MatchConstraint::EQUAL &&
			getConstraintValue<unsigned int>(constraint, *atom, &getType) == AtomType::A) {

			os << AtomExpression::ANY_ATOM;
			return true;
		}

		return false;
	}

	const MatchConstraint* arom_constraint = 
		findMatchConstraint(constr_list, AtomMatchConstraint::AROMATICITY, MatchConstraint::EQUAL);

	if (!arom_constraint)
		arom_constraint = 
			findMatchConstraint(constr_list, AtomMatchConstraint::AROMATICITY, MatchConstraint::NOT_EQUAL);

	if (!arom_constraint)
		return false;

	const MatchConstraint* type_constraint = 
		findMatchConstraint(constr_list, AtomMatchConstraint::TYPE, MatchConstraint::EQUAL);

	if (!type_constraint)
		return false;

	bool write_arom_sym = getConstraintValue<bool>(*arom_constraint, *atom, &getAromaticityFlag);

	if (arom_constraint->getRelation() == MatchConstraint::NOT_EQUAL)
		write_arom_sym = !write_arom_sym;

	switch (getConstraintValue<unsigned int>(*type_constraint, *atom, &getType)) {
		
		case AtomType::A:
			os << (write_arom_sym ?  AtomExpression::ANY_AROMATIC_ATOM : AtomExpression::ANY_NON_AROMATIC_ATOM);
			return true;
		
		case AtomType::C:
			os << (write_arom_sym ? 'c' : 'C');
			return true;

		case AtomType::N:
			os << (write_arom_sym ? 'n' : 'N');
			return true;

		case AtomType::O:
			os << (write_arom_sym ? 'o' : 'O');
			return true;

		case AtomType::S:
			os << (write_arom_sym ? 's' : 'S');
			return true;

		case AtomType::P:
			os << (write_arom_sym ? 'p' : 'P');
			return true;

		case AtomType::B:
			if (write_arom_sym)
				return false;

			os << 'B';
			return true;

		case AtomType::F:
			if (write_arom_sym)
				return false;

			os << 'F';
			return true;

		case AtomType::Cl:
			if (write_arom_sym)
				return false;

			os << "Cl";
			return true;
			
		case AtomType::Br:
			if (write_arom_sym)
				return false;

			os << "Br";
			return true;

		case AtomType::I:
			if (write_arom_sym)
				return false;

			os << 'I';
			return true;

		default:
			return false;
	}

	return false;
}

void Chem::SMARTSDataWriter::DFSTreeNode::writeComplexAtomExpression(const MatchConstraintList& constr_list,
																	 std::string& expr_list_str, std::size_t depth) const
{
	using namespace SMARTS;

	if (depth == 0) {
		if (writeAtomTypeExpression(constr_list, expr_list_str, true))
			return;

		switch (constr_list.getType()) {

			case MatchConstraintList::OR_LIST:
				depth = (constr_list.getSize() == 1 ? 1 : 2);
				break;

			case MatchConstraintList::AND_LIST:
				depth = 1;
				break;

			default:
				return;
		}
	}

	std::size_t list_size = 0;
	std::string expr_str;

	bool or_list = (constr_list.getType() == MatchConstraintList::OR_LIST);

	MatchConstraintList::ConstElementIterator constr_end = constr_list.getElementsEnd();

	for (MatchConstraintList::ConstElementIterator it = constr_list.getElementsBegin(); it != constr_end; ++it) {
		const MatchConstraint& constraint = *it;

		switch (constraint.getID()) {

			case AtomMatchConstraint::CONSTRAINT_LIST:
				writeExpressionList(constraint, expr_str, depth + 1);
				break;

			case AtomMatchConstraint::ENVIRONMENT:
				writeEnvironmentExpression(constraint, expr_str);
				break;

			case AtomMatchConstraint::TYPE:
				if (!or_list && (it + 1) != constr_end) {
					const MatchConstraint& next_constraint = *(it + 1);

					if (next_constraint.getID() == AtomMatchConstraint::AROMATICITY) {
						++it;
						writeAtomTypeExpression(&constraint, &next_constraint, expr_str, true);
						break;
					}
				}

				writeAtomTypeExpression(&constraint, static_cast<const MatchConstraint*>(0),
										expr_str, true);
				break;

			case AtomMatchConstraint::AROMATICITY:
				if (!or_list && (it + 1) != constr_end) {
					const MatchConstraint& next_constraint = *(it + 1);

					if (next_constraint.getID() == AtomMatchConstraint::TYPE) {
						++it;
						writeAtomTypeExpression(&next_constraint, &constraint, expr_str, false);
						break;
					}
				}
					
				writeAtomTypeExpression(static_cast<const MatchConstraint*>(0), &constraint, 
										expr_str, false);
				break;

			case AtomMatchConstraint::HYBRIDIZATION_STATE:
				writeHybridizationStateExpression(constraint, expr_str);
				break;

			case AtomMatchConstraint::CHARGE:
				writeChargeExpression(constraint, expr_str);
				break;

			case AtomMatchConstraint::ISOTOPE:
				writeIsotopeExpression(constraint, expr_str);
				break;

			case AtomMatchConstraint::RING_BOND_COUNT:
				writeRingConnectivityExpression(constraint, expr_str);
				break;

			case AtomMatchConstraint::H_COUNT:
				writeTotalHCountExpression(constraint, expr_str);
				break;

			case AtomMatchConstraint::IMPLICIT_H_COUNT:
				writeImplicitHCountExpression(constraint, expr_str);
				break;

			case AtomMatchConstraint::BOND_COUNT:
				writeConnectivityExpression(constraint, expr_str);
				break;

			case AtomMatchConstraint::EXPLICIT_BOND_COUNT:
				writeExplicitDegreeExpression(constraint, expr_str);
				break;

			case AtomMatchConstraint::VALENCE:
				writeValenceExpression(constraint, expr_str);
				break;

			case AtomMatchConstraint::RING_TOPOLOGY:
				writeRingTopologyExpression(constraint, expr_str);
				break;

			case AtomMatchConstraint::CONFIGURATION:
				writeChiralityExpression(constraint, expr_str);
				break;

			case AtomMatchConstraint::SSSR_RING_COUNT:
				writeRingMembershipExpression(constraint, expr_str);
				break;

			case AtomMatchConstraint::SSSR_RING_SIZE:
				writeRingSizeExpression(constraint, expr_str);
				break;

			case AtomMatchConstraint::UNSATURATION:
				writeUnsaturationFlagExpression(constraint, expr_str);
				break;

			default:
				continue;
		}

		if (expr_str.empty())
			continue;

		if (list_size > 0)
			switch (depth) {

				case 1:
					expr_list_str.push_back(LOW_PRECED_AND_OPERATOR);
					break;

				case 2:
					expr_list_str.push_back(OR_OPERATOR);
					break;

				case 3:
					expr_list_str.push_back(HI_PRECED_AND_OPERATOR);
					break;

				default:
					assert(false);
			}

		expr_list_str.append(expr_str);
		expr_str.clear();

		list_size++;
	}
}

void Chem::SMARTSDataWriter::DFSTreeNode::writeAtomTypeExpression(const MatchConstraint* type_constraint,
																  const MatchConstraint* arom_constraint,
																  std::string& expr_str, bool type_first) const
{
	using namespace SMARTS;

	if (type_constraint && type_constraint->getRelation() != MatchConstraint::EQUAL &&
		type_constraint->getRelation() != MatchConstraint::NOT_EQUAL)
		type_constraint = 0;

	if (arom_constraint && arom_constraint->getRelation() != MatchConstraint::EQUAL &&
		arom_constraint->getRelation() != MatchConstraint::NOT_EQUAL)
		arom_constraint = 0;

	if (!type_constraint && !arom_constraint)
		return;

	unsigned int atom_type = AtomType::UNKNOWN;

	if (type_constraint) {
		atom_type = getConstraintValue<unsigned int>(*type_constraint, *atom, &getType);
	
		if (atom_type == AtomType::UNKNOWN || (atom_type > AtomType::MAX_ATOMIC_NO && atom_type != AtomType::A)) {
			if (!arom_constraint)
				return;

			type_constraint = 0;

		} else if (!arom_constraint) {
			if (atom_type == AtomType::A)
				expr_str.push_back(AtomExpression::ANY_ATOM);
			else
				writeAtomicNumber(atom_type, type_constraint->getRelation() == MatchConstraint::NOT_EQUAL, expr_str);
			return;
		}
	}

	assert(arom_constraint);

	bool write_arom_sym = getConstraintValue<bool>(*arom_constraint, *atom, &getAromaticityFlag);

	if (arom_constraint->getRelation() == MatchConstraint::NOT_EQUAL)
		write_arom_sym = !write_arom_sym;

	if (!type_constraint) {
		expr_str.push_back(write_arom_sym ?  AtomExpression::ANY_AROMATIC_ATOM : AtomExpression::ANY_NON_AROMATIC_ATOM);
		return;
	}

	if (type_constraint->getRelation() == MatchConstraint::NOT_EQUAL) {
		if (type_first) 
			writeAtomicNumber(atom_type, true, expr_str);
	
		expr_str.push_back(write_arom_sym ?  AtomExpression::ANY_AROMATIC_ATOM : AtomExpression::ANY_NON_AROMATIC_ATOM);

		if (!type_first) 
			writeAtomicNumber(atom_type, true, expr_str);

		return;
	}
	
	switch (atom_type) {
		
		case AtomType::A:
			expr_str.push_back(write_arom_sym ? AtomExpression::ANY_AROMATIC_ATOM : AtomExpression::ANY_NON_AROMATIC_ATOM);
			return;
		
		case AtomType::C:
			expr_str.push_back(write_arom_sym ? 'c' : 'C');
			return;

		case AtomType::N:
			expr_str.push_back(write_arom_sym ? 'n' : 'N');
			return;

		case AtomType::O:
			expr_str.push_back(write_arom_sym ? 'o' : 'O');
			return;

		case AtomType::S:
			expr_str.push_back(write_arom_sym ? 's' : 'S');
			return;

		case AtomType::Se:
			expr_str.push_back(write_arom_sym ? 's' : 'S');
			expr_str.push_back('e');
			return;

		case AtomType::Te:
			expr_str.push_back(write_arom_sym ? 't' : 'T');
			expr_str.push_back('e');
			return;

		case AtomType::As:
			expr_str.push_back(write_arom_sym ? 'a' : 'A');
			expr_str.push_back('s');
			return;

		case AtomType::P:
			expr_str.push_back(write_arom_sym ? 'p' : 'P');
			return;

		case AtomType::H:
			if (type_first) 
				writeAtomicNumber(atom_type, false, expr_str);

			expr_str.push_back(write_arom_sym ? AtomExpression::ANY_AROMATIC_ATOM : AtomExpression::ANY_NON_AROMATIC_ATOM);

			if (!type_first) 
				writeAtomicNumber(atom_type, false, expr_str);
			return;

		default:
			if (!write_arom_sym) {
				const std::string& symbol = AtomDictionary::getSymbol(atom_type);

				assert(!symbol.empty());

				expr_str.append(symbol);
				return;
			}
			
			if (type_first) 
				writeAtomicNumber(atom_type, false, expr_str);

			expr_str.push_back(AtomExpression::ANY_AROMATIC_ATOM);
			
			if (!type_first) 
				writeAtomicNumber(atom_type, false, expr_str);
	}
}

bool Chem::SMARTSDataWriter::DFSTreeNode::writeAtomTypeExpression(const MatchConstraintList& constr_list, 
																  std::string& expr_str, bool allow_exp_h) const
{
	using namespace SMARTS;

	if (constr_list.getSize() != 2)
		return false;

	const MatchConstraint* arom_constraint = 
		findMatchConstraint(constr_list, AtomMatchConstraint::AROMATICITY, MatchConstraint::EQUAL);

	if (!arom_constraint)
		arom_constraint = 
			findMatchConstraint(constr_list, AtomMatchConstraint::AROMATICITY, MatchConstraint::NOT_EQUAL);

	if (!arom_constraint)
		return false;

	const MatchConstraint* type_constraint = 
		findMatchConstraint(constr_list, AtomMatchConstraint::TYPE, MatchConstraint::EQUAL);

	if (!type_constraint)
		type_constraint = 
			findMatchConstraint(constr_list, AtomMatchConstraint::TYPE, MatchConstraint::NOT_EQUAL);

	if (!type_constraint)
		return false;

	bool aromatic = getConstraintValue<bool>(*arom_constraint, *atom, &getAromaticityFlag);

	if (arom_constraint->getRelation() == MatchConstraint::NOT_EQUAL)
		aromatic = !aromatic;

	bool write_arom_sym = false;
	bool write_not_prefix = false;
	bool type_first = (type_constraint == &constr_list.getFirstElement());

	switch (constr_list.getType()) {

		case MatchConstraintList::OR_LIST:
			if (type_constraint->getRelation() != MatchConstraint::NOT_EQUAL)
				return false;

			write_not_prefix = true;
			write_arom_sym = !aromatic;
			break;

		case MatchConstraintList::NOT_OR_LIST:
			if (type_constraint->getRelation() != MatchConstraint::NOT_EQUAL)
				return false;

			write_arom_sym = !aromatic;
			break;

		case MatchConstraintList::AND_LIST:
			if (type_constraint->getRelation() != MatchConstraint::EQUAL)
				return false;

			write_arom_sym = aromatic;
			break;

		case MatchConstraintList::NOT_AND_LIST:
			if (type_constraint->getRelation() != MatchConstraint::EQUAL)
				return false;

			write_not_prefix = true;
			write_arom_sym = aromatic;
			break;

		default:
			return false;
	}

	unsigned int atom_type = getConstraintValue<unsigned int>(*type_constraint, *atom, &getType);

	switch (atom_type) {
		
		case AtomType::A:
			if (write_not_prefix)
				expr_str.push_back(NOT_OPERATOR);

			expr_str.push_back(write_arom_sym ? AtomExpression::ANY_AROMATIC_ATOM : AtomExpression::ANY_NON_AROMATIC_ATOM);
			return true;
		
		case AtomType::C:
			if (write_not_prefix)
				expr_str.push_back(NOT_OPERATOR);

			expr_str.push_back(write_arom_sym ? 'c' : 'C');
			return true;

		case AtomType::N:
			if (write_not_prefix)
				expr_str.push_back(NOT_OPERATOR);

			expr_str.push_back(write_arom_sym ? 'n' : 'N');
			return true;

		case AtomType::O:
			if (write_not_prefix)
				expr_str.push_back(NOT_OPERATOR);

			expr_str.push_back(write_arom_sym ? 'o' : 'O');
			return true;

		case AtomType::S:
			if (write_not_prefix)
				expr_str.push_back(NOT_OPERATOR);

			expr_str.push_back(write_arom_sym ? 's' : 'S');
			return true;

		case AtomType::P:
			if (write_not_prefix)
				expr_str.push_back(NOT_OPERATOR);

			expr_str.push_back(write_arom_sym ? 'p' : 'P');
			return true;

		case AtomType::H:
			if (write_not_prefix)
				return false;

			if (allow_exp_h && !write_arom_sym) 
				expr_str.push_back('H');

			else {
				if (type_first) 
					writeAtomicNumber(1, false, expr_str);

				expr_str.push_back(write_arom_sym ? AtomExpression::ANY_AROMATIC_ATOM : AtomExpression::ANY_NON_AROMATIC_ATOM);

				if (!type_first) 
					writeAtomicNumber(1, false, expr_str);
			}
			return true;

		default:
			if (atom_type == AtomType::UNKNOWN || atom_type > AtomType::MAX_ATOMIC_NO) 
				return false;

			if (!write_arom_sym) {
				if (write_not_prefix)
					expr_str.push_back(NOT_OPERATOR);

				const std::string& symbol = AtomDictionary::getSymbol(atom_type);

				assert(!symbol.empty());

				expr_str.append(symbol);
				return true;
			}

			if (write_not_prefix)
				return false;
			
			if (type_first)
				writeAtomicNumber(atom_type, false, expr_str);

			expr_str.push_back(AtomExpression::ANY_AROMATIC_ATOM);

			if (!type_first)
				writeAtomicNumber(atom_type, false, expr_str);

			return true;
	}

	return false;
}

void Chem::SMARTSDataWriter::DFSTreeNode::writeAtomicNumber(unsigned int atomic_no, bool not_prefix, std::string& str) const
{
	using namespace SMARTS;

	if (not_prefix)
		str.push_back(NOT_OPERATOR);

	str.push_back(AtomExpression::ATOMIC_NUMBER_PREFIX);
	str.append(boost::lexical_cast<std::string>(atomic_no));
}

void Chem::SMARTSDataWriter::DFSTreeNode::writeExpressionList(const MatchConstraint& constraint,
															  std::string& expr_list_str, std::size_t depth) const
{
	using namespace SMARTS;

	if (constraint.getRelation() != MatchConstraint::EQUAL)
		return;

	const MatchConstraintList& constr_list = *constraint.getValue<MatchConstraintList::SharedPointer>();

	if (constr_list.getSize() == 0)
		return;

	if (writeAtomTypeExpression(constr_list, expr_list_str)) 
		return;

	switch (depth) {

		case 0:
		case 1:
			assert(false);

		case 2:
			if (constr_list.getType() == MatchConstraintList::OR_LIST) {
				if (constr_list.getSize() == 1)
					depth = 1;

				break;
			}

			if (constr_list.getType() == MatchConstraintList::AND_LIST) {
				depth = 1;
				break;
			}

			return;

		case 3:
			if (constr_list.getType() == MatchConstraintList::AND_LIST) {
				if (constr_list.getSize() == 1)
					depth = 2;

				break;
			}

			if (constr_list.getType() == MatchConstraintList::OR_LIST) { 
				depth = 2;
				break;
			}

			return;

		case 4:
			if (constr_list.getType() == MatchConstraintList::AND_LIST) {
				depth = 3;
				break;
			}

			if (constr_list.getType() == MatchConstraintList::OR_LIST && constr_list.getSize() == 1)
				depth = 3;
			break;

		default:
			return;
	}

	writeComplexAtomExpression(constr_list, expr_list_str, depth);
}

void Chem::SMARTSDataWriter::DFSTreeNode::writeEnvironmentExpression(const MatchConstraint& constraint,
																	 std::string& expr_str) const
{
	using namespace SMARTS;

	if (constraint.getRelation() != MatchConstraint::EQUAL && 
		constraint.getRelation() != MatchConstraint::NOT_EQUAL)
		return;

	const Molecule& env_pattern = *constraint.getValue<Molecule::SharedPointer>();
	std::ostringstream oss;
	
	writer.writeSMARTS(oss, env_pattern);

	std::string smarts = oss.str();

	if (smarts.empty())
		return;

	if (constraint.getRelation() == MatchConstraint::NOT_EQUAL)
		expr_str.push_back(NOT_OPERATOR);

	expr_str.push_back(AtomExpression::RECURSIVE_SMARTS_PREFIX);
	expr_str.push_back(AtomExpression::RECURSIVE_SMARTS_BEGIN);
	expr_str.append(smarts);
	expr_str.push_back(AtomExpression::RECURSIVE_SMARTS_END);
}

void Chem::SMARTSDataWriter::DFSTreeNode::writeImplicitHCountExpression(const MatchConstraint& constraint,
																		std::string& expr_str) const 
{
	using namespace SMARTS;

	if (constraint.getRelation() != MatchConstraint::EQUAL && 
		constraint.getRelation() != MatchConstraint::NOT_EQUAL)
		return;

	std::size_t h_count = getConstraintValue<std::size_t>(constraint, *atom, &getImplicitHydrogenCount);

	if (constraint.getRelation() == MatchConstraint::NOT_EQUAL)
		expr_str.push_back(NOT_OPERATOR);

	expr_str.push_back(AtomExpression::IMPLICIT_H_COUNT_PREFIX);

	if (h_count != 1) 
		expr_str.append(boost::lexical_cast<std::string>(h_count));
}

void Chem::SMARTSDataWriter::DFSTreeNode::writeTotalHCountExpression(const MatchConstraint& constraint,
																	 std::string& expr_str) const 
{
	using namespace SMARTS;

	if (constraint.getRelation() != MatchConstraint::EQUAL && 
		constraint.getRelation() != MatchConstraint::NOT_EQUAL)
		return;

	std::size_t h_count = getConstraintValue<std::size_t>(constraint, *atom, *molGraph, &calcTotalHydrogenCount);

	if (constraint.getRelation() == MatchConstraint::NOT_EQUAL)
		expr_str.push_back(NOT_OPERATOR);

	expr_str.push_back(AtomExpression::TOTAL_H_COUNT_PREFIX);
	expr_str.append(boost::lexical_cast<std::string>(h_count));
}

void Chem::SMARTSDataWriter::DFSTreeNode::writeRingSizeExpression(const MatchConstraint& constraint,
																  std::string& expr_str) const 
{
	using namespace SMARTS;

	if (constraint.getRelation() != MatchConstraint::EQUAL && 
		constraint.getRelation() != MatchConstraint::NOT_EQUAL)
		return;

	std::size_t rsize = constraint.getValue<std::size_t>();

	if (constraint.getRelation() == MatchConstraint::NOT_EQUAL)
		expr_str.push_back(NOT_OPERATOR);

	expr_str.push_back(AtomExpression::RING_SIZE_PREFIX);
	expr_str.append(boost::lexical_cast<std::string>(rsize));
}

void Chem::SMARTSDataWriter::DFSTreeNode::writeRingTopologyExpression(const MatchConstraint& constraint,
																	  std::string& expr_str) const 
{
	using namespace SMARTS;

	if (constraint.getRelation() != MatchConstraint::EQUAL && 
		constraint.getRelation() != MatchConstraint::NOT_EQUAL)
		return;

	bool in_ring = getConstraintValue<bool>(constraint, *atom, &getRingFlag);

	if (constraint.getRelation() == MatchConstraint::NOT_EQUAL)
		in_ring = !in_ring;

	if (!in_ring)
		expr_str.push_back(NOT_OPERATOR);

	expr_str.push_back(AtomExpression::RING_MEMBERSHIP_PREFIX);
}

void Chem::SMARTSDataWriter::DFSTreeNode::writeUnsaturationFlagExpression(const MatchConstraint& constraint,
																		  std::string& expr_str) const 
{
	using namespace SMARTS;

	if (constraint.getRelation() != MatchConstraint::EQUAL && 
		constraint.getRelation() != MatchConstraint::NOT_EQUAL)
		return;

	bool unsat = getConstraintValue<bool>(constraint, *atom, *molGraph, &Internal::isUnsaturated);

	if (constraint.getRelation() == MatchConstraint::NOT_EQUAL)
		unsat = !unsat;

	if (!unsat)
		expr_str.push_back(NOT_OPERATOR);

	expr_str.push_back(AtomExpression::UNSATURATED_FLAG);
}

void Chem::SMARTSDataWriter::DFSTreeNode::writeRingMembershipExpression(const MatchConstraint& constraint,
																		std::string& expr_str) const 
{
	using namespace SMARTS;

	if (constraint.getRelation() != MatchConstraint::EQUAL && 
		constraint.getRelation() != MatchConstraint::NOT_EQUAL)
		return;

	std::size_t num_sssr_rings = getConstraintValue<std::size_t>(constraint, *atom, *molGraph, &Internal::getNumContainingSSSRRings);

	if (constraint.getRelation() == MatchConstraint::NOT_EQUAL)
		expr_str.push_back(NOT_OPERATOR);

	expr_str.push_back(AtomExpression::RING_MEMBERSHIP_PREFIX);
	expr_str.append(boost::lexical_cast<std::string>(num_sssr_rings));
}

void Chem::SMARTSDataWriter::DFSTreeNode::writeHybridizationStateExpression(const MatchConstraint& constraint,
																			std::string& expr_str) const 
{
	using namespace SMARTS;

	if (constraint.getRelation() != MatchConstraint::EQUAL && 
		constraint.getRelation() != MatchConstraint::NOT_EQUAL)
		return;

	unsigned int hyb_state = getConstraintValue<unsigned int>(constraint, *atom, &getHybridizationState);
	unsigned int hyb_id;

	switch (hyb_state) {

		case HybridizationState::SP:
			hyb_id = 1;
			break;

		case HybridizationState::SP2:
			hyb_id = 2;
			break;

		case HybridizationState::SP3:
			hyb_id = 3;
			break;

		default:
			return;
	}

	if (constraint.getRelation() == MatchConstraint::NOT_EQUAL)
		expr_str.push_back(NOT_OPERATOR);

	expr_str.push_back(AtomExpression::HYBRIDIZATION_PREFIX);
	expr_str.append(boost::lexical_cast<std::string>(hyb_id));
}

void Chem::SMARTSDataWriter::DFSTreeNode::writeValenceExpression(const MatchConstraint& constraint,
																 std::string& expr_str) const 
{
	using namespace SMARTS;

	if (constraint.getRelation() != MatchConstraint::EQUAL && 
		constraint.getRelation() != MatchConstraint::NOT_EQUAL)
		return;

	std::size_t valence = getConstraintValue<std::size_t>(constraint, *atom, *molGraph, &Internal::calcValence);

	if (constraint.getRelation() == MatchConstraint::NOT_EQUAL)
		expr_str.push_back(NOT_OPERATOR);

	expr_str.push_back(AtomExpression::VALENCE_PREFIX);

	if (valence != 1)
		expr_str.append(boost::lexical_cast<std::string>(valence));
}

void Chem::SMARTSDataWriter::DFSTreeNode::writeExplicitDegreeExpression(const MatchConstraint& constraint,
																		std::string& expr_str) const 
{
	using namespace SMARTS;

	if (constraint.getRelation() != MatchConstraint::EQUAL && 
		constraint.getRelation() != MatchConstraint::NOT_EQUAL)
		return;

	std::size_t expl_bond_count = getConstraintValue<std::size_t>(constraint, *atom, *molGraph, &Internal::getExplicitBondCount);

	if (constraint.getRelation() == MatchConstraint::NOT_EQUAL)
		expr_str.push_back(NOT_OPERATOR);

	expr_str.push_back(AtomExpression::EXPLICIT_DEGREE_PREFIX);

	if (expl_bond_count != 1)
		expr_str.append(boost::lexical_cast<std::string>(expl_bond_count));
}

void Chem::SMARTSDataWriter::DFSTreeNode::writeConnectivityExpression(const MatchConstraint& constraint,
																	  std::string& expr_str) const 
{
	using namespace SMARTS;

	if (constraint.getRelation() != MatchConstraint::EQUAL && 
		constraint.getRelation() != MatchConstraint::NOT_EQUAL)
		return;

	std::size_t bond_count = getConstraintValue<std::size_t>(constraint, *atom, *molGraph, &Internal::getBondCount);

	if (constraint.getRelation() == MatchConstraint::NOT_EQUAL)
		expr_str.push_back(NOT_OPERATOR);

	expr_str.push_back(AtomExpression::CONNECTIVITY_PREFIX);

	if (bond_count != 1)
		expr_str.append(boost::lexical_cast<std::string>(bond_count));
}

void Chem::SMARTSDataWriter::DFSTreeNode::writeRingConnectivityExpression(const MatchConstraint& constraint,
																		  std::string& expr_str) const 
{
	using namespace SMARTS;

	if (constraint.getRelation() != MatchConstraint::EQUAL && 
		constraint.getRelation() != MatchConstraint::NOT_EQUAL)
		return;

	std::size_t ring_bond_count = getConstraintValue<std::size_t>(constraint, *atom, *molGraph, &Internal::getRingBondCount);

	if (constraint.getRelation() == MatchConstraint::NOT_EQUAL)
		expr_str.push_back(NOT_OPERATOR);

	expr_str.push_back(AtomExpression::RING_CONNECTIVITY_PREFIX);

	if (ring_bond_count != 1)
		expr_str.append(boost::lexical_cast<std::string>(ring_bond_count));
}

void Chem::SMARTSDataWriter::DFSTreeNode::writeChargeExpression(const MatchConstraint& constraint,
																std::string& expr_str) const 
{	
	using namespace SMARTS;

	if (constraint.getRelation() != MatchConstraint::EQUAL && 
		constraint.getRelation() != MatchConstraint::NOT_EQUAL)
		return;

	long charge = getConstraintValue<long>(constraint, *atom, &getFormalCharge);

	if (constraint.getRelation() == MatchConstraint::NOT_EQUAL)
		expr_str.push_back(NOT_OPERATOR);

	if (charge == 0) {
		expr_str.push_back(AtomExpression::POSITIVE_CHARGE_PREFIX);
		expr_str.push_back('0');
		return;
	} 

	expr_str.push_back(charge < 0 ? AtomExpression::NEGATIVE_CHARGE_PREFIX : AtomExpression::POSITIVE_CHARGE_PREFIX); 

	if (std::abs(charge) > 1)
		expr_str.append(boost::lexical_cast<std::string>(std::abs(charge)));
}

void Chem::SMARTSDataWriter::DFSTreeNode::writeChiralityExpression(const MatchConstraint& constraint,
																   std::string& expr_str) const 
{
	using namespace SMARTS;

	if (constraint.getRelation() != MatchConstraint::EQUAL)
		return;

	const StereoDescriptor& stereo_desc = getConstraintValue<StereoDescriptor>(constraint, *atom, *molGraph, &::calcStereoDescriptor);
	
	switch (stereo_desc.getConfiguration()) {

		case AtomConfiguration::R:
		case AtomConfiguration::S:
		case AtomConfiguration::EITHER | AtomConfiguration::R:
		case AtomConfiguration::EITHER | AtomConfiguration::S:
			break;

		default:
			return;
	}

	int parity = getStereoParity(stereo_desc);

	if (parity == 0)
		return;

	expr_str.push_back(AtomExpression::CHIRAL_CLASS_PREFIX);

	if (parity > 0)
		expr_str.push_back(AtomExpression::CHIRAL_CLASS_PREFIX);

	if ((stereo_desc.getConfiguration() & AtomConfiguration::EITHER) != 0)
		expr_str.push_back(UNSPEC_STEREO_SUFFIX);
}

void Chem::SMARTSDataWriter::DFSTreeNode::writeIsotopeExpression(const MatchConstraint& constraint,
																 std::string& expr_str) const 
{
	using namespace SMARTS;

	if (constraint.getRelation() != MatchConstraint::EQUAL && 
		constraint.getRelation() != MatchConstraint::NOT_EQUAL)
		return;

	std::size_t isotope = getConstraintValue<std::size_t>(constraint, *atom, &getIsotope);

	if (constraint.getRelation() == MatchConstraint::NOT_EQUAL)
		expr_str.push_back(NOT_OPERATOR);

	expr_str.append(boost::lexical_cast<std::string>(isotope));
}

void Chem::SMARTSDataWriter::DFSTreeNode::writeReactionAtomMappingID(std::ostream& os, std::size_t aam_id) const
{
	os << SMARTS::AtomExpression::ATOM_MAPPING_ID_PREFIX << aam_id;
}

void Chem::SMARTSDataWriter::DFSTreeNode::writeRingClosures(std::ostream& os) const
{
	std::for_each(ringClosureInEdges.begin(), ringClosureInEdges.end(),
				  boost::bind(&DFSTreeNode::writeRingClosureNumber, this, boost::ref(os), _1));

	EdgeList::const_iterator edges_end = ringClosureOutEdges.end();

	for (EdgeList::const_iterator it = ringClosureOutEdges.begin(); it != edges_end; ++it) {
		const DFSTreeEdge* edge = *it;

		edge->writeBondExpression(os);
		writeRingClosureNumber(os, edge); 
	}
}

void Chem::SMARTSDataWriter::DFSTreeNode::writeRingClosureNumber(std::ostream& os, const DFSTreeEdge* edge) const
{
	std::size_t closure_no = edge->getRingClosureNumber();

	if (closure_no > 9)
		os << SMARTS::CLOSURE_NO_PREFIX;

	os << closure_no;
}

void Chem::SMARTSDataWriter::DFSTreeNode::writeChildNodeExpressions(std::ostream& os) const
{
	std::size_t num_edges = childEdges.size();

	for (std::size_t i = 0; i < num_edges; i++) {
		const DFSTreeEdge* edge = childEdges[i];

		if (i < num_edges - 1) {
			os << SMARTS::GROUPING_PREFIX;
			
			edge->writeBondExpression(os);
			edge->getEnd()->generateSMARTS(os);

			os << SMARTS::GROUPING_SUFFIX;

		} else {
			edge->writeBondExpression(os);
			edge->getEnd()->generateSMARTS(os);
		}
	}
}

int Chem::SMARTSDataWriter::DFSTreeNode::getStereoParity(const StereoDescriptor& stereo_desc) const
{
	std::size_t num_bonds = stereo_desc.getNumReferenceAtoms();

	if (num_bonds < 3) // sanity_check
		return 0;

	unsigned int config = stereo_desc.getConfiguration() & (AtomConfiguration::R | AtomConfiguration::S);

	std::vector<const Atom*> smarts_ref_atoms;

	for (EdgeList::const_iterator it = ringClosureInEdges.begin(), end = ringClosureInEdges.end(); it != end; ++it)
		smarts_ref_atoms.push_back((*it)->getBegin()->atom);

	for (EdgeList::const_iterator it = ringClosureOutEdges.begin(), end = ringClosureOutEdges.end(); it != end; ++it)
		smarts_ref_atoms.push_back((*it)->getEnd()->atom);

	for (EdgeList::const_iterator it = childEdges.begin(), end = childEdges.end(); it != end; ++it)
		smarts_ref_atoms.push_back((*it)->getEnd()->atom);

	if (parentEdge) {
		if (smarts_ref_atoms.size() == 2)
			smarts_ref_atoms.insert(smarts_ref_atoms.begin(), atom);
	
		smarts_ref_atoms.push_back(parentEdge->getBegin()->atom);

	} else {
		if (smarts_ref_atoms.size() == 3)
			smarts_ref_atoms.push_back(atom);

		else if (smarts_ref_atoms.size() == 4) {
			const Atom* first_nbr = smarts_ref_atoms.front();

			smarts_ref_atoms.erase(smarts_ref_atoms.begin());
			smarts_ref_atoms.push_back(first_nbr);
		}
	}

	if (smarts_ref_atoms.size() != 4) // sanity check
		return 0;

	unsigned int perm_parity = stereo_desc.getPermutationParity(*smarts_ref_atoms[0], *smarts_ref_atoms[1], *smarts_ref_atoms[2], *smarts_ref_atoms[3]);

	if (perm_parity == 1)
		return (config == AtomConfiguration::S ? -1 : 1);
	else if (perm_parity == 2)
		return (config == AtomConfiguration::S ? 1 : -1);
	else
		return 0;
}


// -------------------------

Chem::SMARTSDataWriter::DFSTreeEdge::DFSTreeEdge(SMARTSDataWriter& writer): 
	writer(writer), molGraph(0), bond(0) {}

void Chem::SMARTSDataWriter::DFSTreeEdge::setBond(const Bond* bnd)
{
	bond = bnd;
}

const Chem::Bond* Chem::SMARTSDataWriter::DFSTreeEdge::getBond() const
{
	return bond;
}

void Chem::SMARTSDataWriter::DFSTreeEdge::setMolGraph(const MolecularGraph* molgraph)
{
	molGraph = molgraph;
}

void Chem::SMARTSDataWriter::DFSTreeEdge::setNodes(DFSTreeNode* begin, DFSTreeNode* end)
{
	nodes[0] = begin;
	nodes[1] = end;
}

const Chem::SMARTSDataWriter::DFSTreeNode* Chem::SMARTSDataWriter::DFSTreeEdge::getBegin() const
{
	return nodes[0];
}

const Chem::SMARTSDataWriter::DFSTreeNode* Chem::SMARTSDataWriter::DFSTreeEdge::getEnd() const
{
	return nodes[1];
}

void Chem::SMARTSDataWriter::DFSTreeEdge::setRingClosureNumber(std::size_t closure_no)
{
	ringClosureNumber = closure_no;
}

std::size_t Chem::SMARTSDataWriter::DFSTreeEdge::getRingClosureNumber() const
{
	return ringClosureNumber;
}

void Chem::SMARTSDataWriter::DFSTreeEdge::writeBondExpression(std::ostream& os) const
{
	using namespace SMARTS;

	const MatchConstraintList& constr_list = *getMatchConstraints(*bond);

	if (constr_list.getSize() == 0) {
		os << BondExpression::ANY_BOND;
		return;
	}

	if (isImplicitExpression(constr_list))
		return;

	std::string expr_string;

	writeBondExpression(constr_list, expr_string, 0);

	if (!expr_string.empty())
		os << expr_string;
	else
		os << BondExpression::ANY_BOND;
}

bool Chem::SMARTSDataWriter::DFSTreeEdge::isImplicitExpression(const MatchConstraintList& constr_list) const
{
	using namespace SMARTS;

	if (constr_list.getSize() > 2)
		return false;

	if (!isORMatchConstraintList(constr_list))
		return false;

	if (constr_list.getSize() == 1) {
		const MatchConstraint& constraint = constr_list.getFirstElement();
		
		if (constraint.getID() != BondMatchConstraint::ORDER)
			return false;

		if (constraint.getRelation() != MatchConstraint::EQUAL)
			return false;

		if (!constraint.hasValue())
			return false;

		return (constraint.getValue<unsigned int>() == (BondMatchConstraint::SINGLE | BondMatchConstraint::AROMATIC));
	}

	const MatchConstraint* arom_constraint = 
		findMatchConstraint(constr_list, BondMatchConstraint::AROMATICITY, MatchConstraint::EQUAL);

	if (!arom_constraint)
		arom_constraint = 
			findMatchConstraint(constr_list, BondMatchConstraint::AROMATICITY, MatchConstraint::NOT_EQUAL);

	if (!arom_constraint)
		return false;

	bool aromatic = getConstraintValue<bool>(*arom_constraint, *bond, &getAromaticityFlag);

	if (arom_constraint->getRelation() == MatchConstraint::NOT_EQUAL)
		aromatic = !aromatic;

	if (!aromatic)
		return false;
	
	const MatchConstraint* order_constraint = 
		findMatchConstraint(constr_list, BondMatchConstraint::ORDER, MatchConstraint::EQUAL);

	if (!order_constraint)
		return false;

	if (!order_constraint->hasValue())
		return false;

	unsigned int order = order_constraint->getValue<unsigned int>();

	return (order == BondMatchConstraint::SINGLE);
}

void Chem::SMARTSDataWriter::DFSTreeEdge::writeBondExpression(const MatchConstraintList& constr_list,
															  std::string& expr_list_str, std::size_t depth) const
{
	using namespace SMARTS;

	if (depth == 0) {
		switch (constr_list.getType()) {

			case MatchConstraintList::OR_LIST:
				depth = (constr_list.getSize() == 1 ? 1 : 2);
				break;

			case MatchConstraintList::AND_LIST:
				depth = 1;
				break;

			default:
				return;
		}
	}

	std::size_t list_size = 0;
	std::string expr_str;

	MatchConstraintList::ConstElementIterator constr_end = constr_list.getElementsEnd();

	for (MatchConstraintList::ConstElementIterator it = constr_list.getElementsBegin(); it != constr_end; ++it) {
		const MatchConstraint& constraint = *it;

		switch (constraint.getID()) {

			case BondMatchConstraint::CONSTRAINT_LIST:
				writeExpressionList(constraint, expr_str, depth + 1);
				break;
		
			case BondMatchConstraint::ORDER:
				writeOrderExpression(constraint, expr_str, depth);
				break;

			case BondMatchConstraint::AROMATICITY:
				writeAromaticityExpression(constraint, expr_str);
				break;

			case BondMatchConstraint::RING_TOPOLOGY:
				writeRingTopologyExpression(constraint, expr_str);
				break;		

			case BondMatchConstraint::DIRECTION:
				writeDirectionExpression(constraint, expr_str);
				break;		

			default:
				continue;
		}

		if (expr_str.empty())
			continue;

		if (list_size > 0)
			switch (depth) {

				case 1:
					expr_list_str.push_back(LOW_PRECED_AND_OPERATOR);
					break;

				case 2:
					expr_list_str.push_back(OR_OPERATOR);
					break;

				case 3:
					expr_list_str.push_back(HI_PRECED_AND_OPERATOR);
					break;

				default:
					assert(false);
			}

		expr_list_str.append(expr_str);
		expr_str.clear();

		list_size++;
	}
}

void Chem::SMARTSDataWriter::DFSTreeEdge::writeExpressionList(const MatchConstraint& constraint,
															  std::string& expr_list_str, std::size_t depth) const
{
	using namespace SMARTS;

	if (constraint.getRelation() != MatchConstraint::EQUAL)
		return;

	const MatchConstraintList& constr_list = *constraint.getValue<MatchConstraintList::SharedPointer>();

	if (constr_list.getSize() == 0)
		return;

	switch (depth) {

		case 0:
		case 1:
			assert(false);

		case 2:
			if (constr_list.getType() == MatchConstraintList::OR_LIST) {
				if (constr_list.getSize() == 1)
					depth = 1;

				break;
			}

			if (constr_list.getType() == MatchConstraintList::AND_LIST) {
				depth = 1;
				break;
			}

			return;

		case 3:
			if (constr_list.getType() == MatchConstraintList::AND_LIST) {
				if (constr_list.getSize() == 1)
					depth = 2;

				break;
			}

			if (constr_list.getType() == MatchConstraintList::OR_LIST) { 
				depth = 2;
				break;
			}

			return;

		case 4:
			if (constr_list.getType() == MatchConstraintList::AND_LIST) {
				depth = 3;
				break;
			}

			if (constr_list.getType() == MatchConstraintList::OR_LIST && constr_list.getSize() == 1)
				depth = 3;
			break;

		default:
			return;
	}

	writeBondExpression(constr_list, expr_list_str, depth);
}

void Chem::SMARTSDataWriter::DFSTreeEdge::writeOrderExpression(const MatchConstraint& constraint,
															   std::string& expr_str, std::size_t depth) const
{
	using namespace SMARTS;

	if (constraint.getRelation() != MatchConstraint::EQUAL && 
		constraint.getRelation() != MatchConstraint::NOT_EQUAL)
		return;

	std::size_t order;
	bool order_valid = false;

	if (!constraint.hasValue()) {
		bool aromatic_bond = getAromaticityFlag(*bond);
		order = getOrder(*bond);

		if (aromatic_bond) {

			switch (order) {

				case 1:
					order = BondMatchConstraint::SINGLE | BondMatchConstraint::AROMATIC;
					order_valid = true;
					break;

				case 2:
					order = BondMatchConstraint::DOUBLE | BondMatchConstraint::AROMATIC;
					order_valid = true;
					break;

				case 3:
					order = BondMatchConstraint::TRIPLE | BondMatchConstraint::AROMATIC;
					order_valid = true;
					
				default:
					break;
			}
		}

	} else {
		order = constraint.getValue<unsigned int>();

		if (order == BondMatchConstraint::IGNORE_AROMATICITY)
			order = getOrder(*bond);
		else
			order_valid = true;
	}

	if (!order_valid) {
		switch (order) {
			
			case 1:
				order = BondMatchConstraint::SINGLE;
				break;

			case 2:
				order = BondMatchConstraint::DOUBLE;
				break;

			case 3:
				order = BondMatchConstraint::TRIPLE;
					
			default:
				break;	
		}
	}

	std::size_t list_size = 0;
	std::string tmp_expr_str;
	std::string list_separator;
	std::string prefix;

	if (constraint.getRelation() == MatchConstraint::NOT_EQUAL) {
		list_separator.push_back(OR_OPERATOR);
		prefix.push_back(NOT_OPERATOR);
	}

	if ((order & BondMatchConstraint::ANY_ORDER) == BondMatchConstraint::ANY_ORDER) {
		tmp_expr_str.append(prefix);
		tmp_expr_str.push_back(BondExpression::ANY_BOND);

		list_size++;

	} else {
		if ((order & BondMatchConstraint::SINGLE) != 0) {
			tmp_expr_str.append(prefix);
			tmp_expr_str.push_back(BondExpression::SINGLE_BOND);
			list_size++;
		}

		if ((order & BondMatchConstraint::DOUBLE) != 0) {
			if (list_size > 0)
				tmp_expr_str.append(list_separator);

			tmp_expr_str.append(prefix);
			tmp_expr_str.push_back(BondExpression::DOUBLE_BOND);
			list_size++;
		} 

		if ((order & BondMatchConstraint::TRIPLE) != 0) {
			if (list_size > 0)
				tmp_expr_str.append(list_separator);

			tmp_expr_str.append(prefix);
			tmp_expr_str.push_back(BondExpression::TRIPLE_BOND);
			list_size++;
		}

		if ((order & BondMatchConstraint::AROMATIC) != 0) {
			if (list_size > 0)
				tmp_expr_str.append(list_separator);

			tmp_expr_str.append(prefix);
			tmp_expr_str.push_back(BondExpression::AROMATIC_BOND);
			list_size++;
		}
	}

	if (tmp_expr_str.find(OR_OPERATOR) != std::string::npos && depth > 2)
		return;

	expr_str.append(tmp_expr_str);
}

void Chem::SMARTSDataWriter::DFSTreeEdge::writeAromaticityExpression(const MatchConstraint& constraint,
																	 std::string& expr_str) const
{
	using namespace SMARTS;

	if (constraint.getRelation() != MatchConstraint::EQUAL && 
		constraint.getRelation() != MatchConstraint::NOT_EQUAL)
		return;

	bool aromatic = getConstraintValue<bool>(constraint, *bond, &getAromaticityFlag);

	if (constraint.getRelation() == MatchConstraint::NOT_EQUAL)
		aromatic = !aromatic;

	if (!aromatic)
		expr_str.push_back(NOT_OPERATOR);

	expr_str.push_back(BondExpression::AROMATIC_BOND);
}

void Chem::SMARTSDataWriter::DFSTreeEdge::writeRingTopologyExpression(const MatchConstraint& constraint,
																	  std::string& expr_str) const
{
	using namespace SMARTS;

	if (constraint.getRelation() != MatchConstraint::EQUAL && 
		constraint.getRelation() != MatchConstraint::NOT_EQUAL)
		return;

	bool in_ring = getConstraintValue<bool>(constraint, *bond, &getRingFlag);

	if (constraint.getRelation() == MatchConstraint::NOT_EQUAL)
		in_ring = !in_ring;

	if (!in_ring)
		expr_str.push_back(NOT_OPERATOR);

	expr_str.push_back(BondExpression::RING_BOND);
}

void Chem::SMARTSDataWriter::DFSTreeEdge::writeDirectionExpression(const MatchConstraint& constraint,
																   std::string& expr_str) const
{
	using namespace SMARTS;

	if (constraint.getRelation() != MatchConstraint::EQUAL)
		return;

	unsigned int direction = getConstraintValue<unsigned int>(constraint, *bond, &getDirection);

	switch (direction) {

		case BondDirection::UP:
		case BondDirection::DOWN:
		case BondDirection::UP | BondDirection::UNSPECIFIED:
		case BondDirection::DOWN | BondDirection::UNSPECIFIED:
			break;

		default:
			return;
	}

	if ((direction & BondDirection::UP) != 0)
		expr_str.push_back(BondExpression::UP_DIR_FLAG);
	else
		expr_str.push_back(BondExpression::DOWN_DIR_FLAG);

	if ((direction & BondDirection::UNSPECIFIED) != 0)
		expr_str.push_back(UNSPEC_STEREO_SUFFIX);
}
