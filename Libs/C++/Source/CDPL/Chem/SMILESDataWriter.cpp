/* 
 * SMILESDataWriter.cpp 
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
#include <sstream>
#include <locale>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <iterator>
#include <cassert>

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
#include "CDPL/Chem/AtomPropertyFlag.hpp"
#include "CDPL/Chem/BondPropertyFlag.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/AtomDictionary.hpp"
#include "CDPL/Chem/AtomType.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"
#include "CDPL/Chem/CanonicalNumberingCalculator.hpp"
#include "CDPL/Base/Exceptions.hpp"
#include "CDPL/Base/DataIOBase.hpp"
#include "CDPL/Internal/AtomFunctions.hpp"

#include "SMILESDataWriter.hpp"
#include "SMILESData.hpp"


namespace
{

    struct StringCmpFunc
    {

        bool operator()(const std::string& str1, const std::string& str2) const {
            if (str1.size() == str2.size())
                return std::lexicographical_compare(str1.begin(), str1.end(), str2.begin(), str2.end());

            return (str1.size() > str2.size());
        }
    };

    int getBondConfigPriority(unsigned int config)
    {
        using namespace CDPL::Chem;
        
        switch (config) {

            case BondConfiguration::NONE:
                return 1;

            case BondConfiguration::CIS:
            case BondConfiguration::TRANS:
                return 2;

            default:
                return 0;
        }
    }
    
    constexpr std::size_t MAX_NODE_CACHE_SIZE = 1000;
    constexpr std::size_t MAX_EDGE_CACHE_SIZE = 1000;
}


using namespace CDPL;


Chem::SMILESDataWriter::SMILESDataWriter(const Base::DataIOBase& io_base): 
    ioBase(io_base), nodeCache(std::bind(&SMILESDataWriter::createNode, this), MAX_NODE_CACHE_SIZE),
    edgeCache(std::bind(&SMILESDataWriter::createEdge, this), MAX_EDGE_CACHE_SIZE)
{}

Chem::SMILESDataWriter::~SMILESDataWriter() {}

bool Chem::SMILESDataWriter::writeReaction(std::ostream& os, const Reaction& rxn)
{
    init(os, true);

    if (ctrlParameters.recordFormat == "NS") {
        auto& name = getName(rxn);
        
        if (!name.empty())
            os << name << ' ';
    }
    
    if (ctrlParameters.canonicalize)
        writeCanonSMILES(os, rxn);
    else
        writeNonCanonSMILES(os, rxn);

    if (ctrlParameters.recordFormat == "SN") {
        auto& name = getName(rxn);
        
        if (!name.empty())
            os << ' ' << name;
    }
    
    return os.good();
}

bool Chem::SMILESDataWriter::writeMolGraph(std::ostream& os, const MolecularGraph& molgraph)
{
    init(os, false);

    if (ctrlParameters.recordFormat == "NS") {
        auto& name = getName(molgraph);
        
        if (!name.empty())
            os << name << ' ';
    }
    
    if (ctrlParameters.canonicalize)
        writeCanonSMILES(os, molgraph);
    else
        writeNonCanonSMILES(os, molgraph);

    if (ctrlParameters.recordFormat == "SN") {
         auto& name = getName(molgraph);
        
        if (!name.empty())
            os << ' ' << name;
    }
    
    return os.good();
}

void Chem::SMILESDataWriter::init(std::ostream& os, bool rxn_context)
{
    ctrlParameters.strictErrorChecking    = getStrictErrorCheckingParameter(ioBase);
    ctrlParameters.outputHydrogens        = !getOrdinaryHydrogenDepleteParameter(ioBase);
    ctrlParameters.canonicalize           = getSMILESOutputCanonicalFormParameter(ioBase);
    ctrlParameters.outputKekuleForm       = getSMILESOutputKekuleFormParameter(ioBase);
    ctrlParameters.outputIsotope          = getSMILESOutputIsotopeParameter(ioBase);
    ctrlParameters.outputAtomStereo       = getSMILESOutputAtomStereoParameter(ioBase);
    ctrlParameters.outputBondStereo       = getSMILESOutputBondStereoParameter(ioBase);
    ctrlParameters.outputRingBondStereo   = getSMILESOutputRingBondStereoParameter(ioBase);
    ctrlParameters.outputSingleBonds      = getSMILESOutputSingleBondsParameter(ioBase);
    ctrlParameters.outputAromaticBonds    = getSMILESOutputAromaticBondsParameter(ioBase);
    ctrlParameters.noOrganicSubset        = getSMILESNoOrganicSubsetParameter(ioBase);
    ctrlParameters.minStereoBondRingSize  = getSMILESMinStereoBondRingSizeParameter(ioBase);
    ctrlParameters.outputRxnAtomMappingID = rxn_context ? getSMILESRxnOutputAtomMappingIDParameter(ioBase) : getSMILESMolOutputAtomMappingIDParameter(ioBase);
    ctrlParameters.recordFormat           = getSMILESRecordFormatParameter(ioBase);

    if (ctrlParameters.recordFormat != "S" && ctrlParameters.recordFormat != "SN" && ctrlParameters.recordFormat != "NS")
        throw Base::IOError("SMILESDataWriter: invalid smiles record format control-parameter '" + ctrlParameters.recordFormat + '\'');

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
    bool first_comp = true;
    FragmentList& components = *getComponents(molgraph);
    FragmentList::ElementIterator comps_end = components.getElementsEnd();

    for (FragmentList::ElementIterator it = components.getElementsBegin(); it != comps_end; ++it) {
        Fragment& comp = *it;
    
        if (comp.getNumAtoms() == 0)
            continue;

        MolecularGraph* output_molgraph = &comp;

        if (!ctrlParameters.outputHydrogens) {
            buildHDepleteMolGraph(comp);
            output_molgraph = hDepleteMolGraph.get();
        } 

        if (!first_comp)
            os << SMILES::COMPONENT_SEPARATOR;

        freeNodes();
        freeEdges();

        init();

        buildNonCanonDFSTree(*output_molgraph);
        distRingClosureNumbers();
        distBondDirections(molgraph);
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
    unsigned int atom_prop_flags = AtomPropertyFlag::TYPE | AtomPropertyFlag::FORMAL_CHARGE | AtomPropertyFlag::H_COUNT;
    unsigned int bond_prop_flags = BondPropertyFlag::ORDER;

    if (!ctrlParameters.outputKekuleForm) {
        atom_prop_flags |= AtomPropertyFlag::AROMATICITY;
        bond_prop_flags |= BondPropertyFlag::AROMATICITY;
    }

    if (ctrlParameters.outputIsotope)
        atom_prop_flags |= AtomPropertyFlag::ISOTOPE;

    if (ctrlParameters.outputAtomStereo)
        atom_prop_flags |= AtomPropertyFlag::CONFIGURATION;

    if (ctrlParameters.outputBondStereo)
        bond_prop_flags |= BondPropertyFlag::CONFIGURATION;

    if (!canonNumberingCalculator.get())
        canonNumberingCalculator.reset(new CanonicalNumberingCalculator());

    canonNumberingCalculator->setAtomPropertyFlags(atom_prop_flags);
    canonNumberingCalculator->setBondPropertyFlags(bond_prop_flags);

    std::ostringstream oss;
    FragmentList& components = *getComponents(molgraph);
    FragmentList::ElementIterator comps_end = components.getElementsEnd();

    for (FragmentList::ElementIterator it = components.getElementsBegin(); it != comps_end; ++it) {
        Fragment& comp = *it;
    
        if (comp.getNumAtoms() == 0)
            continue;

        if (!ctrlParameters.outputHydrogens) {
            buildHDepleteMolGraph(comp);
            buildCanonMolGraph(*hDepleteMolGraph);

        } else 
            buildCanonMolGraph(comp);

        freeNodes();
        freeEdges();

        init();

        buildCanonDFSTree(*canonMolGraph);
        distRingClosureNumbers();
        distBondDirections(molgraph);
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

        std::size_t exp_bond_count = Internal::getExplicitBondCount(atom, *hDepleteMolGraph);

        if (ctrlParameters.outputBondStereo) {
            if (exp_bond_count == 2 &&
                Internal::calcExplicitValence(atom, *hDepleteMolGraph) == 3 &&
                Internal::getExplicitBondCount(atom, *hDepleteMolGraph, 1, AtomType::H) == 1 &&
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

        if (ctrlParameters.outputAtomStereo) {
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
            
            if (ctrlParameters.outputIsotope && getIsotope(nbr_atom) > 0)
                continue;
                    
            if (ctrlParameters.outputRxnAtomMappingID &&
                getAtomMappingID(nbr_atom) > 0)
                continue;
        
            if (getFormalCharge(nbr_atom) != 0)
                continue;
    
            if (Internal::getExplicitBondCount(nbr_atom, *hDepleteMolGraph) != 1)
                continue;

            if (Internal::calcExplicitValence(nbr_atom, *hDepleteMolGraph) != 1)
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

    canonNumberingCalculator->calculate(molgraph, canonNumbering);

    canonAtomList.clear();

    std::transform(molgraph.getAtomsBegin(), molgraph.getAtomsEnd(), std::back_inserter(canonAtomList),
                   [](const Atom& atom) { return &atom; });

    std::sort(canonAtomList.begin(), canonAtomList.end(), CanonAtomCmpFunc(*this, molgraph));

    std::for_each(canonAtomList.begin(), canonAtomList.end(),
                  std::bind(&Fragment::addAtom, canonMolGraph.get(),
                            std::bind<const Atom&>([](const Atom* atom) -> const Atom& { return *atom; }, std::placeholders::_1)));

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
    using namespace std::placeholders;
    
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
              std::bind(std::less<std::size_t>(),
                        std::bind(&MolecularGraph::getAtomIndex, std::ref(molgraph), 
                                  std::bind(Util::Dereferencer<const Atom*, const Atom&>(), 
                                            std::bind(&NeighborList::value_type::first, _1))),
                        std::bind(&MolecularGraph::getAtomIndex, std::ref(molgraph), 
                                  std::bind(Util::Dereferencer<const Atom*, const Atom&>(), 
                                            std::bind(&NeighborList::value_type::first, _2)))));

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

    if (!ctrlParameters.outputAtomStereo)
        root_atom = &molgraph.getAtom(0);

    else {
        MolecularGraph::ConstAtomIterator atoms_end = molgraph.getAtomsEnd();

        for (MolecularGraph::ConstAtomIterator it = molgraph.getAtomsBegin(); it != atoms_end; ++it) {
            root_atom = &*it;

            std::size_t bond_count = Internal::getExplicitBondCount(*root_atom, molgraph);

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
    using namespace std::placeholders;
    
    NodeList::iterator nodes_end = componentNodes.end();

    for (NodeList::iterator it = componentNodes.begin(); it != nodes_end; ++it) {
        DFSTreeNode* node = *it;

        std::for_each(node->getRingClosureInEdgesBegin(), node->getRingClosureInEdgesEnd(),
                      std::bind(&DFSTreeEdge::setRingClosureNumber, _1,
                                std::bind(&SMILESDataWriter::getRingClosureNumber, this)));

        std::for_each(node->getRingClosureOutEdgesBegin(), node->getRingClosureOutEdgesEnd(),
                      std::bind(&SMILESDataWriter::putRingClosureNumber, this,
                                std::bind(&DFSTreeEdge::getRingClosureNumber, _1)));
    }
}

void Chem::SMILESDataWriter::collectStereoBondEdges(DFSTreeNode* node, const MolecularGraph& molgraph)
{
    for (auto* edge : *node) {
        if (edge->wasVisited())
            continue;

        edge->setVisited(true);
        
        const Bond& bond = *edge->getBond();

        if (!hasStereoDescriptor(bond)) {
            if (isStereoCenter(bond, molgraph, false, true, true, 0)) {
                edge->setConfiguration(BondConfiguration::EITHER);
                edge->getBegin()->setStereoBondEdge(edge);
                edge->getEnd()->setStereoBondEdge(edge);
            }
            
            continue;
        }
        
        const StereoDescriptor& descr = getStereoDescriptor(bond);
        unsigned int config = descr.getConfiguration();

        if (config == BondConfiguration::NONE)
            continue;

        edge->setConfiguration(BondConfiguration::EITHER);
        edge->getBegin()->setStereoBondEdge(edge);
        edge->getEnd()->setStereoBondEdge(edge);
            
        if ((config != BondConfiguration::CIS && config != BondConfiguration::TRANS) || !descr.isValid(bond))
            continue;
        
        if (getRingFlag(bond)) {
            if (!ctrlParameters.outputRingBondStereo)
                continue;

            if (ctrlParameters.minStereoBondRingSize > 0 &&
                (getSizeOfSmallestContainingFragment(bond, *getSSSR(molgraph)) < ctrlParameters.minStereoBondRingSize))
                continue;
        }

        edge->setConfiguration(config);
        
        const Atom* const* descr_ref_atoms = descr.getReferenceAtoms();

        if (descr_ref_atoms[1] == edge->getBegin()->getAtom() && descr_ref_atoms[2] == edge->getEnd()->getAtom())
            edge->setConfigRefAtoms(descr_ref_atoms[0], descr_ref_atoms[3]);
        else if (descr_ref_atoms[1] == edge->getEnd()->getAtom() && descr_ref_atoms[2] == edge->getBegin()->getAtom())
            edge->setConfigRefAtoms(descr_ref_atoms[3], descr_ref_atoms[0]);
        else
            continue;
        
        stereoBondEdges.push_back(edge);
    }
}

void Chem::SMILESDataWriter::distBondDirections(const MolecularGraph& molgraph)
{
    if (!ctrlParameters.outputBondStereo)
        return;
    
    stereoBondEdges.clear();

    for (auto* node : componentNodes)
        collectStereoBondEdges(node, molgraph);

    for (auto* node : componentNodes)
        for (auto* edge : *node) 
            edge->setVisited(false);
    
    for (auto* edge : stereoBondEdges)
        distBondDirections(edge);
}

void Chem::SMILESDataWriter::distBondDirections(DFSTreeEdge* edge)
{
    if (edge->wasVisited())
        return;
    
    edge->setVisited(true);

    if (edge->getConfiguration() == BondConfiguration::EITHER)
        return;

    DFSTreeEdge* ref_edge1 = getBondStereoRefEdge(edge->getBegin(), edge);
    DFSTreeEdge* ref_edge2 = getBondStereoRefEdge(edge->getEnd(), edge);

    if (ref_edge1 && ref_edge2) {
        const Atom* const* config_ref_atoms = edge->getConfigRefAtoms();
        unsigned int       config           = edge->getConfiguration();
        const DFSTreeNode* ref_nodes[2]     = {ref_edge1->getOtherNode(edge->getBegin()), ref_edge2->getOtherNode(edge->getEnd())};

        if ((ref_nodes[0]->getAtom() == config_ref_atoms[0]) ^ (ref_nodes[1]->getAtom() == config_ref_atoms[1]))
            config = (config == BondConfiguration::CIS ? BondConfiguration::TRANS : BondConfiguration::CIS);

        int ref_node1_level = ref_edge1->getLevel(ref_nodes[0]);
        int ref_node2_level = ref_edge2->getLevel(ref_nodes[1]);

        if (ref_node1_level == 0 && ref_node2_level == 0) {
            ref_edge1->setDirection(ref_nodes[0], 1);
            ref_edge2->setDirection(ref_nodes[1], config == BondConfiguration::CIS ? 1 : -1);

        } else if (ref_node1_level != 0 && ref_node2_level == 0)
            ref_edge2->setDirection(ref_nodes[1], config == BondConfiguration::CIS ? ref_node1_level : -ref_node1_level);

        else if (ref_node1_level == 0 && ref_node2_level != 0)
            ref_edge1->setDirection(ref_nodes[0], config == BondConfiguration::CIS ? ref_node2_level : -ref_node2_level);

        else {
            // already defined
        }
    }

    for (std::size_t i = 0; i < 2; i++) {
        DFSTreeNode* node = (i == 0 ? edge->getBegin() : edge->getEnd());

        for (auto* edge : *node) {
            if (edge->wasVisited())
                continue;

            edge->setVisited(true);

            DFSTreeNode* nbr_node = edge->getOtherNode(node);

            if (nbr_node->getStereoBondEdge())
                distBondDirections(nbr_node->getStereoBondEdge());
        }
    }
}

Chem::SMILESDataWriter::DFSTreeEdge* Chem::SMILESDataWriter::getBondStereoRefEdge(DFSTreeNode* node, const DFSTreeEdge* excl_edge)
{
    DFSTreeEdge* ref_edge = 0;
    int ref_nbr_cfg_pri = 0;
        
    for (auto* edge : *node) {
        if (edge == excl_edge)
            continue;
        
        const Bond& bond = *edge->getBond();

        if (getOrder(bond) != 1)
            continue;
        
        if (edge->getDirection() != 0)
            return edge;

        int nbr_cfg_pri = getBondConfigPriority(edge->getOtherNode(node)->getStereoBondEdge() ?
                                                edge->getOtherNode(node)->getStereoBondEdge()->getConfiguration() :
                                                BondConfiguration::NONE);

        if (!ref_edge || nbr_cfg_pri > ref_nbr_cfg_pri) {
            ref_edge = edge;
            ref_nbr_cfg_pri = nbr_cfg_pri;
        }
    }

    if (!ref_edge)
        return 0;
    
    if (ref_edge->getDirection() == 0) {
        DFSTreeNode* ref_node = ref_edge->getOtherNode(node);

        if (ref_node->hasDirEdge()) {
             for (auto* edge : *ref_node) {
                 if (edge->getDirection() == 0)
                     continue;

                 ref_edge->setDirection(node, -edge->getLevel(edge->getOtherNode(ref_node)));
                 break;
             }
        }
    }
    
    return ref_edge;
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

Chem::SMILESDataWriter::DFSTreeNode* Chem::SMILESDataWriter::createNode()
{
    return new DFSTreeNode(*this);
}

Chem::SMILESDataWriter::DFSTreeEdge* Chem::SMILESDataWriter::createEdge()
{
    return new DFSTreeEdge(*this);
}

Chem::SMILESDataWriter::DFSTreeNode* Chem::SMILESDataWriter::allocNode()
{
    DFSTreeNode* node = nodeCache.get();

    node->clear();
    componentNodes.push_back(node);

    return node;
}

Chem::SMILESDataWriter::DFSTreeEdge* Chem::SMILESDataWriter::allocEdge()
{
    DFSTreeEdge* edge = edgeCache.get();

    edge->clear();
    
    return edge;
}

void Chem::SMILESDataWriter::freeNodes()
{
    componentNodes.clear();
    nodeCache.putAll();
}

void Chem::SMILESDataWriter::freeEdges()
{
    edgeCache.putAll();
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
    edges.clear();
    
    parentEdge = 0;
    dirEdge = false;
    stereoBondEdge = 0;
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

Chem::SMILESDataWriter::DFSTreeEdge* Chem::SMILESDataWriter::DFSTreeNode::getParentEdge() const
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

Chem::SMILESDataWriter::EdgeIterator Chem::SMILESDataWriter::DFSTreeNode::getChildEdgesBegin()
{
    return childEdges.begin();
}

Chem::SMILESDataWriter::EdgeIterator Chem::SMILESDataWriter::DFSTreeNode::getChildEdgesEnd()
{
    return childEdges.end();
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

Chem::SMILESDataWriter::EdgeIterator Chem::SMILESDataWriter::DFSTreeNode::begin()
{
    collectEdges();
    
    return edges.begin();
}

Chem::SMILESDataWriter::EdgeIterator Chem::SMILESDataWriter::DFSTreeNode::end()
{
    collectEdges();
    
    return edges.end();
}

void Chem::SMILESDataWriter::DFSTreeNode::hasDirEdge(bool has)
{
    dirEdge = has;
}

bool Chem::SMILESDataWriter::DFSTreeNode::hasDirEdge() const
{
    return dirEdge;
}
                
void Chem::SMILESDataWriter::DFSTreeNode::setStereoBondEdge(DFSTreeEdge* edge)
{
    stereoBondEdge = edge;
}

Chem::SMILESDataWriter::DFSTreeEdge* Chem::SMILESDataWriter::DFSTreeNode::getStereoBondEdge() const
{
    return stereoBondEdge;
}
                
void Chem::SMILESDataWriter::DFSTreeNode::collectEdges()
{
    if (!edges.empty())
        return;

    if (parentEdge)
        edges.push_back(parentEdge);

    edges.insert(edges.end(), childEdges.begin(), childEdges.end());
    edges.insert(edges.end(), ringClosureOutEdges.begin(), ringClosureOutEdges.end());
    edges.insert(edges.end(), ringClosureInEdges.begin(), ringClosureInEdges.end());
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
    std::size_t isotope = (writer.ctrlParameters.outputIsotope ? getIsotope(*atom) : 0);
    std::size_t aam_id = (writer.ctrlParameters.outputRxnAtomMappingID ? getAtomMappingID(*atom) : 0);
    int stereo_rot = (writer.ctrlParameters.outputAtomStereo ? getStereoParity() : 0);
    std::size_t impl_h_count = calcImplicitHydrogenCount(*atom, *molGraph);
    bool in_brackets;

    if (!(in_brackets = (writer.ctrlParameters.noOrganicSubset || charge != 0 || isotope > 0 || stereo_rot != 0 || aam_id > 0))) {
        std::size_t valence = Internal::calcExplicitValence(*atom, *molGraph) + impl_h_count;

        switch (atom_type) {

            case AtomType::B:
                in_brackets = (valence != 3);
                break;

            case AtomType::C:
                in_brackets = (valence != 4);
                break;

            case AtomType::N:
                in_brackets = (valence != 3 || 
                               (!writer.ctrlParameters.outputKekuleForm && getAromaticityFlag(*atom) && impl_h_count > 0));
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
                  std::bind(&DFSTreeNode::writeRingClosureNumber, this,
                            std::ref(os), std::placeholders::_1));

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

    if (writer.ctrlParameters.outputKekuleForm) {
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

Chem::SMILESDataWriter::DFSTreeNode* Chem::SMILESDataWriter::DFSTreeEdge::getBegin() const
{
    return nodes[0];
}

Chem::SMILESDataWriter::DFSTreeNode* Chem::SMILESDataWriter::DFSTreeEdge::getEnd() const
{
    return nodes[1];
}

Chem::SMILESDataWriter::DFSTreeNode* Chem::SMILESDataWriter::DFSTreeEdge::getOtherNode(const DFSTreeNode* node) const
{
    if (nodes[0] == node)
        return nodes[1];

    assert(nodes[1] == node);

    return nodes[0];
}
         
void Chem::SMILESDataWriter::DFSTreeEdge::setRingClosureNumber(std::size_t closure_no)
{
    ringClosureNumber = closure_no;
}

std::size_t Chem::SMILESDataWriter::DFSTreeEdge::getRingClosureNumber() const
{
    return ringClosureNumber;
}

void Chem::SMILESDataWriter::DFSTreeEdge::setDirection(const DFSTreeNode* node, int level)
{
    switch (level) {

        case 1:
            direction = (node == nodes[1] ? SMILES::BondSymbol::UP_DIR_FLAG : SMILES::BondSymbol::DOWN_DIR_FLAG);
            break;

        case -1:
            direction = (node == nodes[1] ? SMILES::BondSymbol::DOWN_DIR_FLAG : SMILES::BondSymbol::UP_DIR_FLAG);
            break;

        default:
            direction = 0;
            return;
    }

    nodes[0]->hasDirEdge(true);
    nodes[1]->hasDirEdge(true);
}

char Chem::SMILESDataWriter::DFSTreeEdge::getDirection() const
{
    return direction;
}

int Chem::SMILESDataWriter::DFSTreeEdge::getLevel(const DFSTreeNode* node) const
{
    if (direction == 0)
        return 0;

    switch (direction) {

        case SMILES::BondSymbol::UP_DIR_FLAG:
            return (node == nodes[1] ? 1 : -1);

        case SMILES::BondSymbol::DOWN_DIR_FLAG:
            return (node == nodes[1] ? -1 : 1);

        default:
            break;
    }
    
    return 0;
}

void  Chem::SMILESDataWriter::DFSTreeEdge::clear()
{
    direction         = 0;
    config            = BondConfiguration::NONE;
    configRefAtoms[0] = 0;
    configRefAtoms[1] = 0;
    visited           = false;
}

void Chem::SMILESDataWriter::DFSTreeEdge::setConfiguration(unsigned int config)
{
    this->config = config;
}

unsigned int Chem::SMILESDataWriter::DFSTreeEdge::getConfiguration() const
{
    return config;
}

void Chem::SMILESDataWriter::DFSTreeEdge::setConfigRefAtoms(const Atom* ref1, const Atom* ref2)
{
    configRefAtoms[0] = ref1;
    configRefAtoms[1] = ref2;
}

const Chem::Atom* const* Chem::SMILESDataWriter::DFSTreeEdge::getConfigRefAtoms() const
{
    return configRefAtoms;
}

void Chem::SMILESDataWriter::DFSTreeEdge::setVisited(bool vis)
{
    visited = vis;
}

bool Chem::SMILESDataWriter::DFSTreeEdge::wasVisited() const
{
    return visited;
}

void Chem::SMILESDataWriter::DFSTreeEdge::writeBondSymbol(std::ostream& os) const
{
    std::size_t order = getOrder(*bond);

    if (writer.ctrlParameters.outputBondStereo && order == 1 && direction != 0) {
        os << direction;
        return;
    }

    if (!writer.ctrlParameters.outputKekuleForm && getAromaticityFlag(*bond)) {
        if (writer.ctrlParameters.outputAromaticBonds) 
            os << SMILES::BondSymbol::AROMATIC_BOND;
        return;    
    }

    switch (order) {

        case 1:
            if (writer.ctrlParameters.outputSingleBonds) 
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
