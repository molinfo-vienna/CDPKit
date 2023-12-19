/* 
 * CIPConfigurationLabelerImpl.cpp 
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
#include <limits>

#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/CIPDescriptor.hpp"

#include "CIPConfigurationLabelerImpl.hpp"
#include "CIPTetrahedralCenter.hpp"
#include "CIPSp2BondCenter.hpp"


using namespace CDPL;


Chem::CIPConfigurationLabelerImpl::CIPConfigurationLabelerImpl():
    molGraph(0)
{}

Chem::CIPConfigurationLabelerImpl::CIPConfigurationLabelerImpl(const CIPConfigurationLabelerImpl& labeler)
{
    copy(labeler);
}

Chem::CIPConfigurationLabelerImpl::~CIPConfigurationLabelerImpl() {}

void Chem::CIPConfigurationLabelerImpl::setup(const MolecularGraph& molgraph)
{
    molGraph = &molgraph;
    
    digraph.setMolecularGraph(molgraph);
    stereoCenters.clear();

    extractAtomCenters();
    extractBondCenters();
}

unsigned int Chem::CIPConfigurationLabelerImpl::getLabel(const Atom& atom)
{
    return getLabelGeneric(atom);
}

unsigned int Chem::CIPConfigurationLabelerImpl::getLabel(const Bond& bond)
{
    return getLabelGeneric(bond);
}
            
void Chem::CIPConfigurationLabelerImpl::copy(const CIPConfigurationLabelerImpl& labeler)
{
    if (!labeler.molGraph) {
        molGraph = 0;
        
        stereoCenters.clear();
        digraph.clear();
        return;
    }

    setup(*labeler.molGraph);
}

unsigned int Chem::CIPConfigurationLabelerImpl::getLabelGeneric(const AtomContainer& cntnr)
{
    auto it = stereoCenters.find(&cntnr);

    if (it == stereoCenters.end())
        return CIPDescriptor::NONE;
    
    rules.enableFullStack(false);
    digraph.clear();
    
    CIPStereoCenter& ctr = *it->second;
    unsigned int label = ctr.label(rules);

    if (label != CIPDescriptor::NONE)
        return label;

    setAuxLabels(ctr);
    
    rules.enableFullStack(true);

    return ctr.label(rules);
}

void Chem::CIPConfigurationLabelerImpl::setAuxLabels(const CIPStereoCenter& ctr)
{
    auxStereoCenters.clear();

    for (const auto& entry : stereoCenters) {
        CIPStereoCenter* curr_ctr = entry.second.get();

        if (curr_ctr == &ctr)
            continue;

        const Atom* const* foci = curr_ctr->getFocusAtoms();

        digraph.getNodes(*foci[0], nodes);
        
        for (auto* node : nodes) {
             if (node->isDuplicate())
                 continue;

             CIPDigraph::Node* low = node;

             if (curr_ctr->getNumFocusAtoms() == 2) {
                 node->getEdges(edges, foci[1]);
                 
                 for (const auto* edge : edges) {
                     if (edge->getOther(*node).getDistance() < node->getDistance())
                         low = &edge->getOther(*node);
                 }
             }
             
             auxStereoCenters.emplace_back(low, curr_ctr);
        }
    }

    std::sort(auxStereoCenters.begin(), auxStereoCenters.end(),
              [](const NodeStereoCenterPair& aux_ctr1, const NodeStereoCenterPair& aux_ctr2) -> bool {
                  return (aux_ctr1.first->getDistance() > aux_ctr2.first->getDistance());
              });

    auxStereoDescrs.clear();
    
    std::size_t prev_root_dist = std::numeric_limits<std::size_t>::max();
    
    for (const auto& entry : auxStereoCenters) {
        CIPDigraph::Node* node = entry.first;

        if (node->getDistance() < prev_root_dist) {
            for (const auto& entry : auxStereoDescrs)
                entry.first->setAuxDescriptor(entry.second);

            prev_root_dist = node->getDistance();
            auxStereoDescrs.clear();
        }
        
        auxStereoDescrs.emplace_back(node, entry.second->label(*node, digraph, rules));
    }

    for (const auto& entry : auxStereoDescrs)
        entry.first->setAuxDescriptor(entry.second);
}

void Chem::CIPConfigurationLabelerImpl::extractAtomCenters()
{
    for (const auto& atom : molGraph->getAtoms()) {
        StereoDescriptor descr = calcStereoDescriptor(atom, *molGraph, 0);
        std::size_t num_ref_atoms = descr.getNumReferenceAtoms();

        if (num_ref_atoms < 3)
            continue;
        
        const Atom* const* ref_atoms = descr.getReferenceAtoms();
        unsigned int config = descr.getConfiguration();

        switch (config) {

            case AtomConfiguration::R:
                config = CIPTetrahedralCenter::LEFT;
                break;
    
            case AtomConfiguration::S:
                config = CIPTetrahedralCenter::RIGHT;
                break;
                
            default:
                config = CIPTetrahedralCenter::UNSPEC;
        }

        StereoCenterPtr ctr_ptr;

        if (num_ref_atoms == 4)
            ctr_ptr.reset(new CIPTetrahedralCenter(digraph,
                                                   &atom,
                                                   { ref_atoms[3], ref_atoms[0], ref_atoms[1], ref_atoms[2] },
                                                   config));
        else
            ctr_ptr.reset(new CIPTetrahedralCenter(digraph,
                                                   &atom,
                                                   { &atom, ref_atoms[0], ref_atoms[1], ref_atoms[2] },
                                                   config));

        stereoCenters.emplace(&atom, std::move(ctr_ptr));
    }
}

void Chem::CIPConfigurationLabelerImpl::extractBondCenters()
{
    for (const auto& bond : molGraph->getBonds()) {
        StereoDescriptor descr = calcStereoDescriptor(bond, *molGraph, 0);

        if (descr.getNumReferenceAtoms() != 4)
            continue;

        const Atom* const* ref_atoms = descr.getReferenceAtoms();
        unsigned int config = descr.getConfiguration();

        switch (config) {

            case BondConfiguration::CIS:
                config = CIPSp2BondCenter::TOGETHER;
                break;

            case BondConfiguration::TRANS:
                config = CIPSp2BondCenter::OPPOSITE;
                break;

            default:
                config = CIPSp2BondCenter::UNSPEC;
        }
        
        StereoCenterPtr ctr_ptr(new CIPSp2BondCenter(digraph,
                                                     { ref_atoms[1], ref_atoms[2] },
                                                     { ref_atoms[0], ref_atoms[3] },
                                                     config));
        
        stereoCenters.emplace(&bond, std::move(ctr_ptr));
    }
}
