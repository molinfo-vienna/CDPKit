/* 
 * TorsionDriverImpl.cpp 
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
#include <cmath>
#include <mutex>

#include "CDPL/ConfGen/MolecularGraphFunctions.hpp"
#include "CDPL/ConfGen/BondFunctions.hpp"
#include "CDPL/ConfGen/ReturnCode.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/MolecularGraphFunctions.hpp"
#include "CDPL/Chem/UtilityFunctions.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/HybridizationState.hpp"
#include "CDPL/ForceField/MMFF94InteractionParameterizer.hpp"
#include "CDPL/ForceField/MMFF94InteractionData.hpp"
#include "CDPL/ForceField/Exceptions.hpp"
#include "CDPL/Internal/AtomFunctions.hpp"

#include "TorsionDriverImpl.hpp"
#include "FallbackTorsionLibrary.hpp"
#include "UtilityFunctions.hpp"


using namespace CDPL;


namespace
{

    struct SymmetryPattern
    {

        SymmetryPattern(Chem::MolecularGraph::SharedPointer&& ptn, std::size_t sym):
            pattern(std::move(ptn)), symmetry(sym) {}

        Chem::MolecularGraph::SharedPointer pattern;
        std::size_t                         symmetry;
    };

    typedef std::vector<SymmetryPattern> SymmetryPatternList;

    SymmetryPatternList symmetryPatterns;

    std::once_flag initSymmetryPatternsFlag;

    void initSymmetryPatterns()
    {
        symmetryPatterns.emplace_back(Chem::parseSMARTS("[*:1]-[*X4^3:1](-[#1])(-[#1])-[#1]"), 3);

        symmetryPatterns.emplace_back(Chem::parseSMARTS("[*:1]-[*X4^3:1](-[F])(-[F])-[F]"), 3);
        symmetryPatterns.emplace_back(Chem::parseSMARTS("[*:1]-[*X4^3:1](-[Cl])(-[Cl])-[Cl]"), 3);
        symmetryPatterns.emplace_back(Chem::parseSMARTS("[*:1]-[*X4^3:1](-[Br])(-[Br])-[Br]"), 3);
        symmetryPatterns.emplace_back(Chem::parseSMARTS("[*:1]-[*X4^3:1](-[I])(-[I])-[I]"), 3);
        symmetryPatterns.emplace_back(Chem::parseSMARTS("[*:1]-[*X4^3:1](-[CH3])(-[CH3])-[CH3]"), 3);

        symmetryPatterns.emplace_back(Chem::parseSMARTS("[CH3]-[NX3:1](-[CH3])-[CX3:1](=O)-[#1,*]"), 2);
        symmetryPatterns.emplace_back(Chem::parseSMARTS("[#1]-[NX3:1](-[#1])-[CX3:1](=O)-[#1,*]"), 2);

        symmetryPatterns.emplace_back(Chem::parseSMARTS("[*:1]-[a:1]1[c](-[#1])[c](-[#1])[c](-[#1])[c]1(-[#1])"), 2);
        symmetryPatterns.emplace_back(Chem::parseSMARTS("[*:1]-[a:1]1[c](-[#1])[nX2][nX2][c]1(-[#1])"), 2);
        symmetryPatterns.emplace_back(Chem::parseSMARTS("[*:1]-[a:1]1[nX2][c](-[#1])[c](-[#1])[nX2]1"), 2);
        symmetryPatterns.emplace_back(Chem::parseSMARTS("[*:1]-[a:1]1[nX2][nX2][nX2][nX2]1"), 2);

        symmetryPatterns.emplace_back(Chem::parseSMARTS("[*:1]-[a:1]1[c](-[#1])[c](-[#1])[a](-[#1,*X1,CH3])[c](-[#1])[c]1(-[#1])"), 2);
        symmetryPatterns.emplace_back(Chem::parseSMARTS("[*:1]-[a:1]1[c](-[#1])[nX2][a](-[#1,*X1,CH3])[nX2][c]1(-[#1])"), 2);
        symmetryPatterns.emplace_back(Chem::parseSMARTS("[*:1]-[a:1]1[c](-[#1])[c](-[#1])[aX2][c](-[#1])[c]1(-[#1])"), 2);
        symmetryPatterns.emplace_back(Chem::parseSMARTS("[*:1]-[a:1]1[nX2][c](-[#1])[a](-[#1,*X1,CH3])[c](-[#1])[nX2]1"), 2);
        symmetryPatterns.emplace_back(Chem::parseSMARTS("[*:1]-[a:1]1[nX2][c](-[#1])[aX2][c](-[#1])[nX2]1"), 2);

        symmetryPatterns.emplace_back(Chem::parseSMARTS("[*:1]-[*X2:1]#[*X2]-[#1,*X1,CH3]"), 360);
        symmetryPatterns.emplace_back(Chem::parseSMARTS("[*:1]-[*X2:1]#[*X1]"), 360);
    };

    const std::size_t MAX_CONF_DATA_CACHE_SIZE    = 1000;
    const double      MIN_TORSION_ANGLE_TOLERANCE = 30.0;
    const double      DUP_TORSION_ANGLE_THRESHOLD = 10.0;

    bool hasAngleWithinDistance(double angle, const ConfGen::FragmentTreeNode::DoubleArray& angles, double dist)
    {
        using namespace ConfGen;

        for (FragmentTreeNode::DoubleArray::const_iterator it = angles.begin(), end = angles.end(); it != end; ++it)
            if (getAbsoluteAngleDistance(angle, *it) < dist)
                return true;

        return false;
    }
}


ConfGen::TorsionDriverImpl::TorsionDriverImpl(): 
    settings(TorsionDriverSettings::DEFAULT), fragTree(MAX_CONF_DATA_CACHE_SIZE)
{
    torLibs.push_back(TorsionLibrary::get());

    torRuleMatcher.findUniqueMappingsOnly(true);
    torRuleMatcher.findAllRuleMappings(true);
    torRuleMatcher.stopAtFirstMatchingRule(true);

    subSearch.uniqueMappingsOnly(true);

    std::call_once(initSymmetryPatternsFlag, &initSymmetryPatterns);
} 

ConfGen::TorsionDriverImpl::~TorsionDriverImpl() {}

ConfGen::TorsionDriverSettings& ConfGen::TorsionDriverImpl::getSettings()
{
    return settings;
}

void ConfGen::TorsionDriverImpl::clearTorsionLibraries()
{
    torLibs.clear();
}

void ConfGen::TorsionDriverImpl::addTorsionLibrary(const TorsionLibrary::SharedPointer& lib)
{
    torLibs.push_back(lib);
}

void ConfGen::TorsionDriverImpl::setup(const Chem::MolecularGraph& molgraph)
{
    std::size_t num_bonds = molgraph.getNumBonds();
    
    rotBondMask.resize(num_bonds);
    rotBondMask.reset();
    rotBonds.clear();

    for (std::size_t i = 0; i < num_bonds; i++) {
        const Chem::Bond& bond = molgraph.getBond(i);

        if (isRotatableBond(bond, molgraph, settings.sampleHeteroAtomHydrogens())) {
            rotBonds.push_back(&bond);
            rotBondMask.set(i);
        }
    }

    splitIntoFragments(molgraph, fragments, rotBondMask, false);
    setup(fragments, molgraph, rotBonds.begin(), rotBonds.end());
}

void ConfGen::TorsionDriverImpl::setup(const Chem::MolecularGraph& molgraph, const Util::BitSet& bond_mask)
{
    rotBonds.clear();

    for (Util::BitSet::size_type i = bond_mask.find_first(); i != Util::BitSet::npos; i = bond_mask.find_next(i))
        rotBonds.push_back(&molgraph.getBond(i));

    splitIntoFragments(molgraph, fragments, bond_mask, false);
    setup(fragments, molgraph, rotBonds.begin(), rotBonds.end());
}

void ConfGen::TorsionDriverImpl::setMMFF94Parameters(const ForceField::MMFF94InteractionData& ia_data, ForceFieldInteractionMask& ia_mask)
{
    fragTree.getRoot()->distMMFF94Parameters(ia_data, ia_mask);
}

void ConfGen::TorsionDriverImpl::setMMFF94Parameters(const ForceField::MMFF94InteractionData& ia_data)
{
    mmff94InteractionMask.setup(ia_data);

    fragTree.getRoot()->distMMFF94Parameters(ia_data, mmff94InteractionMask);
}

bool ConfGen::TorsionDriverImpl::setMMFF94Parameters()
{
    using namespace ForceField;

    const Chem::MolecularGraph& molgraph = *fragTree.getMolecularGraph();

    if (!mmff94Parameterizer.get())
        mmff94Parameterizer.reset(new MMFF94InteractionParameterizer());

    if (!mmff94Data.get())
        mmff94Data.reset(new MMFF94InteractionData());

    try {
        if (parameterizeMMFF94Interactions(molgraph, *mmff94Parameterizer, *mmff94Data, settings.getForceFieldType(),
                                           settings.strictForceFieldParameterization(), settings.getDielectricConstant(),
                                           settings.getDistanceExponent()) == ReturnCode::SUCCESS) {

            setMMFF94Parameters(*mmff94Data);        
            return true;
        }

        if (logCallback)
            logCallback("Force field setup failed!\n");

    } catch (const Error& e) {
        if (logCallback)
            logCallback("Force field setup failed: " + std::string(e.what()) + '\n');
    }

    return false;
}

void ConfGen::TorsionDriverImpl::clearInputCoordinates()
{
    fragTree.getRoot()->clearConformersDownwards();
}

void ConfGen::TorsionDriverImpl::clearInputCoordinates(std::size_t frag_idx)
{
    fragTree.getFragmentNode(frag_idx)->clearConformersUpwards();
}

void ConfGen::TorsionDriverImpl::addInputCoordinates(const Math::Vector3DArray& coords)
{
    for (std::size_t i = 0, num_frags = fragTree.getNumFragments(); i < num_frags; i++) {
        FragmentTreeNode* node = fragTree.getFragmentNode(i);

        node->addConformer(coords);
        
        if (node->getParent())
            node->getParent()->clearConformersUpwards();
    }
}

void ConfGen::TorsionDriverImpl::setInputCoordinates(const Math::Vector3DArray& coords)
{
    fragTree.getRoot()->clearConformersDownwards();

    for (std::size_t i = 0, num_frags = fragTree.getNumFragments(); i < num_frags; i++) {
        FragmentTreeNode* node = fragTree.getFragmentNode(i);

        node->addConformer(coords);
    }
}

void ConfGen::TorsionDriverImpl::addInputCoordinates(const Math::Vector3DArray& coords, std::size_t frag_idx)
{
    doAddInputCoordinates(coords, frag_idx);
}

void ConfGen::TorsionDriverImpl::addInputCoordinates(const ConformerData& conf_data, std::size_t frag_idx)
{
    doAddInputCoordinates(conf_data, frag_idx);
}

void ConfGen::TorsionDriverImpl::addInputCoordinates(const ConformerData::SharedPointer& conf_data, std::size_t frag_idx)
{
    doAddInputCoordinates(conf_data, frag_idx);
}

void ConfGen::TorsionDriverImpl::setInputCoordinates(const Math::Vector3DArray& coords, std::size_t frag_idx)
{
    fragTree.getFragmentNode(frag_idx)->clearConformers();

    doAddInputCoordinates(coords, frag_idx);
}

void ConfGen::TorsionDriverImpl::setInputCoordinates(const ConformerData& conf_data, std::size_t frag_idx)
{
    fragTree.getFragmentNode(frag_idx)->clearConformers();

    doAddInputCoordinates(conf_data, frag_idx);
}

void ConfGen::TorsionDriverImpl::setInputCoordinates(const ConformerData::SharedPointer& conf_data, std::size_t frag_idx)
{
    fragTree.getFragmentNode(frag_idx)->clearConformers();

    doAddInputCoordinates(conf_data, frag_idx);
}

void ConfGen::TorsionDriverImpl::setAbortCallback(const CallbackFunction& func)
{
    fragTree.setAbortCallback(func);
}

const ConfGen::CallbackFunction& ConfGen::TorsionDriverImpl::getAbortCallback() const
{
    return fragTree.getAbortCallback();
}

void ConfGen::TorsionDriverImpl::setTimeoutCallback(const CallbackFunction& func)
{
    fragTree.setTimeoutCallback(func);
}

const ConfGen::CallbackFunction& ConfGen::TorsionDriverImpl::getTimeoutCallback() const
{
    return fragTree.getTimeoutCallback();
}

void ConfGen::TorsionDriverImpl::setLogMessageCallback(const LogMessageCallbackFunction& func)
{
    logCallback = func;
}

const ConfGen::LogMessageCallbackFunction& ConfGen::TorsionDriverImpl::getLogMessageCallback() const
{
    return logCallback;
}

std::size_t ConfGen::TorsionDriverImpl::getNumFragments() const
{
    return fragTree.getNumFragments();
}

const Chem::Fragment& ConfGen::TorsionDriverImpl::getFragment(std::size_t idx) const
{
    return *fragTree.getFragment(idx);
}

ConfGen::FragmentTreeNode& ConfGen::TorsionDriverImpl::getFragmentNode(std::size_t idx) const
{
    return *fragTree.getFragmentNode(idx);
}

unsigned int ConfGen::TorsionDriverImpl::generateConformers()
{
    unsigned int ret_code = fragTree.getRoot()->generateConformers(settings.getEnergyWindow(), settings.getMaxPoolSize());

    if (ret_code != ReturnCode::SUCCESS)
        return ret_code;

    if (settings.orderByEnergy())
        fragTree.getRoot()->orderConformersByEnergy();
    
    return ReturnCode::SUCCESS;
}

std::size_t ConfGen::TorsionDriverImpl::getNumConformers() const
{
    return fragTree.getRoot()->getNumConformers();
}

ConfGen::ConformerData& ConfGen::TorsionDriverImpl::getConformer(std::size_t idx)
{
    return fragTree.getRoot()->getConformer(idx);
}

ConfGen::TorsionDriverImpl::ConstConformerIterator ConfGen::TorsionDriverImpl::getConformersBegin() const
{
    return fragTree.getRoot()->getConformers().begin();
}

ConfGen::TorsionDriverImpl::ConstConformerIterator ConfGen::TorsionDriverImpl::getConformersEnd() const
{
    return fragTree.getRoot()->getConformers().end();
}

template <typename ConfData>
void ConfGen::TorsionDriverImpl::doAddInputCoordinates(const ConfData& conf_data, std::size_t frag_idx) const
{
    FragmentTreeNode* node = fragTree.getFragmentNode(frag_idx);

    node->addConformer(conf_data);
        
    if (node->getParent())
        node->getParent()->clearConformersUpwards();
}

void ConfGen::TorsionDriverImpl::assignTorsionAngles(FragmentTreeNode* node)
{
    using namespace Chem;

    if (!node->hasChildren())
        return;

    assignTorsionAngles(node->getLeftChild());
    assignTorsionAngles(node->getRightChild());

    const Bond* bond = node->getSplitBond();

    if (!bond)
        return;

    std::size_t rot_sym = getRotationalSymmetry(*bond);
    const Atom* const* bond_atoms = node->getSplitBondAtoms();
    const TorsionRuleMatch* match = getTorsionRuleAngles(*bond, node, rot_sym);

    if (match && node->getNumTorsionAngles() != 0) {
        const Atom* const* match_atoms = match->getAtoms();
                
        if (match_atoms[1] == bond_atoms[0])
            node->setTorsionReferenceAtoms(match_atoms[0], match_atoms[3]);
        else
            node->setTorsionReferenceAtoms(match_atoms[3], match_atoms[0]);
    }
        
    if (logCallback) {
        logCallback("Torsion angle assignment for bond #" + std::to_string(fragTree.getMolecularGraph()->getBondIndex(*bond)) + ":\n");

        if (match)
            logCallback(" Matching rule: " + match->getRule().getMatchPatternString() + '\n');
        else
            logCallback(" No matching rule found - fallback to 30° grid search!\n");
    }

    if (node->getNumTorsionAngles() == 0) {
        // fallback: rotation in 30° steps

        for (std::size_t i = 0, num_angles = 12 / rot_sym; i < num_angles; i++) 
            node->addTorsionAngle(i * 30.0);

        node->setTorsionReferenceAtoms(getFirstNeighborAtom(bond_atoms[0], bond_atoms[1], node), 
                                       getFirstNeighborAtom(bond_atoms[1], bond_atoms[0], node));

        if (!node->getTorsionReferenceAtoms()[0] || !node->getTorsionReferenceAtoms()[1])
            node->setTorsionReferenceAtoms(0, 0);
    } 

    if (logCallback) {
        logCallback(" Symmetry: C" + std::to_string(rot_sym) + '\n');
        logCallback(" Angles: ");

        for (FragmentTreeNode::DoubleArray::const_iterator it = node->getTorsionAngles().begin(), end = node->getTorsionAngles().end(); it != end; ++it)
            logCallback(std::to_string(*it) + ' ');

        logCallback("\n");
    }
}

const ConfGen::TorsionRuleMatch* ConfGen::TorsionDriverImpl::getTorsionRuleAngles(const Chem::Bond& bond, FragmentTreeNode* node, std::size_t rot_sym)
{
    using namespace Chem;

    const MolecularGraph& molgraph = *fragTree.getMolecularGraph();
    const TorsionRuleMatch* match = 0;

    for (TorsionLibraryList::const_reverse_iterator it = torLibs.rbegin(), end = torLibs.rend(); it != end; ++it) {
        torRuleMatcher.setTorsionLibrary(*it);

        if (torRuleMatcher.findMatches(bond, molgraph, false)) {
            match = &torRuleMatcher.getMatch(0);
            break;
        }
    } 

    if (!match) {
        torRuleMatcher.setTorsionLibrary(getFallbackTorsionLibrary());

        if (!torRuleMatcher.findMatches(bond, molgraph, false))
            return 0;

        match = &torRuleMatcher.getMatch(0);
    }

    bool mult_matches1 = false;
    bool mult_matches2 = false;
    
    auto match_atoms = match->getAtoms();

    for (std::size_t i = 0, num_matches = torRuleMatcher.getNumMatches(); i < num_matches; i++) {
        auto other_match_atoms = torRuleMatcher.getMatch(i).getAtoms();

        if (match_atoms[1] == other_match_atoms[1]) {
            mult_matches1 |= (match_atoms[0] != other_match_atoms[0]);
            mult_matches2 |= (match_atoms[3] != other_match_atoms[3]);
            continue;
        }

        if (match_atoms[1] == other_match_atoms[2]) {
            mult_matches1 |= (match_atoms[0] != other_match_atoms[3]);
            mult_matches2 |= (match_atoms[3] != other_match_atoms[0]);
        }
    }

    double angle_offs1 = (mult_matches1 ? getAngleOffset(*match_atoms[1]) : 0.0);
    double angle_offs2 = (mult_matches2 ? getAngleOffset(*match_atoms[2]) : 0.0);
    
    const TorsionRule& rule = match->getRule();

    workingAngles.clear();
    
    for (TorsionRule::ConstAngleEntryIterator it = rule.getAnglesBegin(), end = rule.getAnglesEnd(); it != end; ++it)
        workingAngles.push_back(normalizeAngle(it->getAngle()));
    
    if (settings.sampleAngleToleranceRanges()) {
        for (TorsionRule::ConstAngleEntryIterator it = rule.getAnglesBegin(), end = rule.getAnglesEnd(); it != end; ++it) {
            double tol = it->getTolerance1();

            if (tol < MIN_TORSION_ANGLE_TOLERANCE)
                continue;

            addOffsetAngles(it->getAngle(), tol);
        }
    }

    if (angle_offs1 != 0.0)
        for (std::size_t i = 0, num_angles = workingAngles.size(); i < num_angles; i++)
            addOffsetAngles(workingAngles[i], angle_offs1);

    if (angle_offs2 != 0.0)
        for (std::size_t i = 0, num_angles = workingAngles.size(); i < num_angles; i++)
            addOffsetAngles(workingAngles[i], angle_offs2);

    double ident_rot = 360.0 / rot_sym;
    
    for (auto angle : workingAngles)
        node->addTorsionAngle(std::fmod(angle, ident_rot));

    node->removeDuplicateTorsionAngles();

    return match;
}

void ConfGen::TorsionDriverImpl::addOffsetAngles(double angle, double offs)
{
    double tmp = normalizeAngle(angle + offs);

    if (!hasAngleWithinDistance(tmp, workingAngles, DUP_TORSION_ANGLE_THRESHOLD))
        workingAngles.push_back(tmp);

    tmp = normalizeAngle(angle - offs);

    if (!hasAngleWithinDistance(tmp, workingAngles, DUP_TORSION_ANGLE_THRESHOLD))
        workingAngles.push_back(tmp);
}

double ConfGen::TorsionDriverImpl::getAngleOffset(const Chem::Atom& atom) const
{
    using namespace Chem;

    switch (getHybridizationState(atom)) {

        case HybridizationState::SP3:
            if (getAromaticityFlag(atom) || Internal::isPlanarNitrogen(atom, *fragTree.getMolecularGraph()))
                return 180.0;
            
            return 120.0;

        case HybridizationState::SP2:
            return 180.0;
    }
    
    return 0.0;
}

std::size_t ConfGen::TorsionDriverImpl::getRotationalSymmetry(const Chem::Bond& bond)
{
    using namespace Chem;

    const MolecularGraph& molgraph = *fragTree.getMolecularGraph();
    std::size_t node_bond_idx = molgraph.getBondIndex(bond);

    for (const auto& ptn_data : symmetryPatterns) {
        const MolecularGraph& ptn = *ptn_data.pattern;
        std::size_t num_ptn_bonds = ptn.getNumBonds();
        std::size_t ptn_bond_idx = 0;

        for ( ; ptn_bond_idx < num_ptn_bonds; ptn_bond_idx++) {
            const Bond& bond = ptn.getBond(ptn_bond_idx);
        
            if (getAtomMappingID(bond.getBegin()) != 0 && getAtomMappingID(bond.getEnd()) != 0)
                break;
        }

        if (ptn_bond_idx == num_ptn_bonds)
            continue;

        subSearch.clearBondMappingConstraints();
        subSearch.addBondMappingConstraint(ptn_bond_idx, node_bond_idx);
        subSearch.setQuery(ptn);
    
        if (!subSearch.mappingExists(molgraph)) 
            continue;

        return ptn_data.symmetry;
    }

    return 1;
}

const Chem::Atom* ConfGen::TorsionDriverImpl::getFirstNeighborAtom(const Chem::Atom* ctr_atom, const Chem::Atom* excl_atom,
                                                                   const FragmentTreeNode* node) const
{
    using namespace Chem;

    Atom::ConstBondIterator b_it = ctr_atom->getBondsBegin();
    const MolecularGraph& parent_molgraph = *fragTree.getMolecularGraph();

    for (Atom::ConstAtomIterator a_it = ctr_atom->getAtomsBegin(), a_end = ctr_atom->getAtomsEnd(); a_it != a_end; ++a_it, ++b_it) {
        const Atom& nbr_atom = *a_it;

        if (excl_atom == &nbr_atom)
            continue;

        if (!parent_molgraph.containsBond(*b_it))
            continue;

        if (node->containsAtom(nbr_atom))
            return &nbr_atom;
    }

    return 0;
}
