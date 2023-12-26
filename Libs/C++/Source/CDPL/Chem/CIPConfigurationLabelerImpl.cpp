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
   
unsigned int Chem::CIPConfigurationLabelerImpl::getLabel(const AtomContainer& cntnr)
{
    auto it = stereoCenters.find(&cntnr);

    if (it == stereoCenters.end())
        return CIPDescriptor::NONE;

    rules.enableFullStack(false);
    digraph.reset();
    
    auto& ctr = *it->second;
    auto label = ctr.label(rules);

    if (label != CIPDescriptor::NONE)
        return label;
    
    rules.enableFullStack(true);
    
    setAuxLabels(ctr);

    return ctr.label(rules);
}

void Chem::CIPConfigurationLabelerImpl::copy(const CIPConfigurationLabelerImpl& labeler)
{
    if (!labeler.molGraph) {
        molGraph = 0;
        stereoCenters.clear();
        return;
    }

    setup(*labeler.molGraph);
}

void Chem::CIPConfigurationLabelerImpl::setAuxLabels(const CIPStereoCenter& ctr)
{
    auxStereoCenters.clear();

    for (auto& entry : stereoCenters) {
        auto curr_ctr = entry.second.get();

        if (curr_ctr == &ctr)
            continue;

        auto foci = curr_ctr->getFocusAtoms();

        digraph.getNodes(*foci[0], nodes);
        
        for (auto node : nodes) {
             if (node->isDuplicate())
                 continue;

             CIPDigraph::Node* low = node;

             if (curr_ctr->getNumFocusAtoms() == 2) {
                 node->getEdges(edges, foci[1]);
                 
                 for (auto edge : edges) {
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
    
    auto prev_root_dist = std::numeric_limits<std::size_t>::max();
    
    for (auto& entry : auxStereoCenters) {
        auto node = entry.first;

        if (node->getDistance() < prev_root_dist) {
            for (auto& entry : auxStereoDescrs)
                entry.first->setAuxDescriptor(entry.second);

            prev_root_dist = node->getDistance();
            auxStereoDescrs.clear();
        }
        
        auxStereoDescrs.emplace_back(node, entry.second->label(*node, rules));
    }

    for (auto& entry : auxStereoDescrs)
        entry.first->setAuxDescriptor(entry.second);
}

void Chem::CIPConfigurationLabelerImpl::extractAtomCenters()
{
    for (auto& atom : molGraph->getAtoms()) {
        auto descr = calcStereoDescriptor(atom, *molGraph, 0);
        auto num_ref_atoms = descr.getNumReferenceAtoms();

        if (num_ref_atoms < 3)
            continue;

        auto config = descr.getConfiguration();

        switch (config) {

            case AtomConfiguration::R:
                config = CIPTetrahedralCenter::LEFT;
                break;
    
            case AtomConfiguration::S:
                config = CIPTetrahedralCenter::RIGHT;
                break;

            case AtomConfiguration::NONE:
                continue;
                
            default:
                config = CIPTetrahedralCenter::UNSPEC;
        }

        auto ref_atoms = descr.getReferenceAtoms();
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
    for (auto& bond : molGraph->getBonds()) {
        auto descr = calcStereoDescriptor(bond, *molGraph, 0);

        if (descr.getNumReferenceAtoms() != 4)
            continue;

        auto config = descr.getConfiguration();

        switch (config) {

            case BondConfiguration::CIS:
                config = CIPSp2BondCenter::TOGETHER;
                break;

            case BondConfiguration::TRANS:
                config = CIPSp2BondCenter::OPPOSITE;
                break;

            case BondConfiguration::NONE:
                continue;
                
            default:
                config = CIPSp2BondCenter::UNSPEC;
        }

        auto ref_atoms = descr.getReferenceAtoms();
        
        StereoCenterPtr ctr_ptr(new CIPSp2BondCenter(digraph,
                                                     { ref_atoms[1], ref_atoms[2] },
                                                     { ref_atoms[0], ref_atoms[3] },
                                                     config));
        
        stereoCenters.emplace(&bond, std::move(ctr_ptr));
    }
}
