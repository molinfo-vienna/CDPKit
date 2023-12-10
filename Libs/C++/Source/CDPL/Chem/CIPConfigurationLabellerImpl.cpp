/* 
 * CIPConfigurationLabellerImpl.cpp 
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


#include "CDPL/Chem/MolecularGraph.hpp"
#include "CDPL/Chem/Atom.hpp"
#include "CDPL/Chem/Bond.hpp"
#include "CDPL/Chem/AtomFunctions.hpp"
#include "CDPL/Chem/BondFunctions.hpp"
#include "CDPL/Chem/AtomConfiguration.hpp"
#include "CDPL/Chem/BondConfiguration.hpp"
#include "CDPL/Chem/StereoDescriptor.hpp"
#include "CDPL/Chem/CIPDescriptor.hpp"

#include "CIPConfigurationLabellerImpl.hpp"
#include "CIPTetrahedralCenter.hpp"
#include "CIPSp2BondCenter.hpp"


using namespace CDPL;


Chem::CIPConfigurationLabellerImpl::CIPConfigurationLabellerImpl():
    molGraph(0)
{}

Chem::CIPConfigurationLabellerImpl::CIPConfigurationLabellerImpl(const CIPConfigurationLabellerImpl& labeller)
{
    copy(labeller);
}

Chem::CIPConfigurationLabellerImpl::~CIPConfigurationLabellerImpl() {}

void Chem::CIPConfigurationLabellerImpl::setup(const MolecularGraph& molgraph)
{
    molGraph = &molgraph;
    
    digraph.setMolecularGraph(molgraph);
    stereoCenters.clear();

    extractAtomCenters();
    extractBondCenters();
}

unsigned int Chem::CIPConfigurationLabellerImpl::getLabel(const Atom& atom)
{
    // TODO
    return CIPDescriptor::NONE;
}

unsigned int Chem::CIPConfigurationLabellerImpl::getLabel(const Bond& bond)
{
    // TODO
    return CIPDescriptor::NONE;
}
            
void Chem::CIPConfigurationLabellerImpl::copy(const CIPConfigurationLabellerImpl& labeller)
{
    if (!labeller.molGraph) {
        molGraph = 0;
        
        stereoCenters.clear();
        digraph.clear();
        return;
    }

    setup(*labeller.molGraph);
}

void Chem::CIPConfigurationLabellerImpl::extractAtomCenters()
{
    for (const auto& atom : molGraph->getAtoms()) {
        StereoDescriptor descr = calcStereoDescriptor(atom, *molGraph, 0);

        if (descr.getNumReferenceAtoms() < 3)
            continue;
/*        
        const Atom* const* ref_atoms = descr.getReferenceAtoms();
        unsigned int config = descr.getConfiguration();

        switch (config) {

         
            default:
                config = CIPTetrahedralCenter::UNSPEC;
        }

        stereoCenters.emplace(&atom, std::move(ctr_ptr));
*/
    }
}

void Chem::CIPConfigurationLabellerImpl::extractBondCenters()
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
