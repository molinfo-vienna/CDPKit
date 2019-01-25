/* -*- mode: c++; c-basic-offset: 4; tab-width: 4; indent-tabs-mode: t -*- */

/* 
 * SMILESDataWriter.cpp 
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

#include <ostream>
#include <sstream>
#include <locale>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include <cassert>

#include <boost/bind.hpp>

#include "CDPL/Chem/Reaction.hpp"
#include "CDPL/Chem/Molecule.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/ReactionFunctions.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/ControlParameterFunctions.hpp"
#include "CDPL/Chem/ReactionRole.hpp"
#include "CDPL/Chem/BondDirection.hpp"
#include "CDPL/Chem/AtomPropertyFlag.hpp"
#include "CDPL/Chem/BondPropertyFlag.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"
#include "CDPL/Chem/BondDirectionGenerator.hpp"
#include "CDPL/Chem/CanonicalNumberingGenerator.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Base/DataIOBase.hpp"
#include "CDPL/Internal/AddressOf.hpp"

#include "SMILESDataWriter.hpp"
#include "SMILESData.hpp"


namespace
{

	struct StringCmpFunc : public std::binary_function<std::string, std::string, bool>
	{

		bool operator()(const std::string& str1, const std::string& str2) const {
			if (str1.size() == str2.size())
				return std::lexicographical_compare(str1.begin(), str1.end(), str2.begin(), str2.end());

			return (str1.size() > str2.size());
		}
	};
}


using namespace CDPL;


Chem::SMILESDataWriter::SMILESDataWriter(const Base::DataIOBase& io_base): 
	ioBase(io_base), freeNodeIndex(0), freeEdgeIndex(0) {}

Chem::SMILESDataWriter::~SMILESDataWriter() {}

bool Chem::SMILESDataWriter::writeReaction(std::ostream& os, const Reaction& rxn)
{
	init(os, true);

	if (ctrlParameters.canonicalize)
		writeCanonSMILES(os, rxn);
	else
		writeNonCanonSMILES(os, rxn);

	writeName(os, rxn);

	return os.good();
}

bool Chem::SMILESDataWriter::writeMolGraph(std::ostream& os, const MolecularGraph& molgraph)
{
	init(os, false);

	if (ctrlParameters.canonicalize)
		writeCanonSMILES(os, molgraph);
	else
		writeNonCanonSMILES(os, molgraph);

	writeName(os, molgraph);

	return os.good();
}

template <typename T>
void Chem::SMILESDataWriter::writeName(std::ostream& os, const T& obj) const
{
	if (ctrlParameters.recordFormat == "S")
		return;

	if (ctrlParameters.recordFormat == "SN") 
		os << ' ' << getName(obj);
}

void Chem::SMILESDataWriter::init(std::ostream& os, bool rxn_context)
{
	ctrlParameters.strictErrorChecking    =  getStrictErrorCheckingParameter(ioBase); 
	ctrlParameters.writeHydrogens         = !getOrdinaryHydrogenDepleteParameter(ioBase); 
	ctrlParameters.canonicalize           =  getSMILESWriteCanonicalFormParameter(ioBase); 
	ctrlParameters.writeKekuleForm        =  getSMILESWriteKekuleFormParameter(ioBase); 
	ctrlParameters.writeIsotope           =  getSMILESWriteIsotopeParameter(ioBase); 
	ctrlParameters.writeAtomStereo        =  getSMILESWriteAtomStereoParameter(ioBase); 
	ctrlParameters.writeBondStereo        =  getSMILESWriteBondStereoParameter(ioBase); 
	ctrlParameters.writeRingBondStereo    =  getSMILESWriteRingBondStereoParameter(ioBase); 
	ctrlParameters.writeSingleBonds       =  getSMILESWriteSingleBondsParameter(ioBase); 
	ctrlParameters.writeAromaticBonds     =  getSMILESWriteAromaticBondsParameter(ioBase); 
	ctrlParameters.noOrganicSubset        =  getSMILESNoOrganicSubsetParameter(ioBase); 
	ctrlParameters.minStereoBondRingSize  =  getSMILESMinStereoBondRingSizeParameter(ioBase); 
	ctrlParameters.writeRxnAtomMappingID  =  rxn_context ? getSMILESRxnWriteAtomMappingIDParameter(ioBase) : getSMILESMolWriteAtomMappingIDParameter(ioBase);
	ctrlParameters.recordFormat           =  getSMILESRecordFormatParameter(ioBase); 

	if (ctrlParameters.recordFormat != "S" && ctrlParameters.recordFormat != "SN")
		throw Base::IOError("SMILESDataWriter: invalid smiles record format control-parameter");

	os.imbue(std::locale::classic());

	os << std::dec;

	if (os.tellp() > 0)
		os << getRecordSeparatorParameter(ioBase);
}

void Chem::SMILESDataWriter::init()
{
	ringClosureNumberStack.clear();

	highestRingClosureNumber = 0;
}

void Chem::SMILESDataWriter::writeNonCanonSMILES(std::ostream& os, const Reaction& rxn)
{
	bool first_comp = true;

	Reaction::ConstComponentIterator comps_end = rxn.getComponentsEnd(ReactionRole::REACTANT);

	for (Reaction::ConstComponentIterator it = rxn.getComponentsBegin(ReactionRole::REACTANT); it != comps_end; ++it) {
		const Molecule& comp = *it;

		if (comp.getNumAtoms() == 0)
			continue;

		if (!first_comp)
			os << SMILES::COMPONENT_SEPARATOR;
	
		writeNonCanonSMILES(os, comp);

		first_comp = false;
	}

	os << SMILES::REACTION_ROLE_SEPARATOR;

	first_comp = true;

	comps_end = rxn.getComponentsEnd(ReactionRole::AGENT);

	for (Reaction::ConstComponentIterator it = rxn.getComponentsBegin(ReactionRole::AGENT); it != comps_end; ++it) {
		const Molecule& comp = *it;

		if (comp.getNumAtoms() == 0)
			continue;

		if (!first_comp)
			os << SMILES::COMPONENT_SEPARATOR;

		writeNonCanonSMILES(os, comp);

		first_comp = false;
	}

	os << SMILES::REACTION_ROLE_SEPARATOR;

	first_comp = true;

	comps_end = rxn.getComponentsEnd(ReactionRole::PRODUCT);

	for (Reaction::ConstComponentIterator it = rxn.getComponentsBegin(ReactionRole::PRODUCT); it != comps_end; ++it) {
		const Molecule& comp = *it;

		if (comp.getNumAtoms() == 0)
			continue;

		if (!first_comp)
			os << SMILES::COMPONENT_SEPARATOR;

		writeNonCanonSMILES(os, comp);

		first_comp = false;
	}
}

void Chem::SMILESDataWriter::writeCanonSMILES(std::ostream& os, const Reaction& rxn)
{
	canonSMILESStrings.clear();

	Reaction::ConstComponentIterator comps_end = rxn.getComponentsEnd(ReactionRole::REACTANT);

	for (Reaction::ConstComponentIterator it = rxn.getComponentsBegin(ReactionRole::REACTANT); it != comps_end; ++it) {
		const Molecule& comp = *it;

		if (comp.getNumAtoms() == 0)
			continue;

		generateCanonComponentSMILES(comp);
	}

	outputCanonComponentSMILES(os);

	os << SMILES::REACTION_ROLE_SEPARATOR;

	canonSMILESStrings.clear();

	comps_end = rxn.getComponentsEnd(ReactionRole::AGENT);

	for (Reaction::ConstComponentIterator it = rxn.getComponentsBegin(ReactionRole::AGENT); it != comps_end; ++it) {
		const Molecule& comp = *it;

		if (comp.getNumAtoms() == 0)
			continue;

		generateCanonComponentSMILES(comp);
	}

	outputCanonComponentSMILES(os);

	os << SMILES::REACTION_ROLE_SEPARATOR;

	canonSMILESStrings.clear();

	comps_end = rxn.getComponentsEnd(ReactionRole::PRODUCT);

	for (Reaction::ConstComponentIterator it = rxn.getComponentsBegin(ReactionRole::PRODUCT); it != comps_end; ++it) {
		const Molecule& comp = *it;

		if (comp.getNumAtoms() == 0)
			continue;

		generateCanonComponentSMILES(comp);
	}

	outputCanonComponentSMILES(os);
}

void Chem::SMILESDataWriter::writeNonCanonSMILES(std::ostream& os, const MolecularGraph& molgraph)
{
	if (ctrlParameters.writeBondStereo) {
		if (!bondDirGenerator.get())
			bondDirGenerator.reset(new BondDirectionGenerator());

		bondDirGenerator->includeRingBonds(ctrlParameters.writeRingBondStereo);
		bondDirGenerator->setRingSizeLimit(ctrlParameters.minStereoBondRingSize);
	}

	bool first_comp = true;
	FragmentList& components = *getComponents(molgraph);
	FragmentList::ElementIterator comps_end = components.getElementsEnd();

	for (FragmentList::ElementIterator it = components.getElementsBegin(); it != comps_end; ++it) {
		Fragment& comp = *it;
	
		if (comp.getNumAtoms() == 0)
			continue;

		MolecularGraph* output_molgraph = &comp;

		if (!ctrlParameters.writeHydrogens) {
			buildHDepleteMolGraph(comp);
			output_molgraph = hDepleteMolGraph.get();
		} 
		
		if (ctrlParameters.writeBondStereo) {
			perceiveSSSR(*output_molgraph, false);
			bondDirGenerator->generate(*output_molgraph, bondDirections);
		}

		if (!first_comp)
			os << SMILES::COMPONENT_SEPARATOR;

		freeNodes();
		freeEdges();

		init();

		buildNonCanonDFSTree(*output_molgraph);
		distRingClosureNumbers();
		generateSMILES(os);

		first_comp = false;
	}
}

void Chem::SMILESDataWriter::writeCanonSMILES(std::ostream& os, const MolecularGraph& molgraph)
{
	canonSMILESStrings.clear();

	generateCanonComponentSMILES(molgraph);

	outputCanonComponentSMILES(os);
}

void Chem::SMILESDataWriter::generateCanonComponentSMILES(const MolecularGraph& molgraph)
{
	if (ctrlParameters.writeBondStereo) {
		if (!bondDirGenerator.get())
			bondDirGenerator.reset(new BondDirectionGenerator());

		bondDirGenerator->includeRingBonds(ctrlParameters.writeRingBondStereo);
		bondDirGenerator->setRingSizeLimit(ctrlParameters.minStereoBondRingSize);
	}

	unsigned int atom_prop_flags = AtomPropertyFlag::TYPE | AtomPropertyFlag::FORMAL_CHARGE | AtomPropertyFlag::H_COUNT;
	unsigned int bond_prop_flags = BondPropertyFlag::ORDER;

	if (!ctrlParameters.writeKekuleForm) {
		atom_prop_flags |= AtomPropertyFlag::AROMATICITY;
		bond_prop_flags |= BondPropertyFlag::AROMATICITY;
	}

	if (ctrlParameters.writeIsotope)
		atom_prop_flags |= AtomPropertyFlag::ISOTOPE;

	if (ctrlParameters.writeAtomStereo)
		atom_prop_flags |= AtomPropertyFlag::CONFIGURATION;

	if (ctrlParameters.writeBondStereo)
		bond_prop_flags |= BondPropertyFlag::CONFIGURATION;

	if (!canonNumberingGenerator.get())
		canonNumberingGenerator.reset(new CanonicalNumberingGenerator());

	canonNumberingGenerator->setAtomPropertyFlags(atom_prop_flags);
	canonNumberingGenerator->setBondPropertyFlags(bond_prop_flags);

	std::ostringstream oss;
	FragmentList& components = *getComponents(molgraph);
	FragmentList::ElementIterator comps_end = components.getElementsEnd();

	for (FragmentList::ElementIterator it = components.getElementsBegin(); it != comps_end; ++it) {
		Fragment& comp = *it;
	
		if (comp.getNumAtoms() == 0)
			continue;

		if (!ctrlParameters.writeHydrogens) {
			buildHDepleteMolGraph(comp);
			buildCanonMolGraph(*hDepleteMolGraph);

		} else 
			buildCanonMolGraph(comp);
		
		if (ctrlParameters.writeBondStereo) {
			perceiveSSSR(*canonMolGraph, true);
			bondDirGenerator->generate(*canonMolGraph, bondDirections);
		}

		freeNodes();
		freeEdges();

		init();

		buildCanonDFSTree(*canonMolGraph);
		distRingClosureNumbers();
		generateSMILES(oss);

		canonSMILESStrings.push_back(oss.str());

		oss.str(std::string());
	}
}

void Chem::SMILESDataWriter::outputCanonComponentSMILES(std::ostream& os)
{
	CanonSMILESList::iterator canon_smi_beg = canonSMILESStrings.begin();
	CanonSMILESList::iterator canon_smi_end = canonSMILESStrings.end();

	std::sort(canon_smi_beg, canon_smi_end, StringCmpFunc());

	bool first_comp = true;

	for (CanonSMILESList::iterator it = canon_smi_beg; it != canon_smi_end; ++it) {
		if (!first_comp)
			os << SMILES::COMPONENT_SEPARATOR;

		os << *it;

		first_comp = false;
	}
}

void Chem::SMILESDataWriter::buildHDepleteMolGraph(const MolecularGraph& molgraph)
{
	if (!hDepleteMolGraph.get())
		hDepleteMolGraph.reset(new Fragment());

	*hDepleteMolGraph = molgraph;

	std::size_t num_atoms = hDepleteMolGraph->getNumAtoms();

	for (std::size_t i = 0; i < num_atoms; i++) {
		const Atom& atom = hDepleteMolGraph->getAtom(i);
		
		if (getType(atom) == AtomType::H)
			continue;

		std::size_t exp_bond_count = getExplicitBondCount(atom, *hDepleteMolGraph);

		if (ctrlParameters.writeBondStereo) {
			if (exp_bond_count == 2 &&
				calcExplicitValence(atom, *hDepleteMolGraph) == 3 &&
				getExplicitBondCount(atom, *hDepleteMolGraph, 1, AtomType::H) == 1 &&
				calcImplicitHydrogenCount(atom, *hDepleteMolGraph) == 0) {

				bool has_db_geom = false;

				Atom::ConstBondIterator bonds_end = atom.getBondsEnd();
				Atom::ConstAtomIterator a_it = atom.getAtomsBegin();

				for (Atom::ConstBondIterator b_it = atom.getBondsBegin(); b_it != bonds_end; ++b_it, ++a_it) {
					const Bond& bond = *b_it;

					if (!hDepleteMolGraph->containsBond(bond))
						continue;

					const Atom& nbr_atom = *a_it;
				
					if (!hDepleteMolGraph->containsAtom(nbr_atom))
						continue;

					if (getOrder(bond) != 2)
						continue;

					const StereoDescriptor& stereo_desc = getStereoDescriptor(bond);
					unsigned int config = stereo_desc.getConfiguration();

					if ((config == BondConfiguration::CIS || config == BondConfiguration::TRANS) && stereo_desc.isValid(bond)) {
						has_db_geom = true;
						break;
					}
				}

				if (has_db_geom)
					continue;
			}
		}

		if (ctrlParameters.writeAtomStereo) {
			const StereoDescriptor& stereo_desc = getStereoDescriptor(atom);
			unsigned int config = stereo_desc.getConfiguration();

			if ((config == AtomConfiguration::S || config == AtomConfiguration::R) && stereo_desc.isValid(atom) && exp_bond_count < 4)
				continue;
		}

		Atom::ConstBondIterator bonds_end = atom.getBondsEnd();
		Atom::ConstAtomIterator a_it = atom.getAtomsBegin();

		for (Atom::ConstBondIterator b_it = atom.getBondsBegin(); b_it != bonds_end; ++b_it, ++a_it) {
			const Bond& bond = *b_it;

			if (!hDepleteMolGraph->containsBond(bond))
				continue;

			const Atom& nbr_atom = *a_it;

			if (!hDepleteMolGraph->containsAtom(nbr_atom))
				continue;

			if (getType(nbr_atom) != AtomType::H)
				continue;
			
			if (ctrlParameters.writeIsotope && getIsotope(nbr_atom) > 0)
				continue;
					
			if (ctrlParameters.writeRxnAtomMappingID &&
				getAtomMappingID(nbr_atom) > 0)
				continue;
		
			if (getFormalCharge(nbr_atom) != 0)
				continue;
	
			if (getExplicitBondCount(nbr_atom, *hDepleteMolGraph) != 1)
				continue;

			if (calcExplicitValence(nbr_atom, *hDepleteMolGraph) != 1)
				continue;

			if (calcImplicitHydrogenCount(nbr_atom, *hDepleteMolGraph) != 0)
				continue;

			std::size_t nbr_atom_idx = hDepleteMolGraph->getAtomIndex(nbr_atom);

			if (nbr_atom_idx < i)
				i--;

			hDepleteMolGraph->removeAtom(nbr_atom_idx);
			num_atoms--;
		}
	}
}

void Chem::SMILESDataWriter::buildCanonMolGraph(const MolecularGraph& molgraph)
{	
	if (!canonMolGraph.get())
		canonMolGraph.reset(new Fragment());
	else
		canonMolGraph->clear();

	canonNumberingGenerator->generate(molgraph, canonNumbering);

	canonAtomList.clear();

	std::transform(molgraph.getAtomsBegin(), molgraph.getAtomsEnd(), std::back_inserter(canonAtomList),
				   boost::bind(Internal::AddressOf<const Atom>(), _1));

	std::sort(canonAtomList.begin(), canonAtomList.end(), CanonAtomCmpFunc(*this, molgraph));

	std::for_each(canonAtomList.begin(), canonAtomList.end(),
				  boost::bind(&Fragment::addAtom, canonMolGraph.get(),
							  boost::bind(Util::Dereferencer<const Atom*, const Atom&>(), _1)));

	MolecularGraph::ConstBondIterator bonds_end = molgraph.getBondsEnd();
 
	for (MolecularGraph::ConstBondIterator it = molgraph.getBondsBegin(); it != bonds_end; ++it) {
		const Bond& bond = *it;

		if (canonMolGraph->containsAtom(bond.getBegin()) && canonMolGraph->containsAtom(bond.getEnd()))
			canonMolGraph->addBond(bond);
	}
}

void Chem::SMILESDataWriter::buildNonCanonDFSTree(const MolecularGraph& molgraph, DFSTreeNode* node)
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
		const Atom* nbr_atom = &*a_it;
		const Bond* bond = &*b_it;
	
		if (!molgraph.containsAtom(*nbr_atom) || !molgraph.containsBond(*bond))
			continue;

		DFSTreeNode* nbr_node = atomNodeMapping[molgraph.getAtomIndex(*nbr_atom)];

		if (nbr_node) {           
			if (lex_order > nbr_node->getLexicalOrder() && nbr_node != node->getParentEdge()->getBegin()) { // ring closure
				DFSTreeEdge* edge = allocEdge();

				node->addRingClosureOutEdge(edge);
				nbr_node->addRingClosureInEdge(edge);

				edge->setBond(bond);
				edge->setMolGraph(&molgraph);
				edge->setNodes(node, nbr_node);
			}

			continue;
		}

		DFSTreeEdge* edge = allocEdge();

		nbr_node = allocNode();

		nbr_node->setAtom(nbr_atom);
		nbr_node->setMolGraph(&molgraph);
		nbr_node->setParentEdge(edge);

		edge->setBond(bond);
		edge->setMolGraph(&molgraph);
		edge->setNodes(node, nbr_node);

		node->addChildEdge(edge);

		buildNonCanonDFSTree(molgraph, nbr_node);
	}
}

void Chem::SMILESDataWriter::buildCanonDFSTree(const MolecularGraph& molgraph, DFSTreeNode* node)
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

	typedef std::vector<std::pair<const Atom*, const Bond*> > NeighborList;

	NeighborList neighbors;

	Atom::ConstAtomIterator atoms_end = atom->getAtomsEnd();
	Atom::ConstBondIterator b_it = atom->getBondsBegin();

	for (Atom::ConstAtomIterator a_it = atom->getAtomsBegin(); a_it != atoms_end; ++a_it, ++b_it) {
		const Atom* nbr_atom = &*a_it;
		const Bond* bond = &*b_it;

		if (!molgraph.containsAtom(*nbr_atom) || !molgraph.containsBond(*bond))
			continue;

		neighbors.push_back(NeighborList::value_type(nbr_atom, bond));
	}

	NeighborList::iterator nbrs_beg = neighbors.begin();
	NeighborList::iterator nbrs_end = neighbors.end();

	std::sort(nbrs_beg, nbrs_end, 
			  boost::bind(std::less<std::size_t>(),
						  boost::bind(&MolecularGraph::getAtomIndex, boost::ref(molgraph), 
									  boost::bind(Util::Dereferencer<const Atom*, const Atom&>(), 
												  boost::bind(&NeighborList::value_type::first, _1))),
						  boost::bind(&MolecularGraph::getAtomIndex, boost::ref(molgraph), 
									  boost::bind(Util::Dereferencer<const Atom*, const Atom&>(), 
												  boost::bind(&NeighborList::value_type::first, _2)))));

	for (NeighborList::iterator it = nbrs_beg; it != nbrs_end; ++it) {
		const Atom* nbr_atom = it->first;
		const Bond* bond = it->second;
	
		DFSTreeNode* nbr_node = atomNodeMapping[molgraph.getAtomIndex(*nbr_atom)];

		if (nbr_node) {
			if (lex_order > nbr_node->getLexicalOrder() && nbr_node != node->getParentEdge()->getBegin()) { // ring closure
				DFSTreeEdge* edge = allocEdge();

				node->addRingClosureOutEdge(edge);
				nbr_node->addRingClosureInEdge(edge);

				edge->setBond(bond);
				edge->setMolGraph(&molgraph);
				edge->setNodes(node, nbr_node);
			}

			continue;
		}

		DFSTreeEdge* edge = allocEdge();

		nbr_node = allocNode();

		nbr_node->setAtom(nbr_atom);
		nbr_node->setMolGraph(&molgraph);
		nbr_node->setParentEdge(edge);

		edge->setBond(bond);
		edge->setMolGraph(&molgraph);
		edge->setNodes(node, nbr_node);

		node->addChildEdge(edge);

		buildCanonDFSTree(molgraph, nbr_node);
	}
}

Chem::SMILESDataWriter::DFSTreeNode* Chem::SMILESDataWriter::createRootNode(const MolecularGraph& molgraph)
{
	DFSTreeNode* root_node = allocNode();
	const Atom* root_atom = 0;

	if (!ctrlParameters.writeAtomStereo)
		root_atom = &molgraph.getAtom(0);

	else {
		MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

		for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(); it != atoms_end; ++it) {
			root_atom = &*it;

			std::size_t bond_count = getExplicitBondCount(*root_atom, molgraph);

			if (bond_count < 3 || bond_count > 4)
				break;

			const StereoDescriptor& stereo_desc = getStereoDescriptor(*root_atom);
			unsigned int config = stereo_desc.getConfiguration();

			if (config != AtomConfiguration::R && config != AtomConfiguration::S)
				break;

			if (!stereo_desc.isValid(*root_atom))
				break;
		}
	}

	root_node->setAtom(root_atom);
	root_node->setMolGraph(&molgraph);
	root_node->setParentEdge(0);

	return root_node;
}
 
void Chem::SMILESDataWriter::distRingClosureNumbers()
{
	NodeList::iterator nodes_end = componentNodes.end();

	for (NodeList::iterator it = componentNodes.begin(); it != nodes_end; ++it) {
		DFSTreeNode* node = *it;

		std::for_each(node->getRingClosureInEdgesBegin(), node->getRingClosureInEdgesEnd(),
					  boost::bind(&DFSTreeEdge::setRingClosureNumber, _1,
								  boost::bind(&SMILESDataWriter::getRingClosureNumber, this)));

		std::for_each(node->getRingClosureOutEdgesBegin(), node->getRingClosureOutEdgesEnd(),
					  boost::bind(&SMILESDataWriter::putRingClosureNumber, this,
								  boost::bind(&DFSTreeEdge::getRingClosureNumber, _1)));
	}
}

void Chem::SMILESDataWriter::generateSMILES(std::ostream& os) const
{
	componentNodes.front()->generateSMILES(os);
}

std::size_t Chem::SMILESDataWriter::getRingClosureNumber()
{
	if (ringClosureNumberStack.empty()) {
		if (highestRingClosureNumber == 99)
			throw Base::IOError("SMILESDataWriter: ran out of ring closure numbers");

		return ++highestRingClosureNumber;
	}

	std::size_t top_no = ringClosureNumberStack.back();

	ringClosureNumberStack.pop_back();

	return top_no;
}

void Chem::SMILESDataWriter::putRingClosureNumber(std::size_t no)
{
	ringClosureNumberStack.push_back(no);
}

Chem::SMILESDataWriter::DFSTreeNode* Chem::SMILESDataWriter::allocNode()
{
	DFSTreeNode* node;

	if (freeNodeIndex == allocNodes.size()) {
		DFSTreeNode::SharedPointer node_ptr(new DFSTreeNode(*this));
		allocNodes.push_back(node_ptr);

		node = node_ptr.get();
		freeNodeIndex++;

	} else {
		node = allocNodes[freeNodeIndex++].get();
		node->clear();
	}

	componentNodes.push_back(node);

	return node;
}

void Chem::SMILESDataWriter::freeNodes()
{
	componentNodes.clear();
	freeNodeIndex = 0;
}

Chem::SMILESDataWriter::DFSTreeEdge* Chem::SMILESDataWriter::allocEdge()
{
	DFSTreeEdge* edge;

	if (freeEdgeIndex == allocEdges.size()) {
		DFSTreeEdge::SharedPointer edge_ptr(new DFSTreeEdge(*this));
		allocEdges.push_back(edge_ptr);

		edge = edge_ptr.get();
		freeEdgeIndex++;

	} else {
		edge = allocEdges[freeEdgeIndex++].get();
		edge->clear();
	}

	return edge;
}

void Chem::SMILESDataWriter::freeEdges()
{
	freeEdgeIndex = 0;
}


// -------------------------

bool Chem::SMILESDataWriter::CanonAtomCmpFunc::operator()(const Atom* atom1, const Atom* atom2) const
{
	const Util::STArray& can_numbering = writer.canonNumbering;

	return (can_numbering[molGraph.getAtomIndex(*atom1)] < can_numbering[molGraph.getAtomIndex(*atom2)]);
}


// -------------------------

Chem::SMILESDataWriter::DFSTreeNode::DFSTreeNode(SMILESDataWriter& writer): 
	writer(writer), molGraph(0), atom(0), parentEdge(0) {}

void Chem::SMILESDataWriter::DFSTreeNode::clear()
{
	childEdges.clear();
	ringClosureInEdges.clear();
	ringClosureOutEdges.clear();
}
				
void Chem::SMILESDataWriter::DFSTreeNode::setAtom(const Atom* atm)
{
	atom = atm;
}

void Chem::SMILESDataWriter::DFSTreeNode::setMolGraph(const MolecularGraph* molgraph)
{
	molGraph = molgraph;
}

const Chem::Atom* Chem::SMILESDataWriter::DFSTreeNode::getAtom() const
{
	return atom;
}

void Chem::SMILESDataWriter::DFSTreeNode::setLexicalOrder(std::size_t order)
{
	lexicalOrder = order;
}

std::size_t Chem::SMILESDataWriter::DFSTreeNode::getLexicalOrder() const
{
	return lexicalOrder;
}

void Chem::SMILESDataWriter::DFSTreeNode::setParentEdge(DFSTreeEdge* edge)
{
	parentEdge = edge;
}

const Chem::SMILESDataWriter::DFSTreeEdge* Chem::SMILESDataWriter::DFSTreeNode::getParentEdge() const
{
	return parentEdge;
}

void Chem::SMILESDataWriter::DFSTreeNode::addChildEdge(DFSTreeEdge* edge)
{
	childEdges.push_back(edge);
}

void Chem::SMILESDataWriter::DFSTreeNode::addRingClosureInEdge(DFSTreeEdge* edge)
{
	ringClosureInEdges.push_back(edge);
}

void Chem::SMILESDataWriter::DFSTreeNode::addRingClosureOutEdge(DFSTreeEdge* edge)
{
	ringClosureOutEdges.push_back(edge);
}

Chem::SMILESDataWriter::EdgeIterator Chem::SMILESDataWriter::DFSTreeNode::getRingClosureInEdgesBegin()
{
	return ringClosureInEdges.begin();
}

Chem::SMILESDataWriter::EdgeIterator Chem::SMILESDataWriter::DFSTreeNode::getRingClosureInEdgesEnd()
{
	return ringClosureInEdges.end();
}

Chem::SMILESDataWriter::EdgeIterator Chem::SMILESDataWriter::DFSTreeNode::getRingClosureOutEdgesBegin()
{
	return ringClosureOutEdges.begin();
}

Chem::SMILESDataWriter::EdgeIterator Chem::SMILESDataWriter::DFSTreeNode::getRingClosureOutEdgesEnd()
{
	return ringClosureOutEdges.end();
}

void Chem::SMILESDataWriter::DFSTreeNode::generateSMILES(std::ostream& os) const
{
	writeAtomString(os);
	writeRingClosures(os);
	writeChildNodes(os);
}

void Chem::SMILESDataWriter::DFSTreeNode::writeAtomString(std::ostream& os) const
{
	long charge = getFormalCharge(*atom);
	unsigned int atom_type = getType(*atom);
	std::size_t isotope = (writer.ctrlParameters.writeIsotope ? getIsotope(*atom) : 0);
	std::size_t aam_id = (writer.ctrlParameters.writeRxnAtomMappingID ? getAtomMappingID(*atom) : 0);
	int stereo_rot = (writer.ctrlParameters.writeAtomStereo ? getStereoParity() : 0);
	std::size_t impl_h_count = calcImplicitHydrogenCount(*atom, *molGraph);
	bool in_brackets;

	if (!(in_brackets = (writer.ctrlParameters.noOrganicSubset || charge != 0 || isotope > 0 || stereo_rot != 0 || aam_id > 0))) {
		std::size_t valence = calcExplicitValence(*atom, *molGraph) + impl_h_count;

		switch (atom_type) {

			case AtomType::B:
				in_brackets = (valence != 3);
				break;

			case AtomType::C:
				in_brackets = (valence != 4);
				break;

			case AtomType::N:
				in_brackets = (valence != 3 || 
							   (!writer.ctrlParameters.writeKekuleForm && getAromaticityFlag(*atom) && impl_h_count > 0));
				break;

			case AtomType::O:
				in_brackets = (valence != 2);
				break;

			case AtomType::P:
				in_brackets = (valence != 3 && valence != 5);
				break;

			case AtomType::S:
				in_brackets = (valence != 2 && valence != 4 && valence != 6);
				break;

			case AtomType::F:
			case AtomType::Cl:
			case AtomType::Br:
			case AtomType::I:
				in_brackets = (valence != 1);
				break;

			default:
				in_brackets = true;
				break;
		}
	}

	if (in_brackets) {
		os << SMILES::AtomString::SPECIAL_ATOM_PREFIX;

		writeIsotope(os, isotope);
		writeAtomSymbol(os, atom_type);
		writeAtomStereo(os, stereo_rot);
		writeHCount(os, impl_h_count);
		writeCharge(os, charge);
		writeReactionAtomMappingID(os, aam_id);

		os << SMILES::AtomString::SPECIAL_ATOM_SUFFIX;

		return;
	}

	writeAtomSymbol(os, atom_type);
}

void Chem::SMILESDataWriter::DFSTreeNode::writeRingClosures(std::ostream& os) const
{
	std::for_each(ringClosureInEdges.begin(), ringClosureInEdges.end(),
				  boost::bind(&DFSTreeNode::writeRingClosureNumber, this, boost::ref(os), _1));

	EdgeList::const_iterator edges_end = ringClosureOutEdges.end();

	for (EdgeList::const_iterator it = ringClosureOutEdges.begin(); it != edges_end; ++it) {
		const DFSTreeEdge* edge = *it;

		edge->writeBondSymbol(os);
		writeRingClosureNumber(os, edge); 
	}
}

void Chem::SMILESDataWriter::DFSTreeNode::writeChildNodes(std::ostream& os) const
{
	std::size_t num_edges = childEdges.size();

	for (std::size_t i = 0; i < num_edges; i++) {
		const DFSTreeEdge* edge = childEdges[i];

		if (i < num_edges - 1) {
			os << SMILES::BRANCH_PREFIX;
			
			edge->writeBondSymbol(os);
			edge->getEnd()->generateSMILES(os);

			os << SMILES::BRANCH_SUFFIX;

		} else {
			edge->writeBondSymbol(os);
			edge->getEnd()->generateSMILES(os);
		}
	}
}

void Chem::SMILESDataWriter::DFSTreeNode::writeIsotope(std::ostream& os, std::size_t isotope) const
{
	if (isotope > 0)
		os << isotope;
}	

void Chem::SMILESDataWriter::DFSTreeNode::writeAtomSymbol(std::ostream& os, unsigned int atom_type) const
{
	if (atom_type == AtomType::UNKNOWN || atom_type > AtomType::MAX_ATOMIC_NO) {
		os << SMILES::AtomString::UNDEF_ELEMENT_SYMBOL;
		return;
	}

	const std::string& symbol = AtomDictionary::getSymbol(atom_type);

	if (writer.ctrlParameters.writeKekuleForm) {
		os << symbol;
		return;
	}

	bool arom = getAromaticityFlag(*atom);

	if (arom) {
		switch (atom_type) {

			case AtomType::C:
			case AtomType::N:
			case AtomType::O:
			case AtomType::S:
			case AtomType::P:
			case AtomType::As:
			case AtomType::Se:
			case AtomType::Te:
				break;

			default:
				arom = false;
				break;
		}
	}

	if (!arom) {
		os << symbol;
		return;
	}

	os << std::tolower(symbol[0], std::locale::classic());

	if (symbol.length() > 1)
		os << symbol[1];
}

void Chem::SMILESDataWriter::DFSTreeNode::writeAtomStereo(std::ostream& os, int stereo_rot) const
{
	using namespace SMILES;

	if (stereo_rot == 0)
		return;

	if (stereo_rot < 0)
		os << AtomString::CHIRAL_CLASS_PREFIX;
	else
		os << AtomString::CHIRAL_CLASS_PREFIX 
		   << AtomString::CHIRAL_CLASS_PREFIX;
}

void Chem::SMILESDataWriter::DFSTreeNode::writeHCount(std::ostream& os, std::size_t h_count) const
{
	if (h_count == 0)
		return;

	os << SMILES::AtomString::H_COUNT_PREFIX;

	if (h_count != 1)
		os << h_count;
}

void Chem::SMILESDataWriter::DFSTreeNode::writeCharge(std::ostream& os, long charge) const
{
	using namespace SMILES;

	if (charge == 0)
		return;

	os << (charge < 0 ? AtomString::NEGATIVE_CHARGE_PREFIX : AtomString::POSITIVE_CHARGE_PREFIX);

	if (charge > 1 || charge < -1)
		os << (charge > 0 ? charge : -charge);
}

void Chem::SMILESDataWriter::DFSTreeNode::writeReactionAtomMappingID(std::ostream& os, std::size_t aam_id) const
{
	if (aam_id == 0)
		return;

	os << SMILES::AtomString::ATOM_MAPPING_ID_PREFIX << aam_id;
}

void Chem::SMILESDataWriter::DFSTreeNode::writeRingClosureNumber(std::ostream& os, const DFSTreeEdge* edge) const
{
	std::size_t closure_no = edge->getRingClosureNumber();

	if (closure_no > 9)
		os << SMILES::CLOSURE_NO_PREFIX;

	os << closure_no;
}

int Chem::SMILESDataWriter::DFSTreeNode::getStereoParity() const
{
	const StereoDescriptor& stereo_desc = calcStereoDescriptor(*atom, *molGraph, 0);
	unsigned int config = stereo_desc.getConfiguration();

	if (config != AtomConfiguration::R && config != AtomConfiguration::S)
		return 0;

	std::size_t num_bonds = stereo_desc.getNumReferenceAtoms();

	if (num_bonds < 3) // sanity_check
		return 0;

	std::vector<const Atom*> smiles_ref_atoms;

	for (EdgeList::const_iterator it = ringClosureInEdges.begin(), end = ringClosureInEdges.end(); it != end; ++it)
		smiles_ref_atoms.push_back((*it)->getBegin()->atom);

	for (EdgeList::const_iterator it = ringClosureOutEdges.begin(), end = ringClosureOutEdges.end(); it != end; ++it)
		smiles_ref_atoms.push_back((*it)->getEnd()->atom);

	for (EdgeList::const_iterator it = childEdges.begin(), end = childEdges.end(); it != end; ++it)
		smiles_ref_atoms.push_back((*it)->getEnd()->atom);

	if (parentEdge) {
		if (smiles_ref_atoms.size() == 2)
			smiles_ref_atoms.insert(smiles_ref_atoms.begin(), atom);
	
		smiles_ref_atoms.push_back(parentEdge->getBegin()->atom);

	} else {
		if (smiles_ref_atoms.size() == 3)
			smiles_ref_atoms.push_back(atom);

		else if (smiles_ref_atoms.size() == 4) {
			const Atom* first_nbr = smiles_ref_atoms.front();

			smiles_ref_atoms.erase(smiles_ref_atoms.begin());
			smiles_ref_atoms.push_back(first_nbr);
		}
	}

	if (smiles_ref_atoms.size() != 4) // sanity check
		return 0;

	unsigned int perm_parity = stereo_desc.getPermutationParity(*smiles_ref_atoms[0], *smiles_ref_atoms[1], *smiles_ref_atoms[2], *smiles_ref_atoms[3]);

	if (perm_parity == 1)
		return (config == AtomConfiguration::S ? -1 : 1);
	else if (perm_parity == 2)
		return (config == AtomConfiguration::S ? 1 : -1);
	else
		return 0;
}


// -------------------------

Chem::SMILESDataWriter::DFSTreeEdge::DFSTreeEdge(SMILESDataWriter& writer): writer(writer), molGraph(0) {}

void Chem::SMILESDataWriter::DFSTreeEdge::clear() {}

void Chem::SMILESDataWriter::DFSTreeEdge::setBond(const Bond* bnd)
{
	bond = bnd;
}

const Chem::Bond* Chem::SMILESDataWriter::DFSTreeEdge::getBond() const
{
	return bond;
}

void Chem::SMILESDataWriter::DFSTreeEdge::setMolGraph(const MolecularGraph* molgraph)
{
	molGraph = molgraph;
}

void Chem::SMILESDataWriter::DFSTreeEdge::setNodes(DFSTreeNode* begin, DFSTreeNode* end)
{
	nodes[0] = begin;
	nodes[1] = end;
}

const Chem::SMILESDataWriter::DFSTreeNode* Chem::SMILESDataWriter::DFSTreeEdge::getBegin() const
{
	return nodes[0];
}

const Chem::SMILESDataWriter::DFSTreeNode* Chem::SMILESDataWriter::DFSTreeEdge::getEnd() const
{
	return nodes[1];
}

void Chem::SMILESDataWriter::DFSTreeEdge::setRingClosureNumber(std::size_t closure_no)
{
	ringClosureNumber = closure_no;
}

std::size_t Chem::SMILESDataWriter::DFSTreeEdge::getRingClosureNumber() const
{
	return ringClosureNumber;
}

void Chem::SMILESDataWriter::DFSTreeEdge::writeBondSymbol(std::ostream& os) const
{
	std::size_t order = getOrder(*bond);

	if (writer.ctrlParameters.writeBondStereo && order == 1) {
		
		switch (writer.bondDirections[molGraph->getBondIndex(*bond)]) {

			case BondDirection::UP:
				os << SMILES::BondSymbol::UP_DIR_FLAG;
				return;

			case BondDirection::DOWN:
				os << SMILES::BondSymbol::DOWN_DIR_FLAG;
				return;

			default:
				break;
		}
	}

	if (!writer.ctrlParameters.writeKekuleForm && getAromaticityFlag(*bond)) {
		if (writer.ctrlParameters.writeAromaticBonds) 
			os << SMILES::BondSymbol::AROMATIC_BOND;
		return;	
	}

	switch (order) {

		case 1:
			if (writer.ctrlParameters.writeSingleBonds) 
				os << SMILES::BondSymbol::SINGLE_BOND;
			return;

		case 2:
			os << SMILES::BondSymbol::DOUBLE_BOND;
			return;

		case 3:
			os << SMILES::BondSymbol::TRIPLE_BOND;
			return;

		default:
			if (writer.ctrlParameters.strictErrorChecking)
				throw Base::IOError("SMILESDataWriter: invalid bond order");
	}
}
